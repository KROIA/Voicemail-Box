#include "Example_WAVFile.hpp"
#include "BSP_VoiceMailBox.hpp"
#include "main.h"
#include <memory>

namespace Example_WAVFile
{
	/**
	 * @brief Example on how to write to a .wav file using live audio data from the codec.
	 * @details
	 * Since a .wav file is a specific format for audio, real audio data is used in this example.
	 * The example reads the audio data directly from the codec and writes it to a .wav file.
	 * This task is usually done by the AudioRecorder class, but this example shows how to do it manually.
	 */
	void setup_SimpleWrite();
	void loop_SimpleWrite();


	/**
	 * @brief Example on how to read from a .wav file and outputting it to the codec.
	 * @details
	 * Since a .wav file is a specific format for audio, real audio data is used in this example.
	 * The example reads the audio data from a .wav file and plays it back using the codec.
	 * This task is usually done by the AudioPlayer class, but this example shows how to do it manually.
	 */
	void setup_SimpleRead();
	void loop_SimpleRead();
	
	


	

// ------------------------------------------------------------------------------------------------
// ================================================================================================
// ------------------------------------------------------------------------------------------------
	void setup()
	{
		setup_SimpleWrite();
		//setup_SimpleRead();
	}

	void loop()
	{
		loop_SimpleWrite();
		//loop_SimpleRead();
	}






// ------------------------------------------------------------------------------------------------
// ================================================================================================
// ------------------------------------------------------------------------------------------------
	VoiceMailBox::WAVFile *file_1 = nullptr;
	void setup_SimpleWrite()
	{
		using namespace VoiceMailBox;
		VoiceMailBox::setup();

		file_1 = new VoiceMailBox::WAVFile();
		file_1->setSampleRate(48000); // Set sample rate to 48kHz
		file_1->setNumChannels(2);    // Stereo recording
		file_1->setBitsPerSample(16); // Set bits per sample to 16

		// Start recording with BTN0 (SW801)
		getButton(Button::BTN0).setOnFallingEdgeCallback([](DigitalPin&) {
				if (file_1->open("record.wav", File::AccessMode::write))
				{
					println("Recording started");
				}
				else
				{
					println("Failed to open file for writing");
				}
			});

		// Stop recording with BTN1 (SW802)
		getButton(Button::BTN1).setOnFallingEdgeCallback([](DigitalPin&) {
				file_1->close();
				println("Recording stopped");
			});
	}
	void loop_SimpleWrite()
	{
		using namespace VoiceMailBox;
		VoiceMailBox::update();
		AudioCodec& codec = getCodec();

		// Check if the codec has new audio data ready to be written
		if (codec.isDataReadyAndClearFlag())
		{
			if (file_1->isOpen())
			{
				uint32_t sampeCount = codec.getBufferSize() / 2; // Assuming 16-bit stereo audio, each sample is 4 bytes
				// Write audio data to the WAV file
				file_1->writeAudioSamples((int16_t*)codec.getRxBufPtr(), sampeCount);
			}
		}
	}





// ------------------------------------------------------------------------------------------------
// ================================================================================================
// ------------------------------------------------------------------------------------------------
	VoiceMailBox::WAVFile* file_2 = nullptr;
	void setup_SimpleRead()
	{
		using namespace VoiceMailBox;
		VoiceMailBox::setup();

		file_2 = new VoiceMailBox::WAVFile();
		file_2->setSampleRate(48000); // Set sample rate to 48kHz
		file_2->setNumChannels(2);    // Stereo recording
		file_2->setBitsPerSample(16); // Set bits per sample to 16

		// Start playback with BTN0 (SW801)
		getButton(Button::BTN0).setOnFallingEdgeCallback([](DigitalPin&) {
			if (file_2->open("record.wav", File::AccessMode::read))
			{
				println("Playback started");
			}
			else
			{
				println("Failed to open file for reading");
			}
			});

		// Stop playback with BTN1 (SW802)
		getButton(Button::BTN1).setOnFallingEdgeCallback([](DigitalPin&) {
				file_2->close();
				getCodec().clearTxBuf(); // Clear the buffer to avoid noise after playback finished
				println("Playback stopped");
			});
	}
	void loop_SimpleRead()
	{
		using namespace VoiceMailBox;
		VoiceMailBox::update();
		AudioCodec& codec = getCodec();

		// Check if the codec has new audio data ready to be played back
		if (codec.isDataReadyAndClearFlag())
		{
			if (file_2->isOpen() && !file_2->eof())
			{
				uint32_t targetSamples = codec.getBufferSize() / 2; // Assuming 16-bit stereo audio, each sample is 4 bytes
				uint32_t decodedSamples = file_2->readAudioSamples((int16_t*)codec.getTxBufPtr(), targetSamples);
			}
			if (file_2->eof())
			{
				println("End of file reached.");
				codec.clearTxBuf(); // Clear the buffer to avoid noise after playback finished
				file_2->close();
			}
		}
	}
} 
