#include "utilities/AudioPlayer.hpp"

namespace VoiceMailBox
{
	AudioPlayer::AudioPlayer(AudioCodec& codec)
#ifdef VMB_USE_LOGGER_OBJECTS
		: Logger("AudioPlayer")
		, m_codec(codec)
#else
		: m_codec(codec)
#endif
		, m_isPlaying(false)
		, m_isPaused(false)
		, m_loopCount(0)
	    , m_file(codec.getSampleRate(), 48, codec.getNumChannels())
		, m_playingLed(nullptr)
	{

	}
	AudioPlayer::AudioPlayer(AudioCodec& codec, DigitalPin& playingLed)
#ifdef VMB_USE_LOGGER_OBJECTS
		: Logger("AudioPlayer")
		, m_codec(codec)
#else
		: m_codec(codec)
#endif
		, m_isPlaying(false)
		, m_isPaused(false)
		, m_loopCount(0)
		, m_file(codec.getSampleRate(), 48, codec.getNumChannels())
		, m_playingLed(&playingLed)
	{
		if (m_playingLed)
			m_playingLed->set(false);
	}
	AudioPlayer::~AudioPlayer()
	{
		if (isPlaying())
		{
			stop();
		}
	}

	bool AudioPlayer::start(const std::string& filePath)
	{
		return start(filePath, 1);
	}
	bool AudioPlayer::start(const std::string& filePath, uint32_t repetitions)
	{
		if (repetitions == 0)
			return false;
		if (m_isPlaying)
		{
			VMB_LOGLN("Already Playing");
			return false;
		}
		if (m_file.open(filePath, File::AccessMode::read))
		{
			VMB_LOGLN("Playing started");
			m_isPlaying = true;
			m_isPaused = false;
			m_codec.clearTxBuf();
			m_codec.clearDataReadyFlag();
			m_firstPlayingUpdate = true;
			m_loopCount = repetitions-1;
			return true;
		}
		VMB_LOGLN("Failed to open file for playing");
		return false;
	}
	bool AudioPlayer::stop()
	{
		if (!m_isPlaying)
		{
			VMB_LOGLN("Not Playing");
			return false;
		}
		m_isPlaying = false;
		m_isPaused = false;
		m_loopCount = 0;
		m_codec.clearTxBuf();
		m_file.close();
		VMB_LOGLN("Playing stopped");
		return true;
	}

	bool AudioPlayer::pause()
	{
		if (m_isPlaying && !m_isPaused)
		{
			m_isPaused = true;
			m_codec.clearTxBuf();
			VMB_LOGLN("Playing paused");
			return true;
		}
		if (!m_isPlaying)
		{
			VMB_LOGLN("Not Playing");
			return false;
		}
		VMB_LOGLN("Already Paused");
		return false;
	}

	bool AudioPlayer::resume()
	{
		if (m_isPlaying && m_isPaused)
		{
			m_isPaused = false;
			VMB_LOGLN("Playing resumed");
			return true;
		}
		if (!m_isPlaying)
		{
			VMB_LOGLN("Not Playing");
			return false;
		}
		VMB_LOGLN("Already Playing");
		return false;
	}

	void AudioPlayer::update()
	{
		if (!m_isPlaying || m_isPaused)
			return;
		
		if (m_codec.isDataReadyAndClearFlag())
			processAudioSamples(m_codec.getTxBufPtr(), m_codec.getBufferSize());
	}

	void AudioPlayer::processAudioSamples(volatile int16_t* dmaTxBuff, uint32_t size)
	{
		if (m_playingLed)
			m_playingLed->set(1);

		if (m_file.eof())
		{
			VMB_LOGLN("End of file reached");
			if (m_loopCount > 0)
			{
				--m_loopCount;
				m_firstPlayingUpdate = true;
				m_file.seek(0);
			}
			else
			{
				stop();
				if (m_playingLed)
					m_playingLed->set(0);
				return;
			}
		}

		// size/2 because, size is in the DMA size namespace which means size of int16_t elements.
		// readAudioSamples requires the amount of samples, each sample consists of 2 * 16 bit samples (left and right channel)
		uint32_t decodedSamples = m_file.readAudioSamples((int16_t*)dmaTxBuff, size / 2);
		if (m_firstPlayingUpdate)
		{
			if (m_playingLed)
				m_playingLed->set(0);
			// At the start of the file, the convertion must be done twice. 
			// We loose some audio because of that but otherwise it creates a lot of noise in the beginning.
			decodedSamples += m_file.readAudioSamples((int16_t*)dmaTxBuff, size / 2);
			m_firstPlayingUpdate = false;
			if (m_playingLed)
				m_playingLed->set(1);
		}
		VMB_LOGLN("Decoded " + std::to_string(decodedSamples) + " audio samples from mp3");
		if(decodedSamples < size/2)
		{
			VMB_LOGLN("End of file reached");
			if (m_loopCount > 0)
			{
				--m_loopCount;
				m_firstPlayingUpdate = true;
				m_file.seek(0);
			}
		}
		
		if (m_playingLed)
			m_playingLed->set(0);
	}
}
