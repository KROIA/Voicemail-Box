#include "WiFiServerClient.hpp"
#include "stdio.h"
#include "string.h"


namespace VMB
{
	#define ESP_TIMEOUT 2000         // Timeout in milliseconds
	#define ESP_RESPONSE_SIZE 128    // Buffer size for response

	std::array<WiFiServerClient*, 10> WiFiServerClient::s_instances;

	WiFiServerClient::WiFiServerClient(UART_HandleTypeDef& huartInterface)
		: IServerClient()
		, m_huartInterface(huartInterface)
	{
		for (size_t i = 0; i < s_instances.size(); ++i)
		{
			if (s_instances[i] == nullptr)
			{
				s_instances[i] = this;
				break;
			}
			if (i == s_instances.size() - 1)
			{
				printf("All instances are used!\n\r");
				return;
			}
		}

		HAL_UARTEx_ReceiveToIdle_DMA(&m_huartInterface, m_rxBuff[0], sizeof(m_rxBuff[0]));
		m_rx_data.buff = NULL;
		m_rx_data.dataReceived = false;
		m_rx_data.size = 0;

		if (sendATCommand("ATE0")) {
			printf("ESP32 is responsive.\n\r");
		}
		else {
			printf("ESP32 is not responding!\n\r");
			return;
		}
		HAL_Delay(10);
		if (sendATCommand("AT+CWMODE=2")) {
			printf("WiFi mode set to AP.\n\r");
		}
		else {
			printf("Failed to set WiFi mode.\n\r");
		}
		HAL_Delay(10);
		if (sendATCommand("AT+CWSAP=\"MyHotspot\",\"MyPassword\",5,3")) {
			printf("Hotspot created successfully.\n\r");
		}
		else {
			printf("Failed to create hotspot.\n\r");
		}
		HAL_Delay(10);
		if (sendATCommand("AT+CWDHCP=1,1")) {
			printf("DHCP server enabled.\n\r");
		}
		else {
			printf("Failed to enable DHCP.\n\r");
		}
		HAL_Delay(10);
		if (sendATCommand("AT+CWLIF")) {
			printf("Checking connected clients...\n\r");
		}
	}
	WiFiServerClient::~WiFiServerClient()
	{
		for (size_t i = 0; i < s_instances.size(); ++i)
		{
			if (s_instances[i] == this)
			{
				s_instances[i] = nullptr;
				break;
			}
		}
	}

	bool WiFiServerClient::connect()
	{
		return false;
	}
	bool WiFiServerClient::disconnect()
	{
		return false;
	}
	bool WiFiServerClient::send(const char* data, unsigned int length)
	{
		return false;
	}
	unsigned int WiFiServerClient::receive(char* buffer, unsigned int length)
	{
		return 0;
	}

	void WiFiServerClient::on_HAL_UARTEx_RxEventCallback(UART_HandleTypeDef* huart, uint16_t size)
	{
		WiFiServerClient* instance = nullptr;
		for (size_t i = 0; i < s_instances.size(); ++i)
		{
			if (s_instances[i] != nullptr && &s_instances[i]->m_huartInterface == huart)
			{
				instance = s_instances[i];
				break;
			}
		}
		if (!instance)
			return;
		uint8_t* nextBuff = instance->m_rxBuff[instance->buffSwitcher];
		instance->buffSwitcher = !instance->buffSwitcher;

		HAL_UARTEx_ReceiveToIdle_DMA(&instance->m_huartInterface, nextBuff, sizeof(instance->m_rxBuff[0]));
		instance->m_rx_data.buff = instance->m_rxBuff[instance->buffSwitcher];
		instance->m_rx_data.size = size;
		instance->m_rx_data.dataReceived = true;
	}

	int WiFiServerClient::sendATCommand(const char* command)
	{
		//char response[ESP_RESPONSE_SIZE] = {0}; // Buffer for ESP32 response
		uint8_t txBuffer[ESP_RESPONSE_SIZE] = { 0 };
		int index = 0;
		uint32_t startTime = HAL_GetTick(); // Start timer

		// Copy the AT command into the buffer and append "\r\n"
		snprintf((char*)txBuffer, ESP_RESPONSE_SIZE, "%s\r\n", command);

		HAL_StatusTypeDef result = HAL_UART_Transmit_DMA(&m_huartInterface, txBuffer, strlen((char*)txBuffer));

		while ((HAL_GetTick() - startTime) < 1000 * 60 * 5)
		{
			if (m_rx_data.dataReceived)
			{
				m_rx_data.dataReceived = false;
				// Check if response contains "OK" or "ERROR"
				if (strstr((const char*)m_rx_data.buff, "OK"))
				{
					return 1; // Success
				}
				else if (strstr((const char*)m_rx_data.buff, "ERROR"))
				{
					return 0; // Failure
				}
			}
		}
		return 0;
	}
}
