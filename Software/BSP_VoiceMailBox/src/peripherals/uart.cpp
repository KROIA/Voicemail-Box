#include "peripherals/uart.hpp"
#include "utilities/Logger.hpp"
#include <string>
#include <cstring>


namespace VoiceMailBox
{
	UART* UART::s_instances[] = { nullptr };


	UART::UART(VMB_UART_Handle* uartHandle, uint16_t bufferSize)
		: m_uart(uartHandle)
#ifdef VMB_UART_USE_STATIC_BUFFER_SIZE
		, m_bufferSize(VMB_UART_STATIC_BUFFER_SIZE)
		, rx_buffer{ 0 }
		, tx_buffer{ 0 }
#else
		, m_bufferSize(bufferSize)
		, rx_buffer(new uint8_t[bufferSize])
		, tx_buffer(new uint8_t[bufferSize])
#endif
		, rx_data(0)
		, rx_write_index(0)
		, rx_read_index(0)
		, tx_write_index(0)
		, tx_read_index(0)
		, m_sending(false)
		, m_bytesToSend(0)
	{
		for (std::size_t i = 0; i < sizeof(s_instances); i++)
		{
			if (s_instances[i] == nullptr)
			{
				s_instances[i] = this;
				break;
			}
		}

#ifndef VMB_UART_USE_STATIC_BUFFER_SIZE
		memset(tx_buffer, 0, m_bufferSize);
		memset(rx_buffer, 0, m_bufferSize);
#endif
		rx_data = 0;
		rx_write_index = 0;
		rx_read_index = 0;
	}
	UART::~UART()
	{
		for (std::size_t i = 0; i < sizeof(s_instances); i++)
		{
			if (s_instances[i] == this)
			{
				s_instances[i] = nullptr;
				break;
			}
		}
#ifndef VMB_UART_USE_STATIC_BUFFER_SIZE
		delete[] rx_buffer;
		delete[] tx_buffer;
#endif
	}
	bool UART::setup()
	{
		VMB_HAL_Status status = VMB_HAL_UART_Receive_IT(m_uart, &rx_data, 1);
		VMB_LOGGER_HANDLE_STATUS(status, "UART::setup()");
		return status == VMB_HAL_Status::OK;
	}

	void UART::send(const char* str)
	{
		send((uint8_t*)str, strlen(str));
	}
	void UART::send(const uint8_t* data, uint32_t size)
	{
		if (size > m_bufferSize)
		{
			size = m_bufferSize;
		}
		if (data == nullptr)
		{
			return;
		}
		for (uint32_t i = 0; i < size; i++)
		{
			tx_buffer[tx_write_index] = data[i];
			tx_write_index = (tx_write_index + 1) % m_bufferSize;
		}
		m_bytesToSend += size;
		if (size > 0 && !m_sending) 
		{
			m_sending = true;
			m_bytesToSend--;
			VMB_HAL_UART_Transmit_IT(m_uart, &tx_buffer[tx_read_index], 1);
		}		
	}


