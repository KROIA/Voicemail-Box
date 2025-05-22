#ifndef DIGITAL_PIN_HPP
#define DIGITAL_PIN_HPP
/**
 * @brief Digital Pin abstraction class
 * @details This class provides an interface to the GPIO peripheral of the STM32 microcontroller.
 *          It provides methods to set, toggle and get the state of a digital pin.
 * @author Alex Krieg
 */


#include "HAL_abstraction.hpp"
#include "utilities/Updatable.hpp"
#include <functional>


namespace VoiceMailBox
{
	class DigitalPin : public Updatable
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

		/**
		 * @brief The given callback function gets called when the pin state changes to low.
		 * @param callback function that takes a reference to the DigitalPin object that has called the callback
		 */
		void setOnFallingEdgeCallback(const std::function<void(DigitalPin&)>& callback)
		{
			m_onFallingEdge = callback;
		}

		/**
		 * @brief The given callback function gets called when the pin state changes to high.
		 * @param callback function that takes a reference to the DigitalPin object that has called the callback
		 */
		void setOnRisingEdgeCallback(const std::function<void(DigitalPin&)>& callback)
		{
			m_onRisingEdge = callback;
		}

		/**
		 * @brief The given callback function gets called when the pin state is high.
		 * @param callback function that takes a reference to the DigitalPin object that has called the callback
		 */
		void setOnDownCallback(const std::function<void(DigitalPin&)>& callback)
		{
			m_onDown = callback;
		}

		/**
		 * @brief Checks the pin state and calls the callback functions if the pin state has changed.
		 */
		void update() override;

	private:
		VMB_GPIO * const m_gpio;	// GPIO_TypeDef*
		const uint16_t m_pin;		// Pin number
		bool m_logicLevel;			// when set to false, the pin state gets inverted
		bool m_lastState;			// Last state of the pin used to detect rising and falling edges
		

		std::function<void(DigitalPin&)> m_onFallingEdge;	// Callback function to be called when the pin state changes to high
		std::function<void(DigitalPin&)> m_onRisingEdge;	// Callback function to be called when the pin state changes to low
		std::function<void(DigitalPin&)> m_onDown;			// Callback function to be called when the pin state is high
	};
}
#endif
