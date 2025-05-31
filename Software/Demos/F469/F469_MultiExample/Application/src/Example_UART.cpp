#include "Example_UART.hpp"
#include "BSP_VoiceMailBox.hpp"
#include "main.h"
#include <memory>

namespace Example_UART
{
    /**
	 * @brief Example on how to use the UART class to send and receive data.
	 * @details
	 * This example sends some simple text or byte arrays over the UART interface
	 * The UART can also wait for a specific string to be received or read until a target string is found.
     */

    VoiceMailBox::UART uart(getUART_DEBUG(), 1024);

    void setup()
    {
        uart.setup();
    }

    // Called periodically
    void loop()
    {
        // Sends a '\0' terminated string over uart.
        // The '\0' will not be sent!
        // The compiler will implicitly add the '\0' at the end of "Hello World\r\n". 
        uart.send("Hello World\r\n");

        // Sends non character bytes using a array and its length in bytes.
        uint8_t data[5] = { 65, 66, 67, '\r', '\n' };
        uart.send(data, sizeof(data));

        // This reads the number of bytes currently received in the buffer and ready to be read
        uint32_t available = uart.hasBytesReceived();

        uint8_t readBuff[1024] = { 0 };
        uart.receive(readBuff, available);
        uart.send(std::string("1: readBuff: \"" + std::string((const char*)readBuff) + "\"\r\n").c_str());
        memset(readBuff, 0, sizeof(readBuff)); // Clear the buffer

        // Waits until the target string was found or the timeout was reached
        if (uart.waitUntil("Target1", 5000))
        {
            // "Target1" was found in the RX buffer
        	uart.send("Target1 was found\r\n");
        }
        else
        {
            // "Target" was never received or the timeout of 5000ms is reached
        	uart.send("Target1 was not found, timeout\r\n");
        }

        // Waits until the target string was found or timeout was reached. 
        // If the target was found, it flushes all bytes 
        // received to the end index of the found target string
        if (uart.waitUntilAndFlush("Target1", 5000))
        {
            // "Target" was found in the RX buffer and flushed
        }
        else
        {
            // "Target" was never received or the timeout of 5000ms is reached
        	uart.send("Target1 was not found, timeout\r\n");
        }

        // Receives all bytes that are comming until the Target string was received or the timeout was reached or the readBuff is full.
        uint32_t received = uart.receiveUntil(readBuff, sizeof(readBuff), (uint8_t*)"Target2", 7, 5000);
        // Example:
        // RX Buffer inside the uart object:
        // |"BlaBlaBlaTest        "|
        //   ^            ^
        //   |            |
        //  Tail         Head
        //
        // readBuff will contain the string: "BlaBlaBla"
        //
        uart.send(std::string("2: readBuff: \"" + std::string((const char*)readBuff) + "\"\r\n").c_str());
    }
} 
