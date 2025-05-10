#ifndef ATCOMMAND_CLIENT_H
#define ATCOMMAND_CLIENT_H

#include <stdint.h>
#include "uart.hpp"

namespace VoiceMailBox
{
	class ATCommandClient
	{
	public:
		ATCommandClient(void* uartHandle, uint16_t uartBufferSize);
		~ATCommandClient();

		void setup();


		/**
		 * @brief Sends a command to the AT command client.
		 *		  The command must not include the terminating CRLF.
		 * @param command 
		 */
		void sendCommand(const char* command);

		bool hasResponse() const
		{
			return m_uart.hasBytesReceived() > 0;
		}

		bool getResponse(uint8_t* data, uint16_t size)
		{
			return m_uart.receive(data, size);
		}


		bool doesRespond();

	private:
		UART m_uart;

	};
}
#endif
