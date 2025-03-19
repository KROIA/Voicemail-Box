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
	//FATFS FAT32File::s_SDFatFS;
    //char FAT32File::s_SDPath[4] = "0:/";
    uint8_t FAT32File::s_rtext[_MAX_SS];

	FAT32File::FAT32File()
	{
		if(!s_isMounted)
		{
			FRESULT res =  f_mount(&SDFatFS, (TCHAR const*)SDPath, 0);
			if(res == FRESULT::FR_OK)
			{
				//res = f_mkfs((TCHAR const*)s_SDPath, FM_ANY, 0, s_rtext, sizeof(s_rtext));
				//if(res == FRESULT::FR_OK)
				//{
					s_isMounted = true;
				//}
			}
			else
			{

			}
		}
	}
	FAT32File::~FAT32File()
	{

	}

	bool FAT32File::open(const char* path, AccessMode mode)
	{
		switch(mode)
		{
			case AccessMode::read:
			{
				return f_open(&m_fileHandle, path, FA_READ) == FRESULT::FR_OK;
			}
			case AccessMode::write:
			{
				return f_open(&m_fileHandle, path, FA_CREATE_ALWAYS | FA_WRITE) == FRESULT::FR_OK;
			}
			case AccessMode::append:
			{
				return f_open(&m_fileHandle, path, FA_OPEN_APPEND | FA_WRITE) == FRESULT::FR_OK;
			}
		}
		return false;
	}

	bool FAT32File::close()
	{
		return f_close(&m_fileHandle) == FRESULT::FR_OK;
	}

	unsigned int FAT32File::write(const char* text)
	{
		size_t len = strlen(text);
		UINT bytesWritten = 0;
		FRESULT res = f_write(&m_fileHandle, text, len, &bytesWritten);
		return bytesWritten;
	}

}
