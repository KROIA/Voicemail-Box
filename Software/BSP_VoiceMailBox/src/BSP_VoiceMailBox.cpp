#include <BSP_VoiceMailBox.hpp>
#include <platform.hpp>

#include <cstdarg>   // <-- required for va_list and related macros
#include <cstdio>    // <-- required for vsnprintf
#include <cstring>

namespace VoiceMailBox
{
	void setLed(LED led, bool on)
	{
		Components::led[static_cast<int>(led)].set(on);
	}
	void toggleLed(LED led)
	{
		Components::led[static_cast<int>(led)].toggle();
	}

	bool getButtonState(Button button)
	{
		return Components::button[static_cast<int>(button)].get();
	}

	uint32_t getPotiValue(Poti poti)
	{
		return Components::adcPotis[static_cast<int>(poti)].getValue();
	}


	void print(const char* str, ...)
	{
		va_list args;
		va_start(args, str);
		char buffer[256];
		vsnprintf(buffer, sizeof(buffer), str, args);
		va_end(args);

		// Assuming you have a UART or similar function to send the string
		Components::dbgUart.send((uint8_t*)buffer, strlen(buffer));
	}
}
