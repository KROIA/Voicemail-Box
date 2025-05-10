#include "analogPin.hpp"
#include "main.h"


namespace VoiceMailBox
{
	uint32_t ANALOG_PIN::getValue() const
	{
		uint32_t value = 0;
		ADC_HandleTypeDef* _adc = static_cast<ADC_HandleTypeDef*>(adc);
		HAL_ADC_Start(_adc);
		if (HAL_ADC_PollForConversion(_adc, 10) == HAL_OK)
		{
			value = HAL_ADC_GetValue(_adc);
		}
		HAL_ADC_Stop(_adc);
		return value;
	}
	uint32_t ANALOG_PIN::getMaxValue() const
	{
		switch (static_cast<ADC_HandleTypeDef*>(adc)->Init.Resolution) {
		case ADC_RESOLUTION_12B:
			return 4095;
		case ADC_RESOLUTION_10B:
			return 1023;
		case ADC_RESOLUTION_8B:
			return 255;
		case ADC_RESOLUTION_6B:
			return 63;
		}
		return 0;
	}
}
