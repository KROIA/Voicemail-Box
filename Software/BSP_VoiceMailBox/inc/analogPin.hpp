#ifndef ANALOG_PIN_HPP
#define ANALOG_PIN_HPP

#include <stdint.h>


namespace VoiceMailBox
{
	struct ANALOG_PIN
	{
		void* adc;		// ADC_TypeDef*

		uint32_t getValue();
	};
}
#endif