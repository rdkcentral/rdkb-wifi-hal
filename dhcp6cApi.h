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
/**
* @file dhcp6cApi.h
* @brief For CCSP Component: DHCP6-Client Status
*
* @description This header file gives the function call prototypes and structure definitions used for the RDK-Broadband DHCP6Client Status abstraction layer.
*/

#ifndef _DHCP6_CLIENT_API_
#define _DHCP6_CLIENT_API_

/* ert_dhcp6c_get_info() function */
/**
* @description Gets the E-Router Info.
* @param
*    pInfo - E-Router Info(elements of structure "dhcp6cInfo_t"), to be returned
* @return The status of the operation.
* @retval STATUS_SUCCESS if successful.
* @retval STATUS_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
int ert_dhcp6c_get_info(dhcp6cInfo_t *pInfo);

/* ecm_dhcp6c_get_info() function */
/**
* @description Gets the ECM Info.
* @param
*    pInfo - ECM Info(elements of structure "dhcp6cInfo_t"), to be returned
* @return The status of the operation.
* @retval STATUS_SUCCESS if successful.
* @retval STATUS_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
int ecm_dhcp6c_get_info(dhcp6cInfo_t *pInfo);

#endif


