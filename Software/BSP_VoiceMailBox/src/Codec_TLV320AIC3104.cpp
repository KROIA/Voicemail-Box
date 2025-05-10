#include "Codec_TLV320AIC3104.hpp"
#include "platform.hpp"

// DEBUG
#include "BSP_VoiceMailBox.hpp"

namespace VoiceMailBox
{
	Codec_TLV320AIC3104::Codec_TLV320AIC3104(void* i2sHandle, void* i2cHandle, uint8_t deviceAddress, void* nResetPort, uint16_t nResetPin)
		: m_i2c(i2cHandle)
		, m_deviceAddress(deviceAddress)
		, m_nResetPin{ nResetPort, nResetPin }
		, m_i2s(i2sHandle, 512)
		, m_currentRegisterPage(0)
	{
#if ENABLE_CODEC_PERFORMANCE_MEASUREMENTS == 1
		m_i2s.setHalfCpltCallback([this]() { onI2S_DMA_TxRx_HalfCpltCallback(); });
		m_i2s.setCpltCallback([this]() { onI2S_DMA_TxRx_CpltCallback(); });
#endif
	}

	Codec_TLV320AIC3104::~Codec_TLV320AIC3104()
	{

	}

	void Codec_TLV320AIC3104::reset()
	{
		m_nResetPin.set(false); // Set nReset pin low
		Utility::delay(25); // Wait for 10ms
		m_nResetPin.set(true); // Set nReset pin high
		Utility::delay(25); // Wait for 10ms

		// Software reset
		writeRegister(REG::PAGE_0::SOFTWRE_RESET, 0x01); // Example register write for software reset
		Utility::delay(10); // Wait for 10ms
	}
	void Codec_TLV320AIC3104::setup()
	{
		reset(); // Reset the codec
		setCurrentRegisterPage(0); // Set the current register page to 0

		// Initialize codec registers
		writeRegister(REG::PAGE_0::PLL_PROGRAMMING_A, 0x10); //Disable PLL, 2 = 4. MCLK = 256 * 48Khz, fs(ref) = MCLK / (128 * Q)


		writeRegister(REG::PAGE_0::LEFT_ADC_PGA_GAIN_CONTROL,  0x00); //Un-mute left ADC PGA
		writeRegister(REG::PAGE_0::RIGHT_ADC_PGA_GAIN_CONTROL, 0x00); //Un-mute right ADC PGA
		writeRegister(REG::PAGE_0::MIC2_L_R_TO_LEFT_ADC_CONTROL, 0x0F); //Connect MIC2L/LINE2L to left ADC PGA (@0db gain), do not connect MIC2R/LINE2R to left ADC PGA
		writeRegister(REG::PAGE_0::MIC2_LINE2_TO_RIGHT_ADC_CONTROL, 0xF0); //Connect MIC2R/LINE2R to right ADC PGA (@0db gain), do not connect MIC2L/LINE2L to right ADC PGA
		writeRegister(REG::PAGE_0::MIC1LP_LINE1LP_TO_LEFT_ADC_CONTROL, 0x7C); //Power up left ADC
		writeRegister(REG::PAGE_0::MIC1RP_LINE1RP_TO_RIGHT_ADC_CONTROL, 0x7C); //Power up right ADC


		writeRegister(REG::PAGE_0::CODEC_DATA_PATH_SETUP, 0x0A); //fs(ref) = 48khz, left DAC data path plays left-channel input data, right DAC -> right-channel input data

		
		

		writeRegister(REG::PAGE_0::AUDIO_SERIAL_DATA_INTERFACE_CONTROL_B, 0x07); // Enable Re-Sync for ADC and DAC

		writeRegister(REG::PAGE_0::AUDIO_CODEC_DIGITAL_FILTER_CONTROL, 0x00); // Bypass digital filter
		writeRegister(REG::PAGE_0::AUDIO_SERIAL_DATA_INTERFACE_CONTROL_A, 0x00); // Disable 3D effect and others
		

		writeRegister(REG::PAGE_0::DAC_OUTPUT_SWITCHING_CONTROL, 0xA0); // Set Output-switch of DAC_L -> DAC_L2, DAC_R -> DAC_R2


		writeRegister(REG::PAGE_0::DAC_L1_TO_HPLOUT_VOLUME_CONTROL, 0x00); // Disconnect DAC_L1 from HPLOUT
		writeRegister(REG::PAGE_0::DAC_R1_TO_HPLOUT_VOLUME_CONTROL, 0x00); // Disconnect DAC_R1 from HPLOUT
		writeRegister(REG::PAGE_0::PGA_L_TO_HPLOUT_VOLUME_CONTROL, 0x00); // Disconnect PGA_L from HPLOUT
		writeRegister(REG::PAGE_0::PGA_R_TO_HPLOUT_VOLUME_CONTROL, 0x00); // Disconnect PGA_R from HPLOUT

		writeRegister(REG::PAGE_0::DAC_L1_TO_HPROUT_VOLUME_CONTROL, 0x00); // Disconnect DAC_L1 from HPROUT
		writeRegister(REG::PAGE_0::DAC_R1_TO_HPROUT_VOLUME_CONTROL, 0x00); // Disconnect DAC_R1 from HPROUT
		writeRegister(REG::PAGE_0::PGA_L_TO_HPROUT_VOLUME_CONTROL, 0x00); // Disconnect PGA_L from HPROUT
		writeRegister(REG::PAGE_0::PGA_R_TO_HPROUT_VOLUME_CONTROL, 0x00); // Disconnect PGA_R from HPROUT

		

		writeRegister(REG::PAGE_0::LEFT_DAC_DIGITAL_VOLUME_CONTROL, 0x00); //Unmute left DAC channel
		writeRegister(REG::PAGE_0::RIGHT_DAC_DIGITAL_VOLUME_CONTROL, 0x00); //Unmute right DAC channel
		writeRegister(REG::PAGE_0::HPLOUT_OUTPUT_LEVEL_CONTROL, 0x0B); //Unmute left line output (HPLOUT) @ 0dB gain
		writeRegister(REG::PAGE_0::HPROUT_OUTPUT_LEVEL_CONTROL, 0x0B); //Unmute right line output (HPROUT) @ 0dB gain


		writeRegister(REG::PAGE_0::ADC_POWER_AND_OUTPUT_DRIVER_CONTROL, 0xA0); //Power up left and right DAC



		//writeRegister(REG::PAGE_0::HIGH_POWER_OUTPUT_STAGE_CONTROL, 0x80); //Output common mode voltage = 1,65V (= VCC / 2)
		
		//writeRegister(REG::PAGE_0::DAC_L1_TO_LEFT_LOP_M_VOLUME_CONTROL, 0x80); //Route left DAC to left line output
		//writeRegister(REG::PAGE_0::LEFT_LOP_M_OUTPUT_LEVEL_CONTROL, 0x0B); //Unmute left line output
		writeRegister(REG::PAGE_0::CLOCK, 0x01); //CODEC_CLKIN uses CLKDIV_OUT

		// Setup I2S for DMA transmit and receive
		//m_i2s.setup_transmitReceive_DMA((uint16_t*)m_dacDataBuffer, (uint16_t*)m_adcDataBuffer, m_dmaBufferSize);
		m_i2s.setupDMA();
	}

