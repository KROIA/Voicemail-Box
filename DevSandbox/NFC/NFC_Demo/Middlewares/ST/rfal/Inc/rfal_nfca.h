
/**
  ******************************************************************************
  * @file    rfal_nfca.h
  * @author  MMY Application Team
  * @brief   Provides several NFC-A convenience methods and definitions
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


#ifndef RFAL_NFCA_H
#define RFAL_NFCA_H

/*
 ******************************************************************************
 * INCLUDES
 ******************************************************************************
 */
#include "rfal_platform.h"
#include "rfal_utils.h"
#include "rfal_rf.h"
#include "rfal_t1t.h"

/*
 ******************************************************************************
 * GLOBAL DEFINES
 ******************************************************************************
 */

#define RFAL_NFCA_CASCADE_1_UID_LEN                           4U    /*!< UID length of cascade level 1 only tag                            */
#define RFAL_NFCA_CASCADE_2_UID_LEN                           7U    /*!< UID length of cascade level 2 only tag                            */
#define RFAL_NFCA_CASCADE_3_UID_LEN                           10U   /*!< UID length of cascade level 3 only tag                            */

#define RFAL_NFCA_SENS_RES_PLATFORM_MASK                      0x0FU /*!< SENS_RES (ATQA) platform configuration mask  Digital 1.1 Table 10 */
#define RFAL_NFCA_SENS_RES_PLATFORM_T1T                       0x0CU /*!< SENS_RES (ATQA) T1T platform configuration  Digital 1.1 Table 10  */

#define RFAL_NFCA_SEL_RES_CONF_MASK                           0x60U /*!< SEL_RES (SAK) platform configuration mask  Digital 1.1 Table 19   */
#define RFAL_NFCA_SEL_RES_CONF_T2T                            0x00U /*!< SEL_RES (SAK) T2T configuration  Digital 1.1 Table 19             */
#define RFAL_NFCA_SEL_RES_CONF_T4T                            0x20U /*!< SEL_RES (SAK) T4T configuration  Digital 1.1 Table 19             */
#define RFAL_NFCA_SEL_RES_CONF_NFCDEP                         0x40U /*!< SEL_RES (SAK) NFC-DEP configuration  Digital 1.1 Table 19         */
#define RFAL_NFCA_SEL_RES_CONF_T4T_NFCDEP                     0x60U /*!< SEL_RES (SAK) T4T and NFC-DEP configuration  Digital 1.1 Table 19 */


/*! NFC-A minimum FDT(listen) = ((n * 128 + (84)) / fc) with n_min = 9      Digital 1.1  6.10.1
 *                            = (1236)/fc
 * Relax with 3etu: (3*128)/fc as with multiple NFC-A cards, response may take longer (JCOP cards)
 *                            = (1236 + 384)/fc = 1620 / fc                                      */
#define RFAL_NFCA_FDTMIN          1620U
/*
 ******************************************************************************
 * GLOBAL MACROS
 ******************************************************************************
 */

/*! Checks if device is a T1T given its SENS_RES */
#define rfalNfcaIsSensResT1T( sensRes )          ((((rfalNfcaSensRes*)(sensRes))->platformInfo & RFAL_NFCA_SENS_RES_PLATFORM_MASK) == RFAL_NFCA_SENS_RES_PLATFORM_T1T )

/*! Checks if device is a T2T given its SENS_RES */
#define rfalNfcaIsSelResT2T( selRes )            ((((rfalNfcaSelRes*)(selRes))->sak & RFAL_NFCA_SEL_RES_CONF_MASK) == RFAL_NFCA_SEL_RES_CONF_T2T )

/*! Checks if device is a T4T given its SENS_RES */
#define rfalNfcaIsSelResT4T( selRes )            ((((rfalNfcaSelRes*)(selRes))->sak & RFAL_NFCA_SEL_RES_CONF_MASK) == RFAL_NFCA_SEL_RES_CONF_T4T )

/*! Checks if device supports NFC-DEP protocol given its SENS_RES */
#define rfalNfcaIsSelResNFCDEP( selRes )         ((((rfalNfcaSelRes*)(selRes))->sak & RFAL_NFCA_SEL_RES_CONF_MASK) == RFAL_NFCA_SEL_RES_CONF_NFCDEP )

