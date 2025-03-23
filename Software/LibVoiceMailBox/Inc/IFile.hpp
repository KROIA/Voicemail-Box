/*
 * IFile.hpp
 *
 *  Created on: Mar 19, 2025
 *      Author: Alex
 */

#ifndef IFILE_HPP_
#define IFILE_HPP_

#include <string>

namespace VMB
{
	class IFile
	{
	public:
		enum class AccessMode
		{
			read,
			write,
			append,
		};

		virtual ~IFile() = default;

		virtual bool open(const char* path, AccessMode mode) = 0;
		virtual bool open(const char* path, int fa_mode) = 0;
		virtual bool close() = 0;

		virtual unsigned int write(const char* text) = 0;
		unsigned int write(const std::string& text)
		{
			return write(text.c_str());
		}
		virtual unsigned int read(char* buffer, unsigned int length) = 0;
		unsigned int read(std::string& output, unsigned int length)
		{
			output.resize(length);
			return read(&output[0], length);
		}

		virtual bool seek(unsigned int position) = 0;
		virtual unsigned int getSize() const = 0;
		virtual bool isOpen() const = 0;
		virtual bool flush() = 0;
	};
}
#endif /* IFILE_HPP_ */
