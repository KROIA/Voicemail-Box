
/**
  ******************************************************************************
  * @file    rfal_t4t.h
  * @author  MMY Application Team
  * @brief   Provides convenience methods and definitions for T4T (ISO7816-4)
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


#ifndef RFAL_T4T_H
#define RFAL_T4T_H

/*
 ******************************************************************************
 * INCLUDES
 ******************************************************************************
 */
#include "rfal_platform.h"
#include "rfal_utils.h"
#include "rfal_rf.h"
#include "rfal_isoDep.h"

/*
 ******************************************************************************
 * GLOBAL DEFINES
 ******************************************************************************
 */

#define RFAL_T4T_MAX_CAPDU_PROLOGUE_LEN                          4U                          /*!< Command-APDU prologue length (CLA INS P1 P2)                    */
#define RFAL_T4T_LE_LEN                                          1U                          /*!< Le Expected Response Length (short field coding)                */
#define RFAL_T4T_LC_LEN                                          1U                          /*!< Lc Data field length  (short field coding)                      */
#define RFAL_T4T_MAX_RAPDU_SW1SW2_LEN                            2U                          /*!< SW1 SW2 length                                                  */
#define RFAL_T4T_CLA                                          0x00U                          /*!< Class byte (contains 00h because secure message are not used)   */

#define RFAL_T4T_ISO7816_P1_SELECT_BY_DF_NAME                 0x04U                          /*!< P1 value for Select by name                                     */
#define RFAL_T4T_ISO7816_P1_SELECT_BY_FILEID                  0x00U                          /*!< P1 value for Select by file identifier                          */
#define RFAL_T4T_ISO7816_P2_SELECT_FIRST_OR_ONLY_OCCURENCE    0x00U                          /*!<      b2b1 P2 value for First or only occurence                  */
#define RFAL_T4T_ISO7816_P2_SELECT_RETURN_FCI_TEMPLATE        0x00U                          /*!< b4b3      P2 value for Return FCI template                      */
#define RFAL_T4T_ISO7816_P2_SELECT_NO_RESPONSE_DATA           0x0CU                          /*!< b4b3      P2 value for No responce data                         */

#define RFAL_T4T_ISO7816_STATUS_COMPLETE                      0x9000U                        /*!< Command completed \ Normal processing - No further qualification*/


/*
******************************************************************************
* GLOBAL VARIABLES
******************************************************************************
*/


/*
******************************************************************************
* GLOBAL TYPES
******************************************************************************
*/
/*! NFC-A T4T Command-APDU structure */
typedef struct
{
    uint8_t                  CLA;                              /*!< Class byte                                         */
    uint8_t                  INS;                              /*!< Instruction byte                                   */
    uint8_t                  P1;                               /*!< Parameter byte 1                                   */
    uint8_t                  P2;                               /*!< Parameter byte 2                                   */
    uint8_t                  Lc;                               /*!< Data field length                                  */
    bool                     LcFlag;                           /*!< Lc flag (append Lc when true)                      */
    uint8_t                  Le;                               /*!< Expected Response Length                           */
    bool                     LeFlag;                           /*!< Le flag (append Le when true)                      */
    
    rfalIsoDepApduBufFormat  *cApduBuf;                        /*!< Command-APDU buffer  (Tx)                          */
    uint16_t                 *cApduLen;                        /*!< Command-APDU Length                                */
}rfalT4tCApduParam;

/*! NFC-A T4T Response-APDU structure */
typedef struct
{    
    rfalIsoDepApduBufFormat  *rApduBuf;                        /*!< Response-APDU buffer (Rx)                          */
    uint16_t                 rcvdLen;                          /*!< Full response length                               */
    uint16_t                 rApduBodyLen;                     /*!< Response body length                               */
    uint16_t                 statusWord;                       /*!< R-APDU Status Word SW1|SW2                         */
}rfalT4tRApduParam;



/*! NFC-A T4T command set    T4T 1.0 & ISO7816-4 2013 Table 4 */
typedef enum
{
    RFAL_T4T_INS_SELECT           = 0xA4U,                     /*!< T4T Select                                         */
    RFAL_T4T_INS_READBINARY       = 0xB0U,                     /*!< T4T ReadBinary                                     */
    RFAL_T4T_INS_UPDATEBINARY     = 0xD6U,                     /*!< T4T UpdateBinay                                    */
    RFAL_T4T_INS_READBINARY_ODO   = 0xB1U,                     /*!< T4T ReadBinary using ODO                           */
    RFAL_T4T_INS_UPDATEBINARY_ODO = 0xD7U                      /*!< T4T UpdateBinay using ODO                          */
} rfalT4tCmds;

/*
******************************************************************************
* GLOBAL FUNCTION PROTOTYPES
******************************************************************************
*/

