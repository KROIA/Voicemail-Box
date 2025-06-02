# WAVFile
This class is a simplfied interface for reading and writing .wav files to the SD-Card.
All Basic functions used in the project are implemented here.
You can find a ready to run project [here](../../Demos/F469/F469_MultiExample/README.md).

---
## Content
- [Features](#features)
- [Setup](#setup)
- [Usage](#usage)
    - [Writing to a file](#writing-to-a-file)
    - [Appending to a file](#appending-to-a-file)
    - [Reading from a file](#reading-from-a-file)

---
## Features
- Writing/Reading .wav files.

---
## Setup    
- Uses the same setup as the [File](File.md) class
- Make sure the C++ application is setup, you can find the instructions on how to do so [here](CppFromC.md).
  
---
## Usage
#### Writing to a file
``` C++ 
#include "BSP_VoiceMailBox.hpp"
// ...
VoiceMailBox::WAVFile *file = nullptr;
void setup()
{
    using namespace VoiceMailBox;
    VoiceMailBox::setup();

    file = new VoiceMailBox::WAVFile();
    file->setSampleRate(48000); // Set sample rate to 48kHz
    file->setNumChannels(2);    // Stereo recording
    file->setBitsPerSample(16); // Set bits per sample to 16

    // Start recording with BTN0 (SW801)
    getButton(Button::BTN0).setOnFallingEdgeCallback([](DigitalPin&) {
            if (file->open("record.wav", File::AccessMode::write))
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
            file->close();
            println("Recording stopped");
        });
}
void loop()
{
    using namespace VoiceMailBox;
    VoiceMailBox::update();
    AudioCodec& codec = getCodec();

    // Check if the codec has new audio data ready to be written
    if (codec.isDataReadyAndClearFlag())
    {
        if (file->isOpen())
        {
            uint32_t sampeCount = codec.getBufferSize() / 2; // Assuming 16-bit stereo audio, each sample is 4 bytes
            // Write audio data to the WAV file
            file->writeAudioSamples((int16_t*)codec.getRxBufPtr(), sampeCount);
        }
    }
}
```
---

#### Reading from a file
``` C++ 
#include "BSP_VoiceMailBox.hpp"
// ...
VoiceMailBox::WAVFile* file = nullptr;
void setup()
{
    using namespace VoiceMailBox;
    VoiceMailBox::setup();

    file = new VoiceMailBox::WAVFile();
    file->setSampleRate(48000); // Set sample rate to 48kHz
    file->setNumChannels(2);    // Stereo recording
    file->setBitsPerSample(16); // Set bits per sample to 16

    // Start playback with BTN0 (SW801)
    getButton(Button::BTN0).setOnFallingEdgeCallback([](DigitalPin&) {
        if (file->open("record.wav", File::AccessMode::read))
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
            file->close();
            getCodec().clearTxBuf(); // Clear the buffer to avoid noise after playback finished
            println("Playback stopped");
        });
}
void loop()
{
    using namespace VoiceMailBox;
    VoiceMailBox::update();
    AudioCodec& codec = getCodec();

    // Check if the codec has new audio data ready to be played back
    if (codec.isDataReadyAndClearFlag())
    {
        if (file->isOpen() && !file->eof())
        {
            uint32_t targetSamples = codec.getBufferSize() / 2; // Assuming 16-bit stereo audio, each sample is 4 bytes
            uint32_t decodedSamples = file->readAudioSamples((int16_t*)codec.getTxBufPtr(), targetSamples);
        }
        if (file->eof())
        {
            println("End of file reached.");
            codec.clearTxBuf(); // Clear the buffer to avoid noise after playback finished
            file->close();
        }
    }
}
```
---