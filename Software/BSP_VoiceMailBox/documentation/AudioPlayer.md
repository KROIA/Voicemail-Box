# AudioPlayer
This class manages the dataflow from the SD-card to the microphone.
You can find a ready to run project [here](../../Demos/F469/F469_MultiExample/README.md).

## Content
- [Features](#features)
- [Setup](#setup)
- [Usage](#usage)
    - [Basic usage](#basic-usage)
    - [Using the debug Pin](#using-the-debug-pin)

## Features
- Start playback
- Stop playback
- Pause/Resume playback
- Display optional debug information on a digital pin for performance measurement and timing constraint check.

## Setup
Make sure the C++ application is setup in order to use this class
You can find the instructions on how to do so [here](CppFromC.md).

## Usage
### Basic usage
A AudioPlayer object can be instantiated in the Application.cpp.
The codec on which the sound gets played on, must be provided to the constructor.
Make sure that the codec is not a temporary object, since the AudioPlayer class only holds a reference to it.
``` C++
// Application.cpp
#include "BSP_VoiceMailBox.hpp"
#include <string>

// using a namespace globaly is not recommended for production
// but it simplyfies the example here
using namespace VoiceMailBox; 

AudioPlayer* player = nullptr;
const std::string fileName = "record.mp3";

void setup()
{
    VoiceMailBox::setup();

    // Assign the codec from the Voice Mail Box platform to the audio player
    player = new AudioPlayer(getCodec());
}

void loop()
{
    VoiceMailBox::update();

    if(/*any start condition*/)
        player->start(fileName);

    if(/*any pause condition*/)
        player->pause();

    if(/*any resume condition*/)
        player->resume();
   
    if(/*any stop condition*/)
        player->stop(); 
}
```


### Using the debug Pin
``` C++
// Application.cpp
#include "BSP_VoiceMailBox.hpp"

// using a namespace globaly is not recommended for production
// but it simplyfies the example here
using namespace VoiceMailBox; 

AudioPlayer* player = nullptr;
const std::string fileName = "record.mp3";

void setup()
{
    VoiceMailBox::setup();

    DigitalPin &dbgPin = getLed(LED::LED0);

    // Provide the constructor with a reference to a digital pin
    // Make sure that this given pin is not a temporary object, since the Player only holds a reference to it.
    player = new AudioPlayer(getCodec(), dbgPin);
}

void loop()
{
    VoiceMailBox::update();

    // ...
}
```