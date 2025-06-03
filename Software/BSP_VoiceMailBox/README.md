# BSP Voice Mail Box

## About
The Voice-Mail-Box Project (VMB in short) provides a Board Support Package (BSP) that abstracts all key peripheral components using c++.

---
## Content
- [Software structure](#software-structure)
  - [Detailed Software structure overview](#detailed-software-structure-overview)
  - [Peripheral classes](#peripheral-classes)
  - [Data processing classes](#data-processing-classes)
- [Demos](#demos)
  - [Using STM32F469I-DISCOVERY](#using-stm32f469i-discovery)
  - [Using NUCLEO-H755ZI-Q](#using-nucleo-h755zi-q)
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
## Software structure
A very brief visualisation about the software hirarchy is displayed below.
<tr>
<td>
<div align="center">
    <img src="documentation/images/SoftwareStack.png" width="500"> 
</div>
</td>

---
### Detailed Software structure overview 
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
  - [TLV320AIC3104](documentation/TLV320AIC3104.md)
- [ATCommandClient](documentation/ATCommandClient.md)

### Data processing classes
- [File](documentation/File.md)
  - [WAV File](documentation/WAVFile.md)
  - [MP3 File](documentation/MP3File.md)
- MP3
  - [MP3 Encoder](documentation/MP3_encoder.md)
  - [MP3 Decoder](documentation/MP3_decoder.md)
- [Audio Recorder](documentation/AudioRecorder.md)
- [Audio Player](documentation/AudioPlayer.md)

### Other utilities
- [Logger](documentation/Logger.md)
- [Updatable](documentation/Updatable.md)
- [Timer](documentation/Timer.md)

---
## Demos
### Using STM32F469I-DISCOVERY
- [HelloAudio](../Demos/F469/F469_HelloAudio/README.md) empty application + setup guide.
- [Record and Playback](../Demos/F469/F469_RecordPlayback/README.md) example that records audio and plays it back.
- [Multi Example](../Demos/F469/F469_MultiExample/README.md) project, containing multiple small examples for different classes of this project.

### Using NUCLEO-H755ZI-Q
- [HelloAudio](../Demos/H755/H755_HelloAudio/README.md) Currently not working

---
## Unfinished
- [TLV320AIC3104 Audio Codec](documentation/TLV320AIC3104.md) has only the most basic functions implemented and can be expanded to use its full potential.
---
## Needs to be implemented
- SPI class to communicate with the ESP32
- SPI compatibility with the [ATCommandClient](documentation/ATCommandClient.md) class in order to use SPI for sending and receiving AT-Commands. 
- NFC class to read NFC tags.