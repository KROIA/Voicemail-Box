# Hardware
This folder contains all HW-Files and documentation of how to use them

## Info
The name for the Microcontroller/Evaluation Boards will be abreviated in the instructions as the following:
- Voicemail-Box Board: 	VMBB
- STM32F469-Disco:		F469
- Nucleo-H755:			H755
- X-Nucleo NFC8:		NFC8
- P-Mod ESP32:			PMOD
- ...

## Orientation
All jumper/switch settings asume that the board is orientet like this image unless otherwise specified.   
<img src=../Hardware/Picture/20250507_130009.jpg width="500">

Here is a schematic view where jumpers are also labled:  
<img src=../Hardware/Diagramms/HardwareJumper-Overview.png width="500">

## HW Setup
The VMBB is made to be soldered in a full and a partial configuration as well as beeing compatible with
multiple Microcontrollerboards (F469 and H755)

The partial configuration is made for people that are inexperienced with soldering / are lacking equipment.  

The full configuration is made as the de-facto correct way of manufacturing at the cost off beeing way more difficult to produce.

> [!CAUTION]  
> When fully soldering the NFC part will likely require a microscope  
> and the Wifi part will require an aditional USB to UART Converter with 3.3V logic level write the flash memory of ESP32.

to use one or the other, select the correct BOM to solder and only solder the mentioned parts. There are no differences in the use of the finished board.

- tbd: make the BOMs and a assembly plan
- tbd: add pictures

### Soldering
There is no need to solder all possible parts on the pcb. Select the configuration you prefer and only solder the parts in the corresponding BOM.The [Assembly Plan](PCB/Fab/voicemail-box-F_Fab.pdf) shows the position and most of the part Values.
- [Go to partial BOM](PCB/BOM/voicemail-box_partial.csv)
- [Go to full BOM](PCB/BOM/voicemail-box_full.csv)

> [!NOTE]  
> If you want to edit the PCB files I recommend using KICAD with the KiVar Plugin

## Select Microcontroller Board in use (get the correct Jumper settings)
- [Configure Board for H755](Config/H755/H755.md)
- [Configure Board for F469](Config/F469/F469.md)

## Configure periperal Conections (for those which offer this feature)
Some devices can use different Connection Interfaces offereing different benefits.
This is due to the fact, that this is an development board.  
In a specific use, you would select one and ignore the other one.

## WLAN/BLE
Wireless connection can be made either through UART or SPI  
While SPI is way faster, it is more complicated to set up
- [Configure WLAN/BLE using SPI](Config/SPI_WLAN.md)
- [Configure WLAN/BLE using UART](Config/UART_WLAN.md)
## NFC
NFC can be read-out either through I2C or SPI  
While SPI is way faster and is tested.
I2C would help in case that there is a pin-limitation of the final project.
- F469
    - [Configure NFC using SPI](Config/F469/NFC_SPI_F469.md)
    - [Configure NFC using I2C](Config/F469/NFC_I2C_F469.md) 
- H755
    - [Configure NFC using SPI](Config/H755/NFC_SPI_H755.md)
    - [Configure NFC using I2C](Config/H755/NFC_I2C_H755.md) 

## Configure HW Features
- [Configure PSU](Config/PSU.md)
- [Configure Poti](Config/Poti.md)
- [Configure Audio](Config/Audio.md)
- [Configure LEDs](Config/Leds.md)
- [Configure Buttons](Config/Buttons.md)
- [Configure micro SD](Config/uSD.md)
