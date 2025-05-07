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


namespace VoiceMailBox
{
	struct GPIO
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
		void send(uint32_t value);
		void send(int32_t value);
		//void send(float value);
	};

/*
-------------------------------------------------------------------------
	C O M P O N E N T S
-------------------------------------------------------------------------
*/
	struct Components
	{

		// LEDs
		static GPIO led[];

		// Buttons
		static GPIO button[];

		// ADC Potis
		static ANALOG_PIN adcPotis[];

		// UART
		static UART dbgUart;
	};
}


#endif /* INC_PLATFORM_HPP_ */
