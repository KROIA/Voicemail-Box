#include "BSP_VoiceMailBox.hpp"
#include "platform.hpp"

#include <cstdarg>   // <-- required for va_list and related macros
#include <cstdio>    // <-- required for vsnprintf
#include <cstring>

namespace VoiceMailBox
{
	void setup()
	{
		Platform::setup(); // Call the platform-specific setup function
	}


	DigitalPin& getLed(LED led)
	{
		return Platform::led[static_cast<int>(led)];
	}
	void setLed(LED led, bool on)
	{
		Platform::led[static_cast<int>(led)].set(on);
	}
	void toggleLed(LED led)
	{
		Platform::led[static_cast<int>(led)].toggle();
	}

	DigitalPin& getButton(Button button)
	{
		return Platform::button[static_cast<int>(button)];
	}
	bool getButtonState(Button button)
	{
		return Platform::button[static_cast<int>(button)].get();
	}

	AnalogPin& getPoti(Poti poti)
	{
		return Platform::adcPotis[static_cast<int>(poti)];
	}
	uint32_t getPotiValue(Poti poti)
	{
		return Platform::adcPotis[static_cast<int>(poti)].getValue();
	}
	uint32_t getPotiMaxValue(Poti poti)
	{
		return Platform::adcPotis[static_cast<int>(poti)].getMaxValue();
	}

	ATCommandClient& getPmodESP()
	{
		return Platform::pmodESP; // Return the ATCommandClient instance
	}


	Codec_TLV320AIC3104& getCodec()
	{
		return Platform::codec;
	}

#ifdef VMB_DEVELOPMENT_CONFIGURATION
	DigitalPin& getDbgPin(DBG_PIN pin)
	{
		return Platform::dbgPins[static_cast<int>(pin)];
	}
	void setDbgPin(DBG_PIN pin, bool on)
	{
		Platform::dbgPins[static_cast<int>(pin)].set(on);
	}
	void toggleDbgPin(DBG_PIN pin)
	{
		Platform::dbgPins[static_cast<int>(pin)].toggle();
	}
#endif




	void print(const char* str, ...)
	{
		va_list args;
		va_start(args, str);
		std::size_t size = Platform::dbgUart.getBufferSize();
		char* buffer = new char[size];
		vsnprintf(buffer, size, str, args);
		Platform::dbgUart.send((uint8_t*)buffer, strlen(buffer));
 		va_end(args);
		delete[] buffer;
	}
	void println(const char* str, ...)
	{
		va_list args;
		va_start(args, str);
		std::size_t buffSize = Platform::dbgUart.getBufferSize();
		char* buffer = new char[buffSize];
		std::size_t size = strlen(str);
		if (size > buffSize - 3) // Ensure there's space for newline characters
		{
			size = buffSize - 3; // Leave space for newline characters
		}
		vsnprintf(buffer, sizeof(buffer), str, args);

		buffer[size] = '\r'; // Add newline character
		buffer[size + 1] = '\n'; // Add newline character
		buffer[size + 2] = 0; // Add newline character
		Platform::dbgUart.send((uint8_t*)buffer, strlen(buffer));
		va_end(args);
		delete[] buffer;
	}
	void delay(uint32_t ms)
	{
		VMB_HAL_Delay(ms);
	}
	uint32_t getTickCount()
	{
		return VMB_HAL_GetTickCount();
	}
	uint32_t getTickCountInMs()
	{
		return VMB_HAL_GetTickCountInMs();
	}
	void resetTickCount()
	{
		VMB_HAL_ResetTickCounter();
	}

}
