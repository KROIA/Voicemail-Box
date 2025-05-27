# Hello Audio Example
This Setup uses the NUCLEO-H755ZI-Q microcontroller board using the M7 core.

## IOC File Setup
---
### Buttons
Select the Pins and assign them the given function and user label.


| Pin      | Function    | User Label |
| -------- | ----------- | ---------- |
| PD15     | GPIO_Input  | BTN0       |
| PE11     | GPIO_Input  | BTN1       |
| PE14     | GPIO_Input  | BTN2       |
| PE13     | GPIO_Input  | BTN3       |

---
### Leds
Select the Pins and assign them the given function and user label.

| Pin      | Function    | User Label |
| -------- | ----------- | ---------- |
| PA8      | GPIO_Output | LED0       |
| PG12     | GPIO_Output | LED1       |

---
### Debug Pins
The debug pins are optional and only used when the macro **VMB_DEVELOPMENT_CONFIGURATION** is defined in the `settings.h`.
Select the Pins and assign them the given function and user label.

| Pin      | Function    | User Label |
| -------- | ----------- | ---------- |
| PD3      | GPIO_Output | DBG0       |
| PD4      | GPIO_Output | DBG1       |
| PD5      | GPIO_Output | DBG2       |


---
### Potentiometer
Enable the ADC's used in the **Analog** section
#### ADC1
- **Runtime contexts**: Enabled on Cortex-M7.
- **IN5**: IN5 Single-ended
  
#### ADC3
- **Runtime contexts**: Enabled on Cortex-M7.
- **IN1**: IN1 Single-ended
  

Select the Pins and assign them the given function and user label.

| Pin      | Function    | User Label |
| -------- | ----------- | ---------- |
| PB1      | ADC1_INP5   | POT0       |
| PC3      | ADC3_INP1   | POT1       |

---


### WIFI ESP32
#### UART
Enable **USART1** in the **Connectivity** section.
- **Runtime contexts**: Cortex-M7
- **Mode**: Asynchronous
- **Hardware Flow Control**: Disable



##### Parameter Settings
Let the settings to be default but check for the following:
- **Baud Rate**: 115200
- **Word Length**: 8 Bits
- **Parity**: None
- **Stop Bits**: 1

##### NVIC Settings
- **USART1 global interrupt**: Enabled


Select the Pins and assign them the given function.

| Pin      | Function    |
| -------- | ----------- | 
| PB6      | USART1_TX   | 
| PB7      | USART1_RX   |


---
### Debug Console
In order to enable the UART for the debug console as we need, 
the **Virtual Com Port** in the **BSP** section must be disabled.
After that, USART3 can be enabled. 

Enable **USART3** in the **Connectivity** section.
- **Runtime contexts**: Cortex-M7
- **Mode**: Asynchronous
- **Hardware Flow Control**: Disable

##### Parameter Settings
Let the settings to be default but check for the following:
- **Baud Rate**: 115200
- **Word Length**: 8 Bits
- **Parity**: None
- **Stop Bits**: 1

Select the Pins and assign them the given function.

| Pin      | Function    |
| -------- | ----------- | 
| PD8      | USART3_TX   | 
| PD9      | USART3_RX   |

---
### I2C
Enable **I2C1** in the **Connectivity** section.
- **Runtime contexts**: Cortex-M7
- **I2C**: I2C

Select the Pins and assign them the given function.

| Pin      | Function    |
| -------- | ----------- | 
| PB8      | I2C1_SCL    | 
| PB9      | I2C1_SDA    |
  
--- 
### SD Card
Since The SD-Card slot is on our custom board, we need to setup it manually.
Enable **SDMMC1** in the **Connectivity** section.
- **Runtime contexts**: Cortex-M7
- **Mode**: SD 1 bit

Select the Pin and assign them the given function.

| Pin      | Function    | User Label   |
| -------- | ----------- | ------------ |
| PG10     | GPIO_Input  | SD_DETECT    |
  
---
### Audio Codec
Enable **I2S2** in the **Multimedia** section.
- **Runtime contexts**: Cortex-M7
- **Mode**: Full-Duplex Master
- **Master Clock Output**: Enabled

Select the Pins and assign them the given function.

| Pin      | Function    |
| -------- | ----------- | 
| PB12     | I2S2_WS     | 
| PB13     | I2S2_CK     |
| PB14     | I2S2_SDI    |
| PB15     | I2S2_SDO    |
| PC6      | I2S2_MCK    |


##### Parameter Settings
- **Communication Standard**: I2S Philips
- **Data and Frame Format**: 16 Bits Data on 16 Bits Frame
- **Selected Audio Frequency**: 44KHz

#### Reset pin
Select the Pin and assign them the given function.

| Pin      | Function    | User Label   |
| -------- | ----------- | ------------ |
| PG14     | GPIO_Output | CODEC_NRESET |





---
### Project Properties
Open the **Properties** window for the CM7 sub project.

#### Includes
Navigate to **C/C++ General->Paths and Symbols**.
Click **Add** and paste the following path: `${ProjDirPath}/../../../BSP_VoiceMailBox/inc`.
This Path only works if the project was created in the same location as this project.
In the case, you create a project on a different location, you have to change the path accordingly.
Set the checkmarks: **Add to all configurations** and **Add to all languages**.
Confirm it by pressing the **OK** button.

Do the same again for the path: `Application/inc`

For some reason, FATFS is not added to both C and C++, check that by clicking on the languages **GNU C** and **GNU C++**. If the includes for FATFS are only on C, then add them to the C++ language too.


#### Source Locations
Clock **Link Folder** and check the checkmark **Link to folder in the file system**.
Click on **Variables...**, add a **New** variable and name it: `BSP_VoiceMailBox` and the location: `${PROJECT_LOC}\..\..\..\BSP_VoiceMailBox\src`.
Click **OK**, select the newly created variable and click **OK** again, and then again **OK**.
Now switch the **Configuration** to the other one (Debug -> Release or Release -> Debug).
Now click **Add Folder**, select **BSP_VoiceMailBox** from the list and click **OK**.

Add the **Application** source code folder by clicking **Add Folder** and selecting `Application`.
Do that for both configurations (Debug and Release).

#### Libraries
Navigate to **C/C++ Build->Settings**.


##### SpiritDSP MP3 
The spiritDSP MP3 library was used in the [X-CUBE-AUDIO](https://www.st.com/en/embedded-software/x-cube-audio.html) example and therefore also used in this Project.
###### MCU/MPU G++ Linker
Make sure to select both configurations: **All configurations**, on the top of the settings window. 
In the **Libraries** section, add the library: `_mp3decoder_cortex_m7_v2.2.0`.
Sadly there is no encoder library available for the M7. I don't know why and did't find it someware else.
A other MP3 encoder must be used and implemented which is not very straight forward.
An other way would be to use the M4 core. In that case it is the same way as it is for the F469 Discovery board.

Add the library search path: `${ProjDirPath}/../../../BSP_VoiceMailBox/Middlewares/ST/STM32_Audio/Codecs/SpiritDSP_MP3_Dec/lib`

###### MCU/MPU Settings
The floating point ABI must be set to **Mix HW/SW implementation**, otherwise the project will fail on build.

