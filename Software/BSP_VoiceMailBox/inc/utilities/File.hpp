#ifndef FILE_HPP
#define FILE_HPP
/**
 * @brief File abstraction class
 * @details This class provides an interface to the FATFS file system of the STM32 microcontroller.
 *          It encapsulates the FATFS file handle inside the class and provides methods to read and write files.
 * @note On the first construction of a File object, the FATFS file system is mounted automatically.
 * @author Alex Krieg
 */


#include <string>
#include <vector>
#include "fatfs.h"
#include "HAL_abstraction.hpp"


namespace VoiceMailBox
{

	class File
	{
	public:
		enum class AccessMode
		{
			read,
			write,
			append,
		};

		static bool mount();

		/**
		 * @brief Constructor
		 */
		File();
		~File();

		/**
		 * @brief Try's to open a file with the given path and mode.
		 * @param path where the file is located
		 * @param mode how to access the file
		 * @return true if the file was opened successfully, otherwise false
		 */
		bool open(const std::string& path, AccessMode mode);

		/**
		 * @brief Try's to open a file with the given path and mode.
		 * @param path where the file is located
		 * @param mode how to access the file
		 * @return true if the file was opened successfully, otherwise false
		 */
		bool open(const std::string& path, int fa_mode);

		/**
		 * @brief Closes the open file.
		 * @return true if the file was closed successfully, otherwise false
		 */
		bool close();

		/**
		 * @brief Gets the current open file path
		 * @return path to the file
		 */
		const std::string& getPath() const { return m_path; }

		/**
		 * @brief Writes the given string to the file
		 * @param text to write to the file. Expecting a null-terminated string.
		 * @return The amount of bytes to write
		 */
		uint32_t write(const char* text);

		/**
		 * @brief Writes the given data to the file
		 * @param data to be saved to the file
		 * @param size The amount of bytes to write
		 * @return The amount of bytes written
		 */
		uint32_t write(const uint8_t* data, uint32_t size);
		uint32_t write(const char* data, uint32_t size) {
			return write((uint8_t*)data, size);
		}

		/**
		 * @brief Writes the given string to the file
		 * @param text to write to the file.
		 * @return The amount of bytes written
		 */
		uint32_t write(const std::string& text) {
			return write(text.c_str());
		}

		/**
		 * @brief Reads the given amount of bytes from the file
		 * @param buffer to store the read bytes
		 * @param length amount of bytes to be read
		 * @return The amount of bytes read
		 */
		uint32_t read(uint8_t* buffer, uint32_t length);
		uint32_t read(char* buffer, uint32_t length) {
			return read((uint8_t*)buffer, length);
		}

		/**
		 * @brief Reads the given amount of bytes from the file
		 * @param output to store the read bytes
		 * @param length amount of bytes to be read
		 * @return The amount of bytes read
		 */
		uint32_t read(std::string& output, uint32_t length);

		/**
		 * @brief Reads a string from the file until a newline character is encountered
		 * @return the read line as a string, ignoring the newline character
		 */
		std::string readLine();

		/**
		 * @brief Sets the cursor to the given location
		 * @param position to set the cursor to
		 * @return true if the cursor was set successfully, otherwise false
		 */
		bool seek(uint32_t position);


		/**
		 * @brief Gets the current curser position
		 * @return index of the cursor position
		 */
		uint32_t getCursorPosition() const;

		/**
		 * @brief Gets the filesize in bytes
		 * @return filesize in bytes
		 */
		uint32_t getSize() const;

		/**
		 * @return true if the file is open, otherwise false
		 */
		bool isOpen() const { return m_isOpen; }

		/**
		 * @brief Flushes the file
		 * @return true if the file was flushed successfully, otherwise false
		 */
		bool flush();

		/**
		 * @brief Checks if the end of the file is reached
		 * @return true if the end of the file is reached, otherwise false
		 */
		bool eof() const;

		/**
		 * @brief Gets the last error
		 * @return The last occured error
		 */
		FRESULT getLastError() const { return m_lastError; }

		/**
		 * @brief Clears the last error
		 */
		void clearLastError() { m_lastError = FRESULT::FR_OK; }


		/**
		 * @brief Gets the current access mode of the file
		 * @return access mode of the file
		 */
		AccessMode getAccessMode() const
		{
			if(m_currentMode & FA_READ)
				return AccessMode::read;
			if (m_currentMode & FA_WRITE)
				return AccessMode::write;
			if (m_currentMode & FA_OPEN_APPEND)
				return AccessMode::append;

			return AccessMode::read; // Default to read if no mode is set
		}


		/**
		 * @brief Removes the file at the given path
		 * @param path to the file to be removed
		 * @return true if the file was removed successfully, otherwise false
		 */
		static bool remove(const char* path);
		static bool remove(const std::string& path) {
			return remove(path.c_str());
		}

		/**
		 * @brief Renames the file at the given path
		 * @param oldPath to the file to be renamed
		 * @param newPath to the new name of the file
		 * @return true if the file was renamed successfully, otherwise false
		 */
		static bool rename(const char* oldPath, const char* newPath);
		static bool rename(const std::string& oldPath, const std::string& newPath) {
			return rename(oldPath.c_str(), newPath.c_str());
		}

		/**
		 * @brief Checks if the file at the given path exists
		 * @param path to the file to be checked
		 * @return true if the file exists, otherwise false
		 */
		static bool exists(const char* path);
		static bool exists(const std::string& path) {
			return exists(path.c_str());
		}

		/**
		 * @brief Gets a list of file names in the given directory
		 * @param path to the directory to be listed
		 * @return A vector of file names in the given directory
		 */
		static std::vector<std::string> listDirectory(const char* path);
		static std::vector<std::string> listDirectory(const std::string& path) {
			return listDirectory(path.c_str());
		}

	private:

		FIL m_fileHandle;
		bool m_isOpen;
		int m_currentMode;
		std::string m_path;
		FRESULT m_lastError;

		static bool s_isMounted;
		static FATFS s_SDFatFS;
		static uint8_t s_rtext[_MAX_SS];
	};
}
#endif
