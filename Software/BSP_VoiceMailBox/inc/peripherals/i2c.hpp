#ifndef I2C_HPP
#define I2C_HPP
/**
 * @brief I2S abstraction class
 * @details This class provides an interface to the I2S peripheral of the STM32 microcontroller.
 * @author Alex Krieg
 */


#include "HAL_abstraction.hpp"


namespace VoiceMailBox
{
	class I2C
	{
	public:
		/**
		 * @brief Constructor
		 * @param i2cHandle HAL handle for the I2C peripheral
		 */
		I2C(VMB_I2C_Handle* i2cHandle);

		/**
		 * @brief  Write data to a register of a device on the I2C bus.
		 * @param  deviceAddress: Address of the device on the I2C bus.
		 *						  No need for shifting the address by 1 bit.
		 * @param  registerAddress: Address of the register to write to.
		 * @param  data: Data to write to the register. (1 byte)
		 * @retval Status: Status of the operation.
		 */
		VMB_HAL_Status writeRegister(uint8_t deviceAddress, uint8_t registerAddress, uint8_t data);

		/**
		 * @brief  Read data from a register of a device on the I2C bus.
		 * @param  deviceAddress: Address of the device on the I2C bus.
		 *						  No need for shifting the address by 1 bit.
		 * @param  registerAddress: Address of the register to read from.
		 * @param  data: Ref to the data to read from the register. (1 byte)
		 * @retval Status: Status of the operation.
		 */
		VMB_HAL_Status readRegister(uint8_t deviceAddress, uint8_t registerAddress, uint8_t& data);


		/**
		 * @brief Gets the HAL handle for the I2C peripheral.
		 * @return handle to the I2C peripheral.
		 */
		VMB_I2C_Handle * const getHandle() const
		{
			return m_i2c;
		}

		
	private:
		VMB_I2C_Handle * const m_i2c;	// I2C_HandleTypeDef*
	};
}
#endif