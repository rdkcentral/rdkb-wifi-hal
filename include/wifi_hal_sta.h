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
#ifndef __WIFI_HAL_STA_H__
#define __WIFI_HAL_STA_H__

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @addtogroup WIFI_HAL_TYPES
 * @{
 */

typedef struct {

} wifi_sta_capability_t;


typedef struct {
    UINT                        vap_index;
    wifi_connection_status_t    connect_status;
} wifi_station_stats_t;

typedef INT ( * wifi_staConnectionStatus_callback)(INT apIndex, wifi_bss_info_t *bss_dev, wifi_station_stats_t *sta);

/** @} */  //END OF GROUP WIFI_HAL_TYPES

/**
 * @addtogroup WIFI_HAL_APIS
 * @{
 */

/* wifi_connect() function */
 /**
 * @brief To connect the client VAP to specified BSS
 * @param[in] ap_index  - VAP index
 * @param[in] bss       - Information about BSS that client will connect to
 *
 * @return status of the operation
 * @retval RETURN_OK if successful
 * @retval RETURN_ERR if any error is detected
 *
 * @execution Synchronous.
 * @sideeffect None.
 *
 * @note This function must not suspend and must not invoke any blocking system
 * calls. It should probably just send a message to a driver event handler task
 */
INT wifi_connect(INT ap_index, wifi_bss_info_t *bss);

 /* wifi_disconnect() function */
 /**
 * @brief To disconnect the client VAP 
 * @param[in] ap_index          - VAP index
 *
 * @return status of the operation
 * @retval RETURN_OK if successful
 * @retval RETURN_ERR if any error is detected
 *
 * @execution Synchronous.
 * @sideeffect None.
 *
 * @note This function must not suspend and must not invoke any blocking system
 * calls. It should probably just send a message to a driver event handler task
 */
INT wifi_disconnect(INT ap_index);

 /* wifi_staConnectionStatus_callback_register() function */
 /**
 * @brief To disconnect the client VAP 
 * @param[in] callback_proc - Call back function name
 *
 * @return None
 *
 * @execution Synchronous.
 * @sideeffect None.
 *
 * @note This function must not suspend and must not invoke any blocking system
 * calls. It should probably just send a message to a driver event handler task
 */
void wifi_staConnectionStatus_callback_register(wifi_staConnectionStatus_callback callback_proc);

/** @} */  //END OF GROUP WIFI_HAL_APIS


#ifdef __cplusplus
}
#endif

#endif
