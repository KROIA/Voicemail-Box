#include "utilities/WAVFile.hpp"
#include <cstring>

namespace VoiceMailBox
{
	WAVFile::WAVFile()
#ifdef VMB_USE_LOGGER_OBJECTS
		: Logger("WAVFile")
		, m_file()
#else
		: m_file()
#endif
		, m_sampleCounter(0)
		, m_sampleRate(16000)
		, m_numChannels(1)
		, m_bitsPerSample(16)
	{
	}
	WAVFile::~WAVFile()
	{
		close();
	}

	bool WAVFile::open(const std::string& filePath, File::AccessMode mode)
	{
		if (m_file.open(filePath, mode))
		{
			if (mode == File::AccessMode::write)
			{
				m_sampleCounter = 0;
				return writeHeader();
			}
			else if (mode == File::AccessMode::read)
			{
				if (!readHeader())
				{
					VMB_LOGLN("Failed to read WAV header from file: " + m_file.getPath());
					return false;
				}
			}
			else
			{
				VMB_LOGLN("Unknown file access mode: " + std::to_string((int)mode));
				return false;
			}
			return true;
		}
		return false;
	}

	bool WAVFile::close()
	{
		if (m_file.getAccessMode() == File::AccessMode::write ||
			m_file.getAccessMode() == File::AccessMode::append)
		{
			m_file.seek(0);
			writeHeader(); // Update the header with the correct sample count
		}
		else if (m_file.getAccessMode() == File::AccessMode::read)
		{

		}
		else
			VMB_LOGLN("Failed to close file, file is not open: " + m_file.getPath());
		return m_file.close();
	}

	uint32_t WAVFile::writeAudioSamples(const volatile int16_t* data, uint32_t size)
	{
		if (!m_file.isOpen())
		{
			VMB_LOGLN("Failed to write audio samples, file is not open: " + m_file.getPath());
			return 0;
		}
		if (m_file.getAccessMode() != File::AccessMode::write)
		{
			VMB_LOGLN("Failed to write audio samples, file is not opened in write mode: " + m_file.getPath());
			return 0;
		}
		uint32_t written = m_file.write((uint8_t*)data, size * sizeof(int16_t) * m_numChannels);
		m_sampleCounter += size; // Left and right channel are 2x 16 bit samples which counts as one audio sample
		return written;
	}
	uint32_t WAVFile::readAudioSamples(volatile int16_t* data, uint32_t size)
	{
		if (!m_file.isOpen())
		{
			VMB_LOGLN("Failed to write audio samples, file is not open: " + m_file.getPath());
			return 0;
		}
		if (m_file.getAccessMode() != File::AccessMode::read)
		{
			VMB_LOGLN("Failed to read audio samples, file is not opened in read mode: " + m_file.getPath());
			return 0;
		}
		if(m_sampleCounter == 0)
		{
			VMB_LOGLN("No more audio samples to read");
			return 0;
		}
		uint32_t read = m_file.read((uint8_t*)data, size * sizeof(int16_t) * m_numChannels);
		if (m_sampleCounter - size > m_sampleCounter) // Overflow check
		{
			memset((int16_t*)data + size * m_numChannels - m_sampleCounter * 2, 0, 2 * m_sampleCounter * sizeof(int16_t)); // Clear the remaining samples
			m_sampleCounter = 0;
		}
		else
		{
			m_sampleCounter -= size / 2; // Left and right channel are 2x 16 bit samples which counts as one audio sample
		}
		
		return read;
	}

