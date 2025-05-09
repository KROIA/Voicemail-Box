#ifndef I2S_HPP
#define I2S_HPP

#include <stdint.h>


namespace VoiceMailBox
{
	struct I2S
	{
		void* i2s;	// I2S_HandleTypeDef*

		bool setup_transmitReceive_DMA(uint16_t* txData, uint16_t* rxData, uint16_t size);
	};
}
#endif