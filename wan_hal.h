/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2019 RDK Management
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

#ifndef __WAN_HAL_H__
#define __WAN_HAL_H__

#include <stdint.h>

/**
 * @defgroup WAN_HAL WAN HAL
 *
 * @defgroup WAN_HAL_TYPES  WAN HAL Data Types
 * @ingroup  WAN_HAL
 *
 * @defgroup WAN_HAL_APIS   WAN HAL APIs
 * @ingroup  WAN_HAL
 *
 **/

/**
 * @addtogroup WAN_HAL_TYPES
 * @{
 */

#define RETURN_ERROR 1
#define RETURN_OK 0

#define BUFLEN_8 8
#define BUFLEN_32 32
#define BUFLEN_64 64

typedef enum
{
    WAN_MODE_DISABLED = 1,
    WAN_MODE_DSL_ONLY = 2,
    WAN_MODE_ETH_ONLY = 3,
    WAN_MODE_AUTO = 4
} t_eWanMode;

typedef struct 
_WAN_IPV4_CFG 
{
    char ifname[64];         // interface name (erouter0)
    char subnetmask[64];     // subnet mask
    char ipaddress[64];      // ip address to assign (192.168.0.1)
    char dnsservers[256];    // new-line separated list of servers to be added
    char defaultgateway[64]; // default gateway address

} WAN_IPV4_CFG, *PWAN_IPV4_CFG;

typedef struct
_WAN_IPV6_CFG
{
    char ifname[64];         // interface name (erouter0)
    char ipaddress[128];      // ip address to assign 
    char dnsservers[512];    // new-line separated list of servers to be added
    int  preferredlifetime;  
    int  validlifetime;

} WAN_IPV6_CFG, *PWAN_IPV6_CFG;

/*
 * The WAN_QOS_QUEUE structure needed in ccsp-wanagent and wan-hal
  */
typedef  struct
_WAN_QOS_QUEUE
{
    unsigned long       InstanceNumber;
    char                Alias[64];
    unsigned long       queueKey;
    unsigned char       queueEnable;
    char                queueStatus[256];
    char                queueInterface[256];
    unsigned long       queueWeight;
    unsigned long       queuePrecedence;
    unsigned long       REDThreshold;
    char                dropAlgorithm[256];
    char                schedulerAlgorithm[256];
    signed long         shapingRate;
    unsigned long       shapingBurstSize;
    signed long         MinBitRate;
    char                QueueName[256];
    signed long         DslLatency;
    signed long         PtmPriority;
    unsigned long       QueueId;
    unsigned long       LowClassMaxThreshold;
    unsigned long       LowClassMinThreshold;
    unsigned long       HighClassMinThreshold;
    unsigned long       HighClassMaxThreshold;
    char                L2DeviceType[32];

}WAN_QOS_QUEUE,  *PWAN_QOS_QUEUE;

/* * MAPT */
typedef  struct
_WAN_MAPT_CFG
{
    char          ifName[64];
    char          brIPv6Prefix[128];
    char          ruleIPv4Prefix[128];
    char          ruleIPv6Prefix[128];
    unsigned int  psidOffset;
    unsigned int  ratio;
    char          pdIPv6Prefix[128];

} WAN_MAPT_CFG, *PWAN_MAPT_CFG;

/**
 * Structure for SELFHEAL configuration which is required in ccsp-wanagent
 * and wan hal. */
typedef struct
_SELFHEAL_CONFIG
{
    unsigned int rebootStatus;
}
SELFHEAL_CONFIG, *PSELFHEAL_CONFIG;

/** @} */  //END OF GROUP WAN_HAL_TYPES

/**
 * @addtogroup WAN_HAL_APIS
 * @{
 */

/* wan_hal_Init() function */
/**
* @description - Initialise the wan features
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
*/
int wan_hal_Init();

/* wan_hal_SetWanmode() function */
/**
* @description Set wanmode value
*
* @param pValue - the WANMODE value to be set
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
*/
int wan_hal_SetWanmode(t_eWanMode mode);

