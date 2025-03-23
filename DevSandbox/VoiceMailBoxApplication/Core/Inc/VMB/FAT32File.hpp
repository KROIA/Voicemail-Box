/*
 * FAT32File.hpp
 *
 *  Created on: Mar 19, 2025
 *      Author: Alex
 */

#ifndef FAT32FILE_HPP_
#define FAT32FILE_HPP_

#include "IFile.hpp"
#include "stdint.h"
#include "fatfs.h"
#include <string>
#include <vector>

namespace VMB
{
	class FAT32File : public IFile
	{
	public:


		FAT32File();
		~FAT32File();

		bool open(const char* path, AccessMode mode) override;
		bool open(const char* path, int fa_mode) override;
		bool close();

		unsigned int write(const char* text) override;
		unsigned int read(char* buffer, unsigned int length) override;
		bool seek(unsigned int position) override;
		unsigned int getSize() const override;
		bool isOpen() const override { return m_isOpen; }
		bool flush() override;
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
#endif /* FAT32FILE_HPP_ */
