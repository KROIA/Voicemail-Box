#include <BSP_VoiceMailBox.hpp>
#include <platform.hpp>



namespace VoiceMailBox
{
	void setup()
	{
		Platform::setup(); // Call the platform-specific setup function
	}


	DIGITAL_PIN& getLed(LED led)
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

	DIGITAL_PIN& getButton(Button button)
	{
		return Platform::button[static_cast<int>(button)];
	}
	bool getButtonState(Button button)
	{
		return Platform::button[static_cast<int>(button)].get();
	}

	ANALOG_PIN& getPoti(Poti poti)
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


	void print(const char* str, ...)
	{
		va_list args;
		va_start(args, str);
		Utility::print(str, args); // Call the platform-specific print function
		va_end(args);
	}
	void println(const char* str, ...)
	{
		va_list args;
		va_start(args, str);
		Utility::println(str, args); // Call the platform-specific print function
		va_end(args);
	}

	void delay(uint32_t ms)
	{
		Utility::delay(ms); // Call the platform-specific delay function
	}

	Codec_TLV320AIC3104& getCodec()
	{
		return Platform::codec;
	}


	/*void on_uart_rx_dma_received(void* huart, uint16_t Size)
	{
		VoiceMailBox::HAL_UARTEx_RxEventCallback(huart, Size); // Call the platform-specific UART RX DMA received callback
	}*/
}
