#include "peripherals/i2s.hpp"


namespace VoiceMailBox
{
	I2S* I2S::s_instances[] = { nullptr };

	I2S::I2S(VMB_I2S_Handle* i2sHandle, uint16_t bufferSize)
		: m_i2s(i2sHandle)
		, m_halfCpltCallback(nullptr)
		, m_cpltCallback(nullptr)
		
#ifdef VMB_I2S_USE_STATIC_BUFFER_SIZE
		, m_dmaBufferSize(VMB_I2S_STATIC_BUFFER_SIZE)
		, m_adcDataBuffer{ 0 }
		, m_dacDataBuffer{ 0 }
#else
		, m_dmaBufferSize(bufferSize)
		, m_adcDataBuffer(new int16_t[bufferSize])
		, m_dacDataBuffer(new int16_t[bufferSize])
#endif
		, m_dataReadyFlag(0)
		, m_inBufPtr(&m_adcDataBuffer[0])
		, m_outBufPtr(&m_dacDataBuffer[0])
	{
		for (std::size_t i = 0; i < sizeof(s_instances); ++i)
		{
			if (s_instances[i] == nullptr)
			{
				s_instances[i] = this;
				break;
			}
		}
	}
	I2S::~I2S()
	{
		for (std::size_t i = 0; i < sizeof(s_instances); ++i)
		{
			if (s_instances[i] == this)
			{
				s_instances[i] = nullptr;
				break;
			}
		}
#ifndef VMB_I2S_USE_STATIC_BUFFER_SIZE
		delete[] m_adcDataBuffer;
		delete[] m_dacDataBuffer;
#endif
	}

	bool I2S::setupDMA()
	{
		VMB_HAL_Status status = VMB_HAL_I2SEx_TransmitReceive_DMA(m_i2s, (uint16_t*)(m_dacDataBuffer), (uint16_t*)(m_adcDataBuffer), m_dmaBufferSize);
		return status == VMB_HAL_Status::OK;
	}

	void I2S::setHalfCpltCallback(const std::function<void(I2S&)>& callback)
	{
		m_halfCpltCallback = callback;
	}
	void I2S::setCpltCallback(const std::function<void(I2S&)>& callback)
	{
		m_cpltCallback = callback;
	}


	void I2S::onI2S_TXRX_HalfCpltCallback(VMB_I2S_Handle* hi2s)
	{
		// Search the instance that matches the hi2s pointer
		// and call the specific callback on the instance
		for (std::size_t i = 0; i < sizeof(s_instances); ++i)
		{
			if (s_instances[i] != nullptr && s_instances[i]->m_i2s == hi2s)
			{
				s_instances[i]->onI2S_TXRX_HalfCpltCallback();
				return;
			}
		}
	}
	void I2S::onI2S_TXRX_CpltCallback(VMB_I2S_Handle* hi2s)
	{
		// Search the instance that matches the hi2s pointer
		// and call the specific callback on the instance
		for (std::size_t i = 0; i < sizeof(s_instances); ++i)
		{
			if (s_instances[i] != nullptr && s_instances[i]->m_i2s == hi2s)
			{
				s_instances[i]->onI2S_TXRX_CpltCallback();
				return;
			}
		}
	}



	void I2S::onI2S_TXRX_HalfCpltCallback()
	{
		// Inside ISR context! 
		m_inBufPtr = &m_adcDataBuffer[0];
		m_outBufPtr = &m_dacDataBuffer[0];

		m_dataReadyFlag = 1;
		if (m_halfCpltCallback)
		{
			m_halfCpltCallback(*this);
		}
	}
	void I2S::onI2S_TXRX_CpltCallback()
	{
		// Inside ISR context! 
		m_inBufPtr = &m_adcDataBuffer[m_dmaBufferSize / 2];
		m_outBufPtr = &m_dacDataBuffer[m_dmaBufferSize / 2];

		m_dataReadyFlag = 1;
		if (m_cpltCallback)
		{
			m_cpltCallback(*this);
		}
	}
}



