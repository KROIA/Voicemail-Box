#ifndef FILE_HPP
#define FILE_HPP

#include <stdint.h>
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

		File();
		~File();

		bool open(const char* path, AccessMode mode);
		bool open(const char* path, int fa_mode);
		bool close();

		unsigned int write(const char* text);
		unsigned int write(const char* text, uint16_t size);
		unsigned int write(const std::string& text)
		{
			return write(text.c_str());
		}
		unsigned int read(char* buffer, unsigned int length);
		unsigned int read(std::string& output, unsigned int length)
		{
			output.resize(length);
			return read(&output[0], length);
		}

		bool seek(unsigned int position);
		unsigned int getSize() const;
		bool isOpen() const { return m_isOpen; }
		bool flush();


		FRESULT getLastError() const { return m_lastError; }



		static bool remove(const char* path);
		static bool rename(const char* oldPath, const char* newPath);
		static bool exists(const char* path);
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
