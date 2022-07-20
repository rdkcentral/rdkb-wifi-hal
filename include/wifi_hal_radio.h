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

/** @} */  //END OF GROUP WIFI_HAL_TYPES

/**
 * @addtogroup WIFI_HAL_APIS
 * @{
 */
/* wifi_getRadioResetCount() function */
/**
* @brief Get the radio reset count.
*
* @param[in]  radioIndex  Index of Wi-Fi radio channel
* @param[out] output_int  Reset count, to be returned
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous
* @sideeffect None
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT wifi_getRadioResetCount(INT radioIndex, ULONG *output_int);

/* wifi_factoryResetRadios() function */
/**
* @brief Restore all radio parameters without touching access point parameters.
*
* A Specific implementation may dictate some functionalities since different hardware implementations
* may have different requirements.
*
* @param None
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous
*
* @sideeffect None
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
//Restore all radio parameters without touch access point parameters
INT wifi_factoryResetRadios();

/* wifi_factoryResetRadio() function */
/**
* @brief Restore selected radio parameters without touching access point parameters.
*
* @param radioIndex  Index of Wi-Fi Radio channel
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
//Restore selected radio parameters without touch access point parameters
INT wifi_factoryResetRadio(int radioIndex);

/* wifi_getRadioEnable() function */
/**
* @brief Get the Radio enable config parameter.
*
* @param[in]  radioIndex   Index of Wi-Fi radio channel
* @param[out] output_bool  Radio Enable status, to be returned
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous
* @sideeffect None
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
//Get the Radio enable config parameter
INT wifi_getRadioEnable(INT radioIndex, BOOL *output_bool);

/* wifi_setRadioEnable() function */
/**
* @brief Set the Radio enable config parameter.
*
* @param[in]  radioIndex   Index of Wi-Fi radio channel
* @param[in]  enable       Set the selected radio's status as Enable/Disable
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous
* @sideeffect None
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
//Set the Radio enable config parameter
INT wifi_setRadioEnable(INT radioIndex, BOOL enable);

/* wifi_getRadioStatus() function */
/**
* @brief Get the Radio enable status.
*
* @param[in]   radioIndex    Index of Wi-Fi radio channel
* @param[out]  output_bool   Selected radio's enable status, to be returned
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous
* @sideeffect None
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
//Get the Radio enable status
INT wifi_getRadioStatus(INT radioIndex, BOOL *output_bool);

/* wifi_getRadioIfName() function */
/**
* @brief Get the Radio Interface name from platform, eg "wifi0".
*
* @param radioIndex      Index of Wi-Fi radio channel
* @param output_string   Interface name, to be returned
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous
* @sideeffect None
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
//Get the Radio Interface name from platform, eg "wifi0"
INT wifi_getRadioIfName(INT radioIndex, CHAR *output_string);


#ifdef WIFI_HAL_VERSION_3_PHASE2
/* wifi_getRadioChannelsInUse() function */
/**
* @brief Get the list of supported channel. eg: "1-11".
*
* The output_string is a max length 64 octet string that is allocated by the RDKB code.
* Implementations must ensure that strings are not longer than this.
*
* @param[in]  radioIndex     Index of Wi-Fi radio channel
* @param[out] channel_list  List of supported radio channels, to be returned
*
* @return The status of the operation
* @retval WIFI_HAL_SUCCESS if successful
* @retval Error code if any error is detected (WIFI_HAL_ERROR, WIFI_HAL_UNSUPPORTED, etc)
*
* @execution Synchronous
* @sideeffect None
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
//Get the list for used channel. eg: "1,6,9,11"
//The output_string is a max length 256 octet string that is allocated by the RDKB code.  Implementations must ensure that strings are not longer than this.
INT wifi_getRadioChannelsInUse(wifi_radio_index_t radioIndex, wifi_channels_list_t* channel_list);
#endif

/* wifi_getRadioDfsEnable() function */
/**
* @brief Get the Dfs enable status.
*
* @param[in]  radioIndex   Index of Wi-Fi radio channel
* @param[out] output_bool  Get DFS Enable status of the selected radio channel
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous
* @sideeffect None
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT wifi_getRadioDfsEnable(INT radioIndex, BOOL *output_bool);

/* wifi_setRadioDfsEnable() function */
/**
* @brief Set the Dfs enable status.
*
* @param[in] radioIndex  Index of Wi-Fi radio channel
* @param[in] enable      Set DFS Enable status of the selected radio channel
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous
* @sideeffect None
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT wifi_setRadioDfsEnable(INT radioIndex, BOOL enabled);

/* wifi_getRadioMCS() function */
/**
* @brief Get the Modulation Coding Scheme index, eg: "-1", "1", "15".
*
* @param[in]  radioIndex  Index of Wi-Fi radio channel
* @param[out] output_INT  Modulation Coding Scheme index, to be returned
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous
* @sideeffect None
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT wifi_getRadioMCS(INT radioIndex, INT *output_INT);

/* wifi_setRadioMCS() function */
/**
* @brief Set the Modulation Coding Scheme index, eg: "-1", "1", "15".
*
* @param[in] radioIndex  Index of Wi-Fi radio channel
* @param[in] MCS         Modulation Coding Scheme index value
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous
* @sideeffect None
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT wifi_setRadioMCS(INT radioIndex, INT MCS);


/* wifi_getRadioTransmitPower() function */
/**
* @brief Get current Transmit Power in dBm units.
*
* The transmit power value is in dBm units of full power for this radio.
*
* @param[in]  radioIndex   Index of Wi-Fi radio channel
* @param[out] output_ulong Current Transmit power value, to be returned
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous
* @sideeffect None
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT wifi_getRadioTransmitPower(INT radioIndex, ULONG *output_ulong);


/* wifi_getRadioPercentageTransmitPower() function E.g : "75" "100"*/
/**
* @brief Get current Transmit Power level in units of full power.
*
* The transmit power is a percentage value of full power for this radio.
*
* @param[in]  radioIndex   Index of Wi-Fi radio channel
* @param[out] output_ulong Current Transmit power percentage value, to be returned
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous
* @sideeffect None
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT wifi_getRadioPercentageTransmitPower(INT radioIndex, ULONG *output_ulong);

/* wifi_setRadioTransmitPower() function */
/**
* @brief Set current Transmit Power, eg "75", "100".
*
* The transmit power level is in units of full power for this radio.
*
* @param[in] radioIndex      Index of Wi-Fi radio channel
* @param[in] TransmitPower   Transmit power value
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous
* @sideeffect None
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT wifi_setRadioTransmitPower(INT radioIndex, ULONG TransmitPower);

/* wifi_getRadioCarrierSenseThresholdRange() function */
/**
* @brief Indicates the Carrier Sense ranges supported by the radio.
*
* It is measured in dBm. Refer section A.2.3.2 of CableLabs Wi-Fi MGMT Specification.
*
* @param[in]  radioIndex  Index of Wi-Fi radio channel
* @param[out] output      Carrier sense threshold range, to be returned
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous
* @sideeffect None
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT wifi_getRadioCarrierSenseThresholdRange(INT radioIndex, INT *output);  //P3

/* wifi_getRadioCarrierSenseThresholdInUse() function */
/**
* @brief The RSSI signal level at which CS/CCA detects a busy condition.
* 
* This attribute enables Access Points to increase minimum sensitivity to avoid detecting busy condition
* from multiple/weak Wi-Fi sources in dense Wi-Fi environments.
* It is measured in dBm. Refer section A.2.3.2 of CableLabs Wi-Fi MGMT Specification.
*
* @param[in]  radioIndex  Index of Wi-Fi radio channel
* @param[out] output      Carrier sense threshold in use, to be returned
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous
* @sideeffect None
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT wifi_getRadioCarrierSenseThresholdInUse(INT radioIndex, INT *output);    //P3

/* wifi_setRadioCarrierSenseThresholdInUse() function */
/**
* @brief Set Carrier sense threshold in use for the selected radio index.
*
* The RSSI signal level at which CS/CCA detects a busy condition.
* This attribute enables Access Point to increase minimum sensitivity to avoid detecting busy condition
* from multiple/weak Wi-Fi sources in dense Wi-Fi environments. It is measured in dBm.
*
* @param[in] radioIndex  Index of Wi-Fi radio channel
* @param[in] threshold   Carrier sense threshold, to be returned
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous
* @sideeffect None
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT wifi_setRadioCarrierSenseThresholdInUse(INT radioIndex, INT threshold);    //P3

//-----------------------------------------------------------------------------------------------------
/* wifi_applyRadioSettings() function */
/**
* @brief This API is used to apply (push) all previously set radio level variables and make these settings active in the hardware.
*
* Not all implementations may need this function.
* If not needed for a particular implementation simply return no-error (0).
*
* @param[in] radioIndex  Index of Wi-Fi radio channel
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous
* @sideeffect None
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT wifi_applyRadioSettings(INT radioIndex);  

/* wifi_setRadioCtsProtectionEnable() function */
/**
* @brief  Enables CTS protection for the radio used by this Access Point.
*
* @param[in] apIndex  Access Point index
* @param[in] enable   CTS protection enable value
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous
* @sideeffect None
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT wifi_setRadioCtsProtectionEnable(INT apIndex, BOOL enable);          //P3 

/* wifi_setRadioObssCoexistenceEnable() function */
/**
* @brief Enables OBSS Coexistence - fall back to 20MHz if necessary for the radio used by this AP.
*
* @param[in] apIndex   Access Point index
* @param[in] enable    OBSS Coexistence enable value
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous
* @sideeffect None
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT wifi_setRadioObssCoexistenceEnable(INT apIndex, BOOL enable);      

/* wifi_setRadioFragmentationThreshold() function */
/**
* @brief Sets the fragmentation threshold in bytes for the radio used by this Access Point.
*
* @param[in] apIndex    Access Point index
* @param[in] threshold  Fragmentation Threshold value
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous
* @sideeffect None
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT wifi_setRadioFragmentationThreshold(INT apIndex, UINT threshold);    //P3 

/* wifi_setRadioSTBCEnable() function */
/**
* @brief Enable STBC mode in the hardware.
* 0 == not enabled, 1 == enabled.
*
* @param[in]  radioIndex   Radio index
* @param[in]  STBC_Enable  STBC mode enable value
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous
* @sideeffect None
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT wifi_setRadioSTBCEnable(INT radioIndex, BOOL STBC_Enable);

/* wifi_getRadioAMSDUEnable() function */
/**
* @brief Outputs A-MSDU enable status, 0 == not enabled, 1 == enabled.
*
* @param[in]  radioIndex   Radio index
* @param[out] output_bool  A-MSDU enable status, to be returned
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous
* @sideeffect None
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT wifi_getRadioAMSDUEnable(INT radioIndex, BOOL *output_bool);

/* wifi_setRadioAMSDUEnable() function */
/**
* @brief Enables A-MSDU in the hardware, 0 == not enabled, 1 == enabled.
*
* @param[in]  radioIndex    Radio index
* @param[out] amsduEnable   A-MSDU enable status value
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous
* @sideeffect None
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT wifi_setRadioAMSDUEnable(INT radioIndex, BOOL amsduEnable);

/* wifi_getRadioUpTime() function */
/**
* @brief Get the number of seconds elapsed since radio is started.
*
* @param[in] radioIndex  Radio index
* @param[in] uptime      Wifi uptime, to be returned
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous
* @sideeffect None
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT wifi_getRadioUpTime(INT radioIndex, ULONG *uptime);                  // get the number of seconds elapsed since radio is started

/* wifi_getRadioReverseDirectionGrantSupported() function */
/**
* @brief Get radio RDG enable Support.
*
* @param[in]  radioIndex   Radio index
* @param[out] output_bool  RDG enable support value, to be returned
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous
* @sideeffect None
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT wifi_getRadioReverseDirectionGrantSupported(INT radioIndex, BOOL *output_bool);    //Get radio RDG enable Support

/* wifi_getRadioAutoBlockAckEnable() function */
/**
* @brief Get radio auto block ack enable setting.
*
* @param[in]  radioIndex   Radio index
* @param[out] output_bool  Auto block ack enable setting value, to be returned
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous
* @sideeffect None
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT wifi_getRadioAutoBlockAckEnable(INT radioIndex, BOOL *output_bool);             //Get radio auto block ack enable setting

/* wifi_setRadioAutoBlockAckEnable() function */
/**
* @brief Set radio auto block ack enable setting.
*
* @param[in] radioIndex  Radio index
* @param[in] enable      Auto block ack enable setting value
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous
* @sideeffect None
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT wifi_setRadioAutoBlockAckEnable(INT radioIndex, BOOL enable);               //Set radio auto block ack enable setting

/* wifi_getRadioIGMPSnoopingEnable() function */
/**
* @brief Get radio IGMP snooping enable setting.
*
* @param[in]  radioIndex   Radio index
* @param[out] output_bool  Radio IGMP snooping enable setting, to be returned
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous
* @sideeffect None
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT wifi_getRadioIGMPSnoopingEnable(INT radioIndex, BOOL *output_bool);         //Get radio IGMP snooping enable setting

/* wifi_setRadioIGMPSnoopingEnable() function */
/**
* @brief Set radio IGMP snooping enable setting.
*
* @param[in]  radioIndex  Radio index
* @param[out] enable      Radio IGMP snooping enable setting
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous
* @sideeffect None
*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT wifi_setRadioIGMPSnoopingEnable(INT radioIndex, BOOL enable);                   //Set radio IGMP snooping enable setting

/**
 * @brief Set Zero DFS State
 *
 * The Zero DFS feature can be enabled or disabled. For EU countries
 * the "Pre-CAC" can be also set. If the "Pre-CAC" is set, then
 * after passing background CAC driver can start background CAC
 * on the next channel.
 *
 * @param[in]  radioIndex Index of Wi-Fi radio
 * @param[in]  enabled    True if ZeroDFS must be enabled, false otherwise.
 * @param[in]  precac     Valid only for EU regulatory domain. If set,
 *                        after passing requested backgronund CAN, driver
 *                        can start background CAC on the next channel.
 *
 * @return The status of the operation
 * @retval RETURN_OK if successful
 * @retval RETURN_ERR if any error is detected
 *
 * @execution Synchronous
 * @sideeffect None
 *
 */
