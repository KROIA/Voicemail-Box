#include "utilities/MP3File.hpp"
#include <cstring>

namespace VoiceMailBox
{
	MP3File::MP3File(uint32_t sampleRate, uint16_t bitrate, uint16_t numChannels)
		: Logger("MP3File")
		, m_sampleSize(4) // Size in bytes per sample. 1 sample = Left + Right channel @ 16 bits per channel --> 4 bytes
		, m_file()
		, m_encoder(sampleRate, bitrate, numChannels)
		, m_decoder(decoderReadCallback, this, m_sampleSize)

	{

	}
	MP3File::~MP3File()
	{
		close();
	}

	uint32_t MP3File::writeAudioSamples(const int16_t* data, uint32_t sampleCount)
	{
		if (!m_file.isOpen())
		{
			logln("Failed to write audio samples, file is not open: " + m_file.getPath());
			return 0;
		}
		if (m_file.getAccessMode() != File::AccessMode::write)
		{
			logln("Failed to write audio samples, file is not opened in write mode: " + m_file.getPath());
			return 0;
		}

		uint32_t savedBytes = 0;
		for (uint32_t i = 0; i < sampleCount / 576; ++i)
		{
			int8_t* mp3Buffer = nullptr;
			uint32_t bytesToWrite = m_encoder.encode(mp3Buffer, (data + (m_sampleSize/2 * i * 576)));
			savedBytes += bytesToWrite;
			if (bytesToWrite > 0)
				m_file.write((const char*)mp3Buffer, bytesToWrite);
		}
		
		return savedBytes;
	}
	uint32_t MP3File::readAudioSamples(int16_t* data, uint32_t sampleCount)
	{
		if (!m_file.isOpen())
		{
			logln("Failed to write audio samples, file is not open: " + m_file.getPath());
			return 0;
		}
		if (m_file.getAccessMode() != File::AccessMode::read)
		{
			logln("Failed to read audio samples, file is not opened in read mode: " + m_file.getPath());
			return 0;
		}
		
		uint32_t decodedSamples = m_decoder.decode(data, sampleCount);
		return decodedSamples;
	}


	unsigned int MP3File::decoderReadCallback(
		void* pMP3_decoderCompressedData,
		unsigned int nMP3_decoderDataSizeInChars,
		void* pUserData)
	{
		MP3File* instance = (MP3File*)pUserData;
		if (instance->m_file.isOpen())
		{
			// Read the MP3_decoder data from the file
			uint32_t bytesRead = instance->m_file.read((uint8_t*)pMP3_decoderCompressedData, nMP3_decoderDataSizeInChars);
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
