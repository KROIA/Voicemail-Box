#include "utilities/Logger.hpp"
#include "BSP_VoiceMailBox.hpp"
#include <cstdarg>   // <-- required for va_list and related macros
#include <cstdio>    // <-- required for vsnprintf
#include <cstring>

namespace VoiceMailBox
{
	Logger::Logger(const std::string& context)
		: m_context(context)
		, m_enabled(true)
	{
	}
	Logger::~Logger()
	{
	}

	void Logger::log(const std::string& msg)
	{
		if (!m_enabled)
			return;
		print("%s", msg.c_str());
	}
	void Logger::log(const char* str, ...)
	{
		if (!m_enabled)
			return;
		va_list args;
		va_start(args, str);

		char buffer[256];
		int len = vsnprintf(buffer, sizeof(buffer), str, args);

		if (len > 0 && len < sizeof(buffer))
		{
			print(("[" + m_context + "] %s").c_str(), buffer);
		}
		va_end(args);
	}

	void Logger::logln(const std::string& msg)
	{
		if (!m_enabled)
			return;
		print(("[" + m_context + "] %s\r\n").c_str(), msg.c_str());
	}
	void Logger::logln(const char* str, ...)
	{
		if (!m_enabled)
			return;
		va_list args;
		va_start(args, str);

		char buffer[256];
		int len = vsnprintf(buffer, sizeof(buffer), str, args);

		if (len > 0 && len < sizeof(buffer))
		{
			print(("[" + m_context + "] %s\r\n").c_str(), buffer);
		}
		va_end(args);
	}

}
