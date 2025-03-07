# PmodESP32

## Setup
### Communication via UART
Board STM32F469
UART6 auf Stiftleiste CN12
ESP32:2 -- RX -- DiscoveryBoard(CN12:6 -- TX -- STM32:PC6)
ESP32:3 -- TX -- DiscoveryBoard(CN12:8 -- RX -- STM32:PC7)

Software:
UART6
Baud: 115200
DMA für UART6_RX & UART6_TX
NVIC->UART6 global interrupt ENABLED