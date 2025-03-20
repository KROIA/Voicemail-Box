/*
 * FAT32File.cpp
 *
 *  Created on: Mar 19, 2025
 *      Author: Alex
 */


#include "VMB/FAT32File.hpp"
#include "string.h"

namespace VMB
{
	bool FAT32File::s_isMounted = false;
	FATFS FAT32File::s_SDFatFS;
    uint8_t FAT32File::s_rtext[_MAX_SS];

	FAT32File::FAT32File()
    	: m_fileHandle{ 0 }
		, m_isOpen(false)
		, m_currentMode(AccessMode::read)
		, m_path("")
		, m_lastError(FRESULT::FR_OK)
	{
		if(!s_isMounted)
		{
			m_lastError =  f_mount(&s_SDFatFS, (TCHAR const*)SDPath, 0);
			if(m_lastError == FRESULT::FR_OK)
				s_isMounted = true;
			else
			{
				// Can't mount device
			}
		}
	}
	FAT32File::~FAT32File()
	{

	}

	bool FAT32File::open(const char* path, AccessMode mode)
	{
		if(m_isOpen)
		{
			// Already open
			return false;
		}
		switch(mode)
		{
			case AccessMode::read:
			{
				return open(path, FA_READ);
			}
			case AccessMode::write:
			{
				return open(path, FA_WRITE | FA_CREATE_ALWAYS);
			}
			case AccessMode::append:
			{
				return open(path, FA_OPEN_APPEND | FA_WRITE);
			}

			default:
			{
				// Unknown mode
				return false;
			}
		}
		return false;
	}
	bool FAT32File::open(const char* path, int fa_mode)
	{
		if (m_isOpen)
		{
			// Already open
			return false;
		}
		m_lastError = f_open(&m_fileHandle, path, fa_mode);
		if (m_lastError == FR_OK) {
			m_isOpen = true;
			m_path = path;
			m_currentMode = fa_mode;
			return true;
		}
		m_isOpen = false;
		return false;
	}

	bool FAT32File::close()
	{
		if (!m_isOpen)
		{
			// File is not open
			return false;
		}
		m_path.clear();
		m_isOpen = false;
		m_lastError = f_close(&m_fileHandle);
		return m_lastError == FRESULT::FR_OK;
	}

	unsigned int FAT32File::write(const char* text) {
		if (!m_isOpen) return 0;
		UINT written;
		m_lastError = f_write(&m_fileHandle, text, strlen(text), &written);
		return written;
	}
	unsigned int FAT32File::read(char* buffer, unsigned int length) {
		if (!m_isOpen) return 0;
		UINT bytesRead;
		m_lastError = f_read(&m_fileHandle, buffer, length, &bytesRead);
		return bytesRead;
	}
	unsigned int FAT32File::read(std::string& output, unsigned int length) {
		output.resize(length);
		return read(&output[0], length);
	}

	bool FAT32File::seek(unsigned int position) {
		if (!m_isOpen) return false;
		m_lastError = f_lseek(&m_fileHandle, position);
		return m_lastError == FR_OK;
	}

	unsigned int FAT32File::getSize() const {
		if (!m_isOpen) return 0;
		return f_size(&m_fileHandle);
	}
	bool FAT32File::flush() {
		if (!m_isOpen) return false;
		m_lastError = f_sync(&m_fileHandle);
		return m_lastError == FR_OK;
	}

	bool FAT32File::remove(const char* path) {
		return f_unlink(path) == FR_OK;
	}

	bool FAT32File::rename(const char* oldPath, const char* newPath) {
		return f_rename(oldPath, newPath) == FR_OK;
	}

	bool FAT32File::exists(const char* path) {
		FILINFO fileInfo;
		return f_stat(path, &fileInfo) == FR_OK;
	}

	std::vector<std::string> FAT32File::listDirectory(const char* path) {
		std::vector<std::string> files;
		DIR dir;
		FILINFO fileInfo;
		if (f_opendir(&dir, path) == FR_OK) {
			while (f_readdir(&dir, &fileInfo) == FR_OK && fileInfo.fname[0] != 0) {
				files.emplace_back(fileInfo.fname);
			}
			f_closedir(&dir);
		}
		return files;
	}

	


}
