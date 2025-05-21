#include "peripherals/digitalPin.hpp"

namespace VoiceMailBox
{
	DigitalPin::DigitalPin(VMB_GPIO* gpio, uint16_t pin)
		: m_gpio(gpio)
		, m_pin(pin)
		, m_onFallingEdge(nullptr)
		, m_onRisingEdge(nullptr)
		, m_onDown(nullptr)
		, m_logicLevel(1)
		, m_lastState(0)
	{
		
	}
	DigitalPin::DigitalPin(VMB_GPIO* gpio, uint16_t pin, bool isInverted)
		: m_gpio(gpio)
		, m_pin(pin)
		, m_onFallingEdge(nullptr)
		, m_onRisingEdge(nullptr)
		, m_onDown(nullptr)
		, m_logicLevel(!isInverted)
		, m_lastState(0)
	{

	}
	void DigitalPin::set(bool on)
	{
		VMB_HAL_GPIO_WritePin(m_gpio, m_pin, (VMB_GPIO_PinState)(on == m_logicLevel));
	}
	void DigitalPin::toggle()
	{
		VMB_HAL_GPIO_TogglePin(m_gpio, m_pin);
	}
	bool DigitalPin::get()
	{
		return VMB_HAL_GPIO_ReadPin(m_gpio, m_pin) == m_logicLevel;
	}

	void DigitalPin::update()
	{
		bool currentState = get();
		if (currentState != m_lastState)
		{
			if (currentState == 0)
			{
				if (m_onFallingEdge)
					m_onFallingEdge(*this);
			}
			else
			{
				if (m_onRisingEdge)
					m_onRisingEdge(*this);
			}
			m_lastState = currentState;
		}
		if (currentState == 0)
		{
			if (m_onDown)
				m_onDown(*this);
		}
	}
}
