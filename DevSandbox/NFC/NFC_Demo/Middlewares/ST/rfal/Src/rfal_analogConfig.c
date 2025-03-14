
/**
  ******************************************************************************
  * @file    rfal_analogConfig.c
  * @author  MMY Application Team
  * @brief   Funcitons to manage and set analog settings.
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
  
/*
 ******************************************************************************
 * INCLUDES
 ******************************************************************************
 */
#include "rfal_analogConfig.h"
#include "rfal_chip.h"
#include "rfal_utils.h"
#include "rfal_platform.h"


#ifndef RFAL_FEATURE_DYNAMIC_ANALOG_CONFIG
	#define RFAL_FEATURE_DYNAMIC_ANALOG_CONFIG     false       /*!<  Dynamic Analog Configs config missing. Disabled by default */
#endif /* RFAL_FEATURE_DYNAMIC_ANALOG_CONFIG */


/* Check whether the Default Analog settings are to be used or custom ones */
#ifdef RFAL_ANALOG_CONFIG_CUSTOM
    extern const uint8_t  rfalAnalogConfigCustomSettings[];
    extern const uint16_t rfalAnalogConfigCustomSettingsLength;
#else
    #include "rfal_analogConfigTbl.h"
#endif

/*
 ******************************************************************************
 * DEFINES
 ******************************************************************************
 */


#define RFAL_TEST_REG         0x0080U      /*!< Test Register indicator  */    

/*
 ******************************************************************************
 * MACROS
 ******************************************************************************
 */

/*
 ******************************************************************************
 * LOCAL DATA TYPES
 ******************************************************************************
 */

#if RFAL_FEATURE_DYNAMIC_ANALOG_CONFIG
    static uint8_t gRfalAnalogConfig[RFAL_ANALOG_CONFIG_TBL_SIZE]; /*!< Analog Configuration Settings List */
#endif /* RFAL_FEATURE_DYNAMIC_ANALOG_CONFIG */


/*! Struct for Analog Config Look Up Table Update */
typedef struct {
    const uint8_t *currentAnalogConfigTbl; /*!< Reference to start of current Analog Configuration      */
    uint16_t configTblSize;          /*!< Total size of Analog Configuration                      */
    bool    ready;                  /*!< Indicate if Look Up Table is complete and ready for use */
} rfalAnalogConfigMgmt;

static rfalAnalogConfigMgmt   gRfalAnalogConfigMgmt;  /*!< Analog Configuration LUT management */

/*
 ******************************************************************************
 * LOCAL TABLES
 ******************************************************************************
 */

/*
 ******************************************************************************
 * LOCAL FUNCTION PROTOTYPES
 ******************************************************************************
 */
static rfalAnalogConfigNum rfalAnalogConfigSearch( rfalAnalogConfigId configId, uint16_t *configOffset );

#if RFAL_FEATURE_DYNAMIC_ANALOG_CONFIG
    static void rfalAnalogConfigPtrUpdate( const uint8_t* analogConfigTbl );
#endif /* RFAL_FEATURE_DYNAMIC_ANALOG_CONFIG */

/*
 ******************************************************************************
 * GLOBAL VARIABLE DEFINITIONS
 ******************************************************************************
 */

/*
 ******************************************************************************
 * GLOBAL FUNCTIONS
 ******************************************************************************
 */

void rfalAnalogConfigInitialize( void )
{
    /* Use default Analog configuration settings in Flash by default. */

/* Check whether the Default Analog settings are to be used or custom ones */  
#ifdef RFAL_ANALOG_CONFIG_CUSTOM
    gRfalAnalogConfigMgmt.currentAnalogConfigTbl = rfalAnalogConfigCustomSettings;
    gRfalAnalogConfigMgmt.configTblSize          = rfalAnalogConfigCustomSettingsLength;
#else  
    gRfalAnalogConfigMgmt.currentAnalogConfigTbl = rfalAnalogConfigDefaultSettings;
    gRfalAnalogConfigMgmt.configTblSize          = sizeof(rfalAnalogConfigDefaultSettings);
#endif
  
  gRfalAnalogConfigMgmt.ready = true;
} /* rfalAnalogConfigInitialize() */


