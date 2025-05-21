#ifndef MP3_ENCODER_HPP
#define MP3_ENCODER_HPP
/**
 * @author Alex Krieg
 */


#include "HAL_abstraction.hpp"
#include "utilities/File.hpp"
#include "peripherals/digitalPin.hpp"
#include <string>
#include "../Middlewares/ST/STM32_Audio/Codecs/SpiritDSP_MP3_Enc/inc/spiritMP3Enc.h"


namespace VoiceMailBox
{
	/**
	 * @brief This class uses the SPIRIT Audio Engine from STMicroelectronics to encode PCM data to MP3.
	 * @details
	 *   The encode method is called when the DMA interrupt (half complete and complete) has occurred. Not inside the ISR!
	 */
	class MP3_encoder
	{
	public:
		/**
		 * @brief Constructor
		 * @param sampleRate provided by the audio codec
		 * @param bitrate that defines the compression rate of the MP3 file.
		 * @param numChannels 1 or 2 (default=2) to specify if the audio signal is mono or stereo.
		 * 
		 * @details
		 * This is a copy of the SPIRIT DSP MP3 encoder API documentation:
		 *    Initialize MP3 encoder module.
		 *    valid initialization values:
		 *    numChannels:
		 *        1 or 2
		 *    sampleRate:
		 *        48000, 44100, 32000 (MPEG-1)
		 *        24000, 22050, 16000 (MPEG-2)
		 *        12000, 11025,  8000 (MPEG-2.5)
		 *    bitrateKbps:
		 *        32, 40, 48, 56, 64, 80, 96, 112, 128, 160, 192, 224, 256, 320 for MPEG-1 sampling rates
		 *        8,  16, 24, 32, 40, 48, 56, 64,  80,  96,  112, 128, 144, 160 for MPEG-2 sampling rates
		 *        8,  16, 24, 32, 40, 48, 56, 64 for MPEG-2.5 sampling rates
		 * 	  
		 *    If specified bitrate value not given in the table above, the encoder
		 *    produces free-format stream with specified bitrate (may be not supported by
		 *    some decoders).
		 */
		MP3_encoder(uint32_t sampleRate, uint32_t bitrateKbps, uint16_t numChannels);
		~MP3_encoder();

		/**
		 * @brief Encodes the given audio samples for Left and Right channel. to MP3 Frames.
		 * @param outputBuffer encoded data buffer that can be directly written to a file.
		 * @param inputBuffer Interleaved PCM data buffer (16-bit signed integer) [Left, Right, Left, Right...]
		 *                    This buffer must contain 576 samples (2 channels * 576 samples * 16 bits = 2304 bytes)
		 * @return the size of the output buffer in bytes
		 */
		uint32_t encode(int8_t*& outputBuffer, const int16_t* inputBuffer);


		uint32_t getSampleRate() const { return m_sampleRate; }
		uint32_t getBitrateKbps() const { return m_bitrateKbps; }
		uint32_t getNumChannels() const { return m_numChannels; }


	private:
		uint32_t m_sampleRate;
		uint32_t m_bitrateKbps;
		uint32_t m_numChannels;
		
		
		TMP3E_persist* m_persist = nullptr;
		TMP3E_scratch* m_scratch = nullptr;
		
		E_MP3E_STATUS m_encInitStatus;

		struct EncodedFrameData
		{
			uint32_t frameSize = 0;	// Size of the encoded frame in bytes
			int8_t* frameData = nullptr;	// Pointer to the encoded frame data
		};

		EncodedFrameData m_encodedFrameData[2];
		uint8_t m_encodedFrameIndexSwitch = 0;	// Switch between the two encoded frame data buffers
	};
}
#endif
