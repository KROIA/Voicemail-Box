#include "utilities/AudioRecorder.hpp"
#include "BSP_VoiceMailBox.hpp"


namespace VoiceMailBox
{
	AudioRecorder::AudioRecorder(AudioCodec& codec)
		: Logger("AudioRecorder")
		, m_codec(codec)
		, m_isRecording(false)
		, m_wavFile()
		, m_recordingLed(nullptr)
	{
		m_wavFile.setBitsPerSample(codec.getBitsPerSample());
		m_wavFile.setNumChannels(codec.getNumChannels());
		m_wavFile.setSampleRate(codec.getSampleRate());
	}
	AudioRecorder::AudioRecorder(AudioCodec& codec, DigitalPin& recordingLed)
		: Logger("AudioRecorder")
		, m_codec(codec)
		, m_isRecording(false)
		, m_wavFile()
		, m_recordingLed(&recordingLed)
	{
		m_wavFile.setBitsPerSample(codec.getBitsPerSample());
		m_wavFile.setNumChannels(codec.getNumChannels());
		m_wavFile.setSampleRate(codec.getSampleRate());
		if (m_recordingLed)
			m_recordingLed->set(false);
	}
	AudioRecorder::~AudioRecorder()
	{
		if (isRecording())
		{
			stopRecording();
		}
	}

	bool AudioRecorder::startRecording()
	{
		if (m_isRecording)
		{
			logln("Already recording");
			// Already recording
			return false;
		}


		//if (m_wavFile.open("record.wav", File::AccessMode::write))
		if (m_mp3File.open("record.mp3", File::AccessMode::write))
		{
			logln("Recording started");
			if (m_recordingLed)
				m_recordingLed->set(true);
			m_isRecording = true;
			return true;
		}
		logln("Failed to open file for recording");
		return false;
	}
	bool AudioRecorder::stopRecording()
	{
		if (!m_isRecording)
		{
			logln("Not recording");
			// Not recording
			return false;
		}
		m_isRecording = false;
		//m_wavFile.close();
		m_mp3File.close();
		if (m_recordingLed)
			m_recordingLed->set(false);
		logln("Recording stopped");
		return true;
	}

	void AudioRecorder::update()
	{
		if (!m_isRecording)
			return;
		if (m_codec.isDataReadyAndClear())
			processAudioSamples(m_codec.getRxBufPtr(), m_codec.getBufferSize());
	}

	void AudioRecorder::processAudioSamples(volatile int16_t* samples, uint32_t size)
	{
		

		//if (size != 576 * 2) // 576 samples = 1152 bytes = 1.5ms @ 48kHz
		//{
		//	logln("Invalid size: " + std::to_string(size));
		//	return;
		//}

		for (uint32_t i = 0; i < size / (2 * 576); ++i)
		{
			if (m_recordingLed)
				m_recordingLed->toggle();
			int8_t* mp3Buffer = nullptr;
			uint32_t bytesToWrite = m_mp3.encode(mp3Buffer, (int16_t*)(samples + (i* 2 * 576)));
			if (bytesToWrite > 0)
			{
				m_mp3File.write((const char*)mp3Buffer, bytesToWrite);
				logln("Processing " + std::to_string(bytesToWrite) + " audio samples");
			}
			else
			{
				//logln("Failed to encode audio samples");
			}
		}
		if (m_recordingLed)
			m_recordingLed->set(0);

		//m_wavFile.writeAudioSamples(samples, size);
		//log("Processing " + std::to_string(size) + " audio samples");
	}
}
