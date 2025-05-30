#ifndef CODEC_TLV320AIC3104_HPP
#define CODEC_TLV320AIC3104_HPP
/**
 * @brief This file contains the interface to the TLV320AIC3104 codec.
 * @details This codec is used to record and play audio data
 * 
 * @note Only the core features are implemented and tested.
*/



#include "HAL_abstraction.hpp"

#include "AudioCodec.hpp"
#include "digitalPin.hpp"
#include "i2c.hpp"
#include "i2s.hpp"
#include "utilities/Logger.hpp"



namespace VoiceMailBox
{
	class Codec_TLV320AIC3104 : public AudioCodec, public Logger
	{
		/**
		 * @brief Register map
		 * @details
		 * The Register map is divided into two pages.
		 * Page 0 contains the most important registers for the codec.
		 * @see setCurrentRegisterPage() and getCurrentRegisterPage() to change the page.
		 */
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
		/**
		 * @brief Constructor
		 * @param i2sHandle used to receive and transmit audio samples
		 * @param i2sBufferSize size for the i2s DMA buffer
		 * @param i2c used to configure the codec
		 * @param i2cDeviceAddress  of the codec on the I2C bus. Default address is 0x18
		 * @param resetPort port on which the reset pin is connected 
		 * @param resetPin  pin on the reset port
		 * @param resetPinIsInverted if true, the reset pin is active low, otherwise active high
		 */
		Codec_TLV320AIC3104(VMB_I2S_Handle* i2sHandle, uint16_t i2sBufferSize,
							I2C& i2c, uint8_t i2cDeviceAddress,
							VMB_GPIO* resetPort, uint16_t resetPin, bool resetPinIsInverted = true);
		~Codec_TLV320AIC3104();

		void reset();

		/**
		 * @brief Configures the codec and starts the I2S DMA
		 * @return true if successfull, otherwise false
		 */
		bool setup();

		/**
		 * @brief Start the DMA for i2s
		 * @return true if start was successful, otherwise false
		 */
		bool startDMA() override { return m_i2s.startDMA();	}

		/**
		 * @brief Stop the DMA for i2s
		 * @return true if stop was successful, otherwise false
		 */
		bool stopDMA() override { return m_i2s.stopDMA(); }

		/**
		 * @return true if a new batch of audio samples is ready to be processed.
		 */
		bool isDataReady() const override { return m_i2s.isDataReady(); }

		/**
		 * @brief Checks the data ready flag and clears it if it was set.
		 * @return true if a new batch of audio samples is ready to be processed.
		 */
		bool isDataReadyAndClearFlag() override { return m_i2s.isDataReadyAndClearFlag(); }

		/**
		 * @brief Clears the data ready flag.
		 */
		void clearDataReadyFlag() override { m_i2s.clearDataReadyFlag(); }

		/**
		 * @brief Gets the current ADC buffer pointer.
		 * @return current ADC buffer pointer
		 */
		volatile int16_t* getRxBufPtr() override { return m_i2s.getRxBufPtr(); }

		/**
		 * @brief Gets the current DAC buffer pointer.
		 * @return current DAC buffer pointer
		 */
		volatile int16_t* getTxBufPtr() override { return m_i2s.getTxBufPtr(); }

		/**
		 * @brief Gets the size of the ping and pong buffer.
		 * @return size of the ping and pong buffer
		 */
		uint32_t getBufferSize() const override { return m_i2s.getBufferSize(); }

		/**
		 * @brief Gets the sample rate of the audio codec
		 * @return samplerate [Hz]
		 */
		uint32_t getSampleRate() const override {
			return 48000; // The codec is always configured to 48kHz
		}

		/**
		 * @brief Gets the sample resolution
		 * @return amount of bits per sample
		 */
		uint16_t getBitsPerSample() const override {
			return 16; // The codec is always configured to 16 bit
		}

		/**
		 * @brief Gets the amount of channels
		 * @return 1 for mono and 2 for stereo
		 */
		uint16_t getNumChannels() const override {
			return 2; // The codec is always configured to 2 channels
		}

		/**
		 * @brief Sets all DAC values to 0.
		 */
		void clearTxBuf() override { m_i2s.clearTxBuf(); }
		
		/**
		 * @brief Gets the I2S Object.
		 * @return I2S object
		 */
		const I2S& getI2S() { return m_i2s; }

		// -----------------------------------------------------------------
		//    Performance measurements
		// -----------------------------------------------------------------
		/**
		 * @brief In order to use the function getProcessingTimeRatio(),
		 *        the function startDataProcessing() must be called on start of the data processing
		 * @note The VMB_ENABLE_CODEC_PERFORMANCE_MEASUREMENTS macro must be defined, otherwise this function does nothing
		 */
		void startDataProcessing() override;

		/**
		 * @brief In order to use the function getProcessingTimeRatio(),
		 *        the function endDataProcessing() must be called on end of the data processing
		 * @note The VMB_ENABLE_CODEC_PERFORMANCE_MEASUREMENTS macro must be defined, otherwise this function does nothing
		 */
		void endDataProcessing() override;

		/**
		 * @brief Returns the ratio of the processing time to the DMA transfer time
		 * @note The VMB_ENABLE_CODEC_PERFORMANCE_MEASUREMENTS macro must be defined, otherwise this function does nothing
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
		 *                 |              +--+			 +--+			+--+		   +--+
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
		float getProcessingTimeRatio() const override
		{
#ifdef VMB_ENABLE_CODEC_PERFORMANCE_MEASUREMENTS
			if (m_DMA_halfProcessingTicks == 0)
				return 0.0f;
			return static_cast<float>(m_dataProcessingTicks) / static_cast<float>(m_DMA_halfProcessingTicks);
#else
			return 1.0;
#endif
		}

		/**
		 * @brief Sets the input gain of the microphone for Left and Right
		 * @param db in a range from 0dB to 59.5dB in 0.5dB steps
		 */
		void setMicrophoneGainDB(float db);

	private:

		/**
		 * @brief Writes the data byte to the given register address of the codec.
		 * @param registerAddress which can be on page 0 or page 1.
		 * @param data byte to be set
		 * @return true if the write was successful, false otherwise
		 */
		bool writeRegister(uint8_t registerAddress, uint8_t data);

		/**
		 * @brief Reads a byte from the given register address of the codec.
		 * @param registerAddress which can be on page 0 or page 1.
		 * @return the register value of the selected register at the current selected register-page.
		 */
		uint8_t readRegister(uint8_t registerAddress);

		/**
		 * @brief Reads the current selected register-page
		 * @return 0 if page 0 is selected, 1 if page 1 is selected
		 */
		uint8_t getCurrentRegisterPage();

		/**
		 * @brief Select a specific register-page
		 * @param page to select. (0 or 1)
		 */
		void setCurrentRegisterPage(uint8_t page);

		// This functions must only be called from the I2S DMA interrupt context
		void onI2S_DMA_TxRx_HalfCpltCallback();
		void onI2S_DMA_TxRx_CpltCallback();

		I2C& m_i2c;
		uint8_t m_i2cDeviceAddress;
		DigitalPin m_resetPin;
		I2S m_i2s; 

		uint8_t m_currentRegisterPage = 0; // Current page number selected for accessing registers

		
		// Performance mesurements
#ifdef VMB_ENABLE_CODEC_PERFORMANCE_MEASUREMENTS
		uint32_t m_startDataProcessingTick = 0;
		uint32_t m_dataProcessingTicks = 0;
		uint32_t m_DMA_halfTransferTick = 0;
		uint32_t m_DMA_halfProcessingTicks = 0;
#endif
	};
}
#endif