/* wan_hal_SetWanConnectionEnable() function */
/**
* @description Set wanconnection enable value
*
* @param pValue - the WanConnectionEnable value to be set
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
*/
int wan_hal_SetWanConnectionEnable(unsigned int enable);
/**
* @description Set SelfHeal Configuration to wanmanager
*
* @param pSelfHealConfig - Ptr to struct contains the configuration
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
*/
int wan_hal_SetSelfHealConfig(PSELFHEAL_CONFIG pSelfHealConfig);

/* wanmgr_hal_GetWanOEUpstreamCurrRate() function */
/**
* @description Get the current payload bandwidth of the upstream WANoE Connection
*
* @param pValue - Pointer field where the current payload bandwidth to be updated
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
*/
int wan_hal_GetWanOEUpstreamCurrRate(unsigned int *pValue);

/* wanmgr_hal_GetWanOEDownstreamCurrRate() function */
/**
* @description Get the current payload bandwidth of the downstream WANoE Connection
*
* @param pValue - Pointer field where the current payload bandwidth to be updated
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
*/
int wan_hal_GetWanOEDownstreamCurrRate(unsigned int *pValue);

/* wan_hal_SetQosConfiguration() function */
/**
* @description Sets the current QoS configuration
*
* @param queueInfo - QoS configurations to be set
* @param QueueNumberOfEntries - The number of QoS profiles
* @param baseifname - Base interface name
* @param wanifname - Wan interface name
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
*/
int wan_hal_SetQoSConfiguration(PWAN_QOS_QUEUE pQueue, unsigned int QueueNumberOfEntries, const char* baseifname, const char* wanifname);

/* wan_hal_restart_wan_service() function */
/**
* @description Sets the current QoS configuration
*
* @param queueInfo - QoS configurations to be set
* @param QueueNumberOfEntries - The number of QoS profiles
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
*/ 
int wan_hal_RestartWanService(void);

/* wan_hal_ConfigureIpv4() function */
/**
* @description configure IPv4 dnsservers, netmask and ip address for the required interface
*
* @param pWanIpv4Cfg     - fill needed WAN_IPV4_CFG information 
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
*/
int wan_hal_ConfigureIpv4(PWAN_IPV4_CFG pWanIpv4Cfg);

/* wan_hal_UnConfigureIpv4() function */
/**
* @description unconfigure IPv4 dnsservers, netmask and ip address for the required interface
*
* @param pWanIpv4Cfg     - fill needed WAN_IPV4_CFG information    
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
*/
int wan_hal_UnConfigureIpv4(PWAN_IPV4_CFG pWanIpv4Cfg);

/* wan_hal_ConfigureIpv6() function */
/**
* @description Add IPv6 address for the required interface
*
* @param pWanIpv6Cfg     - fill needed WAN_IPV6_CFG information
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
*/
int wan_hal_ConfigureIpv6(PWAN_IPV6_CFG pWanIpv6Cfg);

/* wan_hal_UnConfigureIpv4() function */
/**
* @description Delete IPv6 address for the required interface
*
* @param pWanIpv6Cfg     - fill needed WAN_IPV6_CFG information
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
*/
int wan_hal_UnConfigureIpv6(PWAN_IPV6_CFG pWanIpv6Cfg);

/* wan_hal_EnableMapt() function */
/**
* @description Enable MAPT for the required interface
*
* @param pMAPTCfg             - Needs to fill PWAN_MAPT_CFG params
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
*/
int wan_hal_EnableMapt( PWAN_MAPT_CFG pMAPTCfg );

/* wan_hal_DisableMapt() function */
/**
* @description Disable MAPT for the required interface
*
* @param ifName               - interface name
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
*/
int wan_hal_DisableMapt(const char* ifName);

/**
 * @description Set/Reset WanOE mode based on the enable flag. If it is
 * true, update the boardparam to set WAN_ETH_MODE in the CPE. Else disabled
 * the WAN_ETH_MODE and reclaim ethernet port.
 * @param enable flag indicates to enable or disable ETH_WAN mode in CPE.
 */
int wan_hal_enableWanOEMode(const unsigned char enable);

/**
 * @description Get authentication information like ADSL username and password.
 * @param autInfo to hold the authentication data
 * @retval RETURN_OK if successful else RETURN_ERR
 */
int wan_hal_getAuthInfo(char *authInfo);

/** @} */  //END OF GROUP WAN_HAL_APIS
#endif /* __WAN_HAL_H__ */
