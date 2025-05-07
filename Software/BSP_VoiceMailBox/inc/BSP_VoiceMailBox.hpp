#ifndef BSP_VOICE_MAIL_BOX
#define BSP_VOICE_MAIL_BOX


#include <stdbool.h>
#include <stdint.h>

namespace VoiceMailBox
{
	enum class LED
	{
		LED0,
		LED1
	};

	enum class Button
	{
		BTN0,
		BTN1,
		BTN2,
		BTN3
	};

	enum class Poti
	{
		POT0,
		POT1
	};

	void setLed(LED led, bool on);
	void toggleLed(LED led);

	bool getButtonState(Button button);

	uint32_t getPotiValue(Poti poti);


	void print(const char* str, ...);
	void delay(uint32_t ms);

}

#endif
