// Application.cpp
#include "Application.h"
#include "BSP_VoiceMailBox.hpp"

VoiceMailBox::AudioRecorder *recorder = nullptr;
VoiceMailBox::AudioPlayer* player = nullptr;
const std::string fileName = "record.mp3";


void setup()
{
	VoiceMailBox::setup();

	// Assign the codec from the Voice Mail Box platform to the audio recorder
	recorder = new VoiceMailBox::AudioRecorder(VoiceMailBox::getCodec(), VoiceMailBox::getLed(VoiceMailBox::LED::LED0));

	// Assign the codec from the Voice Mail Box platform to the audio player
	player = new VoiceMailBox::AudioPlayer(VoiceMailBox::getCodec(), VoiceMailBox::getLed(VoiceMailBox::LED::LED1));


	// Attach callback for when button 0 gets pressed
	// On the falling edge, the recording will start until the button gets pressed again
	VoiceMailBox::getButton(VoiceMailBox::Button::BTN0).setOnFallingEdgeCallback([](VoiceMailBox::DigitalPin&){
		if(player->isPlaying())
			player->stop(); // Stop the player before a new recording starts
		if(recorder->isRecording())
		{
			recorder->stop();
			VoiceMailBox::println("Recording stopped");
		}
		else
		{
			if(recorder->start(fileName))
				VoiceMailBox::println("Recording started");
			else
				VoiceMailBox::println("Can't start recording for %s", fileName);
		}
	});


	// Attach callback for when button 1 gets pressed
	// On the falling edge, the playback will start until the button gets pressed again or
	// the playback has finished
	VoiceMailBox::getButton(VoiceMailBox::Button::BTN1).setOnFallingEdgeCallback([](VoiceMailBox::DigitalPin&){
			if(recorder->isRecording())
				recorder->stop(); // Stop recording before the playback starts
			if(player->isPlaying())
			{
				player->stop();
				VoiceMailBox::println("Playback stopped");
			}
			else
			{
				if(player->start(fileName))
					VoiceMailBox::println("Playback started");
				else
					VoiceMailBox::println("Can't start playback for %s", fileName);
			}
		});
}

void loop()
{
	VoiceMailBox::update();
}
