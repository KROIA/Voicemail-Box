// Application.cpp
#include "Application.h"
#include "BSP_VoiceMailBox.hpp"

// Include examples
#include "Example_AnalogPin.hpp"
#include "Example_DigitalPin.hpp"
#include "Example_AudioPlayer.hpp"
#include "Example_AudioRecorder.hpp"


// List of all examples
enum Example
{
	example_AnalogPin,
	example_DigitalPin,
	example_AudioPlayer,
	example_AudioRecorder,

	__count // used to count the examples. let it be the last element!
};
struct ExampleCallerFunctions
{
	void (*setup)(void) = nullptr;
	void (*loop)(void) = nullptr;
};

// Registering the setup and loop functions of each example
ExampleCallerFunctions exampleFunctions[Example::__count]
{
	{ Example_AnalogPin::setup, Example_AnalogPin::loop },
	{ Example_DigitalPin::setup, Example_DigitalPin::loop },
	{ Example_AudioPlayer::setup, Example_AudioPlayer::loop },
	{ Example_AudioRecorder::setup, Example_AudioRecorder::loop }
};


/**
 * @brief Select the example you want to run.
 * @details You can find the source code of each example in the Application/src folder
 */
const Example selectedExample = Example::example_AudioRecorder;


void setup()
{
	(*exampleFunctions[selectedExample].setup)();
}

void loop()
{
	(*exampleFunctions[selectedExample].loop)();
}
