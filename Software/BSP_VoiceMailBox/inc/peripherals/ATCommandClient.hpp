#ifndef ATCOMMAND_CLIENT_H
#define ATCOMMAND_CLIENT_H

#include "HAL_abstraction.hpp"
#include "peripherals/DigitalPin.hpp"
#include "uart.hpp"
#include "utilities/File.hpp"
#include "utilities/Logger.hpp"
#include <string>
#include <cstdlib>
#include <memory>
#include <cstddef>
#include <iostream>
#include <cassert>
#include <new>

namespace VoiceMailBox
{
	class ATCommandClient 
#ifdef VMB_USE_LOGGER_OBJECTS
		: public Logger
#endif
	{
	public:
		ATCommandClient(VMB_UART_Handle* uartHandle, uint16_t uartBufferSize);
		ATCommandClient(VMB_UART_Handle* uartHandle, uint16_t uartBufferSize, DigitalPin &trafficLed);
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
		bool waitUntilAndFlush(const char* response, uint32_t timeout = 5000);
		void flushRX();
		uint32_t flushNBytes(uint32_t nBytes);

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
		bool readFileDownloadResponse(uint32_t timeout);

		enum class DownloadState {
			ExtractingHeaderData,
			ParsingStartOfFile,
			ParsingFile
		};
		struct DownloadData
		{
			DownloadState state;
			uint32_t contentLength;
			uint32_t contentReceived;
			std::string fileName;
			bool fileComplete;
			File file;
		};
		bool processFrame(DownloadData& data, uint8_t* frame, uint32_t size);

		bool convertToUInt16(const std::string& str, uint16_t& outValue);
		bool convertToUInt32(const std::string& str, uint32_t& outValue);

		void toggleLED() {
			if (m_trafficLed)
				m_trafficLed->toggle();
		}
		void setLED(bool on) {
			if (m_trafficLed)
				m_trafficLed->set(on);
		}

		UART m_uart;
		DigitalPin* m_trafficLed;	// LED to visualize the UP/DOWNLOAD of files
	};
}
#endif
