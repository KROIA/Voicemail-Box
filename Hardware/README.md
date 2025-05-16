# Hardware
This folder contains all HW-Files and descriptions

## Info
The name for the Microcontroller/Evaluation Boards will be abreviated in the instaructions as the following:
- Voicemail-Box Board: 	VMBB
- STM32F469-Disco:		F469
- Nucleo-H755:			H755
- X-Nucleo NFC8:		NFC8
- P-Mod ESP32:			PMOD
- ...

---

Place descision tree here...??


---
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
- [Go to partial BOM](BOM/BOM_partial.csv)
- [Go to full BOM](BOM/BOM_full.csv)

### Select Microcontroller Board in use
- [Configure Board for H755](H755/H755.md)
- [Configure Board for F469](F469/F469.md)

### Configure periperal Conections (for those which offer this feature)
- WLAN/BLE
	- [Configure WLAN/BLE using SPI](Config/SPI_WLAN.md)
	- [Configure WLAN/BLE using UART](Config/UART_WLAN.md)
- NFC
	- [Configure NFC using SPI](Config/SPI_NFC.md)
	- [Configure NFC using I2C](Config/I2C_NFC.md)

### Configure HW Features
- [Configure PSU](Config/PSU.md)
- [Configure Poti](Config/Poti.md)
- [Configure Audio](Config/Audio.md)
- [Configure LEDs](Config/Leds.md)
- [Configure Buttons](Config/Buttons.md)
- [Configure micro SD](Config/uSD.md)
