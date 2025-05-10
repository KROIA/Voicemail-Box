#ifndef BSP_VOICE_MAIL_BOX
#define BSP_VOICE_MAIL_BOX


#include <stdbool.h>
#include <stdint.h>

#include "digitalPin.hpp"
#include "analogPin.hpp"
#include "uart.hpp"
#include "i2c.hpp"
#include "Codec_TLV320AIC3104.hpp"
#include "ATCommandClient.hpp"
#include "File.hpp"

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

    

	void setup();

	DIGITAL_PIN& getLed(LED led);
	void setLed(LED led, bool on);
	void toggleLed(LED led);


	DIGITAL_PIN& getButton(Button button);
	bool getButtonState(Button button);

	ANALOG_PIN& getPoti(Poti poti);
	uint32_t getPotiValue(Poti poti);
	uint32_t getPotiMaxValue(Poti poti);


	ATCommandClient& getPmodESP();

	void print(const char* str, ...);
	void println(const char* str, ...);
	void delay(uint32_t ms);

	Codec_TLV320AIC3104& getCodec();
}

#endif