bool rfalAnalogConfigIsReady( void )
{
    return gRfalAnalogConfigMgmt.ready;
}

ReturnCode rfalAnalogConfigListWriteRaw( const uint8_t *configTbl, uint16_t configTblSize )
{
#if RFAL_FEATURE_DYNAMIC_ANALOG_CONFIG
    
    /* Check if the Configuration Table exceed the Table size */
    if ( configTblSize >= RFAL_ANALOG_CONFIG_TBL_SIZE )
    {
        rfalAnalogConfigInitialize(); /* Revert to default Analog Configuration */
        return RFAL_ERR_NOMEM;
    }
    
    /* Check for invalid parameters */
    if( (configTbl == NULL) || (configTblSize == 0U) )
    {
        return RFAL_ERR_PARAM;
    }
    
    /* NOTE: Function does not check for the validity of the Table contents (conf IDs, conf sets, register address)  */
    RFAL_MEMCPY( gRfalAnalogConfig, configTbl, configTblSize );
    
    /* Update the total size of configuration settings */
    gRfalAnalogConfigMgmt.configTblSize = configTblSize;
        
    rfalAnalogConfigPtrUpdate(gRfalAnalogConfig);
    return RFAL_ERR_NONE;
    
#else
    
    // If Analog Configuration Update is to be disabled
    RFAL_NO_WARNING(configTbl);
    RFAL_NO_WARNING(configTblSize);
    return RFAL_ERR_REQUEST;
    
#endif /* RFAL_FEATURE_DYNAMIC_ANALOG_CONFIG */
}

ReturnCode rfalAnalogConfigListWrite( uint8_t more, const rfalAnalogConfig *config )
{
#if RFAL_FEATURE_DYNAMIC_ANALOG_CONFIG
    
    rfalAnalogConfigId configId;
    rfalAnalogConfigNum numConfig;
    uint8_t configSize;

    if (true == gRfalAnalogConfigMgmt.ready)
    {   /* First Update to the Configuration list. */
        gRfalAnalogConfigMgmt.ready = false;   // invalidate the config List
        gRfalAnalogConfigMgmt.configTblSize = 0; // Clear the config List
    }

    configId = RFAL_GETU16(config->id);
    
    /* Check validity of the Configuration ID. */
    /* NOTE: Direction DPO uses 2msb of the Technology field as level indicator */
    if ( ((RFAL_ANALOG_CONFIG_TECH_RFU <= RFAL_ANALOG_CONFIG_ID_GET_TECH(configId)) && (RFAL_ANALOG_CONFIG_ID_GET_DIRECTION(configId) != RFAL_ANALOG_CONFIG_DPO))
       ||((RFAL_ANALOG_CONFIG_BITRATE_6780 < RFAL_ANALOG_CONFIG_ID_GET_BITRATE(configId)) && (RFAL_ANALOG_CONFIG_BITRATE_53 > RFAL_ANALOG_CONFIG_ID_GET_BITRATE(configId)))
       ||(RFAL_ANALOG_CONFIG_BITRATE_1p6 < RFAL_ANALOG_CONFIG_ID_GET_BITRATE(configId))
       )
    {
        rfalAnalogConfigInitialize(); /* Revert to default Analog Configuration */
        return RFAL_ERR_PARAM;
    }
                    
    numConfig = config->num;
    configSize = (uint8_t)(sizeof(rfalAnalogConfigId) + sizeof(rfalAnalogConfigNum) + (numConfig * sizeof(rfalAnalogConfigRegAddrMaskVal)));
    
    /* Check if the Configuration Set exceed the Table size. */
    if ( RFAL_ANALOG_CONFIG_TBL_SIZE <= (gRfalAnalogConfigMgmt.configTblSize + configSize) )
    {
        rfalAnalogConfigInitialize(); /* Revert to default Analog Configuration */
        return RFAL_ERR_NOMEM;
    }
    
    /* NOTE: Function does not check for the validity of the Register Address. */
    RFAL_MEMCPY(&gRfalAnalogConfig[gRfalAnalogConfigMgmt.configTblSize], (const uint8_t*)config, configSize);
    
    /* Increment the total size of configuration settings. */
    gRfalAnalogConfigMgmt.configTblSize += configSize;

    /* Check if it is the last Analog Configuration to load. */
    if (RFAL_ANALOG_CONFIG_UPDATE_LAST == more)
    {   /* Update the Analog Configuration to the new settings. */
        rfalAnalogConfigPtrUpdate(gRfalAnalogConfig);
    }
    
    return RFAL_ERR_NONE;
    
#else
    
    // If Analog Configuration Update is to be disabled
    RFAL_NO_WARNING(config);
    RFAL_NO_WARNING(more);
    return RFAL_ERR_DISABLED;
    
#endif /* RFAL_FEATURE_DYNAMIC_ANALOG_CONFIG */
    
} /* rfalAnalogConfigListUpdate() */