/*! Checks if device supports ISO-DEP and NFC-DEP protocol given its SENS_RES */
#define rfalNfcaIsSelResT4TNFCDEP( selRes )      ((((rfalNfcaSelRes*)(selRes))->sak & RFAL_NFCA_SEL_RES_CONF_MASK) == RFAL_NFCA_SEL_RES_CONF_T4T_NFCDEP )

/*! Checks if a NFC-A listener device supports multiple protocols (ISO-DEP and NFC-DEP) */
#define rfalNfcaLisDevIsMultiProto( lisDev )     (((rfalNfcaListenDevice*)(lisDev))->type == RFAL_NFCA_T4T_NFCDEP )

/*
******************************************************************************
* GLOBAL TYPES
******************************************************************************
*/

/*! NFC-A Listen device types */
typedef enum {
    RFAL_NFCA_T1T        = 0x01,                                  /* Device configured for T1T  Digital 1.1 Table 9                               */
    RFAL_NFCA_T2T        = 0x00,                                  /* Device configured for T2T  Digital 1.1 Table 19                              */
    RFAL_NFCA_T4T        = 0x20,                                  /* Device configured for T4T  Digital 1.1 Table 19                              */
    RFAL_NFCA_NFCDEP     = 0x40,                                  /* Device configured for NFC-DEP  Digital 1.1 Table 19                          */
    RFAL_NFCA_T4T_NFCDEP = 0x60                                   /* Device configured for NFC-DEP and T4T  Digital 1.1 Table 19                  */
} rfalNfcaListenDeviceType;


/*! SENS_RES (ATQA) format  Digital 1.1  6.6.3 & Table 7 */
typedef struct
{ 
    uint8_t      anticollisionInfo;                               /*!< SENS_RES Anticollision Information                                         */
    uint8_t      platformInfo;                                    /*!< SENS_RES Platform Information                                              */
} rfalNfcaSensRes;


/*! SDD_REQ (Anticollision) format   Digital 1.1  6.7.1 & Table 11 */
typedef struct
{
    uint8_t      selCmd;                                          /*!< SDD_REQ SEL_CMD: cascade Level                                             */
    uint8_t      selPar;                                          /*!< SDD_REQ SEL_PAR: Byte Count[4b] | Bit Count[4b] (NVB: Number of Valid Bits)*/
} rfalNfcaSddReq;


/*! SDD_RES (UID CLn) format   Digital 1.1  6.7.2 & Table 15 */
typedef struct
{
    uint8_t      nfcid1[RFAL_NFCA_CASCADE_1_UID_LEN];             /*!< NFCID1 cascade level NFCID                                                 */
    uint8_t      bcc;                                             /*!< BCC Exclusive-OR over first 4 bytes of SDD_RES                             */
} rfalNfcaSddRes;


/*! SEL_REQ (Select) format   Digital 1.1  6.8.1 & Table 17 */
typedef struct
{
    uint8_t      selCmd;                                          /*!< SDD_REQ SEL_CMD: cascade Level                                             */
    uint8_t      selPar;                                          /*!< SDD_REQ SEL_PAR: Byte Count[4b] | Bit Count[4b] (NVB: Number of Valid Bits)*/
    uint8_t      nfcid1[RFAL_NFCA_CASCADE_1_UID_LEN];             /*!< NFCID1 data                                                                */
    uint8_t      bcc;                                             /*!< Checksum calculated as exclusive-OR over the 4 bytes of NFCID1 CLn         */
} rfalNfcaSelReq;


/*! SEL_RES (SAK) format   Digital 1.1  6.8.2 & Table 19 */
typedef struct
{
    uint8_t      sak;                                             /*!< Select Acknowledge                                                         */
} rfalNfcaSelRes;


/*! NFC-A listener device (PICC) struct  */
typedef struct
{
    rfalNfcaListenDeviceType type;                                /*!< NFC-A Listen device type                                                   */
    rfalNfcaSensRes          sensRes;                             /*!< SENS_RES (ATQA)                                                            */
    rfalNfcaSelRes           selRes;                              /*!< SEL_RES  (SAK)                                                             */
    uint8_t                  nfcId1Len;                           /*!< NFCID1 Length                                                              */
    uint8_t                  nfcId1[RFAL_NFCA_CASCADE_3_UID_LEN]; /*!< NFCID1   (UID)                                                             */
#ifdef RFAL_FEATURE_T1T
    rfalT1TRidRes            ridRes;                              /*!< RID_RES                                                                    */
#endif /* RFAL_FEATURE_T1T */
    bool                     isSleep;                             /*!< Device sleeping flag                                                       */
} rfalNfcaListenDevice;

