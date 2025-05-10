#ifndef CODEC_TLV320AIC3104_HPP
#define CODEC_TLV320AIC3104_HPP

/*
	Author:		Alex Krieg
	Created on:	May 9, 2025

*/

#include <stdint.h>
#include "digitalPin.hpp"
#include "i2c.hpp"
#include "i2s.hpp"


#define ENABLE_CODEC_PERFORMANCE_MEASUREMENTS 1  // Set to 0 to disable performance measurements

namespace VoiceMailBox
{
	class Codec_TLV320AIC3104
	{
		// Register addresses
		struct REG {
			struct PAGE_0 {                                                                                //  DECIMAL
				static constexpr uint8_t PAGE_SELECT = 0x00;											   //   0
				static constexpr uint8_t SOFTWRE_RESET = 0x01;											   //   1
				static constexpr uint8_t CODEC_SAMPLE_RATE_SELECT = 0x02;								   //   2
				static constexpr uint8_t PLL_PROGRAMMING_A = 0x03;										   //   3 
				static constexpr uint8_t PLL_PROGRAMMING_B = 0x04;										   //   4
				static constexpr uint8_t PLL_PROGRAMMING_C = 0x05;										   //   5
				static constexpr uint8_t PLL_PROGRAMMING_D = 0x06;										   //   6 
				static constexpr uint8_t CODEC_DATA_PATH_SETUP = 0x07;									   //   7
				static constexpr uint8_t AUDIO_SERIAL_DATA_INTERFACE_CONTROL_A = 0x08;					   //   8
				static constexpr uint8_t AUDIO_SERIAL_DATA_INTERFACE_CONTROL_B = 0x09;					   //   9
				static constexpr uint8_t AUDIO_SERIAL_DATA_INTERFACE_CONTROL_C = 0x0A;					   //  10
				static constexpr uint8_t AUDIO_CODEC_OVERFLOW_FLAG = 0x0B;								   //  11
				static constexpr uint8_t AUDIO_CODEC_DIGITAL_FILTER_CONTROL = 0x0C;						   //  12
				static constexpr uint8_t HEADSET_BUTTON_PRESS_DETECTION_A = 0x0D;						   //  13
				static constexpr uint8_t HEADSET_BUTTON_PRESS_DETECTION_B = 0x0E;						   //  14
				static constexpr uint8_t LEFT_ADC_PGA_GAIN_CONTROL = 0x0F;								   //  15
				static constexpr uint8_t RIGHT_ADC_PGA_GAIN_CONTROL = 0x10;								   //  16
				static constexpr uint8_t MIC2_L_R_TO_LEFT_ADC_CONTROL = 0x11;							   //  17
				static constexpr uint8_t MIC2_LINE2_TO_RIGHT_ADC_CONTROL = 0x12;						   //  18
				static constexpr uint8_t MIC1LP_LINE1LP_TO_LEFT_ADC_CONTROL = 0x13;						   //  19
				// RESERVED 0x14																		   //
				static constexpr uint8_t MIC1RP_LINE1RP_TO_LEFT_ADC_CONTROL = 0x15;						   //  21
				static constexpr uint8_t MIC1RP_LINE1RP_TO_RIGHT_ADC_CONTROL = 0x16;					   //  22
				// RESERVED 0x17																		   //
				static constexpr uint8_t MIC1LP_LINE1LP_TO_RIGHT_ADC_CONTROL = 0x18;					   //  24
				static constexpr uint8_t MICBIAS_CONTROL = 0x19;										   //  25
				static constexpr uint8_t LEFT_AGC_CONTROL_A = 0x1A;										   //  26
				static constexpr uint8_t LEFT_AGC_CONTROL_B = 0x1B;										   //  27
				static constexpr uint8_t LEFT_AGC_CONTROL_C = 0x1C;										   //  28
				static constexpr uint8_t RIGHT_AGC_CONTROL_A = 0x1D;									   //  29
				static constexpr uint8_t RIGHT_AGC_CONTROL_B = 0x1E;									   //  30
				static constexpr uint8_t RIGHT_AGC_CONTROL_C = 0x1F;									   //  31
				static constexpr uint8_t LEFT_AGC_GAIN = 0x20;											   //  32
				static constexpr uint8_t RIGHT_AGC_GAIN = 0x21;											   //  33
				static constexpr uint8_t LEFT_AGC_NOISE_GATE_DEBOUNCE = 0x22;							   //  34
				static constexpr uint8_t RIGHT_AGC_NOISE_GATE_DEBOUNCE = 0x23;							   //  35
				static constexpr uint8_t ADC_FLAG = 0x24;												   //  36
				static constexpr uint8_t ADC_POWER_AND_OUTPUT_DRIVER_CONTROL = 0x25;					   //  37
				static constexpr uint8_t HIGH_POWER_OUTPUT_DRIVER_CONTROL = 0x26;						   //  38
				// RESERVED 0x27																		   //
				static constexpr uint8_t HIGH_POWER_OUTPUT_STAGE_CONTROL = 0x28;						   //  40
				static constexpr uint8_t DAC_OUTPUT_SWITCHING_CONTROL = 0x29;							   //  41
				static constexpr uint8_t OUTPUT_DRIVER_POP_REDUCTION = 0x2A;							   //  42
				static constexpr uint8_t LEFT_DAC_DIGITAL_VOLUME_CONTROL = 0x2B;						   //  43
				static constexpr uint8_t RIGHT_DAC_DIGITAL_VOLUME_CONTROL = 0x2C;						   //  45
				// RESERVED 0x2D																		   //
				static constexpr uint8_t PGA_L_TO_HPLOUT_VOLUME_CONTROL = 0x2E;							   //  46
				static constexpr uint8_t DAC_L1_TO_HPLOUT_VOLUME_CONTROL = 0x2F;						   //  47
				// RESERVED 0x30																		   //
				static constexpr uint8_t PGA_R_TO_HPLOUT_VOLUME_CONTROL = 0x31;							   //  49
				static constexpr uint8_t DAC_R1_TO_HPLOUT_VOLUME_CONTROL = 0x32;						   //  50
				static constexpr uint8_t HPLOUT_OUTPUT_LEVEL_CONTROL = 0x33;							   //  51
				// RESERVED 0x34																		   //
				static constexpr uint8_t PGA_L_TO_HPLCOM_VOLUME_CONTROL = 0x35;							   //  53
				static constexpr uint8_t DAC_L1_TO_HPLCOM_VOLUME_CONTROL = 0x36;						   //  54
				// RESERVED 0x37																		   //  
				static constexpr uint8_t PGA_R_TO_HPLCOM_VOLUME_CONTROL = 0x38;							   //  56
				static constexpr uint8_t DAC_R1_TO_HPLCOM_VOLUME_CONTROL = 0x39;						   //  57
				static constexpr uint8_t HPLCOM_OUTPUT_LEVEL_CONTROL = 0x3A;							   //  58
				// RESERVED 0x3B																		   //
				static constexpr uint8_t PGA_L_TO_HPROUT_VOLUME_CONTROL = 0x3C;							   //  60
				static constexpr uint8_t DAC_L1_TO_HPROUT_VOLUME_CONTROL = 0x3D;						   //  61
				// RESERVED 0x3E																		   //
				static constexpr uint8_t PGA_R_TO_HPROUT_VOLUME_CONTROL = 0x3F;							   //  63
				static constexpr uint8_t DAC_R1_TO_HPROUT_VOLUME_CONTROL = 0x40;						   //  64
				static constexpr uint8_t HPROUT_OUTPUT_LEVEL_CONTROL = 0x41;							   //  65
				// RESERVED 0x42																		   //
				static constexpr uint8_t PGA_L_TO_HPRCOM_VOLUME_CONTROL = 0x43;							   //  67
				static constexpr uint8_t DAC_L1_TO_HPRCOM_VOLUME_CONTROL = 0x44;						   //  68
				// RESERVED 0x45																		   //
				static constexpr uint8_t PGA_R_TO_HPRCOM_VOLUME_CONTROL = 0x46;							   //  70
				static constexpr uint8_t DAC_R1_TO_HPRCOM_VOLUME_CONTROL = 0x47;						   //  71
				static constexpr uint8_t HPRCOM_OUTPUT_LEVEL_CONTROL = 0x48;							   //  72
				// RESERVED 0x49 - 0x50																	   //
				static constexpr uint8_t PGA_L_TO_LEFT_LOP_M_VOLUME_CONTROL = 0x51;						   //  81
				static constexpr uint8_t DAC_L1_TO_LEFT_LOP_M_VOLUME_CONTROL = 0x52;					   //  82
				// RESERVED 0x53																		   //
				static constexpr uint8_t PGA_R_TO_LEFT_LOP_M_VOLUME_CONTROL = 0x54;						   //  84
				static constexpr uint8_t DAC_R1_TO_LEFT_LOP_M_VOLUME_CONTROL = 0x55;					   //  85
				static constexpr uint8_t LEFT_LOP_M_OUTPUT_LEVEL_CONTROL = 0x56;						   //  86
				// RESERVED 0x57																		   //
				static constexpr uint8_t PGA_L_TO_RIGHT_LOP_M_VOLUME_CONTROL = 0x58;					   //  88
				static constexpr uint8_t DAC_L1_TO_RIGHT_LOP_M_VOLUME_CONTROL = 0x59;					   //  89
				// RESERVED 0x5A																		   //
				static constexpr uint8_t PGA_R_TO_RIGHT_LOP_M_VOLUME_CONTROL = 0x5B;					   //  91
				static constexpr uint8_t DAC_R1_TO_RIGHT_LOP_M_VOLUME_CONTROL = 0x5C;					   //  92
				static constexpr uint8_t RIGHT_LOP_M_OUTPUT_LEVEL_CONTROL = 0x5D;						   //  93
				static constexpr uint8_t MODULE_POWER_STATUS = 0x5E;									   //  94
				static constexpr uint8_t OUTPUT_DRIVER_SHORT_CIRCUIT_DETECTION_STATUS = 0x5F;			   //  95
				static constexpr uint8_t STICKY_INTERRUPT_FLAGS = 0x60;									   //  96
				static constexpr uint8_t REALTIME_INTERRUPT_FLAGS = 0x61;								   //  97
				// RESERVED 0x62 - 0x64																	   //
				static constexpr uint8_t CLOCK = 0x65;													   //  101
				static constexpr uint8_t CLOCK_GENERATION_CONTROL = 0x66;								   //  102
				static constexpr uint8_t LEFT_AGC_NEW_PROGRAMMABLE_ATTACK_TIME = 0x67;					   //  103
				static constexpr uint8_t LEFT_AGC_NEW_PROGRAMMABLE_DECAY_TIME = 0x68;					   //  104
				static constexpr uint8_t RIGHT_AGC_NEW_PROGRAMMABLE_ATTACK_TIME = 0x69;					   //  105
				static constexpr uint8_t RIGHT_AGC_NEW_PROGRAMMABLE_DECAY_TIME = 0x6A;					   //  106
				static constexpr uint8_t NEW_PROGRAMMABLE_ADC_DIGITAL_PATH_AND_I2C_BUS_CONDITION = 0x6B;   //  107
				static constexpr uint8_t PASSIVE_ANALOG_SIGNAL_BYPASS_SELECTION_DURING_POWER_DOWN = 0x6C;  //  108
				static constexpr uint8_t DAC_QUIESCENT_CURRENT_AJUSTMENT = 0x6D;						   //  109
				// RESERVED 0x6E - 0x7F
			};
			struct PAGE_1 {

			};
		};



