#ifndef SETTINGS_H
#define SETTINGS_H
/**
 * @brief This file contains macro definitions and settings to 
 *        enable/disable/configure certain features in the VMB firmware.
 * 
 * @author Alex Krieg
 */

/**
 * @details	When defined, 3 Debug Pins are available to use in the application for debugging purposes.
 */
#define VMB_DEVELOPMENT_CONFIGURATION
#ifdef VMB_DEVELOPMENT_CONFIGURATION
	#define VMB_DEVELOPMENT_ENABLE_DBG_PINS_IN_CODEC
	#define VMB_DEVELOPMENT_ENABLE_DBG_PINS_IN_ATCOMMAND_CLIENT
#endif


/**
 * @details
 *	When defined, automatic performance measurement is enabled to track the Codecs 
 *  DMA processing time vs. signal processing time.
 *	This measurement is used to check if the Processing of the audio signal takes longer than the time, 
 *  the DMA takes to get new audio samples.
 *	Audio signal processing must be faster than the DMA time.
 *
 *	When disabled, the following function will be disabled and does nothing.
 *	Codec_TLV320AIC3104::getProcessingTimeRatio();
 */
#define VMB_ENABLE_CODEC_PERFORMANCE_MEASUREMENTS 


/**
 * @details
 *	When VMB_UART_USE_STATIC_BUFFER_SIZE is defined, all UART instances will use a
 *  static buffer size defined by VMB_UART_STATIC_BUFFER_SIZE.
 *	When VMB_UART_USE_STATIC_BUFFER_SIZE is not defined, each UART instance will use a
 *  dynamic buffer size defined by the constructor parameter.
 */
#define VMB_UART_USE_STATIC_BUFFER_SIZE
#define VMB_UART_STATIC_BUFFER_SIZE 1024*5

/**
 * @details
 *	Maximum number of UART instances.
 *	Adjust as needed.
 */
#define VMB_UART_MAX_INSTANCES 2

/**
 * @details
 *	When VMB_I2S_USE_STATIC_BUFFER_SIZE is defined, all I2S instances will use a 
 *  static buffer size defined by VMB_I2S_STATIC_BUFFER_SIZE.
 *	When VMB_I2S_USE_STATIC_BUFFER_SIZE is not defined, each I2S instance will use a
 *  dynamic buffer size defined by the constructor parameter.
 */
#define VMB_I2S_USE_STATIC_BUFFER_SIZE
//#define VMB_I2S_STATIC_BUFFER_SIZE 1024*50

// Since the MP3 encoder needs 576 sanmples per processing, the buffer size should be multiple of 576.
// Multiplication by 4 because of 2 channels (left and right) and PING and PONG buffers which are 2 halfs of the whole buffer size
// Multiplication by 10 to process 10 frames at once
#define VMB_I2S_STATIC_BUFFER_SIZE 576 * 4 * 2

/**
 * @details
 *	Maximum number of I2S instances.
 *	Adjust as needed.
 */
#define VMB_I2S_MAX_INSTANCES 1


#endif
