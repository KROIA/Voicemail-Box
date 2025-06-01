#include "utilities/MP3_decoder.hpp"
#if defined(VMB_AUDIO_FORMAT_MP3)
#include <stdint.h>
#include <cstring>


namespace VoiceMailBox
{
	MP3_decoder::MP3_decoder(fnSpiritMP3ReadCallback* mp3ReadDataCallback, void* argForReadDataCallback, uint8_t sampleSize)
		: m_sampleSize(sampleSize)
	{
		// Initialize the decoder
		SpiritMP3DecoderInit(&m_decoder,
			mp3ReadDataCallback,
			nullptr,	// No processing function
			argForReadDataCallback);	// Pass the instance as user data
	}
	MP3_decoder::~MP3_decoder()
	{
	
	}

	uint32_t MP3_decoder::decode(int16_t* dmaTx, uint32_t requestedSampleCount)
	{
		uint32_t samplesDecoded = SpiritMP3Decode(&m_decoder,
			dmaTx,
			requestedSampleCount, 
			nullptr); // No informational structure

		if (samplesDecoded != requestedSampleCount)
		{
			// Set remaining samples to 0
			memset((uint8_t*)dmaTx + samplesDecoded * m_sampleSize, 0, (requestedSampleCount - samplesDecoded) * m_sampleSize);
		}
		return samplesDecoded;
	}
}
#endif