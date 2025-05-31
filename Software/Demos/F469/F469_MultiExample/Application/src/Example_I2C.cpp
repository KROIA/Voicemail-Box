#include "Example_I2C.hpp"
#include "BSP_VoiceMailBox.hpp"
#include "main.h"

namespace Example_I2C
{
	VoiceMailBox::I2C i2c(getI2C_Handle());
	void setup()
	{
		VoiceMailBox::setup();
		uint8_t deviceAddress = 0x18;   // Use the address of the Codec
		uint8_t registerAddress = 0x00; // Use the "Page Select" register to write to the first page
		// inside the target.
		uint8_t dataToWrite = 0x01;

		// Writes the value 0x01 to the register 0x00 on the device 0x05.
		i2c.writeRegister(deviceAddress, registerAddress, dataToWrite);

		// Reads the register 0x00 from the device 0x18 and
		// stores the value in the <readData> variable
		uint8_t readData = 0;
		i2c.readRegister(deviceAddress, registerAddress, readData);
		VoiceMailBox::println("Read data: 0x%02X", readData);
	}

	void loop()
	{

	}
} 
