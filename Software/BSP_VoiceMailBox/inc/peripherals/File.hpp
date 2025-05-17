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
		bool open(const char* path, AccessMode mode);

		/**
		 * @brief Try's to open a file with the given path and mode.
		 * @param path where the file is located
		 * @param mode how to access the file
		 * @return true if the file was opened successfully, otherwise false
		 */
		bool open(const char* path, int fa_mode);

		/**
		 * @brief Closes the open file.
		 * @return true if the file was closed successfully, otherwise false
		 */
		bool close();

		/**
		 * @brief Writes the given string to the file
		 * @param text to write to the file. Expecting a null-terminated string.
		 * @return The amount of bytes to write
		 */
		unsigned int write(const char* text);

		/**
		 * @brief Writes the given data to the file
		 * @param data to be saved to the file
		 * @param size The amount of bytes to write
		 * @return The amount of bytes written
		 */
		unsigned int write(const uint8_t* data, uint32_t size);

		/**
		 * @brief Writes the given string to the file
		 * @param text to write to the file.
		 * @return The amount of bytes written
		 */
		unsigned int write(const std::string& text)
		{
			return write(text.c_str());
		}

		/**
		 * @brief Reads the given amount of bytes from the file
		 * @param buffer to store the read bytes
		 * @param length amount of bytes to be read
		 * @return The amount of bytes read
		 */
		unsigned int read(char* buffer, uint32_t length);

		/**
		 * @brief Reads the given amount of bytes from the file
		 * @param output to store the read bytes
		 * @param length amount of bytes to be read
		 * @return The amount of bytes read
		 */
		unsigned int read(std::string& output, uint32_t length);

		/**
		 * @brief Sets the cursor to the given location
		 * @param position to set the cursor to
		 * @return true if the cursor was set successfully, otherwise false
		 */
		bool seek(unsigned int position);

		/**
		 * @brief Gets the filesize in bytes
		 * @return filesize in bytes
		 */
		unsigned int getSize() const;

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
		 * @brief Removes the file at the given path
		 * @param path to the file to be removed
		 * @return true if the file was removed successfully, otherwise false
		 */
		static bool remove(const char* path);

		/**
		 * @brief Renames the file at the given path
		 * @param oldPath to the file to be renamed
		 * @param newPath to the new name of the file
		 * @return true if the file was renamed successfully, otherwise false
		 */
		static bool rename(const char* oldPath, const char* newPath);

		/**
		 * @brief Checks if the file at the given path exists
		 * @param path to the file to be checked
		 * @return true if the file exists, otherwise false
		 */
		static bool exists(const char* path);

		/**
		 * @brief Gets a list of file names in the given directory
		 * @param path to the directory to be listed
		 * @return A vector of file names in the given directory
		 */
		static std::vector<std::string> listDirectory(const char* path);

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
