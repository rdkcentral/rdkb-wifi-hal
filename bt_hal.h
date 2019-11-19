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

#ifndef __BT_HAL_H__
#define __BT_HAL_H__

/**
* @defgroup bt_hal Bluetooth HAL
*
* @defgroup BLUETOOTH_HAL_TYPES  Bluetooth HAL Data Types
* @ingroup  bt_hal
*
* @defgroup BLUETOOTH_HAL_APIS   Bluetooth HAL  APIs
* @ingroup  bt_hal
*
**/


/**
 * @addtogroup BLUETOOTH_HAL_TYPES
 * @{
 */

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
#define LONG    long
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

typedef enum
{
        BLE_ENABLE = 1,
        BLE_DISABLE,
        BLE_LAST
}BLE_Status_e;

/**
 * @}
 */

/**
 * @addtogroup BLUETOOTH_HAL_APIS
 * @{
 */

/**********************************************************************************
*
*  BLE Subsystem level function prototypes 
*
**********************************************************************************/


/* ble_Enable :  */
/**
* @description Enable/disable BLE radio.
*
* @param BLE_Status_e status  New BLE radio status 
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls.
*
*/
INT ble_Enable(BLE_Status_e status);

/* ble_Status :  */
/**
* @description Returns BLE status.
*
* @param BLE_Status_e * status  Pointer to status, to be returned 
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls.
*
*/
INT ble_GetStatus(BLE_Status_e *status);

#endif

/**
 * @}
 */

