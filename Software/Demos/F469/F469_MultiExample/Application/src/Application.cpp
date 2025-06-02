// Application.cpp
#include "Application.h"
#include "BSP_VoiceMailBox.hpp"

// Include examples
#include "Example_AnalogPin.hpp"
#include "Example_DigitalPin.hpp"
#include "Example_AudioPlayer.hpp"
#include "Example_AudioRecorder.hpp"
#include "Example_File.hpp"
#include "Example_WAVFile.hpp"
#include "Example_MP3File.hpp"
#include "Example_I2C.hpp"
#include "Example_I2S.hpp"
#include "Example_MP3Decoder.hpp"
#include "Example_MP3Encoder.hpp"
#include "Example_UART.hpp"
#include "Example_DCOffset.hpp"
#include "Example_ATCommandClient.hpp"
#include "Example_Codec_TLV320AIC3104.hpp"
#include "Example_Logger.hpp"
#include "Example_Updatable.hpp"
#include "Example_Timer.hpp"


// List of all examples
enum Example
{
	example_AnalogPin,
	example_DigitalPin,
	example_AudioPlayer,
	example_AudioRecorder,
	example_File,
	example_WAVFile,
	example_MP3File,
	example_I2C,
	example_I2S,
	example_MP3Decoder,
	example_MP3Encoder,
	example_UART,
	example_DCOffset,
	example_ATCommandClient,
	example_Codec_TLV320AIC3104,
	example_Example_Logger,
	example_Updatable,
	example_Timer,

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
	{ Example_AudioRecorder::setup, Example_AudioRecorder::loop },
	{ Example_File::setup, Example_File::loop },
	{ Example_WAVFile::setup, Example_WAVFile::loop },
	{ Example_MP3File::setup, Example_MP3File::loop },
	{ Example_I2C::setup, Example_I2C::loop },
	{ Example_I2S::setup, Example_I2S::loop },
	{ Example_MP3Decoder::setup, Example_MP3Decoder::loop },
	{ Example_MP3Encoder::setup, Example_MP3Encoder::loop },
	{ Example_UART::setup, Example_UART::loop },
	{ Example_DCOffset::setup, Example_DCOffset::loop },
	{ Example_ATCommandClient::setup, Example_ATCommandClient::loop },
	{ Example_Codec_TLV320AIC3104::setup, Example_Codec_TLV320AIC3104::loop },
	{ Example_Logger::setup, Example_Logger::loop },
	{ Example_Updatable::setup, Example_Updatable::loop },
	{ Example_Timer::setup, Example_Timer::loop }
};


/**
 * @brief Select the example you want to run.
 * @details You can find the source code of each example in the Application/src folder
 */
const Example selectedExample = Example::example_Timer;


void setup()
{
	(*exampleFunctions[selectedExample].setup)();
}

void loop()
{
	(*exampleFunctions[selectedExample].loop)();
}