INT wifi_setZeroDFSState(UINT radioIndex, BOOL enable, BOOL precac);

/**
 * @brief Get Zero DFS State
 *
 * The Zero DFS feature can be enabled or disabled. For EU countries
 * the "Pre-CAC" can be also set. If the "Pre-CAC" is set, then
 * after passing background CAC driver can start background CAC
 * on next channel.
 *
 * @param[in]   radioIndex Index of Wi-Fi radio
 * @param[out]  enabled    True if ZeroDFS is enabled, false otherwise.
 * @param[out]  precac     Valid only for EU regulatory domain. If true,
 *                         then driver can start background CAC on
 *                         the next channel.
 *
 * @return The status of the operation
 * @retval RETURN_OK if successful
 * @retval RETURN_ERR if any error is detected
 *
 * @execution Synchronous
 * @sideeffect None
 *
 */
INT wifi_getZeroDFSState(UINT radioIndex, BOOL *enable, BOOL *precac);

/* 802.11ax HAL API prototypes */

INT wifi_setDownlinkMuType(INT radio_index, wifi_dl_mu_type_t mu_type);

INT wifi_getDownlinkMuType(INT radio_index, wifi_dl_mu_type_t *mu_type);

INT wifi_setUplinkMuType(INT radio_index, wifi_ul_mu_type_t mu_type);

