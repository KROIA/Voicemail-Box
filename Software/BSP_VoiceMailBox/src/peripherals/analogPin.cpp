#include "peripherals/AnalogPin.hpp"

namespace VoiceMailBox
{
	AnalogPin::AnalogPin(VMB_ADC_Handle* adcHandle)
		: m_adc(adcHandle) // Initialize the ADC handle
	{

	}

	uint32_t AnalogPin::getValue() const
	{
		uint32_t value = 0;
		VMB_HAL_ADC_Start(m_adc);
		if (VMB_HAL_ADC_PollForConversion(m_adc, 10) == VMB_HAL_Status::OK)
		{
			value = VMB_HAL_ADC_GetValue(m_adc);
		}
		VMB_HAL_ADC_Stop(m_adc);
		return value;
	}
	uint32_t AnalogPin::getMaxValue() const
	{
		return VMB_HAL_ADC_GetMaxValue(m_adc);
	}
}
