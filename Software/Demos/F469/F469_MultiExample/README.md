# Multi Example


## How to select a example
One example can be selected in the `Application.cpp`.
Set the variable `selectedExample` to a desired enum value.
The rest is handled automatically. You can now navigate to the examples specific code.
For example the AnalogPin example is programmed in the `Example_AnalogPin.cpp`.
In that file there may be multiple usecases programmed.
Each usecase can be enabled individually.
Each such `Example_XX.cpp` is structured the same way.
Here a quick file overview:
- On the top are function declarations for setup and loop for that specific usecase example. Additionally a quick description about that usecase is given.
- The `setup()` and `loop()` functions are called from the main `Application.cpp`.
  In that functions you have to uncomment that specific usecase you want to run.
  Do that for both functions and do not mix examples.
- On the bottom of the file are the different use case implementations.
  You can treat them as if they were in the main `Application.cpp` `setup()` and `loop()` functions. This makes it easy to copy code in your own project. 


---
## Examples
- [AnalogPin](#analogpin-example)
- [DigitalPin](#digitalpin-example)
- [AudioPlayer](#audioplayer-example)





---
### AnalogPin example
1) Usage of the built-in potentiometer. It prints the analog value to the console.
2) Instantiating a custom potentiometer. Also prints the analog value to the console.



### DigitalPin example
1) Usage of the built-in button and led. It takes the button value and switches the led on when the button is pressed.
2) Instantiating a custom button and led. It does the same as the first use case.
3) Usage of the callback functions of a button. 
  It turns the LED0 on when BTN0 gets pressed and turns the LED0 off when the BTN0 gets released.
  When the BTN0 is pressed down, the LED1 gets toggled, therefore blinks as long as the BTN0 is held down.


### AudioPlayer example
1) Plays a mp3 file called `record.mp3` from the SD-Card on startup once.
2) Plays a mp3 file called `record.mp3` from the SD-Card when the BTN0 gets pressed.
  By clicking the same button again, the playback will be stopped.
  When playing, the BTN1 can be used to pause/resume the playback.
