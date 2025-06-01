#include "Example_DCOffset.hpp"
#include "BSP_VoiceMailBox.hpp"
#include "main.h"
#include <memory>

namespace Example_DCOffset
{
    /**
	 * @brief This example shows how to remove the DC offset from the left and right audio channels.
	 * @details
	 * Download the Serial Oscilloscope from https://x-io.co.uk/serial-oscilloscope/
	 * Connect it to the STM32 via USB and open the Serial Monitor.
	 * In the Serial Oscilloscope, click "Oscilloscope->Channel 1,2 and 3".
	 * Once the example is running, you can see the Left and Right microphone audio channels visualized in the Serial Oscilloscope.
	 * Press the button BTN0 to toggle the DC offset removal on and off.
     */

    bool applyDCOffset = false;
    void setup()
    {
		using namespace VoiceMailBox;
        VoiceMailBox::setup();

		// Button to toggle the DC offset removal on and off
		getButton(Button::BTN0).setOnFallingEdgeCallback([](DigitalPin&) {
			    applyDCOffset = !applyDCOffset;
                AudioCodec& codec = getCodec();
			    codec.enableMeasurementRXDCOffset(applyDCOffset);
                //println("DC Offset %s", applyDCOffset ? "enabled" : "disabled");
			});
    }

    void loop()
    {
    	using namespace VoiceMailBox;
    	VoiceMailBox::update();

        AudioCodec& codec = getCodec();
        if (codec.isDataReadyAndClearFlag())
        {
			int16_t rxDCOffsetLeft  = codec.getRXDCOffsetLeft();
			int16_t rxDCOffsetRight = codec.getRXDCOffsetRight();

            if(applyDCOffset)
			{
				codec.removeRXDCOffsetLeft();
				codec.removeRXDCOffsetRight();
			}

			int16_t* rxBuffer = (int16_t*)codec.getRxBufPtr();
			uint32_t bufferSize = codec.getBufferSize();


			// Do not print all the samples since the UART is way to slow for that
			for (uint32_t i = 0; i < bufferSize; i+=100)
			{
				// Using the Serial Oscilloscope, you can visualize the audio data
				print((std::to_string(rxBuffer[i]) +","+ std::to_string(rxBuffer[i+1]) + "\r").c_str());
			}
			

			// Copy the received audio data to the transmit buffer
			// Not important for this example
			memcpy((int16_t*)codec.getTxBufPtr(), (int16_t*)codec.getRxBufPtr(), bufferSize * sizeof(int16_t));
        }
    }
} 