	uint32_t UART::hasBytesReceived() const
	{
		return (m_bufferSize + rx_write_index - rx_read_index) % m_bufferSize;
	}
	uint32_t UART::receive(uint8_t* data, uint32_t size)
	{
		if (data == nullptr)
		{
			return 0;
		}
		uint16_t bytesReceived = hasBytesReceived();
		if (bytesReceived == 0)
		{
			return 0;
		}
		if (size > bytesReceived)
		{
			size = bytesReceived;
		}
		for (uint16_t i = 0; i < size; i++)
		{
			data[i] = rx_buffer[(rx_read_index + i) % m_bufferSize];
		}
		rx_read_index = (rx_read_index + size) % m_bufferSize; // Update read index
		return size;
	}
	uint32_t UART::receiveUntil(uint8_t* data, uint32_t size, uint8_t* target, uint32_t targetSize, uint32_t timeoutMS)
	{
		if (data == nullptr || target == nullptr)
		{
			return 0;
		}
		uint32_t startTime = VMB_HAL_GetTickCountInMs();
		uint32_t currentWriteIndex = 0;

		while (VMB_HAL_GetTickCountInMs() - startTime < timeoutMS)
		{
			uint32_t rb = hasBytesReceived();
			if (rb >= targetSize)
			{
				bool found = false;
				uint32_t matchCount = 0;
				uint32_t foundIndex = 0;
				for (uint32_t i = rx_read_index; i != (rx_write_index-targetSize) % m_bufferSize; i = (i + 1) % m_bufferSize)
				{
					
					for (uint32_t j = 0; j < targetSize; j++)
					{
						if (rx_buffer[(i + j) % m_bufferSize] == target[j])
						{
							if(j == 0)
								foundIndex = i;
							matchCount++;
							if(matchCount == targetSize)
							{
								found = true;
								goto extractData;
							}
						}
						else
						{
							matchCount = 0;
							break;
						}
					}
				}
				extractData:


				if (found)
				{
					while(1)
					{
						if (currentWriteIndex < size)
						{
							if (rx_read_index == foundIndex)
							{
								return currentWriteIndex;
							}
							data[currentWriteIndex] = rx_buffer[rx_read_index];
							rx_read_index = (rx_read_index + 1) % m_bufferSize; // Update read index
							currentWriteIndex++;
						}
						else
						{
							return currentWriteIndex;
						}
					}
				}
				else
				{
					for (uint32_t i = 0; i < rb - targetSize; i++)
					{					
						if (currentWriteIndex < size)
						{
							data[currentWriteIndex] = rx_buffer[rx_read_index];
							currentWriteIndex++;
							rx_read_index = (rx_read_index + 1) % m_bufferSize; // Update read index
						}
						else
						{
							return currentWriteIndex;
						}
					}
				}
			}
		}
		// Timeout reached, return the data received so far
		VMB_LOGGER_PRINTLN("UART::receiveUntil() timeout reached, returning data received so far.");
		return currentWriteIndex;
	}
	bool UART::waitUntil(char character, uint32_t timeoutMS)
	{
		uint32_t startTime = VMB_HAL_GetTickCountInMs();
		uint32_t readIndex = rx_read_index;
		uint32_t currentReceivedBytes = hasBytesReceived();
		// Search first occurrence of character in the buffer
		for (uint32_t i = 0; i < currentReceivedBytes; i++)
		{
			if (rx_buffer[(readIndex + i) % m_bufferSize] == character)
			{
				return true;
			}
		}
		readIndex = currentReceivedBytes;
		uint32_t timeoutTime = startTime + timeoutMS;

		// If not found, wait for the character to be received
		while (VMB_HAL_GetTickCountInMs() > timeoutTime)
		{
			uint16_t rb = hasBytesReceived();
			if (currentReceivedBytes != rb)
			{
				currentReceivedBytes = rb;
				if (rx_buffer[readIndex % m_bufferSize] == character)
				{
					return true; // Character found
				}
				++readIndex;
			}
		}
		// Timeout reached
		VMB_LOGGER_PRINTLN(std::string("UART::waitUntil() timeout reached, character: '")+character+"' not found.");
		return false;
	}
	bool UART::waitUntil(const char* str, uint32_t timeoutMS)
	{
		uint32_t startIndex = 0;
		bool result = waitUntil_internal(str, timeoutMS, startIndex);
		if (!result)
		{
			VMB_LOGGER_PRINTLN("UART::waitUntil() timeout reached, string: \""+std::string(str)+"\" not found.");
		}
		return result;
	}
	bool UART::waitUntilAndFlush(const char* str, uint32_t timeoutMS)
	{
		uint32_t startIndex = 0;
		bool result = waitUntil_internal(str, timeoutMS, startIndex);
		if (result)
		{
			rx_read_index = (startIndex + strlen(str)) % m_bufferSize; // Update read index
		}
		else
		{
			VMB_LOGGER_PRINTLN("UART::waitUntilAndFlush() timeout reached, string: \"" + std::string(str) + "\" not found.");
		}
		return result;
	}

