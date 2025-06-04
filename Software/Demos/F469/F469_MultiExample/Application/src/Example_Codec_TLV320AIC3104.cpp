#include "Example_Codec_TLV320AIC3104.hpp"
#include "BSP_VoiceMailBox.hpp"
#include "main.h"
#include <memory>
#include <cmath>

namespace Example_Codec_TLV320AIC3104
{
	/**
	 * @brief This example shows a basic usage of the TLV320AIC3104 codec.
	 * @details
	 * A codec object gets created manually this is not recomended since the BSP_VoiceMailBox already has a codec object created.
	 * But in case you want to create your own codec object for whatever reason, this example shows how to do it.
	 * The example captures audio data from the codec and plays it back directly.
	 */
	void setup_CaptureAndPlayback();
	void loop_CaptureAndPlayback();


	/**
	 * @brief This example shows a basic usage of the TLV320AIC3104 codec with volume control.
	 * @details
	 * Not like in the first example, in this the codec from the BSP_VoiceMailBox is used.
	 * This is more easy because the BSP already has created the codec object with all the correct handles.
	 * The POT1 potentiometer is used to control the volume of the audio data captured from the codec.
	 */
	void setup_CaptureAndPlaybackWithVolume();
	void loop_CaptureAndPlaybackWithVolume();
	
	

	void setup_PerformanceTracking();
	void loop_PerformanceTracking();

	

// ------------------------------------------------------------------------------------------------
// ================================================================================================
// ------------------------------------------------------------------------------------------------
	void setup()
	{
		//setup_CaptureAndPlayback();
		//setup_CaptureAndPlaybackWithVolume();
		setup_PerformanceTracking();
	}

	void loop()
	{
		//loop_CaptureAndPlayback();
		//loop_CaptureAndPlaybackWithVolume();
		loop_PerformanceTracking();
	}






// ------------------------------------------------------------------------------------------------
// ================================================================================================
// ------------------------------------------------------------------------------------------------
	VoiceMailBox::Codec_TLV320AIC3104* codec = nullptr;
	VoiceMailBox::I2C *i2c = nullptr;
	void setup_CaptureAndPlayback()
	{
		using namespace VoiceMailBox;

		// Create a I2C object on which the codec is connected
		i2c = new VoiceMailBox::I2C(getI2C_Handle());

		// Create a codec object and providing the I2S and I2C haldes.
		// 1024 for the I2S buffer size which is only used when the macro "VMB_I2S_USE_STATIC_BUFFER_SIZE" is not defined in the settings.h.
		// 0x18 is the default I2C address of the TLV320AIC3104 and can be found in its datasheet.
		// GPIO_TypeDef* and pin must be passed. It is the Reset pin of the codec: PIN 31.
		codec = new Codec_TLV320AIC3104(getI2S_CODEC(), 1024,
										*i2c, 0x18,
										CODEC_NRESET_GPIO_Port, CODEC_NRESET_Pin);

		codec->setup();
	}
	void loop_CaptureAndPlayback()
	{
		using namespace VoiceMailBox;

		// Process the codecs audio data
		if (codec->isDataReadyAndClearFlag())
		{
			int16_t* txBuffer = (int16_t*)codec->getTxBufPtr();
			int16_t* rxBuffer = (int16_t*)codec->getRxBufPtr();
			uint32_t size = codec->getBufferSize();

			// Redirect capture to the output
			memcpy(txBuffer, rxBuffer, size * sizeof(int16_t));
		}
	}





// ------------------------------------------------------------------------------------------------
// ================================================================================================
// ------------------------------------------------------------------------------------------------
	void setup_CaptureAndPlaybackWithVolume()
	{
		using namespace VoiceMailBox;
		VoiceMailBox::setup();
	}
	void loop_CaptureAndPlaybackWithVolume()
	{
		using namespace VoiceMailBox;
		VoiceMailBox::update();
		AudioCodec& codec = getCodec();
		AnalogPin& potentiometer = getPotentiometer(Potentiometer::POT1);

		if (codec.isDataReadyAndClearFlag())
		{
			uint32_t potentiometerValue = potentiometer.getValue();
			double volumePercent = 100 - ((double)potentiometerValue * 100.0 / (double)potentiometer.getMaxValue());

			// volumeScale is a value with range [0.36 - 2.71]
			double volumeScale = std::exp((volumePercent - 50) / 50.0); // Scale the volume based on the potentiometer value

			int16_t* rxBuffer = (int16_t*)codec.getRxBufPtr();
			int16_t* txBuffer = (int16_t*)codec.getTxBufPtr();
			uint32_t bufferSize = codec.getBufferSize();

			for (uint32_t i = 0; i < bufferSize; ++i)
			{
				// Apply volume scaling to the captured audio data
				txBuffer[i] = static_cast<int16_t>(rxBuffer[i] * volumeScale);
			}
		}
	}



// ------------------------------------------------------------------------------------------------
// ================================================================================================
// ------------------------------------------------------------------------------------------------

	const uint32_t maxDelayMS = 100; // Maximum delay in milliseconds
	void setup_PerformanceTracking()
	{
		VoiceMailBox::setup();
	}
	void loop_PerformanceTracking()
	{
		using namespace VoiceMailBox;
		DigitalPin& led0 = getLed(LED::LED0);
		DigitalPin& led1 = getLed(LED::LED1);

		led0.set(1);

		VoiceMailBox::update();
		AudioCodec& codec = getCodec();
		AnalogPin& potentiometer = getPotentiometer(Potentiometer::POT1);

		led0.set(0);
		if (codec.isDataReadyAndClearFlag())
		{
			// Start processing
			led1.set(1);
			codec.startDataProcessing();                              // Used to mesure processing performance
			uint32_t potentiometerValue = potentiometer.getValue();
			uint32_t delayMS = maxDelayMS - ((double)potentiometerValue * maxDelayMS / (double)potentiometer.getMaxValue()); // 0 - 100 ms

			int16_t* rxBuffer = (int16_t*)codec.getRxBufPtr();
			int16_t* txBuffer = (int16_t*)codec.getTxBufPtr();
			uint32_t bufferSize = codec.getBufferSize();

			delay(delayMS);											  // simulate processing time
			memcpy(txBuffer, rxBuffer, bufferSize * sizeof(int16_t)); // Redirect capture to the output
			codec.endDataProcessing();                                // Used to mesure processing performance
			led1.set(0);
			// End processing

			float performanceRatio = codec.getProcessingTimeRatio();
			if (performanceRatio > 1)
			{
				println("Processing time utilization: %.2f%% ! Processing takes longer than it should !", performanceRatio * 100.0f);
			}
			else
			{
				println("Processing time utilization: %.2f%%", performanceRatio * 100.0f);
			}
		}
	}
} 
