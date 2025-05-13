#include "peripherals/digitalPin.hpp"

namespace VoiceMailBox
{
	DigitalPin::DigitalPin(VMB_GPIO* gpio, uint16_t pin)
		: m_gpio(gpio)
		, m_pin(pin)
	{
		//VMB_HAL_GPIO_Init(gpio, pin);
	}
	void DigitalPin::set(bool on)
	{
		VMB_HAL_GPIO_WritePin(m_gpio, m_pin, (VMB_GPIO_PinState)on);
	}
	void DigitalPin::toggle()
	{
		VMB_HAL_GPIO_TogglePin(m_gpio, m_pin);
	}
	bool DigitalPin::get()
	{
		return VMB_HAL_GPIO_ReadPin(m_gpio, m_pin) == GPIO_PIN_SET;
	}
}
