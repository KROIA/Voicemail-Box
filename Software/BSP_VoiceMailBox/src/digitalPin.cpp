#include "digitalPin.hpp"
#include "main.h"


namespace VoiceMailBox
{
	void DIGITAL_PIN::set(bool on)
	{
		HAL_GPIO_WritePin(static_cast<GPIO_TypeDef*>(gpio), pin, (GPIO_PinState)on);
	}
	void DIGITAL_PIN::toggle()
	{
		HAL_GPIO_TogglePin(static_cast<GPIO_TypeDef*>(gpio), pin);
	}
	bool DIGITAL_PIN::get()
	{
		return HAL_GPIO_ReadPin(static_cast<GPIO_TypeDef*>(gpio), pin) == GPIO_PIN_SET;
	}
}