	void Codec_TLV320AIC3104::onI2S_DMA_TxRx_HalfCpltCallback()
	{
		// Inside ISR context! 
#if ENABLE_CODEC_PERFORMANCE_MEASUREMENTS == 1
		m_DMA_halfTransferTick = Utility::getTickCount();
#endif
		setLed(LED::LED1, 1); // Set LED1 on		
	}
	void Codec_TLV320AIC3104::onI2S_DMA_TxRx_CpltCallback()
	{
		// Inside ISR context! 
#if ENABLE_CODEC_PERFORMANCE_MEASUREMENTS == 1
		m_DMA_halfProcessingTicks = Utility::getTickCount() - m_DMA_halfTransferTick;
#endif
		setLed(LED::LED1, 0); // Set LED1 off
	}


	void Codec_TLV320AIC3104::startDataProcessing()
	{
#if ENABLE_CODEC_PERFORMANCE_MEASUREMENTS == 1
		m_startDataProcessingTick = Utility::getTickCount();
#endif
	}
	void Codec_TLV320AIC3104::endDataProcessing()
	{
#if ENABLE_CODEC_PERFORMANCE_MEASUREMENTS == 1
		m_dataProcessingTicks = Utility::getTickCount() - m_startDataProcessingTick;
#endif
	}


	void Codec_TLV320AIC3104::writeRegister(uint8_t registerAddress, uint8_t data)
	{
		I2C::Status status = m_i2c.writeRegister(m_deviceAddress, registerAddress, data);
		if (status != I2C::Status::OK)
		{
			// Handle error
		}
	}

	uint8_t Codec_TLV320AIC3104::readRegister(uint8_t registerAddress)
	{
		uint8_t data = 0;
		I2C::Status status = m_i2c.readRegister(m_deviceAddress, registerAddress, data);
		if (status != I2C::Status::OK)
		{
			// Handle error
		}
		return data;
	}

	uint8_t Codec_TLV320AIC3104::getCurrentRegisterPage()
	{
		return readRegister(REG::PAGE_0::PAGE_SELECT); // Read the current register page
	}
	void Codec_TLV320AIC3104::setCurrentRegisterPage(uint8_t page)
	{
		writeRegister(REG::PAGE_0::PAGE_SELECT, page & 0x01); // Set the current register page
		m_currentRegisterPage = page & 0x01; // Update the current register page

		// Readback the current register page to verify
		uint8_t currentPage = getCurrentRegisterPage();
		if (currentPage != m_currentRegisterPage)
		{
			// Handle error
		}
	}


	
}
