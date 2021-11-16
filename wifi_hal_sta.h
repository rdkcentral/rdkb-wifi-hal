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


/**
 * @addtogroup WIFI_HAL_APIS
 * @{
 */

/* wifi_connect() function */
 /**
 * Description: To connect the client VAP to specified BSS
 * Parameters :
 *      ap_index - VAP index
 *      wifi_bss_info_t - Information about BSS that client will connect to
 *
 * @return status of the operation
 *  return RETURN_OK - on success
 *  return RETURN_ERR - on failure
 *
 * @execution Synchronous.
 * @sideeffect None.
 *
 */
INT wifi_connect(INT ap_index, wifi_bss_info_t *bss);

/* wifi_disconnect() function */
 /**
 * Description: To disconnect client
 * Parameters : 
 *      ap_index - index of client VAP
 *
 * @return status of the operation
 *  return RETURN_OK - on success
 *  return RETURN_ERR - on failure
 *
 * @execution Synchronous.
 * @sideeffect None.
 *
 */

INT wifi_disconnect(INT ap_index);

/* wifi_getClientCapability() function */
 /**
 * Description: To get client
 * Parameters : 
 *      ap_index - index of client VAP
 *      capability - wifi_client_capabilities_t structure
 *
 * @return status of the operation
 *  return RETURN_OK - on success
 *  return RETURN_ERR - on failure
 *
 * @execution Synchronous.
 * @sideeffect None.
 *
 */
INT wifi_getStationCapability(INT ap_index, wifi_sta_capability_t *cap);

/* wifi_findNetworks() function */
 /**
 * Description: To get client
 * Parameters :
 *      ap_index - index of client VAP
 *      channel - channel number and band information
 *      bss     - array of wifi_bss_info_t structure allocated by HAL layer and to be freed by caller
 *      num_bss - number in array
 *
 * @return status of the operation
 *  return RETURN_OK - on success
 *  return RETURN_ERR - on failure
 *
 * @execution Synchronous.
 * @sideeffect None.
 *
 */
INT wifi_findNetworks(INT ap_index, wifi_channel_t *channel, wifi_bss_info_t **bss, UINT *num_bss);


/* wifi_getStationStats() function */
 /**
 * Description: Return the station stats
 * Parameters :
 *      ap_index - index of client VAP
 *      sta      - station stats
 *
 * @return status of the operation
 *  return RETURN_OK - on success
 *  return RETURN_ERR - on failure
 *
 * @execution Synchronous.
 * @sideeffect None.
 *
 */
INT wifi_getStationStats(INT ap_index, wifi_station_stats_t *sta);


typedef INT ( * wifi_staConnectionStatus_callback)(INT apIndex, wifi_bss_info_t *bss_dev, wifi_station_stats_t *sta);

void wifi_staConnectionStatus_callback_register(wifi_staConnectionStatus_callback callback_proc);



#ifdef __cplusplus
}
#endif

#endif
