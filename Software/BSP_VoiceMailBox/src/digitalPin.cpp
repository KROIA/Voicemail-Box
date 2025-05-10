#include "digitalPin.hpp"
#include "HAL_abstraction.hpp"


namespace VoiceMailBox
{
	void DIGITAL_PIN::set(bool on)
	{
		VMB_HAL_GPIO_WritePin(static_cast<VMB_GPIO*>(gpio), pin, (VMB_GPIO_PinState)on);
	}
	void DIGITAL_PIN::toggle()
	{
		VMB_HAL_GPIO_TogglePin(static_cast<VMB_GPIO*>(gpio), pin);
	}
	bool DIGITAL_PIN::get()
	{
		return VMB_HAL_GPIO_ReadPin(static_cast<VMB_GPIO*>(gpio), pin) == GPIO_PIN_SET;
	}
}