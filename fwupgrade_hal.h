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

#ifndef __FWUPGRADE_HAL_H__
#define __FWUPGRADE_HAL_H__

#include <sys/time.h>

/**********************************************************************
               CONSTANT DEFINITIONS
**********************************************************************/

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


/* FW Download HAL API Prototype */

/* fwupgrade_hal_set_download_url  - 1 */

/**
* @description Set FW Download Settings
* @param char* pUrl
* @param char* pfilename
*
* @return the status of the operation
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any Downloading is in process or Url string is invalided.
*/
INT fwupgrade_hal_set_download_url (char* pUrl, char* pfilename);

/* fwupgrade_hal_get_download_Url: */

/**
* @description Get FW Download Url
* @param char* pUrl
* @param char* pfilename
* @return the status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if FW url string is empty.
*/
INT fwupgrade_hal_get_download_url (char *pUrl, char* pfilename);

/* fwupgrade_hal_set_download_interface: */
/**
* @description Set the FW Download Interface
* @param unsigned int interface - interface=0 for wan0, interface=1 for erouter0
* @return the status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*/
/* interface=0 for wan0, interface=1 for erouter0 */
INT fwupgrade_hal_set_download_interface (unsigned int interface);

/* fwupgrade_hal_GetDownload_Interface: */
/**
* @description Get the FW Download Interface
* @param unsigned int* pinterface - interface=0 for wan0, interface=1 for erouter0
* @return the status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*/
/* interface=0 for wan0, interface=1 for erouter0 */
INT fwupgrade_hal_get_download_interface (unsigned int* pinterface);

/* fwupgrade_halDownload - 3 */
/**
* @description Start FW Download
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
INT fwupgrade_hal_download ();

/* fwupgrade_hal_get_download_status  4 */
/**
* @description Get the FW Download Status
* @param <None>
* @return the status of the FW Download.
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
INT fwupgrade_hal_get_download_status ();

/* fwupgrade_hal_Reboot_Ready - 5 */
/**
* @description Get the Reboot Ready Status
* @param ULONG *pValue- Values of 1 for Ready, 2 for Not Ready
* @return the status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*/
INT fwupgrade_hal_reboot_ready (ULONG *pValue);

/* fwupgrade_hal_download_reboot_now - 6*/
/**
* @description FW Download Reboot Now
* @param <None>
* @return the status of the reboot operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any reboot is in process.
*/
INT fwupgrade_hal_download_reboot_now ();

/* fwupgrade_hal_FWupdateAndFactoryReset : */
/**
* @description: Firmware update and factory reset the device
* @param None
* @return the status of the Firmware update and factory reset operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any reboot is in process.
*/
INT fwupgrade_hal_update_and_factoryreset ();

/* fwupgrade_hal_FWupdateAndFactoryReset : */
/**
* @description: Downloads and upgrades the firmware
* @param None
* @return the status of the Firmware download and upgrade status
* @retval RETURN_OK if successful.
* @retval RETURN_ERR in case of remote server not reachable
*/
INT fwupgrade_hal_download_install(const char *url);

#endif //__FWUPGRADE_HAL_H__

