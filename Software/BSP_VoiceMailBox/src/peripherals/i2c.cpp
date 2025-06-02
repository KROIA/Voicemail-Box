#include "peripherals/i2c.hpp"
#include "utilities/Logger.hpp"

namespace VoiceMailBox
{
	I2C::I2C(VMB_I2C_Handle* i2cHandle)
		: m_i2c(i2cHandle)
	{

	}


	VMB_HAL_Status I2C::writeRegister(uint8_t deviceAddress, uint8_t registerAddress, uint8_t data)
	{
		VMB_HAL_Status status = VMB_HAL_I2C_Mem_Write(m_i2c,
			deviceAddress << 1,
			registerAddress,
			I2C_MEMADD_SIZE_8BIT,
			&data,
			1,
			HAL_MAX_DELAY);
		VMB_LOGGER_PRINT_STATUS(status, "I2C::writeRegister()");
		return status; 
	}

	VMB_HAL_Status I2C::readRegister(uint8_t deviceAddress, uint8_t registerAddress, uint8_t& data)
	{
		VMB_HAL_Status status = VMB_HAL_I2C_Mem_Read(m_i2c,
			deviceAddress << 1,
			registerAddress,
			I2C_MEMADD_SIZE_8BIT,
			&data,
			1,
			HAL_MAX_DELAY);
		VMB_LOGGER_PRINT_STATUS(status, "I2C::readRegister()");
		return status; 
	}
}