ReturnCode rfalAnalogConfigListReadRaw( uint8_t *tblBuf, uint16_t tblBufLen, uint16_t *configTblSize )
{
    /* Check if the the current table will fit into the given buffer */
    if( tblBufLen < gRfalAnalogConfigMgmt.configTblSize )
    {
        return RFAL_ERR_NOMEM;
    }
    
    /* Check for invalid parameters */
    if( configTblSize == NULL )
    {
        return RFAL_ERR_PARAM;
    }
    
    /* Copy the whole Table to the given buffer */
    if( gRfalAnalogConfigMgmt.configTblSize > 0U )                     /* MISRA 21.18 */
    {
        RFAL_MEMCPY( tblBuf, gRfalAnalogConfigMgmt.currentAnalogConfigTbl, gRfalAnalogConfigMgmt.configTblSize );
    }
    *configTblSize = gRfalAnalogConfigMgmt.configTblSize;
    
    return RFAL_ERR_NONE;
}

ReturnCode rfalAnalogConfigListRead( rfalAnalogConfigOffset *configOffset, uint8_t *more, rfalAnalogConfig *config, rfalAnalogConfigNum numConfig )
{
    uint16_t configSize;
    const rfalAnalogConfigOffset offset = *configOffset;
    rfalAnalogConfigNum numConfigSet;
    
    /* Check if the number of register-mask-value settings for the respective Configuration ID will fit into the buffer passed in. */
    if (gRfalAnalogConfigMgmt.currentAnalogConfigTbl[offset + sizeof(rfalAnalogConfigId)] > numConfig)
    {
        return RFAL_ERR_NOMEM;
    }

    /* Get the number of Configuration set */
    numConfigSet = gRfalAnalogConfigMgmt.currentAnalogConfigTbl[offset + sizeof(rfalAnalogConfigId)];
    
    /* Pass Configuration Register-Mask-Value sets */
    configSize = (sizeof(rfalAnalogConfigId) + sizeof(rfalAnalogConfigNum) + (uint16_t)(numConfigSet * sizeof(rfalAnalogConfigRegAddrMaskVal)));
    RFAL_MEMCPY( (uint8_t*) config
              , &gRfalAnalogConfigMgmt.currentAnalogConfigTbl[offset]
              , configSize
              );
    *configOffset = offset + configSize;
                
    /* Check if it is the last Analog Configuration in the Table.*/
    *more = (uint8_t)((*configOffset >= gRfalAnalogConfigMgmt.configTblSize) ? RFAL_ANALOG_CONFIG_UPDATE_LAST
                                                                             : RFAL_ANALOG_CONFIG_UPDATE_MORE); 

    return RFAL_ERR_NONE;
} /* rfalAnalogConfigListRead() */


