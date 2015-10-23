/*
 * If not stated otherwise in this file or this component's Licenses.txt file the
 * following copyright and licenses apply:
 *
 * Copyright 2015 RDK Management
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

#ifndef LONG
#define LONG   long
#endif

#ifndef UINT
#define UINT  unsigned int
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
* Description: Retrieves the global information for all shared DBs and makes them accessible locally.
* Parameters : None
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
INT cm_hal_InitDB(void);

/* docsis_InitDS :  */
/**
* Description: Init global PHY level info and DBs and get direct access to DS HW.
* Parameters : None
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
INT docsis_InitDS(void);

/* docsis_InitUS :  */
/**
* Description: Init global PHY level info and DBs and get direct access to US HW.
* Parameters : None
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
INT docsis_InitUS(void);

/*  docsis_getCMStatus : */
/**
* Description: Retrieve, format and output the Cable Modem DOCSIS status.
* Parameters : 
*     CHAR* cm_status - status string, to be returned
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
INT docsis_getCMStatus(CHAR *cm_status);

/*  docsis_GetDSChannel : */
/**
* Description: Retrieve all the relevant DS channel info from global DBs.
* Parameters : 
*     PCMMGMT_CM_DS_CHANNEL * ppinfo - all info of DS channel, to be returned
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
INT docsis_GetDSChannel(PCMMGMT_CM_DS_CHANNEL * ppinfo);

/*  docsis_GetUsStatus : */
/**
* Description: Retrieve all the relevant US channel info from global DBs.
* Parameters : 
*    USHORT i - index to the US channel
*    PCMMGMT_CM_US_CHANNEL pinfo - info of one US channel, to be returned
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
INT docsis_GetUsStatus(USHORT i, PCMMGMT_CM_US_CHANNEL pinfo);

/*  docsis_GetUSChannel : */
/**
* Description:  Retrieve particular US channel information from global DBs.
* Parameters : 
*     PCMMGMT_CM_US_CHANNEL * ppinfo - all info of US channel, to be returned
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
INT docsis_GetUSChannel(PCMMGMT_CM_US_CHANNEL * ppinfo);

/*  docsis_GetDOCSISInfo : */
/**
* Description:  Retrieve current DOCSIS registration status and report it.
* Parameters : 
*     PCMMGMT_CM_DOCSIS_INFO pinfo - registration info, to be returned
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
INT docsis_GetDOCSISInfo(PCMMGMT_CM_DOCSIS_INFO pinfo);

/*  docsis_GetNumOfActiveTxChannels : */
/**
* Description: Retrieve number of US channels actively in use in current registration.
* Parameters : 
*     ULONG * cnt - pointer to number, to be returned
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
INT docsis_GetNumOfActiveTxChannels(ULONG * cnt);

/*  docsis_GetNumOfActiveRxChannels : */
/**
* Description: Retrieve number of DS channels actively in use in current registration.
* Parameters : 
*     ULONG * cnt - pointer to number, to be returned
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
INT docsis_GetNumOfActiveRxChannels(ULONG * cnt);

/*  docsis_GetErrorCodewords : */
/**
* Description: Scan all active DS channels and report errors in packets received.
* Parameters : 
*     PCMMGMT_CM_ERROR_CODEWORDS * ppinfo - error info retrieved
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
INT docsis_GetErrorCodewords(PCMMGMT_CM_ERROR_CODEWORDS * ppinfo);

/*  docsis_GetMddIpModeOverride : */
/**
* Description: Retrieve the current MIMO status.
* Parameters : 
*     CHAR *pValue - status retrieved
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
INT docsis_GetMddIpModeOverride(CHAR *pValue);

/*  docsis_SetMddIpModeOverride : */
/**
* Description: Set the current global MIMO status.
* Parameters : 
*     CHAR *pValue - status to be set to
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
INT docsis_SetMddIpModeOverride(CHAR *pValue);

/*  docsis_GetUSChannelId : */
/**
* Description: Retrieve the US channel ID in its MAC domain.
* Parameters : none
*
* @return UINT8 - Channel ID
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system�
* calls. It should probably just send a message to a driver event handler task.�
*
*/
UINT8 docsis_GetUSChannelId(void);

