#ifndef LOGGER_HPP
#define LOGGER_HPP
/**
 * @brief
 * @details
 *
 * @author Alex Krieg
 */

#include <string>
#include "HAL_abstraction.hpp"

// Use these log macros inside a Logger derived class
// By using these macros, the logger can be disabled completly from the build
#ifdef VMB_USE_LOGGER_OBJECTS
	#define VMB_LOG(x, ...) Logger::log(x, ##__VA_ARGS__)
	#define VMB_LOGLN(x, ...) Logger::logln(x, ##__VA_ARGS__)
	#define VMB_LOGGER_ENABLE Logger::enableLogging(true)
	#define VMB_LOGGER_DISABLE Logger::enableLogging(false)

	#define VMB_LOGGER_PRINT(x, ...) Logger::print(x, ##__VA_ARGS__)
	#define VMB_LOGGER_PRINTLN(x, ...) Logger::println(x, ##__VA_ARGS__)

	#define VMB_LOGGER_HANDLE_STATUS(status, context) Logger::handleStatus(status, context)
#else
	#define VMB_LOG(x, ...) 
	#define VMB_LOGLN(x, ...) 
	#define VMB_LOGGER_ENABLE
	#define VMB_LOGGER_DISABLE

	#define VMB_LOGGER_PRINT(x, ...) 
	#define VMB_LOGGER_PRINTLN(x, ...) 

	#define VMB_LOGGER_HANDLE_STATUS(status, context) 
#endif

namespace VoiceMailBox
{
#ifdef VMB_USE_LOGGER_OBJECTS
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

		static void print(const std::string& msg);
		static void print(const char* str, ...);

		static void println(const std::string& msg);
		static void println(const char* str, ...);

		static void handleStatus(VMB_HAL_Status status, const std::string& context = "");
	private:
		std::string m_context;
		bool m_enabled;
	};
#else
	namespace Logger
	{
		void print(const std::string& msg);
		void print(const char* str, ...);

		void println(const std::string& msg);
		void println(const char* str, ...);

		static void handleStatus(VMB_HAL_Status status, const std::string& context = "");
	}
#endif
}
#endif