/*
******************************************************************************
* GLOBAL FUNCTION PROTOTYPES
******************************************************************************
*/

/*! 
 *****************************************************************************
 * \brief  Initialize NFC-A Poller mode
 *  
 * This methods configures RFAL RF layer to perform as a 
 * NFC-A Poller/RW (ISO14443A PCD) including all default timings and bit rate
 * to 106 kbps
 
 *
 * \return RFAL_ERR_WRONG_STATE  : RFAL not initialized or mode not set
 * \return RFAL_ERR_NONE         : No error
 *****************************************************************************
 */
ReturnCode rfalNfcaPollerInitialize( void );


/*! 
 *****************************************************************************
 * \brief  NFC-A Poller Check Presence
 *  
 * This method checks if a NFC-A Listen device (PICC) is present on the field
 * by sending an ALL_REQ (WUPA) or SENS_REQ (REQA)
 *  
 * \param[in]  cmd     : Indicate if to send an ALL_REQ or a SENS_REQ
 * \param[out] sensRes : If received, the SENS_RES
 *
 * \return RFAL_ERR_WRONG_STATE  : RFAL not initialized or incorrect mode
 * \return RFAL_ERR_PARAM        : Invalid parameters
 * \return RFAL_ERR_IO           : Generic internal error 
 * \return RFAL_ERR_RF_COLLISION : Collision detected one or more device in the field
 * \return RFAL_ERR_PAR          : Parity error detected, one or more device in the field
 * \return RFAL_ERR_CRC          : CRC error detected, one or more device in the field
 * \return RFAL_ERR_FRAMING      : Framing error detected, one or more device in the field
 * \return RFAL_ERR_PROTO        : Protocol error detected, one or more device in the field
 * \return RFAL_ERR_TIMEOUT      : Timeout error, no listener device detected
 * \return RFAL_ERR_NONE         : No error, one or more device in the field
 *****************************************************************************
 */
ReturnCode rfalNfcaPollerCheckPresence( rfal14443AShortFrameCmd cmd, rfalNfcaSensRes *sensRes );


/*! 
 *****************************************************************************
 * \brief  NFC-A Poller Select
 *  
 * This method selects a NFC-A Listener device (PICC) 
 *  
 * \param[in]  nfcid1   : Listener device NFCID1 to be selected
 * \param[in]  nfcidLen : Length of the NFCID1 to be selected  
 * \param[out] selRes   : pointer to place the SEL_RES
 *
 * \return RFAL_ERR_WRONG_STATE  : RFAL not initialized or incorrect mode
 * \return RFAL_ERR_PARAM        : Invalid parameters
 * \return RFAL_ERR_IO           : Generic internal error
 * \return RFAL_ERR_TIMEOUT      : Timeout error
 * \return RFAL_ERR_PAR          : Parity error detected
 * \return RFAL_ERR_CRC          : CRC error detected
 * \return RFAL_ERR_FRAMING      : Framing error detected
 * \return RFAL_ERR_PROTO        : Protocol error detected
 * \return RFAL_ERR_NONE         : No error, SEL_RES received
 *****************************************************************************
 */
ReturnCode rfalNfcaPollerSelect( const uint8_t *nfcid1, uint8_t nfcidLen, rfalNfcaSelRes *selRes );


/*! 
 *****************************************************************************
 * \brief  NFC-A Poller Start Select
 *  
 * This method starts the selection of a NFC-A Listener device (PICC) 
 *  
 * \param[in]  nfcid1   : Listener device NFCID1 to be selected
 * \param[in]  nfcidLen : Length of the NFCID1 to be selected  
 * \param[out] selRes   : pointer to place the SEL_RES
 *
 * \return RFAL_ERR_WRONG_STATE  : RFAL not initialized or incorrect mode
 * \return RFAL_ERR_PARAM        : Invalid parameters
 * \return RFAL_ERR_IO           : Generic internal error
 * \return RFAL_ERR_TIMEOUT      : Timeout error
 * \return RFAL_ERR_PAR          : Parity error detected
 * \return RFAL_ERR_CRC          : CRC error detected
 * \return RFAL_ERR_FRAMING      : Framing error detected
 * \return RFAL_ERR_PROTO        : Protocol error detected
 * \return RFAL_ERR_NONE         : No error, SEL_RES received
 *****************************************************************************
 */
