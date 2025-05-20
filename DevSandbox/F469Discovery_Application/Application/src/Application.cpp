/*
 * Application.cpp
 *
 *  Created on: May 7, 2025
 *      Author: Alex
 */
#include "Application.h"
#include "BSP_VoiceMailBox.hpp"
#include <math.h>
#include <string>
#include <cstring>

 // WiFi Settings
const std::string WIFI_SSID = "Schmarotzer WLAN";
const std::string WIFI_PASSWORD = "ScheissZahlekombination";

// Server Settings
const std::string serverIP = "192.168.86.110";
const uint16_t serverPort = 8000;
const std::string uploadURL = "devicesbackend/upload/";
const std::string downloadURL = "media/";

// File Settings
const std::string fileName = "record.wav";



VoiceMailBox::AudioRecorder* recorder = nullptr;
VoiceMailBox::AudioPlayer* player = nullptr;



void setup()
{
	using namespace VoiceMailBox;
	VoiceMailBox::setup();

	recorder = new AudioRecorder(getCodec(), getLed(LED::LED0));
	player = new AudioPlayer(getCodec(), getLed(LED::LED0));

	// Connect to WiFi
	ATCommandClient& pmodESP = getPmodESP();
	int counter = 5; 
	while (!pmodESP.connectToWifi(WIFI_SSID, WIFI_PASSWORD) && counter > 0)
	{
		delay(1000);
		--counter;
		if (counter > 0)
			println("Try to reconnect to WIFI");
		else
			println("Failed to connect to WIFI");
	}

	// Setup button callbacks
	// BTN0: Record/Stop
	// BTN1: Play/Stop
	// BTN2: Upload
	// BTN3: Download
	getButton(Button::BTN0).setOnFallingEdgeCallback([](DigitalPin&) {
			if (player->isPlaying())
				player->stopPlayback();
			if (recorder->isRecording())
				recorder->stopRecording();
			else
				recorder->startRecording();
		});

	getButton(Button::BTN1).setOnFallingEdgeCallback([](DigitalPin&) {
			if (recorder->isRecording())
				recorder->stopRecording();
			if (player->isPlaying())
				player->stopPlayback();
			else
				player->startPlayback();
		});

	getButton(Button::BTN2).setOnFallingEdgeCallback([&pmodESP](DigitalPin&) {
			if (player->isPlaying())
				player->stopPlayback();
			if (recorder->isRecording())
				recorder->stopRecording();
			if (pmodESP.sendFileToServer(fileName, uploadURL, serverIP, serverPort))
				println("File sent successfully");
			else
				println("Failed to send file");
		});

	getButton(Button::BTN3).setOnFallingEdgeCallback([&pmodESP](DigitalPin&) {
			if (player->isPlaying())
				player->stopPlayback();
			if (recorder->isRecording())
				recorder->stopRecording();
			if (pmodESP.downloadFileFromServer(fileName, downloadURL + fileName, serverIP, serverPort))
				println("File downloaded successfully");
			else
				println("Failed to download file");
		});

}

void loop()
{
	VoiceMailBox::update();

	recorder->update();
	player->update();
}
