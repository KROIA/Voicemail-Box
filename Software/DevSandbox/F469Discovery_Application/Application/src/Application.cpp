/*
 * Application.cpp
 *
 *  Created on: May 7, 2025
 *      Author: Alex
 */
#include "Application.h"
#include "BSP_VoiceMailBox.hpp"
#include <math.h>
#include <string>
#include <cstring>


VoiceMailBox::Codec_TLV320AIC3104& codec = VoiceMailBox::getCodec();
VoiceMailBox::DigitalPin& statusLED = VoiceMailBox::getLed(VoiceMailBox::LED::LED0);

void setup()
{
	using namespace VoiceMailBox;
	VoiceMailBox::setup();
}

void loop()
{
	using namespace VoiceMailBox;
	VoiceMailBox::update();

	// Process the codecs audio data
	if (codec.isDataReadyAndClearFlag())
	{
		statusLED.set(1);
		int16_t* txBuffer = (int16_t*)codec.getTxBufPtr();
		int16_t* rxBuffer = (int16_t*)codec.getRxBufPtr();
		uint32_t size = codec.getBufferSize();

		// Redirect capture to the output
		memcpy(txBuffer, rxBuffer, size * sizeof(int16_t));
		statusLED.set(0);
	}


	// Ajust the microphone input gain in dB
	static uint32_t time = getTickCountInMs();
	static float lastMicrophoneGainDB = 0;
	uint32_t currentMs = getTickCountInMs();
	if (time + 1000 < currentMs)
	{
		time = getTickCountInMs();
		auto& codec = getCodec();
		float gainDB = 59.5f - getPotentiometer(Potentiometer::POT1).getValue() * 59.5f / getPotentiometer(Potentiometer::POT1).getMaxValue();
		if (std::abs(gainDB - lastMicrophoneGainDB) > 0.25f)
		{
			lastMicrophoneGainDB = gainDB;
			codec.setMicrophoneGainDB(gainDB);
			println("Set microphone gain to %.2f dB", gainDB);
		}
	}
}
