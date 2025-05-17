#include "peripherals/uart.hpp"
#include <string>
#include <cstring>
#include "BSP_VoiceMailBox.hpp"


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
	void UART::setup()
	{
		VMB_HAL_UART_Receive_IT(m_uart, &rx_data, 1);
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
		//memcpy(tx_buffer, data, size);
		//VMB_HAL_UART_Transmit(static_cast<VMB_UART_Handle*>(m_uart), tx_buffer, size, 100);
		//VMB_HAL_UART_Transmit_IT(static_cast<VMB_UART_Handle*>(m_uart), tx_buffer, size);
		for (uint32_t i = 0; i < size; i++)
		{
			tx_buffer[tx_write_index] = data[i];
			tx_write_index = (tx_write_index + 1) % m_bufferSize;
			//if(tx_read_index == tx_write_index)
			//	tx_read_index = (tx_read_index + 1) % m_bufferSize;
		}
		m_bytesToSend += size;
		if (size > 0 && !m_sending) // Buffer overflow
		{
			m_sending = true;
			m_bytesToSend--;
			//uint16_t index = tx_read_index;
			//tx_read_index = (tx_read_index + 1) % m_bufferSize; // Overwrite the oldest data
			VMB_HAL_UART_Transmit_IT(m_uart, &tx_buffer[tx_read_index], 1);
		}		
	}


	uint32_t UART::hasBytesReceived() const
	{
		//if(rx_write_index < rx_read_index)
		//	return rx_write_index + m_bufferSize - rx_read_index;
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
		if (rx_write_index == rx_read_index) // Buffer overflow
		{
			int a=0;
		}
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
			if (rb > targetSize)
			{
				//setDbgPin(DBG_PIN::DBG2, 1);
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
								//setDbgPin(DBG_PIN::DBG2, 0);
								return currentWriteIndex;
							}
							data[currentWriteIndex] = rx_buffer[rx_read_index];
							rx_read_index = (rx_read_index + 1) % m_bufferSize; // Update read index
							currentWriteIndex++;
							if (rx_write_index == rx_read_index) // Buffer overflow
									{
										int a=0;
									}

						}
						else
						{
							//setDbgPin(DBG_PIN::DBG2, 0);
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
							if (rx_write_index == rx_read_index) // Buffer overflow
									{
										int a=0;
									}
						}
						else
						{
							//setDbgPin(DBG_PIN::DBG2, 0);
							return currentWriteIndex;
						}
					}
				}
			}
		}
		//setDbgPin(DBG_PIN::DBG2, 0);
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
		return false;
	}
	bool UART::waitUntil(const char* str, uint32_t timeoutMS)
	{
		uint16_t strLength = strlen(str);
		uint32_t startTime = VMB_HAL_GetTickCountInMs();
		uint32_t startOffset = 0;
		uint16_t currentReceivedBytes =  hasBytesReceived();
		// Search first occurrence of string in the buffer
		if(currentReceivedBytes >= strLength)
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
					return true;
				}
			}
		}
		// If not found, wait for the string to be received
		//delay(2);
		while (VMB_HAL_GetTickCountInMs() - startTime < timeoutMS)
		{
			uint16_t rb = hasBytesReceived();
			if (rb - currentReceivedBytes > strLength)
			{
				setDbgPin(DBG_PIN::DBG2, 1);
				currentReceivedBytes = rb - strLength;
				//for (uint16_t i = (rx_read_index + startOffset) % m_bufferSize; i != rx_write_index; i = (i + 1) % m_bufferSize)
				for(uint32_t i=startOffset; i<=currentReceivedBytes; ++i)
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
						setDbgPin(DBG_PIN::DBG2, 0);
						return true;
					}
				}
				setDbgPin(DBG_PIN::DBG2, 0);
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




