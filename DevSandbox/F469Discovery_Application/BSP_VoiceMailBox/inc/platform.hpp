/*
 * platform.h
 *
 *  Created on: May 7, 2025
 *      Author: Alex
 */

#ifndef INC_PLATFORM_HPP_
#define INC_PLATFORM_HPP_

#include <stdint.h>


namespace VoiceMailBox
{
	struct GPIO
	{
		void* gpio;		// GPIO_TypeDef* pointer
		uint16_t pin;	// Pin number

		void set(bool on);
		void toggle();
		bool get();
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
	};
}


#endif /* INC_PLATFORM_HPP_ */
