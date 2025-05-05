
- Connectivity->ETH:
	Disable on both M7 & M4



- Connectivity->SDMMC1:
  Mode = "SD 1 bit"
  NVIC:
	SDMMC1 global interrupt: Enabled
  DMA Setting:
	? Nicht gefunden?: SDIO_RX, DMA2 Stream 3, Peripheral To Memory, Low
	? Nicht gefunden?: SDIO_TX, DMA2 Stream 6, Memory To Peripheral, Low

- WiFi-Modul:
	USART1:
		Enabled on M4
		DMA für RX and TX
		PIN(PB6): 	USART1_TX 
		PIN(PB7): 	USART1_RX
	? PIN(PC2):			INT
	


- I2S2 (I2S_A, Dataflow(STM32->Codec)):
	Enabled on M4
	? HalfDuplexMasterTransmit
	[x] Master Clock Output
	Parameter Settings:
		Selected Audio Frequency: 44KHz
	GPIO Settings:
		PIN(PB12): I2S2_WS
		PIN(PB13): I2S2_CK
		PIN(PB15): I2S2_SDO
		PIN(PC6): I2S_MCK
	NVIC Settings:
		SPI2 global interrupt: Enabled 
	DMA Settings:
		SPI2_TX:
			Mode: Circular
			Data Width: Half Word
	
- I2S3 (I2S_B, Dataflow(Codec->STM32)):
	Enabled on M4
	? HalfDuplexMasterReceive
	? [x] Master Clock Output
	Parameter Settings:
		Selected Audio Frequency: 44KHz
	GPIO Settings:
		PIN(PA15): I2S3_WS
		PIN(PB3): I2S3_CK
		PIN(PC7): I2S3_MCK
		PIN(PC11): I2S3_SDI
		? PIN(PB4):              I2S_SDA_ext
		? PIN(PG14): 		    CODEC_nReset  
	NVIC Settings:
		SPI3 global interrupt: Enabled
	DMA Settings:
		SPI3_RX:
			Mode: Circular
			Data Width: Half Word
		
- I2C1 (Codec config):
	Enabled on M4
	GPIO Settings:
		PIN(PB8):	I2C1_SCL
		PIN(PB9): 	I2C1_SDA
	DMA Settings:
		I2C1_TX:
			Mode: Normal
			Data Width: Byte
		I2S1_RX:
			Mode: Normal
			Data Width: Byte
			
- SPI1 (SPI2 auf dem Schema, NFC-Reader):
	Enabled on M4
	Full-Duplex Master
	Hardware NSS Output Signal
	GPIO Settings:
		PIN(PA4): 	SPI1_NSS
		PIN(PB3):	SPI1_SCK
		PIN(PB5):	SPI1_MOSI
		PIN(PG9):	SPI1_MISO
		? PIN(PA3): NFC_INT 
	DMA Settings:
		SPI1_RX:
			Mode: Circular
			Data Width: Byte
		SPI1_TX:
			Mode: Circular
			Data Width: Byte
	NVIC Settings:
		DMA1 stream2 global interrupt: Enabled
		DMA1 stream6 global interrupt: Enabled
		SPI1 global interrupt: Enabled
		

- LEDS:
	PIN(PA8): 	LED0
		User Label: LED0
		Pin Context Assignment: ARM Cortex-M4
	PIN(PG12): 	LED1
		User Label: LED1
		Pin Context Assignment: ARM Cortex-M4

- Buttons:
	PIN(PD15):	BTN0
		User Label:	BTN0
		Pin Context Assignment: ARM Cortex-M4
	PIN(PE11):	BTN1
		User Label:	BTN1
		Pin Context Assignment: ARM Cortex-M4
	PIN(PE14):	BTN2
		User Label:	BTN2
		Pin Context Assignment: ARM Cortex-M4
	PIN(PE13):	BTN3
		User Label:	BTN3
		Pin Context Assignment: ARM Cortex-M4
		
- Potis:
	PIN(PB1):	ADC1_INP5
		User Label:	POT0
		Pin Context Assignment: ARM Cortex-M4
	PIN(PC1):	ADC1_INP11
		User Label:	POT1
		Pin Context Assignment: ARM Cortex-M4