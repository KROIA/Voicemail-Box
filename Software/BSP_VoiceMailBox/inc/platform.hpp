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
		static constexpr std::size_t buffer_size = 256;

		void* uart;		// UART_HandleTypeDef*
		
		UART(void* uartHandle);
		void startRX_DMA();

		void send(const char* str);
		void send(uint8_t* data, uint16_t size);

		uint16_t hasBytesReceived();
		bool receive(uint8_t* data, uint16_t size);
		//void receive(uint8_t* data, uint16_t size, uint32_t timeout);



		void onDMAReceivedData(uint16_t size);
		private:

		
		uint8_t rx_buffer[2][buffer_size];
		uint8_t tx_buffer[buffer_size];
		//bool dataReceived = false;
		uint16_t dataSize = 0;
		uint8_t* current_RX_Buffer = nullptr;
		bool bufferSwitcher;
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
		static UART wifiUart;


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

	}

}


#endif /* INC_PLATFORM_HPP_ */
