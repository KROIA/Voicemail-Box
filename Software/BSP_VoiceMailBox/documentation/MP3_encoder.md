# MP3_encoder
The MP3 encoder library used in this project is from the [X-CUBE-AUDIO](https://www.st.com/en/embedded-software/x-cube-audio.html) example project.
The MP3_encoder class is just a C++ wrapper to make it easy to use the library.
The encoder is used to write mp3 encoded data from a source like the i2s data stream.
You can find a ready to run project [here](../../Demos/F469/F469_MultiExample/README.md).

---
## Content
- [Features](#features)
- [Setup](#setup)
- [Usage](#usage)

---
## Features
- Encodes analog audio samples to mp3 frames 

---
## Setup
- Uses the Spirit MP3 library for encoding and decoding. [Click here](../../Demos/F469/F469_HelloAudio/README.md/#spiritdsp-mp3) to learn how to include the library.
- Place a wav file with the name `music.wav` onto the SD-Card.


---
## Usage
This example takes a `music.wav` file and converts it to a `conv.mp3` file.
> [!WARNING] 
> **encoder->encode(mp3Buffer, data);** provides a valid **mp3Buffer** pointer only once 
> every second call. That means the returned byte count must be checked and only if that 
> os non zero, the pointer can be used as array to save to a file.

``` C++ 
// Application.cpp
#include "BSP_VoiceMailBox.hpp" // includes "peripherals/i2s.hpp"

VoiceMailBox::WAVFile* wavFile = nullptr;
VoiceMailBox::File* mp3File = nullptr;
VoiceMailBox::MP3_encoder* encoder = nullptr;

void setup()
{
    // 48000 : sample rate in Hz
    // 48 : bitrate in kbps
    // 2 : number of channels (1 for mono, 2 for stereo)
    encoder = new VoiceMailBox::MP3_encoder(48000, 48, 2);

    mp3File = new VoiceMailBox::File();
    wavFile = new VoiceMailBox::WAVFile();
    wavFile->setSampleRate(48000); // Set sample rate to 48kHz
    wavFile->setNumChannels(2);    // Stereo recording
    wavFile->setBitsPerSample(16); // Set bits per sample to 16

    if (!wavFile->open("music.wav", VoiceMailBox::File::AccessMode::read))
    {
        VoiceMailBox::println("Failed to open file for reading.");
    }
    if (!mp3File->open("conv.mp3", VoiceMailBox::File::AccessMode::write))
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
    VoiceMailBox::println("Starting MP3 encoding...");
    while (!wavFile->eof())
    {
        size_t bytesRead = wavFile->readAudioSamples(data, sampleCount);
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
            mp3File->write((const char*)mp3Buffer, bytesToWrite);
        }
        else
        {
            // This is not a problem, the encoder only produces data on every second call of the encode function.
        }
    }
    VoiceMailBox::println("Encoding finished");
    finished = true;
    mp3File->close();
    wavFile->close();
}
```