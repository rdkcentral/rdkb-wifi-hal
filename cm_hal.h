/**
* @file cm_hal.h
* @author cisco
* @brief For CCSP Component:  CcspCMAgent
*
*@description This header file gives the function call prototypes and 
structure definitions used for the RDK-Broadband 
hardware abstraction layer for Cable Modem 
*/

/*
 * If not stated otherwise in this file or this component's Licenses.txt file the
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

    copyright:

        Cisco Systems, Inc., 2014
        All Rights Reserved.

    ---------------------------------------------------------------

    description:

        This header file gives the function call prototypes and 
        structure definitions used for the RDK-Broadband 
        hardware abstraction layer for Cable Modem

        NOTE:
        THIS VERSION IS AN EARLY DRAFT INTENDED TO GET COMMENTS FROM COMCAST.
        TESTING HAS NOT YET BEEN COMPLETED.  
       
    ---------------------------------------------------------------

    environment:

        This HAL layer is intended to support cable modem drivers 
        through an open API.  
        Changes may be needed to support different hardware enviornments.

    ---------------------------------------------------------------

    author:

        Cisco

**********************************************************************/


#ifndef __CM_HAL_H__
#define __CM_HAL_H__

#include <sys/time.h>

/**********************************************************************
               CONSTANT DEFINITIONS
**********************************************************************/

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
/**********************************************************************************
 *
 *  CM Subsystem level function prototypes 
 *
**********************************************************************************/

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
* @note This function must not suspend and must not invoke any blocking system�
* calls. It should probably just send a message to a driver event handler task.�
*
*/

INT cm_hal_HTTP_LED_Flash( BOOLEAN LedFlash );
#endif
 
