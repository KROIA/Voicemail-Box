#include "Example_AudioPlayer.hpp"
#include "BSP_VoiceMailBox.hpp"
#include "main.h"

namespace Example_AudioPlayer
{
	/**
	 * @brief Example on how to play a simple audio file.
	 * @details 
	 * This example plays a simple audio file from the SD card once.
	 */
	void setup_SimplePlayback();
	void loop_SimplePlayback();

	/**
	 * @brief Example on how to start/stop and pause/resume playback of an audio file.
	 * @details
	 * This example uses BTN0 (SW801) to start/stop playback and BTN1 (SW802) to pause/resume playback of an audio file.
	 */
	void setup_StartStopAndPause();
	void loop_StartStopAndPause();






// ------------------------------------------------------------------------------------------------
// ================================================================================================
// ------------------------------------------------------------------------------------------------
	void setup()
	{
		// Select one of the examples to run, comment out the others
		//setup_SimplePlayback();
	    setup_StartStopAndPause();
	}

	void loop()
	{
		// Select one of the examples to run, comment out the others (dont mix them with the setup)
		//loop_SimplePlayback();
		loop_StartStopAndPause();
	}






// ------------------------------------------------------------------------------------------------
// ================================================================================================
// ------------------------------------------------------------------------------------------------
	VoiceMailBox::AudioPlayer* player_1 = nullptr;
	void setup_SimplePlayback()
	{
		VoiceMailBox::setup();

		// Assign the codec from the Voice Mail Box platform to the audio player
		player_1 = new VoiceMailBox::AudioPlayer(VoiceMailBox::getCodec());
		player_1->start("record.mp3");
	}
	void loop_SimplePlayback()
	{
		VoiceMailBox::update();
	}






// ------------------------------------------------------------------------------------------------
// ================================================================================================
// ------------------------------------------------------------------------------------------------
	VoiceMailBox::AudioPlayer* player_2 = nullptr;

	void setup_StartStopAndPause()
	{
		using namespace VoiceMailBox;
		VoiceMailBox::setup();

		// Assign the codec from the Voice Mail Box platform to the audio player
		player_2 = new VoiceMailBox::AudioPlayer(VoiceMailBox::getCodec());

		// Start/Stop playback with BTN0 (SW801)
		getButton(Button::BTN0).setOnFallingEdgeCallback([](DigitalPin&) {
				if (player_2->isPlaying() && !player_2->isPaused())
				{
					player_2->stop();
					println("Playback stopped");
				}
				else
				{
					player_2->start("record.mp3");
					println("Playback started");
				}
			});

		// Pause/Resume playback with BTN1 (SW802)
		getButton(Button::BTN1).setOnFallingEdgeCallback([](DigitalPin&) {
				if (player_2->isPaused())
				{
					player_2->resume();
					println("Playback resumed");
				}
				else
				{
					player_2->pause();
					println("Playback paused");
				}
			});
	}
	void loop_StartStopAndPause()
	{
		VoiceMailBox::update();
	}
} 
