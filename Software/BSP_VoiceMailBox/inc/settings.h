#ifndef SETTINGS_H
#define SETTINGS_H
/**
 * @brief This file contains macro definitions and settings to 
 *        enable/disable/configure certain features in the VMB firmware.
 * 
 * @author Alex Krieg
 */


// Define one of the following macros in the main.h
//#define VMB_MICROCONTROLLER_BOARD__STM32F469I_DISCOVERY
//#define VMB_MICROCONTROLLER_BOARD__STM32NUCLEO_H755ZI_Q



#if defined(VMB_MICROCONTROLLER_BOARD__STM32F469I_DISCOVERY) + defined(VMB_MICROCONTROLLER_BOARD__STM32NUCLEO_H755ZI_Q) != 1
	#error "Exactly one platform must be defined!"
#endif

// ------------------------------------------------------------------------------------------------
// ===================================== D E B U G G I N G ========================================
// ------------------------------------------------------------------------------------------------
/**
 * @details	When defined, 3 Debug Pins are available to use in the application for debugging purposes.
 */
#define VMB_DEVELOPMENT_CONFIGURATION
#ifdef VMB_DEVELOPMENT_CONFIGURATION
	#define VMB_DEVELOPMENT_ENABLE_DBG_PINS_IN_CODEC
	#define VMB_DEVELOPMENT_ENABLE_DBG_PINS_IN_ATCOMMAND_CLIENT
#endif

// Logger
// If this macro is defined, the Logger class gets compilated into the project.
// If this macro is not defined, all logging calls will be removed completly from the project. 
#define VMB_USE_LOGGER_OBJECTS

// If this macro is defined, all objects derived by the logger class will be enabled by default.
// Otherwise the logger functionality of these objects must be enabled explicitly by calling the function Logger::enableLogging().
#define VMB_LOGGER_OBJECTS_ENABLED_BY_DEFAULT


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

// ------------------------------------------------------------------------------------------------
// ================================================================================================
// ------------------------------------------------------------------------------------------------






// ------------------------------------------------------------------------------------------------
// ========================================== U A R T =============================================
// ------------------------------------------------------------------------------------------------
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
 * @brief Specifies the static buffer size for the UART instances.
 * @details
 *	Maximum number of UART instances.
 *	Adjust as needed.
 */
#define VMB_UART_MAX_INSTANCES 2

// ------------------------------------------------------------------------------------------------
// ================================================================================================
// ------------------------------------------------------------------------------------------------






// ------------------------------------------------------------------------------------------------
// =========================================== I 2 S ==============================================
// ------------------------------------------------------------------------------------------------
/**
 * @details
 *	When VMB_I2S_USE_STATIC_BUFFER_SIZE is defined, all I2S instances will use a 
 *  static buffer size defined by VMB_I2S_STATIC_BUFFER_SIZE.
 *	When VMB_I2S_USE_STATIC_BUFFER_SIZE is not defined, each I2S instance will use a
 *  dynamic buffer size defined by the constructor parameter.
 */
#define VMB_I2S_USE_STATIC_BUFFER_SIZE

/**
 * @brief Defines the static buffer size for the I2S instances.
 * @details
 * Since the MP3 encoder needs 576 sanmples per processing, the buffer size should be multiple of 576.
 * Multiplication by 4 because of 2 channels (left and right) and PING and PONG buffers which are 2 halfs of the whole buffer size
 * Multiplication by 10 to process 10 frames at once
 */
#define VMB_I2S_STATIC_BUFFER_SIZE 576 * 4 * 10

/**
 * @brief Defines the static buffer size for the I2S instances.
 * @details
 *	Maximum number of I2S instances.
 *	Adjust as needed.
 */
#define VMB_I2S_MAX_INSTANCES 1

// ------------------------------------------------------------------------------------------------
// ================================================================================================
// ------------------------------------------------------------------------------------------------


// ------------------------------------------------------------------------------------------------
// ========================== I N T E R N A L   L E D   U S A G E =================================
// ------------------------------------------------------------------------------------------------

/**
 * @details
 *	When VMB_USE_INTERNAL_LEDS is defined, the internal LEDs are used.
 *	When VMB_USE_INTERNAL_LEDS is not defined, the internal LEDs are not used.
 */
#define VMB_USE_INTERNAL_LEDS


// ------------------------------------------------------------------------------------------------
// ================================================================================================
// ------------------------------------------------------------------------------------------------



// ------------------------------------------------------------------------------------------------
// ===================================== S D - C A R D ============================================
// ------------------------------------------------------------------------------------------------
/**
 * @details 
 *  This is the name of the logical drive path in the fatfs.c file
 *  It is called differently on the different microcontroller boards. �\(�_o)/�
 *  The name is used to mount the SD card and access files on it. 
 * @see File.cpp
 */
#if defined(VMB_MICROCONTROLLER_BOARD__STM32F469I_DISCOVERY)
	#define VMB_VAR_NAME_SDPATH SDPath
#elif defined(VMB_MICROCONTROLLER_BOARD__STM32NUCLEO_H755ZI_Q)
	#define VMB_VAR_NAME_SDPATH USERPath
#endif
// ------------------------------------------------------------------------------------------------
// ================================================================================================
// ------------------------------------------------------------------------------------------------



// ------------------------------------------------------------------------------------------------
// ======================================= A U D I O ==============================================
// ------------------------------------------------------------------------------------------------
#define VMB_AUDIO_FORMAT_WAV 1

// MP3 encoder is not available on the Cortex-M7 core because spirit 
// did not provide a library for it. ¯\_(ツ)_/¯
#if !defined(CORE_CM7) 
#define VMB_AUDIO_FORMAT_MP3 2
#endif

#define VMB_USED_AUDIO_FORMAT VMB_AUDIO_FORMAT_WAV

// ------------------------------------------------------------------------------------------------
// ================================================================================================
// ------------------------------------------------------------------------------------------------

#endif
