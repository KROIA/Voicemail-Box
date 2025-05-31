#include "Example_MP3Encoder.hpp"
#include "BSP_VoiceMailBox.hpp"
#include "main.h"
#include <memory>

namespace Example_MP3Encoder
{
	/**
	 * @brief Example on how to convert a .wav file to .mp3 format.
	 * @details
	 * This example reads audio samples from a .wav file and encodes them to .mp3 format using the MP3_encoder class.
	 * The encoded data is then written to a new .mp3 file.
	 */

	VoiceMailBox::WAVFile wavFile;
	VoiceMailBox::File mp3File;
	VoiceMailBox::MP3_encoder* encoder = nullptr;

	void setup()
	{
		// 48000 : sample rate in Hz
		// 48 : bitrate in kbps
		// 2 : number of channels (1 for mono, 2 for stereo)
		encoder = new VoiceMailBox::MP3_encoder(48000, 48, 2);

		wavFile.setSampleRate(48000); // Set sample rate to 48kHz
		wavFile.setNumChannels(2);    // Stereo recording
		wavFile.setBitsPerSample(16); // Set bits per sample to 16

		if (!wavFile.open("music.wav", VoiceMailBox::File::AccessMode::read))
		{
			VoiceMailBox::println("Failed to open file for reading.");
		}
		if (!mp3File.open("conv.mp3", VoiceMailBox::File::AccessMode::write))
		{
			VoiceMailBox::println("Failed to open file for writing.");
		}		
	}

	void loop()
	{
		static bool finished = false;
		if (finished)
			return;
		if (!mp3File.isOpen())
		{
			VoiceMailBox::println("mp3File is not open");
			VoiceMailBox::delay(1000);
			return;
		}
		if (!wavFile.isOpen())
		{
			VoiceMailBox::println("wavFile is not open");
			VoiceMailBox::delay(1000);
			return;
		}

		const size_t sampleCount = 576; // Number of samples per frame for MP3 (2 channels, 16 bits per sample)
		int16_t data[sampleCount*2] = { 0 }; // Buffer to hold decoded audio samples
		VoiceMailBox::println("Starting MP3 encoding...");
		while (!wavFile.eof())
		{
			size_t bytesRead = wavFile.readAudioSamples(data, sampleCount);
			if (bytesRead == 0)
			{
				// End of file or error
				break;
			}
			// Encode the audio data to MP3 format
			int8_t* mp3Buffer = nullptr;
			uint32_t bytesToWrite = encoder->encode(mp3Buffer, data);
			
			if (bytesToWrite > 0)
			{
				// Write the encoded MP3 data to the file
				mp3File.write((const char*)mp3Buffer, bytesToWrite);
			}
			else
			{
				// This is not a problem, the encoder only produces data on every second call of the encode function.
			}
		}
		VoiceMailBox::println("Encoding finished");
		finished = true;
		mp3File.close();
		wavFile.close();
	}
} 
