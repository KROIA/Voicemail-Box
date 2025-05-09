#ifndef DIGITAL_PIN_HPP
#define DIGITAL_PIN_HPP

#include <stdint.h>


namespace VoiceMailBox
{
	struct DIGITAL_PIN
	{
		void* gpio;		// GPIO_TypeDef*
		uint16_t pin;	// Pin number

		void set(bool on);
		void toggle();
		bool get();
	};
}
#endif