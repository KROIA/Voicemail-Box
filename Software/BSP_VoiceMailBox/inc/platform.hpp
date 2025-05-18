#ifndef PLATFORM_HPP
#define PLATFORM_HPP
/**
 * @brief Platform abstraction layer
 * @details This file contains the declaration of all low level components
 *          from the ViceMailBox platform.
 * 
 *  @author Alex Krieg
 */

#include "settings.h"

#include "peripherals/DigitalPin.hpp"
#include "peripherals/AnalogPin.hpp"
#include "peripherals/uart.hpp"
#include "peripherals/i2c.hpp"
#include "peripherals/Codec_TLV320AIC3104.hpp"
#include "peripherals/ATCommandClient.hpp"



namespace VoiceMailBox
{
	struct Platform
	{
		/**
		 * @brief Leds available on the Voice Mail Box board.
		 */
		static DigitalPin led[];

		/**
		 * @brief Buttons available on the Voice Mail Box board.
		 */
		static DigitalPin button[];

		/**
		 * @brief Potentiometers available on the Voice Mail Box board.
		 */
		static AnalogPin adcPotis[];

		/**
		 * @brief UART connections available on the Voice Mail Box board.
		 * @details The UART is used for debugging and is connected to the ST-Link.
		 */
		static UART dbgUart;
		
		/**
		 * @brief Audiocodec TLV320AIC3104 available on the Voice Mail Box board.
		 */
		static Codec_TLV320AIC3104 codec;

		/**
		 * @brief Encapsulation of a UART/SPI connection for the ESP32 module.
		 */
		static ATCommandClient pmodESP;

#ifdef VMB_DEVELOPMENT_CONFIGURATION
		/**
		 * @brief Debug pins available on the Voice Mail Box board.
		 * @details These pins are not routed to a connector and therefore must be soldered
		 *          manually on the board.
		 */
		static DigitalPin dbgPins[];
#endif

		/**
		 * @brief Setup the platform.
		 */
		static void setup();

		static void update();
	};
}
#endif /* PLATFORM_HPP */
