#include "peripherals/AudioCodec.hpp"


namespace VoiceMailBox
{
	void AudioCodec::update()
	{
		if (m_enableMeasurementRXDCOffset)
		{
			if (isDataReady())
			{
				// Get the current ADC buffer pointer
				volatile int16_t* rxBufPtr = getRxBufPtr();
				uint32_t buffSize = getBufferSize();

				// Using a simple FIR filter to calculate the DC offset
				for (size_t i = 0; i < buffSize; ++i)
				{
					m_RXDCOffset_FIR_filter = m_RXDCOffset_FIR_filter * 0.9f + static_cast<float>(rxBufPtr[i]) * 0.1f;
				}
			}
		}
	}
}