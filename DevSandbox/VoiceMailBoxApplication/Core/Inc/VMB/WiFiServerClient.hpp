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
#include <array>


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
		unsigned int receive(char* buffer, unsigned int length) override;
		bool isConnected() const override { return m_isConnected; }

		static void on_HAL_UARTEx_RxEventCallback(UART_HandleTypeDef* huart, uint16_t size);

	private:
		typedef struct {
			uint8_t* buff;
			bool dataReceived;
			uint16_t size;
		} RX_Data;

		int sendATCommand(const char* command);

		static std::array<WiFiServerClient*, 10> s_instances;

		bool m_isConnected;
		UART_HandleTypeDef& m_huartInterface;
		bool buffSwitcher = true;
		uint8_t m_rxBuff[2][1024];
		volatile RX_Data m_rx_data;
	};
}

#endif /* WIFI_SERVER_CLIENT_HPP_ */
