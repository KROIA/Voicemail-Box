#ifndef AUDIO_RECORDER_HPP
#define AUDIO_RECORDER_HPP
/**
 * @author Alex Krieg
 */


#include <string>
#include "settings.h"
#include "Logger.hpp"
#include "HAL_abstraction.hpp"
#include "peripherals/AudioCodec.hpp"
#include "peripherals/DigitalPin.hpp"

#include "Updatable.hpp"
#include "WAVFile.hpp"
#include "MP3File.hpp"

namespace VoiceMailBox
{
	/**
	 * @brief This class is used record audio samples to a given audio file (mp3)
	 * 	
	 * @details A reference to the audio codec must be passed to the constructor, 
	 *          which is used to play the audio data.
	 * 
	 *          Additionally, a digital pin can be passed to the constructor, which is used to
	 *          visualize debug information on the pin during capture.
	 *          The pin is set to HIGH when a audio sample convertion starts and set to LOW when the conversion is finished.
	 *          This indicates the time it takes to convert the audio samples provided from the last DMA transfer.
	 *          This time must always be less than the time it takes for the DMA to finish its half transfer.
	 */
	class AudioRecorder :
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
		AudioRecorder(AudioCodec& codec);

		/**
		 * @brief Constructor
		 * @param codec reference on which the audio gets played on
		 * @param playingLed for debugging purposes
		 */
		AudioRecorder(AudioCodec& codec, DigitalPin &recordingLed);

		virtual ~AudioRecorder();

		/**
		 * @brief Starts the recording and saves the audio samples to a given mp3 file.
		 * @param filePath to the mp3 file. Example: "myAudio.mp3"
		 * @return true if the recording was started successfully, false otherwise.
		 */
		virtual bool start(const std::string& filePath);

		/**
		 * @brief Stops the recording of the current audio file.
		 * @return true if the recording was stopped successfully
		 *         false if no recording was in progress
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
		 * @return true if recorder is currently recording, false otherwise.
		 */
		bool isRecording() { return m_isRecording && !m_isPaused; }

		/**
		 * @return true if a file is currently paused
		 */
		bool isPaused() { return m_isPaused; }

		/**
		 * @brief This function needs to be called in the main loop.
		 *        It gathers the audio samples from the DMA buffer and saves it converted as mp3 to the specified file.
		 */
		void update() override;

	protected:
		/**
		 * @brief This function is called when the DMA transfer is half complete or complete.
		 *        It processes the audio samples from the DMA buffer and saves it to the file.
		 * @param dmaRxBuff Pointer from the DMA buffer
		 * @param size Size of the DMA buffer
		 */
		virtual void processAudioSamples(volatile int16_t* dmaRxBuff, uint32_t size);		

		AudioCodec& m_codec;	// AudioCodec
		bool m_isRecording;
		bool m_isPaused;

		//WAVFile m_wavFile;	// WAV file object
		MP3File m_file;	// MP3 file object

		DigitalPin* m_recordingLed;	// Recording LED pin
	};
}
#endif
