#ifndef BSP_VOICE_MAIL_BOX
#define BSP_VOICE_MAIL_BOX
/**
 * @brief This file provides an high level interface to the hardware components of the VoiceMailBox platform.
 */


#include "platform.hpp"

#include "utilities/File.hpp"
#include "utilities/AudioRecorder.hpp"
#include "utilities/AudioPlayer.hpp"

#include <cstdarg>   // <-- required for va_list and related macros
#include <cstdio>    // <-- required for vsnprintf

namespace VoiceMailBox
{

    
	/**
	 *	@brief Setup the platform. 
	 *	Call this function once at startup after the HAL has initialized the peripherals.
	 */
	inline void setup() { Platform::setup(); }

	/**
	 * @brief Updates the updatable objects of the platform.
	 */
	inline void update() { Platform::update(); }

	/**
	 *	@brief Gets the led object for the given LED.
	 *  @param led The LED to get.
	 *	@return The led object.
	 */
	inline DigitalPin& getLed(LED led) { return Platform::getLed(led); }

	/**
	 * @brief Sets the state of the given LED.
	 * @param led 
	 * @param on 
	 */
	inline void setLed(LED led, bool on) { Platform::getLed(led).set(on); }

	/**
	 * @brief Toggles the state of the given LED.
	 * @param led 
	 */
	inline void toggleLed(LED led) { Platform::getLed(led).toggle(); }

	/**
	 * @brief Gets the button object for the given button.
	 * @param button The button to get. 
	 * @return Digital pin instance for the button.
	 */
	inline DigitalPin& getButton(Button button) { return Platform::getButton(button); }

	/**
	 * @brief Reads the pin on which the given button is connected.
	 * @param button to read the pin from
	 * @return true if the button is pressed, false otherwise.
	 */
	inline bool getButtonState(Button button) { return Platform::getButton(button).get(); }

	/**
	 * @brief Gets the ADC object for the given Poti.
	 * @param poti index
	 * @return ADC object for the given Poti.
	 */
	inline AnalogPin& getPotentiometer(Potentiometer poti) { return Platform::getPotentiometer(poti); }

	/**
	 * @brief Gets the current value of the given Poti.
	 * @param poti to read the ADC value from
	 * @return ADC value of the given Poti.
	 */
	inline uint32_t getPotiValue(Potentiometer poti) { return Platform::getPotentiometer(poti).getValue(); }

	/**
	 * @brief Gets the maximum possible value of the given Poti.
	 * @param poti 
	 * @return the maximum ADC value possible of the given Poti.
	 */
	inline uint32_t getPotiMaxValue(Potentiometer poti) { return Platform::getPotentiometer(poti).getMaxValue(); }

	/**
	 * @brief Gets the ATCommandClient instance that represents the Pmod ESP Wifi/Bluetooth module.
	 * @return Pmod ESP ATCommandClient instance.
	 */
	inline ATCommandClient& getPmodESP() { return Platform::getPmodESP(); }

	/**
	 * @brief Gets the Codec_TLV320AIC3104 instance that represents the audio codec.
	 * @return Codec instance.
	 */
	inline Codec_TLV320AIC3104& getCodec() { return Platform::getCodec(); }


#ifdef VMB_DEVELOPMENT_CONFIGURATION
	/**
	 * @brief Gets the digital pin instance for the given debug pin.
	 * @param pin The debug pin to get.
	 * @return The digital pin instance for the given debug pin.
	 */
	inline DigitalPin& getDbgPin(DBG_PIN pin) { return Platform::getDebugPin(pin); }

	/**
	 * @brief Sets the state of the given debug pin.
	 * @param pin The debug pin to set.
	 * @param on The state to set the debug pin to.
	 */
	inline void setDbgPin(DBG_PIN pin, bool on) { Platform::getDebugPin(pin).set(on); }

	/**
	 * @brief Toggles the state of the given debug pin.
	 * @param pin The debug pin to toggle.
	 */
	inline void toggleDbgPin(DBG_PIN pin) { Platform::getDebugPin(pin).toggle(); }
#endif

