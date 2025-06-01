#include "Example_AudioRecorder.hpp"
#include "BSP_VoiceMailBox.hpp"
#include "main.h"
#include <string>

namespace Example_AudioRecorder
{
	/**
	 * @brief Example on how to start/stop and pause/resume recording of an audio file.
	 * @details
	 * This example uses BTN0 (SW801) to start/stop recording and BTN1 (SW802) to pause/resume recording of an audio file.
	 */
	void setup_StartStopAndPause();
	void loop_StartStopAndPause();






// ------------------------------------------------------------------------------------------------
// ================================================================================================
// ------------------------------------------------------------------------------------------------
	void setup()
	{
		// Select one of the examples to run, comment out the others
	    setup_StartStopAndPause();
	}

	void loop()
	{
		// Select one of the examples to run, comment out the others (dont mix them with the setup)
		loop_StartStopAndPause();
	}






// ------------------------------------------------------------------------------------------------
// ================================================================================================
// ------------------------------------------------------------------------------------------------
	VoiceMailBox::AudioRecorder* recorder_1 = nullptr;

	void setup_StartStopAndPause()
	{
		using namespace VoiceMailBox;
		VoiceMailBox::setup();

		// Assign the codec from the Voice Mail Box platform to the audio player
		recorder_1 = new VoiceMailBox::AudioRecorder(VoiceMailBox::getCodec());

		VoiceMailBox::getCodec().enableMeasurementRXDCOffset(true);

		// Start/Stop recording with BTN0 (SW801)
		getButton(Button::BTN0).setOnFallingEdgeCallback([](DigitalPin&) {
				if (recorder_1->isRecording() && !recorder_1->isPaused())
				{
					recorder_1->stop();
					println("Recording stopped");
				}
				else
				{
					recorder_1->start("record.mp3");
					println("Recording started");
				}
			});

		// Pause/Resume recording with BTN1 (SW802)
		getButton(Button::BTN1).setOnFallingEdgeCallback([](DigitalPin&) {
				if (recorder_1->isPaused())
				{
					recorder_1->resume();
					println("Recording resumed");
				}
				else
				{
					recorder_1->pause();
					println("Recording paused");
				}
			});
	}
	void loop_StartStopAndPause()
	{
		VoiceMailBox::update();
		
		static uint64_t lastTime = VoiceMailBox::VMB_HAL_GetTickCountInMs();
		if (VoiceMailBox::VMB_HAL_GetTickCountInMs() - lastTime > 1000)
		{
			lastTime = VoiceMailBox::VMB_HAL_GetTickCountInMs();

			VoiceMailBox::println("DC Offset RX Left: %.2f, Right: %.2f", VoiceMailBox::getCodec().getRXDCOffsetLeft(),VoiceMailBox::getCodec().getRXDCOffsetRight());
		}
	}
} 
