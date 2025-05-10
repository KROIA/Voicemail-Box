#include "uart.hpp"
#include "HAL_abstraction.hpp"
#include <string>
#include <cstring>

namespace VoiceMailBox
{
	UART* UART::s_instances[20] = { nullptr };


	UART::UART(void* uartHandle, std::size_t bufferSize)
		: uart(uartHandle)
		, m_bufferSize(bufferSize)
		, rx_buffer(new uint8_t[bufferSize])
		, rx_data(0)
		, rx_write_index(0)
		, rx_read_index(0)
		, tx_buffer(new uint8_t[bufferSize])
		, tx_write_index(0)
		, tx_read_index(0)
		, m_sending(false)
	{
		for (std::size_t i = 0; i < max_instances; i++)
		{
			if (s_instances[i] == nullptr)
			{
				s_instances[i] = this;
				break;
			}
		}

		memset(tx_buffer, 0, sizeof(tx_buffer));
		memset(rx_buffer, 0, sizeof(rx_buffer));
		rx_data = 0;
		rx_write_index = 0;
		rx_read_index = 0;
	}
	UART::~UART()
	{
		for (std::size_t i = 0; i < max_instances; i++)
		{
			if (s_instances[i] == this)
			{
				s_instances[i] = nullptr;
				break;
			}
		}
		delete[] rx_buffer;
		delete[] tx_buffer;
	}
	void UART::setup()
	{
		VMB_HAL_UART_Receive_IT(static_cast<VMB_UART_Handle*>(uart), &rx_data, 1);
	}

	void UART::send(const char* str)
	{
		send((uint8_t*)str, strlen(str));
	}
	void UART::send(uint8_t* data, uint16_t size)
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
		//VMB_HAL_UART_Transmit(static_cast<VMB_UART_Handle*>(uart), tx_buffer, size, 100);
		//VMB_HAL_UART_Transmit_IT(static_cast<VMB_UART_Handle*>(uart), tx_buffer, size);
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
			VMB_HAL_UART_Transmit_IT(static_cast<VMB_UART_Handle*>(uart), &tx_buffer[index], 1);
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

	void UART::flush()
	{
		rx_write_index = 0;
		rx_read_index = 0;
		tx_write_index = 0;
		tx_read_index = 0;
		m_sending = false;
		memset(rx_buffer, 0, sizeof(rx_buffer));
		memset(tx_buffer, 0, sizeof(tx_buffer));
	}

	

	void UART::onITReceivedData(void* huart)
	{
		for (std::size_t i = 0; i < max_instances; i++)
		{
			if (s_instances[i] != nullptr && s_instances[i]->uart == huart)
			{
				s_instances[i]->onITReceivedData();
				return;
			}
		}
	}
	void UART::onITByteSent(void* huart)
	{
		for (std::size_t i = 0; i < max_instances; i++)
		{
			if (s_instances[i] != nullptr && s_instances[i]->uart == huart)
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
		VMB_HAL_UART_Receive_IT(static_cast<VMB_UART_Handle*>(uart), &rx_data, 1);
	}
	void UART::onITByteSent()
	{
		if (tx_write_index != tx_read_index) // Buffer overflow
		{
			uint16_t index = tx_read_index;
			tx_read_index = (tx_read_index + 1) % m_bufferSize; // Overwrite the oldest data
			VMB_HAL_UART_Transmit_IT(static_cast<VMB_UART_Handle*>(uart), &tx_buffer[index], 1);
		}
		else
			m_sending = false;
	}
}




// Called when one byte is received
void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart)
{
	VoiceMailBox::UART::onITReceivedData(huart);
}
void HAL_UART_TxCpltCallback(UART_HandleTypeDef* huart)
{
	VoiceMailBox::UART::onITByteSent(huart);
}




