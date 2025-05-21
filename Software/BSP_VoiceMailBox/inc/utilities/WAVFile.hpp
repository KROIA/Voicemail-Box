#ifndef WAV_FILE_HPP
#define WAV_FILE_HPP
/**
 * @brief
 * @details
 *
 * @author Alex Krieg
 */

#include "settings.h"
#include "Logger.hpp"
#include "HAL_abstraction.hpp"
#include "File.hpp"
#include <stdint.h>
#include <string>

namespace VoiceMailBox
{
	class WAVFile : public Logger
	{
	public:
		WAVFile();
		~WAVFile();

		void setSampleRate(uint32_t sampleRate) { m_sampleRate = sampleRate; }
		void setNumChannels(uint16_t numChannels) { m_numChannels = numChannels; }
		void setBitsPerSample(uint16_t bitsPerSample) { m_bitsPerSample = bitsPerSample; }

		bool open(const std::string& filePath, File::AccessMode mode);
		bool close();
		bool isOpen() const { return m_file.isOpen(); }
		std::string getPath() const { return m_file.getPath(); }

		uint32_t writeAudioSamples(const volatile int16_t* data, uint32_t size);
		uint32_t readAudioSamples(volatile int16_t* data, uint32_t size);

	private:
		bool writeHeader();
		bool readHeader();

		File m_file;
		uint32_t m_sampleCounter;

		uint32_t m_sampleRate = 16000; // Default sample rate
		uint16_t m_numChannels = 1;    // Default number of channels
		uint16_t m_bitsPerSample = 16; // Default bits per sample
	};
}
#endif