	bool WAVFile::writeHeader()
	{
		if (m_file.getAccessMode() != File::AccessMode::write)
		{
			VMB_LOGLN("Failed to write file header, file is not opened in write mode: " + m_file.getPath());
			return false;
		}
		uint32_t byte_rate = m_sampleRate * m_numChannels * (m_bitsPerSample / 8);
		uint16_t block_align = m_numChannels * (m_bitsPerSample / 8);
		uint32_t data_chunk_size = m_sampleCounter * block_align;
		uint32_t riff_chunk_size = 36 + data_chunk_size;

		//m_sampleRate /= m_numChannels;

		uint8_t header[44];

		memcpy(header, "RIFF", 4);
		header[4] = (uint8_t)(riff_chunk_size & 0xFF);
		header[5] = (uint8_t)((riff_chunk_size >> 8) & 0xFF);
		header[6] = (uint8_t)((riff_chunk_size >> 16) & 0xFF);
		header[7] = (uint8_t)((riff_chunk_size >> 24) & 0xFF);
		memcpy(header + 8, "WAVEfmt ", 8);

		header[16] = 16;  // PCM header size
		header[17] = 0; header[18] = 0; header[19] = 0;

		header[20] = 1;  // Audio format = PCM
		header[21] = 0;

		header[22] = (uint8_t)(m_numChannels & 0xFF);
		header[23] = (uint8_t)((m_numChannels >> 8) & 0xFF);

		header[24] = (uint8_t)(m_sampleRate & 0xFF);
		header[25] = (uint8_t)((m_sampleRate >> 8) & 0xFF);
		header[26] = (uint8_t)((m_sampleRate >> 16) & 0xFF);
		header[27] = (uint8_t)((m_sampleRate >> 24) & 0xFF);

		header[28] = (uint8_t)(byte_rate & 0xFF);
		header[29] = (uint8_t)((byte_rate >> 8) & 0xFF);
		header[30] = (uint8_t)((byte_rate >> 16) & 0xFF);
		header[31] = (uint8_t)((byte_rate >> 24) & 0xFF);

		header[32] = (uint8_t)(block_align & 0xFF);
		header[33] = (uint8_t)((block_align >> 8) & 0xFF);

		header[34] = (uint8_t)(m_bitsPerSample & 0xFF);
		header[35] = (uint8_t)((m_bitsPerSample >> 8) & 0xFF);

		memcpy(header + 36, "data", 4);
		header[40] = (uint8_t)(data_chunk_size & 0xFF);
		header[41] = (uint8_t)((data_chunk_size >> 8) & 0xFF);
		header[42] = (uint8_t)((data_chunk_size >> 16) & 0xFF);
		header[43] = (uint8_t)((data_chunk_size >> 24) & 0xFF);
		if (m_file.write(header, sizeof(header)) != sizeof(header))
		{
			VMB_LOGLN("Failed to write WAV header to file: " + m_file.getPath());
			return false;
		}
		return true;
	}
	bool WAVFile::readHeader()
	{
		if (m_file.getAccessMode() != File::AccessMode::read)
		{
			VMB_LOGLN("Failed to read file header, file is not opened in read mode: " + m_file.getPath());
			return false;
		}
		uint8_t header[44];
		if (m_file.read(header, sizeof(header)) != sizeof(header))
		{
			VMB_LOGLN("Failed to read WAV header from file: " + m_file.getPath());
			return false;
		}
		if (memcmp(header, "RIFF", 4) != 0)
		{
			VMB_LOGLN("Invalid WAV file: " + m_file.getPath());
			return false;
		}
		uint32_t riff_chunk_size = 
			  (uint32_t)header[4] |
			(((uint32_t)header[5]) << 8) | 
			(((uint32_t)header[6]) << 16) | 
			(((uint32_t)header[7]) << 24);

		if (memcmp(header + 8, "WAVEfmt ", 8) != 0)
		{
			VMB_LOGLN("Invalid WAV file format: " + m_file.getPath());
			return false;
		}

		uint16_t audio_format = header[20] | (((uint32_t)header[21]) << 8);

		if (audio_format != 1)
		{
			VMB_LOGLN("Unsupported audio format: " + std::to_string(audio_format));
			return false;
		}

		m_numChannels = 
			  (uint32_t)header[22] |
			(((uint32_t)header[23]) << 8);

		m_sampleRate =
			  (uint32_t)header[24] |
			(((uint32_t)header[25]) << 8) |
			(((uint32_t)header[26]) << 16) |
			(((uint32_t)header[27]) << 24);

		//uint32_t byte_rate =
		//	  (uint32_t)header[28] |
		//	(((uint32_t)header[29]) << 8) |
		//	(((uint32_t)header[30]) << 16) |
		//	(((uint32_t)header[31]) << 24);

		uint16_t block_align =
			  (uint32_t)header[32] |
			(((uint32_t)header[33]) << 8);

		m_bitsPerSample =
		      (uint32_t)header[34] |
			(((uint32_t)header[35]) << 8);

		if (memcmp(header + 36, "data", 4) != 0)
		{
			VMB_LOGLN("Invalid WAV data chunk: " + m_file.getPath());
			return false;
		}
		uint32_t data_chunk_size =
			(uint32_t)header[40] |
			(((uint32_t)header[41]) << 8) |
			(((uint32_t)header[42]) << 16) |
			(((uint32_t)header[43]) << 24);

		if (data_chunk_size != (riff_chunk_size - 36))
		{
			VMB_LOGLN("Invalid WAV data chunk size: " + std::to_string(data_chunk_size));
			return false;
		}
		if (m_numChannels != 1 && m_numChannels != 2)
		{
			VMB_LOGLN("Unsupported number of channels: " + std::to_string(m_numChannels));
			return false;
		}

		if (m_bitsPerSample != 8 && m_bitsPerSample != 16)
		{
			VMB_LOGLN("Unsupported bits per sample: " + std::to_string(m_bitsPerSample));
			return false;
		}

		if (m_sampleRate != 8000 &&
			m_sampleRate != 16000 &&
			m_sampleRate != 44100 &&
			m_sampleRate != 48000)
		{
			VMB_LOGLN("Unsupported sample rate: " + std::to_string(m_sampleRate));
			return false;
		}

		m_sampleCounter = data_chunk_size / block_align;
		return true;
	}
}
