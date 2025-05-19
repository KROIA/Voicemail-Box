#ifndef AUDIO_RECORDER_HPP
#define AUDIO_RECORDER_HPP
/**
 * @brief 
 * @details 
 * 
 * @author Alex Krieg
 */


#include <string>
#include "settings.h"
#include "Logger.hpp"
#include "HAL_abstraction.hpp"
#include "peripherals/AudioCodec.hpp"
#include "peripherals/DigitalPin.hpp"

#include "WAVFile.hpp"
#include "MP3.hpp"

namespace VoiceMailBox
{
	class AudioRecorder : public Logger
	{
	public:
		AudioRecorder(AudioCodec& codec);
		AudioRecorder(AudioCodec& codec, DigitalPin &recordingLed);
		virtual ~AudioRecorder();

		virtual bool startRecording();
		virtual bool stopRecording();

		bool isRecording() { return m_isRecording; }


		virtual void update();

	protected:
		virtual void processAudioSamples(volatile int16_t* samples, uint32_t size);		

		AudioCodec& m_codec;	// AudioCodec
		bool m_isRecording;

		WAVFile m_wavFile;	// WAV file object
		File m_mp3File;	// MP3 file object

		DigitalPin* m_recordingLed;	// Recording LED pin


		MP3 m_mp3;	// MP3 encoder object
	};
}
#endif
