#ifndef UART_HPP
#define UART_HPP

#include <stdint.h>
#include <cstdarg>


namespace VoiceMailBox
{
	struct UART
	{
		static constexpr std::size_t buffer_size = 256;
#define UART_USE_TX_DMA 0
#define UART_USE_RX_DMA 0

		void* uart;		// UART_HandleTypeDef*

		UART(void* uartHandle);
		~UART();
		void setup();

		void send(const char* str);
		void send(uint8_t* data, uint16_t size);

		uint16_t hasBytesReceived();
		bool receive(uint8_t* data, uint16_t size);
		//void receive(uint8_t* data, uint16_t size, uint32_t timeout);


#if UART_USE_RX_DMA == 1
		void onDMAReceivedData(uint16_t size);
#else
		void onITReceivedData();
#endif


#if UART_USE_RX_DMA == 1
		static void onDMAReceivedData(void* huart, uint16_t Size);
#else
		static void onITReceivedData(void* huart);
#endif

	private:

#if UART_USE_RX_DMA == 1
		uint8_t rx_buffer[2][buffer_size];
		uint16_t dataSize = 0;
		uint8_t* current_RX_Buffer = nullptr;
		bool bufferSwitcher;
#else
		uint8_t rx_buffer[buffer_size];
		uint8_t rx_data;
		uint16_t rx_write_index;
		uint16_t rx_read_index;
#endif
		uint8_t tx_buffer[buffer_size];

		// The list of instances is used to distribute the interrupts received on the peripheral
		static constexpr std::size_t max_instances = 20; // Maximum number of UART instances
		static UART* s_instances[max_instances]; // Array can hold instances of UART
	};
}
#endif