	bool UART::waitUntil_internal(const char* str, uint32_t timeoutMS, uint32_t& startIndex)
	{
		uint16_t strLength = strlen(str);
		uint32_t startTime = VMB_HAL_GetTickCountInMs();
		uint32_t startOffset = 0;
		uint16_t currentReceivedBytes = hasBytesReceived();
		// Search first occurrence of string in the buffer
		if (currentReceivedBytes >= strLength)
		{
			for (uint16_t i = 0; i <= currentReceivedBytes - strLength; ++i)
			{
				bool found = true;

				for (uint16_t j = 0; j < strLength; j++)
				{
					if (rx_buffer[(rx_read_index + i + j) % m_bufferSize] != str[j])
					{
						found = false;
						++startOffset;
						break;
					}
				}

				if (found)
				{
					startIndex = i;
					return true;
				}
			}
		}
		// If not found, wait for the string to be received
		while (VMB_HAL_GetTickCountInMs() - startTime < timeoutMS)
		{
			uint16_t rb = hasBytesReceived();
			if (rb - currentReceivedBytes >= strLength)
			{
				currentReceivedBytes = rb - strLength;
				for (uint32_t i = startOffset; i <= currentReceivedBytes; ++i)
				{
					bool found = true;
					for (uint16_t j = 0; j < strLength; j++)
					{
						if (rx_buffer[(rx_read_index + i + j) % m_bufferSize] != str[j])
						{
							++startOffset;
							found = false;
							break;
						}
					}
					if (found)
					{
						startIndex = i;
						return true;
					}
				}
			}
		}
		// Timeout reached
		return false;
	}


	void UART::flush()
	{
		rx_write_index = 0;
		rx_read_index = 0;
		tx_write_index = 0;
		tx_read_index = 0;
		m_sending = false;
		memset(rx_buffer, 0, m_bufferSize);
		memset(tx_buffer, 0, m_bufferSize);
	}
	void UART::flushRX()
	{
		rx_read_index = rx_write_index; // Update read index
	}

	uint32_t UART::flushNBytes(uint32_t nBytes)
	{
		uint32_t currentReceivedBytes = hasBytesReceived();
		if (currentReceivedBytes == 0)
		{
			return 0;
		}
		if (nBytes > currentReceivedBytes)
		{
			nBytes = currentReceivedBytes;
		}
		rx_read_index = (rx_read_index + nBytes) % m_bufferSize; // Update read index
		return nBytes;
	}

	

	void UART::onITReceivedData(VMB_UART_Handle* huart)
	{
		for (std::size_t i = 0; i < sizeof(s_instances); i++)
		{
			if (s_instances[i] != nullptr && s_instances[i]->m_uart == huart)
			{
				s_instances[i]->onITReceivedData();
				return;
			}
		}
	}
	void UART::onITByteSent(VMB_UART_Handle* huart)
	{
		for (std::size_t i = 0; i < sizeof(s_instances); i++)
		{
			if (s_instances[i] != nullptr && s_instances[i]->m_uart == huart)
			{
				s_instances[i]->onITByteSent();
				return;
			}
		}
	}


	void UART::onITReceivedData()
	{
		// Circular buffer implementation
		rx_buffer[rx_write_index] = rx_data;
		rx_write_index = (rx_write_index + 1) % m_bufferSize;


		if (rx_write_index == rx_read_index) // Buffer overflow
		{
			rx_read_index = (rx_read_index + 1) % m_bufferSize; // Overwrite the oldest data
		}
		VMB_HAL_UART_Receive_IT(m_uart, &rx_data, 1);
	}
	void UART::onITByteSent()
	{
		tx_read_index = (tx_read_index + 1) % m_bufferSize;
		if (m_bytesToSend > 0) // Buffer overflow
		{
			VMB_HAL_UART_Transmit_IT(m_uart, &tx_buffer[tx_read_index], 1);
			m_bytesToSend--;
		}
		else
			m_sending = false;
	}
}




