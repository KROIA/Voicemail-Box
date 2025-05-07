#include "platform.hpp"
#include "main.h"

namespace VoiceMailBox
{

	/*
		Fill in the GPIO_TypeDef* and pin values, generated from the CUBEMX for the LEDs
	*/
	GPIO Components::led[] = {
				{ LED0_GPIO_Port, LED0_Pin },
				{ LED1_GPIO_Port, LED1_Pin }
	};

	/*
		Fill in the GPIO_TypeDef* and pin values, generated from the CUBEMX for the buttons
	*/
	GPIO Components::button[] = {
				{ BTN0_GPIO_Port, BTN0_Pin },
				{ BTN1_GPIO_Port, BTN1_Pin },
				{ BTN2_GPIO_Port, BTN2_Pin },
				{ BTN3_GPIO_Port, BTN3_Pin }
	};



	void GPIO::set(bool on)
	{
		HAL_GPIO_WritePin(static_cast<GPIO_TypeDef*>(gpio), pin, (GPIO_PinState)on);
	}
	void GPIO::toggle()
	{
		HAL_GPIO_TogglePin(static_cast<GPIO_TypeDef*>(gpio), pin);
	}
	bool GPIO::get()
	{
		return HAL_GPIO_ReadPin(static_cast<GPIO_TypeDef*>(gpio), pin) == GPIO_PIN_SET;
	}

}