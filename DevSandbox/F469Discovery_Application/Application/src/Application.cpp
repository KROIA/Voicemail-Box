/*
 * Application.cpp
 *
 *  Created on: May 7, 2025
 *      Author: Alex
 */
#include "Application.h"
#include "BSP_VoiceMailBox.hpp"
#include <math.h>

void processData();
void setup()
{

	using namespace VoiceMailBox;
	VoiceMailBox::setup();
	sendToWifi("AT\r\n");

	delay(3);
	while(!canReceiveFromWifi())
	{
		println("Waiting for response from WIFI...");
		delay(2);
		sendToWifi("AT\r\n");
	}
	char response[20] = { 0 };
	if(receiveFromWifi(response, sizeof(response)))
	{
		print("Response: ");
		delay(10);
		println(response);
	}
}

void loop()
{
	using namespace VoiceMailBox;
	//setLed(LED::LED0, getButtonState(Button::BTN0));
	//setLed(LED::LED1, getButtonState(Button::BTN1));


	Codec_TLV320AIC3104& codec = getCodec();
	if(codec.isDataReadyAndClear())
		processData();
}

void processData()
{
	using namespace VoiceMailBox;
	setLed(LED::LED0, 1);
	Codec_TLV320AIC3104& codec = getCodec();
	codec.startDataProcessing();
	static float performance = 0;
	static float leftIn, leftOut;
	static float rightIn, rightOut;

	static float absFIER = 0;
	const static float scale = 0.01f;
	const static float scaleInv =  1/scale;

	volatile int16_t* adcData = codec.getRxBufPtr();
	volatile int16_t* dacData = codec.getTxBufPtr();

	static uint32_t maxPotiVal = getPotiMaxValue(Poti::POT1);


	uint32_t rawPoti = getPotiValue(Poti::POT1);
	float poti = std::exp(0.5f-(float)rawPoti/(float)maxPotiVal);

	for(uint8_t n=0; n<codec.getBufferSize(); n++)
	{
		// redirect microphone to speaker
		dacData[n] = (int16_t)((float)adcData[n]*poti);
		//print("%i\r", adcData[n]);
	}
	/*for(uint8_t n=0; n<codec.getBufferSize()/2-1; n+=2)
	{
		// Left Channel

		// Get ADC input and convert to float
		leftIn = adcData[n] * scale;
		//if(leftIn > 1.0f)
		//	leftIn -= 2.0f;

		leftOut = leftIn;

		dacData[n] = (int16_t)(leftOut * scaleInv);


		// Right Channel

		// Get ADC input and convert to float
		rightIn = adcData[n+1] * scale;
		//if(rightIn > 1.0f)
		//	rightIn -= 2.0f;

		rightOut = leftOut;

		//float absL = leftIn;
		//float absR = rightIn;
		//if(absL < 0)
		//	absL = -absL;
		//if(absR < 0)
		//	absR = -absR;

		//absFIER = (absFIER*0.9f) + (0.1f*(absL + absR));
		absFIER = leftIn;

		dacData[n+1] = (int16_t)(rightOut * scaleInv);

		//print("%.1f\r", absFIER);

	}*/

	//print("%f\r", performance);
	performance = codec.getProcessingTimeRatio();
	setLed(LED::LED0, 0);
	codec.endDataProcessing();
}
