#include "Example_Logger.hpp"
#include "BSP_VoiceMailBox.hpp"

namespace Example_Logger
{
	/**
	 * @brief Simple console logging using the static Logger methodes.
	 */
	void staticLogging();


	/**
	 * @brief Creating a derived class from the Logger class and using the object logging macros.
	 */
	void derivedClass();
	
	


	

// ------------------------------------------------------------------------------------------------
// ================================================================================================
// ------------------------------------------------------------------------------------------------
	void setup()
	{
		VoiceMailBox::setup();
		staticLogging();
		derivedClass();
	}

	void loop()
	{
		VoiceMailBox::update();
	}






// ------------------------------------------------------------------------------------------------
// ================================================================================================
// ------------------------------------------------------------------------------------------------
	void staticLogging()
	{
		using namespace VoiceMailBox;
		
		Logger::print("Hello World!\r\n");
		Logger::println("This is a static logging example.");
		Logger::print("This is a static logging example with a number: %i\r\n", 15);
		Logger::println("This is a static logging example with a number: %i", 15);

		Logger::printStatus(VMB_HAL_Status::BUSY, "HAL_CALL_XY()");
	}





// ------------------------------------------------------------------------------------------------
// ================================================================================================
// ------------------------------------------------------------------------------------------------
	class TestObj
#ifdef VMB_USE_LOGGER_OBJECTS // Use this macro because if the macro is not defined, the Logger class does not exist and therefore can not be derived from
		: public VoiceMailBox::Logger
#endif
	{
	public:
		TestObj()
	#ifdef VMB_USE_LOGGER_OBJECTS // Also use the macro here because of the same reason as above
			: Logger("TestObj")   // Pass the context string to the constructor of the Logger object
	#endif
		{}

		void someFunction()
		{
			// Use these macros to be able to disable logging in production code using the settings.h
			VMB_LOG("Hello World!\r\n");
			VMB_LOGLN("This is a object logging example.");
			VMB_LOG("This is a object logging example with a number: %i\r\n", 15);
			VMB_LOGLN("This is a object logging example with a number: %i", 15);

			VMB_LOGGER_LOG_STATUS(VoiceMailBox::VMB_HAL_Status::BUSY, "HAL_CALL_XY()");
		}
	};

	void derivedClass()
	{
		TestObj testObj;
		testObj.someFunction();
	}
} 
