/*
 * IFile.hpp
 *
 *  Created on: Mar 19, 2025
 *      Author: Alex
 */

#ifndef IFILE_HPP_
#define IFILE_HPP_


namespace VMB
{
	class IFile
	{
	public:
		enum AccessMode
		{
			read,
			write,
			append,
		};

		virtual ~IFile() = default;


	};
}
#endif /* IFILE_HPP_ */
