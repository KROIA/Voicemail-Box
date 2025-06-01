#include "peripherals/AudioCodec.hpp"


namespace VoiceMailBox
{
	void AudioCodec::update()
	{
		if (m_enableMeasurementRXDCOffset)
		{
			// Get the current ADC buffer pointer
			int16_t* rxBufPtr = (int16_t*)getRxBufPtr();
			if (rxBufPtr != m_lastRXBufPtr)
			{
				m_lastRXBufPtr = rxBufPtr;
				
				uint32_t buffSize = getBufferSize();

				// Using a simple FIR filter to calculate the DC offset
				float invCoeff = 1.0f - m_FIR_filterCoefficient;
				for (size_t i = 0; i < buffSize; i+=2)
				{
					m_RXDCOffset_FIR_filterLeft  = m_RXDCOffset_FIR_filterLeft  * invCoeff + static_cast<float>(rxBufPtr[i])     * m_FIR_filterCoefficient;
					m_RXDCOffset_FIR_filterRight = m_RXDCOffset_FIR_filterRight * invCoeff + static_cast<float>(rxBufPtr[i + 1]) * m_FIR_filterCoefficient;
				}
			}
		}
	}

	void AudioCodec::removeRXDCOffsetLeft()
	{
		update();
		int16_t offset = getRXDCOffsetLeft();
		if (offset != 0)
		{
			volatile int16_t* rxBufPtr = getRxBufPtr();
			uint32_t buffSize = getBufferSize();
			for (size_t i = 0; i < buffSize; i += 2)
			{
				rxBufPtr[i] -= offset;
			}
		}
	}
	void AudioCodec::removeRXDCOffsetRight()
	{
		update();
		int16_t offset = getRXDCOffsetRight();
		if (offset != 0)
		{
			volatile int16_t* rxBufPtr = getRxBufPtr();
			uint32_t buffSize = getBufferSize();
			for (size_t i = 1; i < buffSize; i += 2)
			{
				rxBufPtr[i] -= offset;
			}
		}
	}
}
