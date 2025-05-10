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

#include "digitalPin.hpp"
#include "analogPin.hpp"
#include "uart.hpp"
#include "i2c.hpp"
#include "Codec_TLV320AIC3104.hpp"
#include "ATCommandClient.hpp"


namespace VoiceMailBox
{
	


	

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
		//static UART wifiUart;
		

		// Audio Codec
		static Codec_TLV320AIC3104 codec;

		static ATCommandClient pmodESP;

		static void setup();
	};


/*
-------------------------------------------------------------------------
	U T I L I T Y
-------------------------------------------------------------------------
*/
	namespace Utility
	{
		

		void delay(uint32_t ms);
		void print(const char* str, va_list args);
		void println(const char* str, va_list args);

		uint32_t getTickCount();
		void resetTickCount();

	}

}


#endif /* INC_PLATFORM_HPP_ */
