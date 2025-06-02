#include "utilities/Logger.hpp"
#include "platform.hpp"
#include <cstdarg>   // <-- required for va_list and related macros
#include <cstdio>    // <-- required for vsnprintf
#include <cstring>

namespace VoiceMailBox
{
#ifdef VMB_USE_LOGGER_OBJECTS
	Logger::Logger(const std::string& context)
		: m_context(context)
#ifdef VMB_LOGGER_OBJECTS_ENABLED_BY_DEFAULT
		, m_enabled(true)
#else
		, m_enabled(false)
#endif
	{
	}
	Logger::~Logger()
	{
	}


	void Logger::log(const std::string& msg)
	{
		if (!m_enabled)
			return;
		print("[" + m_context + "] " + msg);
	}
	void Logger::log(const char* str, ...)
	{
		if (!m_enabled)
			return;
		va_list args;
		va_start(args, str);

		char buffer[256];
		int len = vsnprintf(buffer, sizeof(buffer), str, args);

		if (len > 0 && len < (int)sizeof(buffer))
		{
			print("[" + m_context + "] ");
			print(buffer);
		}
		va_end(args);
	}

	void Logger::logln(const std::string& msg)
	{
		if (!m_enabled)
			return;
		println("[" + m_context + "] " + msg);
	}
	void Logger::logln(const char* str, ...)
	{
		if (!m_enabled)
			return;
		va_list args;
		va_start(args, str);

		char buffer[256];
		int len = vsnprintf(buffer, sizeof(buffer), str, args);

		if (len > 0 && len < (int)sizeof(buffer))
		{
			print("[" + m_context + "] ");
			println(buffer);
		}
		va_end(args);
	}

	void Logger::logStatus(VMB_HAL_Status status, const std::string& context)
	{
		switch (status)
		{
		case VMB_HAL_Status::OK:
#ifdef VMB_LOGGER_ENABLE_STATUS_PRINT_OK
			logln("Status OK " + (context.empty() ? "" : " in " + context));
#endif
			break;
		case VMB_HAL_Status::ERROR:
#ifdef VMB_LOGGER_ENABLE_STATUS_PRINT_ERROR
			logln("Error occurred" + (context.empty() ? "" : " in " + context));
#endif
			break;
		case VMB_HAL_Status::BUSY:
#ifdef VMB_LOGGER_ENABLE_STATUS_PRINT_BUSY
			logln("Device is busy" + (context.empty() ? "" : " in " + context));
#endif
			break;
		case VMB_HAL_Status::TIMEOUT:
#ifdef VMB_LOGGER_ENABLE_STATUS_PRINT_TIMEOUT
			logln("Operation timed out" + (context.empty() ? "" : " in " + context));
#endif
			break;
		default:
#ifdef VMB_LOGGER_ENABLE_STATUS_PRINT_UNKNOWN
			logln("Unknown status: " + std::to_string(static_cast<int>(status)) + (context.empty() ? "" : " in " + context));
#endif
			break;
		}
	}

#endif

	void Logger::print(const std::string& msg)
	{
		Platform::getDebugUART().send(msg.c_str());
	}
	void Logger::print(const char* str, ...)
	{
		va_list args;
		va_start(args, str);

		char buffer[256];
		int len = vsnprintf(buffer, sizeof(buffer), str, args);

		if (len > 0 && len < (int)sizeof(buffer))
		{
			Platform::getDebugUART().send((uint8_t*)buffer, len);
		}
		va_end(args);
	}

	void Logger::println(const std::string& msg)
	{
		Platform::getDebugUART().send((msg + "\r\n").c_str());
	}
	void Logger::println(const char* str, ...)
	{
		va_list args;
		va_start(args, str);

		char buffer[256];
		int len = vsnprintf(buffer, sizeof(buffer), str, args);

		if (len > 0 && len < (int)sizeof(buffer))
		{
			Platform::getDebugUART().send((uint8_t*)buffer, len);
			Platform::getDebugUART().send("\r\n");
		}
		va_end(args);
	}

	void Logger::printStatus(VMB_HAL_Status status, const std::string& context)
	{
		switch (status)
		{
		case VMB_HAL_Status::OK:
#ifdef VMB_LOGGER_ENABLE_STATUS_PRINT_OK
			println("Status OK " + (context.empty() ? "" : " in " + context));
#endif
			break;
		case VMB_HAL_Status::ERROR:
#ifdef VMB_LOGGER_ENABLE_STATUS_PRINT_ERROR
			println("Error occurred" + (context.empty() ? "" : " in " + context));
#endif
			break;
		case VMB_HAL_Status::BUSY:
#ifdef VMB_LOGGER_ENABLE_STATUS_PRINT_BUSY
			println("Device is busy" + (context.empty() ? "" : " in " + context));
#endif
			break;
		case VMB_HAL_Status::TIMEOUT:
#ifdef VMB_LOGGER_ENABLE_STATUS_PRINT_TIMEOUT
			println("Operation timed out" + (context.empty() ? "" : " in " + context));
#endif
			break;
		default:
#ifdef VMB_LOGGER_ENABLE_STATUS_PRINT_UNKNOWN
			println("Unknown status: " + std::to_string(static_cast<int>(status)) + (context.empty() ? "" : " in " + context));
#endif
			break;
		}
	}
}
