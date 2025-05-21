#ifndef MP3_HPP
#define MP3_HPP
/**
 * @brief 
 * @details 
 * @author Alex Krieg
 */


#include "HAL_abstraction.hpp"
#include "utilities/File.hpp"
#include "peripherals/digitalPin.hpp"
#include <string>
#include "../Middlewares/ST/STM32_Audio/Codecs/SpiritDSP_MP3_Enc/inc/spiritMP3Enc.h"
#include "../Middlewares/ST/STM32_Audio/Codecs/SpiritDSP_MP3_Dec/inc/spiritMP3Dec.h"


namespace VoiceMailBox
{
	class MP3
	{
	public:
		MP3();
		~MP3();

		/**
		 * @brief Encodes the given audio samples for Left and Right channel. to MP3 Frames.
		 * @param outputBuffer encoded data buffer
		 * @param inputBuffer Interleaved PCM data buffer (16-bit signed integer) [Left, Right, Left, Right...]
		 *                    This buffer must contain 576 samples (2 channels * 576 samples * 16 bits = 2304 bytes)
		 * @return the size of the output buffer in bytes
		 */
		uint32_t encode(int8_t*& outputBuffer, int16_t* inputBuffer);


		bool startDecode(const std::string& mp3FilePath, uint32_t dmaTxSize, DigitalPin*dbgLed);
		bool stopDecode();
		bool decodeProcess(int16_t* dmaTx, uint32_t dmaTxSize);
	private:

		static unsigned int decoderReadCallback(
			void* pMP3CompressedData,                 
			unsigned int nMP3DataSizeInChars,           
			void* pUserData);                           

		struct EncoderData
		{
			TMP3E_persist* persist = nullptr;
			TMP3E_scratch* scratch = nullptr;
			uint32_t encAudioLength = 0;
			uint32_t encNumChannels = 2;
			E_MP3E_STATUS encInitStatus;

			struct EncodedFrameData
			{
				uint32_t frameSize = 0;	// Size of the encoded frame in bytes
				int8_t* frameData = nullptr;	// Pointer to the encoded frame data
			};

			EncodedFrameData encodedFrameData[2];
			uint8_t encodedFrameIndexSwitch = 0;	// Switch between the two encoded frame data buffers
		};

		struct DecoderData
		{
			TSpiritMP3Decoder decoder;
			fnSpiritMP3ReadCallback* readCallback = nullptr;
			File file;
			int16_t* tmpTxBuffer = nullptr;
			DigitalPin* dbgLed = nullptr;
		};

		EncoderData m_encoder;
		DecoderData m_decoder;
	};
}
#endif