
All settings are tested on the STM32F469-Discovery Board


## SD-Card Setup
### IOC Settings
- **Connectivity->SDIO:**
  Mode = "SD 1 bit"
  DMA Setting:
  SDIO_RX, DMA2 Stream 3, Peripheral To Memory, Low
  SDIO_TX, DMA2 Stream 6, Memory To Peripheral, Low

- **System Core->NVIC:**
  SDIO global interrupt: Enabled, Preamption Priority = 0, Sub Priority = 0

- **Middleware and Software Packs:**
  FATFS:
  SD Card: ON
  Advanced Settings->SDIO:
  Use dma template: Enabled
  
  
## ESP32 Setup
### IOC Settigns
UART6 auf Stiftleiste CN12
ESP32:2 -- RX -- DiscoveryBoard(CN12:6 -- TX -- STM32:PC6)
ESP32:3 -- TX -- DiscoveryBoard(CN12:8 -- RX -- STM32:PC7)

Software:
UART6
Baud: 115200
DMA für UART6_RX & UART6_TX
NVIC->UART6 global interrupt ENABLED
