/**
  ******************************************************************************
  * @file    st25r3916_irq.h
  * @author  MMY Application Team
  * @brief   ST25R3916 Interrupt handling
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

#ifndef ST25R3916_IRQ_H
#define ST25R3916_IRQ_H

/*
******************************************************************************
* INCLUDES
******************************************************************************
*/

#include "rfal_platform.h"

/*
******************************************************************************
* GLOBAL DEFINES
******************************************************************************
*/

#define ST25R3916_IRQ_MASK_ALL             (uint32_t)(0xFFFFFFFFUL)  /*!< All ST25R3916 interrupt sources                             */
#define ST25R3916_IRQ_MASK_NONE            (uint32_t)(0x00000000UL)  /*!< No ST25R3916 interrupt source                               */

/* Main interrupt register */
#define ST25R3916_IRQ_MASK_OSC             (uint32_t)(0x00000080U)   /*!< ST25R3916 oscillator stable interrupt                       */
#define ST25R3916_IRQ_MASK_FWL             (uint32_t)(0x00000040U)   /*!< ST25R3916 FIFO water level interrupt                        */
#define ST25R3916_IRQ_MASK_RXS             (uint32_t)(0x00000020U)   /*!< ST25R3916 start of receive interrupt                        */
#define ST25R3916_IRQ_MASK_RXE             (uint32_t)(0x00000010U)   /*!< ST25R3916 end of receive interrupt                          */
#define ST25R3916_IRQ_MASK_TXE             (uint32_t)(0x00000008U)   /*!< ST25R3916 end of transmission interrupt                     */
#define ST25R3916_IRQ_MASK_COL             (uint32_t)(0x00000004U)   /*!< ST25R3916 bit collision interrupt                           */
#define ST25R3916_IRQ_MASK_RX_REST         (uint32_t)(0x00000002U)   /*!< ST25R3916 automatic reception restart interrupt             */
#define ST25R3916_IRQ_MASK_RFU             (uint32_t)(0x00000001U)   /*!< ST25R3916 RFU interrupt                                     */

/* Timer and NFC interrupt register */
#define ST25R3916_IRQ_MASK_DCT             (uint32_t)(0x00008000U)   /*!< ST25R3916 termination of direct command interrupt.          */
#define ST25R3916_IRQ_MASK_NRE             (uint32_t)(0x00004000U)   /*!< ST25R3916 no-response timer expired interrupt               */
#define ST25R3916_IRQ_MASK_GPE             (uint32_t)(0x00002000U)   /*!< ST25R3916 general purpose timer expired interrupt           */
#define ST25R3916_IRQ_MASK_EON             (uint32_t)(0x00001000U)   /*!< ST25R3916 external field on interrupt                       */
#define ST25R3916_IRQ_MASK_EOF             (uint32_t)(0x00000800U)   /*!< ST25R3916 external field off interrupt                      */
#define ST25R3916_IRQ_MASK_CAC             (uint32_t)(0x00000400U)   /*!< ST25R3916 collision during RF collision avoidance interrupt */
#define ST25R3916_IRQ_MASK_CAT             (uint32_t)(0x00000200U)   /*!< ST25R3916 minimum guard time expired interrupt              */
#define ST25R3916_IRQ_MASK_NFCT            (uint32_t)(0x00000100U)   /*!< ST25R3916 initiator bit rate recognised interrupt           */

/* Error and wake-up interrupt register */
#define ST25R3916_IRQ_MASK_CRC             (uint32_t)(0x00800000U)   /*!< ST25R3916 CRC error interrupt                               */
#define ST25R3916_IRQ_MASK_PAR             (uint32_t)(0x00400000U)   /*!< ST25R3916 parity error interrupt                            */
#define ST25R3916_IRQ_MASK_ERR2            (uint32_t)(0x00200000U)   /*!< ST25R3916 soft framing error interrupt                      */
#define ST25R3916_IRQ_MASK_ERR1            (uint32_t)(0x00100000U)   /*!< ST25R3916 hard framing error interrupt                      */
#define ST25R3916_IRQ_MASK_WT              (uint32_t)(0x00080000U)   /*!< ST25R3916 wake-up interrupt                                 */
#define ST25R3916_IRQ_MASK_WAM             (uint32_t)(0x00040000U)   /*!< ST25R3916 wake-up due to amplitude interrupt                */
#define ST25R3916_IRQ_MASK_WPH             (uint32_t)(0x00020000U)   /*!< ST25R3916 wake-up due to phase interrupt                    */
#if defined(ST25R3916)
#define ST25R3916_IRQ_MASK_WCAP            (uint32_t)(0x00010000U)   /*!< ST25R3916 wake-up due to capacitance measurement            */
#elif defined(ST25R3916B)
#define ST25R3916_IRQ_MASK_WCAP            ST25R3916_IRQ_MASK_NONE   /*!< ST25R3916B disable capacitive WU                            */
#endif /* ST25R3916 */

