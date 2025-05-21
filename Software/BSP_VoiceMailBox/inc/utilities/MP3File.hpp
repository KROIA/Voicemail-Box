#ifndef MP3_FILE_HPP
#define MP3_FILE_HPP
/**
 * @author Alex Krieg
 */

#include "settings.h"
#include "Logger.hpp"
#include "HAL_abstraction.hpp"
#include "File.hpp"
#include "MP3_encoder.hpp"
#include "MP3_decoder.hpp"
#include <stdint.h>
#include <string>

namespace VoiceMailBox
{
	/**
	 * @brief This class handles the encoding and decoding of mp3 files.
	 * 
	 * @details A simple interface is provided for easy writing and reading of audio samples.
	 *          When writing, the given PCM audio samples are converted to mp3 before they are written to the file.
	 *          When reading, the mp3 data is decoded to PCM audio samples.
	 */
	class MP3File : public Logger
	{
	public:
		/**
		 * @brief Constructor
		 * @param sampleRate that is used to encode and decode the audio samples
		 * @param bitrate for the compression rate of the mp3 file.
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
		 *    bitrate:
		 *        32, 40, 48, 56, 64, 80, 96, 112, 128, 160, 192, 224, 256, 320 for MPEG-1 sampling rates
		 *        8,  16, 24, 32, 40, 48, 56, 64,  80,  96,  112, 128, 144, 160 for MPEG-2 sampling rates
		 *        8,  16, 24, 32, 40, 48, 56, 64 for MPEG-2.5 sampling rates
		 * 	  
		 *    If specified bitrate value not given in the table above, the encoder
		 *    produces free-format stream with specified bitrate (may be not supported by
		 *    some decoders).
		 */
		MP3File(uint32_t sampleRate, uint16_t bitrate, uint16_t numChannels);
		~MP3File();

		/**
		 * @brief Opens a file for reading or writing.
		 * @param filePath to the mp3 file. Example: "myAudio.mp3"
		 * @param mode if read or write ...
		 * @return true if the file was opened successfully, false otherwise.
		 */
		bool open(const std::string& filePath, File::AccessMode mode)
		{
			return m_file.open(filePath, mode);
		}

		/**
		 * @brief Closes the file
		 * @return true if the file was closed successfully, false otherwise.
		 */
		bool close()
		{
			return m_file.close();
		}

		/**
		 * @return true if the file is open, false otherwise.
		 */
		bool isOpen() const { return m_file.isOpen(); }

		/**
		 * @return the current path to the file.
		 */
		std::string getPath() const { return m_file.getPath(); }

		/**
		 * @brief Writes the given audio samples to the file.
		 * @param data to the sample array
		 * @param sampleCount to specify the amount of samples to be stored. This is not the the array length. 
		 *                    The array length is sampleCount * 2 (for stereo) or sampleCount (for mono).
		 * @return the amount of bytes written to the file.
		 */
		uint32_t writeAudioSamples(const int16_t* data, uint32_t sampleCount);

		/**
		 * @brief Reads the given amount of audio samples from the file to the given data buffer.
		 * @param data array in which the audio samples are stored.
		 * @param sampleCount to specify how many PCM samples should be read from the file. This is not the array length of the provided data buffer.
		 *                    The array length is sampleCount * 2 (for stereo) or sampleCount (for mono).
		 * @return the amount of decoded samples from the file.
		 */
		uint32_t readAudioSamples(int16_t* data, uint32_t sampleCount);

	private:
		static unsigned int decoderReadCallback(
			void* pMP3CompressedData,
			unsigned int nMP3DataSizeInChars,
			void* pUserData);

		uint8_t m_sampleSize; // Size in bytes per sample. 1 sample = Left + Right channel @ 16 bits per channel --> 4 bytes
		File m_file;

		
		MP3_encoder m_encoder;
		MP3_decoder m_decoder;
	};
}
#endif