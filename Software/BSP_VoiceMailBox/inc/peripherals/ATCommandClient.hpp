#ifndef ATCOMMAND_CLIENT_H
#define ATCOMMAND_CLIENT_H

#include "HAL_abstraction.hpp"
#include "uart.hpp"
#include "File.hpp"
#include <string>

namespace VoiceMailBox
{
	class ATCommandClient
	{
	public:
		ATCommandClient(VMB_UART_Handle* uartHandle, uint16_t uartBufferSize);
		~ATCommandClient();

		void setup();


		/**
		 * @brief Sends a command to the AT command client.
		 *		  The command must not include the terminating CRLF.
		 * @param command 
		 */
		bool sendCommand(const std::string &command);
		bool sendCommand(const char* command);
		bool sendBytes(const uint8_t* data, uint16_t size);

		bool waitUntil(const char* response, uint32_t timeout = 5000);

		bool hasResponse() const
		{
			return m_uart.hasBytesReceived() > 0;
		}

		bool getResponse(uint8_t* data, uint16_t size)
		{
			return m_uart.receive(data, size);
		}
		


		bool doesRespond();


		bool connectToWifi(const std::string& ssid, const std::string& password);
		bool sendFileToServer(const std::string& localFileName, const std::string& urlPath, const std::string& serverIP, uint16_t serverPort);
		bool downloadFileFromServer(const std::string& localFileName, const std::string& urlPath, const std::string& serverIP, uint16_t serverPort);


		

	private:
		bool readFileDownloadResponse(File &file, std::string& response, uint32_t timeout);
		bool convertToUInt16(const std::string& str, uint16_t& outValue);
		void log(const std::string &msg);

		UART m_uart;
		bool m_enableLogging = true;

	};
}
#endif
