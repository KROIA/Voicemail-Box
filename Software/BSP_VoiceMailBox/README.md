# BSP Voice Mail Box

## About
The Voice-Mail-Box Project (VMB in short) provides a Board Support Package (BSP) that abstracts all key peripheral components using c++.

## Overview
A very brief visualisation about the software hirarchy is displayed below.
<tr>
<td>
<div align="center">
    <img src="documentation/images/SoftwareStack.png" width="500"> 
</div>
</td>

## Detailed Software structure overview 
This view displays the relation between the key software components delivered by the BSP.
The Application must include only the **BSP_VoiceMailBox.h** header file, it already includes all relevant hardware components and software tools related to the VMB.

<tr>
<td>
<div align="center">
    <img src="documentation/images/SoftwareStructureOverview.png" width="800"> 
</div>
</td>


## Peripheral classes
- [AnalogPin](documentation/AnalogPin.md)
- [DigitalPin](documentation/DigitalPin.md)
- [I2C](documentation/I2C.md)
- [I2S](documentation/I2S.md)
- [UART](documentation/UART.md)
- [AudioCodec](documentation/AudioCodec.md)
  - [TLV320AIC3104](documentation/TLV320AIC3104.md)
- [ATCommandClient](documentation/ATCommandClient.md)

## Data processing classes
- [File](documentation/File.md)
  - [WAV File](documentation/WAVFile.md)
  - [MP3 File](documentation/MP3File.md)
- MP3
  - [MP3 Encoder](documentation/MP3Encoder.md)
  - [MP3 Decoder](documentation/MP3Decoder.md)
- [Audio Recorder](documentation/AudioRecorder.md)
- [Audio Player](documentation/AudioPlayer.md)

## Demos
### STM32F469I-DISCOVERY
- [HelloAudio](../Demos/F469/F469_HelloAudio/README.md) empty application