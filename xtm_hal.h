/*========================================================================================
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
*===========================================================================================*/

#ifndef __XTM_HAL_H__
#define __XTM_HAL_H__

#ifndef ULLONG
#define ULLONG unsigned long long
#endif

#ifndef ULONG
#define ULONG unsigned long
#endif

#ifndef USHORT
#define USHORT unsigned short
#endif

#ifndef BOOL
#define BOOL unsigned char
#endif

#ifndef CHAR
#define CHAR char
#endif

#ifndef UCHAR
#define UCHAR unsigned char
#endif

#ifndef INT
#define INT int
#endif

#ifndef UINT
#define UINT unsigned int
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef ENABLE
#define ENABLE 1
#endif

#ifndef RETURN_OK
#define RETURN_OK 0
#endif

#ifndef RETURN_ERR
#define RETURN_ERR -1
#endif

/**
 * @brief enum to identify the XTM link type.
 * It could be either ATM, PTM or Not Supported.
 */
typedef enum _XTM_LINK_TYPE
{
    PTM_LINK = 0,
    ATM_LINK,
    NOT_SUPPORTED
} XTM_LINK_TYPE, *PXTM_LINK_TYPE;

/**
 * Enum to store the link status information.
 */
typedef enum _XTM_LINK_STATUS
{
    XTM_LINK_TRAINING = 0,
    XTM_LINK_UP,
    XTM_LINK_DOWN,
    XTM_LINK_DORMANT,
    XTM_LINK_NOT_PRESENT,
    XTM_LINK_LOWER_LAYER_DOWN,
    XTM_LINK_UNKNOWN,
    XTM_LINK_ERROR,
} XTM_LINK_STATUS, *PXTM_LINK_STATUS;

/**
 * Struture used to hold the XTM (PTM/ATM) line Statistics
 * information.
 */
typedef struct _XTM_LINK_STATS
{
    ULONG BytesSent;
    ULONG BytesReceived;
    ULONG PacketsSent;
    ULONG PacketsReceived;
    UINT ErrorsSent;
    UINT ErrorsReceived;
    ULONG UnicastPacketsSent;
    ULONG UnicastPacketsReceived;
    UINT DiscardPacketsSent;
    UINT DiscardPacketsReceived;
    ULONG MulticastPacketsSent;
    ULONG MulticastPacketsReceived;
    ULONG BroadcastPacketsSent;
    ULONG BroadcastPacketsReceived;
    UINT UnknownProtoPacketsReceived;
    UINT Atm_TransmittedBlocks;
    UINT Atm_ReceivedBlocks;
    UINT Atm_CRCErrors;
    UINT Atm_HECErrors;
} XTM_LINK_STATS, *PXTM_LINK_STATS;

/* xtm_hal_init() function */
/**
* @brief - Initialise the xtm features
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
*/
INT xtm_hal_init();

/* xtm_hal_setLinkEnable() function */
/**
* @brief - Enable/Disable XTM link interface. This bringup the XTM interface up.
*
* @param Type of XTM link type. Could be ATM or PTM
* @param XTM link line index
* @param Enable/Disable flag
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*/
INT xtm_hal_setLinkEnable(XTM_LINK_TYPE type, UINT lineIndex, BOOL enable);

/* xtm_hal_getLinkEnable() function */
/**
* @brief - Get XTM link interface enabled or not.
*
* @param Type of XTM link type. Could be ATM or PTM
* @param Flag to store enable/disable status
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*/
INT xtm_hal_getLinkEnable(XTM_LINK_TYPE type, BOOL* enable);


/* xtm_hal_getLinkStats() function */
/**
* @brief - Get XTM link statistics information
*
* @param Type of XTM link type. Could be ATM or PTM
* @param Structure pointer to hold statistics information
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*/
INT xtm_hal_getLinkStats(XTM_LINK_TYPE type, UINT lineIndex, PXTM_LINK_STATS linkStats);

/* xtm_hal_getLinkName() function */
/**
* @brief - Get XTM (ATM/PTM) link interface name
*
* @param Type of XTM link type. Could be ATM or PTM
* @param XTM link line index
* @param String to hold XTM link interface name
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*/
INT xtm_hal_getLinkName(XTM_LINK_TYPE type, UINT lineIndex, CHAR *ifName);

/* xtm_hal_getLinkMacAddress() function */
/**
* @brief - Get XTM (ATM/PTM) link interface mac address.
*
* @param Type of XTM link type. Could be ATM or PTM
* @param XTM link line index
* @param String to hold XTM link interface Mac address
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
*/
INT xtm_hal_getLinkMacAddress(XTM_LINK_TYPE type, UINT lineIndex, CHAR *macAddr);

/* xtm_hal_getLinkStatus() function */
/**
* @brief - Get XTM (ATM/PTM) interface link status.
*
* @param Type of XTM link type. Could be ATM or PTM
* @param XTM link line index
* @param Enum object to hold the link status
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*/
INT xtm_hal_getLinkStatus(XTM_LINK_TYPE type, UINT lineIndex, PXTM_LINK_STATUS linkStatus);

/* xtm_hal_getLinkNumberOfEntries () function */
/**
* @brief - Get total number of XTM (ATM/PTM) link entries.
*
* @param Type of XTM link type. Could be ATM or PTM
* @param Unsigned integer to store the total number of XTM line entries
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*/
INT xtm_hal_getLinkNumberOfEntries(XTM_LINK_TYPE type, UINT *lineCount);

/* xtm_hal_getLinkLastChange() function */
/**
* @brief - Get XTM (ATM/PTM) link interface last configured time stamp.
*
* @param Type of XTM link type. Could be ATM or PTM
* @param PTM line index number
* @param String to hold the last XTM interface configured time.
*
* @return The status of the operation
* @return The status of the operation
* @retval Return last timestamp value
*/
INT xtm_hal_getLinkLastChange(XTM_LINK_TYPE type, UINT lineIndex, UINT *timestamp);
#endif
