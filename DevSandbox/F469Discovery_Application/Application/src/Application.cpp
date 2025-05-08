/*
 * Application.cpp
 *
 *  Created on: May 7, 2025
 *      Author: Alex
 */
#include "Application.h"
#include "BSP_VoiceMailBox.hpp"


void setup()
{
	/*
	using namespace VoiceMailBox;
	VoiceMailBox::setup();
	sendToWifi("AT\r\n");

	delay(10);
	while(!canReceiveFromWifi())
	{
		println("Waiting for response from WIFI...");
		delay(100);
		sendToWifi("AT\r\n");
	}
	char response[20] = { 0 };
	if(receiveFromWifi(response, sizeof(response)))
	{
		print("Response: ");
		delay(10);
		println(response);
	}*/

}

void loop()
{
	using namespace VoiceMailBox;
	//setLed(LED::LED0, getButtonState(Button::BTN0));
	//setLed(LED::LED1, getButtonState(Button::BTN1));

	//print("Poti %i\n\r",getPotiValue(Poti::POT1));

	//GPIO_PinState state = HAL_GPIO_ReadPin(BTN0_GPIO_Port, BTN0_Pin);
		  //BSP_VOICE_MAIL_BOX_setLed0((bool)state);
		  //HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, state);


	//delay(10);
}
