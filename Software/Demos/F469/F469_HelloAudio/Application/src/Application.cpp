// Application.cpp
#include "Application.h"
#include "BSP_VoiceMailBox.hpp"

void setup()
{
	VoiceMailBox::setup();
}

void loop()
{
	VoiceMailBox::update();
}
