



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
### IOC SEttigns
