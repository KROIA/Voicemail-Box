#include "utilities/MP3.hpp"
#include <stdint.h>
#include <cstring>

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


		// Initialize the MP3 decoder
		m_decoder.readCallback = decoderReadCallback;
		SpiritMP3DecoderInit(&m_decoder.decoder,
			m_decoder.readCallback,
			nullptr,	// No processing function
			nullptr);	// No token
	}
	MP3::~MP3()
	{
		delete[] (uint8_t*)m_encoder.persist;
		delete[] (uint8_t*)m_encoder.scratch;

		delete[] m_decoder.tmpTxBuffer;
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

	bool MP3::startDecode(const std::string& mp3FilePath, uint32_t dmaTxSize, DigitalPin*dbgLed)
	{
		m_decoder.dbgLed = dbgLed;
		// Open the MP3 file
		m_decoder.file.open(mp3FilePath, File::AccessMode::read);
		if (!m_decoder.file.isOpen())
		{
			// Handle error opening file
			return false;
		}

		// Initialize the decoder
		SpiritMP3DecoderInit(&m_decoder.decoder,
			m_decoder.readCallback,
			nullptr,	// No processing function
			(void*)this);	// Pass the instance as user data

		if(m_decoder.tmpTxBuffer)
		{
			delete[] m_decoder.tmpTxBuffer;
		}
		m_decoder.tmpTxBuffer = new int16_t[dmaTxSize];
		return true;
	}
	bool MP3::stopDecode()
	{
		m_decoder.file.close();
		if (m_decoder.tmpTxBuffer)
		{
			delete[] m_decoder.tmpTxBuffer;
			m_decoder.tmpTxBuffer = nullptr;
		}
		return true;
	}
	bool MP3::decodeProcess(int16_t* dmaTx, uint32_t dmaTxSize)
	{
		if (m_decoder.file.isOpen())
		{
			//// Read the MP3 data from the file
			//uint32_t bytesRead = m_decoder.file.read(dmaTx, dmaTxSize);
			//if (bytesRead == 0)
			//{
			//	// Handle end of file or error
			//	return false;
			//}

			// Decode the MP3 data
			uint32_t samplesDecoded = SpiritMP3Decode(&m_decoder.decoder,
				dmaTx,
				dmaTxSize / 2,
				nullptr); // No informational structure
			return samplesDecoded > 0;
			//if (samplesDecoded > 0)
			//{
			//	// Process the decoded samples
			//	memcpy(dmaTx, m_decoder.tmpTxBuffer, samplesDecoded * sizeof(int16_t) * 2);
			//	if (samplesDecoded > dmaTxSize / (sizeof(int16_t) * 2))
			//	{
			//		// More samples decodes than required
			//		int a = 0;
			//	}
			//	return true;
			//}
		}
		return false;
	}

	unsigned int MP3::decoderReadCallback(
		void* pMP3CompressedData,
		unsigned int nMP3DataSizeInChars,
		void* pUserData)
	{
		MP3* instance = (MP3*)pUserData;
		if (instance->m_decoder.file.isOpen())
		{
			// Read the MP3 data from the file
			//if(instance->m_decoder.dbgLed)
			//{
			//	instance->m_decoder.dbgLed->set(1);
			//}
			uint32_t bytesRead = instance->m_decoder.file.read((uint8_t*)pMP3CompressedData, nMP3DataSizeInChars);
			//if (instance->m_decoder.dbgLed)
			//{
			//	instance->m_decoder.dbgLed->set(0);
			//}
			if (bytesRead == 0)
			{
				// Handle end of file or error
				return 0;
			}
			return bytesRead;
		}
		return 0;
	}

}
