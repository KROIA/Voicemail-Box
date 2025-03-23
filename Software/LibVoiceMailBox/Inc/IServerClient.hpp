/*
 * IServerClient.hpp
 *
 *  Created on: Mar 19, 2025
 *      Author: Alex
 */

#ifndef ISERVERCLIENT_HPP_
#define ISERVERCLIENT_HPP_

#include <string>

namespace VMB
{
	class IServerClient
	{
	public:
		virtual ~IServerClient() = default;

		virtual bool connect(const char* ip, unsigned short port) = 0;
		virtual bool disconnect() = 0;

		virtual bool send(const char* data, unsigned int length) = 0;
		bool send(const std::string& data)
		{
			return send(data.c_str(), data.size());
		}
		virtual unsigned int receive(char* buffer, unsigned int length) = 0;
		unsigned int receive(std::string& output, unsigned int length)
		{
			output.resize(length);
			return receive(&output[0], length);
		}

		virtual bool isConnected() const = 0;
		virtual bool flush() = 0;
	};
}
#endif /* ISERVERCLIENT_HPP_ */
