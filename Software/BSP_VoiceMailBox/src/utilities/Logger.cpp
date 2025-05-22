#include "utilities/Logger.hpp"
#include "platform.hpp"
#include "settings.h"
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
		Platform::getDebugUART().send(("[" + m_context + "] ").c_str());
		Platform::getDebugUART().send(msg.c_str());
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
			Platform::getDebugUART().send(("[" + m_context + "] ").c_str());
			Platform::getDebugUART().send((uint8_t*)buffer, len);
		}
		va_end(args);
	}

	void Logger::logln(const std::string& msg)
	{
		if (!m_enabled)
			return;
		Platform::getDebugUART().send(("[" + m_context + "] ").c_str());
		Platform::getDebugUART().send(msg.c_str());
		Platform::getDebugUART().send("\r\n");
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
			Platform::getDebugUART().send(("[" + m_context + "] ").c_str());
			Platform::getDebugUART().send((uint8_t*)buffer, len);
			Platform::getDebugUART().send("\r\n");
		}

		va_end(args);
	}
#endif
}
