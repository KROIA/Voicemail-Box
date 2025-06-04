#ifndef ANALOG_PIN_HPP
#define ANALOG_PIN_HPP
/**
 * @author Alex Krieg
 */


#include "HAL_abstraction.hpp"

namespace VoiceMailBox
{
	/**
	 * @brief ADC abstraction class
	 * @details This class provides an interface to the ADC peripheral of the STM32 microcontroller.
	 *          It handles the ADC conversion and provides a method to get the converted value.
	 */
	class AnalogPin
	{
	public:
		/**
		 * @brief Constructor
		 * @param adcHandle HAL handle for the ADC peripheral
		 */
		AnalogPin(VMB_ADC_Handle* adcHandle);

		/**
		 * @brief Gets the current value of the ADC.
		 * @return converted value of the ADC
		 */
		uint32_t getValue() const;

		/**
		 * @brief Gets the maximum possible ADC value
		 * @return maximum possible ADC value
		 */
		uint32_t getMaxValue() const;

		/**
		 * @brief Gets the HAL handle for the ADC peripheral.
		 * @return handle to the ADC peripheral.
		 */
		VMB_ADC_Handle* const getHandle() const
		{
			return m_adc;
		}
	private:
		VMB_ADC_Handle * const m_adc;		// ADC_TypeDef*
	};
}
#endif