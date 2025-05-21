#ifndef DIGITAL_PIN_HPP
#define DIGITAL_PIN_HPP
/**
 * @brief Digital Pin abstraction class
 * @details This class provides an interface to the GPIO peripheral of the STM32 microcontroller.
 *          It provides methods to set, toggle and get the state of a digital pin.
 * @author Alex Krieg
 */


#include "HAL_abstraction.hpp"
#include <functional>


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
		 * @brief Constructor
		 * @param gpio HAL handle for the GPIO peripheral
		 * @param pin Pin number
		 * @param isInverted If true, the pin state is inverted. (active low)
		 */
		DigitalPin(VMB_GPIO* gpio, uint16_t pin, bool isInverted);

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


		void setOnFallingEdgeCallback(const std::function<void(DigitalPin&)>& callback)
		{
			m_onFallingEdge = callback;
		}
		void setOnRisingEdgeCallback(const std::function<void(DigitalPin&)>& callback)
		{
			m_onRisingEdge = callback;
		}
		void setOnDownCallback(const std::function<void(DigitalPin&)>& callback)
		{
			m_onDown = callback;
		}
		void update();

	private:
		VMB_GPIO * const m_gpio;		// GPIO_TypeDef*
		const uint16_t m_pin;	// Pin number
		bool m_logicLevel; // when set to false, the pin state gets inverted
		bool m_lastState;
		

		std::function<void(DigitalPin&)> m_onFallingEdge;	// Callback function to be called when the pin state changes to high
		std::function<void(DigitalPin&)> m_onRisingEdge;	// Callback function to be called when the pin state changes to low
		std::function<void(DigitalPin&)> m_onDown;	// Callback function to be called when the pin state is high
	};
}
#endif