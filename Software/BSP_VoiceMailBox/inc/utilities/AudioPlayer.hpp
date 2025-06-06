#ifndef AUDIO_PLAYER_HPP
#define AUDIO_PLAYER_HPP
/**
 * @author Alex Krieg
 */


#include <string>
#include "Logger.hpp"
#include "HAL_abstraction.hpp"
#include "peripherals/AudioCodec.hpp"
#include "peripherals/digitalPin.hpp"

#include "Updatable.hpp"
#include "WAVFile.hpp"
#include "MP3File.hpp"

namespace VoiceMailBox
{
	/**
	 * @brief This class is used to play audio from a given audio file (mp3)
	 * 
	 * @details A reference to the audio codec must be passed to the constructor, 
	 *          which is used to play the audio data.
	 * 
	 *          Additionally, a digital pin can be passed to the constructor, which is used to
	 *          visualize debug information on the pin during playback.
	 *          The pin is set to HIGH when a audio sample convertion starts and set to LOW when the conversion is finished.
	 *          This indicates the time it takes to convert the audio samples needed for the next DMA transfer.
	 *          This time must always be less than the time it takes for the DMA to finish its half transfer.
	 */
	class AudioPlayer : 
#ifdef VMB_USE_LOGGER_OBJECTS
		public Logger, 
#endif
		public Updatable
	{
	public:
		/**
		 * @brief Constructor
		 * @param codec reference on which the audio gets played on
		 */
		AudioPlayer(AudioCodec& codec);

		/**
		 * @brief Constructor
		 * @param codec reference on which the audio gets played on
		 * @param playingLed for debugging purposes
		 */
		AudioPlayer(AudioCodec& codec, DigitalPin& playingLed);

		virtual ~AudioPlayer();

		/**
		 * @brief Starts the playback from a given mp3 file.
		 * @param filePath to the mp3 file. Example: "myAudio.mp3"
		 * @return true if the playback was started successfully, false otherwise.
		 */
		virtual bool start(const std::string &filePath);

		/**
		 * @brief Starts the playback from a given mp3 file for a given number of repetitions.
		 * @param filePath to the mp3 file. Example: "myAudio.mp3"
		 * @param repetitions amount how many times the file should be played. Value must be greater than 0.
		 * @return true if the playback was started successfully, false otherwise.
		 */
		virtual bool start(const std::string &filePath, uint32_t repetitions);

		/**
		 * @brief Stops the playback of the current audio file.
		 * @return true if the playback was stopped successfully
		 *         false if no playback was active
		 */
		virtual bool stop();

		/**
		 * @brief Pauses the playback of the current audio file.
		 * @return true if the playback was paused successfully, false if no playback was active
		 */
		virtual bool pause();

		/**
		 * @brief Resumes a paused playback of the current audio file.
		 * @return true if the playback was resumed successfully, false if no playback or pause was active
		 */
		virtual bool resume();

		/**
		 * @return true if a file is currently playing 
		 */
		bool isPlaying() { return m_isPlaying && !m_isPaused; }

		/**
		 * @return true if a file is currently paused
		 */
		bool isPaused() { return m_isPaused; }

		/**
		 * @brief This function needs to be called in the main loop.
		 *        It provides the audio codec with new audio samples when the codecs DMA is ready for new data.
		 */
		void update() override;

	protected:
		/**
		 * @brief This function is called when the DMA transfer is half complete or complete.
		 *        It converts the mp3 data to PCM audio samples and fills the DMA buffer with new data.
		 * @param dmaTxBuff pointer to the DMA buffer
		 * @param size size of the DMA buffer
		 */
		virtual void processAudioSamples(volatile int16_t* dmaTxBuff, uint32_t size);


		AudioCodec& m_codec;	// AudioCodec
		bool m_isPlaying; 
		bool m_isPaused;
		uint32_t m_loopCount;
		bool m_firstPlayingUpdate = false; 

#if VMB_USED_AUDIO_FORMAT == VMB_AUDIO_FORMAT_WAV
		WAVFile m_file;	// WAV file object
#elif VMB_USED_AUDIO_FORMAT == VMB_AUDIO_FORMAT_MP3
		MP3File m_file;	// MP3 file object
#endif

		DigitalPin* m_playingLed;	// Recording LED pin
	};
}
#endif
