#include <BSP_VoiceMailBox.hpp>
#include <platform.hpp>

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
}
