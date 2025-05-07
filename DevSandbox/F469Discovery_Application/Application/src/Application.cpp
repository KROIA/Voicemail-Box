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

}

void loop()
{
	using namespace VoiceMailBox;
	setLed(LED::LED0, getButtonState(Button::BTN0));
	setLed(LED::LED1, getButtonState(Button::BTN1));


	//GPIO_PinState state = HAL_GPIO_ReadPin(BTN0_GPIO_Port, BTN0_Pin);
		  //BSP_VOICE_MAIL_BOX_setLed0((bool)state);
		  //HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, state);


	HAL_Delay(10);
}
