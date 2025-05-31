#include "Example_I2S.hpp"
#include "BSP_VoiceMailBox.hpp"
#include "main.h"
#include <memory>

namespace Example_I2S
{
	// Create a I2S object and providing the handle from the main.c. Using the same I2S handle as the codec uses.
    // Use a int16_t[1024] array for data in and out. (only used if the macro VMB_I2S_USE_STATIC_BUFFER_SIZE is not defined)
    VoiceMailBox::I2S i2s(getI2S_CODEC(), 1024);

    void setup()
    {
		// Because we use the same I2S, we do the setup of the platform so that the codec is initialized correctly.
        VoiceMailBox::setup();
		// Since we use the same I2S handle and the DMA was already started in the BSP_VoiceMailBox::setup(), we stop the dma from the platforms codec 
        // so that we can use our own I2S instance
        i2s.stopDMA();

        // If you instantiate a I2S independently from the platforms own I2S, connected to the codec, you don't need the two function calls above.



        // Start the DMA for RX and TX data transfers
        if(!i2s.startDMA())
		{
			VoiceMailBox::println("I2S DMA start failed!");
		}
		else
		{
			VoiceMailBox::println("I2S DMA started successfully.");
		}
    }

    void loop()
    {
        // Check if there was a Ping-Pong swap, triggered by the DMA ISR
        if (i2s.isDataReadyAndClearFlag())
        {
            // Get pointers to the microphone and speaker data array. 
            volatile int16_t* microphoneSamples = i2s.getRxBufPtr();
            volatile int16_t* audioOutSamples = i2s.getTxBufPtr();

            // Size of the current ping or pong buffer
            uint32_t bufferSize = i2s.getBufferSize();

            // Example processing: 
            // Stream the microphone directly back to the output
            memcpy((int16_t*)audioOutSamples, (int16_t*)microphoneSamples, bufferSize * sizeof(int16_t));
        }
    }
} 
