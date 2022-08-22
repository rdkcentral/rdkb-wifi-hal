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

/* wifi_staConnectionStatus_callback() */
/**
 * @brief To get the station connection status
 * @param[in] apIndex       - VAP index
 * @param[in,out] bss_dev   - To get connected client Bss information
 * @param[in,out] sta       - To get the connection status of the Vap index
 * 
 * @return The status of the operation
 * @retval WIFI_HAL_SUCCESS if successful
 * @retval WIFI_HAL_ERROR if an generic error is detected
 * @retval WIFI_HAL_INTERNAL_ERROR if an internal error is detected
 * @retval WIFI_HAL_UNSUPPORTED if the API is not supported
 * @retval WIFI_HAL_INVALID_ARGUMENTS if any of the arguments is invalid
 * @retval WIFI_HAL_INVALID_VALUE if the value is invalid
 *
 * @execution Synchronous.
 * @sideeffect None.
 *
 * @note This function must not suspend and must not invoke any blocking system
 * calls. It should probably just send a message to a driver event handler task
 */
typedef INT ( * wifi_staConnectionStatus_callback)(INT apIndex, wifi_bss_info_t *bss_dev, wifi_station_stats_t *sta);

/** @} */  //END OF GROUP WIFI_HAL_TYPES

/**
 * @addtogroup WIFI_HAL_APIS
 * @{
 */
 /* wifi_startScan() function */
 /**
 * @brief Scan for neighbour BSS on a specific frequency or list of frequencies, 
 * If the number of the elements in the frequency is zero then scan all frequencies
 * 
 * @param[in] index     - Radio index
 * @param[in] scan_mode - Mode  how to scan
 * @param[in] dwell_time- Amount of time in millisec remain on a specific channel
 * @param[in] num       - Number of elements in the array
 * @param[in] chan_list - List of frequencies
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
INT wifi_startScan(wifi_radio_index_t index, wifi_neighborScanMode_t scan_mode, INT dwell_time, UINT num, UINT *chan_list);

/* wifi_connect() function */
 /**
 * @brief To connect the BSS to the specified bss
 * @param[in] apIndex  - VAP index
 * @param[in] bss      - Information about BSS that client will connect to
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
INT wifi_connect(INT apIndex, wifi_bss_info_t *bss);

 /* wifi_disconnect() function */
 /**
 * @brief To disconnect the client VAP 
 * @param[in] apIndex          - VAP index
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
INT wifi_disconnect(INT apIndex);

 /* wifi_staConnectionStatus_callback_register() function */
 /**
 * @brief Callback function to disconnect the client VAP 
 * @param[in] callback_proc - Call back function name
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
