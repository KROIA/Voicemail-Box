#include "peripherals/ATCommandClient.hpp"
#include "peripherals/File.hpp"
#include "BSP_VoiceMailBox.hpp"
#include <string>
#include <cstring>

namespace VoiceMailBox
{
	ATCommandClient::ATCommandClient(VMB_UART_Handle* uartHandle, uint16_t uartBufferSize)
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


		sendCommand("ATE0");
		waitUntil("OK\r\n", 5000); // Disable echo
	}


	bool ATCommandClient::sendCommand(const std::string& command)
	{
		return sendCommand(command.c_str());
	}
	bool ATCommandClient::sendCommand(const char* command)
	{
		m_uart.flush();
		m_uart.send((uint8_t*)command, strlen(command));
		m_uart.send((uint8_t*)("\r\n"), 2);
		uint32_t currentTick = VMB_HAL_GetTickCountInMs();
		uint32_t timeout = currentTick + 1000; // 1 second timeout
		bool timedOut = false;
		while (m_uart.isSending() && !timedOut)
		{
			timedOut =  VMB_HAL_GetTickCountInMs() > timeout;
			VMB_HAL_Delay(1); // Wait for the UART to finish sending
		}
		return !timedOut;
	}
	bool ATCommandClient::sendBytes(const uint8_t* data, uint16_t size)
	{
		m_uart.send(data, size);
		uint32_t currentTick = VMB_HAL_GetTickCountInMs();
		uint32_t timeout = currentTick + 1000; // 1 second timeout
		bool timedOut = false;
		while (m_uart.isSending() && !timedOut)
		{
			timedOut = VMB_HAL_GetTickCountInMs() > timeout;
			VMB_HAL_Delay(1); // Wait for the UART to finish sending
		}
		return !timedOut;
	}

	bool ATCommandClient::waitUntil(const char* response, uint32_t timeout)
	{
		return m_uart.waitUntil(response, timeout);
	}


	bool ATCommandClient::doesRespond()
	{
		sendCommand("AT");
		if(m_uart.waitUntil("OK\r\n", 5000))
		{
			log("responds to AT command");
			return true; // Device responds to AT command
		}
		else
		{
			log("does not respond to AT command");
			return false; // Device does not respond
		}
	}



	bool ATCommandClient::connectToWifi(const std::string& ssid, const std::string& password)
	{
		std::string command = "AT+CWJAP=\"" + ssid + "\",\"" + password + "\"";
		sendCommand(command.c_str());
		if (waitUntil("WIFI GOT IP\r\n", 10000))
		{
			// Successfully connected to WiFi
			log("Connected to WiFi");
			return true;
		}
		else
		{
			// Failed to connect to WiFi
			log("Failed to connect to WiFi");
			return false;
		}
	}

	bool ATCommandClient::sendFileToServer(const std::string& fileName, const std::string& serverIP, uint16_t serverPort)
	{
		File file;
		if (!file.open(fileName.c_str(), File::AccessMode::read))
		{
			log("Failed to open file: \"" +fileName+"\"");
			return false; // Failed to open the file
		}

		uint32_t fileSize = file.getSize();
		if (fileSize == 0)
		{
			log("File is empty: \"" + fileName + "\"");
			return false; // File is empty
		}

		// open TCP connection to the server
		std::string startRequest = "AT+CIPSTART=\"TCP\",\"" + serverIP + "\"," + std::to_string(serverPort);
		sendCommand(startRequest.c_str());
		if (!waitUntil("OK\r\n", 5000))
		{
			log("Failed to connect to server: \"" + serverIP + ":" + std::to_string(serverPort) + "\"");
			return false; // Failed to connect to the server
		}

		std::string _fileName = fileName;
		if (_fileName.find("/") != std::string::npos)
		{
			_fileName = _fileName.substr(_fileName.find_last_of("/") + 1);
		}
		else if (_fileName.find("\\") != std::string::npos)
		{
			_fileName = _fileName.substr(_fileName.find_last_of("\\") + 1);
		}

		std::string boundary = "------------------------eYRLjSUtcTX8XlV9TLI4k1";
		//std::string boundary = "----4k1";


		std::string post = "POST /devicesbackend/upload/ HTTP/1.1\r\n";
		std::string host = "Host: " + serverIP + ":" + std::to_string(serverPort) + "\r\n";
		std::string userAgent = "User-Agent: ESP32\r\n";
		//std::string accept = "Accept: */*\r\n";
		std::string contentType = "Content-Type: multipart/form-data; boundary=" + boundary + "\r\n";
		std::string emptyLine = "\r\n";
		std::string boundaryStart = "--" + boundary + "\r\n";
		std::string contentDisposition = "Content-Disposition: form-data; name=\"test\"; filename=\"" + _fileName + "\"\r\n";
		std::string contentTypeFile = "Content-Type: text/plain\r\n";
		std::string boundaryEnd = "--" + boundary + "--\r\n";




		std::string contentLength = "Content-Length: " + std::to_string(fileSize + boundaryStart.size() + 
			contentDisposition.size() + contentTypeFile.size() + emptyLine.size() + boundaryEnd.size() + 2) + "\r\n";


		

		//std::string contentHeaderTop =
		//	"\r\n"+boundary+"\r\n"
		//	"Content-Disposition: form-data; name=\"test\"; filename=\"" + _fileName + "\"\r\n"
		//	"Content-Type: text/plain\r\n";
		//
		//std::string contentHeaderBottom =
		//	"\r\n"+boundary+"--\r\n";

		//uint32_t contentLength = contentHeaderTop.length() + fileSize + contentHeaderBottom.length();

		//std::vector<std::string> headers = {
		//	"POST /devicesbackend/upload/ HTTP/1.1\r\n",
		//	"Host: " + serverIP + ":" + std::to_string(serverPort)+"\r\n",
		//	"User-Agent: ESP32\r\n",
		//	"Content-Length: " + std::to_string(contentLength) + "\r\n",
		//	"Content-Type: multipart/form-data; boundary=" + boundary + "\r\n",
		//};

		//std::string postRequest =
		//	"POST /devicesbackend/upload/ HTTP/1.1\r\n"
		//	"Host: 192.168.1.116:8000\r\n"
		//	"User-Agent: ESP32\r\n"
		//	"Content-Length: " + std::to_string(contentLength) + "\r\n"
		//	"Content-Type: multipart/form-data; boundary="+boundary+"\r\n";

		uint32_t postRequestSize =
			post.length() +
			host.length() +
			userAgent.length() +
			//accept.length() +
			contentLength.length() +
			contentType.length() +
			emptyLine.length() +
			boundaryStart.length() +
			contentDisposition.length() +
			contentTypeFile.length() +
			emptyLine.length() +
			fileSize +
			boundaryEnd.length()+2;
		//for (const auto& header : headers)
		//{
		//	postRequestSize += header.length();
		//}

		sendCommand("AT+CIPSEND=" + std::to_string(postRequestSize));

		if (!waitUntil(">", 5000))
		{
			log("Failed to send data to server");
			return false; // Failed to send data to the server
		}

		delay(50); // Give the ESP some time to process the command

		//for (const auto& header : headers)
		//{
		//	sendBytes((const uint8_t*)header.c_str(), header.size());
		//	//delay(10); // Give the ESP some time to process the command
		//}

		//sendCommand(postRequest.c_str());
		//sendBytes((const uint8_t*)contentHeaderTop.c_str(), contentHeaderTop.size());
		sendBytes((const uint8_t*)post.c_str(), post.size());
		sendBytes((const uint8_t*)host.c_str(), host.size());
		sendBytes((const uint8_t*)userAgent.c_str(), userAgent.size());
		//sendBytes((const uint8_t*)accept.c_str(), accept.size());
		sendBytes((const uint8_t*)contentLength.c_str(), contentLength.size());
		sendBytes((const uint8_t*)contentType.c_str(), contentType.size());
		sendBytes((const uint8_t*)emptyLine.c_str(), emptyLine.size());
		sendBytes((const uint8_t*)boundaryStart.c_str(), boundaryStart.size());
		sendBytes((const uint8_t*)contentDisposition.c_str(), contentDisposition.size());
		sendBytes((const uint8_t*)contentTypeFile.c_str(), contentTypeFile.size());
		sendBytes((const uint8_t*)emptyLine.c_str(), emptyLine.size());
		uint8_t* buffer = new uint8_t[fileSize];
		if (file.read((char*)buffer, fileSize) != fileSize)
		{
			log("Failed to read file: \"" + fileName + "\"");
			delete[] buffer;
			return false; // Failed to read the file
		}
		uint32_t currentSendPos = 0;
		uint32_t deltaPos = m_uart.getBufferSize() / 2;
		uint32_t splits = fileSize / deltaPos;
		for (uint32_t i = 0; i < splits; ++i)
		{
			if (!sendBytes(buffer + currentSendPos, deltaPos))
			{
				log("Failed to send file data");
				delete[] buffer;
				return false; // Failed to send file data
			}
			//delay(5); // Give the ESP some time to process the command
			currentSendPos += deltaPos;
		}
		if (currentSendPos < fileSize)
		{
			if (!sendBytes(buffer + currentSendPos, fileSize - currentSendPos))
			{
				log("Failed to send file data");
				delete[] buffer;
				return false; // Failed to send file data
			}
		}
		sendBytes((const uint8_t*)"\r\n", 2); // Send the empty line after the file data
		delete[] buffer;
		buffer = nullptr;
		//delay(20); // Give the ESP some time to process the command
		//sendBytes((const uint8_t*)contentHeaderBottom.c_str(), contentHeaderBottom.size());
		sendBytes((const uint8_t*)boundaryEnd.c_str(), boundaryEnd.size());
		if (!waitUntil("SEND OK\r\n", 5000))
		{
			log("Failed to send file data");
			return false; // Failed to send file data
		}

		if (!waitUntil("same-origin", 10000))
		{
			log("Failed to send file data");
			return false; // Failed to send file data
		}

		delay(100); // Give the ESP some time to process the command
		sendCommand("AT+CIPCLOSE");
		if (!waitUntil("CLOSED\r\n", 5000))
		{
			log("Failed to close connection");
			return false; // Failed to close connection
		}

		log("File sent successfully: \"" + fileName + "\" to "+ serverIP+":"+std::to_string(serverPort));
		return true;
	}


	void ATCommandClient::log(const std::string& msg)
	{
		if (m_enableLogging)
		{
			// Log the message to the console or a file
			std::string logMessage = "[ATCommandClient]: " + msg + "\r\n";
			print(logMessage.c_str());
		}
	}
}
