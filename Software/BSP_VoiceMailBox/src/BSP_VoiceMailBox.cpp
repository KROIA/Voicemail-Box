#include <BSP_VoiceMailBox.hpp>
#include <platform.hpp>



namespace VoiceMailBox
{
	void setLed(LED led, bool on)
	{
		Platform::led[static_cast<int>(led)].set(on);
	}
	void toggleLed(LED led)
	{
		Platform::led[static_cast<int>(led)].toggle();
	}

	bool getButtonState(Button button)
	{
		return Platform::button[static_cast<int>(button)].get();
	}

	uint32_t getPotiValue(Poti poti)
	{
		return Platform::adcPotis[static_cast<int>(poti)].getValue();
	}


	void print(const char* str, ...)
	{
		va_list args;
		va_start(args, str);
		Utility::print(str, args); // Call the platform-specific print function
		va_end(args);
	}

	void delay(uint32_t ms)
	{
		Utility::delay(ms); // Call the platform-specific delay function
	}
}
