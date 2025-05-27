#ifndef WAV_FILE_HPP
#define WAV_FILE_HPP
/**
 * @brief
 * @details
 *
 * @author Alex Krieg
 */

#include "HAL_abstraction.hpp"
#include "Logger.hpp"
#include "File.hpp"
#include <stdint.h>
#include <string>

#if defined(VMB_AUDIO_FORMAT_WAV)
namespace VoiceMailBox
{
	class WAVFile  
#ifdef VMB_USE_LOGGER_OBJECTS
		: public Logger
#endif
	{
	public:
		WAVFile();
		~WAVFile();

		void setSampleRate(uint32_t sampleRate) { m_sampleRate = sampleRate; }
		void setNumChannels(uint16_t numChannels) { m_numChannels = numChannels; }
		void setBitsPerSample(uint16_t bitsPerSample) { m_bitsPerSample = bitsPerSample; }

		bool open(const std::string& filePath, File::AccessMode mode);
		bool close();
		std::string getPath() const { return m_file.getPath(); }

		uint32_t writeAudioSamples(const volatile int16_t* data, uint32_t size);
		uint32_t readAudioSamples(volatile int16_t* data, uint32_t size);



		/**
		 * @brief Sets the cursor to the given location
		 * @param position to set the cursor to
		 * @return true if the cursor was set successfully, otherwise false
		 */
		bool seek(uint32_t position) { return m_file.seek(position); }

		/**
		 * @brief Gets the current curser position
		 * @return index of the cursor position
		 */
		uint32_t getCursorPosition() const { return m_file.getCursorPosition(); }

		/**
		 * @brief Gets the filesize in bytes
		 * @return filesize in bytes
		 */
		uint32_t getSize() const { return m_file.getSize(); }

		/**
		 * @return true if the file is open, otherwise false
		 */
		bool isOpen() const { return m_file.isOpen(); }

		/**
		 * @brief Flushes the file
		 * @return true if the file was flushed successfully, otherwise false
		 */
		bool flush() { return m_file.flush(); }

		/**
		 * @brief Checks if the end of the file is reached
		 * @return true if the end of the file is reached, otherwise false
		 */
		bool eof() const { return m_file.eof(); }

		/**
		 * @brief Gets the last error
		 * @return The last occured error
		 */
		FRESULT getLastError() const { return m_file.getLastError(); }

		/**
		 * @brief Clears the last error
		 */
		void clearLastError() { m_file.clearLastError(); }

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
#endif // defined(VMB_AUDIO_FORMAT_WAV)
#endif // WAV_FILE_HPP