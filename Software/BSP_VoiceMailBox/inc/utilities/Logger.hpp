#ifndef LOGGER_HPP
#define LOGGER_HPP
/**
 * @author Alex Krieg
 */

#include <string>
#include "HAL_abstraction.hpp"

// Use these log macros inside a Logger derived class
// By using these macros, the logger can be disabled completly from the build
#ifdef VMB_USE_LOGGER_OBJECTS
	#define VMB_LOG(x, ...) Logger::log(x, ##__VA_ARGS__)
	#define VMB_LOGLN(x, ...) Logger::logln(x, ##__VA_ARGS__)
	#define VMB_LOGGER_LOG_STATUS(status, context) Logger::logStatus(status, context)
	#define VMB_LOGGER_ENABLE Logger::enableLogging(true)
	#define VMB_LOGGER_DISABLE Logger::enableLogging(false)

	#define VMB_LOGGER_IS_ENABLED Logger::isLoggingEnabled()

	#define VMB_LOGGER_PRINT(x, ...) Logger::print(x, ##__VA_ARGS__)
	#define VMB_LOGGER_PRINTLN(x, ...) Logger::println(x, ##__VA_ARGS__)
	#define VMB_LOGGER_PRINT_STATUS(status, context) Logger::printStatus(status, context)
#else
	#define VMB_LOG(x, ...) 
	#define VMB_LOGLN(x, ...) 
	#define VMB_LOGGER_LOG_STATUS(status, context)
	#define VMB_LOGGER_ENABLE
	#define VMB_LOGGER_DISABLE

	#define VMB_LOGGER_IS_ENABLED false

	#define VMB_LOGGER_PRINT(x, ...) 
	#define VMB_LOGGER_PRINTLN(x, ...) 
	#define VMB_LOGGER_PRINT_STATUS(status, context) 
#endif

namespace VoiceMailBox
{
#ifdef VMB_USE_LOGGER_OBJECTS
	/**
	 * @brief The Logger class privides a interface to log messages to the debug console.
	 * @details
	 * Using this class as a baseclass for othet objects allows logging easy
	 * It does not only print the messages to the console, it also puts a "context" related string in front of each message.
	 * This makes it easier to identify the source of the message when reading the console output.
	 *
	 * Use the class using the macros below because the whole logger can be disabled from the build and
	 * to prevent compiler error because of missing functions, the macros will be replaced with empty functions when the logger is disabled.
	 */
	class Logger
	{
	public:
		/**
		 * @brief Constructor
		 * @param context is a text that will appear in front of each log message.
		 */
		Logger(const std::string& context);
		virtual ~Logger();

		/**
		 * @brief Enables or disables the logging functionality.
		 * @details If logging is disabled, the log message will not appear in the console.
		 *          The function call and the text will still exist in the binary. 
		 *          For Release builds which do not need any logging, the logger can be disabled in the settings.h
		 *          This will remove all logging functionality from the binary.
		 * @param enable 
		 */
		void enableLogging(bool enable) { m_enabled = enable; }

		/**
		 * @brief 
		 * @return 
		 */
		bool isLoggingEnabled() const { return m_enabled; }

		/**
		 * @brief Print a message to the console.
		 * @param msg to be printed
		 */
		void log(const std::string& msg);

		/**
		 * @brief Print a message to the console.
		 * @param str to be printed
		 * @param [in]... variable arguments to be formatted into the string
		 */
		void log(const char* str, ...);

		/**
		 * @brief Print a message to the console and add a newline at the end.
		 * @param msg to be printed
		 */
		void logln(const std::string& msg);

		/**
		 * @brief Print a message to the console and add a newline at the end.
		 * @param str to be printed
		 * @param [in]... variable arguments to be formatted into the string
		 */
		void logln(const char* str, ...);

		/**
		 * @brief Prints the result of a HAL function call.
		 * @param status used to print the correct result message.
		 * @param context that can be used to specify in which context the status value was generated from
		 *
		 * @note Each status value can be enabled/disabled indivually in the settings.h file.
		 */
		void logStatus(VMB_HAL_Status status, const std::string& context = "");






		/**
		 * @brief Prints a message to the console without any context string.
		 * @param msg to be printed
		 */
		static void print(const std::string& msg);

		/**
		 * @brief Print a message to the console without any context string.
		 * @param str to be printed
		 * @param [in]... variable arguments to be formatted into the string
		 */
		static void print(const char* str, ...);

		/**
		 * @brief Print a message to the console without any context string and add a newline at the end.
		 * @param msg to be printed
		 */
		static void println(const std::string& msg);

		/**
		 * @brief Print a message to the console without any context string and add a newline at the end.
		 * @param str to be printed
		 * @param [in]... variable arguments to be formatted into the string
		 */
		static void println(const char* str, ...);

		/**
		 * @brief Prints the result of a HAL function call.
		 * @param status used to print the correct result message.
		 * @param context that can be used to specify in which context the status value was generated from
		 * 
		 * @note Each status value can be enabled/disabled indivually in the settings.h file.
		 */
		static void printStatus(VMB_HAL_Status status, const std::string& context = "");
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

		void printStatus(VMB_HAL_Status status, const std::string& context = "");
	}
#endif
}
#endif