/*  docsis_SetUSChannelId : */
/**
* Description: Set the US channel ID in its MAC domain.
* Parameters : 
*    INT index = Index to set the Upstream Channel ID to
*
* @return None
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system�
* calls. It should probably just send a message to a driver event handler task.�
*
*/
void docsis_SetUSChannelId(INT index);

/*  docsis_GetDownFreq : */
/**
* Description: Retrieve the current primary channel DS channel frequency from the LKF table.
* Parameters : None
*
* @return ULONG - channel frequency
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system�
* calls. It should probably just send a message to a driver event handler task.�
*
*/
ULONG docsis_GetDownFreq(void);

/*  docsis_SetStartFreq : */
/**
* Description: Change the DS primary channel frequency in the LKF table.
* Parameters : 
*     ULONG value - frequency to get set to 
*
* @return None
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system�
* calls. It should probably just send a message to a driver event handler task.�
*
*/
void docsis_SetStartFreq(ULONG value);

/*  docsis_GetDownFreq : */
/**
* Description: Retrieve the DOCSIS event log entries and display it.
* Parameters : 
*    CMMGMT_CM_EventLogEntry_t *entryArray - entries to be returned
*    INT len - length of log entries
*
* @return INT - number of log entries retrieved
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system�
* calls. It should probably just send a message to a driver event handler task.�
*
*/
INT docsis_GetDocsisEventLogItems(CMMGMT_CM_EventLogEntry_t *entryArray, INT len);

/*  docsis_ClearDocsisEventLog : */
/**
* Description: Clear the DOCSIS event log.
* Parameters : None
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
INT docsis_ClearDocsisEventLog(void);

/*  cm_hal_GetDHCPInfo : */
/**
* Description: Retrieve all the relevant DHCP info for this CM.
* Parameters : 
*     PCMMGMT_CM_DHCP_INFO pInfo - all DHCP info for CM, to be returned
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
INT cm_hal_GetDHCPInfo(PCMMGMT_CM_DHCP_INFO pInfo);

/*  cm_hal_GetIPv6DHCPInfo : */
/**
* Description: Retrieve all the relevant IPv6 DHCP info for this CM.
* Parameters : 
*     PCMMGMT_CM_IPV6DHCP_INFO pInfo - all IPv6 DHCP info for CM, to be returned
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
INT cm_hal_GetIPv6DHCPInfo(PCMMGMT_CM_IPV6DHCP_INFO pInfo);

/*  cm_hal_GetCPEList : */
/**
* Description: Retrieve list of CPEs connected to the CM
* Parameters : 
*     PCMMGMT_DML_CPE_LIST * ppCPEList - List of all CPE, to be returned
*     ULONG* InstnaceNum - Number of instances, to be returned
*     CHAR* LanMode - input of "router" or "bridge" mode of the modem
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
INT cm_hal_GetCPEList(PCMMGMT_DML_CPE_LIST * ppCPEList, ULONG* InstanceNum, CHAR* LanMode);

/*  cm_hal_GetMarket : */
/**
* Description: Retrieve the market of this modem
* Parameters : 
*     CHAR* market - Name of the market for this modem, "US" or "EURO", to be returned 
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
INT cm_hal_GetMarket(CHAR* market);
/* HTTP Download HAL API Prototype */

/* cm_hal_Set_HTTP_DL_Url  - 1 */

/* Description: Set Http Download Settings
Parameters : char* pHttpUrl;
Parameters : char* pfilename;

@return the status of the operation
@retval RETURN_OK if successful.
@retval RETURN_ERR if any Downloading is in process or Url string is invalided.
*/
INT cm_hal_Set_HTTP_Download_Url (char* pHttpUrl, char* pfilename);

/* cm_hal_Get_HTTP_Download_Url: */

/* Description: Get Http Download Url
Parameters : char* pHttpUrl
Parameters : char* pfilename;
@return the status of the operation.
@retval RETURN_OK if successful.
@retval RETURN_ERR if http url string is empty.
*/
INT cm_hal_Get_HTTP_Download_Url (char *pHttpUrl, char* pfilename);

