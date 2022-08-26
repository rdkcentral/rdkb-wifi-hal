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
#ifndef __WIFI_HAL_RADIO_H__
#define __WIFI_HAL_RADIO_H__

#ifdef __cplusplus
extern "C"{
#endif

#include "wifi_hal_ap.h"

/**
 * @addtogroup WIFI_HAL_TYPES
 * @{
 */

/**
 * @brief Guard intervals types
 */
typedef enum {
    wifi_guard_interval_400 = 0x01,
    wifi_guard_interval_800 = 0x02,
    wifi_guard_interval_1600 = 0x04,
    wifi_guard_interval_3200 = 0x08,
    wifi_guard_interval_auto = 0x10,
} wifi_guard_interval_t;

#define MAXNUMSECONDARYCHANNELS     7

/**
 * @brief Wifi Radio Operation Parameters
 */
typedef struct {
    BOOL enable;                                        /**< The radio enable. */
    wifi_freq_bands_t   band;                           /**< the radio frequency band. */
    BOOL autoChannelEnabled;                            /**< set bAutoChannelEnabled to TRUE to enable Auto Channel. */
    UINT op_class;                                      /**< The Operating class. */
    UINT channel;                                       /**< The radio primary channel. */
    UINT numSecondaryChannels;                          /**< The number odf secondary channels in the list */
    UINT channelSecondary[MAXNUMSECONDARYCHANNELS];     /**< The List of secondary radio channel. */
    wifi_channelBandwidth_t channelWidth;               /**< The channel bandwidth. */
    wifi_ieee80211Variant_t variant;                    /**< The radio operating mode */
    UINT csa_beacon_count;                              /**< Specifies how long CSA need to be announced. */
    wifi_countrycode_type_t countryCode;                /**< The country code. */
    BOOL DCSEnabled;                                    /**< set DCSEnabled to TRUE to enable DCS. */
    UINT dtimPeriod;                                    /**< The DTIM period. */
    UINT beaconInterval;                                /**< The beacon interval. */
    UINT operatingClass;                                /**< The Operating class. */
    UINT basicDataTransmitRates;                        /**< The basic data transmit rates in Mbps. It uses bitmask to return multiples bitrates and wifi_bitrate_t has the definition of valid values*/
    UINT operationalDataTransmitRates;                  /**< The operational data transmit rates in Mbps. It uses bitmask to return multiples bitrates and wifi_bitrate_t has the definition of valid values*/
    UINT fragmentationThreshold;                        /**< The fragmentation threshold in bytes. */
    wifi_guard_interval_t guardInterval;               /**< The guard interval. */
    UINT transmitPower;                                /**<  The transmit power in percentage, eg "75", "100". */
    UINT rtsThreshold;                                 /**< The packet size threshold in bytes to apply RTS/CTS backoff rules. */
    BOOL factoryResetSsid;
    UINT radioStatsMeasuringRate;
    UINT radioStatsMeasuringInterval;
    BOOL ctsProtection;
    BOOL obssCoex;
    BOOL stbcEnable;
    BOOL greenFieldEnable;
    UINT userControl;
    UINT adminControl;
    UINT chanUtilThreshold;
    BOOL chanUtilSelfHealEnable;
} __attribute__((packed)) wifi_radio_operationParam_t;

/**
 * @brief Enhanced Distributed Channel Access parameters
 */
typedef struct {
    CHAR aifsn;    /**< Arbitration Inter-Frame Space Number */
    CHAR cw_min;   /**< Lower bound Contention Window. */
    CHAR cw_max;   /**< Upper bound Contention Window. */
    CHAR timer;    /**< */
} wifi_edca_t;

typedef enum {
    wifi_dl_data_ack_immediate,
    wifi_dl_data_block_ack_immediate,
    wifi_dl_data_block_ack_deferred,
} wifi_dl_data_ack_type_t;

/**
 * @brief To get the scan results for particular radio. 
 * The client is responsible for copying the data  
 * 
 * @param[in] index     Index of Wi-Fi radio 
 * @param[in] bss      BSS Info of the current radio channel
 * @param[in] num_bss  Number of bss channels
 *
 * @return The status of the operation
 * @retval WIFI_HAL_SUCCESS if successful
 * @retval WIFI_HAL_ERROR if error
 *
 * @execution Synchronous
 * @sideeffect None
 *
 * @note This function must not suspend and must not invoke any blocking system
 * calls. It should probably just send a message to a driver event handler task.
 *
 */
typedef INT (*wifi_scanResults_callback)(wifi_radio_index_t index, wifi_bss_info_t **bss, UINT *num_bss);

/** @} */  //END OF GROUP WIFI_HAL_TYPES

/**
 * @addtogroup WIFI_HAL_APIS
 * @{
 */

/**
* @brief Get current Transmit Power in dBm units.
*
* The transmit power value is in dBm units of full power for this radio.
*
* @param[in]  radioIndex        Index of Wi-Fi radio channel
* @param[out] opRadioTxPower    Current Transmit power value, to be returned
*
* @return The status of the operation
* @retval WIFI_HAL_SUCCESS if successful
* @retval WIFI_HAL_ERROR if error
*
* @execution Synchronous
* @sideeffect None
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT wifi_getRadioTransmitPower(INT radioIndex, ULONG *opRadioTxPower);

/**
* @brief Get the Operating Channel Bandwidth
* 
* eg "20MHz", "40MHz", "80MHz", "80+80", "160".
* The output_string is a max length 64 octet string that is allocated by the upper layer.  
* Implementations must ensure that strings are not longer than this.
*
* @param[in] radioIndex     Index of Wi-Fi radio channel
* @param[out] opRadioOpChnBw Get operating channel bandwidth for the selected 
* radio channel in the pre-allocated char buffer
*
* @return The status of the operation
* @retval WIFI_HAL_SUCCESS if successful
* @retval WIFI_HAL_ERROR if error
* @retval WIFI_HAL_INVALID_ARGUMENTS if any of the arguments is invalid
*
* @execution Synchronous
* @sideeffect None
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
* Get the Operating Channel Bandwidth. eg "20MHz", "40MHz", "80MHz", "80+80", "160"
* The opRadioOpChnBw is a max length 64 octet string that is allocated by the RDKB code.  Implementations must ensure that strings are not longer than this.
*/
INT wifi_getRadioOperatingChannelBandwidth(INT radioIndex, CHAR *opRadioOpChnBw);

/**
 * @brief Set Radio Operating Parameters
 *
 * This API is used to configure all radio operation parameter in a
 * single set. Tt includes channel number, channelWidth, mode and
 * auto channel configuration.
 *
 * @param[in]   index           Index of Wi-Fi radio
 * @param[in]   operationParam  Radio Operating Parameters
 *
 * @return The status of the operation
 * @retval WIFI_HAL_SUCCESS if successful
 * @retval WIFI_HAL_ERROR if an generic error is detected
 * @retval WIFI_HAL_INTERNAL_ERROR if an internal error is detected
 * @retval WIFI_HAL_UNSUPPORTED if the API is not supported
 * @retval WIFI_HAL_INVALID_ARGUMENTS if any of the arguments is invalid
 * @retval WIFI_HAL_INVALID_VALUE if the value is invalid
 * 
 * @execution Synchronous
 * @sideeffect None
 * 
 * @note This function must not suspend and must not invoke any blocking system
 * calls. It should probably just send a message to a driver event handler task.
 */
INT wifi_setRadioOperatingParameters(wifi_radio_index_t index, wifi_radio_operationParam_t *operationParam);

/**
  * @brief Get Radio Operating Parameters
  *
  * @param[in]   radio_index     Index of Wi-Fi radio
  * @param[out]  operationParam  Radio Operating Parameters
  *
  * @return The status of the operation
  * @retval WIFI_HAL_SUCCESS if successful
  * @retval WIFI_HAL_ERROR if an generic error is detected
  * @retval WIFI_HAL_INTERNAL_ERROR if an internal error is detected
  * @retval WIFI_HAL_UNSUPPORTED if the API is not supported
  * @retval WIFI_HAL_INVALID_ARGUMENTS if any of the arguments is invalid
  * @retval WIFI_HAL_INVALID_VALUE if the value is invalid
  *
  * @execution Synchronous
  * @sideeffect None
  *
  */
 INT wifi_getRadioOperatingParameters(wifi_radio_index_t index, wifi_radio_operationParam_t *operationParam);

/**
 * @brief Callback function to get scan results 
 *
 * @param[in]   callback_proc   - Scan result callback function
 *
 * @execution Synchronous
 * @sideeffect None
 *
 *  @note This function must not suspend and must not invoke any blocking system
 * calls. It should probably just send a message to a driver event handler task
 */
void wifi_scanResults_callback_register(wifi_scanResults_callback callback_proc);
/** @} */  //END OF GROUP WIFI_HAL_APIS

#ifdef __cplusplus
}
#endif

#endif