ReturnCode rfalNfcaPollerStartSelect( const uint8_t *nfcid1, uint8_t nfcidLen, rfalNfcaSelRes *selRes );


/*! 
 *****************************************************************************
 * \brief  NFC-A Poller Get Select Status
 *  
 * This method gets the selection status
 *  
 *
 * \return RFAL_ERR_WRONG_STATE  : RFAL not initialized or incorrect mode
 * \return RFAL_ERR_PARAM        : Invalid parameters
 * \return RFAL_ERR_IO           : Generic internal error
 * \return RFAL_ERR_TIMEOUT      : Timeout error
 * \return RFAL_ERR_PAR          : Parity error detected
 * \return RFAL_ERR_CRC          : CRC error detected
 * \return RFAL_ERR_FRAMING      : Framing error detected
 * \return RFAL_ERR_PROTO        : Protocol error detected
 * \return RFAL_ERR_NONE         : No error, SEL_RES received
 *****************************************************************************
 */
ReturnCode rfalNfcaPollerGetSelectStatus( void );


/*! 
 *****************************************************************************
 * \brief  NFC-A Poller Sleep
 *  
 * This method sends a SLP_REQ (HLTA)
 * No response is expected afterwards   Digital 1.1  6.9.2.1 
 *  
 * \return RFAL_ERR_WRONG_STATE  : RFAL not initialized or incorrect mode
 * \return RFAL_ERR_PARAM        : Invalid parameters
 * \return RFAL_ERR_IO           : Generic internal error
 * \return RFAL_ERR_NONE         : No error
 *****************************************************************************
 */
ReturnCode rfalNfcaPollerSleep( void );


/*!
 *****************************************************************************
 * \brief  NFC-A Poller Start Sleep
 *  
 * This method sends a SLP_REQ (HLTA)
 * No response is expected afterwards   Digital 1.1  6.9.2.1 
 *  
 * \return RFAL_ERR_WRONG_STATE  : RFAL not initialized or incorrect mode
 * \return RFAL_ERR_PARAM        : Invalid parameters
 * \return RFAL_ERR_IO           : Generic internal error
 * \return RFAL_ERR_NONE         : No error
 *****************************************************************************
 */
ReturnCode rfalNfcaPollerStartSleep( void );


/*! 
 *****************************************************************************
 * \brief  NFC-A Poller Get Sleep Status
 *  
 *  Returns the Sleep status
 *  
 * \return RFAL_ERR_WRONG_STATE  : RFAL not initialized or incorrect mode
 * \return RFAL_ERR_PARAM        : Invalid parameters
 * \return RFAL_ERR_IO           : Generic internal error
 * \return RFAL_ERR_NONE         : No error
 *****************************************************************************
 */
ReturnCode rfalNfcaPollerGetSleepStatus( void );


/*!
 *****************************************************************************
 * \brief  NFC-A Technology Detection
 *  
 * This method performs NFC-A Technology Detection as defined in the spec
 * given in the compliance mode
 *  
 * \param[in]  compMode  : compliance mode to be performed
 * \param[out] sensRes   : location to store the SENS_RES, if received
 * 
 * When compMode is set to ISO compliance a SLP_REQ (HLTA) is not sent 
 * after detection. When set to EMV a ALL_REQ (WUPA) is sent instead of 
 * a SENS_REQ (REQA)
 *  
 * \return RFAL_ERR_WRONG_STATE  : RFAL not initialized or incorrect mode
 * \return RFAL_ERR_PARAM        : Invalid parameters
 * \return RFAL_ERR_IO           : Generic internal error
 * \return RFAL_ERR_NONE         : No error, one or more device in the field
 *****************************************************************************
 */
ReturnCode rfalNfcaPollerTechnologyDetection( rfalComplianceMode compMode, rfalNfcaSensRes *sensRes );


