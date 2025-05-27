#ifndef AUDIO_CODEC_H
#define AUDIO_CODEC_H
/**
 * @brief
 * @details
 *
 * @author Alex Krieg
 */

#include "HAL_abstraction.hpp"
#include <stdint.h>

namespace VoiceMailBox
{
	/**
	 * @brief This interface class defines generic functionality for the usage of a audio codec.
	 *        Derive from this class in case a new type of codec is used.
	 */
	class AudioCodec
	{
	public:
		virtual ~AudioCodec() = default;

		/**
		 * @brief Start the DMA for i2s
		 * @return true if start was successful, otherwise false
		 */
		virtual bool startDMA() = 0;

		/**
		 * @brief Stop the DMA for i2s
		 * @return true if stop was successful, otherwise false
		 */
		virtual bool stopDMA() = 0;

		/**
		 * @return true if a new batch of audio samples is ready to be processed.
		 */
		virtual bool isDataReady() const = 0;

		/**
		 * @brief Checks the data ready flag and clears it if it was set.
		 * @return true if a new batch of audio samples is ready to be processed.
		 */
		virtual bool isDataReadyAndClearFlag() = 0;

		/**
		 * @brief Clears the data ready flag.
		 */
		virtual void clearDataReadyFlag() = 0;

		/**
		 * @brief Gets the current ADC buffer pointer.
		 * @return current ADC buffer pointer
		 */
		virtual volatile int16_t* getRxBufPtr() = 0;

		/**
		 * @brief Gets the current DAC buffer pointer.
		 * @return current DAC buffer pointer
		 */
		virtual volatile int16_t* getTxBufPtr() = 0;


		/**
		 * @brief Gets the size of the ping and pong buffer.
		 * @return size of the ping and pong buffer
		 */
		virtual uint32_t getBufferSize() const = 0;

		/**
		 * @brief Gets the sample rate of the audio codec
		 * @return samplerate [Hz]
		 */
		virtual uint32_t getSampleRate() const = 0;

		/**
		 * @brief Gets the sample resolution
		 * @return amount of bits per sample
		 */
		virtual uint16_t getBitsPerSample() const = 0;

		/**
		 * @brief Gets the amount of channels
		 * @return 1 for mono and 2 for stereo
		 */
		virtual uint16_t getNumChannels() const = 0;

		/**
		 * @brief Sets the DMA's TX (audio output) buffer to 0
		 */
		virtual void clearTxBuf() = 0;
		

		// -----------------------------------------------------------------
		//    Performance measurements
		// -----------------------------------------------------------------
		/**
		 * @brief In order to use the function getProcessingTimeRatio(),
		 *        the function startDataProcessing() must be called on start of the data processing
		 * @note The VMB_ENABLE_CODEC_PERFORMANCE_MEASUREMENTS macro must be defined, otherwise this function does nothing
		 */
		virtual void startDataProcessing() = 0;

		/**
		 * @brief In order to use the function getProcessingTimeRatio(),
		 *        the function endDataProcessing() must be called on end of the data processing
		 * @note The VMB_ENABLE_CODEC_PERFORMANCE_MEASUREMENTS macro must be defined, otherwise this function does nothing
		 */
		virtual void endDataProcessing() = 0;

		/**
		 * @brief Returns the ratio of the processing time to the DMA transfer time
		 * @note The VMB_ENABLE_CODEC_PERFORMANCE_MEASUREMENTS macro must be defined, otherwise this function does nothing
		 * @details: The ratio is calculated as follows:
		 *
		 * 	               |  DMA has new data ready      DMA has new data ready
		 *                 |           \                  /          \
		 * 	               |            \                /            \
		 * 	               |             +--------------+			   +--------------+
		 * 	               |             |              |	t_dma      |	t_dma	  |
		 * 	               |             |              |<------------>|<------------>|
		 * 	          DMA  | ------------+              +--------------+			  +---
		 * 	               |
		 *                 |              +--+			 +--+			+--+		   +--+
		 * 	               |              |  |			 |  |		    |  |		   |  |
		 * 	               |              |  | 			 |  | 			|  | 		   |  |
		 * Data Processing | -------------+  +-----------+  +-----------+  +-----------+  +---
		 *                 |             /    \
		 *                 |            /      \                        |<>|<--------->|
		 *                 |Data Processing     Data Processing         t_p    t_idle
		 *                 |     Start               End
		 *                 +--------------------------------------------------------------> Time
		 *
		 *
		 *		t_dma: Time it takes for a half DMA transfer. After each half DMA transfer, a new processing workload is ready.
		 *        t_p: Time it takes to process the data.
		 *	   t_idle: Time it takes to wait for the next half DMA transfer until new data is available.
		 *
		 *        The ratio is calculated as follows:
		 *		  Ratio = t_p / t_dma
		 *
		 * The ratio is used to determine if the processing time is too long compared to the DMA transfer time.
		 * If the ratio is greater than 1, it means that the processing time is longer than the DMA transfer time.
		 * The value should be in the range of 0 to 1, where 0 means, that processing is so fast,
		 * the processor is idle most of the time.
		 * When the ratio near 1, it means that there is not much margin for processing time.
		 *
		 * The ratio can be lowered, by increasing the DMA buffer size.
		 * But this will increase the latency of the system.
		 *
		 * @return Processing time ratio
		 */
		virtual float getProcessingTimeRatio() const = 0;

	protected:

	};
}
#endif
