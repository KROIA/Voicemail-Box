#include "ATCommandClient.hpp"
#include "HAL_abstraction.hpp"
#include <string>
#include <cstring>

namespace VoiceMailBox
{
	ATCommandClient::ATCommandClient(void* uartHandle, uint16_t uartBufferSize)
		: m_uart(uartHandle, uartBufferSize)
	{

	}

	ATCommandClient::~ATCommandClient()
	{
	}

	void ATCommandClient::setup()
	{
		// Setup the UART for AT command client
		m_uart.setup();

	}


	void ATCommandClient::sendCommand(const char* command)
	{
		m_uart.flush();
		m_uart.send((uint8_t*)command, strlen(command));
		m_uart.send((uint8_t*)("\r\n"), 2);
		uint32_t currentTick = VMB_HAL_GetTickCount();
		uint32_t timeout = currentTick + 1000; // 1 second timeout
		while (m_uart.isSending() && VMB_HAL_GetTickCount() < timeout)
		{
			VMB_HAL_Delay(1); // Wait for the UART to finish sending
		}
	}

	bool ATCommandClient::doesRespond()
	{
		sendCommand("AT");
		// Wait for a short period to allow the AT command client to respond
		VMB_HAL_Delay(5);
		uint16_t size = m_uart.hasBytesReceived();
		if (size > 0)
		{
			uint8_t data[64];
			m_uart.receive(data, size);
			// Check if the response contains "OK"
			if (strstr((const char*)data, "OK") != nullptr)
			{
				return true;
			}
		}
		else
		{
			// No response received
			return false;
		}

		// Check if the AT command client has responded
		return m_uart.hasBytesReceived() > 0;
	}
}
