# Multi Example


## How to select a example
One example can be selected in the `Application.cpp`.
Set the variable `selectedExample` to a desired enum value.
The rest is handled automatically. You can now navigate to the examples specific code.
Lets take the AnalogPin example. Its code is programmed in the `Example_AnalogPin.cpp`.
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
- [AudioRecorder](#audiorecorder-example)
- [File](#file-example)
  - [WAV File](#wav-file-example)
  - [MP3 File](#mp3-file-example)
- [I2C](#i2c-example)
- [I2S](#i2s-example)
- [MP3 Encoder](#mp3-encoder-example)
- [MP3 Decoder](#mp3-decoder-example)
- [UART](#uart-example)



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



### AudioRecorder example
1) Records a mp3 file called `record.mp3` to the SD-Card when the BTN0 gets pressed.
  By clicking the same button again, the recording will be stopped.
  When playing, the BTN1 can be used to pause/resume the recording.


### File example
1) Example on how to write to a file.
2) Example on how to append to a file.
3) Example on how to read from a file.

#### WAV File example
1) Example on how to write to a .wav file using live audio data from the codec.
2) Example on how to read from a .wav file and outputting it to the codec.

#### MP3 File example
1) Example on how to write to a .mp3 file using live audio data from the codec.
2) Example on how to read from a .mp3 file and outputting it to the codec.

#### I2C example
The example writes to the first register on the audio codec and reads the value back.

#### I2S example
The example uses a i2s object to read and write the audio data from the audio codec.
The codec sends microphone data and the application copies that microphone data to the
speaker output buffer. 
Since the audio codec needs to be configured before data arrives on the i2s, the following code is called first to ensure setup and then stop the DMA in order to start it manually afterwards again. Just for you to know that the DMA needs to be started on a i2s object.
Using the platforms audio codec object directly will take that step from you.
``` C++
VoiceMailBox::setup();
i2s.stopDMA();
```

#### MP3 Encoder example
This example reads audio samples from a .wav file and encodes them to .mp3 format using the `MP3_encoder` class. The encoded data is then written to a new .mp3 file.


#### MP3 Decoder example
This example uses the MP3_decoder class to decode an MP3 file and write the decoded audio data to a WAV file.
The MP3_decoder class is used to read compressed MP3 data and decode it into PCM audio samples.
The WAVFile class is used to write the decoded audio samples to a WAV file.

#### UART example
This example sends some simple text or byte arrays over the UART interface
The UART can also wait for a specific string to be received or read until a target string is found.

#### DC Offset correction example
This example shows how to remove the DC offset from the left and right audio channels.