#include "i2s.hpp"
#include "HAL_abstraction.hpp"


namespace VoiceMailBox
{
	I2S* I2S::s_instances[max_instances] = { nullptr };

	I2S::I2S(void* i2sHandle, uint16_t bufferSize)
		: m_i2s(i2sHandle)
		, m_halfCpltCallback(nullptr)
		, m_cpltCallback(nullptr)
		, m_dmaBufferSize(bufferSize)
		, m_adcDataBuffer(new int16_t[bufferSize])
		, m_dacDataBuffer(new int16_t[bufferSize])
		, m_dataReadyFlag(0)
		, m_inBufPtr(&m_adcDataBuffer[0])
		, m_outBufPtr(&m_dacDataBuffer[0])
	{
		for (std::size_t i = 0; i < max_instances; ++i)
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
		for (std::size_t i = 0; i < max_instances; ++i)
		{
			if (s_instances[i] == this)
			{
				s_instances[i] = nullptr;
				break;
			}
		}
		delete[] m_adcDataBuffer;
		delete[] m_dacDataBuffer;
	}

	bool I2S::setupDMA()
	{
		VMB_HAL_Status status = VMB_HAL_I2SEx_TransmitReceive_DMA(static_cast<VMB_I2S_Handle*>(m_i2s), (uint16_t*)(m_dacDataBuffer), (uint16_t*)(m_adcDataBuffer), m_dmaBufferSize);
		return status == VMB_HAL_Status::OK;
	}


	void I2S::onI2S_TXRX_HalfCpltCallback(void* hi2s)
	{
		for (std::size_t i = 0; i < max_instances; ++i)
		{
			if (s_instances[i] != nullptr && s_instances[i]->m_i2s == hi2s)
			{
				s_instances[i]->onI2S_TXRX_HalfCpltCallback();
				return;
			}
		}
	}
	void I2S::onI2S_TXRX_CpltCallback(void* hi2s)
	{
		for (std::size_t i = 0; i < max_instances; ++i)
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
			m_halfCpltCallback();
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
			m_cpltCallback();
		}
	}
}


void HAL_I2SEx_TxRxHalfCpltCallback(I2S_HandleTypeDef* hi2s)
{
	/*if (VoiceMailBox::Platform::codec.getI2S().i2s == hi2s)
	{
		VoiceMailBox::Platform::codec.onI2S_DMA_TxRx_HalfCpltCallback();
	}*/
	VoiceMailBox::I2S::onI2S_TXRX_HalfCpltCallback(hi2s); // Call the static method to handle the callback
}


void HAL_I2SEx_TxRxCpltCallback(I2S_HandleTypeDef* hi2s)
{
	/*if (VoiceMailBox::Platform::codec.getI2S().i2s == hi2s)
	{
		VoiceMailBox::Platform::codec.onI2S_DMA_TxRx_CpltCallback();
	}*/
	VoiceMailBox::I2S::onI2S_TXRX_CpltCallback(hi2s); // Call the static method to handle the callback
}
