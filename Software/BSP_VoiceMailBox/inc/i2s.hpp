#ifndef I2S_HPP
#define I2S_HPP

#include <stdint.h>
#include <cstdio>
#include <functional>


namespace VoiceMailBox
{
	class I2S
	{
	public:
		
		I2S(void* i2sHandle, uint16_t bufferSize);
		~I2S();

		bool setupDMA();

		void setHalfCpltCallback(const std::function<void()>& callback)
		{
			m_halfCpltCallback = callback;
		}
		void setCpltCallback(const std::function<void()>& callback)
		{
			m_cpltCallback = callback;
		}


		bool isDataReady() const { return m_dataReadyFlag; }
		bool isDataReadyAndClear() {
			bool dataReady = m_dataReadyFlag;

			// To prevent race condition between reading the ready flag and resetting it, 
			// the reset is only done if the flag was set
			if (dataReady)
				m_dataReadyFlag = 0;
			return dataReady;
		}
		void clearDataReadyFlag() { m_dataReadyFlag = 0; }

		volatile int16_t* getRxBufPtr() { return m_inBufPtr; }
		volatile int16_t* getTxBufPtr() { return m_outBufPtr; }
		uint16_t getBufferSize() const { return m_dmaBufferSize / 2; }
		


		static void onI2S_TXRX_HalfCpltCallback(void* hi2s);
		static void onI2S_TXRX_CpltCallback(void* hi2s);
	private:
		void onI2S_TXRX_HalfCpltCallback();
		void onI2S_TXRX_CpltCallback();


		void* m_i2s;	// I2S_HandleTypeDef*
		std::function<void()> m_halfCpltCallback;
		std::function<void()> m_cpltCallback;


		/**
		 * @brief DMA Pingpong buffer
		 */
		uint16_t m_dmaBufferSize; // Size of the DMA Pingpong-Buffer
		volatile int16_t *m_adcDataBuffer; // Buffer for ADC data
		volatile int16_t *m_dacDataBuffer; // Buffer for DAC data
		volatile uint8_t m_dataReadyFlag = 0; // Flag to indicate if data is ready for processing
		volatile int16_t* m_inBufPtr; // Pointer to the current ADC buffer (Depending on the pingpong state)
		volatile int16_t* m_outBufPtr; // Pointer to the current DAC buffer (Depending on the pingpong state)



		// The list of instances is used to distribute the interrupts received on the peripheral
		static constexpr std::size_t max_instances = 20; // Maximum number of I2S instances
		static I2S* s_instances[max_instances]; // Array can hold instances of I2S
	};
}
#endif
