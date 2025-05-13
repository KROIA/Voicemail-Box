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

void processData();
void sendDemoHTTPRequest();
bool testFile();
void create_wav_header(VoiceMailBox::File &file, uint32_t sample_rate, uint16_t bits_per_sample,
	uint16_t num_channels, uint32_t num_samples);

VoiceMailBox::File file;
uint32_t sampleCounter = 0;
uint32_t targetSamples = 48000*20;
bool isRecording = false;

void setup()
{
	using namespace VoiceMailBox;
	VoiceMailBox::setup();

	if(isRecording)
	{
		file.open("record.wav", FA_WRITE | FA_CREATE_ALWAYS);
		//Codec_TLV320AIC3104& codec = getCodec();
		create_wav_header(file, 48000, 16, 2, targetSamples); // Create WAV header
	}
	sendDemoHTTPRequest();
	//testFile();
}

void loop()
{
	using namespace VoiceMailBox;
	//setLed(LED::LED0, getButtonState(Button::BTN0));
	//setLed(LED::LED1, getButtonState(Button::BTN1));


	Codec_TLV320AIC3104& codec = getCodec();
	if(codec.isDataReadyAndClear())
		processData();
}

void processData()
{
	using namespace VoiceMailBox;
#ifdef VMB_DEVELOPMENT_CONFIGURATION
	setDbgPin(DBG_PIN::DBG1, 1); // Set DBG1 on
#endif

	Codec_TLV320AIC3104& codec = getCodec();
	codec.startDataProcessing();
	static float performance = 0;
	static float leftIn, leftOut;
	static float rightIn, rightOut;

	static float absFIER = 0;
	const static float scale = 0.01f;
	const static float scaleInv = 1 / scale;

	volatile int16_t* adcData = codec.getRxBufPtr();
	volatile int16_t* dacData = codec.getTxBufPtr();

	static uint32_t maxPotiVal = getPotiMaxValue(Poti::POT1);
	uint32_t codecBufferSize = codec.getBufferSize();

	uint32_t rawPoti = getPotiValue(Poti::POT1);
	float poti = std::exp(0.5f - (float)rawPoti / (float)maxPotiVal);


	//uint8_t tmp[64];
	for (uint32_t n = 0; n < codecBufferSize; n++)
	{
		// redirect microphone to speaker
		dacData[n] = (int16_t)((float)adcData[n] * poti);

		//print("%i\r", adcData[n]);
	}



	// Save audio samples to the file until the target amount of samples is reached
	if(isRecording)
	{
		long count = codecBufferSize;
		if (sampleCounter + count > targetSamples)
			count = targetSamples - sampleCounter;
		if (count > 1)
		{
			file.write((uint8_t*)adcData, codec.getBufferSize()*2); // Write to file
			sampleCounter += count/2;
		}
		else
		{
			file.close();
			isRecording = false;
		}
	}
	performance = codec.getProcessingTimeRatio();
#ifdef VMB_DEVELOPMENT_CONFIGURATION
	setDbgPin(DBG_PIN::DBG1, 0); // Set DBG1 off
#endif
	codec.endDataProcessing();
}


