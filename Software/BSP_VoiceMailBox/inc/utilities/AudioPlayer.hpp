#ifndef AUDIO_PLAYER_HPP
#define AUDIO_PLAYER_HPP
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

namespace VoiceMailBox
{
	class AudioPlayer : public Logger
	{
	public:
		AudioPlayer(AudioCodec& codec);
		AudioPlayer(AudioCodec& codec, DigitalPin& playingLed);
		virtual ~AudioPlayer();

		virtual bool startPlayback();
		virtual bool stopPlayback();

		bool isPlaying() { return m_isPlaying; }


		virtual void update();

	protected:
		virtual void processAudioSamples(volatile int16_t* samples, uint32_t size);

		AudioCodec& m_codec;	// AudioCodec
		bool m_isPlaying;

		WAVFile m_wavFile;	// WAV file object

		DigitalPin* m_playingLed;	// Recording LED pin
	};
}
#endif