ReturnCode rfalSetAnalogConfig( rfalAnalogConfigId configId )
{
    rfalAnalogConfigOffset configOffset = 0;
    rfalAnalogConfigNum numConfigSet;
    const rfalAnalogConfigRegAddrMaskVal *configTbl;
    ReturnCode retCode = RFAL_ERR_NONE;
    rfalAnalogConfigNum i;
    
    if (true != gRfalAnalogConfigMgmt.ready)
    {
        return RFAL_ERR_REQUEST;
    }
    
    /* Search LUT for the specific Configuration ID. */
    while(true)
    {
        numConfigSet = rfalAnalogConfigSearch(configId, &configOffset);
        if( RFAL_ANALOG_CONFIG_LUT_NOT_FOUND == numConfigSet )
        {
            break;
        }
        
        configTbl = (rfalAnalogConfigRegAddrMaskVal *)( (uintptr_t)gRfalAnalogConfigMgmt.currentAnalogConfigTbl + (uint32_t)configOffset); 
        /* Increment the offset to the next index to search from. */
        configOffset += (uint16_t)(numConfigSet * sizeof(rfalAnalogConfigRegAddrMaskVal)); 
        
        if ((gRfalAnalogConfigMgmt.configTblSize + 1U) < configOffset)
        {   /* Error check make sure that the we do not access outside the configuration Table Size */
            return RFAL_ERR_NOMEM;
        }
        
        for ( i = 0; i < numConfigSet; i++)
        {
            if( (RFAL_GETU16(configTbl[i].addr) & RFAL_TEST_REG) != 0U )
            {
                RFAL_EXIT_ON_ERR(retCode, rfalChipChangeTestRegBits( (RFAL_GETU16(configTbl[i].addr) & ~RFAL_TEST_REG), configTbl[i].mask, configTbl[i].val) );
            }
            else
            {
                RFAL_EXIT_ON_ERR(retCode, rfalChipChangeRegBits( RFAL_GETU16(configTbl[i].addr), configTbl[i].mask, configTbl[i].val) );
            }
        }
        
    } /* while(found Analog Config Id) */
    
    return retCode;
    
} /* rfalSetAnalogConfig() */


uint16_t rfalAnalogConfigGenModeID( rfalMode md, rfalBitRate br, uint16_t dir )
{
    uint16_t id;
    
    /* Assign Poll/Listen Mode */
    id = ((md >= RFAL_MODE_LISTEN_NFCA) ? RFAL_ANALOG_CONFIG_LISTEN : RFAL_ANALOG_CONFIG_POLL);
    
    /* Assign Technology */
    switch( md )
    {
        case RFAL_MODE_POLL_NFCA:
        case RFAL_MODE_POLL_NFCA_T1T:
        case RFAL_MODE_LISTEN_NFCA:            
            id |= RFAL_ANALOG_CONFIG_TECH_NFCA;
            break;
        
        case RFAL_MODE_POLL_NFCB:
        case RFAL_MODE_POLL_B_PRIME:
        case RFAL_MODE_POLL_B_CTS:
        case RFAL_MODE_LISTEN_NFCB:
            id |= RFAL_ANALOG_CONFIG_TECH_NFCB;
            break;
        
        case RFAL_MODE_POLL_NFCF:
        case RFAL_MODE_LISTEN_NFCF:
            id |= RFAL_ANALOG_CONFIG_TECH_NFCF;
            break;
        
        case RFAL_MODE_POLL_NFCV:
        case RFAL_MODE_POLL_PICOPASS:
            id |= RFAL_ANALOG_CONFIG_TECH_NFCV;
            break;
        
        case RFAL_MODE_POLL_ACTIVE_P2P:
        case RFAL_MODE_LISTEN_ACTIVE_P2P:
            id |= RFAL_ANALOG_CONFIG_TECH_AP2P;
            break;
        
        default:
            id = RFAL_ANALOG_CONFIG_TECH_CHIP;
            break;
    }
    
    /* Assign Bitrate */
    id |= (((((uint16_t)(br) >= (uint16_t)RFAL_BR_52p97) ? (uint16_t)(br) : ((uint16_t)(br)+1U)) << RFAL_ANALOG_CONFIG_BITRATE_SHIFT) & RFAL_ANALOG_CONFIG_BITRATE_MASK);
    
    /* Assign Direction */
    id |= ((dir<<RFAL_ANALOG_CONFIG_DIRECTION_SHIFT) & RFAL_ANALOG_CONFIG_DIRECTION_MASK);
    
    return id;
    
} /* rfalAnalogConfigGenModeID() */

/*
 ******************************************************************************
 * LOCAL FUNCTIONS
 ******************************************************************************
 */

