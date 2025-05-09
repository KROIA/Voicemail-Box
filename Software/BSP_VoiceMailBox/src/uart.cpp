#include "uart.hpp"
#include "main.h"
#include <string>
#include <cstring>

namespace VoiceMailBox
{
	UART::UART(void* uartHandle)
		: uart(uartHandle)
	{
		memset(tx_buffer, 0, sizeof(tx_buffer));
		memset(rx_buffer, 0, sizeof(rx_buffer));
#if UART_USE_RX_DMA == 1
		current_RX_Buffer = rx_buffer[0];
		bufferSwitcher = 1;
		dataSize = 0;
#else
		rx_data = 0;
		rx_write_index = 0;
		rx_read_index = 0;
#endif
	}
	void UART::setup()
	{
#if UART_USE_RX_DMA == 1
		HAL_UARTEx_ReceiveToIdle_DMA(static_cast<UART_HandleTypeDef*>(uart), current_RX_Buffer, buffer_size);
#else
		HAL_UART_Receive_IT(static_cast<UART_HandleTypeDef*>(uart), &rx_data, 1);
#endif
	}

	void UART::send(const char* str)
	{
		send((uint8_t*)str, strlen(str));
	}
	void UART::send(uint8_t* data, uint16_t size)
	{
		if (size > buffer_size)
		{
			size = buffer_size;
		}
		if (data == nullptr)
		{
			return;
		}
		memcpy(tx_buffer, data, size);
#if UART_USE_TX_DMA == 1
		HAL_UART_Transmit_DMA(static_cast<UART_HandleTypeDef*>(uart), tx_buffer, size);
#else
		HAL_UART_Transmit_IT(static_cast<UART_HandleTypeDef*>(uart), tx_buffer, size);
#endif
	}

	uint16_t UART::hasBytesReceived()
	{
#if UART_USE_RX_DMA == 1
		return dataSize;
#else
		return rx_write_index - rx_read_index;
#endif
	}
	bool UART::receive(uint8_t* data, uint16_t size)
	{
		if (data == nullptr)
		{
			return false;
		}
#if UART_USE_RX_DMA == 1
		if (dataSize == 0)
		{
			return false;
		}
		if (size > dataSize)
		{
			size = dataSize;
		}

		memcpy(data, current_RX_Buffer, size);
		dataSize = 0;
		return true;
#else
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
			data[i] = rx_buffer[(rx_read_index + i) % buffer_size];
		}
		rx_read_index = (rx_read_index + size) % buffer_size; // Update read index
		return true;
#endif
	}
	//void UART::receive(uint8_t* data, uint16_t size, uint32_t timeout)
	//{
	//	HAL_UART_Receive(static_cast<UART_HandleTypeDef*>(uart), data, size, timeout);
	//}
#if UART_USE_RX_DMA == 1
	void UART::onDMAReceivedData(uint16_t size)
	{
		uint8_t* nextBuffer = rx_buffer[bufferSwitcher];
		bufferSwitcher = !bufferSwitcher;

		HAL_UARTEx_ReceiveToIdle_DMA(static_cast<UART_HandleTypeDef*>(uart), nextBuffer, buffer_size);
		//HAL_UART_Receive_DMA(static_cast<UART_HandleTypeDef*>(uart), nextBuffer, buffer_size);
		dataSize = size;
		//dataReceived = true;
		current_RX_Buffer = rx_buffer[bufferSwitcher];
	}
#else
	void UART::onITReceivedData()
	{
		// Circular buffer implementation
		rx_buffer[rx_write_index] = rx_data;
		rx_write_index = (rx_write_index + 1) % buffer_size;


		if (rx_write_index == rx_read_index) // Buffer overflow
		{
			rx_read_index = (rx_read_index + 1) % buffer_size; // Overwrite the oldest data
		}
		HAL_UART_Receive_IT(static_cast<UART_HandleTypeDef*>(uart), &rx_data, 1);
	}
#endif
}




