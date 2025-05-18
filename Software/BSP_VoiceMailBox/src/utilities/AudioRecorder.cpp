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

		m_isRecording = true;
		if (m_wavFile.open("record.wav", File::AccessMode::write))
		{
			logln("Recording started");
			if (m_recordingLed)
				m_recordingLed->set(true);
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
		m_wavFile.close();
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
		if (m_recordingLed)
			m_recordingLed->toggle();
		m_wavFile.writeAudioSamples(samples, size);
		//log("Processing " + std::to_string(size) + " audio samples");
	}
}