/*! 
 *****************************************************************************
 * \brief  NFC-A Start Technology Detection
 *  
 * This method starts NFC-A Technology Detection as defined in the spec
 * given in the compliance mode
 *  
 * \param[in]  compMode  : compliance mode to be performed
 * \param[out] sensRes   : location to store the SENS_RES, if received
 * 
 * When compMode is set to ISO compliance a SLP_REQ (HLTA) is not sent 
 * after detection. When set to EMV a ALL_REQ (WUPA) is sent instead of 
 * a SENS_REQ (REQA)
 *  
 * \return RFAL_ERR_WRONG_STATE  : RFAL not initialized or incorrect mode
 * \return RFAL_ERR_PARAM        : Invalid parameters
 * \return RFAL_ERR_IO           : Generic internal error
 * \return RFAL_ERR_NONE         : No error, one or more device in the field
 *****************************************************************************
 */
ReturnCode rfalNfcaPollerStartTechnologyDetection( rfalComplianceMode compMode, rfalNfcaSensRes *sensRes );


/*!
 *****************************************************************************
 *  \brief  NFC-A Get Technology Detection Status
 *
 *  Returns the Technology Detection status
 *
 * \return RFAL_ERR_WRONG_STATE  : RFAL not initialized or incorrect mode
 * \return RFAL_ERR_PARAM        : Invalid parameters
 * \return RFAL_ERR_IO           : Generic internal error
 * \return RFAL_ERR_NONE         : No error, one or more device in the field
 *****************************************************************************
 */
ReturnCode rfalNfcaPollerGetTechnologyDetectionStatus( void );


/*! 
 *****************************************************************************
 * \brief  NFC-A Poller Collision Resolution
 *  
 * Collision resolution for one NFC-A Listener device/card (PICC) as 
 * defined in Activity 2.1  9.3.4
 * 
 * This method executes anti collision loop and select the device with higher NFCID1
 * 
 * When devLimit = 0 it is configured to perform collision detection only. Once a collision 
 * is detected the collision resolution is aborted immidiatly. If only one device is found
 * with no collisions, it will properly resolved. 
 *
 * \param[in]  devLimit    : device limit value (CON_DEVICES_LIMIT)
 * \param[out] collPending : pointer to collision pending flag (INT_COLL_PEND)
 * \param[out] selRes      : location to store the last Select Response from listener device (PICC)
 * \param[out] nfcId1      : location to store the NFCID1 (UID), ensure RFAL_NFCA_CASCADE_3_UID_LEN
 * \param[out] nfcId1Len   : pointer to length of NFCID1 (UID)
 *
 * \return RFAL_ERR_WRONG_STATE  : RFAL not initialized or mode not set
 * \return RFAL_ERR_PARAM        : Invalid parameters
 * \return RFAL_ERR_IO           : Generic internal error
 * \return RFAL_ERR_PROTO        : Card length invalid
 * \return RFAL_ERR_IGNORE       : conDevLimit is 0 and there is a collision
 * \return RFAL_ERR_NONE         : No error
 *****************************************************************************
 */
ReturnCode rfalNfcaPollerSingleCollisionResolution( uint8_t devLimit, bool *collPending, rfalNfcaSelRes *selRes, uint8_t *nfcId1, uint8_t *nfcId1Len );


/*! 
 *****************************************************************************
 * \brief  NFC-A Poller Full Collision Resolution
 *  
 * Performs a full Collision resolution as defined in Activity 2.1  9.3.4
 *
 * \param[in]  compMode    : compliance mode to be performed
 * \param[in]  devLimit    : device limit value, and size nfcaDevList
 * \param[out] nfcaDevList : NFC-A listener device info
 * \param[out] devCnt      : Devices found counter
 *
 * When compMode is set to ISO compliance it assumes that the device is
 * not sleeping and therefore no ALL_REQ (WUPA) is sent at the beginning.
 * When compMode is set to NFC compliance an additional ALL_REQ (WUPA) is sent 
 * at the beginning.
 *  
 *  
 * When devLimit = 0 it is configured to perform collision detection only. Once a collision 
 * is detected the collision resolution is aborted immidiatly. If only one device is found
 * with no collisions, it will properly resolved.
 *
 *
 * \return RFAL_ERR_WRONG_STATE  : RFAL not initialized or mode not set
 * \return RFAL_ERR_PARAM        : Invalid parameters
 * \return RFAL_ERR_IO           : Generic internal error
 * \return RFAL_ERR_NONE         : No error
 *****************************************************************************
 */
ReturnCode rfalNfcaPollerFullCollisionResolution( rfalComplianceMode compMode, uint8_t devLimit, rfalNfcaListenDevice *nfcaDevList, uint8_t *devCnt );


