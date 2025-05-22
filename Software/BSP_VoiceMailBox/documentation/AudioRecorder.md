# AudioRecorder
This class manages the dataflow from the microphone to the SD-card.

- [Features](#features)
- [Setup](#setup)
- [Usage](#usage)
    - [Modify main.h and main.c](#modify-mainh-and-mainc)
    - [Inside the C++ Application](#inside-the-c-application)

# Features
- Start recording
- Stop recording
- Display optional debug information on a digital pin for performance measurement and timing constraint check.

# Setup
Make sure the C++ application is setup in order to use this class
You can find the instructions on how to do so [here](CppFromC.md).

# Usage


``` C++
// Application.cpp
#include "BSP_VoiceMailBox.hpp"

// using a namespace globaly is not recommended for production
// but it simplyfies the example here
using namespace VoiceMailBox; 

AudioRecorder* recorder = nullptr;

void setup()
{
    recorder = new AudioRecorder(getCodec());
}

void loop()
{
    if(/*any start condition*/)
        recorder->startRecording();
    //...
    if(/*any stop condition*/)
        recorder->stopRecording(); 
}
```