	/**
	 * @brief Print a string to the debug UART, which is connected to the ST-Link.
	 * @param str pointer to the string to print.
	 * @param [in] ... args
	 *
	 * @note This function is variadic and uses the same format as printf.
	 */
	static void print(const char* str, ...)
	{
		va_list args;
		va_start(args, str);
		std::string buffer;
		buffer.resize(Platform::getDebugUART().getBufferSize()); // Allocate a buffer of 256 bytes
		int len = vsnprintf(&buffer[0], buffer.size(), str, args);
		if (len < 0)
		{
			// Handle error
			return;
		}
		if ((long)len >= (long)buffer.size())
		{
			// Handle buffer overflow
			return;
		}
		Platform::getDebugUART().send((uint8_t*)buffer.data(), len); // Send the formatted string
		va_end(args);
	}

	/**
	 * @brief Print a string to the debug UART, which is connected to the ST-Link.
	 * @param str string object to print.
	 * @param [in] ... args
	 *
	 * @note This function is variadic and uses the same format as printf.
	 */
	static void print(const std::string& str, ...)
	{
		va_list args;
		va_start(args, str);
		std::string buffer;
		buffer.resize(Platform::getDebugUART().getBufferSize()); // Allocate a buffer of 256 bytes
		int len = vsnprintf(&buffer[0], buffer.size(), str.c_str(), args);
		if (len < 0)
		{
			// Handle error
			return;
		}
		if ((long)len >= (long)buffer.size())
		{
			// Handle buffer overflow
			return;
		}
		Platform::getDebugUART().send((uint8_t*)buffer.data(), len); // Send the formatted string
		va_end(args);
	}

	/**
	 * @brief Print a string, with a newline at the end, to the debug UART,
	 *		  which is connected to the ST-Link.
	 * @param str pointer to the string to print.
	 * @param [in] ... args
	 *
	 * @note This function is variadic and uses the same format as printf.
	 */
	static void println(const char* str, ...)
	{
		va_list args;
		va_start(args, str);
		std::string buffer;
		buffer.resize(Platform::getDebugUART().getBufferSize()); // Allocate a buffer of 256 bytes
		int len = vsnprintf(&buffer[0], buffer.size(), str, args);
		if (len < 0)
		{
			// Handle error
			return;
		}
		if ((long)len >= (long)buffer.size() - 2)
		{
			// Handle buffer overflow
			return;
		}
		buffer[len++] = '\r'; // Add a newline character
		buffer[len++] = '\n'; // Add a newline character
		Platform::getDebugUART().send((uint8_t*)buffer.data(), len); // Send the formatted string
		va_end(args);
	}

	/**
	 * @brief Print a string, with a newline at the end, to the debug UART,
	 *		  which is connected to the ST-Link.
	 * @param str string object to print.
	 * @param [in] ... args
	 *
	 * @note This function is variadic and uses the same format as printf.
	 */
	static void println(const std::string& str, ...)
	{
		va_list args;
		va_start(args, str);
		std::string buffer;
		buffer.resize(Platform::getDebugUART().getBufferSize()); // Allocate a buffer of 256 bytes
		int len = vsnprintf(&buffer[0], buffer.size(), str.c_str(), args);
		if (len < 0)
		{
			// Handle error
			return;
		}
		if ((long)len >= (long)buffer.size() - 2)
		{
			// Handle buffer overflow
			return;
		}
		buffer[len++] = '\r'; // Add a newline character
		buffer[len++] = '\n'; // Add a newline character
		Platform::getDebugUART().send((uint8_t*)buffer.data(), len); // Send the formatted string
		va_end(args);
	}

	/**
	 * @brief waits until the given milli seconds have passed.
	 * @param ms time to wait in milli seconds
	 */
	inline void delay(uint32_t ms)
	{
		VMB_HAL_Delay(ms);
	}

	/**
	 * @brief Gets the current cpu tick count.
	 * @return current tick count.
	 */
	inline uint32_t getTickCount()
	{
		return VMB_HAL_GetTickCount();
	}


	inline uint64_t getTickCountInUs()
	{
		return VMB_HAL_GetTickCountInUs();
	}

	/**
	 * @brief Gets the current milli seconds since the tick counter was reset
	 * @return current milliseconds since the tick counter was reset.
	 */
	inline uint64_t getTickCountInMs()
	{
		return VMB_HAL_GetTickCountInMs();
	}

	/**
	 * @brief Resets the tick count to 0.
	 */
	inline void resetTickCount()
	{
		VMB_HAL_ResetTickCounter();
	}
}

#endif
