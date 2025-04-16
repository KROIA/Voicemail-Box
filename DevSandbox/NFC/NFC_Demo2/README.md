# Voicemail-Box

## About
This is a description of how to change the settings of the example ST-Project for STM32F469-Disco to interact with the NFC evl Board.


## Steps for configuration (all in Cube)
- Disable Free RTOS (In my Case)
- Disable USB and FATFS (for completly clean project)

# Configure SPI
Enable SPI2 as Full-Dublex Master
Disable HW NSS

set Pins as following:
- MOSI = PB15
- MISO = PB14
- SCK  = PD3
- NSS  = PH6 -> set as GPIO Output

- Set Speed and configure Clock Mode for rising and falling ("DDR"-like)