/*! 
 *****************************************************************************
 * \brief  Update the link to Analog Configuration LUT
 *  
 * Update the link to the Analog Configuration LUT for the subsequent search 
 * of Analog Settings.
 * 
 * \param[in]  analogConfigTbl: reference to the start of the new Analog Configuration Table
 *
 *****************************************************************************
 */
#if RFAL_FEATURE_DYNAMIC_ANALOG_CONFIG
static void rfalAnalogConfigPtrUpdate( const uint8_t* analogConfigTbl )
{

    gRfalAnalogConfigMgmt.currentAnalogConfigTbl = analogConfigTbl;
    gRfalAnalogConfigMgmt.ready = true;
    
} /* rfalAnalogConfigPtrUpdate() */
#endif /* RFAL_FEATURE_DYNAMIC_ANALOG_CONFIG */


/*! 
 *****************************************************************************
 * \brief  Search the Analog Configuration LUT for a specific Configuration ID.
 *  
 * Search the Analog Configuration LUT for the Configuration ID.
 * 
 * \param[in]  configId: Configuration ID to search for.
 * \param[in]  configOffset: Configuration Offset in Table
 * 
 * \return number of Configuration Sets
 * \return #RFAL_ANALOG_CONFIG_LUT_NOT_FOUND in case Configuration ID is not found.
 *****************************************************************************
 */
static rfalAnalogConfigNum rfalAnalogConfigSearch( rfalAnalogConfigId configId, uint16_t *configOffset )
{
    rfalAnalogConfigId foundConfigId;
    rfalAnalogConfigId configIdMaskVal;
    const uint8_t *configTbl;
    const uint8_t *currentConfigTbl;
    uint16_t i;
    
    currentConfigTbl = gRfalAnalogConfigMgmt.currentAnalogConfigTbl;
    configIdMaskVal  = ((RFAL_ANALOG_CONFIG_POLL_LISTEN_MODE_MASK | RFAL_ANALOG_CONFIG_BITRATE_MASK) 
                       |((RFAL_ANALOG_CONFIG_TECH_CHIP == RFAL_ANALOG_CONFIG_ID_GET_TECH(configId)) ? (RFAL_ANALOG_CONFIG_TECH_MASK | RFAL_ANALOG_CONFIG_CHIP_SPECIFIC_MASK) : configId)
                       |((RFAL_ANALOG_CONFIG_NO_DIRECTION == RFAL_ANALOG_CONFIG_ID_GET_DIRECTION(configId)) ? RFAL_ANALOG_CONFIG_DIRECTION_MASK : configId)
                       );
    
    
    /* When specific ConfigIDs are to be used, override search mask */
    if( (RFAL_ANALOG_CONFIG_ID_GET_DIRECTION(configId) == RFAL_ANALOG_CONFIG_DPO) )
    {
        configIdMaskVal = (RFAL_ANALOG_CONFIG_POLL_LISTEN_MODE_MASK | RFAL_ANALOG_CONFIG_TECH_MASK | RFAL_ANALOG_CONFIG_BITRATE_MASK | RFAL_ANALOG_CONFIG_DIRECTION_MASK);
    }
    
    
    i = *configOffset;
    while (i < gRfalAnalogConfigMgmt.configTblSize)
    {
        configTbl = &currentConfigTbl[i];
        foundConfigId = RFAL_GETU16(configTbl);
        if (configId == (foundConfigId & configIdMaskVal))
        {
            *configOffset = (uint16_t)(i + sizeof(rfalAnalogConfigId) + sizeof(rfalAnalogConfigNum));
            return configTbl[sizeof(rfalAnalogConfigId)];
        }
        
        /* If Config Id does not match, increment to next Configuration Id */
        i += (uint16_t)( sizeof(rfalAnalogConfigId) + sizeof(rfalAnalogConfigNum) 
                        + (configTbl[sizeof(rfalAnalogConfigId)] * sizeof(rfalAnalogConfigRegAddrMaskVal) )
                        );
    } /* for */
    
    return RFAL_ANALOG_CONFIG_LUT_NOT_FOUND;
} /* rfalAnalogConfigSearch() */
