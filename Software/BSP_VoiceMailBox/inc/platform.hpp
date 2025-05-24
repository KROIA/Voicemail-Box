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
	/**
	 * @brief List of all LEDs available on the Voice Mail Box board.
	 */
	enum LED
	{
		LED0,
		LED1
	};

	/**
	 * @brief List of all buttons available on the Voice Mail Box board.
	 */
	enum Button
	{
		BTN0,
		BTN1,
		BTN2,
		BTN3
	};

	/**
	 * @brief List of all potentiometers available on the Voice Mail Box board.
	 */
	enum Potentiometer
	{
		POT0,
		POT1
	};

#ifdef VMB_DEVELOPMENT_CONFIGURATION
	/**
	 * @brief List of all debug pins available on the Voice Mail Box board.
	 * @details These pins are not routed to a connector and therefore must be soldered
	 */
	enum DBG_PIN
	{
		DBG0,
		DBG1,
		DBG2,
	};
#endif

	struct Platform
	{


		/**
		 * @brief Leds available on the Voice Mail Box board.
		 */
		static DigitalPin& getLed(LED index);

		/**
		 * @brief Buttons available on the Voice Mail Box board.
		 */
		static DigitalPin& getButton(Button index);

		/**
		 * @brief Potentiometers available on the Voice Mail Box board.
		 */
		static AnalogPin& getPotentiometer(Potentiometer index);

		/**
		 * @brief UART connections available on the Voice Mail Box board.
		 * @details The UART is used for debugging and is connected to the ST-Link.
		 */
		static UART& getDebugUART();
		
		/**
		 * @brief Audiocodec TLV320AIC3104 available on the Voice Mail Box board.
		 */
		static Codec_TLV320AIC3104& getCodec();

		/**
		 * @brief Encapsulation of a UART/SPI connection for the ESP32 module.
		 */
		static ATCommandClient& getPmodESP();

		/**
		 * @brief Gets the I2C bus instance used for communication with the codec and other I2C devices.
		 * @return I2C instance reference
		 */
		static I2C& getI2C();

#ifdef VMB_DEVELOPMENT_CONFIGURATION
		/**
		 * @brief Debug pins available on the Voice Mail Box board.
		 * @details These pins are not routed to a connector and therefore must be soldered
		 *          manually on the board.
		 */
		static DigitalPin& getDebugPin(DBG_PIN index);
#endif

		/**
		 * @brief Setup the platform.
		 */
		static void setup();

		/**
		 * @brief Updates objects that need to be updated in the main loop.
		 */
		static void update();

	private:
		
	};
}
#endif /* PLATFORM_HPP */
