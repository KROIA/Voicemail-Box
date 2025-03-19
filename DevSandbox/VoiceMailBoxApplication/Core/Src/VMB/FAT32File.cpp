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
    ///char FAT32File::s_SDPath[4] = "0:/";
    uint8_t FAT32File::s_rtext[_MAX_SS];

	FAT32File::FAT32File()
    	: m_fileHandle{ 0 }
		, m_isOpen(false)
		, m_currentMode(AccessMode::read)
		, m_path("")
	{
		if(!s_isMounted)
		{
			FRESULT res =  f_mount(&s_SDFatFS, (TCHAR const*)SDPath, 0);
			if(res == FRESULT::FR_OK)
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
		bool success = false;
		switch(mode)
		{
			case AccessMode::read:
			{
				success = f_open(&m_fileHandle, path, FA_READ) == FRESULT::FR_OK;
			}
			case AccessMode::write:
			{
				success = f_open(&m_fileHandle, path, FA_CREATE_ALWAYS | FA_WRITE) == FRESULT::FR_OK;
			}
			case AccessMode::append:
			{
				success = f_open(&m_fileHandle, path, FA_OPEN_APPEND | FA_WRITE) == FRESULT::FR_OK;
			}

			default:
			{
				// Unknown mode
				return false;
			}
		}


		if(success)
		{
			m_currentMode = mode;
			m_path = std::move(std::string(path));
		}
		m_isOpen = success;
		return success;
	}

	bool FAT32File::close()
	{
		m_path.clear();
		m_isOpen = false;
		return f_close(&m_fileHandle) == FRESULT::FR_OK;
	}

	unsigned int FAT32File::write(const char* text)
	{
		if(!m_isOpen)
		{
			// File is not open
			return 0;
		}
		size_t len = strlen(text);
		UINT bytesWritten = 0;
		FRESULT res = f_write(&m_fileHandle, text, len, &bytesWritten);
		return bytesWritten;
	}

}
