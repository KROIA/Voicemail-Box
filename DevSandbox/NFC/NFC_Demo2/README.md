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

Set Speed (less than 10MHz)and configure Clock Mode for rising and falling ("DDR"-like)  
![image](https://github.com/user-attachments/assets/d3cd274b-aa2c-4bb1-880d-82783c48b83e)

### Configure and connect Middleware
enable X-CUBE-NFC6 in Cube (found under Middleware)  
(will require install the first time used)  
![Pasted image (2)](https://github.com/user-attachments/assets/be88ad70-8a59-470d-8a49-159d236f064b)  

Cube throws error if no leds selected... to be tested
![image](https://github.com/user-attachments/assets/897531ae-f18b-4cae-8397-8062443a9687)

Pinout of GPIO can be seen here:
![image](https://github.com/KROIA/Voicemail-Box/blob/f469_NFC/Documentation/Pinout%20Demos/pinout.png?raw=true)





