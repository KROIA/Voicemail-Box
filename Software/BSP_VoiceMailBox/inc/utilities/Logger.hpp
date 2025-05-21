#ifndef LOGGER_HPP
#define LOGGER_HPP
/**
 * @brief
 * @details
 *
 * @author Alex Krieg
 */

#include <string>
#include "settings.h"

namespace VoiceMailBox
{
	class Logger
	{
	public:
		Logger(const std::string& context);
		virtual ~Logger();

		void enableLogging(bool enable) { m_enabled = enable; }
		bool isLoggingEnabled() const { return m_enabled; }

		void log(const std::string& msg);
		void log(const char* str, ...);

		void logln(const std::string& msg);
		void logln(const char* str, ...);


	private:
		std::string m_context;
		bool m_enabled;
	};
}
#endif