/*
 * WiFiServerClient.hpp
 *
 *  Created on: Mar 23, 2025
 *      Author: Alex
 */

#ifndef WIFI_SERVER_CLIENT_HPP_
#define WIFI_SERVER_CLIENT_HPP_

#include "IServerClient.hpp"
#include "stm32f4xx_hal.h"


namespace VMB
{
	class WiFiServerClient : public IServerClient
	{
	public:
		WiFiServerClient(UART_HandleTypeDef &huartInterface);
		~WiFiServerClient();

		bool connect() override;
		bool disconnect() override;
		bool send(const char* data, unsigned int length) override;
		bool receive(char* buffer, unsigned int length) override;
		bool isConnected() const override { return m_isConnected; }

	private:
		bool m_isConnected;
		UART_HandleTypeDef& m_huartInterface;
	};
}

#endif /* WIFI_SERVER_CLIENT_HPP_ */