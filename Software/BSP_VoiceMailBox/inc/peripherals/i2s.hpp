#ifndef I2S_HPP
#define I2S_HPP
/**
 * @brief I2S abstraction class
 * @details This class provides an interface to the I2S peripheral of the STM32 microcontroller.
 *          It handles the DMA transfer and provides a callback mechanism for processing data.
 * @author Alex Krieg
 */

#include <functional>
#include <cstring>
#include "HAL_abstraction.hpp"


namespace VoiceMailBox
{
	class I2S
	{
	public:
		/**
		 * @brief Constructor
		 * @param i2sHandle HAL handle for the I2S peripheral
		 * @param bufferSize Size of the DMA buffer. Each buffer element is 2 bytes (16 bit).
		 *                   The size is only used when the VMB_I2S_USE_STATIC_BUFFER_SIZE macro is not defined
		 */
		I2S(VMB_I2S_Handle* i2sHandle, uint32_t bufferSize);
		~I2S();

		/**
		 * @brief Starts the I2S DMA transfer.
		 * @return true if successful, false otherwise.
		 */
		bool startDMA();

		bool stopDMA();

		/**
		 * @brief Sets a custom callback function to be called when the DMA transfer is half complete.
		 * @note The callback function will be called in the context of the DMA interrupt handler.
		 *		 Therefore do not call any blocking or long running functions in the callback.
		 * @param callback 
		 */
		void setHalfCpltCallback(const std::function<void(I2S&)>& callback);

		/**
		 * @brief Sets a custom callback function to be called when the DMA transfer is complete.
		 * @note The callback function will be called in the context of the DMA interrupt handler.
		 *		 Therefore do not call any blocking or long running functions in the callback.
		 * @param callback 
		 */
		void setCpltCallback(const std::function<void(I2S&)>& callback);

		/**
		 * @brief Checks if a new batch of data is ready to be processed
		 * @note The flag is not reset automatically after reading it.
		 * @return true if new data is ready, false otherwise
		 */
		bool isDataReady() const { return m_dataReadyFlag; }

		/**
		 * @brief Checks if a new batch of data is ready to be processed
		 * @note The flag is reset automatically after reading it.
		 * @return true if new data is ready, false otherwise
		 */
		bool isDataReadyAndClearFlag() {
			bool dataReady = m_dataReadyFlag;

			// To prevent race condition between reading the ready flag and resetting it, 
			// the reset is only done if the flag was set
			if (dataReady)
				m_dataReadyFlag = 0;
			return dataReady;
		}

		/**
		 * @brief Clears the data ready flag.
		 */
		void clearDataReadyFlag() { m_dataReadyFlag = 0; }

		/**
		 * @brief Gets the current ADC buffer pointer.
		 * @note Do read this pointer on every processing call to get the correct buffer.
		 * @return current pingpong buffer pointer for ADC data
		 */
		volatile int16_t* getRxBufPtr() { return m_inBufPtr; }

		/**
		 * @brief Gets the current DAC buffer pointer.
		 * @note Do read this pointer on every processing call to get the correct buffer.
		 * @return current pingpong buffer pointer for DAC data
		 */
		volatile int16_t* getTxBufPtr() { return m_outBufPtr; }

		/**
		 * @brief Gets the size of the ping and pong buffer.
		 * @return size of the ping and pong buffer
		 */
		uint32_t getBufferSize() const { return m_dmaBufferSize / 2; }
		
		/**
		 * @brief Gets the I2S HAL handle. 
		 * @return i2s handle
		 */
		VMB_I2S_Handle * const getHandle() const { return m_i2s; }

		/**
		 * @brief Sets all DAC values to 0.
		 */
		void clearTxBuf() {
			memset((uint16_t*)m_dacDataBuffer, 0, m_dmaBufferSize * sizeof(int16_t)); // Clear the DAC buffer
		}



		/**
		 * @brief ISR callback from the HAL library calls this function to notify the I2S instance
		 * @warning Do not call this function from any other function than the specific ISR.
		 * @param hi2s 
		 */
		static void onI2S_TXRX_HalfCpltCallback(VMB_I2S_Handle* hi2s);

		/**
		 * @brief ISR callback from the HAL library calls this function to notify the I2S instance
		 * @warning Do not call this function from any other function than the specific ISR.
		 * @param hi2s 
		 */
		static void onI2S_TXRX_CpltCallback(VMB_I2S_Handle* hi2s);
	private:
		void onI2S_TXRX_HalfCpltCallback();
		void onI2S_TXRX_CpltCallback();


		VMB_I2S_Handle * const m_i2s;	// I2S_HandleTypeDef*
		std::function<void(I2S&)> m_halfCpltCallback;
		std::function<void(I2S&)> m_cpltCallback;


		/**
		 * @brief DMA Pingpong buffer
		 */
		const uint32_t m_dmaBufferSize; // Size of the DMA Pingpong-Buffer
#ifdef VMB_I2S_USE_STATIC_BUFFER_SIZE
		volatile int16_t m_adcDataBuffer[VMB_I2S_STATIC_BUFFER_SIZE]; // Buffer for ADC data
		volatile int16_t m_dacDataBuffer[VMB_I2S_STATIC_BUFFER_SIZE]; // Buffer for DAC data
#else
		volatile int16_t *m_adcDataBuffer; // Buffer for ADC data
		volatile int16_t *m_dacDataBuffer; // Buffer for DAC data
#endif
		volatile uint8_t m_dataReadyFlag = 0; // Flag to indicate if data is ready for processing
		volatile int16_t* m_inBufPtr; // Pointer to the current ADC buffer (Depending on the pingpong state)
		volatile int16_t* m_outBufPtr; // Pointer to the current DAC buffer (Depending on the pingpong state)



		// The list of instances is used to distribute the interrupts received on the peripheral
		static I2S* s_instances[VMB_I2S_MAX_INSTANCES]; // Array can hold instances of I2S
	};
}
#endif
