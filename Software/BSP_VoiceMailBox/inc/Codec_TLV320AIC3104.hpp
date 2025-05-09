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


namespace VoiceMailBox
{
	class Codec_TLV320AIC3104
	{
		// Register addresses
		struct REG {
			struct PAGE_0 {
				static constexpr uint8_t PAGE_SELECT = 0x00;
				static constexpr uint8_t SOFTWRE_RESET = 0x01;
				static constexpr uint8_t CODEC_SAMPLE_RATE_SELECT = 0x02;
				static constexpr uint8_t PLL_PROGRAMMING_A = 0x03;
				static constexpr uint8_t PLL_PROGRAMMING_B = 0x04;
				static constexpr uint8_t PLL_PROGRAMMING_C = 0x05;
				static constexpr uint8_t PLL_PROGRAMMING_D = 0x06;
				static constexpr uint8_t CODEC_DATA_PATH_SETUP = 0x07;
				static constexpr uint8_t AUDIO_SERIAL_DATA_INTERFACE_CONTROL_A = 0x08;
				static constexpr uint8_t AUDIO_SERIAL_DATA_INTERFACE_CONTROL_B = 0x09;
				static constexpr uint8_t AUDIO_SERIAL_DATA_INTERFACE_CONTROL_C = 0x0A;
				static constexpr uint8_t AUDIO_CODEC_OVERFLOW_FLAG = 0x0B;
				static constexpr uint8_t AUDIO_CODEC_DIGITAL_FILTER_CONTROL = 0x0C;
				static constexpr uint8_t HEADSET_BUTTON_PRESS_DETECTION_A = 0x0D;
				static constexpr uint8_t HEADSET_BUTTON_PRESS_DETECTION_B = 0x0E;
				static constexpr uint8_t LEFT_ADC_PGA_GAIN_CONTROL = 0x0F;
				static constexpr uint8_t RIGHT_ADC_PGA_GAIN_CONTROL = 0x10;
				static constexpr uint8_t MIC2_L_R_TO_LEFT_ADC_CONTROL = 0x11;
				static constexpr uint8_t MIC2_LINE2_TO_RIGHT_ADC_CONTROL = 0x12;
				static constexpr uint8_t MIC1LP_LINE1LP_TO_LEFT_ADC_CONTROL = 0x13;
				// RESERVED 0x14
				static constexpr uint8_t MIC1RP_LINE1RP_TO_LEFT_ADC_CONTROL = 0x15;
				static constexpr uint8_t MIC1RP_LINE1RP_TO_RIGHT_ADC_CONTROL = 0x16;
				// RESERVED 0x17
				static constexpr uint8_t MIC1LP_LINE1LP_TO_RIGHT_ADC_CONTROL = 0x18;
				static constexpr uint8_t MICBIAS_CONTROL = 0x19;
				static constexpr uint8_t LEFT_AGC_CONTROL_A = 0x1A;
				static constexpr uint8_t LEFT_AGC_CONTROL_B = 0x1B;
				static constexpr uint8_t LEFT_AGC_CONTROL_C = 0x1C;
				static constexpr uint8_t RIGHT_AGC_CONTROL_A = 0x1D;
				static constexpr uint8_t RIGHT_AGC_CONTROL_B = 0x1E;
				static constexpr uint8_t RIGHT_AGC_CONTROL_C = 0x1F;
				static constexpr uint8_t LEFT_AGC_GAIN = 0x20;
				static constexpr uint8_t RIGHT_AGC_GAIN = 0x21;
				static constexpr uint8_t LEFT_AGC_NOISE_GATE_DEBOUNCE = 0x22;
				static constexpr uint8_t RIGHT_AGC_NOISE_GATE_DEBOUNCE = 0x23;
				static constexpr uint8_t ADC_FLAG = 0x24;
				static constexpr uint8_t ADC_POWER_AND_OUTPUT_DRIVER_CONTROL = 0x25;
				static constexpr uint8_t HIGH_POWER_OUTPUT_DRIVER_CONTROL = 0x26;
				// RESERVED 0x27
				static constexpr uint8_t HIGH_POWER_OUTPUT_STAGE_CONTROL = 0x28;
				static constexpr uint8_t DAC_OUTPUT_SWITCHING_CONTROL = 0x29;
				static constexpr uint8_t OUTPUT_DRIVER_POP_REDUCTION = 0x2A;
				static constexpr uint8_t LEFT_DAC_DIGITAL_VOLUME_CONTROL = 0x2B;
				static constexpr uint8_t RIGHT_DAC_DIGITAL_VOLUME_CONTROL = 0x2C;
				// RESERVED 0x2D
				static constexpr uint8_t PGA_L_TO_HPLOUT_VOLUME_CONTROL = 0x2E;
				static constexpr uint8_t DAC_L1_TO_HPLOUT_VOLUME_CONTROL = 0x2F;
				// RESERVED 0x30
				static constexpr uint8_t PGA_R_TO_HPLOUT_VOLUME_CONTROL = 0x31;
				static constexpr uint8_t DAC_R1_TO_HPLOUT_VOLUME_CONTROL = 0x32;
				static constexpr uint8_t HPLOUT_OUTPUT_LEVEL_CONTROL = 0x33;
				// RESERVED 0x34
				static constexpr uint8_t PGA_L_TO_HPLCOM_VOLUME_CONTROL = 0x35;
				static constexpr uint8_t DAC_L1_TO_HPLCOM_VOLUME_CONTROL = 0x36;
				// RESERVED 0x37
				static constexpr uint8_t PGA_R_TO_HPLCOM_VOLUME_CONTROL = 0x38;
				static constexpr uint8_t DAC_R1_TO_HPLCOM_VOLUME_CONTROL = 0x39;
				static constexpr uint8_t HPLCOM_OUTPUT_LEVEL_CONTROL = 0x3A;
				// RESERVED 0x3B
				static constexpr uint8_t PGA_L_TO_HPROUT_VOLUME_CONTROL = 0x3C;
				static constexpr uint8_t DAC_L1_TO_HPROUT_VOLUME_CONTROL = 0x3D;
				// RESERVED 0x3E
				static constexpr uint8_t PGA_R_TO_HPROUT_VOLUME_CONTROL = 0x3F;
				static constexpr uint8_t DAC_R1_TO_HPROUT_VOLUME_CONTROL = 0x40;
				static constexpr uint8_t HPROUT_OUTPUT_LEVEL_CONTROL = 0x41;
				// RESERVED 0x42
				static constexpr uint8_t PGA_L_TO_HPRCOM_VOLUME_CONTROL = 0x43;
				static constexpr uint8_t DAC_L1_TO_HPRCOM_VOLUME_CONTROL = 0x44;
				// RESERVED 0x45
				static constexpr uint8_t PGA_R_TO_HPRCOM_VOLUME_CONTROL = 0x46;
				static constexpr uint8_t DAC_R1_TO_HPRCOM_VOLUME_CONTROL = 0x47;
				static constexpr uint8_t HPRCOM_OUTPUT_LEVEL_CONTROL = 0x48;
				// RESERVED 0x49 - 0x50
				static constexpr uint8_t PGA_L_TO_LEFT_LOP_M_VOLUME_CONTROL = 0x51;
				static constexpr uint8_t DAC_L1_TO_LEFT_LOP_M_VOLUME_CONTROL = 0x52;
				// RESERVED 0x53
				static constexpr uint8_t PGA_R_TO_LEFT_LOP_M_VOLUME_CONTROL = 0x54;
				static constexpr uint8_t DAC_R1_TO_LEFT_LOP_M_VOLUME_CONTROL = 0x55;
				static constexpr uint8_t LEFT_LOP_M_OUTPUT_LEVEL_CONTROL = 0x56;
				// RESERVED 0x57
				static constexpr uint8_t PGA_L_TO_RIGHT_LOP_M_VOLUME_CONTROL = 0x58;
				static constexpr uint8_t DAC_L1_TO_RIGHT_LOP_M_VOLUME_CONTROL = 0x59;
				// RESERVED 0x5A
				static constexpr uint8_t PGA_R_TO_RIGHT_LOP_M_VOLUME_CONTROL = 0x5B;
				static constexpr uint8_t DAC_R1_TO_RIGHT_LOP_M_VOLUME_CONTROL = 0x5C;
				static constexpr uint8_t RIGHT_LOP_M_OUTPUT_LEVEL_CONTROL = 0x5D;
				static constexpr uint8_t MODULE_POWER_STATUS = 0x5E;
				static constexpr uint8_t OUTPUT_DRIVER_SHORT_CIRCUIT_DETECTION_STATUS = 0x5F;
				static constexpr uint8_t STICKY_INTERRUPT_FLAGS = 0x60;
				static constexpr uint8_t REALTIME_INTERRUPT_FLAGS = 0x61;
				// RESERVED 0x62 - 0x64
				static constexpr uint8_t CLOCK = 0x65;
				static constexpr uint8_t CLOCK_GENERATION_CONTROL = 0x66;
				static constexpr uint8_t LEFT_AGC_NEW_PROGRAMMABLE_ATTACK_TIME = 0x67;
				static constexpr uint8_t LEFT_AGC_NEW_PROGRAMMABLE_DECAY_TIME = 0x68;
				static constexpr uint8_t RIGHT_AGC_NEW_PROGRAMMABLE_ATTACK_TIME = 0x69;
				static constexpr uint8_t RIGHT_AGC_NEW_PROGRAMMABLE_DECAY_TIME = 0x6A;
				static constexpr uint8_t NEW_PROGRAMMABLE_ADC_DIGITAL_PATH_AND_I2C_BUS_CONDITION = 0x6B;
				static constexpr uint8_t PASSIVE_ANALOG_SIGNAL_BYPASS_SELECTION_DURING_POWER_DOWN = 0x6C;
				static constexpr uint8_t DAC_QUIESCENT_CURRENT_AJUSTMENT = 0x6D;
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

