#ifndef I2C_HPP
#define I2C_HPP

#include <stdint.h>


namespace VoiceMailBox
{
	struct I2C
	{
		// 1 : 1 Mapping from the HAL_StatusTypeDef
		enum class Status
		{
			OK = 0x00U,
			ERROR = 0x01U,
			BUSY = 0x02U,
			TIMEOUT = 0x03U
		};

		void* i2c;	// I2C_HandleTypeDef*

		I2C(void* i2cHandle);

		/**
		 * @brief  Write data to a register of a device on the I2C bus.
		 * @param  deviceAddress: Address of the device on the I2C bus.
		 *						  No need for shifting the addres by 1 bit.
		 * @param  registerAddress: Address of the register to write to.
		 * @param  data: Data to write to the register. (1 byte)
		 * @retval Status: Status of the operation.
		 */
		Status writeRegister(uint8_t deviceAddress, uint8_t registerAddress, uint8_t data);

		/**
		 * @brief  Read data from a register of a device on the I2C bus.
		 * @param  deviceAddress: Address of the device on the I2C bus.
		 *						  No need for shifting the addres by 1 bit.
		 * @param  registerAddress: Address of the register to read from.
		 * @param  data: Ref to the data to read from the register. (1 byte)
		 * @retval Status: Status of the operation.
		 */
		Status readRegister(uint8_t deviceAddress, uint8_t registerAddress, uint8_t& data);



	};
}
#endif