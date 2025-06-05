# Timer
This class offers a timer that can be used to run specific code periodically.
You can find a ready to run project [here](../../Demos/F469/F469_MultiExample/README.md).

---
## Content
- [Features](#features)
- [Benefit of this timer](#benefit-of-this-timer)
- [Setup](#setup)
- [Usage](#usage)
    - [Timer with if statement](#timer-with-if-statement)
    - [Timer with callback](#timer-with-callback)
    - [Automatic restart](#automatic-restart)

---
## Features
- Timing in approximate millisecond accuracy.
- Using timer in a if statement that gets executed if the timer has expired.
- Using callback functions to execute a function when the timer has expired.

> [!NOTE]
> The Timer class does not handle time overflows.
> Since the internal used time is 64bit this would only be a problem after 3655 Years at a clock frequency of 160MHz.

---
## Benefit of this timer
A usecase for the Timer class is the following code where some code needs to be executed at a given interval. Using classical methodes this is a common solution to the problem:
``` C++
#include "BSP_VoiceMailBox.hpp"
uint32_t previousTick = HAL_GetTick();  // Record the start time

void loop()
{
    VoiceMailBox::update();
    uint32_t currentTick = HAL_GetTick();
    if ((currentTick - previousTick) >= 1000)  // 1000 ms = 1 second
    {
        previousTick = currentTick;

        // Your code to run every 1 second goes here
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);  // For example, toggle an LED
    }
}
```

Using the Timer class, the same task can be done with much less and more readable code:
``` C++
#include "BSP_VoiceMailBox.hpp"
VoiceMailBox::Timer timer;

void setup()
{
    VoiceMailBox::update();
    timer.onFinish([](){
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);  // For example, toggle an LED
    });
    timer.enableAutoRestart(true);
    timer.start(1000);
}
void loop()
{
    VoiceMailBox::update(); // Will update the timer objects
}
```
---
## Setup    
- Make sure the C++ application is setup in order to use this class
You can find the instructions on how to do so [here](CppFromC.md).

---
## Usage
#### Timer with if statement
``` C++ 
#include "BSP_VoiceMailBox.hpp"

VoiceMailBox::Timer* timer = nullptr;
void setup()
{
    VoiceMailBox::setup();

    timer = new VoiceMailBox::Timer();
    timer->start(1000); // time in ms
}
void loop()
{
    using namespace VoiceMailBox;
    VoiceMailBox::update();

    if (timer->hasFinished())
    {
        timer->start();
        println("Cyclic print after " + std::to_string(getTickCountInMs())+ "ms");
    }
}
```
---

#### Timer with callback
``` C++ 
#include "BSP_VoiceMailBox.hpp"

VoiceMailBox::Timer* timer = nullptr;
void setup()
{
    using namespace VoiceMailBox;
    VoiceMailBox::setup();

    timer = new VoiceMailBox::Timer([]() {
            timer->start(); // Restart the timer for the next callback
            println("Cyclic print after " + std::to_string(getTickCountInMs()) + "ms");
        });
    timer->start(1000);
}
void loop()
{
    VoiceMailBox::update();
}
```
---

#### Automatic restart
``` C++ 
#include "BSP_VoiceMailBox.hpp"

VoiceMailBox::Timer* timer = nullptr;
void setup()
{
    using namespace VoiceMailBox;
    VoiceMailBox::setup();

    timer = new VoiceMailBox::Timer([]() {
            println("Cyclic print after " + std::to_string(getTickCountInMs()) + "ms");
        });
    timer->enableAutoRestart(true); // Enable auto-restart
    timer->start(1000);
}
void loop()
{
    VoiceMailBox::update();
}
```
---
