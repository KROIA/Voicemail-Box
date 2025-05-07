#ifndef BSP_VOICE_MAIL_BOX
#define BSP_VOICE_MAIL_BOX

#include <platform.hpp>
#include "stdbool.h"

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

	void setLed(LED led, bool on);
	void toggleLed(LED led);

	bool getButtonState(Button button);

}

#endif
