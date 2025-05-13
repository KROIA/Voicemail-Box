#ifndef BSP_VOICE_MAIL_BOX
#define BSP_VOICE_MAIL_BOX
/**
 * @brief This file provides an high level interface to the hardware components of the VoiceMailBox platform.
 */

#include "settings.h"

#include "peripherals/digitalPin.hpp"
#include "peripherals/analogPin.hpp"
#include "peripherals/uart.hpp"
#include "peripherals/i2c.hpp"
#include "peripherals/Codec_TLV320AIC3104.hpp"
#include "peripherals/ATCommandClient.hpp"
#include "peripherals/File.hpp"

namespace VoiceMailBox
{
	enum class LED
	{
		LED0,
		LED1
	};

	enum class Button
	{
		BTN0,
		BTN1,
		BTN2,
		BTN3
	};

	enum class Poti
	{
		POT0,
		POT1
	};

#ifdef VMB_DEVELOPMENT_CONFIGURATION
	enum class DBG_PIN
	{
		DBG0,
		DBG1,
		DBG2,
	};
#endif
    
	/**
	 *	@brief Setup the platform. 
	 *	Call this function once at startup after the HAL has initialized the peripherals.
	 */
	void setup();

	/**
	 *	@brief Gets the led object for the given LED.
	 *  @param led The LED to get.
	 *	@return The led object.
	 */
	DigitalPin& getLed(LED led);

	/**
	 * @brief Sets the state of the given LED.
	 * @param led 
	 * @param on 
	 */
	void setLed(LED led, bool on);

	/**
	 * @brief Toggles the state of the given LED.
	 * @param led 
	 */
	void toggleLed(LED led);

	/**
	 * @brief Gets the button object for the given button.
	 * @param button The button to get. 
	 * @return Digital pin instance for the button.
	 */
	DigitalPin& getButton(Button button);

	/**
	 * @brief Reads the pin on which the given button is connected.
	 * @param button to read the pin from
	 * @return true if the button is pressed, false otherwise.
	 */
	bool getButtonState(Button button);

	/**
	 * @brief Gets the ADC object for the given Poti.
	 * @param poti 
	 * @return ADC object for the given Poti.
	 */
	AnalogPin& getPoti(Poti poti);

	/**
	 * @brief Gets the current value of the given Poti.
	 * @param poti to read the ADC value from
	 * @return ADC value of the given Poti.
	 */
	uint32_t getPotiValue(Poti poti);

	/**
	 * @brief Gets the maximum possible value of the given Poti.
	 * @param poti 
	 * @return the maximum ADC value possible of the given Poti.
	 */
	uint32_t getPotiMaxValue(Poti poti);

	/**
	 * @brief Gets the ATCommandClient instance that represents the Pmod ESP Wifi/Bluetooth module.
	 * @return Pmod ESP ATCommandClient instance.
	 */
	ATCommandClient& getPmodESP();

	/**
	 * @brief Gets the Codec_TLV320AIC3104 instance that represents the audio codec.
	 * @return Codec instance.
	 */
	Codec_TLV320AIC3104& getCodec();


#ifdef VMB_DEVELOPMENT_CONFIGURATION
	/**
	 * @brief Gets the digital pin instance for the given debug pin.
	 * @param pin The debug pin to get.
	 * @return The digital pin instance for the given debug pin.
	 */
	DigitalPin& getDbgPin(DBG_PIN pin);

	/**
	 * @brief Sets the state of the given debug pin.
	 * @param pin The debug pin to set.
	 * @param on The state to set the debug pin to.
	 */
	void setDbgPin(DBG_PIN pin, bool on);

	/**
	 * @brief Toggles the state of the given debug pin.
	 * @param pin The debug pin to toggle.
	 */
	void toggleDbgPin(DBG_PIN pin);
#endif

	/**
	 * @brief Print a string to the debug UART, which is connected to the ST-Link.
	 * @param str
	 * @param [in] ... args
	 *
	 * @note This function is variadic and uses the same format as printf.
	 */
	void print(const char* str, ...);

	/**
	 * @brief Print a string, with a newline at the end, to the debug UART,
	 *		  which is connected to the ST-Link.
	 * @param str
	 * @param [in] ... args
	 *
	 * @note This function is variadic and uses the same format as printf.
	 */
	void println(const char* str, ...);

	/**
	 * @brief waits until the given milli seconds have passed.
	 * @param ms time to wait in milli seconds
	 */
	void delay(uint32_t ms);

	/**
	 * @brief Gets the current cpu tick count.
	 * @return current tick count.
	 */
	uint32_t getTickCount();

	/**
	 * @brief Gets the current milli seconds since the tick counter was reset
	 * @return current milliseconds since the tick counter was reset.
	 */
	uint32_t getTickCountInMs();

	/**
	 * @brief Resets the tick count to 0.
	 */
	void resetTickCount();
}

#endif
