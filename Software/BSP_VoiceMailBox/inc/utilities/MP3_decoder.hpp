#ifndef MP3_DECODER_HPP
#define MP3_DECODER_HPP
/**
 * @author Alex Krieg
 */


#include "HAL_abstraction.hpp"
#if defined(VMB_AUDIO_FORMAT_MP3)
#include "utilities/File.hpp"
#include "peripherals/digitalPin.hpp"
#include <string>
#include "../Middlewares/ST/STM32_Audio/Codecs/SpiritDSP_MP3_Dec/inc/spiritMP3Dec.h"


namespace VoiceMailBox
{
	/**
	 * @brief This class uses the SPIRIT Audio Engine from STMicroelectronics to decode MP3 files.
	 * @details
	 *   A reader callback function must be passed to the constructor, which is called by the decoder to read the MP3 data.
	 *   The callback function must return the number of bytes read from the file or other source.
	 * 
	 *   The decode methode is called when the DMA interrupt (half complete and complete) has occured. Not inside the ISR!
	 */
	class MP3_decoder
	{
	public:
		/**
		 * @brief Constructor
		 * @param mp3ReadDataCallback function that gets called by the SPIRIT MP3 decoder to read the MP3 data
		 * @param argForReadDataCallback custom argument to any object that can be received when the callback is called 
		 * @param sampleSize that defines how many bytes one audio sample consists of.
		 *                   1 sample = Left + Right channel @ 16 bits per channel --> 4 bytes
		 */
		MP3_decoder(fnSpiritMP3ReadCallback* mp3ReadDataCallback, void* argForReadDataCallback, uint8_t sampleSize);
		~MP3_decoder();

		/**
		 * @brief MP3 to PCM decoder
		 * @param dmaTx is the DMA buffer that is currently not used by the DMA to stream audio data to the I2S peripheral.
		 *              Using a Ping-Pong Buffer for the DMA. When the DMA uses The Ping buffer, the decoder writes to the Pong buffer and vice versa.
		 * @param requestedSampleCount Amount of samples requested to decode. Make sure to calculate the value correctly. It is not the size of the buffer!
		 *                             It is the numer of samples that should be decoded. One sample may contains multiple array elements!
		 *                             Make sure that the size used is divisible by 576, which is the number of samples per frame in MP3.
		 * @return the number of samples decoded and written to the dmaTx buffer.
		 */
		uint32_t decode(int16_t* dmaTx, uint32_t requestedSampleCount);
	private:
		uint8_t m_sampleSize; // Size in bytes per sample. 1 sample = Left + Right channel @ 16 bits per channel --> 4 bytes
		TSpiritMP3Decoder m_decoder;
	};
}
#endif // defined(VMB_AUDIO_FORMAT_MP3)
#endif // MP3_DECODER_HPP