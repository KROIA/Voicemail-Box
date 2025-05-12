#ifndef UART_HPP
#define UART_HPP

#include <stdint.h>
#include <cstdarg>


namespace VoiceMailBox
{
	struct UART
	{
		//static constexpr std::size_t buffer_size = 256;

		void* uart;		// UART_HandleTypeDef*

		UART(void* uartHandle, std::size_t bufferSize);
		~UART();
		void setup();

		void send(const char* str);
		void send(uint8_t* data, uint16_t size);

		uint16_t hasBytesReceived() const;
		bool receive(uint8_t* data, uint16_t size);
		//void receive(uint8_t* data, uint16_t size, uint32_t timeout);

		// Timeout in ms
		void waitUntil(char character, uint32_t timeoutMS = 0xFFFFFFFF); // Wait until a character is received (blocking)
		void waitUntil(const char* str, uint32_t timeoutMS = 0xFFFFFFFF); // Wait until a string is received (blocking)
		void flush();

		bool isSending() const
		{
			return m_sending;
		}


		

		static void onITReceivedData(void* huart);
		static void onITByteSent(void* huart);


	private:
		void onITReceivedData();
		void onITByteSent();

		std::size_t m_bufferSize;

		// RX buffer
		uint8_t *rx_buffer;
		uint8_t rx_data;
		uint16_t rx_write_index;
		uint16_t rx_read_index;

		uint8_t *tx_buffer;
		uint16_t tx_write_index;
		uint16_t tx_read_index;
		volatile bool m_sending;

		// The list of instances is used to distribute the interrupts received on the peripheral
		static constexpr std::size_t max_instances = 20; // Maximum number of UART instances
		static UART* s_instances[max_instances]; // Array can hold instances of UART
	};
}
#endif