void sendDemoHTTPRequest()
{
	// This demo is inspired by the EMBSYS1 Lab10
	using namespace VoiceMailBox;
	ATCommandClient& pmodESP = getPmodESP();

	if(pmodESP.doesRespond())
	{
		println("PmodESP does respond");
		char response[256] = { 0 };

		while (!pmodESP.connectToWifi("Alex-PC", "87924ikR"))
		{
			delay(1000);
			println("Try to reconnect to WIFI");
		}

		/*pmodESP.sendCommand("ATE0");
		delay(10);

		// connect to wifi
		pmodESP.sendCommand("AT+CWJAP=\"Alex-PC\",\"87924ikR\"");

		// wait for response
		delay(10);
		while (!pmodESP.waitUntil("WIFI GOT IP\r\n\r\nOK\r\n"))
		{
			println("Waiting for response from WIFI...");
			delay(2);
		}
		bool isConnected = false;
		pmodESP.getResponse((uint8_t*)response, sizeof(response));
		print("Response: ");
		println(response);*/
		delay(15);

		// Request ip address
		pmodESP.sendCommand("AT+CIPSTA?");
		delay(15);
		while (!pmodESP.hasResponse())
		{
			println("Waiting for response from WIFI...");
			delay(2);
		}
		if (pmodESP.getResponse((uint8_t*)response, sizeof(response)))
		{
			print("Response: ");
			println(response);
		}

		bool repeat = true;
		while (repeat)
		{
			if (pmodESP.sendFileToServer("testFile.txt", "192.168.137.1", 8000))
			{
				println("File sent successfully");
			}
			else
			{
				println("Failed to send file");
			}
			delay(6000);
		}




		// Send request to server
		std::string startRequest = "AT+CIPSTART=\"TCP\",\"192.168.137.1\",8000";
		pmodESP.sendCommand(startRequest.c_str());
		//delay(50);
		while (!pmodESP.waitUntil("OK"))
		{
			println("Waiting for response from WIFI...");
			delay(2);
		}
		//delay(100);
		if (pmodESP.getResponse((uint8_t*)response, sizeof(response)))
		{
			print("Response: ");
			println(response);
		}

		std::string sizeInfo = "AT+CIPSEND=401";
		pmodESP.sendCommand(sizeInfo.c_str());
		//delay(50);
		while (!pmodESP.waitUntil(">"))
		{
			println("Waiting for response from WIFI...");
			delay(2);
		}
		//delay(100);
		if (pmodESP.getResponse((uint8_t*)response, sizeof(response)))
		{
			print("Response: ");
			println(response);
		}
		//delay(50);


		// Send post request
		int delayMS = 0;
		pmodESP.sendCommand("POST /devicesbackend/upload/ HTTP/1.1");
		delay(delayMS);
		pmodESP.sendCommand("Host: 192.168.1.116:8000\r\nUser-Agent: ESP32");
		delay(delayMS);
		//pmodESP.sendCommand("User-Agent: ESP32");
		delay(delayMS);
		pmodESP.sendCommand("Content-Length: 202");
		delay(delayMS);
		pmodESP.sendCommand("Content-Type: multipart/form-data; boundary=------------------------eYRLjSUtcTX8XlV9TLI4k1");
		delay(delayMS);
		pmodESP.sendCommand("");
		delay(delayMS);
		pmodESP.sendCommand("--------------------------eYRLjSUtcTX8XlV9TLI4k1");
		delay(delayMS);
		pmodESP.sendCommand("Content-Disposition: form-data; name=\"test\"; filename=\"aaa.txt\"");
		delay(delayMS);
		pmodESP.sendCommand("Content-Type: text/plain");
		delay(delayMS);
		pmodESP.sendCommand("");
		delay(delayMS);
		pmodESP.sendCommand("12345");
		delay(delayMS);
		pmodESP.sendCommand("--------------------------eYRLjSUtcTX8XlV9TLI4k1--");
		delay(delayMS);

		//pmodESP.sendCommand("AT+CIPCLOSE");
		while (!pmodESP.waitUntil("SEND"))
		{
			println("Waiting for response from WIFI...");
			delay(20);
			pmodESP.sendCommand("AT+CIPCLOSE");
		}
		delay(100);
		if (pmodESP.getResponse((uint8_t*)response, sizeof(response)))
		{
			print("Response: ");
			println(response);
		}

	}
	else
	{
		println("PmodESP does not respond");
	}
}
bool testFile()
{
	using namespace VoiceMailBox;
	File file;

	// Open a file for writing
	if (file.open("test.txt", FA_WRITE | FA_CREATE_ALWAYS)) {
		print("File opened for writing\n\r");
		file.write("Hello, FATFS!");
		file.flush();
		file.close();
	}
	else {
		print("Failed to open file for writing\n\r");
	}

	// Open the same file for reading
	if (file.open("test.txt", FA_READ)) {
		char buffer[20] = { 0 };
		file.read(buffer, sizeof(buffer) - 1);
		print("Read from file: %s\n\r", buffer);
		file.close();
	}
	else {
		print("Failed to open file for reading\n\r");
		return false;
	}

	// Check if file exists
	if (File::exists("test.txt")) {
		print("File exists!\n\r");
	}
	else {
		print("File does not exist\n\r");
		return false;
	}

	// Rename the file
	if (File::rename("test.txt", "renamed.txt")) {
		print("File renamed successfully\n\r");
	}
	else {
		print("Failed to rename file\n\r");
		return false;
	}

	// Delete the file
	if (File::remove("renamed.txt")) {
		print("File deleted successfully\n\r");
	}
	else {
		print("Failed to delete file\n\r");
		return false;
	}

	// List files in root directory
	print("Listing root directory:\n\r");
	std::vector<std::string> files = File::listDirectory("/");
	for (const auto& name : files) {
		print(" - %s\n\r", name.c_str());
	}
	return true;
}