/*! 
 *****************************************************************************
 * \brief  T4T Compose APDU
 *  
 * This method computes a C-APDU according to NFC Forum T4T and ISO7816-4.
 * 
 * If C-APDU contains data to be sent, it must be placed inside the buffer
 *   rfalT4tTxRxApduParam.txRx.cApduBuf.apdu and signaled by Lc
 *
 * To transceive the formed APDU the ISO-DEP layer shall be used
 *
 * \see rfalIsoDepStartApduTransceive()
 * \see rfalIsoDepGetApduTransceiveStatus()
 * \see rfalT4TPollerParseRAPDU()
 *
 * \warning The ISO-DEP module is used to perform the tranceive. Usually 
 *          activation has been done via ISO-DEP activatiavtion. If not
 *          please call rfalIsoDepInitialize() before.
 * 
 * \param[in,out] apduParam : APDU parameters
 *                            apduParam.cApduLen will contain the APDU length 
 * 
 * \return RFAL_ERR_PARAM        : Invalid parameter
 * \return RFAL_ERR_PROTO        : Protocol error
 * \return RFAL_ERR_NONE         : No error
 *****************************************************************************
 */
ReturnCode rfalT4TPollerComposeCAPDU( const rfalT4tCApduParam *apduParam );


/*! 
 *****************************************************************************
 * \brief  T4T Parse R-APDU
 *  
 * This method parses a R-APDU according to NFC Forum T4T and ISO7816-4.
 * It will extract the data length and check if the Satus word is expected.
 *
 * \param[in,out] apduParam : APDU parameters
 *                            apduParam.rApduBodyLen will contain the data length 
 *                            apduParam.statusWord will contain the SW1 and SW2 
 * 
 * \return RFAL_ERR_REQUEST      : Status word (SW1 SW2) different from 9000
 * \return RFAL_ERR_PARAM        : Invalid parameter
 * \return RFAL_ERR_PROTO        : Protocol error
 * \return RFAL_ERR_NONE         : No error
 *****************************************************************************
 */
ReturnCode rfalT4TPollerParseRAPDU( rfalT4tRApduParam *apduParam );

/*! 
 *****************************************************************************
 * \brief  T4T Compose Select Application APDU
 *  
 * This method computes a Select Application APDU according to NFC Forum T4T
 *
 * To transceive the formed APDU the ISO-DEP layer shall be used
 *
 * \see rfalIsoDepStartApduTransceive()
 * \see rfalIsoDepGetApduTransceiveStatus()
 * 
 * \param[out]     cApduBuf : buffer where the C-APDU will be placed
 * \param[in]      aid      : Application ID to be used
 * \param[in]      aidLen   : Application ID length
 * \param[out]     cApduLen : Composed C-APDU length
 * 
 * \return RFAL_ERR_PARAM        : Invalid parameter
 * \return RFAL_ERR_PROTO        : Protocol error
 * \return RFAL_ERR_NONE         : No error
 *****************************************************************************
 */
ReturnCode rfalT4TPollerComposeSelectAppl( rfalIsoDepApduBufFormat *cApduBuf, const uint8_t* aid, uint8_t aidLen, uint16_t *cApduLen );

/*! 
 *****************************************************************************
 * \brief  T4T Compose Select File APDU
 *  
 * This method computes a Select File APDU according to NFC Forum T4T
 *
 * To transceive the formed APDU the ISO-DEP layer shall be used
 *
 * \see rfalIsoDepStartApduTransceive()
 * \see rfalIsoDepGetApduTransceiveStatus()
 * 
 * \param[out]     cApduBuf : buffer where the C-APDU will be placed
 * \param[in]      fid      : File ID to be used
 * \param[in]      fidLen   : File ID length
 * \param[out]     cApduLen : Composed C-APDU length
 * 
 * \return RFAL_ERR_PARAM        : Invalid parameter
 * \return RFAL_ERR_PROTO        : Protocol error
 * \return RFAL_ERR_NONE         : No error
 *****************************************************************************
 */
ReturnCode rfalT4TPollerComposeSelectFile( rfalIsoDepApduBufFormat *cApduBuf, const uint8_t* fid, uint8_t fidLen, uint16_t *cApduLen );

/*! 
 *****************************************************************************
 * \brief  T4T Compose Select File APDU for Mapping Version 1
 *  
 * This method computes a Select File APDU according to NFC Forum T4TOP_v1.0
 *
 * To transceive the formed APDU the ISO-DEP layer shall be used
 *
 * \see rfalIsoDepStartApduTransceive()
 * \see rfalIsoDepGetApduTransceiveStatus()
 * 
 * \param[out]     cApduBuf : buffer where the C-APDU will be placed
 * \param[in]      fid      : File ID to be used
 * \param[in]      fidLen   : File ID length
 * \param[out]     cApduLen : Composed C-APDU length
 * 
 * \return RFAL_ERR_PARAM        : Invalid parameter
 * \return RFAL_ERR_PROTO        : Protocol error
 * \return RFAL_ERR_NONE         : No error
 *****************************************************************************
 */