INT wifi_getUplinkMuType(INT radio_index, wifi_ul_mu_type_t *mu_type);

INT wifi_setGuardInterval(INT radio_index, wifi_guard_interval_t guard_interval);

INT wifi_getGuardInterval(INT radio_index, wifi_guard_interval_t *guard_interval);

INT wifi_setBSSColor(INT radio_index, UCHAR color);

INT wifi_getBSSColor(INT radio_index, UCHAR *color);

/**
 * @brief Get the list of avaiable BSS color
 *
 * This API return a list of availables BSS color that can be used to
 * to configure the radio using wifi_setBSSColor API.
 * This list should be created based on neighbours BSS color and
 * the station reports.
 *
 * @param[in]   radio_index       Index of Wi-Fi radio
 * @param[in]   maxNumberColors   Maximum number of color that can be
                                  retuned
 * @param[out]  colorList         The list of avaiable BSS color
 * @param[out]  numColorReturned  Number of color returned in the list
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
INT wifi_getAvailableBSSColor(INT radio_index, INT maxNumberColors, UCHAR* colorList, INT *numColorReturned);

/**
 * @brief Get MU (Multi-User) EDCA (Enhanced Distributed Channel Access) parameter
 *
 * @param[in]   radio_index    Index of Wi-Fi radio
 * @param[in]   ac             The Access Category
 * @param[out]  edca           The MU EDCA parameters
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
INT wifi_getMuEdca(INT radio_index, wifi_access_category_t ac, wifi_edca_t *edca);

INT wifi_setDownlinkDataAckType (INT radio_index,
                                wifi_dl_data_ack_type_t ack_type);

INT    wifi_get80211axDefaultParameters    (INT radio_index, wifi_80211ax_params_t    *params);


/////////////////////////// tri radio definitions /////////////////////////////////

/**
 * @brief Set Radio Operating Parameters
 *
 * This API is used to configured all radio operation parameter in a
 * single set. it includes channel number, channelWidth, mode and
 * auto channel configuration.
 *
 * @param[in]   radio_index     Index of Wi-Fi radio
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

/* wifi_getScanResults() function */
 /**
 * Description: Return scan results 
 * Parameters :
 *      ap_index - index of client VAP
 *      channel  - scan channel
 *      bss      - bss stats
 *      num_bss  - number of bss returned
 *
 * @return status of the operation
 *  return RETURN_OK - on success
 *  return RETURN_ERR - on failure
 *
 * @execution Synchronous.
 * @sideeffect None.
 *
 */
INT wifi_getScanResults(wifi_radio_index_t index, wifi_channel_t *channel, wifi_bss_info_t **bss, UINT *num_bss);
 

typedef INT ( * wifi_scanResults_callback)(wifi_radio_index_t index, wifi_bss_info_t **bss, UINT *num_bss);

void wifi_scanResults_callback_register(wifi_scanResults_callback callback_proc);


/** @} */  //END OF GROUP WIFI_HAL_APIS

#ifdef __cplusplus
}
#endif

#endif
