#include "Example_MP3Decoder.hpp"
#include "BSP_VoiceMailBox.hpp"
#include "main.h"
#include <memory>

namespace Example_MP3Decoder
{
	/**
	 * @brief Example on how to convert an MP3 file and write the decoded audio data to a WAV file.
	 * @details
	 * This example uses the MP3_decoder class to decode an MP3 file and write the decoded audio data to a WAV file.
	 * The MP3_decoder class is used to read compressed MP3 data and decode it into PCM audio samples.
	 * The WAVFile class is used to write the decoded audio samples to a WAV file.
	 */

	unsigned int decoderReadCallback(
		void* pMP3_decoderCompressedData,
		unsigned int nMP3_decoderDataSizeInChars,
		void* pUserData);

	VoiceMailBox::WAVFile* wavFile = nullptr;
	VoiceMailBox::File* mp3File = nullptr;
	VoiceMailBox::MP3_decoder* decoder = nullptr;

	void setup()
	{
		// decoderReadCallback: function that gets called by the MP3_decoder to read compressed data from the MP3 file.
		// &mp3File: pointer to the MP3 file that is being read. (any void* can be used here, but we use a pointer to the MP3 file for convenience)
		// 4: samplesize in bytes. [int16_t(LEFT), int16_t(RIGHT)] is one sample
		decoder = new VoiceMailBox::MP3_decoder(decoderReadCallback, mp3File, 4);

		mp3File = new VoiceMailBox::File();
		wavFile = new VoiceMailBox::WAVFile();
		wavFile->setSampleRate(48000); // Set sample rate to 48kHz
		wavFile->setNumChannels(2);    // Stereo recording
		wavFile->setBitsPerSample(16); // Set bits per sample to 16

		if (!mp3File->open("music.mp3", VoiceMailBox::File::AccessMode::read))
		{
			VoiceMailBox::println("Failed to open file for reading.");
		}
		if (!wavFile->open("conv.wav", VoiceMailBox::File::AccessMode::write))
		{
			VoiceMailBox::println("Failed to open file for writing.");
		}
	}

	void loop()
	{
		static bool finished = false;
		if (finished)
			return;
		if (!mp3File->isOpen())
		{
			VoiceMailBox::println("mp3File is not open");
			VoiceMailBox::delay(1000);
			return;
		}
		if (!wavFile->isOpen())
		{
			VoiceMailBox::println("wavFile is not open");
			VoiceMailBox::delay(1000);
			return;
		}

		const size_t sampleCount = 576; // Number of samples per frame for MP3 (2 channels, 16 bits per sample)
		int16_t data[sampleCount*2] = { 0 }; // Buffer to hold decoded audio samples
		VoiceMailBox::println("Starting MP3 decoding...");
		while (!mp3File->eof())
		{
			// Request <sampleCount> samples from the MP3 decoder
			unsigned int samplesRead = decoder->decode(data, sampleCount);
			static bool firstRun = true;
			if (firstRun)
			{
				samplesRead = decoder->decode(data, sampleCount); // For the first run, the decoding must be done twice to prevent noise
				firstRun = false;
			}
			if (samplesRead == 0)
			{
				// End of file
				break;
			}

			// Write the decoded audio data to the WAV file
			wavFile->writeAudioSamples(data, samplesRead); // 4 bytes per sample (2 channels * 2 bytes per channel)
		}
		VoiceMailBox::println("Decoding finished");
		mp3File->close();
		wavFile->close();
		finished = true;
	}

	// This function is called by the MP3_decoder to read compressed data from the MP3 file.
	unsigned int decoderReadCallback(
		void* pMP3_decoderCompressedData,
		unsigned int nMP3_decoderDataSizeInChars,
		void* pUserData)
	{
		// The pUserData is the pointer that was passed by the MP3_decoder constructor, which is a pointer to the mp3File->
		VoiceMailBox::File* file = (VoiceMailBox::File*)pUserData;
		if (file->isOpen())
		{
			// Read the MP3_decoder data from the file
			uint32_t bytesRead = file->read((uint8_t*)pMP3_decoderCompressedData, nMP3_decoderDataSizeInChars);
			return bytesRead;
		}
		return 0;
	}
} 