ReturnCode rfalT4TPollerComposeSelectFileV1Mapping( rfalIsoDepApduBufFormat *cApduBuf, const uint8_t* fid, uint8_t fidLen, uint16_t *cApduLen );

/*! 
 *****************************************************************************
 * \brief  T4T Compose Read Data APDU
 *  
 * This method computes a Read Data APDU according to NFC Forum T4T
 *
 * To transceive the formed APDU the ISO-DEP layer shall be used
 *
 * \see rfalIsoDepStartApduTransceive()
 * \see rfalIsoDepGetApduTransceiveStatus()
 * 
 * \param[out]     cApduBuf : buffer where the C-APDU will be placed
 * \param[in]      offset   : File offset
 * \param[in]      expLen   : Expected length (Le)
 * \param[out]     cApduLen : Composed C-APDU length
 * 
 * \return RFAL_ERR_PARAM        : Invalid parameter
 * \return RFAL_ERR_PROTO        : Protocol error
 * \return RFAL_ERR_NONE         : No error
 *****************************************************************************
 */
ReturnCode rfalT4TPollerComposeReadData( rfalIsoDepApduBufFormat *cApduBuf, uint16_t offset, uint8_t expLen, uint16_t *cApduLen );

/*! 
 *****************************************************************************
 * \brief  T4T Compose Read Data ODO APDU
 *  
 * This method computes a Read Data ODO APDU according to NFC Forum T4T
 *
 * To transceive the formed APDU the ISO-DEP layer shall be used
 *
 * \see rfalIsoDepStartApduTransceive()
 * \see rfalIsoDepGetApduTransceiveStatus()
 * 
 * \param[out]     cApduBuf : buffer where the C-APDU will be placed
 * \param[in]      offset   : File offset
 * \param[in]      expLen   : Expected length (Le)
 * \param[out]     cApduLen : Composed C-APDU length
 * 
 * \return RFAL_ERR_PARAM        : Invalid parameter
 * \return RFAL_ERR_PROTO        : Protocol error
 * \return RFAL_ERR_NONE         : No error
 *****************************************************************************
 */
ReturnCode rfalT4TPollerComposeReadDataODO( rfalIsoDepApduBufFormat *cApduBuf, uint32_t offset, uint8_t expLen, uint16_t *cApduLen );

/*! 
 *****************************************************************************
 * \brief  T4T Compose Write Data APDU
 *  
 * This method computes a Write Data APDU according to NFC Forum T4T
 *
 * To transceive the formed APDU the ISO-DEP layer shall be used
 *
 * \see rfalIsoDepStartApduTransceive()
 * \see rfalIsoDepGetApduTransceiveStatus()
 * 
 * \param[out]     cApduBuf : buffer where the C-APDU will be placed
 * \param[in]      offset   : File offset
 * \param[in]      data     : Data to be written
 * \param[in]      dataLen  : Data length to be written (Lc)
 * \param[out]     cApduLen : Composed C-APDU length
 * 
 * \return RFAL_ERR_PARAM        : Invalid parameter
 * \return RFAL_ERR_PROTO        : Protocol error
 * \return RFAL_ERR_NONE         : No error
 *****************************************************************************
 */
ReturnCode rfalT4TPollerComposeWriteData( rfalIsoDepApduBufFormat *cApduBuf, uint16_t offset, const uint8_t* data, uint8_t dataLen, uint16_t *cApduLen );

/*! 
 *****************************************************************************
 * \brief  T4T Compose Write Data ODO APDU
 *  
 * This method computes a Write Data ODO sAPDU according to NFC Forum T4T
 *
 * To transceive the formed APDU the ISO-DEP layer shall be used
 *
 * \see rfalIsoDepStartApduTransceive()
 * \see rfalIsoDepGetApduTransceiveStatus()
 * 
 * \param[out]     cApduBuf : buffer where the C-APDU will be placed
 * \param[in]      offset   : File offset
 * \param[in]      data     : Data to be written
 * \param[in]      dataLen  : Data length to be written (Lc)
 * \param[out]     cApduLen : Composed C-APDU length
 * 
 * \return RFAL_ERR_PARAM        : Invalid parameter
 * \return RFAL_ERR_PROTO        : Protocol error
 * \return RFAL_ERR_NONE         : No error
 *****************************************************************************
 */
ReturnCode rfalT4TPollerComposeWriteDataODO( rfalIsoDepApduBufFormat *cApduBuf, uint32_t offset, const uint8_t* data, uint8_t dataLen, uint16_t *cApduLen );

#endif /* RFAL_T4T_H */

/**
  * @}
  *
  * @}
  *
  * @}
  */
