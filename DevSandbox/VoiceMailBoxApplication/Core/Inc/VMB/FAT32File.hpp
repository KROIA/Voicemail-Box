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

namespace VMB
{
	class FAT32File : public IFile
	{
	public:


		FAT32File();
		~FAT32File();

		bool open(const char* path, AccessMode mode);
		bool close();

		unsigned int write(const char* text);
	private:
		FIL m_fileHandle;

		static bool s_isMounted;
		//static FATFS s_SDFatFS;
		//static char s_SDPath[4];
		static uint8_t s_rtext[_MAX_SS];
	};
}
#endif /* FAT32FILE_HPP_ */
