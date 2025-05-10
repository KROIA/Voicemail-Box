#include "i2c.hpp"
#include "HAL_abstraction.hpp"


namespace VoiceMailBox
{
	I2C::I2C(void* i2cHandle)
		: i2c(i2cHandle)
	{

	}


	I2C::Status I2C::writeRegister(uint8_t deviceAddress, uint8_t registerAddress, uint8_t data)
	{
		VMB_HAL_Status status = VMB_HAL_I2C_Mem_Write(static_cast<VMB_I2C_Handle*>(i2c),
			deviceAddress << 1,
			registerAddress,
			I2C_MEMADD_SIZE_8BIT,
			&data,
			1,
			HAL_MAX_DELAY);

		return (Status)status; // 1 : 1 mapping
	}

	I2C::Status I2C::readRegister(uint8_t deviceAddress, uint8_t registerAddress, uint8_t& data)
	{
		VMB_HAL_Status status = VMB_HAL_I2C_Mem_Read(static_cast<VMB_I2C_Handle*>(i2c),
			deviceAddress << 1,
			registerAddress,
			I2C_MEMADD_SIZE_8BIT,
			&data,
			1,
			HAL_MAX_DELAY);

		return (Status)status; // 1 : 1 mapping
	}
}
