# Logger
The Logger class provides two ways on how debug messages can be printed to the console.
The Logger can be used with its static methodes or as a baseclass for derived objects. 

## Content
- [Features](#features)
- [Setup](#setup)
- [Usage](#usage)
  - [Static usage](#static-usage)
  - [Usage in a derived class](#usage-in-a-derived-class)

---
## Features
- Static Logging to the debug console without the usage of a Logger object
- Logger object to enable a additional context string before each debug message
- Variadic parameter usage is supported


---
## Setup    
Follow the setup for the [UART](UART.md). For the F469 it is UART3.
Make sure the C++ application is setup in order to use this class
You can find the instructions on how to do so [here](CppFromC.md).

---
## Usage
### Static usage
The logger can be used with static function calls. 
Below is a simple example for that case
``` C++ 
// Application.cpp
#include "BSP_VoiceMailBox.hpp" // includes "peripherals/i2s.hpp"

void setup()
{
    VoiceMailBox::setup();
    using namespace VoiceMailBox;

    Logger::print("Hello World!\r\n");
    Logger::println("This is a static logging example.");
    Logger::print("This is a static logging example with a number: %i\r\n", 15);
    Logger::println("This is a static logging example with a number: %i", 15);

    Logger::printStatus(VMB_HAL_Status::BUSY, "HAL_CALL_XY()");


    // When these macros are used instead, the messages can be deactivated and removed from the build
    // depending on a setting in the settings.h
    // This is usefull for adding debug messages in the code which need to be removed for production compilation.
    VMB_LOGGER_PRINT("Hello World!\r\n");
    VMB_LOGGER_PRINTLN("This is a static logging example.");
    VMB_LOGGER_PRINT("This is a static logging example with a number: %i\r\n", 15);
    VMB_LOGGER_PRINTLN("This is a static logging example with a number: %i", 15);

    VMB_LOGGER_PRINT_STATUS(VMB_HAL_Status::BUSY, "HAL_CALL_XY()");
}
```

This code produces the console output:
```
Hello World!
This is a static logging example.
This is a static logging example with a number: 15
This is a static logging example with a number: 15
Device is busy in HAL_CALL_XY()
Hello World!
This is a static logging example.
This is a static logging example with a number: 15
This is a static logging example with a number: 15
Device is busy in HAL_CALL_XY()
```

---
### Usage in a derived class
A object can derive from the Logger class. This has the benefit that on construction a context string can be passed to the Logger constructor.
That context string gets used on every print call in the beginning.
``` C++ 
// Application.cpp
#include "BSP_VoiceMailBox.hpp" // includes "peripherals/i2s.hpp"

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

void setup()
{
    VoiceMailBox::setup();
    using namespace VoiceMailBox;

    TestObj testObj;
    testObj.someFunction();
}
```

This code produces the console output:
```
[TestObj] Hello World!
[TestObj] This is a object logging example.
[TestObj] This is a object logging example with a number: 15
[TestObj] This is a object logging example with a number: 15
[TestObj] Device is busy in HAL_CALL_XY()
```