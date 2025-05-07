
## IOC File Settings

### Middleware and Software Packs:
	- FREERTOS:
		Disable



### Buttons:
	PIN(PA7):	BTN0
		User Label:	BTN0
	PIN(PA2):	BTN1
		User Label:	BTN1
	PIN(PG12):	BTN2
		User Label:	BTN2
	PIN(PA1):	BTN3
		User Label:	BTN3


### LEDS:
	PIN(PA6): 	LED0
		User Label: LED0
	PIN(PG12): 	LED1
		User Label: LED1
		
### Potis:
	PIN(PC4):	ADC1_IN14
		User Label:	POT0
	PIN(PC3):	ADC2_IN13
		User Label:	POT1
		
### WiFi:
	USART6:
		Baud Rate: 115200
		Word Length: 8 Bits (including parity)
		Parity: None
		Stop Bits: 1
		PIN(PG14): 	TX 
		PIN(PG9): 	RX
		DMA Settings:
			DMA für RX & TX
			Mode: Normal
		NVIC Settings:
			[x] USART6 global interrupt
	? PIN(PC5):			INT
	
### Debug Console:
	USART3:
		Baud Rate: 115200
		Word Length: 8 Bits (including parity)
		Parity: None
		Stop Bits: 1
		DMA Settings:
			DMA für RX & TX
			Mode: Normal
		NVIC Settings:
			[x] USART3 global interrupt
	
		
		
## Project Properties
		C/C++ General->Paths and Symbols:
			Includes:
				Add:
					Directory: ${ProjDirPath}/../../Software/BSP_VoiceMailBox/inc
					[x] Add to all configurations
					[x] Add to all languages
			Source Location:
				Link Folder:
					[x] Link to folder in file system
					Variables...
						New...
							Name: BSP_VoiceMailBox
							Location: ${PROJECT_LOC}/../../Software/BSP_VoiceMailBox/src
							OK
						Select the new created variable: BSP_VoiceMailBox
						OK
				OK
				