/* Passive Target Interrupt Register */
#define ST25R3916_IRQ_MASK_PPON2           (uint32_t)(0x80000000U)   /*!< ST25R3916 PPON2 Field on waiting Timer interrupt            */
#define ST25R3916_IRQ_MASK_SL_WL           (uint32_t)(0x40000000U)   /*!< ST25R3916 Passive target slot number water level interrupt  */
#define ST25R3916_IRQ_MASK_APON            (uint32_t)(0x20000000U)   /*!< ST25R3916 Anticollision done and Field On interrupt         */
#define ST25R3916_IRQ_MASK_RXE_PTA         (uint32_t)(0x10000000U)   /*!< ST25R3916 RXE with an automatic response interrupt          */
#define ST25R3916_IRQ_MASK_WU_F            (uint32_t)(0x08000000U)   /*!< ST25R3916 212/424b/s Passive target interrupt: Active       */
#define ST25R3916_IRQ_MASK_RFU2            (uint32_t)(0x04000000U)   /*!< ST25R3916 RFU2 interrupt                                    */
#define ST25R3916_IRQ_MASK_WU_A_X          (uint32_t)(0x02000000U)   /*!< ST25R3916 106kb/s Passive target state interrupt: Active*   */
#define ST25R3916_IRQ_MASK_WU_A            (uint32_t)(0x01000000U)   /*!< ST25R3916 106kb/s Passive target state interrupt: Active    */

/*
******************************************************************************
* GLOBAL FUNCTION PROTOTYPES
******************************************************************************
*/


/*! 
 *****************************************************************************
 *  \brief  Wait until an ST25R3916 interrupt occurs
 *
 *  This function is used to access the ST25R3916 interrupt flags. Use this
 *  to wait for max. \a tmo milliseconds for the \b first interrupt indicated
 *  with mask \a mask to occur.
 *
 *  \param[in] mask : mask indicating the interrupts to wait for.
 *  \param[in] tmo : time in milliseconds until timeout occurs. If set to 0
 *                   the functions waits forever.
 *
 *  \return : 0 if timeout occured otherwise a mask indicating the cleared
 *              interrupts.
 *
 *****************************************************************************
 */
uint32_t st25r3916WaitForInterruptsTimed( uint32_t mask, uint16_t tmo );

/*! 
 *****************************************************************************
 *  \brief  Get status for the given interrupt
 *
 *  This function is used to check whether the interrupt given by \a mask
 *  has occured. If yes the interrupt gets cleared. This function returns
 *  only status bits which are inside \a mask.
 *
 *  \param[in] mask : mask indicating the interrupt to check for.
 *
 *  \return the mask of the interrupts occurred
 *
 *****************************************************************************
 */
uint32_t st25r3916GetInterrupt( uint32_t mask );

/*! 
 *****************************************************************************
 *  \brief  Init the 3916 interrupt
 *
 *  This function is used to check whether the interrupt given by \a mask
 *  has occured. 
 *
 *****************************************************************************
 */
void st25r3916InitInterrupts( void );

/*! 
 *****************************************************************************
 *  \brief  Modifies the Interrupt
 *
 *  This function modifies the interrupt
 *  
 *  \param[in] clr_mask : bit mask to be cleared on the interrupt mask 
 *  \param[in] set_mask : bit mask to be set on the interrupt mask 
 *****************************************************************************
 */
void st25r3916ModifyInterrupts( uint32_t clr_mask, uint32_t set_mask );

/*! 
 *****************************************************************************
 *  \brief Checks received interrupts
 *
 *  Checks received interrupts and saves the result into global params
 *****************************************************************************
 */
void st25r3916CheckForReceivedInterrupts( void );

/*! 
 *****************************************************************************
 *  \brief  ISR Service routine
 *
 *  This function modiefies the interupt
 *****************************************************************************
 */
void  st25r3916Isr( void );

/*! 
 *****************************************************************************
 *  \brief  Enable a given ST25R3916 Interrupt source
 *
 *  This function enables all interrupts given by \a mask, 
 *  ST25R3916_IRQ_MASK_ALL enables all interrupts.
 *
 *  \param[in] mask: mask indicating the interrupts to be enabled
 *
 *****************************************************************************
 */
void st25r3916EnableInterrupts( uint32_t mask );

/*! 
 *****************************************************************************
 *  \brief  Disable one or more a given ST25R3916 Interrupt sources
 *
 *  This function disables all interrupts given by \a mask. 0xff disables all.
 *
 *  \param[in] mask: mask indicating the interrupts to be disabled.
 *
 *****************************************************************************
 */
void st25r3916DisableInterrupts( uint32_t mask );

/*! 
 *****************************************************************************
 *  \brief  Clear all ST25R3916 irq flags
 *
 *****************************************************************************
 */
void st25r3916ClearInterrupts( void );

/*! 
 *****************************************************************************
 *  \brief  Clears and then enables the given ST25R3916 Interrupt sources
 *
 *  \param[in] mask: mask indicating the interrupts to be cleared and enabled
 *****************************************************************************
 */
void st25r3916ClearAndEnableInterrupts( uint32_t mask );

/*! 
 *****************************************************************************
 *  \brief  Sets IRQ callback for the ST25R3916 interrupt
 *
 *  \param[in] cb: pointer to the callback method
 *
 *****************************************************************************
 */
void st25r3916IRQCallbackSet( void (*cb)( void ) );

/*! 
 *****************************************************************************
 *  \brief  Sets IRQ callback for the ST25R3916 interrupt
 *
 *****************************************************************************
 */
void st25r3916IRQCallbackRestore( void );

#endif /* ST25R3916_IRQ_H */

/**
  * @}
  *
  * @}
  *
  * @}
  * 
  * @}
  */
