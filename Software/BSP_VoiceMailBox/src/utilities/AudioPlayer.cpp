#include "utilities/AudioPlayer.hpp"
#include "BSP_VoiceMailBox.hpp"

namespace VoiceMailBox
{
	AudioPlayer::AudioPlayer(AudioCodec& codec)
		: Logger("AudioPlayer")
		, m_codec(codec)
		, m_isPlaying(false)
	    , m_file(codec.getSampleRate(), 48, codec.getNumChannels())
		, m_playingLed(nullptr)
	{

	}
	AudioPlayer::AudioPlayer(AudioCodec& codec, DigitalPin& playingLed)
		: Logger("AudioPlayer")
		, m_codec(codec)
		, m_isPlaying(false)
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
			stopPlayback();
		}
	}

	bool AudioPlayer::startPlayback(const std::string& filePath)
	{
		if (m_isPlaying)
		{
			logln("Already Playing");
			return false;
		}
		if (m_file.open(filePath, File::AccessMode::read))
		{
			logln("Playing started");
			m_isPlaying = true;
			m_codec.clearTxBuf();
			m_codec.clearDataReadyFlag();
			m_firstPlayingUpdate = true;
			return true;
		}
		logln("Failed to open file for playing");
		return false;
	}
	bool AudioPlayer::stopPlayback()
	{
		if (!m_isPlaying)
		{
			logln("Not Playing");
			return false;
		}
		m_isPlaying = false;
		m_codec.clearTxBuf();
		m_file.close();
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

	void AudioPlayer::processAudioSamples(volatile int16_t* dmaTxBuff, uint32_t size)
	{
		if (m_playingLed)
			m_playingLed->set(1);

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
		logln("Decoded " + std::to_string(decodedSamples) + " audio samples from mp3");
		if(decodedSamples < size/2)
		{
			logln("End of file reached");
			stopPlayback();
		}
		
		if (m_playingLed)
			m_playingLed->set(0);
	}
}
