#ifndef __WAN_HAL_H__
#define __WAN_HAL_H__

#include <stdint.h>

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
    unsigned long       HighClassMinThreshold;
    unsigned long       HighClassMaxThreshold;
    char                L2DeviceType[32];
}
WAN_QOS_QUEUE,  *PWAN_QOS_QUEUE;

/**
 * Structure for SELFHEAL configuration which is required in ccsp-wanagent
 * and wan hal. */
typedef struct
_SELFHEAL_CONFIG
{
    unsigned int rebootStatus;
}
SELFHEAL_CONFIG, *PSELFHEAL_CONFIG;

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
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
*/
int wan_hal_SetQoSConfiguration(PWAN_QOS_QUEUE pQueue, unsigned int QueueNumberOfEntries);

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

#endif /* __WAN_HAL_H__ */
