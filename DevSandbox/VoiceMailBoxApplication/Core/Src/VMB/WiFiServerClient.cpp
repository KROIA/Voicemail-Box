#include "WiFiServerClient.hpp"

namespace VMB
{
	WiFiServerClient::WiFiServerClient(UART_HandleTypeDef& huartInterface)
		: IServerClient()
		, m_huartInterface(huartInterface)
	{

	}
	WiFiServerClient::~WiFiServerClient()
	{

	}

	bool WiFiServerClient::connect()
	{

	}
	bool WiFiServerClient::disconnect()
	{

	}
	bool WiFiServerClient::send(const char* data, unsigned int length)
	{

	}
	bool WiFiServerClient::receive(char* buffer, unsigned int length)
	{

	}
}