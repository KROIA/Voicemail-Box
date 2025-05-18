#include "peripherals/ATCommandClient.hpp"
#include "peripherals/File.hpp"
#include "BSP_VoiceMailBox.hpp"
#include <string>
#include <cstring>
#include <limits>
#include <charconv>  // For std::from_chars (C++17 and later)

namespace VoiceMailBox
{
	class AutoLedClearer
	{
	public:
		AutoLedClearer(DigitalPin* led)
			: m_led(led)
		{
			if(m_led)
				m_led->set(true);
		}
		~AutoLedClearer()
		{
			if (m_led)
				m_led->set(false);
		}

	private:
		DigitalPin* m_led;
	};

	ATCommandClient::ATCommandClient(VMB_UART_Handle* uartHandle, uint16_t uartBufferSize)
		: Logger("ATCommandClient")
		, m_uart(uartHandle, uartBufferSize)
		, m_trafficLed(nullptr)
	{

	}
	ATCommandClient::ATCommandClient(VMB_UART_Handle* uartHandle, uint16_t uartBufferSize, DigitalPin& trafficLed)
		: Logger("ATCommandClient")
		, m_uart(uartHandle, uartBufferSize)
		, m_trafficLed(&trafficLed)
	{
		setLED(false);
	}

	ATCommandClient::~ATCommandClient()
	{
	}

