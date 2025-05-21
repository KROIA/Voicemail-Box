#include "utilities/AudioPlayer.hpp"
#include "BSP_VoiceMailBox.hpp"

namespace VoiceMailBox
{
	AudioPlayer::AudioPlayer(AudioCodec& codec)
		: Logger("AudioPlayer")
		, m_codec(codec)
		, m_isPlaying(false)
		//, m_wavFile()
		, m_playingLed(nullptr)
	{
		//m_wavFile.setBitsPerSample(codec.getBitsPerSample());
		//m_wavFile.setNumChannels(codec.getNumChannels());
		//m_wavFile.setSampleRate(codec.getSampleRate());
	}
	AudioPlayer::AudioPlayer(AudioCodec& codec, DigitalPin& playingLed)
		: Logger("AudioPlayer")
		, m_codec(codec)
		, m_isPlaying(false)
		//, m_wavFile()
		, m_playingLed(&playingLed)
	{
		//m_wavFile.setBitsPerSample(codec.getBitsPerSample());
		//m_wavFile.setNumChannels(codec.getNumChannels());
		//m_wavFile.setSampleRate(codec.getSampleRate());
		if (m_playingLed)
			m_playingLed->set(false);
	}
	AudioPlayer::~AudioPlayer()
	{
		if (isPlaying())
		{
			stopPlayback();
		}
	}

	bool AudioPlayer::startPlayback()
	{
		if (m_isPlaying)
		{
			logln("Already Playing");
			// Already Playing
			return false;
		}

		if (m_mp3.startDecode("record.mp3", m_codec.getBufferSize(), m_playingLed))
		{
			logln("Playing started");
			if (m_playingLed)
				m_playingLed->set(true);
			m_isPlaying = true;
			return true;
		}
		/*if (m_wavFile.open("record.wav", File::AccessMode::read))
		{
			logln("Playing started");
			if (m_playingLed)
				m_playingLed->set(true);
			return true;
		}
		logln("Failed to open file for playing");*/
		return false;
	}
	bool AudioPlayer::stopPlayback()
	{
		if (!m_isPlaying)
		{
			logln("Not Playing");
			// Not Playing
			return false;
		}
		m_isPlaying = false;
		// Clear TX buffer
		m_codec.clearTxBuf();
		m_mp3.stopDecode();
		//m_wavFile.close();
		if (m_playingLed)
			m_playingLed->set(false);
		logln("Playing stopped");
		return true;
	}

	void AudioPlayer::update()
	{
		if (!m_isPlaying)
			return;
		if (m_codec.isDataReadyAndClear())
			processAudioSamples(m_codec.getTxBufPtr(), m_codec.getBufferSize());
	}

	void AudioPlayer::processAudioSamples(volatile int16_t* samples, uint32_t size)
	{
		if (m_playingLed)
			m_playingLed->set(1);
		if (m_mp3.decodeProcess((int16_t*)samples, size))
		{
			
		}
		else
		{
			logln("Failed to decode audio samples");
			stopPlayback();
		}
		if (m_playingLed)
			m_playingLed->set(0);
		/*if (m_wavFile.isOpen())
		{
			uint32_t bytesRead = m_wavFile.readAudioSamples(samples, size);
			if (m_playingLed)
				m_playingLed->toggle();
			if (bytesRead == 0)
			{
				logln("End of file reached");
				stopPlayback();
			}
		}
		else
		{
			logln("Failed to read audio samples, file is not open: " + m_wavFile.getPath());
		}*/
	}
}
