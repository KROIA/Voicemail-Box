#ifndef AUDIO_PLAYER_HPP
#define AUDIO_PLAYER_HPP
/**
 * @author Alex Krieg
 */


#include <string>
#include "settings.h"
#include "Logger.hpp"
#include "HAL_abstraction.hpp"
#include "peripherals/AudioCodec.hpp"
#include "peripherals/DigitalPin.hpp"

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
	class AudioPlayer : public Logger
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
		virtual bool startPlayback(const std::string &filePath);

		/**
		 * @brief Stops the playback of the current audio file.
		 * @return true if the playback was stopped successfully
		 *         false if no playback was active
		 */
		virtual bool stopPlayback();

		/**
		 * @return true if a file is currently playing 
		 */
		bool isPlaying() { return m_isPlaying; }


		/**
		 * @brief This function needs to be called in the main loop.
		 *        It provides the audio codec with new audio samples when the codecs DMA is ready for new data.
		 */
		virtual void update();

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
		bool m_firstPlayingUpdate = false; 

		//WAVFile m_wavFile;	// WAV file object
		MP3File m_file;

		DigitalPin* m_playingLed;	// Recording LED pin
	};
}
#endif
