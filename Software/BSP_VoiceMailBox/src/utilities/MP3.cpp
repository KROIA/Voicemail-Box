#include "utilities/MP3.hpp"
#include <stdint.h>

namespace VoiceMailBox
{
	MP3::MP3()
		: m_encoder()
	{
		// Initialize the MP3 encoder
		m_encoder.persist = (TMP3E_persist*)new uint8_t[MP3E__SizeofPersistent()];
		m_encoder.scratch = (TMP3E_scratch*)new uint8_t[MP3E__SizeofScratch()];

		uint32_t MP3EncAudioLength = 0;
		uint32_t MP3EncSampleRate = 48000;

		uint32_t MP3EncBitRate = 48000;

		m_encoder.encInitStatus = MP3E__Init(
			m_encoder.persist,
			MP3EncSampleRate,
			MP3EncBitRate / 1000,     /* Bitrate, Kbps */
			m_encoder.encNumChannels,      /* Number of input channels */
			0);
	}
	MP3::~MP3()
	{
		delete[] (uint8_t*)m_encoder.persist;
		delete[] (uint8_t*)m_encoder.scratch;


	}


	uint32_t MP3::encode(int8_t*& outputBuffer, int16_t* inputBuffer)
	{
		//uint32_t encodedSize = 0;
		/* Encode PCM data and get the MP3 frame */
		m_encoder.encodedFrameData[m_encoder.encodedFrameIndexSwitch].frameData =
			(int8_t*)MP3E__Encode576(m_encoder.persist,
								     m_encoder.scratch,
									 (const short*)inputBuffer,
									 (const short*)((uint32_t)inputBuffer + 2),
									 m_encoder.encNumChannels,
									 (unsigned int*)&m_encoder.encodedFrameData[m_encoder.encodedFrameIndexSwitch].frameSize);

		m_encoder.encodedFrameIndexSwitch = (m_encoder.encodedFrameIndexSwitch + 1) % 2;	// Switch between the two encoded frame data buffers
		/* Check if the encoding was successful */
		if (m_encoder.encodedFrameData[m_encoder.encodedFrameIndexSwitch].frameSize != 0)
		{
			outputBuffer = m_encoder.encodedFrameData[m_encoder.encodedFrameIndexSwitch].frameData;
			uint32_t encodedSize = m_encoder.encodedFrameData[m_encoder.encodedFrameIndexSwitch].frameSize;
			m_encoder.encAudioLength += encodedSize;
			m_encoder.encodedFrameData[m_encoder.encodedFrameIndexSwitch].frameSize = 0;	// Reset the frame size for the next encoding
			return encodedSize;
		}
		return 0;
	}

}