	public:
		// 0x18 is the default address for the TLV320AIC3104
		Codec_TLV320AIC3104(void* i2sHandle, 
						    void* i2cHandle, uint8_t deviceAddress,
							void* nResetPort, uint16_t nResetPin);
		~Codec_TLV320AIC3104();

		void reset();
		void setup();

		bool isDataReady() const { return m_i2s.isDataReady(); }
		bool isDataReadyAndClear() { return m_i2s.isDataReadyAndClear(); }
		void clearDataReadyFlag() { m_i2s.clearDataReadyFlag(); }

		volatile int16_t* getRxBufPtr() { return m_i2s.getRxBufPtr(); }
		volatile int16_t* getTxBufPtr() { return m_i2s.getTxBufPtr(); }
		uint16_t getBufferSize() const { return m_i2s.getBufferSize(); }


		

		const I2S& getI2S() { return m_i2s; }


		// Performance measurements

		/**
		 * @brief In order to use the function getProcessingTimeRatio(),
		 *        the function startDataProcessing() must be called on start of the data processing
		 */
		void startDataProcessing();

		/**
		 * @brief In order to use the function getProcessingTimeRatio(),
		 *        the function endDataProcessing() must be called on end of the data processing
		 */
		void endDataProcessing();

		/**
		 * @brief Returns the ratio of the processing time to the DMA transfer time
		 * @details: The ratio is calculated as follows:
		 * 
		 * 	               |  DMA has new data ready      DMA has new data ready  
		 *                 |           \                  /          \
		 * 	               |            \                /            \
		 * 	               |             +--------------+			   +--------------+			  
		 * 	               |             |              |	t_dma      |	t_dma	  |			   
		 * 	               |             |              |<------------>|<------------>| 			   
		 * 	          DMA  | ------------+              +--------------+			  +---
		 * 	               |
		 *				   |              +--+			 +--+			+--+		   +--+				  
		 * 	               |              |  |			 |  |		    |  |		   |  |				   
		 * 	               |              |  | 			 |  | 			|  | 		   |  | 			   
		 * Data Processing | -------------+  +-----------+  +-----------+  +-----------+  +---
		 *                 |             /    \                         
		 *                 |            /      \                        |<>|<--------->| 
		 *                 |Data Processing     Data Processing         t_p    t_idle
		 *                 |     Start               End
		 *                 +--------------------------------------------------------------> Time
		 * 
		 *		
		 *		t_dma: Time it takes for a half DMA transfer. After each half DMA transfer, a new processing workload is ready.
		 *        t_p: Time it takes to process the data.
		 *	   t_idle: Time it takes to wait for the next half DMA transfer until new data is available.
		 * 
		 *        The ratio is calculated as follows:
		 *		  Ratio = t_p / t_dma
		 *		  
		 * The ratio is used to determine if the processing time is too long compared to the DMA transfer time.	
		 * If the ratio is greater than 1, it means that the processing time is longer than the DMA transfer time.
		 * The value should be in the range of 0 to 1, where 0 means, that processing is so fast,
		 * the processor is idle most of the time.
		 * When the ratio near 1, it means that there is not much margin for processing time. 
		 * 
		 * The ratio can be lowered, by increasing the DMA buffer size. 
		 * But this will increase the latency of the system.
		 * 
		 * @return Processing time ratio
		 */
		float getProcessingTimeRatio() const
		{
#if ENABLE_CODEC_PERFORMANCE_MEASUREMENTS == 1
			if (m_DMA_halfProcessingTicks == 0)
				return 0.0f;
			return static_cast<float>(m_dataProcessingTicks) / static_cast<float>(m_DMA_halfProcessingTicks);
#else
			return 1.0;
#endif
		}

	private:
		void writeRegister(uint8_t registerAddress, uint8_t data);
		uint8_t readRegister(uint8_t registerAddress);

		uint8_t getCurrentRegisterPage();
		void setCurrentRegisterPage(uint8_t page);

		// This functions must only be called from the I2S DMA interrupt context
		void onI2S_DMA_TxRx_HalfCpltCallback();
		void onI2S_DMA_TxRx_CpltCallback();

		I2C m_i2c;
		uint8_t m_deviceAddress;
		DIGITAL_PIN m_nResetPin;
		I2S m_i2s; 

		uint8_t m_currentRegisterPage = 0; // Current page number selected for accessing registers

		
		// Performance mesurements
#if ENABLE_CODEC_PERFORMANCE_MEASUREMENTS == 1
		uint32_t m_startDataProcessingTick = 0;
		uint32_t m_dataProcessingTicks = 0;
		uint32_t m_DMA_halfTransferTick = 0;
		uint32_t m_DMA_halfProcessingTicks = 0;
#endif
	};
}
#endif
