#include "utilities/MP3_encoder.hpp"
#include <stdint.h>
#include <cstring>

namespace VoiceMailBox
{
	MP3_encoder::MP3_encoder(uint32_t sampleRate, uint32_t bitrateKbps, uint16_t numChannels)
		: m_sampleRate(sampleRate)
		, m_bitrateKbps(bitrateKbps)
		, m_numChannels(numChannels)
	{
		// Initialize the MP3_encoder encoder
		m_persist = (TMP3E_persist*)new uint8_t[MP3E__SizeofPersistent()];
		m_scratch = (TMP3E_scratch*)new uint8_t[MP3E__SizeofScratch()];

		m_encInitStatus = MP3E__Init(
			m_persist,
			sampleRate,
			bitrateKbps,     /* Bitrate, Kbps */
			m_numChannels,      /* Number of input channels */
			0);
	}
	MP3_encoder::~MP3_encoder()
	{
		delete[] (uint8_t*)m_persist;
		delete[] (uint8_t*)m_scratch;
	}


	uint32_t MP3_encoder::encode(int8_t*& outputBuffer, const int16_t* inputBuffer)
	{
		/* Encode PCM data and get the MP3_encoder frame */
		m_encodedFrameData[m_encodedFrameIndexSwitch].frameData =
			(int8_t*)MP3E__Encode576(m_persist,
								     m_scratch,
									 (const short*)inputBuffer,
									 (const short*)((uint32_t)inputBuffer + 2),
									 m_numChannels,
									 (unsigned int*)&m_encodedFrameData[m_encodedFrameIndexSwitch].frameSize);

		m_encodedFrameIndexSwitch = (m_encodedFrameIndexSwitch + 1) % 2;	// Switch between the two encoded frame data buffers
		/* Check if the encoding was successful */
		if (m_encodedFrameData[m_encodedFrameIndexSwitch].frameSize != 0)
		{
			outputBuffer = m_encodedFrameData[m_encodedFrameIndexSwitch].frameData;
			uint32_t encodedSize = m_encodedFrameData[m_encodedFrameIndexSwitch].frameSize;
			m_encodedFrameData[m_encodedFrameIndexSwitch].frameSize = 0;	// Reset the frame size for the next encoding
			return encodedSize;
		}
		return 0;
	}
}
