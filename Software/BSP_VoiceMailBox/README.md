# BSP Voice Mail Box

## About
The Voice-Mail-Box Project (VMB in short) provides a Board Support Package (BSP) that abstracts all key peripheral components using c++.

---
## Content
- [Repository overview for the software part](#repository-overview-for-the-software-part)
- [Demos](#demos)
  - [Using STM32F469I-DISCOVERY](#using-stm32f469i-discovery)
  - [Using NUCLEO-H755ZI-Q](#using-nucleo-h755zi-q)
- [Software structure](#software-structure)
  - [Detailed Software structure](#detailed-software-structure)
  - [Peripheral classes](#peripheral-classes)
  - [Data processing classes](#data-processing-classes)
  - [Other utilitiy classes](#other-utilitiy-classes)
  - [HAL abstraction](#hal-abstraction)
  - [Update loop](#-update-loop)
- [Unfinished](#unfinished)
- [Needs to be implemented](#needs-to-be-implemented)

---
## Repository overview for the software part
The software part of this project contains the following folders:
- **BSP_VoiceMailBox** 
  The folder contains the **Board Support Package** for the Voice-Mail-Box and is the hart of the software project.
  It contains all classes which are visualized in the picture in the chapter [Detailed Software structure overview](#detailed-software-structure-overview).  
- **Demos**
  The folder contains some demo projects, using the **BSP** from above.
  In that folder are two sub folders
  - **F469** Containing the example projects for the **STM32F469I-DISCOVERY** board
  - **F755** Containing the example projects for the **NUCLEO-H755ZI-Q** board
- **DevSandbox** 
  The folder contains projects, used to develop the **BSP**. 
  They may be not working since they were created to test stuff or to test downloaded demo projects from ST.


Each project contains only the business logic for the application, the **BSP** is a shared code base over all projects.
The **BSP** gets included in every project. 

---
## Demos
### Using STM32F469I-DISCOVERY
- [HelloAudio](../Demos/F469/F469_HelloAudio/README.md) empty application + setup guide.
- [Record and Playback](../Demos/F469/F469_RecordPlayback/README.md) example that records audio and plays it back.
- [Multi Example](../Demos/F469/F469_MultiExample/README.md) project, containing multiple small examples for different classes of this project.

### Using NUCLEO-H755ZI-Q
- :warning: [HelloAudio](../Demos/H755/H755_HelloAudio/README.md) Currently not working


---
## Software structure
A very brief visualisation about the software hirarchy is displayed below.
<tr>
<td>
<div align="center">
    <img src="documentation/images/SoftwareStack.png" width="500"> 
</div>
</td>

---
### Detailed Software structure 
This view displays the relation between the key software components delivered by the BSP.
The Application must include only the **BSP_VoiceMailBox.h** header file, it already includes all relevant hardware components and software tools related to the VMB.

<tr>
<td>
<div align="center">
    <img src="documentation/images/SoftwareStructureOverview.png" width="800"> 
</div>
</td>


### Peripheral classes
- [AnalogPin](documentation/AnalogPin.md)
- [DigitalPin](documentation/DigitalPin.md)
- [I2C](documentation/I2C.md)
- [I2S](documentation/I2S.md)
- [UART](documentation/UART.md)
- [AudioCodec](documentation/AudioCodec.md)
  - [Codec_TLV320AIC3104](documentation/Codec_TLV320AIC3104.md)
- :satellite: [ATCommandClient](documentation/ATCommandClient.md)

### Data processing classes
- [File](documentation/File.md)
  - :musical_note: [WAV File](documentation/WAVFile.md)
  - :musical_note: [MP3 File](documentation/MP3File.md)
- MP3
  - :small_red_triangle_down: [MP3 Encoder](documentation/MP3_encoder.md)
  - :small_red_triangle: [MP3 Decoder](documentation/MP3_decoder.md)
- :microphone: [Audio Recorder](documentation/AudioRecorder.md)
- :speaker: [Audio Player](documentation/AudioPlayer.md)

### Other utilitiy classes
- :pencil: [Logger](documentation/Logger.md)
- :repeat: [Updatable](documentation/Updatable.md)
- :watch: [Timer](documentation/Timer.md)

### HAL abstraction
All HAL related functions are located in two files:
- **HAL_abstraction.hpp**: 
  Contains inline functions, encapsulating all HAL functions used in the BSP.
  Do not use HAL functions inside the BSP directly, that would break the software design of the HAL abstraction. If a new HAL function is needed, create a new inline function with the same name but a **VMB_** in front to signalize its the same function but specific for the BSP
- **interrupts.cpp**: 
  Contains all interrupt callbacks used in the BSP.
  Each class that uses interrupt callbacks, contains a static method that gets called in the interrupt callback to simplify the logic inside the HAL callback.

### :repeat: Update loop
The update loop is programmed in the Platform struct and handles the updating of all **Updatable** objects, clears the I2S flags if configured so and handles the updating of the systick counter for when an overflow occures.
For a smooth operation, this function must be called cyclically without any delays if possible.
You can see the function calls in almost all examples in the loop() function.

---
## Unfinished
- :construction: [TLV320AIC3104 Audio Codec](documentation/Codec_TLV320AIC3104.md) has only the most basic functions implemented and can be expanded to use its full potential.
  
---
## Needs to be implemented
- :construction: SPI class to communicate with the ESP32
- :construction: SPI compatibility with the [ATCommandClient](documentation/ATCommandClient.md) class in order to use SPI for sending and receiving AT-Commands. 
- :construction: NFC class to read NFC tags.