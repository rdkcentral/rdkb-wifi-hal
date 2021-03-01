/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2016 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/

/**********************************************************************
   Copyright [2014] [Cisco Systems, Inc.]
 
   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at
 
       http://www.apache.org/licenses/LICENSE-2.0
 
   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
**********************************************************************/

/**********************************************************************

    module: cm_hal.h

        For CCSP Component:  CcspCMAgent

    ---------------------------------------------------------------

    description:

        This header file gives the function call prototypes and 
        structure definitions used for the RDK-Broadband 
        hardware abstraction layer for Cable Modem

    ---------------------------------------------------------------

    environment:

        This HAL layer is intended to support cable modem drivers 
        through an open API.  
        Changes may be needed to support different hardware enviornments.

    ---------------------------------------------------------------

    author:

        Cisco
	Comcast

**********************************************************************/


#ifndef __CM_HAL_H__
#define __CM_HAL_H__

#include <sys/time.h>

/**********************************************************************
               CONSTANT DEFINITIONS
**********************************************************************/
#define OFDM_PARAM_STR_MAX_LEN 64

#ifdef __cplusplus
extern "C"{
#endif


#ifndef CHAR
#define CHAR  char
#endif

#ifndef UCHAR
#define UCHAR unsigned char
#endif

#ifndef BOOLEAN
#define BOOLEAN  unsigned char
#endif

#ifndef USHORT
#define USHORT  unsigned short
#endif

#ifndef UINT8
#define UINT8 unsigned char
#endif

#ifndef INT
#define INT   int
#endif

#ifndef UINT
#define UINT  unsigned int
#endif

#ifndef LONG
#define LONG	long
#endif

#ifndef ULONG
#define ULONG unsigned long
#endif

#ifndef TRUE
#define TRUE     1
#endif

#ifndef FALSE
#define FALSE    0
#endif

#ifndef ENABLE
#define ENABLE   1
#endif

#ifndef RETURN_OK
#define RETURN_OK   0
#endif

#ifndef RETURN_ERR
#define RETURN_ERR   -1
#endif

#ifndef IPV4_ADDRESS_SIZE
#define  IPV4_ADDRESS_SIZE                          4
#endif

#ifndef IP_ADDRESS_LENGTH
#define  IP_ADDRESS_LENGTH                          IP_ADDRESS_SIZE
#endif

#ifndef ANSC_IPV4_ADDRESS
/*
 * While we're trying really hard to smooth the procedure of switch-over from IPv4 to IPv4, there
 * are many places where using the IP address as an integer for comparision and calculation is much
 * easier than array-based operation.
 */
#define  ANSC_IPV4_ADDRESS                                                                  \
         union                                                                              \
         {                                                                                  \
            UCHAR                   Dot[IPV4_ADDRESS_SIZE];                                 \
            ULONG                   Value;                                                  \
         }
#endif

/**
* @defgroup CM_HAL CM HAL
*
* Cable Modem HAL component provides interface that cable modem software developers can use to interface to RDK-B.
*
* @defgroup CM_HAL_TYPES  CM HAL Data Types
* @ingroup  CM_HAL
*
* @defgroup CM_HAL_APIS   CM HAL  APIs
* @ingroup  CM_HAL
*
**/


/**
 * @addtogroup CM_HAL_TYPES
 * @{
 */

/**********************************************************************
                STRUCTURE DEFINITIONS
**********************************************************************/

typedef  struct
_CMMGMT_CM_DS_CHANNEL {
    ULONG                           ChannelID;
    CHAR                            Frequency[64];
    CHAR                            PowerLevel[64];
    CHAR                            SNRLevel[64];
    CHAR                            Modulation[64];
    ULONG                           Octets;
    ULONG                           Correcteds;
    ULONG                           Uncorrectables;
    CHAR                            LockStatus[64];
}
CMMGMT_CM_DS_CHANNEL, *PCMMGMT_CM_DS_CHANNEL;

typedef  struct
_CMMGMT_CM_US_CHANNEL {
    ULONG                           ChannelID;
    CHAR                            Frequency[64];
    CHAR                            PowerLevel[64];
    CHAR                            ChannelType[64];
    CHAR                            SymbolRate[64];
    CHAR                            Modulation[64];
    CHAR                            LockStatus[64];
}
CMMGMT_CM_US_CHANNEL, *PCMMGMT_CM_US_CHANNEL;

typedef  struct
_CMMGMT_CM_DOCSIS_INFO
{
    CHAR                            DOCSISVersion[64];
    CHAR                            DOCSISDownstreamScanning[64];
    CHAR                            DOCSISDownstreamRanging[64];
    CHAR                            DOCSISUpstreamScanning[64];
    CHAR                            DOCSISUpstreamRanging[64];
    CHAR                            DOCSISTftpStatus[64];
    CHAR                            DOCSISDataRegComplete[64];
    ULONG                           DOCSISDHCPAttempts;
    CHAR                            DOCSISConfigFileName[64];
    ULONG                           DOCSISTftpAttempts;
    CHAR                            ToDStatus[64];
    BOOLEAN                         BPIState;
    BOOLEAN                         NetworkAccess;
    ANSC_IPV4_ADDRESS               UpgradeServerIP;
    ULONG                           MaxCpeAllowed;
    CHAR                            UpstreamServiceFlowParams[64];
    CHAR                            DownstreamServiceFlowParams[64];
    CHAR                            DOCSISDownstreamDataRate[64];
    CHAR                            DOCSISUpstreamDataRate[64];
    CHAR                            CoreVersion[64];
}
CMMGMT_CM_DOCSIS_INFO, *PCMMGMT_CM_DOCSIS_INFO;

typedef  struct
_CMMGMT_CM_ERROR_CODEWORDS {
    ULONG                           UnerroredCodewords;
    ULONG                           CorrectableCodewords;
    ULONG                           UncorrectableCodewords;
}
CMMGMT_CM_ERROR_CODEWORDS, *PCMMGMT_CM_ERROR_CODEWORDS;

/*
typedef enum
{
    PRI_EMERGENCY = 1,
    PRI_ALERT,
    PRI_CRITICAL,
    PRI_ERROR,
    PRI_WARNING,
    PRI_NOTICE,
    PRI_INFORMATION,
    PRI_DEBUG,

    PRI_LAST = 0xffffffff

}CMMGMT_CM_EventMgrPriorit_e;
*/

#define EVM_MAX_EVENT_TEXT      255

typedef struct
{
    UINT                docsDevEvIndex;
    struct timeval      docsDevEvFirstTime;
    struct timeval      docsDevEvLastTime;
    UINT                docsDevEvCounts;
    UINT                docsDevEvLevel;
    UINT                docsDevEvId;
    CHAR                docsDevEvText[EVM_MAX_EVENT_TEXT];
    
}CMMGMT_CM_EventLogEntry_t;

typedef  struct
_CMMGMT_DML_CM_LOG {
    BOOLEAN                         EnableLog;
    BOOLEAN                         ClearDocsisLog;
}
CMMGMT_DML_CM_LOG,  *PCMMGMT_DML_CM_LOG;

typedef  struct
_CMMGMT_DML_DOCSISLOG_FULL {
    ULONG                           Index;
    ULONG                           EventID;
    ULONG                           EventLevel;
    CHAR                            Time[64];
    CHAR                            Description[256];
}
CMMGMT_DML_DOCSISLOG_FULL,  *PCMMGMT_DML_DOCSISLOG_FULL;

typedef  struct
_CMMGMT_CM_DHCP_INFO
{
    ANSC_IPV4_ADDRESS               IPAddress;
    CHAR                            BootFileName[64];
    ANSC_IPV4_ADDRESS               SubnetMask;
    ANSC_IPV4_ADDRESS               Gateway;
    ANSC_IPV4_ADDRESS               TFTPServer;
    CHAR                            TimeServer[64];
    INT                             TimeOffset;
    ULONG                           LeaseTimeRemaining;
    CHAR                            RebindTimeRemaining[64];
    CHAR                            RenewTimeRemaining[64];
    CHAR                            MACAddress[64];
    CHAR                            DOCSISDHCPStatus[64];
}
CMMGMT_CM_DHCP_INFO, *PCMMGMT_CM_DHCP_INFO;

typedef  struct
_CMMGMT_CM_IPV6DHCP_INFO
{
    CHAR                            IPv6Address[40];
    CHAR                            IPv6BootFileName[64];
    CHAR                            IPv6Prefix[40];
    CHAR                            IPv6Router[40];
    CHAR                            IPv6TFTPServer[40];
    CHAR                            IPv6TimeServer[40];

    ULONG                           IPv6LeaseTimeRemaining;
    ULONG                           IPv6RebindTimeRemaining;
    ULONG                           IPv6RenewTimeRemaining;
}
CMMGMT_CM_IPV6DHCP_INFO, *PCMMGMT_CM_IPV6DHCP_INFO;

typedef  struct
_CMMGMT_DML_CPE_LIST
{
    CHAR                            IPAddress[32];
    CHAR                            MACAddress[32];
}
CMMGMT_DML_CPE_LIST,  *PCMMGMT_DML_CPE_LIST;

//>> Docsis3.1
typedef struct _DOCSIF31_CM_DS_OFDM_CHAN {
    unsigned int ChannelId;                     /**< The Cable Modem Termination System identification of the OFDM downstream channel within this particular MAC interface. if the interface is down, the object returns the most current value.  If the downstream channel ID is unknown, this object returns a value of 0. */
    unsigned int ChanIndicator;                 /**< This data type defines the subcarrier spacing for the FFT mode in use. For downstream OFDM channels, if the FFT mode is 4K mode, then spacing is 50 kHz; if it is 8K mode, then the spacing is 25 kHz. For upstream OFDMA channels, if the FFT mode is 2K mode, then the spacing is 50kHz; if the mode is 4K mode, then the spacing is 25kHz. In units of kHz. */
                                                /**< other(1), primary(2), backupPrimary(3), nonPrimary(4) */
    unsigned int SubcarrierZeroFreq;            /**< The center frequency of the subcarrier 0 of the OFDM transmission. Note that since ubcarrier 0 is always excluded, it will actually be below the allowed downstream spectrum band. This is the frequency of subcarrier X(0) in the definition of the DFT. */
    unsigned int FirstActiveSubcarrierNum;      /**< The number of the first non-excluded subcarrier. The valid range is 148 to 7895 */
    unsigned int LastActiveSubcarrierNum;       /**< The number of the last non-excluded subcarrier. The valid range is 148 to 7895 */
    unsigned int NumActiveSubcarriers;          /**< The number of active data subcarriers within the OFDM downstream channel (i.e. this exclude subcarriers for continuous pilots and the PLC). For 4K FFT mode, the maximum number of subcarriers including continuous pilots and the PLC cannot exceed 3800, and for 8K FFT mode, the maximum number of active subcarriers including continuous pilots and the PLC cannot be greater than 7600. */
                                                /**< There are a minimum of 56 continuous pilots in a 192MHz channel that has no exclusions, and the size of the PLC is 8 subcarriers for 4K FFT mode and 16 subcarriers for 8K FFT mode. Therefore the maximum value of NumActiveSubcarriers is 3736 (or 3800 - 56 - 8) for 4K FFT mode and 7528 (or 7600 - 56 - 16) for 8K FFT mode. */
    unsigned int SubcarrierSpacing;             /**< The subcarrier spacing associated with a particular FFT mode configured on the OFDM downstream channel. If it is 4K mode, then the subcarrier spacing is 50kHz. If it is 8K mode, then the subcarrier spacing is 25kHz. */
                                                /**< in kHz */
    unsigned int CyclicPrefix;                  /**< Cyclic prefix enables the receiver to overcome the effects of inter-symbol-interference and intercarrier-interference caused  by micro-reflections in the channel. There are five possible alues for the length of the CP and the choice depends on the delay spread of the channel - a longer delay spread requires a longer cyclic prefix. The cyclic prefix (in usec) are converted into samples using the sample rate of 204.8 Msamples/s and is an integer multiple of: 1/64 * 20 us. */
    unsigned int RollOffPeriod;                 /**< Roll off period maximizes channel capacity by sharpening the edges of the spectrum of the OFDM signal. For windowing purposes another segment at the start of the IDFT output is appended to the end of the IDFT output - the roll-off postfix (RP). There are five possible values for the (RP), and the choice depends on the bandwidth of the channel and the number of exclusion bands within the channel. A larger RP provides sharper edges in the spectrum of the OFDM signal; however,  there is a time vs. frequency trade-off. Larger RP values reduce the efficiency of transmission in the time domain, but because the spectral edges are sharper, more useful subcarriers appear in the frequency domain. There is an optimum value for the RP that maximizes capacity for a given bandwidth and/or exclusion band scenario. */
    unsigned int PlcFreq;                       /**< This is the PHY Link Channel (PLC) frequency. It is the center frequency of the lowest frequency subcarrier of the PLC. The aim of the PLC is for the CMTS to convey to the CM the physical properties of the OFDM channel */
    unsigned int NumPilots;                     /**< The number of continuous pilots configured for the OFDM downstream channel as received in the OCD message. */
    unsigned int TimeInterleaverDepth;          /**< The time interleaving used for this downstream channel as received in the OCD message. */
    char averageSNR[OFDM_PARAM_STR_MAX_LEN];    /**< The averageSNR value of this downstream channel */
    char PowerLevel[OFDM_PARAM_STR_MAX_LEN];    /**< The power level of this downstream channel */
    unsigned long long PlcTotalCodewords;       /**< The total number of PLC codewords received by the CM. */
    unsigned long long PlcUnreliableCodewords;  /**< The total number of PLC codewords which failed post-decoding LDPC syndrome check. */
    unsigned long long NcpTotalFields;          /**< The total number of NCP fields received by the CM. */
    unsigned long long NcpFieldCrcFailures;     /**< The total number of NCP fields received by the CM which failed the CRC check. */

} DOCSIF31_CM_DS_OFDM_CHAN, *PDOCSIF31_CM_DS_OFDM_CHAN;


typedef struct _DOCSIF31_CM_US_OFDMA_CHAN {
    unsigned int ChannelId;                     /**< The Cable Modem identification of the OFDMA upstream channel within this particular MAC interface. If the interface is down, the object returns the most current value.  If the upstream channel ID is unknown, this object returns a value of 0. */
    unsigned int ConfigChangeCt;                /**< The value of the Configuration Change Count field in the Upstream Channel Descriptor (UCD) MAC Management Message corresponding to this OFDMA channel. */
    unsigned int SubcarrierZeroFreq;            /**< The lower edge frequency of the OFDMA upstream channel in Hz */
    unsigned int FirstActiveSubcarrierNum;      /**< The upper edge of the OFDMA upstream channel. The minimum channel width for an OFDMA upstream channel is 6.4 MHz in 4K mode and 10MHz in 2K mode. The valid range is 74 to 3947. */
    unsigned int LastActiveSubcarrierNum;       /**< The last active subcarrier number. The valid range is 74 to 3947. */
    unsigned int NumActiveSubcarriers;          /**< The number of active subcarriers within the OFDMA upstream channel. The valid range is 1 to 3800. */
    unsigned int SubcarrierSpacing;             /**< The subcarrier spacing associated with a particular FFT mode configured on the OFDMA upstream channel. If it is 2K mode, then the subcarrier spacing is 50kHz. If it is 4K mode, then the subcarrier spacing is 25kHz. */
    unsigned int CyclicPrefix;                  /**< Cyclic prefix is added in order to enable the receiver to overcome the effects of inter-symbol interference (ISI) and inter-carrier interference caused by microreflections in the channel. The cyclic prefix (in usec) is converted into samples using the sample rate of 102.4 Msamples/s. There are eleven values for the length of the CP and the choice depends on the delay spread of the channel; a longer delay spread requires a longer cyclic prefix. */
    unsigned int RollOffPeriod;                 /**< Windowing is applied in order to maximize channel capacity by sharpening the edges of the spectrum of the OFDMA signal. Windowing is applied in the time domain by tapering (or rolling off) the edges using a raised cosine function. There are eight possible values of roll-off prefix. The Roll-Off Period is given in us and in number of samples using the sample rate of 102.4 Msamples/s. The configuration where Roll-off prefix value is greater than or equal to cyclic prefix value is considered invalid. */
    unsigned int NumSymbolsPerFrame;            /**< The number of symbol periods per frame. For channel bandwidth greater than 72MHz, the maximum number of symbol periods per frame is 18 for 2K mode and 9 for 4K mode. For channel bandwidth less than 72 MHz but greater than 48MHz, the maximum number of symbols per frame is 24 for 2K mode and 12 for 4K mode. For channel bandwidth less than 48MHz, the maximum number of symbol periods is 36 for 2K mode and 18 for 4K mode. The minimum number of symbol periods per frame is 6 for both the FFT modes and is independent of the channel bandwidth. */
    unsigned int TxPower;                       /**< The operational transmit power for the associated OFDMA upstream channel.The CM reports its Target Power, P1.6r_n as described in [PHYv3.1]. Valid values for this object are 68 to (213 + (4*(Pmax - 65 dBmV))), since 68 quarter dBmV represents the lowest Tx power value 17 dBmV and 213 represents the nearest quarter dBmV to the highest Tx power value 53.2 dBmV. */
    unsigned char PreEqEnabled;                          /**< Whether pre-equalization is enabled on the associated OFDMA upstream channel. */
} DOCSIF31_CM_US_OFDMA_CHAN, *PDOCSIF31_CM_US_OFDMA_CHAN;

typedef struct _DOCSIF31_CMSTATUSOFDMA_US {
    // The full definitions for the fields below can be referenced within DOCS-IF31-MIB.
    unsigned int ChannelId;                     // The Cable Modem identification of the
                                                // OFDMA upstream channel within this
                                                // particular MAC interface. If the
                                                // interface is down, the object
                                                // returns the most current value.
                                                // If the upstream channel ID is unknown,
                                                // this object returns a value of 0.
    unsigned int T3Timeouts;                    // Number of T3 counter timeouts.
    unsigned int T4Timeouts;                    // Number of T4 counter timeouts.
    unsigned int RangingAborteds;               // Number of times ranging process
                                                // has been aborted.
    unsigned int T3Exceededs;                   // Number of excessive T3 timeouts.
    unsigned char IsMuted;                      // Indicates if upstream channel is muted.
    unsigned int RangingStatus;                 // Ranging State of CM:
                                                // other(1),aborted(2),retriesExceeded(3),
                                                // success(4),continue(5),timeoutT4(6)
} DOCSIF31_CMSTATUSOFDMA_US, *PDOCSIF31_CMSTATUSOFDMA_US;
//<< Docsis3.1

#define MAX_KICKSTART_ROWS 5

typedef struct _fixed_length_buffer {
    USHORT length;
    UINT8 *buffer;
} fixed_length_buffer_t;

typedef struct _snmpv3_kickstart_row {
    fixed_length_buffer_t security_name;
    fixed_length_buffer_t security_number;
} snmp_kickstart_row_t;

typedef struct _snmpv3_kickstart_table {
    UINT8 n_rows;
    snmp_kickstart_row_t *kickstart_values[MAX_KICKSTART_ROWS];
} snmpv3_kickstart_table_t;

/** @} */  //END OF GROUP CM_HAL_TYPES


/**********************************************************************************
 *
 *  CM Subsystem level function prototypes 
 *
**********************************************************************************/

/**
 * @addtogroup CM_HAL_APIS
 * @{
 */

/* cm_hal_InitDB :  */
/**
* @description Retrieves the global information for all shared DBs and makes them accessible locally.
* @param None
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT cm_hal_InitDB(void);

/* docsis_InitDS :  */
/**
* @description Init global PHY level info and DBs and get direct access to DS HW.
* @param None
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT docsis_InitDS(void);

/* docsis_InitUS :  */
/**
* @description Init global PHY level info and DBs and get direct access to US HW.
* @param None
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT docsis_InitUS(void);

/*  docsis_getCMStatus : */
/**
* @description Retrieve, format and output the Cable Modem DOCSIS status.
* @param CHAR* cm_status - status string, to be returned
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT docsis_getCMStatus(CHAR *cm_status);

/*  docsis_GetDSChannel : */
/**
* @description Retrieve all the relevant DS channel info from global DBs.
* @param PCMMGMT_CM_DS_CHANNEL * ppinfo - all info of DS channel, to be returned
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT docsis_GetDSChannel(PCMMGMT_CM_DS_CHANNEL * ppinfo);

/*  docsis_GetUsStatus : */
/**
* @description Retrieve all the relevant US channel info from global DBs.
* @param USHORT i - index to the US channel
* @param PCMMGMT_CM_US_CHANNEL pinfo - info of one US channel, to be returned
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT docsis_GetUsStatus(USHORT i, PCMMGMT_CM_US_CHANNEL pinfo);

/*  docsis_GetUSChannel : */
/**
* @description Retrieve particular US channel information from global DBs.
* @param PCMMGMT_CM_US_CHANNEL * ppinfo - all info of US channel, to be returned
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT docsis_GetUSChannel(PCMMGMT_CM_US_CHANNEL * ppinfo);

/*  docsis_GetDOCSISInfo : */
/**
* @description Retrieve current DOCSIS registration status and report it.
* @param PCMMGMT_CM_DOCSIS_INFO pinfo - registration info, to be returned
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT docsis_GetDOCSISInfo(PCMMGMT_CM_DOCSIS_INFO pinfo);

/*  docsis_GetNumOfActiveTxChannels : */
/**
* @description Retrieve number of US channels actively in use in current registration.
* @param ULONG * cnt - pointer to number, to be returned
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT docsis_GetNumOfActiveTxChannels(ULONG * cnt);

/*  docsis_GetNumOfActiveRxChannels : */
/**
* @description Retrieve number of DS channels actively in use in current registration.
* @Param ULONG * cnt - pointer to number, to be returned
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT docsis_GetNumOfActiveRxChannels(ULONG * cnt);

/*  docsis_GetErrorCodewords : */
/**
* @description Scan all active DS channels and report errors in packets received.
* @param PCMMGMT_CM_ERROR_CODEWORDS * ppinfo - error info retrieved
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT docsis_GetErrorCodewords(PCMMGMT_CM_ERROR_CODEWORDS * ppinfo);

/*  docsis_GetMddIpModeOverride : */
/**
* @description Retrieve the current MIMO status.
* @param CHAR *pValue - status retrieved
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT docsis_GetMddIpModeOverride(CHAR *pValue);

/*  docsis_SetMddIpModeOverride : */
/**
* @description Set the current global MIMO status.
* @param CHAR *pValue - status to be set to
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT docsis_SetMddIpModeOverride(CHAR *pValue);

/*  docsis_GetUSChannelId : */
/**
* @description Retrieve the US channel ID in its MAC domain.
* @param none
*
* @return UINT8 - Channel ID
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
UINT8 docsis_GetUSChannelId(void);

/*  docsis_SetUSChannelId : */
/**
* @description Set the US channel ID in its MAC domain.
* @param INT index = Index to set the Upstream Channel ID to
*
* @return None
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
void docsis_SetUSChannelId(INT index);

/*  docsis_GetDownFreq : */
/**
* @description Retrieve the current primary channel DS channel frequency from the LKF table.
* @param None
*
* @return ULONG - channel frequency
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
ULONG docsis_GetDownFreq(void);

/*  docsis_SetStartFreq : */
/**
* @description Change the DS primary channel frequency in the LKF table.
* @param ULONG value - frequency to get set to 
*
* @return None
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
void docsis_SetStartFreq(ULONG value);

/*  docsis_GetDownFreq : */
/**
* @description Retrieve the DOCSIS event log entries and display it.
* @param CMMGMT_CM_EventLogEntry_t *entryArray - entries to be returned
* @param INT len - length of log entries
*
* @return INT - number of log entries retrieved
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT docsis_GetDocsisEventLogItems(CMMGMT_CM_EventLogEntry_t *entryArray, INT len);

/*  docsis_ClearDocsisEventLog : */
/**
* @description Clear the DOCSIS event log.
* @param None
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT docsis_ClearDocsisEventLog(void);

/*  cm_hal_GetDHCPInfo : */
/**
* @description Retrieve all the relevant DHCP info for this CM.
* @param PCMMGMT_CM_DHCP_INFO pInfo - all DHCP info for CM, to be returned
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT cm_hal_GetDHCPInfo(PCMMGMT_CM_DHCP_INFO pInfo);

/*  cm_hal_GetIPv6DHCPInfo : */
/**
* @description Retrieve all the relevant IPv6 DHCP info for this CM.
* @param PCMMGMT_CM_IPV6DHCP_INFO pInfo - all IPv6 DHCP info for CM, to be returned
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT cm_hal_GetIPv6DHCPInfo(PCMMGMT_CM_IPV6DHCP_INFO pInfo);

/*  cm_hal_GetCPEList : */
/**
* @description Retrieve list of CPEs connected to the CM
* @param PCMMGMT_DML_CPE_LIST * ppCPEList - List of all CPE, to be returned
* @param ULONG* InstnaceNum - Number of instances, to be returned
* @param CHAR* LanMode - input of "router" or "bridge" mode of the modem
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT cm_hal_GetCPEList(PCMMGMT_DML_CPE_LIST * ppCPEList, ULONG* InstanceNum, CHAR* LanMode);

/*  cm_hal_GetMarket : */
/**
* @description Retrieve the market of this modem
* @param CHAR* market - Name of the market for this modem, "US" or "EURO", to be returned 
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT cm_hal_GetMarket(CHAR* market);

/* HTTP Download HAL API Prototype */

/* cm_hal_Set_HTTP_DL_Url  - 1 */

/**
* @description Set Http Download Settings
* @param char* pHttpUrl
* @param char* pfilename
*
* @return the status of the operation
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any Downloading is in process or Url string is invalided.
*/
INT cm_hal_Set_HTTP_Download_Url (char* pHttpUrl, char* pfilename);

/* cm_hal_Get_HTTP_Download_Url: */

/**
* @description Get Http Download Url
* @param char* pHttpUrl
* @param char* pfilename
* @return the status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if http url string is empty.
*/
INT cm_hal_Get_HTTP_Download_Url (char *pHttpUrl, char* pfilename);

/* cm_hal_Set_HTTP_Download_Interface: */
/**
* @description Set the HTTP Download Interface
* @param unsigned int interface - interface=0 for wan0, interface=1 for erouter0
* @return the status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*/
/* interface=0 for wan0, interface=1 for erouter0 */
INT cm_hal_Set_HTTP_Download_Interface(unsigned int interface);

/* cm_hal_Get_HTTP_Download_Interface: */
/**
* @description Get the HTTP Download Interface
* @param unsigned int* pinterface - interface=0 for wan0, interface=1 for erouter0
* @return the status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*/
/* interface=0 for wan0, interface=1 for erouter0 */
INT cm_hal_Get_HTTP_Download_Interface(unsigned int* pinterface);

/* cm_hal_HTTP_Download - 3 */
/**
* @description Start Http Download
* @param <None>
* @return the status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any Downloading is in process.
*
* @execution Synchronous.
* @sideeffect None.
* 
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*/
INT cm_hal_HTTP_Download ();

/* cm_hal_ Get_HTTP_Download _Status ? 4 */
/**
* @description Get the HTTP Download Status
* @param <None>
* @return the status of the HTTP Download.
* @retval 0 -   Download is not started.
* @retval 0-100 - Values of percent of download.
* @retval 200 - Download is completed and waiting for reboot.
* @retval 400 - Invalided Http server Url
* @retval 401 - Cannot connect to Http server
* @retval 402 - File is not found on Http server
* @retval 403 - HW_Type_DL_Protection Failure
* @retval 404 - HW Mask DL Protection Failure
* @retval 405 - DL Rev Protection Failure
* @retval 406 - DL Header Protection Failure
* @retval 407 - DL CVC Failure
* @retval 500 - General Download Failure
* 	
*/
INT cm_hal_Get_HTTP_Download_Status();

/* cm_hal_Reboot_Ready - 5 */
/**
* @description Get the Reboot Ready Status
* @param ULONG *pValue- Values of 1 for Ready, 2 for Not Ready
* @return the status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*/
INT cm_hal_Reboot_Ready(ULONG *pValue);

/* cm_hal_HTTP_DL_Reboot_Now - 6*/
/**
* @description Http Download Reboot Now
* @param <None>
* @return the status of the reboot operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any reboot is in process.
*/
INT cm_hal_HTTP_Download_Reboot_Now();

/* cm_hal_FWupdateAndFactoryReset : */
/**
* @description: Firmware update and factory reset the device
* @param char* pUrl - NULL for snmp
* @param char* pImagename - NULL for snmp
* @return the status of the Firmware update and factory reset operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any reboot is in process.
*/
INT cm_hal_FWupdateAndFactoryReset(char* pUrl, char* pImagename);

/*  cm_hal_ReinitMac : */
/**
* @description Reinit CM.  Performs reinit MAC only to same DS/US
* @param None
*

* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*

*/
INT cm_hal_ReinitMac();

/*  docsis_GetProvIpType : */
/**
* @description Retrieve the provisioned wan0 IP type
* @param CHAR* pValue - ip type currently provisioned on wan0
* values are "IPv4", "IPv6", or "unknown"
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT docsis_GetProvIpType(CHAR *pValue); 

/*  docsis_GetCert : */
/**
* @description Retrieve the location of the certificate
* @param CHAR* pCert - certificate location, to be returned
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT docsis_GetCert(CHAR* pCert);

/*  docsis_GetCertStatus : */
/**
* @description Retrieve status of the certificate 
* @param ULONG *pVal - certificate status, to be returned
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT docsis_GetCertStatus(ULONG *pVal);


/*  cm_hal_Get_CableModemResetCount : */
/**
* @description Retrieve the count of cable modem reset
* @param ULONG *resetcnt - Count to be returned
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.

*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT cm_hal_Get_CableModemResetCount(ULONG *resetcnt);

/*  cm_hal_Get_LocalResetCount : */
/**
* @description Retrieve the count of local reset
* @param ULONG *resetcnt - Count to be returned
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/

INT cm_hal_Get_LocalResetCount(ULONG *resetcnt);

/*  cm_hal_Get_DocsisResetCount : */
/**
* @description Retrieve the count of docsis reset
* @param ULONG *resetcnt - Count to be returned
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/

INT cm_hal_Get_DocsisResetCount(ULONG *resetcnt);

/*  cm_hal_Get_ErouterResetCount : */
/**
* @description Retrieve the count of erouter reset
* @param ULONG *resetcnt - Count to be returned
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/

INT cm_hal_Get_ErouterResetCount(ULONG *resetcnt);

/*  cm_hal_HTTP_LED_Flash : */
/**
*@description Enable/Disable HTTP LED Flashing
* @param BOOLEAN *bLEDFlashState - Enable/Disable LED Flash
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/

INT cm_hal_HTTP_LED_Flash( BOOLEAN LedFlash );

//>> Docsis3.1
/*  docsis_GetDsOfdmChanTable : */
/**
*@description Get the Downstream DSOF channel table (docsIf31CmDsOfdmChanTable)
* @param PDOCSIF31_CM_DS_OFDM_CHAN *ppinfo - Ponter to get the return array
* @param int *output_NumberOfEntries - Array size need to be return with output_NumberOfEntries
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
* @note HAL function need to allocate the array of DOCSIF31_CM_DS_OFDM_CHAN and return with ppinfo.
*
*/
INT docsis_GetDsOfdmChanTable(PDOCSIF31_CM_DS_OFDM_CHAN *ppinfo, int *output_NumberOfEntries);

/*  docsis_GetUsOfdmaChanTable : */
/**
*@description Get the Upstream DSOFA channel table (docsIf31CmUsOfdmaChanTables)
* @param PDOCSIF31_CM_US_OFDMA_CHAN *ppinfo - Ponter to get the return array
* @param int *output_NumberOfEntries - Array size need to be return with output_NumberOfEntries
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
* @note HAL function need to allocate the array of DOCSIF31_CM_US_OFDMA_CHAN and return with ppinfo.
*
*/
INT docsis_GetUsOfdmaChanTable(PDOCSIF31_CM_US_OFDMA_CHAN *ppinfo, int *output_NumberOfEntries);

/*  docsis_GetStatusOfdmaUsTable : */
/**
*@description Get the Upstream DSOFA channel status table (docsIf31CmStatusOfdmaUsTable)
* @param PDOCSIF31_CMSTATUSOFDMA_US *ppinfo - Ponter to get the return array
* @param int *output_NumberOfEntries - Array size need to be return with output_NumberOfEntries
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
* @note HAL function need to allocate the array of DOCSIF31_CMSTATUSOFDMA_US and return with ppinfo.
*
*/
INT docsis_GetStatusOfdmaUsTable(PDOCSIF31_CMSTATUSOFDMA_US *ppinfo, int *output_NumberOfEntries);
//<< Docsis3.1

/*  cm_hal_snmpv3_kickstart_initialize: */
/**
* @description Configure the SNMPv3 security parameters on the CM.
* @param snmpv3_kickstart_table_t * pKickstart_Table - a pointer to the SNMPv3 kickstart table
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*
*/
INT cm_hal_snmpv3_kickstart_initialize(snmpv3_kickstart_table_t *pKickstart_Table);
/** @} */  //END OF GROUP CM_HAL_APIS


/*  docsis_IsEnergyDetected: */
/**
* @description Get the docsis energy to detect WAN mode.
* @param BOOLEAN *pEnergyDetected , 0 for No Docsis, 1 if DOCSIS is connected
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*
*/

INT docsis_IsEnergyDetected( BOOLEAN *pEnergyDetected );


/*  cm_hal_set_ReinitMacThreshold: */
/**
* @description Set ReinitMacThreshold value.
* @param ULONG value , value to be set
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
INT cm_hal_set_ReinitMacThreshold(ULONG value);

/*  cm_hal_get_ReinitMacThreshold: */
/**
* @description Get ReinitMacThreshold value.
* @param ULONG* pValue , value to be returned
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
INT cm_hal_get_ReinitMacThreshold(ULONG *pValue);

#ifdef __cplusplus
}
#endif

#endif
 
