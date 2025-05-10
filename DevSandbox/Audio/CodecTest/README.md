

## Setup
Multimedia->
	SAI1->
		Master with master Clock Out
		[X] I2S/PCM Protocol
		NVIC Setings->
			SAI1 global interrupt: Enabled
		Parameter Settings->
			Basic Parameters->
				Audio Mode: Master Receive
			Clock Parameters->
				Audio Frequency: 48kHz
		DMA Settings->
			SAI1_A, DMA2 Stream1, Peripheral to Memory
			Mode: Circular
			Data Width: Half Word
			