#include "analogPin.hpp"
#include "main.h"


namespace VoiceMailBox
{
	uint32_t ANALOG_PIN::getValue()
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
}
