#ifndef DIGITAL_PIN_HPP
#define DIGITAL_PIN_HPP
/**
 * @brief Digital Pin abstraction class
 * @details This class provides an interface to the GPIO peripheral of the STM32 microcontroller.
 *          It provides methods to set, toggle and get the state of a digital pin.
 * @author Alex Krieg
 */


#include "HAL_abstraction.hpp"


namespace VoiceMailBox
{
	class DigitalPin
	{
	public:
		/**
		 * @brief Constructor
		 * @param gpio HAL handle for the GPIO peripheral
		 * @param pin Pin number
		 */
		DigitalPin(VMB_GPIO* gpio, uint16_t pin);

		/**
		 * @brief Sets the pinstate to high or low.
		 * @param on 
		 */
		void set(bool on);

		/**
		 * @brief Toggles the pinstate.
		 */
		void toggle();

		/**
		 * @brief Gets the pinstate.
		 * @return true if the pin is high, false if it is low.
		 */
		bool get();

		/**
		 * @brief Gets the HAL handle for the GPIO peripheral.
		 * @return handle to the GPIO peripheral.
		 */
		VMB_GPIO * const getGPIO() const { return m_gpio; }

		/**
		 * @brief Gets the pin number.
		 * @return pin number
		 */
		uint16_t getPin() const { return m_pin; }

	private:
		VMB_GPIO * const m_gpio;		// GPIO_TypeDef*
		const uint16_t m_pin;	// Pin number
	};
}
#endif