/*
 * platform.h
 *
 *  Created on: May 7, 2025
 *      Author: Alex
 * 
 * This file contains the declaration of all low level components from the ViceMailBox research Platform.
 */

#ifndef INC_PLATFORM_HPP_
#define INC_PLATFORM_HPP_

#include <stdint.h>
#include <cstdarg>

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

	struct ANALOG_PIN
	{
		void* adc;		// ADC_TypeDef*

		uint32_t getValue();
	};

	struct UART
	{
		void* uart;		// UART_HandleTypeDef*

		void send(const char* str);
		void send(uint8_t* data, uint16_t size);
	};

/*
-------------------------------------------------------------------------
	C O M P O N E N T S
-------------------------------------------------------------------------
*/
	struct Platform
	{

		// LEDs
		static DIGITAL_PIN led[];

		// Buttons
		static DIGITAL_PIN button[];

		// ADC Potis
		static ANALOG_PIN adcPotis[];

		// UART
		static UART dbgUart;
	};


/*
-------------------------------------------------------------------------
	U T I L I T Y
-------------------------------------------------------------------------
*/
	namespace Utility
	{
		static constexpr size_t print_buffer_size;

		void delay(uint32_t ms);
		void print(const char* str, va_list args);

	}

}


#endif /* INC_PLATFORM_HPP_ */
