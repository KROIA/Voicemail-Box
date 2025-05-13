#include "peripherals/uart.hpp"
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
	void UART::send(const uint8_t* data, uint16_t size)
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
		for (uint16_t i = 0; i < size; i++)
		{
			tx_buffer[tx_write_index] = data[i];
			tx_write_index = (tx_write_index + 1) % m_bufferSize;
			if(tx_read_index == tx_write_index)
				tx_read_index = (tx_read_index + 1) % m_bufferSize;
		}
		if (size > 0 && !m_sending) // Buffer overflow
		{
			m_sending = true;
			uint16_t index = tx_read_index;
			tx_read_index = (tx_read_index + 1) % m_bufferSize; // Overwrite the oldest data
			VMB_HAL_UART_Transmit_IT(m_uart, &tx_buffer[index], 1);
		}		
	}


	uint16_t UART::hasBytesReceived() const
	{
		return rx_write_index - rx_read_index;
	}
	bool UART::receive(uint8_t* data, uint16_t size)
	{
		if (data == nullptr)
		{
			return false;
		}
		uint16_t bytesReceived = hasBytesReceived();
		if (bytesReceived == 0)
		{
			return false;
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
		return true;
	}
	bool UART::waitUntil(char character, uint32_t timeoutMS)
	{
		uint32_t startTime = VMB_HAL_GetTickCountInMs();
		uint16_t readIndex = rx_read_index;
		// Search first occurrence of character in the buffer
		for (uint16_t i = rx_read_index; i < rx_write_index; i++)
		{
			if (rx_buffer[i] == character)
			{
				return true;
			}
		}
		readIndex = (rx_write_index-1) % m_bufferSize; // Update read index to the end of the buffer + 1

		// If not found, wait for the character to be received
		uint16_t currentReceivedBytes = hasBytesReceived();
		while (VMB_HAL_GetTickCountInMs() - startTime < timeoutMS)
		{
			uint16_t rb = hasBytesReceived();
			if (currentReceivedBytes != rb)
			{
				currentReceivedBytes = rb;
				if (rx_buffer[readIndex] == character)
				{
					return true; // Character found
				}
				readIndex = (rx_write_index-1) % m_bufferSize;
			}
		}
		// Timeout reached
		return false;
	}
	bool UART::waitUntil(const char* str, uint32_t timeoutMS)
	{
		uint16_t strLength = strlen(str);
		uint32_t startTime = VMB_HAL_GetTickCountInMs();
		// Search first occurrence of string in the buffer
		for (uint16_t i = rx_read_index; i < rx_write_index; i++)
		{
			bool found = true;
			for (uint16_t j = 0; j < strLength; j++)
			{
				if (rx_buffer[(i + j) % m_bufferSize] != str[j])
				{
					found = false;
					break;
				}
			}
			if (found)
			{
				return true;
			}
		}
		// If not found, wait for the string to be received
		uint16_t currentReceivedBytes = hasBytesReceived();
		while (VMB_HAL_GetTickCountInMs() - startTime < timeoutMS)
		{
			uint16_t rb = hasBytesReceived();
			if (currentReceivedBytes != rb)
			{
				currentReceivedBytes = rb;
				for (uint16_t i = rx_read_index; i < rx_write_index; i++)
				{
					bool found = true;
					for (uint16_t j = 0; j < strLength; j++)
					{
						if (rx_buffer[(i + j) % m_bufferSize] != str[j])
						{
							found = false;
							break;
						}
					}
					if (found)
					{
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
		if (tx_write_index != tx_read_index) // Buffer overflow
		{
			uint16_t index = tx_read_index;
			tx_read_index = (tx_read_index + 1) % m_bufferSize; // Overwrite the oldest data
			VMB_HAL_UART_Transmit_IT(m_uart, &tx_buffer[index], 1);
		}
		else
			m_sending = false;
	}
}