void create_wav_header(VoiceMailBox::File& file, uint32_t sample_rate, uint16_t bits_per_sample,
	uint16_t num_channels, uint32_t num_samples) 
{
	using namespace VoiceMailBox;
	uint32_t byte_rate = sample_rate * num_channels * (bits_per_sample / 8);
	uint16_t block_align = num_channels * (bits_per_sample / 8);
	uint32_t data_chunk_size = num_samples * block_align;
	uint32_t riff_chunk_size = 36 + data_chunk_size;

	//sample_rate /= num_channels;

	uint8_t header[44];

	memcpy(header, "RIFF", 4);
	header[4] = (uint8_t)(riff_chunk_size & 0xFF);
	header[5] = (uint8_t)((riff_chunk_size >> 8) & 0xFF);
	header[6] = (uint8_t)((riff_chunk_size >> 16) & 0xFF);
	header[7] = (uint8_t)((riff_chunk_size >> 24) & 0xFF);
	memcpy(header + 8, "WAVEfmt ", 8);

	header[16] = 16;  // PCM header size
	header[17] = 0; header[18] = 0; header[19] = 0;

	header[20] = 1;  // Audio format = PCM
	header[21] = 0;

	header[22] = (uint8_t)(num_channels & 0xFF);
	header[23] = (uint8_t)((num_channels >> 8) & 0xFF);

	header[24] = (uint8_t)(sample_rate & 0xFF);
	header[25] = (uint8_t)((sample_rate >> 8) & 0xFF);
	header[26] = (uint8_t)((sample_rate >> 16) & 0xFF);
	header[27] = (uint8_t)((sample_rate >> 24) & 0xFF);

	header[28] = (uint8_t)(byte_rate & 0xFF);
	header[29] = (uint8_t)((byte_rate >> 8) & 0xFF);
	header[30] = (uint8_t)((byte_rate >> 16) & 0xFF);
	header[31] = (uint8_t)((byte_rate >> 24) & 0xFF);

	header[32] = (uint8_t)(block_align & 0xFF);
	header[33] = (uint8_t)((block_align >> 8) & 0xFF);

	header[34] = (uint8_t)(bits_per_sample & 0xFF);
	header[35] = (uint8_t)((bits_per_sample >> 8) & 0xFF);

	memcpy(header + 36, "data", 4);
	header[40] = (uint8_t)(data_chunk_size & 0xFF);
	header[41] = (uint8_t)((data_chunk_size >> 8) & 0xFF);
	header[42] = (uint8_t)((data_chunk_size >> 16) & 0xFF);
	header[43] = (uint8_t)((data_chunk_size >> 24) & 0xFF);

	if (file.isOpen())
	{
		file.write(header, sizeof(header));
		println("WAV header written to file");
	}
	else
	{
		println("File is not open");
		return;
	}
}
