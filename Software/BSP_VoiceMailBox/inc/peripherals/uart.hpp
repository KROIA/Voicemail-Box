#ifndef UART_HPP
#define UART_HPP
/**
 * @brief UART abstraction class
 * @details This class provides an interface to the UART peripheral of the STM32 microcontroller.
 *          It implements a circular buffer for RX and TX data.
 * @author Alex Krieg
 */



#include "HAL_abstraction.hpp"
#include <atomic>

namespace VoiceMailBox
{
	class UART
	{
	public:
		/**
		 * @brief Constructor
		 * @param uartHandle HAL handle for the UART peripheral
		 * @param bufferSize Size of the circular buffer in bytes
		 *                   The size is only used when the VMB_UART_USE_STATIC_BUFFER_SIZE macro is not defined
		 */
		UART(VMB_UART_Handle* uartHandle, uint16_t bufferSize);
		~UART();

		/**
		 * @brief Starts the UART peripherals revceiver interrupt.
		 * @return true if VMB_HAL_UART_Receive_IT was successful, false otherwise.
		 */
		bool setup();

		/**
		 * @brief Sends the given string over UART.
		 *        Expecting a null-terminated string.
		 * @param str 
		 */
		void send(const char* str);

		/**
		 * @brief Sends the given array of bytes over UART.
		 * @param data pointer to the array of bytes to send
		 * @param size amount of bytes to send
		 */
		void send(const uint8_t* data, uint32_t size);

		/**
		 * @brief Returns the amount of bytes what have been received and not yet read.
		 * @return number of unread bytes in the RX buffer
		 */
		uint32_t hasBytesReceived() const;

		/**
		 * @brief Reads the given amount of bytes from the RX buffer.
		 * @details This function will not block until the requested amount of bytes is received.
		 *          It will read the min(size, hasBytesReceived()) bytes from the RX buffer.
		 * @param data buffer to store the read bytes
		 * @param size target amount of bytes to read
		 * @return amount of bytes read from the RX buffer
		 */
		uint32_t receive(uint8_t* data, uint32_t size);

		/**
		 * @brief Reads all bytes from the RX buffer until the target string is found or the timeout is reached or the <data> buffer is full.
		 * @param data buffer to store the read bytes
		 * @param size of the <data> buffer
		 * @param target string to search for in the RX buffer
		 * @param targetSize of the <target> string
		 * @param timeoutMS to stop waiting for the target string
		 * @return amount of bytes read from the RX buffer
		 * 
		 * @details This function will block until the target string has been found or the timeout has been reached.
		 *          If the <data> buffer is full, the function will no longer wait for the target string.
		 */
		uint32_t receiveUntil(uint8_t* data, uint32_t size, uint8_t* target, uint32_t targetSize, uint32_t timeoutMS = 0xFFFFFFFF);

		/**
		 * @brief Waits until the given character is received or the timeout is reached.
		 * @param character target character to wait for
		 * @param timeoutMS timeout in milliseconds
		 * @return true if the character was received, false if the timeout was reached.
		 */
		bool waitUntil(char character, uint32_t timeoutMS = 0xFFFFFFFF); // Wait until a character is received (blocking)
		
		/**
		 * @brief Waits until the given string was found in the RX buffer or the timeout is reached.
		 * @param str to search for in the RX buffer
		 * @param timeoutMS timeout in milliseconds
		 * @return true if the string was found, false if the timeout was reached.
		 */
		bool waitUntil(const char* str, uint32_t timeoutMS = 0xFFFFFFFF); // Wait until a string is received (blocking)
		bool waitUntilAndFlush(const char* str, uint32_t timeoutMS = 0xFFFFFFFF); // Wait until a string is received (blocking)
		
		/**
		 * @brief Resets the Circular buffer counters and clears the RX and TX buffers.
		 */
		void flush();

		/**
		 * @brief Clears the RX buffer
		 */
		void flushRX();

		/**
		 * @brief Erases n bytes from the RX buffer
		 * @param nBytes amount of bytes to be flushed
		 * @return amount of bytes flushed (can be less than nBytes, 
		 *         because the buffer may not contain as many bytes as nBytes.
		 */
		uint32_t flushNBytes(uint32_t nBytes);

		/**
		 * @brief Gets the current status of a TX transfer.
		 * @return true if the UART is currently sending data, false otherwise.
		 */
		bool isSending() const
		{
			return m_sending;
		}

		/**
		 * @brief Gets the HAL handle for the UART peripheral.
		 * @return uart handle
		 */
		VMB_UART_Handle * const getHandle() { return m_uart; }

		/**
		 * @brief Gets the buffersize of the circular RX/TX Buffer
		 * @return buffersize
		 */
		uint32_t getBufferSize() const { return m_bufferSize; }
		

		/**
		 * @brief ISR callback from the HAL library calls this function to notify the UART instance
	     * @warning Do not call this function from any other function than the specific ISR.
		 * @param huart 
		 */
		static void onITReceivedData(VMB_UART_Handle* huart);

		/**
		 * @brief ISR callback from the HAL library calls this function to notify the UART instance
		 * @warning Do not call this function from any other function than the specific ISR.
		 * @param huart
		 */ 
		static void onITByteSent(VMB_UART_Handle* huart);


	private:
		bool waitUntil_internal(const char* str, uint32_t timeoutMS, uint32_t &startIndex);
		void onITReceivedData();
		void onITByteSent();

		VMB_UART_Handle * const m_uart;		// UART_HandleTypeDef*

		const uint32_t m_bufferSize;

		// RX buffer
#ifdef VMB_UART_USE_STATIC_BUFFER_SIZE
		uint8_t rx_buffer[VMB_UART_STATIC_BUFFER_SIZE];
		uint8_t tx_buffer[VMB_UART_STATIC_BUFFER_SIZE];
#else
		uint8_t *rx_buffer;
		uint8_t* tx_buffer;
#endif
		uint8_t rx_data;
		uint32_t rx_write_index;
		uint32_t rx_read_index;

		
		uint32_t tx_write_index;
		uint32_t tx_read_index;
		volatile bool m_sending;
		std::atomic<uint16_t> m_bytesToSend;

		// The list of instances is used to distribute the interrupts received on the peripheral
		static UART* s_instances[VMB_UART_MAX_INSTANCES]; // Array can hold instances of UART
	};
}
#endif