/*! 
 *****************************************************************************
 * \brief  NFC-A Poller Full Collision Resolution with Sleep
 *  
 * Performs a full Collision resolution similar to rfalNfcaPollerFullCollisionResolution
 * but an additional SLP_REQ (HLTA) -> SENS_RES (REQA) is sent regardless if there 
 * was a collision.
 * This proprietary behaviour ensures proper activation of certain devices that suffer
 * from influence of Type B commands as foreseen in ISO14443-3 5.2.3 or were somehow
 * not detected by the first round of collision resolution
 *
 * \param[in]  devLimit    : device limit value, and size nfcaDevList
 * \param[out] nfcaDevList : NFC-A listener device info
 * \param[out] devCnt      : Devices found counter
 *  
 *
 * \return RFAL_ERR_WRONG_STATE  : RFAL not initialized or mode not set
 * \return RFAL_ERR_PARAM        : Invalid parameters
 * \return RFAL_ERR_IO           : Generic internal error
 * \return RFAL_ERR_NONE         : No error
 *****************************************************************************
 */
ReturnCode rfalNfcaPollerSleepFullCollisionResolution( uint8_t devLimit, rfalNfcaListenDevice *nfcaDevList, uint8_t *devCnt );


/*!
 *****************************************************************************
 * \brief  NFC-A Poller Start Full Collision Resolution
 *  
 * This method starts the full Collision resolution as defined 
  * in Activity 1.0 or 1.1  9.3.4
 *
 * \param[in]  compMode    : compliance mode to be performed
 * \param[in]  devLimit    : device limit value, and size nfcaDevList
 * \param[out] nfcaDevList : NFC-A listener device info
 * \param[out] devCnt      : Devices found counter
 *
 * When compMode is set to ISO compliance it assumes that the device is
 * not sleeping and therefore no ALL_REQ (WUPA) is sent at the beginning.
 * When compMode is set to NFC compliance an additional ALL_REQ (WUPA) is sent at 
 * the beginning.
 *  
 *  
 * When devLimit = 0 it is configured to perform collision detection only. Once a collision 
 * is detected the collision resolution is aborted immidiatly. If only one device is found
 * with no collisions, it will properly resolved.
 *
 *
 * \return RFAL_ERR_WRONG_STATE  : RFAL not initialized or mode not set
 * \return RFAL_ERR_PARAM        : Invalid parameters
 * \return RFAL_ERR_IO           : Generic internal error
 * \return RFAL_ERR_NONE         : No error
 *****************************************************************************
 */
ReturnCode rfalNfcaPollerStartFullCollisionResolution( rfalComplianceMode compMode, uint8_t devLimit, rfalNfcaListenDevice *nfcaDevList, uint8_t *devCnt );


/*!
 *****************************************************************************
 *  \brief  NFC-A Get Full Collision Resolution Status
 *
 *  Returns the Collision Resolution status
 *
 *  \return RFAL_ERR_BUSY         : Operation is ongoing
 *  \return RFAL_ERR_WRONG_STATE  : RFAL not initialized or incorrect mode
 *  \return RFAL_ERR_PARAM        : Invalid parameters
 *  \return RFAL_ERR_IO           : Generic internal error
 *  \return RFAL_ERR_TIMEOUT      : Timeout error
 *  \return RFAL_ERR_PAR          : Parity error detected
 *  \return RFAL_ERR_CRC          : CRC error detected
 *  \return RFAL_ERR_FRAMING      : Framing error detected
 *  \return RFAL_ERR_PROTO        : Protocol error detected
 *  \return RFAL_ERR_NONE         : No error, activation successful
 *****************************************************************************
 */
ReturnCode rfalNfcaPollerGetFullCollisionResolutionStatus( void );


/*!
 *****************************************************************************
 * \brief NFC-A Listener is SLP_REQ 
 * 
 * Checks if the given buffer contains valid NFC-A SLP_REQ (HALT)
 * 
 * \param[in] buf: buffer containing data
 * \param[in] bufLen: length of the data in buffer to be checked
 * 
 * \return true if data in buf contains a SLP_REQ ; false otherwise
 *****************************************************************************
 */
bool rfalNfcaListenerIsSleepReq( const uint8_t *buf, uint16_t bufLen );


#endif /* RFAL_NFCA_H */

/**
  * @}
  *
  * @}
  *
  * @}
  */
