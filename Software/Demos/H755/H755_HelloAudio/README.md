# Hello Audio Example
This Setup uses the NUCLEO-H755ZI-Q microcontroller board using the M7 core.

> [!CAUTION]  
> This board is not tested using this configuration
> Some steps may be faulty

> [!CAUTION]  
> MP3 encoding is not supported on the M7 
> In case MP3 needs to be used, use the M4 core.

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

##### NVIC Settings
- **USART3 global interrupt**: Enabled

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
- **Selected Audio Frequency**: 48KHz

##### NVIC Settings
- **SPI2 global interrupt**: Enabled

##### DMA Settings
- **I2S2_EXT_RX** using DMA1 Stream 3 Peripheral To Memory
  **Mode**: Circular
  **Data Width**: Half Word
<br>
- **SPI2_TX** using DMA1 Stream 4 Memory To Peripheral
  **Mode**: Circular
  **Data Width**: Half Word

#### Reset pin
Select the Pin and assign them the given function.

| Pin      | Function    | User Label   |
| -------- | ----------- | ------------ |
| PG14     | GPIO_Output | CODEC_NRESET |



---
## Create Application body
Follow the instructions on [How to call C++ code from C](../../../BSP_VoiceMailBox/documentation/CppFromC.md) to setup the Application body.

### Setup de BSP_VoiceMailBox
#### Microcontroller board selection
In the `main.h` add the following define.
It defines which board is selected to switch between the different HAL implementations in the BSP.
``` C
/* USER CODE BEGIN Private defines */
#define VMB_MICROCONTROLLER_BOARD__STM32F469I_DISCOVERY
/* USER CODE END Private defines */
``` 
---
#### Peripheral handle getter functions
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
#### Peripheral GPIOs
CUBE MX sometimes generates macros using the user labels from the IOC file. But for the H755 for example, that process is not made during code generation.
In that case these definitions must been made manually and look like this:
``` C
// Buttons
// BTN0 is on PD15
#define BTN0_GPIO_Port GPIOD
#define BTN0_Pin GPIO_PIN_15
// BTN1 is on PE11
#define BTN1_GPIO_Port GPIOE
#define BTN1_Pin GPIO_PIN_11
// BTN2 is on PE14
#define BTN2_GPIO_Port GPIOE
#define BTN2_Pin GPIO_PIN_14
// BTN3 is on PE13
#define BTN3_GPIO_Port GPIOE
#define BTN3_Pin GPIO_PIN_13

// LEDs
// LED0 is on PA8
#define LED0_GPIO_Port GPIOA
#define LED0_Pin GPIO_PIN_8
// LED1 is on PG12
#define LED1_GPIO_Port GPIOG
#define LED1_Pin GPIO_PIN_12

// Debug pins
// DBG0 is on PD3
#define DBG0_GPIO_Port GPIOD
#define DBG0_Pin GPIO_PIN_3
// DBG1 is on PD4
#define DBG1_GPIO_Port GPIOD
#define DBG1_Pin GPIO_PIN_4
// DBG2 is on PD5
#define DBG2_GPIO_Port GPIOD
#define DBG2_Pin GPIO_PIN_5


// Audio codec
// CODEC_NRESET is on PG14
#define CODEC_NRESET_GPIO_Port GPIOG
#define CODEC_NRESET_Pin GPIO_PIN_14
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
### Project Properties
Open the **Properties** window for the CM7 sub project.
Navigate to **C/C++ General->Paths and Symbols**.

#### Includes
Click **Add** and paste the following path: `${ProjDirPath}/../../../../BSP_VoiceMailBox/inc`.
This Path only works if the project was created in the same location as this project.
In the case, you create a project on a different location, you have to change the path accordingly.
Set the checkmarks: **Add to all configurations** and **Add to all languages**.
Confirm it by pressing the **OK** button.

For some reason, FATFS may not added to both C and C++, check that by clicking on the languages **GNU C** and **GNU C++**. If the includes for FATFS are only on C, then add them to the C++ language too.


#### Source Locations
Click **Link Folder** and check the checkmark **Link to folder in the file system**.
Click on **Variables...**, add a **New** variable and name it: `BSP_VoiceMailBox` and the location: `${PROJECT_LOC}\..\..\..\..\BSP_VoiceMailBox\src`.
Click **OK**, select the newly created variable and click **OK** again, and then again **OK**.
Now switch the **Configuration** to the other one (Debug -> Release or Release -> Debug).
Now click **Add Folder**, select **BSP_VoiceMailBox** from the list and click **OK**.

#### Libraries
##### SpiritDSP MP3 
The spiritDSP MP3 library was used in the [X-CUBE-AUDIO](https://www.st.com/en/embedded-software/x-cube-audio.html) example and therefore also used in this Project.
- In the `Libraries` section click on `Add...` and fill the following in the dialog:
  - **File**: `_mp3decoder_cortex_m7_v2.2.0`
  - **Add to all configurations**: `checked`
  - **Add to all languages**: `checked`
   `OK`
<br>
<br>

- In the `Library Paths` section click on `Add...` and fill the following in the dialog:
  - **Directory**: `${ProjDirPath}/../../../../BSP_VoiceMailBox/Middlewares/ST/STM32_Audio/Codecs/SpiritDSP_MP3_Dec/lib`
  - **Add to all configurations**: `checked`
  - **Add to all languages**: `checked`
   `OK`
<br>
<br>

> [!CAUTION]  
> Sadly there is no encoder library available for the M7. I don't know why and did't find it someware else.
A other MP3 encoder must be used and implemented which is not very straight forward.
An other way would be to use the M4 core. In that case it is the same way as it is for the F469 Discovery board.

###### Floating point unit settings
Navigate to `C/C++ Build->Settings` and in the `MCU/MPU Settings` set the **floating point ABI** to `Mix HW/SW implementation`, otherwise the project will not compile.
Do that for both configurations: **Debug** and **Release**