/* interface=0 for wan0, interface=1 for erouter0 */
INT cm_hal_Set_HTTP_Download_Interface(unsigned int interface);

/* interface=0 for wan0, interface=1 for erouter0 */
INT cm_hal_Get_HTTP_Download_Interface(unsigned int* pinterface);

/* cm_hal_HTTP_Download - 3 */
/**
Description: Start Http Download
Parameters: <None>
@return the status of the operation.
@retval RETURN_OK if successful.
@retval RETURN_ERR if any Downloading is in process.

*/
INT cm_hal_HTTP_Download ();

/* cm_hal_ Get_HTTP_Download _Status ? 4 */
/**
Description: Get the HTTP Download Status
Parameters : <None>
@return the status of the HTTP Download.
?	0 ? Download is not started.
?	Number between 0 to 100: Values of percent of download.
?	200 ? Download is completed and waiting for reboot.
?	400 -  Invalided Http server Url
?	401 -  Cannot connect to Http server
?	402 -  File is not found on Http server
?	403 -  HW_Type_DL_Protection Failure
?	404 -  HW Mask DL Protection Failure
?	405 -  DL Rev Protection Failure
?	406 -  DL Header Protection Failure
?	407 -  DL CVC Failure
?	500 -  General Download Failure
?	*/
INT cm_hal_Get_HTTP_Download_Status();

/* cm_hal_Reboot_Ready - 5 */
/*
Description: Get the Reboot Ready Status
Parameters:
ULONG *pValue- Values of 1 for Ready, 2 for Not Ready
@return the status of the operation.
@retval RETURN_OK if successful.
@retval RETURN_ERR if any error is detected

*/
INT cm_hal_Reboot_Ready(ULONG *pValue);

/* cm_hal_HTTP_DL_Reboot_Now - 6*/
/*
Description:  Http Download Reboot Now
Parameters : <None>
@return the status of the reboot operation.
@retval RETURN_OK if successful.
@retval RETURN_ERR if any reboot is in process.
*/
INT cm_hal_HTTP_Download_Reboot_Now();

/*  cm_hal_ReinitMac : */
/**
* Description: Reinit CM.  Performs reinit MAC only to same DS/US
* Parameters :
*     None
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
INT cm_hal_ReinitMac();

/*  docsis_GetProvIpType : */
/**
* Description: Retrieve the provisioned wan0 IP type
* Parameters :
*     CHAR* pValue - ip type currently provisioned on wan0
*           values are "IPv4", "IPv6", or "unknown"
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
INT docsis_GetProvIpType(CHAR *pValue);


/*  docsis_GetCert : */
/**
* Description: Retrieve the location of the certificate
* Parameters : 
*     CHAR* pCert - certificate location, to be returned
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
INT docsis_GetCert(CHAR* pCert);

/*  docsis_GetCertStatus : */
/**
* Description: Retrieve status of the certificate 
* Parameters : 
*    ULONG *pVal - certificate status, to be returned
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
INT docsis_GetCertStatus(ULONG *pVal);

/*  cm_hal_Get_CableModemResetCount : */
/**
* Description: Retrieve the count of cable modem reset
* Parameters :
*    ULONG *resetcnt - Count to be returned
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
INT cm_hal_Get_LocalResetCount(ULONG *resetcnt);

/*  cm_hal_Get_LocalResetCount : */
/**
* Description: Retrieve the count of local reset
* Parameters :
*    ULONG *resetcnt - Count to be returned
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

INT cm_hal_Get_LocalResetCount(ULONG *resetcnt);

/*  cm_hal_Get_DocsisResetCount : */
/**
* Description: Retrieve the count of docsis reset
* Parameters :
*    ULONG *resetcnt - Count to be returned
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

INT cm_hal_Get_DocsisResetCount(ULONG *resetcnt);

/*  cm_hal_Get_ErouterResetCount : */
/**
* Description: Retrieve the count of erouter reset
* Parameters :
*    ULONG *resetcnt - Count to be returned
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

INT cm_hal_Get_ErouterResetCount(ULONG *resetcnt);


#endif
 
