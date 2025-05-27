#include "utilities/File.hpp"
#include <cstring>

namespace VoiceMailBox
{
	bool File::s_isMounted = false;
	FATFS File::s_SDFatFS;
	uint8_t File::s_rtext[_MAX_SS];

	File::File()
		: m_fileHandle{ 0 }
		, m_isOpen(false)
		, m_currentMode(FA_READ)
		, m_path("")
		, m_lastError(FRESULT::FR_OK)
	{
		if (!s_isMounted)
		{
			m_lastError = f_mount(&s_SDFatFS, (TCHAR const*)VMB_VAR_NAME_SDPATH, 0);
			if (m_lastError == FRESULT::FR_OK)
				s_isMounted = true;
			else
			{
				// Can't mount device
			}
		}
	}
	File::~File()
	{
		close();
	}

	bool File::open(const std::string& path, AccessMode mode)
	{
		if (m_isOpen)
		{
			// Already open
			return false;
		}
		switch (mode)
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
	bool File::open(const std::string& path, int fa_mode)
	{
		if (m_isOpen)
		{
			// Already open
			return false;
		}
		m_lastError = f_open(&m_fileHandle, path.c_str(), fa_mode);
		if (m_lastError == FR_OK) {
			m_isOpen = true;
			m_path = path;
			m_currentMode = fa_mode;
			return true;
		}
		m_isOpen = false;
		return false;
	}

	bool File::close()
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

	uint32_t File::write(const char* text) {
		if (!m_isOpen) return 0;
		UINT written;
		m_lastError = f_write(&m_fileHandle, text, strlen(text), &written);
		return written;
	}
	uint32_t File::write(const uint8_t* data, uint32_t size) {
		if (!m_isOpen) return 0;
		UINT written;
		static constexpr size_t pageSize = 512; // Assuming a page size of 512 bytes

		if (size > pageSize)
		{
			uint16_t bytesToFillPage = pageSize - (m_fileHandle.fptr % pageSize); // bytes to fill the page
			uint8_t dataAlignment = (uint32_t)data % 4; // data alignment

			if (bytesToFillPage % 4 == dataAlignment)
			{
				m_lastError = f_write(&m_fileHandle, data, size, &written);
				return written;
			}
			else
			{
				// Force FATFS to use its own buffer instead of writing to the DMA from the string directly.
				// This is a workaround to prevent the alignment issue when using the DMA which otherwise leads to false file content. (multiple characters)
				UINT writtenSum = 0;
				static constexpr size_t subPageSize = pageSize / 2;
				for (uint32_t i = 0; i < size / subPageSize; ++i)
				{
					m_lastError = f_write(&m_fileHandle, data + i * subPageSize, subPageSize, &written);
					writtenSum += written;
				}
				m_lastError = f_write(&m_fileHandle, data + (size / subPageSize) * subPageSize, size % subPageSize, &written);
				writtenSum += written;
				return writtenSum;
			}
		}
		else
		{
			m_lastError = f_write(&m_fileHandle, data, size, &written);
			return written;
		}
	}
	uint32_t File::read(uint8_t* buffer, uint32_t length) {
		if (!m_isOpen) return 0;
		UINT bytesRead;
		m_lastError = f_read(&m_fileHandle, buffer, length, &bytesRead);
		return bytesRead;
	}
	uint32_t File::read(std::string& output, uint32_t length)
	{
		output.resize(length);
		return read((uint8_t*)&output[0], length);
	}
	bool File::seek(uint32_t position) {
		if (!m_isOpen) return false;
		m_lastError = f_lseek(&m_fileHandle, position);
		return m_lastError == FR_OK;
	}
	uint32_t File::getCursorPosition() const
	{
		if (!m_isOpen) return 0;
		return f_tell(&m_fileHandle);
	}

	uint32_t File::getSize() const {
		if (!m_isOpen) return 0;
		return f_size(&m_fileHandle);
	}
	bool File::flush() {
		if (!m_isOpen) return false;
		m_lastError = f_sync(&m_fileHandle);
		return m_lastError == FR_OK;
	}
	bool File::eof() const
	{
		if (!m_isOpen) return false;
		return f_eof(&m_fileHandle);
	}

	bool File::remove(const char* path) {
		return f_unlink(path) == FR_OK;
	}

	bool File::rename(const char* oldPath, const char* newPath) {
		return f_rename(oldPath, newPath) == FR_OK;
	}

	bool File::exists(const char* path) {
		FILINFO fileInfo;
		return f_stat(path, &fileInfo) == FR_OK;
	}

	std::vector<std::string> File::listDirectory(const char* path) {
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