		bool isDataReady() const { return m_dataReadyFlag; }
		bool isDataReadyAndClear()  { 
			bool dataReady = m_dataReadyFlag;
			m_dataReadyFlag = 0;
			return dataReady;
		}
		void clearDataReadyFlag() { m_dataReadyFlag = 0; }

		volatile int16_t* getRxBufPtr() { return m_inBufPtr; }
		volatile int16_t* getTxBufPtr() { return m_outBufPtr; }
		uint16_t getBufferSize() const { return m_dmaBufferSize/2; }


		void onI2S_DMA_TxRx_HalfCpltCallback();
		void onI2S_DMA_TxRx_CpltCallback();

		const I2S& getI2S() { return m_i2s; }

	private:
		void writeRegister(uint8_t registerAddress, uint8_t data);
		uint8_t readRegister(uint8_t registerAddress);

		uint8_t getCurrentRegisterPage();
		void setCurrentRegisterPage(uint8_t page);

		I2C m_i2c;
		uint8_t m_deviceAddress;
		DIGITAL_PIN m_nResetPin;
		I2S m_i2s; // I2S_HandleTypeDef*

		uint8_t m_currentRegisterPage = 0; // Current page number selected for accessing registers

		static constexpr uint16_t m_dmaBufferSize = 128; // Size of the DMA Pingpong-Buffer
		int16_t m_adcDataBuffer[m_dmaBufferSize]; // Buffer for ADC data
		int16_t m_dacDataBuffer[m_dmaBufferSize]; // Buffer for DAC data
		uint8_t m_dataReadyFlag = 0; // Flag to indicate if data is ready for processing
		volatile int16_t* m_inBufPtr;
		volatile int16_t* m_outBufPtr = &m_dacDataBuffer[0];

	};
}
#endif
