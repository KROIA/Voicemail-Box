#include "i2s.hpp"
#include "main.h"


namespace VoiceMailBox
{
	bool I2S::setup_transmitReceive_DMA(uint16_t* txData, uint16_t* rxData, uint16_t size)
	{
		HAL_StatusTypeDef status = HAL_I2SEx_TransmitReceive_DMA(static_cast<I2S_HandleTypeDef*>(i2s), txData, rxData, size);
		return status == HAL_OK;
	}
}