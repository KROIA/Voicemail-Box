/**
  ******************************************************************************
  * @file    stm32469i_discovery_audio.h
  * @author  MCD Application Team
  * @version V2.0.0
  * @date    27-January-2017
  * @brief   This file contains the common defines and functions prototypes for
  *          the stm32469i_discovery_audio.c driver.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32469I_DISCOVERY_AUDIO_H
#define __STM32469I_DISCOVERY_AUDIO_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#if defined(BSP_AUDIO_USE_RTOS)
#include "k_mem.h"
#else
#include <stdlib.h>
#endif

/* Include audio component Driver */
#include "../Components/cs43l22/cs43l22.h"
#include "stm32469i_discovery.h"
#include "../../../Middlewares/ST/STM32_Audio/Addons/PDM/Inc/pdm2pcm_glo.h"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup STM32469I_Discovery
  * @{
  */

/** @addtogroup STM32469I-Discovery_AUDIO
  * @{
  */

/** @defgroup STM32469I-Discovery_AUDIO_Exported_Types STM32469I Discovery AUDIO Exported Types
  * @{
  */
/**
  * @}
  */

/** @defgroup STM32469I-Discovery_AUDIO_Exported_Constants  STM32469I Discovery AUDIO Exported Constants
  * @{
  */

/** @defgroup BSP_Audio_Out_Option BSP AUDIO OUT Option
  * @{
  */
#define BSP_AUDIO_OUT_CIRCULARMODE      ((uint32_t)0x00000001) /* BUFFER CIRCULAR MODE */
#define BSP_AUDIO_OUT_NORMALMODE        ((uint32_t)0x00000002) /* BUFFER NORMAL MODE   */
#define BSP_AUDIO_OUT_STEREOMODE        ((uint32_t)0x00000004) /* STEREO MODE          */
#define BSP_AUDIO_OUT_MONOMODE          ((uint32_t)0x00000008) /* MONO MODE            */
/**
  * @}
  */

/*------------------------------------------------------------------------------
                          USER SAI defines parameters
 -----------------------------------------------------------------------------*/
/** @defgroup CODEC_AudioFrame_SLOT_TDMMode  STM32469I Discovery Audio Slot TDM mode
  * @brief In W8994 codec the Audio frame contains 4 slots : TDM Mode
  * TDM format :
  * +------------------|------------------|--------------------|-------------------+
  * | CODEC_SLOT0 Left | CODEC_SLOT1 Left | CODEC_SLOT0 Right  | CODEC_SLOT1 Right |
  * +------------------------------------------------------------------------------+
  * @{
  */
/* To have 2 separate audio stream in Both headphone and speaker the 4 slot must be activated */
#define CODEC_AUDIOFRAME_SLOT_0123                   SAI_SLOTACTIVE_0 | SAI_SLOTACTIVE_1 | SAI_SLOTACTIVE_2 | SAI_SLOTACTIVE_3
/* To have an audio stream in headphone only SAI Slot 0 and Slot 2 must be activated */
#define CODEC_AUDIOFRAME_SLOT_02                     SAI_SLOTACTIVE_0 | SAI_SLOTACTIVE_2
/* To have an audio stream in speaker only SAI Slot 1 and Slot 3 must be activated */
#define CODEC_AUDIOFRAME_SLOT_13                     SAI_SLOTACTIVE_1 | SAI_SLOTACTIVE_3
/**
  * @}
  */

/* SAI peripheral configuration defines */
#define AUDIO_SAIx                           SAI1_Block_A
#define AUDIO_SAIx_CLK_ENABLE()              __HAL_RCC_SAI1_CLK_ENABLE()
#define AUDIO_SAIx_CLK_DISABLE()             __HAL_RCC_SAI1_CLK_DISABLE()
#define AUDIO_SAIx_MCLK_SCK_SD_FS_AF         GPIO_AF6_SAI1

#define AUDIO_SAIx_MCLK_ENABLE()             __HAL_RCC_GPIOG_CLK_ENABLE()
#define AUDIO_SAIx_MCLK_DISABLE()            __HAL_RCC_GPIOG_CLK_DISABLE()

#define AUDIO_SAIx_MCK_PIN                   GPIO_PIN_7
#define AUDIO_SAIx_MCLK_GPIO_PORT            GPIOG

#define AUDIO_SAIx_SCK_SD_FS_ENABLE()        __HAL_RCC_GPIOE_CLK_ENABLE()
#define AUDIO_SAIx_SCK_SD_FS_DISABLE()       __HAL_RCC_GPIOE_CLK_DISABLE()
#define AUDIO_SAIx_FS_PIN                    GPIO_PIN_4
#define AUDIO_SAIx_SCK_PIN                   GPIO_PIN_5
#define AUDIO_SAIx_SD_PIN                    GPIO_PIN_6
#define AUDIO_SAIx_SCK_SD_FS_GPIO_PORT       GPIOE

#define AUDIO_RESET_ENABLE()                 __HAL_RCC_GPIOE_CLK_ENABLE()
#define AUDIO_RESET_DISABLE()                __HAL_RCC_GPIOE_CLK_DISABLE()
#define AUDIO_RESET_PIN                      GPIO_PIN_2
#define AUDIO_RESET_GPIO_PORT                GPIOE

/* SAI DMA Stream definitions */
#define AUDIO_SAIx_DMAx_CLK_ENABLE()         __HAL_RCC_DMA2_CLK_ENABLE()
#define AUDIO_SAIx_DMAx_CLK_DISABLE()        __HAL_RCC_DMA2_CLK_DISABLE()
#define AUDIO_SAIx_DMAx_STREAM               DMA2_Stream3
#define AUDIO_SAIx_DMAx_CHANNEL              DMA_CHANNEL_0
#define AUDIO_SAIx_DMAx_IRQ                  DMA2_Stream3_IRQn
#define AUDIO_SAIx_DMAx_PERIPH_DATA_SIZE     DMA_PDATAALIGN_HALFWORD
#define AUDIO_SAIx_DMAx_MEM_DATA_SIZE        DMA_MDATAALIGN_HALFWORD
#define DMA_MAX_SZE                          0xFFFF

#define AUDIO_SAIx_DMAx_IRQHandler           DMA2_Stream3_IRQHandler

/* Select the interrupt preemption priority for the DMA interrupt */
#define AUDIO_OUT_IRQ_PREPRIO           5   /* Select the preemption priority level(0 is the highest) */

/* Disable SAIx PLL */
#define AUDIO_SAIx_PLL_DISABLE()             HAL_RCCEx_DisablePLLSAI1()
/*------------------------------------------------------------------------------
                        AUDIO IN CONFIGURATION
------------------------------------------------------------------------------*/
/* SPI Configuration defines */
#define AUDIO_I2Sx                           SPI3
#define AUDIO_I2Sx_CLK_ENABLE()              __HAL_RCC_SPI3_CLK_ENABLE()
#define AUDIO_I2Sx_CLK_DISABLE()             __HAL_RCC_SPI3_CLK_DISABLE()
#define AUDIO_I2Sx_SCK_PIN                   GPIO_PIN_3
#define AUDIO_I2Sx_SCK_GPIO_PORT             GPIOB
#define AUDIO_I2Sx_SCK_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOB_CLK_ENABLE()
#define AUDIO_I2Sx_SCK_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOB_CLK_DISABLE()
#define AUDIO_I2Sx_SCK_AF                    GPIO_AF6_SPI3

#define AUDIO_I2Sx_SD_PIN                    GPIO_PIN_6
#define AUDIO_I2Sx_SD_GPIO_PORT              GPIOD
#define AUDIO_I2Sx_SD_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOD_CLK_ENABLE()
#define AUDIO_I2Sx_SD_GPIO_CLK_DISABLE()     __HAL_RCC_GPIOD_CLK_DISABLE()
#define AUDIO_I2Sx_SD_AF                     GPIO_AF5_I2S3ext

/* I2S DMA Stream Rx definitions */
#define AUDIO_I2Sx_DMAx_CLK_ENABLE()        __HAL_RCC_DMA1_CLK_ENABLE()
#define AUDIO_I2Sx_DMAx_CLK_DISABLE()       __HAL_RCC_DMA1_CLK_DISABLE()
#define AUDIO_I2Sx_DMAx_STREAM              DMA1_Stream2
#define AUDIO_I2Sx_DMAx_CHANNEL             DMA_CHANNEL_0
#define AUDIO_I2Sx_DMAx_IRQ                 DMA1_Stream2_IRQn
#define AUDIO_I2Sx_DMAx_PERIPH_DATA_SIZE    DMA_PDATAALIGN_HALFWORD
#define AUDIO_I2Sx_DMAx_MEM_DATA_SIZE       DMA_MDATAALIGN_HALFWORD

#define AUDIO_I2Sx_DMAx_IRQHandler          DMA1_Stream2_IRQHandler

/* Select the interrupt preemption priority and subpriority for the IT/DMA interrupt */
#define AUDIO_IN_IRQ_PREPRIO                ((uint32_t)6)   /* Select the preemption priority level(0 is the highest) */


/* Two channels are used:
   - one channel as input which is connected to I2S SCK in stereo mode
   - one channel as output which divides the frequency on the input
*/

#define AUDIO_TIMx_CLK_ENABLE()             __HAL_RCC_TIM4_CLK_ENABLE()
#define AUDIO_TIMx_CLK_DISABLE()            __HAL_RCC_TIM4_CLK_DISABLE()
#define AUDIO_TIMx                          TIM4
#define AUDIO_TIMx_IN_CHANNEL               TIM_CHANNEL_1
#define AUDIO_TIMx_OUT_CHANNEL              TIM_CHANNEL_2 /* Select channel 2 as output */
#define AUDIO_TIMx_GPIO_CLK_ENABLE()        __HAL_RCC_GPIOD_CLK_ENABLE()
#define AUDIO_TIMx_GPIO_CLK_DISABLE()       __HAL_RCC_GPIOD_CLK_DISABLE()
#define AUDIO_TIMx_GPIO_PORT                GPIOD
#define AUDIO_TIMx_IN_GPIO_PIN              GPIO_PIN_12
#define AUDIO_TIMx_OUT_GPIO_PIN             GPIO_PIN_13
#define AUDIO_TIMx_AF                       GPIO_AF2_TIM4

/*------------------------------------------------------------------------------
             CONFIGURATION: Audio Driver Configuration parameters
------------------------------------------------------------------------------*/

#define AUDIODATA_SIZE                      2   /* 16-bits audio data size */

/* Audio status definition */
#define AUDIO_OK                            ((uint8_t)0)
#define AUDIO_ERROR                         ((uint8_t)1)
#define AUDIO_TIMEOUT                       ((uint8_t)2)

/* AudioFreq * DataSize (2 bytes) * NumChannels (Stereo: 2) */
#define DEFAULT_AUDIO_IN_FREQ               I2S_AUDIOFREQ_16K
#define DEFAULT_AUDIO_IN_BIT_RESOLUTION     ((uint8_t)16)
#define DEFAULT_AUDIO_IN_CHANNEL_NBR        ((uint8_t)2) /* Mono = 1, Stereo = 2 */
#define DEFAULT_AUDIO_IN_VOLUME             ((uint16_t)64)

/* PDM buffer input size */
#define INTERNAL_BUFF_SIZE                  (128*DEFAULT_AUDIO_IN_FREQ/16000*DEFAULT_AUDIO_IN_CHANNEL_NBR)
/* PCM buffer output size */
#define PCM_OUT_SIZE                        (DEFAULT_AUDIO_IN_FREQ/1000*DEFAULT_AUDIO_IN_CHANNEL_NBR)
#define CHANNEL_DEMUX_MASK                  ((uint8_t)0x55)

/*------------------------------------------------------------------------------
                    OPTIONAL Configuration defines parameters
------------------------------------------------------------------------------*/

/* Delay for the Codec to be correctly reset */
#define CODEC_RESET_DELAY           ((uint8_t)5)

/*------------------------------------------------------------------------------
                            OUTPUT DEVICES definition
------------------------------------------------------------------------------*/

/**
  * @}
  */

/** @defgroup STM32469I-Discovery_AUDIO_Exported_Variables  STM32469I-Discovery AUDIO Exported Variables
  * @{
  */
extern __IO uint16_t AudioInVolume;
 /**
  * @}
  */

/** @defgroup STM32469I-Discovery_AUDIO_Exported_Macros STM32469I-Discovery AUDIO Exported Macros
  * @{
  */
#define DMA_MAX(x)           (((x) <= DMA_MAX_SZE)? (x):DMA_MAX_SZE)
/**
  * @}
  */

/** @defgroup STM32469I-Discovery_AUDIO_OUT_Exported_Functions  STM32469I Discovery AUDIO OUT Exported Functions
  * @{
  */
uint8_t BSP_AUDIO_OUT_Init(uint16_t OutputDevice, uint8_t Volume, uint32_t AudioFreq);
uint8_t BSP_AUDIO_OUT_Play(uint16_t* pBuffer, uint32_t Size);
void    BSP_AUDIO_OUT_ChangeBuffer(uint16_t *pData, uint16_t Size);
uint8_t BSP_AUDIO_OUT_Pause(void);
uint8_t BSP_AUDIO_OUT_Resume(void);
uint8_t BSP_AUDIO_OUT_Stop(uint32_t Option);
uint8_t BSP_AUDIO_OUT_SetVolume(uint8_t Volume);
void    BSP_AUDIO_OUT_SetFrequency(uint32_t AudioFreq);
void    BSP_AUDIO_OUT_SetAudioFrameSlot(uint32_t AudioFrameSlot);
uint8_t BSP_AUDIO_OUT_SetMute(uint32_t Cmd);
uint8_t BSP_AUDIO_OUT_SetOutputMode(uint8_t Output);
void    BSP_AUDIO_OUT_DeInit(void);

/* User Callbacks: user has to implement these functions in his code if they are needed. */
/* This function is called when the requested data has been completely transferred.*/
void    BSP_AUDIO_OUT_TransferComplete_CallBack(void);

/* This function is called when half of the requested buffer has been transferred. */
void    BSP_AUDIO_OUT_HalfTransfer_CallBack(void);

/* This function is called when an Interrupt due to transfer error on or peripheral
   error occurs. */
void    BSP_AUDIO_OUT_Error_CallBack(void);

/* These function can be modified in case the current settings (e.g. DMA stream)
   need to be changed for specific application needs */
void  BSP_AUDIO_OUT_ClockConfig(SAI_HandleTypeDef *hsai, uint32_t AudioFreq, void *Params);
void  BSP_AUDIO_OUT_MspInit(SAI_HandleTypeDef *hsai, void *Params);
void  BSP_AUDIO_OUT_MspDeInit(SAI_HandleTypeDef *hsai, void *Params);

/**
  * @}
  */

/** @defgroup STM32469I-Discovery_AUDIO_IN_Exported_Functions  STM32469I Discovery AUDIO IN Exported Functions
  * @{
  */
uint8_t BSP_AUDIO_IN_Init(uint32_t AudioFreq, uint32_t BitRes, uint32_t ChnlNbr);
uint8_t BSP_AUDIO_IN_Record(uint16_t *pData, uint32_t Size);
uint8_t BSP_AUDIO_IN_Stop(void);
uint8_t BSP_AUDIO_IN_Pause(void);
uint8_t BSP_AUDIO_IN_Resume(void);
uint8_t BSP_AUDIO_IN_SetVolume(uint8_t Volume);
void    BSP_AUDIO_IN_DeInit(void);
uint8_t BSP_AUDIO_IN_PDMToPCM(uint16_t* PDMBuf, uint16_t* PCMBuf);
/* User Callbacks: user has to implement these functions in his code if they are needed. */
/* This function should be implemented by the user application.
   It is called into this driver when the current buffer is filled to prepare the next
   buffer pointer and its size. */
void    BSP_AUDIO_IN_TransferComplete_CallBack(void);
void    BSP_AUDIO_IN_HalfTransfer_CallBack(void);

/* This function is called when an Interrupt due to transfer error on or peripheral
   error occurs. */
void    BSP_AUDIO_IN_Error_Callback(void);

/* These function can be modified in case the current settings (e.g. DMA stream)
   need to be changed for specific application needs */
void  BSP_AUDIO_IN_ClockConfig(I2S_HandleTypeDef *hi2s, void *Params);   
void  BSP_AUDIO_IN_MspInit(I2S_HandleTypeDef *hi2s, void *Params);
void  BSP_AUDIO_IN_MspDeInit(I2S_HandleTypeDef *hi2s, void *Params);

/**
  * @}
  */ 

/**
  * @}
  */ 

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __STM32469I_DISCOVERY_AUDIO_H */
