# HelloAudio for the F469
The HelloAudio example is just a empty application ready to expand on.
Copy the project in case you want to develop a custom application.

Below is a setup guide that describes step by step how to configure a completly new project for the Voice Mail Box platform. It uses the **STM32F469I-DISCOVERY** board.
> [!WARNING]  
> Read each instruction carfully since there are many pitfalls. 

## Content
- [Project creation](#project-creation)
- [IOC File Setup](#ioc-file-setup)
  - [Disable unused parts](#disable-unused-parts)
  - [Buttons](#buttons)
  - [Leds](#leds)
  - [Debug Pins](#debug-pins)
  - [Potentiometer](#potentiometer)
  - [WIFI ESP32](#wifi-esp32)
  - [Debug Console](#debug-console)
  - [I2C](#i2c)
  - [Audio Codec](#audio-codec)
- [Create Application body](#create-application-body)
- [Setup de BSP_VoiceMailBox](#setup-de-bsp_voicemailbox)
  - [Microcontroller board selection](#microcontroller-board-selection)
  - [Peripheral handle getter functions](#peripheral-handle-getter-functions)
  - [Peripheral GPIOs](#peripheral-gpios)
  - [Basic Application using the BSP_VoiceMailBox](#basic-application-using-the-bsp_voicemailbox)
- [Project Properties](#project-properties)
  - [Includes](#includes)
  - [Source Locations](#source-locations)
  - [Libraries](#libraries)
    - [SpiritDSP MP3](#spiritdsp-mp3)
- [Compiler errors](#compiler-errors)

---
## Project creation
Create a new STM32 Project and select the Board: **STM32F469I-DISCO** in the **Board Selector** window.
Select Target Language **C++**
Initialize all peripherals in default mode. 



## IOC File Setup
### Disable unused parts
#### Connectivity
- Disable I2C2
- QUADSPI

#### Multimedia
- SAI1

#### Middleware and Software Packages
- FREERTOS, we don't use a OS.
---
### Buttons
Select the Pins and assign them the given function and user label.


| Pin      | Function    | User Label |
| -------- | ----------- | ---------- |
| PA7      | GPIO_Input  | BTN0       |
| PA2      | GPIO_Input  | BTN1       |
| PG12     | GPIO_Input  | BTN2       |
| PA1      | GPIO_Input  | BTN3       |

---
### Leds
Select the Pins and assign them the given function and user label.

| Pin      | Function    | User Label |
| -------- | ----------- | ---------- |
| PA6      | GPIO_Output | LED0       |
| PG11     | GPIO_Output | LED1       |

---
### Debug Pins
The debug pins are optional and only used when the macro **VMB_DEVELOPMENT_CONFIGURATION** is defined in the `settings.h`.
Select the Pins and assign them the given function and user label.

| Pin      | Function    | User Label |
| -------- | ----------- | ---------- |
| PC7      | GPIO_Output | DBG0       |
| PC13     | GPIO_Output | DBG1       |
| PA4      | GPIO_Output | DBG2       |


---
### Potentiometer
Select the Pins and assign them the given function and user label.

| Pin      | Function    | User Label |
| -------- | ----------- | ---------- |
| PC4      | ADC1_IN14   | POT0       |
| PC3      | ADC2_IN13   | POT1       |

---
### WIFI ESP32
#### UART
Enable **USART6** in the **Connectivity** section.
- **Mode**: Asynchronous
- **Hardware Flow Control**: Disable



##### Parameter Settings
Let the settings to be default but check for the following:
- **Baud Rate**: 115200
- **Word Length**: 8 Bits
- **Parity**: None
- **Stop Bits**: 1

##### NVIC Settings
- **USART6 global interrupt**: Enabled


Select the Pins and assign them the given function.

| Pin      | Function    |
| -------- | ----------- | 
| PG14     | USART1_TX   | 
| PG9      | USART1_RX   |


---
### Debug Console
Enable **USART3** in the **Connectivity** section.
- **Mode**: Asynchronous
- **Hardware Flow Control**: Disable

##### Parameter Settings
Let the settings to be default but check for the following:
- **Baud Rate**: 115200
- **Word Length**: 8 Bits
- **Parity**: None
- **Stop Bits**: 1

##### NVIC Settings
- **USART3 global interrupt**: Enabled

Select the Pins and assign them the given function.

| Pin      | Function    |
| -------- | ----------- | 
| PB10     | USART3_TX   | 
| PB11     | USART3_RX   |

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
#### System Core
##### NVIC
- **SDIO global interrupt**: ON
#### Connectivity
##### SDIO
- **Mode**: SD 1 bit
###### DMA Setting
- SDIO_RX, DMA2 Stream 3, Peripheral To Memory, Low
- SDIO_TX, DMA2 Stream 6, Memory To Peripheral, Low
#### Middleware and Software Packs
##### FATFS
- **SD Card**: ON
###### Advanced Settings->SDIO:
- **Use dma template**: Enabled
  
---
### Audio Codec
Enable **I2S2** in the **Multimedia** section.
- **Mode**: Full-Duplex Master
- **Master Clock Output**: Enabled

Select the Pins and assign them the given function.

| Pin      | Function    |
| -------- | ----------- | 
| PB12     | I2S2_WS     | 
| PB13     | I2S2_CK     |
| PC1      | I2S2_SD     |
| PC2      | I2S2_ext_SD |
| PC6      | I2S2_MCK    |


##### Parameter Settings
- **Communication Standard**: I2S Philips
- **Data and Frame Format**: 16 Bits Data on 16 Bits Frame
- **Selected Audio Frequency**: 48KHz

#### Reset pin
Select the Pin and assign them the given function.

| Pin      | Function    | User Label   |
| -------- | ----------- | ------------ |
| PG13     | GPIO_Output | CODEC_NRESET |


---
## Create Application body
Follow the instructions on [How to call C++ code from C](../../../BSP_VoiceMailBox/documentation/CppFromC.md) to setup the Application body.

---
## Setup de BSP_VoiceMailBox
### Microcontroller board selection
In the `main.h` add the following define.
It defines which board is selected to switch between the different HAL implementations in the BSP.
``` C
/* USER CODE BEGIN Private defines */
#define VMB_MICROCONTROLLER_BOARD__STM32F469I_DISCOVERY
/* USER CODE END Private defines */
``` 
---
### Peripheral handle getter functions
To get access to the peripheral handles, the following code must be inserted in the `main.h`:

``` C
/* USER CODE BEGIN EFP */

/**
 * @brief The BSP of the Voice Mail Box needs to access the different peripheral handles generated by the CubeMX.
 * @details
 * When porting the project to a different microcontroller, these getters have to be manually declared here,
 * implemented in the main.cpp and used in the Platform.cpp.
 */
ADC_HandleTypeDef* getADC_POT0();
ADC_HandleTypeDef* getADC_POT1();

UART_HandleTypeDef* getUART_DEBUG();
UART_HandleTypeDef* getUART_WIFI();

I2C_HandleTypeDef* getI2C_Handle();
I2S_HandleTypeDef* getI2S_CODEC();

/* USER CODE END EFP */
```

Implement the functions in the `main.c`.
The instance name may be different. You can find the correct name in the `main.c` on the top where CUBE MX has generated the structs instances.
``` C
/* USER CODE BEGIN PV */
ADC_HandleTypeDef* getADC_POT0()
{
    return &hadc1;
}
ADC_HandleTypeDef* getADC_POT1()
{
    return &hadc2;
}
UART_HandleTypeDef* getUART_DEBUG()
{
    return &huart3;
}
UART_HandleTypeDef* getUART_WIFI()
{
    return &huart6;
}
I2C_HandleTypeDef* getI2C_Handle()
{
    return &hi2c1;
}
I2S_HandleTypeDef* getI2S_CODEC()
{
    return &hi2s2;
}
/* USER CODE END PV */
```
---
### Peripheral GPIOs
CUBE MX sometimes generates macros using the user labels from the IOC file. But for the H755 for example, that process is not made during code generation.
In that case these definitions must been made manually and look like this:
``` C
#define BTN0_Pin GPIO_PIN_7
#define BTN0_GPIO_Port GPIOA
// ... Other pins
```
That macros will be used in the `Platform.cpp` for creating the `DigitalPin` instances.

``` C++
// Inside the Platform.cpp
// Fill in the GPIO_TypeDef* and pin values, generated from the CUBEMX for the buttons
DigitalPin& Platform::getButton(Button index)
{
    // Creating static instances of the DigitalPin class for each button
    // The constructor of the DigitalPin class takes the <GPIO_TypeDef*>, <pin number> and <isInverted> as parameters
    // On this board the buttons are active high, so the isInverted parameter is set to false or can be omitted
    static DigitalPin button[] = 
    {
        { BTN0_GPIO_Port, BTN0_Pin },  // <---
        { BTN1_GPIO_Port, BTN1_Pin },
        { BTN2_GPIO_Port, BTN2_Pin },
        { BTN3_GPIO_Port, BTN3_Pin }
    };
    return button[index];
}
```
Make sure you use the same macro names as they already are used in the `Platform.cpp`, so that the `Platform.cpp` can be let unchanged. Otherwise the `Platform.cpp` must be edited to fit your custom peripheral GOPIO macro names.

---
### Basic Application using the BSP_VoiceMailBox
Replace the empty Application by the following code

``` C++
// Application.cpp
#include "Application.h"
#include "BSP_VoiceMailBox.hpp"

void setup()
{
    VoiceMailBox::setup();
}

void loop()
{
    VoiceMailBox::update();
}

```
---
## Project Properties
Open the **Properties** window for the project.
Navigate to C/C++ General->Paths and Symbols.

### Includes
Click **Add** and paste the following path: `${ProjDirPath}/../../../BSP_VoiceMailBox/inc`.
The path may be different, depending on where the project got created, but in this case the include path is specified relative to the current projects path.
In the case, you create a project on a different location, you have to change the path accordingly.
Set the checkmarks: **Add to all configurations** and **Add to all languages**.
Confirm it by pressing the **OK** button.

For some reason, FATFS may not added to both C and C++, check that by clicking on the languages **GNU C** and **GNU C++**. If the includes for FATFS are only on C, then add them to the C++ language too.


### Source Locations
Click **Link Folder** and check the checkmark **Link to folder in the file system**.
Click on **Variables...**, add a **New** variable and name it: `BSP_VoiceMailBox` and the location: `${PROJECT_LOC}\..\..\..\BSP_VoiceMailBox\src`.
Click **OK**, select the newly created variable and click **OK** again, and then again **OK**.
Now switch the **Configuration** to the other one (Debug -> Release or Release -> Debug).
Now click **Add Folder**, select **BSP_VoiceMailBox** from the list and click **OK**.

### Libraries
#### SpiritDSP MP3 
The spiritDSP MP3 library was used in the [X-CUBE-AUDIO](https://www.st.com/en/embedded-software/x-cube-audio.html) example and therefore also used in this Project.
- In the `Libraries` section click on `Add...` and fill the following in the dialog:
  - **File**: `_mp3decoder_cortex_m4_v2.2.0`
  - **Add to all configurations**: `checked`
  - **Add to all languages**: `checked`
   `OK`
<br>
- In the `Libraries` section click on `Add...` and fill the following in the dialog:
  - **File**: `_mp3encoder_cortex_m4_v2.2.0`
  - **Add to all configurations**: `checked`
  - **Add to all languages**: `checked`
   `OK`
<br>
<br>
- In the `Library Paths` section click on `Add...` and fill the following in the dialog:
  - **Directory**: `${ProjDirPath}/../../../BSP_VoiceMailBox/Middlewares/ST/STM32_Audio/Codecs/SpiritDSP_MP3_Dec/lib`
  - **Add to all configurations**: `checked`
  - **Add to all languages**: `checked`
   `OK`
<br>
- In the `Library Paths` section click on `Add...` and fill the following in the dialog:
  - **Directory**: `${ProjDirPath}/../../../BSP_VoiceMailBox/Middlewares/ST/STM32_Audio/Codecs/SpiritDSP_MP3_Enc/lib`
  - **Add to all configurations**: `checked`
  - **Add to all languages**: `checked`
   `OK`
<br>
<br>


###### Floating point unit settings
Navigate to `C/C++ Build->Settings` and in the `MCU/MPU Settings` set the **floating point ABI** to `Mix HW/SW implementation`, otherwise the project will not compile.
Do that for both configurations: **Debug** and **Release**




---
## Compiler errors
#### False floating point setting
Error: `F469_HelloAudio.elf uses VFP register arguments`
Means the [FPU setting](#floating-point-unit-settings) is not correct. 


#### No peripheral handle getter functions
Error: `'getADC_POT0' was not declared in this scope`
Or similar errors related to the `Platform.cpp` mean that there is no get function for the needed peripheral handle structs. [See here](#peripheral-handle-getter-functions) how to resolve the issue.



#### No peripheral GPIO macros defined
Error: `'BTN0_Pin' undeclared`
Or similar errors related to the `Platform.cpp` mean that there are undefined macros which must be defined in the `main.h`. [See here](#peripheral-gpios) how to resolve the issue.

#### No settings header
Error: `No settings header included, make sure to provide a custom settings header in the main.h file when VMB_CUSTOM_SETTINGS_HEADER is defined!`
If you use custom settings, make sure to not only define the macro `VMB_CUSTOM_SETTINGS_HEADER` but also include a custom settings header in the `main.h` that provides all settings needed for the BSP.
