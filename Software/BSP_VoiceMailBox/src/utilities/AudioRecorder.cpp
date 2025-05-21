#include "utilities/AudioRecorder.hpp"
#include "BSP_VoiceMailBox.hpp"


namespace VoiceMailBox
{
	AudioRecorder::AudioRecorder(AudioCodec& codec)
		: Logger("AudioRecorder")
		, m_codec(codec)
		, m_isRecording(false)
		, m_file(codec.getSampleRate(), 48, codec.getNumChannels())
		, m_recordingLed(nullptr)
	{
	}
	AudioRecorder::AudioRecorder(AudioCodec& codec, DigitalPin& recordingLed)
		: Logger("AudioRecorder")
		, m_codec(codec)
		, m_isRecording(false)
		, m_file(codec.getSampleRate(), 48, codec.getNumChannels())
		, m_recordingLed(&recordingLed)
	{
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

	bool AudioRecorder::startRecording(const std::string& filePath)
	{
		if (m_isRecording)
		{
			logln("Already recording");
			return false;
		}

		if (m_file.open(filePath, File::AccessMode::write))
		{
			logln("Recording started");
			m_isRecording = true;
			m_codec.clearDataReadyFlag();
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
			return false;
		}
		m_isRecording = false;
		m_file.close();
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

	void AudioRecorder::processAudioSamples(volatile int16_t* dmaRxBuff, uint32_t size)
	{
		if (m_recordingLed)
			m_recordingLed->set(1);
		// size/2 because, size is in the DMA size namespace which means size of int16_t elements.
		// readAudioSamples requires the amount of samples, each sample consists of 2 * 16 bit samples (left and right channel)
		uint32_t bytesWritten = m_file.writeAudioSamples((int16_t*)dmaRxBuff, size / 2);

		logln("Saved " + std::to_string(bytesWritten) + " bytes to mp3");
		if (m_recordingLed)
			m_recordingLed->set(0);
	}
}
