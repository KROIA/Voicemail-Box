#include "utilities/AudioRecorder.hpp"


namespace VoiceMailBox
{
	AudioRecorder::AudioRecorder(AudioCodec& codec)
#ifdef VMB_USE_LOGGER_OBJECTS
		: Logger("AudioRecorder")
		, m_codec(codec)
#else
		: m_codec(codec)
#endif
		, m_isRecording(false)
		, m_file(codec.getSampleRate(), 48, codec.getNumChannels())
		, m_recordingLed(nullptr)
	{
	}
	AudioRecorder::AudioRecorder(AudioCodec& codec, DigitalPin& recordingLed)
#ifdef VMB_USE_LOGGER_OBJECTS
		: Logger("AudioRecorder")
		, m_codec(codec)
#else
		: m_codec(codec)
#endif
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
			stop();
		}
	}

	bool AudioRecorder::start(const std::string& filePath)
	{
		if (m_isRecording)
		{
			VMB_LOGLN("Already recording");
			return false;
		}

		if (m_file.open(filePath, File::AccessMode::write))
		{
			VMB_LOGLN("Recording started");
			m_isRecording = true;
			m_isPaused = false;
			m_codec.clearDataReadyFlag();
			return true;
		}
		VMB_LOGLN("Failed to open file for recording");
		return false;
	}
	bool AudioRecorder::stop()
	{
		if (!m_isRecording)
		{
			VMB_LOGLN("Not recording");
			return false;
		}
		m_isRecording = false;
		m_isPaused = false;
		m_file.close();
		VMB_LOGLN("Recording stopped");
		return true;
	}

	bool AudioRecorder::pause()
	{
		if (m_isRecording && !m_isPaused)
		{
			m_isPaused = true;
			m_codec.clearTxBuf();
			VMB_LOGLN("Recording paused");
			return true;
		}
		if (!m_isRecording)
		{
			VMB_LOGLN("Not Recording");
			return false;
		}
		VMB_LOGLN("Already Paused");
		return false;
	}

	bool AudioRecorder::resume()
	{
		if (m_isRecording && m_isPaused)
		{
			m_isPaused = false;
			VMB_LOGLN("Recording resumed");
			return true;
		}
		if (!m_isRecording)
		{
			VMB_LOGLN("Not Recording");
			return false;
		}
		VMB_LOGLN("Already Playing");
		return false;
	}

	void AudioRecorder::update()
	{
		if (!m_isRecording || m_isPaused)
			return;
		if (m_codec.isDataReadyAndClearFlag())
			processAudioSamples(m_codec.getRxBufPtr(), m_codec.getBufferSize());
	}

	void AudioRecorder::processAudioSamples(volatile int16_t* dmaRxBuff, uint32_t size)
	{
		if (m_recordingLed)
			m_recordingLed->set(1);
		// size/2 because, size is in the DMA size namespace which means size of int16_t elements.
		// readAudioSamples requires the amount of samples, each sample consists of 2 * 16 bit samples (left and right channel)
		uint32_t bytesWritten = m_file.writeAudioSamples((int16_t*)dmaRxBuff, size / 2);

		VMB_LOGLN("Saved " + std::to_string(bytesWritten) + " bytes to mp3");
		if (m_recordingLed)
			m_recordingLed->set(0);
	}
}
