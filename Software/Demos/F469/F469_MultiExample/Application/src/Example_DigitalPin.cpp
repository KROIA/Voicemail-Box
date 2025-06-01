#include "Example_DigitalPin.hpp"
#include "BSP_VoiceMailBox.hpp"
#include "main.h"

namespace Example_DigitalPin
{
	/**
	 * @brief Example on how to use a built-in button switch a LED on the Voice Mail Box.
	 * @details 
	 *  This example uses the button BTN0 and LED0 on the Voice Mail Box.
	 *  BTN0 is SW801 on the PCB and LED0 is LD804.
	 */
	void setup_UseBuiltinButtonAndLed();
	void loop_UseBuiltinButtonAndLed();

	/**
	 * @brief Example on how to use a custom digital pin.
	 * @details
	 * This example creates a custom button and LED.
	 * It does the same as the first example but it shows how to instantiate a custom button and LED.
	 */
	void setup_UseCustomButton();
	void loop_UseCustomButton();
	


	/**
	 * @brief Example on how to use the callback functions on a button
	 * @details
	 * This example shows how to use the callback functions on a button.
	 * All 3 callbacks are used:
	 * - OnFallingEdge: called when the button gets pressed
	 * - OnRisingEdge: called when the button gets released
	 * - OnDown: called when the button is pressed and held down
	 */
	void setup_ButtonCallbacks();
	void loop_ButtonCallbacks();


// ------------------------------------------------------------------------------------------------
// ================================================================================================
// ------------------------------------------------------------------------------------------------
	void setup()
	{
		

		// Select one of the examples to run, comment out the others
		setup_UseBuiltinButtonAndLed();
		// setup_UseCustomButton();
		// setup_ButtonCallbacks();
	}

	void loop()
	{
		

		// Select one of the examples to run, comment out the others (dont mix them with the setup)
		loop_UseBuiltinButtonAndLed();
		// loop_UseCustomButton();
		// loop_ButtonCallbacks();
	}






// ------------------------------------------------------------------------------------------------
// ================================================================================================
// ------------------------------------------------------------------------------------------------
	// To instantiate, the GPIO port and pin number must be provided.
	// Additionaly a bool can be provided to specify if the pin is inverted (active low).
	VoiceMailBox::DigitalPin customButton(BTN1_GPIO_Port, BTN1_Pin, true);
	VoiceMailBox::DigitalPin customLed(LED1_GPIO_Port, LED1_Pin, true);

	void setup_UseBuiltinButtonAndLed()
	{
		VoiceMailBox::setup();
		// Nothing to setup here
	}
	void loop_UseBuiltinButtonAndLed()
	{
		using namespace VoiceMailBox;
		VoiceMailBox::update();

		DigitalPin& button_0 = getButton(Button::BTN0);
		DigitalPin& led_0    = getLed(LED::LED0);
		led_0.set(button_0.get());
	}






// ------------------------------------------------------------------------------------------------
// ================================================================================================
// ------------------------------------------------------------------------------------------------
	void setup_UseCustomButton()
	{
		VoiceMailBox::setup();
		// Nothing to setup here
	}
	void loop_UseCustomButton()
	{
		VoiceMailBox::update();
		customLed.set(customButton.get());
	}




// ------------------------------------------------------------------------------------------------
// ================================================================================================
// ------------------------------------------------------------------------------------------------
	void setup_ButtonCallbacks()
	{
		using namespace VoiceMailBox;
		VoiceMailBox::setup();
		DigitalPin& button_0 = getButton(Button::BTN0);

		button_0.setOnFallingEdgeCallback([](DigitalPin&) {
			println("Button 0 pressed");
			getLed(LED::LED0).set(true);
			});

		button_0.setOnRisingEdgeCallback([](DigitalPin&) {
			println("Button 0 released");
			getLed(LED::LED0).set(false);
			});

		button_0.setOnDownCallback([](DigitalPin&) {
			println("Button 0 is held down");
			// You can do something here while the button is held down
			// For example, you could blink the LED
			getLed(LED::LED1).toggle();
			});
	}
	void loop_ButtonCallbacks()
	{
		VoiceMailBox::update();
		VoiceMailBox::delay(100); // Just a delay to avoid flooding the console with messages and make the toggeling more visible
	}
} 
