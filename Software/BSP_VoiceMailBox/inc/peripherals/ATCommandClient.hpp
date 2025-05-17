#ifndef ATCOMMAND_CLIENT_H
#define ATCOMMAND_CLIENT_H

#include "HAL_abstraction.hpp"
#include "uart.hpp"
#include "File.hpp"
#include <string>
#include <cstdlib>
#include <memory>
#include <cstddef>
#include <iostream>
#include <cassert>
#include <new>

namespace VoiceMailBox
{

	template <typename T, std::size_t Alignment>
	struct AlignedAllocator {
		using value_type = T;

		AlignedAllocator() noexcept = default;

		template <typename U>
		AlignedAllocator(const AlignedAllocator<U, Alignment>&) noexcept {}

		T* allocate(std::size_t n) noexcept {
			std::size_t size = n * sizeof(T);
			std::uintptr_t raw = reinterpret_cast<std::uintptr_t>(std::malloc(size + Alignment + sizeof(void*)));
			if (!raw) return nullptr;

			std::uintptr_t aligned = (raw + sizeof(void*) + Alignment - 1) & ~(Alignment - 1);
			reinterpret_cast<void**>(aligned)[-1] = reinterpret_cast<void*>(raw);
			return reinterpret_cast<T*>(aligned);
		}

		void deallocate(T* p, std::size_t) noexcept {
			if (p) {
				void* raw = reinterpret_cast<void**>(p)[-1];
				std::free(raw);
			}
		}

		template <typename U>
		struct rebind {
			using other = AlignedAllocator<U, Alignment>;
		};
	};

	template <class T, class U, std::size_t A1, std::size_t A2>
	bool operator==(const AlignedAllocator<T, A1>&, const AlignedAllocator<U, A2>&) { return A1 == A2; }

	template <class T, class U, std::size_t A1, std::size_t A2>
	bool operator!=(const AlignedAllocator<T, A1>&, const AlignedAllocator<U, A2>&) { return !(A1 == A2); }

	using AlignedString = std::basic_string<char, std::char_traits<char>, AlignedAllocator<char, 4>>;


	class ATCommandClient
	{
	public:
		ATCommandClient(VMB_UART_Handle* uartHandle, uint16_t uartBufferSize);
		~ATCommandClient();

		void setup();


		/**
		 * @brief Sends a command to the AT command client.
		 *		  The command must not include the terminating CRLF.
		 * @param command 
		 */
		bool sendCommand(const std::string &command);
		bool sendCommand(const char* command);
		bool sendBytes(const uint8_t* data, uint16_t size);

		bool waitUntil(const char* response, uint32_t timeout = 5000);

		bool hasResponse() const
		{
			return m_uart.hasBytesReceived() > 0;
		}

		bool getResponse(uint8_t* data, uint16_t size)
		{
			return m_uart.receive(data, size);
		}
		


		bool doesRespond();


		bool connectToWifi(const std::string& ssid, const std::string& password);
		bool sendFileToServer(const std::string& localFileName, const std::string& urlPath, const std::string& serverIP, uint16_t serverPort);
		bool downloadFileFromServer(const std::string& localFileName, const std::string& urlPath, const std::string& serverIP, uint16_t serverPort);


		

	private:
		bool readFileDownloadResponse(std::string& response, uint32_t timeout);

		enum class DownloadState {
			ExtractingHeaderData,
			ParsingStartOfFile,
			ParsingFile
		};
		struct DownloadData
		{
			DownloadState state;
			uint32_t contentLength;
			uint32_t contentReceived;
			std::string fileName;
			bool fileComplete;
			File file;
		};
		bool processFrame(DownloadData& data, uint8_t* frame, uint32_t size);

		bool convertToUInt16(const std::string& str, uint16_t& outValue);
		bool convertToUInt32(const std::string& str, uint32_t& outValue);
		void log(const std::string &msg);

		UART m_uart;
		bool m_enableLogging = true;

	};
}
#endif
