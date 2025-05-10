#include "analogPin.hpp"
#include "HAL_abstraction.hpp"


namespace VoiceMailBox
{
	uint32_t ANALOG_PIN::getValue() const
	{
		uint32_t value = 0;
		VMB_ADC_Handle* _adc = static_cast<VMB_ADC_Handle*>(adc);
		VMB_HAL_ADC_Start(_adc);
		if (VMB_HAL_ADC_PollForConversion(_adc, 10) == VMB_HAL_Status::OK)
		{
			value = VMB_HAL_ADC_GetValue(_adc);
		}
		VMB_HAL_ADC_Stop(_adc);
		return value;
	}
	uint32_t ANALOG_PIN::getMaxValue() const
	{
		switch (static_cast<VMB_ADC_Handle*>(adc)->Init.Resolution) {
		case VMB_ADC_RESOLUTION_12B:
			return 4095;
		case VMB_ADC_RESOLUTION_10B:
			return 1023;
		case VMB_ADC_RESOLUTION_8B:
			return 255;
		case VMB_ADC_RESOLUTION_6B:
			return 63;
		}
		return 0;
	}
}