	void ATCommandClient::setup()
	{
		// Setup the UART for AT command client
		m_uart.setup();


		sendCommand("ATE0");
		waitUntilAndFlush("OK\r\n", 5000); // Disable echo
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
	bool ATCommandClient::waitUntilAndFlush(const char* response, uint32_t timeout)
	{
		return m_uart.waitUntilAndFlush(response, timeout);
	}
	void ATCommandClient::flushRX()
	{
		m_uart.flushRX();
	}
	uint32_t ATCommandClient::flushNBytes(uint32_t nBytes)
	{
		return m_uart.flushNBytes(nBytes);
	}


	bool ATCommandClient::doesRespond()
	{
		flushRX();
		sendCommand("AT");
		if(m_uart.waitUntil("OK\r\n", 5000))
		{
			flushRX();
			logln("responds to AT command");
			return true; // Device responds to AT command
		}
		else
		{
			logln("does not respond to AT command");
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

	bool ATCommandClient::sendFileToServer(const std::string& localFileName, const std::string& urlPath, const std::string& serverIP, uint16_t serverPort)
	{

		AutoLedClearer clearer(m_trafficLed);

		flushRX();
		File file;
		if (!file.open(localFileName.c_str(), File::AccessMode::read))
		{
			logln("Failed to open file: \"" +localFileName+"\"");
			return false; // Failed to open the file
		}

		uint32_t fileSize = file.getSize();
		if (fileSize == 0)
		{
			logln("File is empty: \"" + localFileName + "\"");
			return false; // File is empty
		}

		// open TCP connection to the server
		std::string startRequest = "AT+CIPSTART=\"TCP\",\"" + serverIP + "\"," + std::to_string(serverPort);
		sendCommand(startRequest.c_str());
		if (!waitUntilAndFlush("OK\r\n", 5000))
		{
			logln("Failed to connect to server: \"" + serverIP + ":" + std::to_string(serverPort) + "\"");
			return false; // Failed to connect to the server
		}

		std::string _localFileName = localFileName;
		if (_localFileName.find("/") != std::string::npos)
		{
			_localFileName = _localFileName.substr(_localFileName.find_last_of("/") + 1);
		}
		else if (_localFileName.find("\\") != std::string::npos)
		{
			_localFileName = _localFileName.substr(_localFileName.find_last_of("\\") + 1);
		}

		std::string boundary = "------------------------eYRLjSUtcTX8XlV9TLI4k1";
		//std::string boundary = "----4k1";


		std::string post = "POST /"+ urlPath +" HTTP/1.1\r\n";
		std::string host = "Host: " + serverIP + ":" + std::to_string(serverPort) + "\r\n";
		std::string userAgent = "User-Agent: ESP32\r\n";
		std::string contentType = "Content-Type: multipart/form-data; boundary=" + boundary + "\r\n";
		std::string emptyLine = "\r\n";
		std::string boundaryStart = "--" + boundary + "\r\n";
		std::string contentDisposition = "Content-Disposition: form-data; name=\"test\"; localFileName=\"" + _localFileName + "\"\r\n";
		std::string contentTypeFile = "Content-Type: text/plain\r\n";
		std::string boundaryEnd = "--" + boundary + "--\r\n";




		std::string contentLength = "Content-Length: " + std::to_string(fileSize + boundaryStart.size() + 
			contentDisposition.size() + contentTypeFile.size() + emptyLine.size() + boundaryEnd.size() + 2) + "\r\n";


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
			emptyLine.length();
			//fileSize +
			//boundaryEnd.length()+2;


		sendCommand("AT+CIPSEND=" + std::to_string(postRequestSize));
		toggleLED();
		if (!waitUntilAndFlush(">", 5000))
		{
			logln("Failed to send data to server 1");
			return false; // Failed to send data to the server
		}
		toggleLED();

		//delay(50); // Give the ESP some time to process the command


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

		if (!waitUntilAndFlush("SEND OK\r\n", 5000))
		{
			logln("Failed to send file data");
			return false; // Failed to send file data
		}
		toggleLED();
		//delay(20); // Give the ESP some time to process the command


		// Read the file and send it in chunks
		//uint8_t* buffer = new uint8_t[fileSize];
		//if (file.read((char*)buffer, fileSize) != fileSize)
		//{
		//	logln("Failed to read file: \"" + localFileName + "\"");
		//	delete[] buffer;
		//	return false; // Failed to read the file
		//}
		uint32_t deltaPos = std::min(m_uart.getBufferSize(), (uint32_t)1024);
		uint32_t splits = fileSize / deltaPos;

		std::string buffer;
		buffer.resize(deltaPos);
		for (uint32_t i = 0; i < splits; ++i)
		{
			toggleLED();
			logln("Uploading: %.2f %",(float)i*100.f / (float)splits);
			sendCommand("AT+CIPSEND=" + std::to_string(deltaPos));

			uint32_t bytesRead = file.read((uint8_t*)buffer.c_str(), deltaPos);

			if (!waitUntilAndFlush(">", 5000))
			{
				logln("Failed to send data to server 2");
				return false; // Failed to send data to the server
			}

			if (!sendBytes((uint8_t*)buffer.c_str(), bytesRead))
			{
				logln("Failed to send file data");
				return false; // Failed to send file data
			}
			if (!waitUntilAndFlush("SEND OK\r\n", 5000))
			{
				logln("Failed to send file data");
				return false; // Failed to send file data
			}
			
		}
		uint32_t bytesRead = file.read((uint8_t*)buffer.c_str(), fileSize - splits * deltaPos);
		if (bytesRead > 0)
		{
			toggleLED();
			sendCommand("AT+CIPSEND=" + std::to_string(bytesRead));
			if (!waitUntilAndFlush(">", 5000))
			{
				logln("Failed to send data to server 3");
				return false; // Failed to send data to the server
			}
			if (!sendBytes((uint8_t*)buffer.c_str(), bytesRead))
			{
				logln("Failed to send file data");
				return false; // Failed to send file data
			}
			if (!waitUntilAndFlush("SEND OK\r\n", 5000))
			{
				logln("Failed to send file data");
				return false; // Failed to send file data
			}
			//delay(20); // Give the ESP some time to process the command
		}
		toggleLED();
		sendCommand("AT+CIPSEND=" + std::to_string(2 + boundaryEnd.size()));
		if (!waitUntilAndFlush(">", 5000))
		{
			logln("Failed to send data to server 4");
			return false; // Failed to send data to the server
		}
		sendBytes((const uint8_t*)"\r\n", 2); // Send the empty line after the file data
		sendBytes((const uint8_t*)boundaryEnd.c_str(), boundaryEnd.size()); // Send the empty line after the file data

		if (!waitUntilAndFlush("SEND OK\r\n", 5000))
		{
			logln("Failed to send file data");
			return false; // Failed to send file data
		}

		if (!waitUntilAndFlush("same-origin", 10000))
		{
			logln("Failed to send file data");
			return false; // Failed to send file data
		}

		//delay(100); // Give the ESP some time to process the command
		sendCommand("AT+CIPCLOSE");
		if (!waitUntilAndFlush("CLOSED\r\n", 5000))
		{
			logln("Failed to close connection");
			return false; // Failed to close connection
		}
		toggleLED();

		logln("File sent successfully: \"" + localFileName + "\" to "+ serverIP+":"+std::to_string(serverPort));
		return true;
	}


	bool ATCommandClient::downloadFileFromServer(const std::string& locallocalFileName, const std::string& urlPath, const std::string& serverIP, uint16_t serverPort)
	{
		AutoLedClearer clearer(m_trafficLed);
		flushRX();
		// Open TCP connection to the server
		std::string startRequest = "AT+CIPSTART=\"TCP\",\"" + serverIP + "\"," + std::to_string(serverPort);
		sendCommand(startRequest.c_str());
		if (!waitUntilAndFlush("OK\r\n", 5000)) {
			logln("Failed to connect to server: \"" + serverIP + ":" + std::to_string(serverPort) + "\"");
			return false;
		}

		std::string getRequest =
			"GET /" + urlPath + " HTTP/1.1\r\n" +
			"Host: " + serverIP + ":" + std::to_string(serverPort) + "\r\n" +
			"User-Agent: ESP32\r\n" +
			"Connection: close\r\n\r\n";

		sendCommand("AT+CIPSEND=" + std::to_string(getRequest.size()));
		if (!waitUntilAndFlush(">", 5000)) {
			logln("Failed to prepare to send GET request");
			return false;
		}
		toggleLED();
		sendBytes(reinterpret_cast<const uint8_t*>(getRequest.c_str()), getRequest.size());

		if (!waitUntilAndFlush("bytes\r\n", 5000)) {
			logln("Failed to send GET request");
			return false;
		}
		uint8_t flushBuffer[100] = { 0 };
		m_uart.receiveUntil(flushBuffer, sizeof(flushBuffer), (uint8_t*)"+IPD,", 5, 1000);
		//m_uart.receive(flushBuffer, 7); // Flush the buffer until the connection is closed

		toggleLED();
		// Wait for HTTP response headers and body
		std::string response;
		//File file;
		if (!readFileDownloadResponse(response, 10000)) { // You need to implement this method to read raw data from the ESP module
			logln("Failed to read response from server");
			return false;
		}

		logln("File downloaded successfully: \"" + locallocalFileName + "\" from " + urlPath);
		return true;
	}

	bool ATCommandClient::readFileDownloadResponse(std::string& response, uint32_t timeout)
	{
		DownloadData data;
		data.state = DownloadState::ExtractingHeaderData;
		data.contentLength = 0;
		data.contentReceived = 0;
		data.fileComplete = false;

		setLED(false);
		//delay(1000);
		while (!data.fileComplete)
		{
			toggleLED();
#ifdef VMB_DEVELOPMENT_ENABLE_DBG_PINS_IN_ATCOMMAND_CLIENT
			setDbgPin(DBG_PIN::DBG0, 1); // Set DBG0 on
#endif
			if (!m_uart.waitUntil("+IPD,", timeout)) // Wait for the start of the response
			{
				logln("Failed to read framesize");
				return false; // Failed to read response from server
			}
#ifdef VMB_DEVELOPMENT_ENABLE_DBG_PINS_IN_ATCOMMAND_CLIENT
			setDbgPin(DBG_PIN::DBG0, 0); // Set DBG0 on
#endif
			toggleLED();
			std::string ipdResponse;
			ipdResponse.resize(512); // Allocate a buffer for the IPD response
			uint32_t bytesReaded = m_uart.receiveUntil((uint8_t*)ipdResponse.c_str(), 512, (uint8_t*)"+IPD,", 5, timeout);
			bytesReaded += m_uart.receiveUntil((uint8_t*)ipdResponse.c_str()+bytesReaded, 512-bytesReaded, (uint8_t*)":", 1, timeout);
			ipdResponse = ipdResponse.substr(ipdResponse.find("+IPD,") + 5);
			ipdResponse.shrink_to_fit();
			uint8_t flushDummy;
			m_uart.receive(&flushDummy, 1); // Read the end of the IPD response
			uint32_t frameSize = 0;
			if (!convertToUInt32(ipdResponse, frameSize)) {
				logln("Failed to convert framesize to uint32_t");
				return false; // Failed to convert framesize
			}

			// Wait until the amount of bytes received is equal to the frame size
			uint32_t startTime = VMB_HAL_GetTickCountInMs();
			while (m_uart.hasBytesReceived() < frameSize)
			{
				if (VMB_HAL_GetTickCountInMs() - startTime > timeout)
				{
					logln("Timeout waiting for file content");
					return false; // Timeout waiting for file content
				}
			}

			//std::string content;
			//content.resize(frameSize); // Allocate a buffer for the file content
			//m_uart.receive((uint8_t*)content.c_str(), frameSize);
			std::string content;
			content.resize(frameSize);
#ifdef VMB_DEVELOPMENT_ENABLE_DBG_PINS_IN_ATCOMMAND_CLIENT
			setDbgPin(DBG_PIN::DBG0, 1); // Set DBG0 on
#endif
			uint32_t bytesRead = m_uart.receive((uint8_t*)content.c_str(), frameSize);
#ifdef VMB_DEVELOPMENT_ENABLE_DBG_PINS_IN_ATCOMMAND_CLIENT
			setDbgPin(DBG_PIN::DBG0, 0); // Set DBG0 on
#endif
			uint32_t stillInUartBuff = m_uart.hasBytesReceived();
			if(stillInUartBuff >  100)
			{
				int a=0;
			}
			//logln("Still in uartBuff: "+std::to_string(stillInUartBuff));

			if (!processFrame(data, (uint8_t*)content.c_str(), frameSize))
			{
				logln("Failed to process frame");
				//delete[] content;
				return false; // Failed to process frame
			}
			
			if(data.state == DownloadState::ParsingStartOfFile)
			{
				if (!processFrame(data, (uint8_t*)content.c_str(), frameSize))
				{
					logln("Failed to process start of file");
					//delete[] content;
					//content = nullptr;
					return false; // Failed to process frame
				}
			}
			//delete[] content;
			//content = nullptr;
		}

		data.file.close(); // Close the file

		return data.fileComplete;
	}

	bool ATCommandClient::processFrame(DownloadData& data, uint8_t* frame, uint32_t size)
	{
		switch (data.state)
		{
		case DownloadState::ExtractingHeaderData:
		{
			// Extract the header data from the frame
			std::string frameStr((char*)frame, size);
			size_t contentLengthIndex = frameStr.find("Content-Length: ");
			if (contentLengthIndex != std::string::npos)
			{
				contentLengthIndex += 16; // Move the index to the start of the content length value
				std::string contentLengthStr = frameStr.substr(contentLengthIndex, frameStr.find("\r\n", contentLengthIndex) - contentLengthIndex);
				uint32_t contentLength = 0;
				if (convertToUInt32(contentLengthStr, contentLength))
				{
					data.contentLength = contentLength;
				}
			}


			size_t fileNameIndex = frameStr.find("filename=\"");
			if (fileNameIndex != std::string::npos)
			{
				fileNameIndex += 10; // Move the index to the start of the file name value
				std::string fileNameStr = frameStr.substr(fileNameIndex, frameStr.find("\"", fileNameIndex) - fileNameIndex);
				data.fileName = fileNameStr;
			}

			if(data.contentLength > 0 && data.fileName.size() > 0)
			{
				data.file.open(data.fileName.c_str(), File::AccessMode::write);
				if (!data.file.isOpen())
				{
					logln("Failed to open file for writing: \"" + data.fileName + "\"");
					return false; // Failed to open the file
				}
				if(frameStr.find("\r\n\r\n") != std::string::npos)
					data.state = DownloadState::ParsingStartOfFile;
			}
			break;
		}
		case DownloadState::ParsingStartOfFile:
		{
			// Extract the file content from the frame
			std::string frameStr((char*)frame, size);
			size_t contentStartIndex = frameStr.find("\r\n\r\n");
			if (contentStartIndex != std::string::npos)
			{
				contentStartIndex += 4; // Move the index to the start of the file content
				std::string fileContentStr = frameStr.substr(contentStartIndex, frameStr.size() - contentStartIndex);
				uint32_t bytesToSave = fileContentStr.size();
				if (data.contentReceived + bytesToSave > data.contentLength)
				{
					bytesToSave = data.contentLength - data.contentReceived;
				}

				logln("Writing block: "+std::to_string(0) + " at: "+std::to_string(data.contentReceived) + " with size: "+std::to_string(bytesToSave));
#ifdef VMB_DEVELOPMENT_ENABLE_DBG_PINS_IN_ATCOMMAND_CLIENT
				setDbgPin(DBG_PIN::DBG1, 1); // Set DBG0 on
#endif
				data.contentReceived += data.file.write((uint8_t*)fileContentStr.c_str(), bytesToSave); // Write the file content to the file
#ifdef VMB_DEVELOPMENT_ENABLE_DBG_PINS_IN_ATCOMMAND_CLIENT
				//setDbgPin(DBG_PIN::DBG1, 0); // Set DBG0 on
				setDbgPin(DBG_PIN::DBG1, 0); // Set DBG0 on
#endif
				//delay(10);
				if (data.contentReceived >= data.contentLength)
				{
					data.fileComplete = true; // File download complete
					data.file.close(); // Close the file
				}
			}
			else
			{
				logln("Failed to find start of file content in frame");
				return false; // Failed to find start of file content
			}
			data.state = DownloadState::ParsingFile;
			break;
		}
		case DownloadState::ParsingFile:
		{
			static uint32_t count = 1;
			uint32_t bytesToSave = size;
			if(data.contentReceived + bytesToSave > data.contentLength)
			{
				bytesToSave = data.contentLength - data.contentReceived;
			}
			/*data.file.close();
			std::string fileName = data.fileName.substr(0, data.fileName.find("."));
			data.file.open((fileName+"_"+std::to_string(count++)+".txt").c_str(), File::AccessMode::write);
			//data.file.open(data.fileName.c_str(), File::AccessMode::append);
			if (!data.file.isOpen())//
			{
				logln("Failed to open file for writing: \"" + data.fileName + "\"");
				return false; // Failed to open the file
			}*/
			logln("Writing block: "+std::to_string(count++) + " at: "+std::to_string(data.contentReceived)  + " with size: "+std::to_string(bytesToSave));
#ifdef VMB_DEVELOPMENT_ENABLE_DBG_PINS_IN_ATCOMMAND_CLIENT
			setDbgPin(DBG_PIN::DBG1, 1); // Set DBG0 on
#endif
			uint32_t written = data.file.write(frame, bytesToSave); // Write the file content to the file
#ifdef VMB_DEVELOPMENT_ENABLE_DBG_PINS_IN_ATCOMMAND_CLIENT
			//setDbgPin(DBG_PIN::DBG1, 0); // Set DBG0 on
			setDbgPin(DBG_PIN::DBG1, 0); // Set DBG0 on
#endif
			data.contentReceived += written;
			logln("Downloading: %.2f %", (float)data.contentReceived * 100.f / (float)data.contentLength);
			if (data.contentReceived >= data.contentLength)
			{
				data.fileComplete = true; // File download complete
				data.file.close(); // Close the file
			}
			break;
		}
		default:
			logln("Invalid download state");
			return false; // Invalid download state
		}
		return true; // Frame processed successfully
	}


	bool ATCommandClient::convertToUInt16(const std::string& str, uint16_t& outValue)
	{
		// Use std::from_chars for efficient and safe conversion (C++17+)
		uint32_t temp = 0; // Use a larger type to detect overflow
		auto [ptr, ec] = std::from_chars(str.data(), str.data() + str.size(), temp);

		outValue = static_cast<uint32_t>(temp);
		std::string cmp = std::to_string(outValue);
		size_t minSize = std::min(str.size(), cmp.size());
		bool compared = true;
		for(size_t i=0; i<minSize; ++i)
		{
			if(cmp[i] != str[i])
			{
				compared = false;
				break;
			}
		}
	}
	bool ATCommandClient::convertToUInt32(const std::string& str, uint32_t& outValue)
	{
		// Use std::from_chars for efficient and safe conversion (C++17+)
		uint64_t temp = 0; // Use a larger type to detect overflow
		auto [ptr, ec] = std::from_chars(str.data(), str.data() + str.size(), temp);
		outValue = static_cast<uint32_t>(temp);
		std::string cmp = std::to_string(outValue);
		size_t minSize = std::min(str.size(), cmp.size());
		bool compared = true;
		for(size_t i=0; i<minSize; ++i)
		{
			if(cmp[i] != str[i])
			{
				compared = false;
				break;
			}
		}
		return compared;
	}
}
