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

#ifndef __WIFI_HAL_CLIENTMGT_H__
#define __WIFI_HAL_CLIENTMGT_H__

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @addtogroup WIFI_HAL_APIS
 * @{
 */
/* wifi_getBandSteeringEnable() function */
/**
* @brief To get Band Steering enable status.
*
* @param[out] enable  Band Steering enable status, to be returned
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
INT wifi_getBandSteeringEnable(BOOL *enable);

/* wifi_setBandSteeringEnable() function */
/**
* @brief To turn on/off Band steering.
*
* @param[in] enable  Band Steering enable status
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
INT wifi_setBandSteeringEnable(BOOL enable);

/* wifi_getBandSteeringApGroup() function */
/**
* @brief To get Band Steering Access Point group.
*
* @param[out] output_ApGroup Band Steering Access point group
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
INT wifi_getBandSteeringApGroup(char *output_ApGroup);    

/* wifi_setBandSteeringApGroup() function */
/**
* @brief To set Band Steering Access Point group. 
*
* @param[in] ApGroup - Band Steering Access Point  group
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
//To set Band Steering AP group 
//ApGroup contains AP index(start from 1) pair array, in following format "$index_2.4G,$index_5G;$index_2.4G,$index_5G"
//Example "1,2;3,4;7,8" for Private, XH, LnF pairs. 
//ApGroup have to contain at least one AP pair, such as "1,2"
INT wifi_setBandSteeringApGroup(char *ApGroup); 

//<<
/* wifi_getBandSteeringBandUtilizationThreshold() function */
/**
* @brief To set and read the band steering BandUtilizationThreshold parameters.
*
* @param[in]  radioIndex     Radio Index
* @param[out] pBuThreshold   Steering bane utilization threshold, to be returned
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
INT wifi_getBandSteeringBandUtilizationThreshold (INT radioIndex, INT *pBuThreshold);

/* wifi_setBandSteeringBandUtilizationThreshold() function */
/**
* @brief To set the band steering BandUtilizationThreshold parameters.
*
* @param[in] radioIndex    Radio Index
* @param[in] buThreshold   Steering bane utilization threshold
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
INT wifi_setBandSteeringBandUtilizationThreshold (INT radioIndex, INT buThreshold);

/* wifi_getBandSteeringRSSIThreshold() function */
/**
* @brief To read the band steering RSSIThreshold parameters.
*
* @param[in] radioIndex       Radio Index
* @param[in] pRssiThreshold   Band steering RSSIThreshold value, to be returned
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
INT wifi_getBandSteeringRSSIThreshold (INT radioIndex, INT *pRssiThreshold);

/* wifi_setBandSteeringRSSIThreshold() function */
/**
* @brief To set the band steering RSSIThreshold parameters.
*
* For 2.4G, the expectation is if the 2G rssi is below the set value steer to 2G
* For 5G, if the set value is greater than the set threshold value then steer to 5
*
* @param[in] radioIndex     Radio Index
* @param[in] rssiThreshold  Band steering RSSIThreshold value
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
INT wifi_setBandSteeringRSSIThreshold (INT radioIndex, INT rssiThreshold);

/* wifi_getBandSteeringPhyRateThreshold() function */
/**
* @brief To read the band steering physical modulation rate threshold parameters.
*
* @param[in]  radioIndex    Radio Index
* @param[out] pPrThreshold  Physical modulation rate threshold value, to be returned
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
INT wifi_getBandSteeringPhyRateThreshold (INT radioIndex, INT *pPrThreshold); //If chip is not support, return -1

/* wifi_setBandSteeringPhyRateThreshold() function */
/**
* @brief To set the band steering physical modulation rate threshold parameters.
*
* @param[in] radioIndex   Radio Index
* @param[in] prThreshold  Physical modulation rate threshold value
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
INT wifi_setBandSteeringPhyRateThreshold (INT radioIndex, INT prThreshold); //If chip is not support, return -1

/* wifi_getBandSteeringOverloadInactiveTime() function */
/**
* @brief To read the inactivity time (in seconds) for steering under overload condition 
*
*
* @param[in]  radioIndex             Radio Index
* @param[out] overloadInactiveTime   inactivity time (in seconds) for steering under overload condition
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
INT wifi_getBandSteeringOverloadInactiveTime (INT radioIndex, INT *overloadInactiveTime); //If chip is not support, return -1

/* wifi_setBandSteeringOverloadInactiveTime() function */
/**
* @brief To set the inactivity time (in seconds) for steering under overload condition.
*
*
* @param[in] radioIndex             Radio Index
* @param[in] overloadInactiveTime   Inactivity time (in seconds) for steering under overload condition
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
INT wifi_setBandSteeringOverloadInactiveTime (INT radioIndex, INT overloadInactiveTime); //If chip is not support, return -1

/* wifi_getBandSteeringIdleInactiveTime() function */
/**
* @brief To read the inactivity time (in seconds) for steering under Idle condition.
*
* @param[in]  radioIndex         Radio Index
* @param[out] idleInactiveTime   Inactivity time (in seconds) for steering under Idle condition
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
INT wifi_getBandSteeringIdleInactiveTime (INT radioIndex, INT *idleInactiveTime); //If chip is not support, return -1

/* wifi_getBandSteeringIdleInactiveTime() function */
/**
* @brief To set the inactivity time (in seconds) for steering under Idle condition.
*
*
* @param[in]  radioIndex         Radio Index
* @param[in]  idleInactiveTime   Inactivity time (in seconds) for steering under Idle condition
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
INT wifi_setBandSteeringIdleInactiveTime (INT radioIndex, INT idleInactiveTime); //If chip is not support, return -1

/* wifi_getBandSteeringLog() function */
/**
* @brief To get the band steering log.
*
* If no steering or record_index is out of boundary, return -1.
*
* @param[in]  record_index       Record index
* @param[out] pSteeringTime      Returns the UTC time in seconds
* @param[in]  pClientMAC         pClientMAC is pre allocated as 64bytes
* @param[in]  pSourceSSIDIndex   Source SSID index
* @param[in]  pDestSSIDIndex     Destination SSID index
* @param[out] pSteeringReason    Returns the predefined steering trigger reason
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
INT wifi_getBandSteeringLog(INT record_index, ULONG *pSteeringTime, CHAR *pClientMAC, INT *pSourceSSIDIndex, INT *pDestSSIDIndex, INT *pSteeringReason); 

/* wifi_getApAssociatedDevicesHighWatermarkThreshold() function */
/**
* @brief Get the HighWatermarkThreshold value, that is lesser than or equal to MaxAssociatedDevices.
*
* Setting this parameter does not actually limit the number of clients that can associate with this access point
* as that is controlled by MaxAssociatedDevices.
* MaxAssociatedDevices or 50.
* The default value of this parameter should be equal to MaxAssociatedDevices.
* In case MaxAssociatedDevices is 0 (zero), the default value of this parameter should be 50.
* A value of 0 means that there is no specific limit and Watermark calculation algorithm should be turned off.
*
* @param[in]  apIndex  Access Point index
* @param[out] output   HighWatermarkThreshold value, to be returned
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
INT wifi_getApAssociatedDevicesHighWatermarkThreshold(INT apIndex, UINT *output);

/* wifi_setApAssociatedDevicesHighWatermarkThreshold() function */
/**
* @brief Set the HighWatermarkThreshold value, that is lesser than or equal to MaxAssociatedDevices.
*
* Setting this parameter does not actually limit the number of clients that can associate with this access point
* as that is controlled by MaxAssociatedDevices.
* MaxAssociatedDevices or 50.
* The default value of this parameter should be equal to MaxAssociatedDevices.
* In case MaxAssociatedDevices is 0 (zero), the default value of this parameter should be 50. 
* A value of 0 means that there is no specific limit and Watermark calculation algorithm should be turned off.
*
* @param[in] apIndex    Access Point index
* @param[in] Threshold  HighWatermarkThreshold value 
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
INT wifi_setApAssociatedDevicesHighWatermarkThreshold(INT apIndex, UINT Threshold);

/* wifi_getApAssociatedDevicesHighWatermarkThresholdReached() function */
/**
* @brief Get the number of times the current total number of associated device has reached the HighWatermarkThreshold value.
*
* This calculation can be based on the parameter AssociatedDeviceNumberOfEntries as well.
* Implementation specifics about this parameter are left to the product group and the device vendors.
* It can be updated whenever there is a new client association request to the access point.
*
* @param[in]  apIndex Access Point index
* @param[out] output  Number of times the current total number of associated device has reached
*                     the HighWatermarkThreshold value, to be returned
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
INT wifi_getApAssociatedDevicesHighWatermarkThresholdReached(INT apIndex, UINT *output);

/* wifi_getApAssociatedDevicesHighWatermark() function */
/**
* @brief Maximum number of associated devices that have ever associated with the access point concurrently
* since the last reset of the device or WiFi module.
*
* @param[in]  apIndex  Access Point index
* @param[out] output   Maximum number of associated devices that have ever associated with the access point concurrently,
*                      to be returned 
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
INT wifi_getApAssociatedDevicesHighWatermark(INT apIndex, UINT *output);

/* wifi_getApAssociatedDevicesHighWatermarkDate() function */
/**
* @brief Get Date and Time at which the maximum number of associated devices ever associated with the access point
* concurrently since the last reset of the device or WiFi module.
*
* In short when was AssociatedDevicesHighWatermark updated
* This dateTime value is in UTC.
*
* @param[in]   apIndex             Access Point index
* @param[out]  output_in_seconds   Date and Time at which the maximum number of associated 
*                                  devices ever associated with the access point
*                                  concurrenlty, to be returned.
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
INT wifi_getApAssociatedDevicesHighWatermarkDate(INT apIndex, ULONG *output_in_seconds);

/* @description Set the Fast Transition capability to disabled, full FT
 * support, or adaptive FT support.  Adaptive support is the same as full
 * support except the Mobility Domain Element is not sent in Beacon Frames.
 * 
 * @param apIndex - AP Index the setting applies to.
 * @param activate - 0 = disabled, 1 = full FT support, 2 = adaptive support.
 * @return The status of the operation.
 * @retval RETURN_OK if successful.
 * @retval RETURN_ERR if any error is detected.
 */
INT wifi_setFastBSSTransitionActivated(INT apIndex, UCHAR activate);

/**
 * @brief Get the Fast Transition capability value.  
 * 
 * @param apIndex - AP Index the setting applies to.
 * @param activate - 0 = disabled, 1 = full FT support, 2 = adaptive support.
 *
 * @return The status of the operation.
 * @retval RETURN_OK if successful.
 * @retval RETURN_ERR if any error is detected.
 */
INT wifi_getBSSTransitionActivated(INT apIndex, BOOL *activate);
/** @} */  //END OF GROUP WIFI_HAL_APIS

/**
 * @addtogroup WIFI_HAL_TYPES
 * @{
 */
/**
 * @brief Set the Fast Transition capability to disabled, full FT
**
 * @brief EAP/EAPOL Authenticator information.
 *
 * Structure which holds the the EAP/EAPOL Config param values.
 */
typedef struct _wifi_eap_config_t
{
    unsigned int    uiEAPOLKeyTimeout;
    unsigned int    uiEAPOLKeyRetries;
    unsigned int    uiEAPIdentityRequestTimeout;
    unsigned int    uiEAPIdentityRequestRetries;
    unsigned int    uiEAPRequestTimeout;
    unsigned int    uiEAPRequestRetries;
} wifi_eap_config_t;
/** @} */  //END OF GROUP WIFI_HAL_TYPES

/**
 * @addtogroup WIFI_HAL_APIS
 * @{
 */
/**
 * @brief Get the Fast Transition over DS activated value.  
 * @description Set the EAP authentication and EAPOL Handshake parameters.
 * EAPOL Key Timeout and max retries [M1 and M3]
 * EAP Identity Request and max retries
 * EAP Request Timeout and max retries
 * @param [in] apIndex - VAP number
 * @param [in] value - Either timeout or retry value
 * @param [in] param - Pramater string name to be configured as follows
 * eapolkey(timeout or retries),
 * eapidentityrequest(timeout or retries),
 * eaprequest(timeout or retries)
 * @return The status of the operation.
 * @retval RETURN_OK if successful.
 * @retval RETURN_ERR if any error is detected.
 */
INT wifi_setEAP_Param(UINT apIndex, UINT value, char  *param);

/* @description Get the EAP authentication and EAPOL Handshake parameters.
 * EAPOL Key Timeout and max retries [M1 and M3]
 * EAP Identity Request and max retries
 * EAP Request Timeout and max retries
 * @param [in] apIndex - VAP number
 * @param [in] output to be filled
 * @return The status of the operation.
 * @retval RETURN_OK if successful.
 * @retval RETURN_ERR if any error is detected.
 */
INT wifi_getEAP_Param(UINT apIndex, wifi_eap_config_t *output);

/* @description Get the Fast Transition over DS activated value.  
 * See 802.11-2016 section 13.3.
 * 
 * @param apIndex - AP Index the setting applies to.
 * @param activate - True for activated (enabled), false for not activated
 * (disabled).
 *
 * @return The status of the operation.
 * @retval RETURN_OK if successful.
 * @retval RETURN_ERR if any error is detected.
 */
INT wifi_getFTOverDSActivated(INT apIndex, BOOL *activate);

/**
 * @brief Set the Fast Transition over DS activated value. 
 * See 802.11-2016 section 13.3. 
 * 
 * @param apIndex - AP Index the setting applies to.
 * @param activate - True for activated (enabled), false for not activated
 * (disabled).
 *
 * @return The status of the operation.
 * @retval RETURN_OK if successful.
 * @retval RETURN_ERR if any error is detected.
 */
INT wifi_setFTOverDSActivated(INT apIndex, BOOL *activate);

/**
 * @brief Get the Fast Transition Mobility Domain value. 
 * See 802.11-2016 section 13.3. 
 * 
 * @param apIndex - AP Index the setting applies to.
 * @param mobilityDomain - Value of the FT Mobility Domain for this AP.
 *
 * @return The status of the operation.
 * @retval RETURN_OK if successful.
 * @retval RETURN_ERR if any error is detected.
 */
INT wifi_getFTMobilityDomainID(INT apIndex, UCHAR mobilityDomain[2]);

/**
 * @brief Set the Fast Transition Mobility Domain value.  
 * See 802.11-2016 section 13.3.
 * 
 * @param apIndex - AP Index the setting applies to.
 * @param mobilityDomain - Value of the FT Mobility Domain for this AP.
 *
 * @return The status of the operation.
 * @retval RETURN_OK if successful.
 * @retval RETURN_ERR if any error is detected.
 */
INT wifi_setFTMobilityDomainID(INT apIndex, UCHAR mobilityDomain[2]);

/**
 * @brief Get the Fast Transition Resource Request Support value. 
 * See 802.11-2016 section 13.3. 
 * 
 * @param apIndex - AP Index the setting applies to.
 * @param supported - True is FT resource request supported, false is not
 * supported.
 *
 * @return The status of the operation.
 * @retval RETURN_OK if successful.
 * @retval RETURN_ERR if any error is detected.
 */
INT wifi_getFTResourceRequestSupported(INT apIndex, BOOL *supported);

/**
 * @brief Set the Fast Transition Resource Request Support value.  
 * See 802.11-2016 section 13.3.
 * 
 * @param apIndex - AP Index the setting applies to.
 * @param suppored - True is FT resource request supported, false is not
 * supported.
 *
 * @return The status of the operation.
 * @retval RETURN_OK if successful.
 * @retval RETURN_ERR if any error is detected.
 */
INT wifi_setFTResourceRequestSupported(INT apIndex, BOOL *supported);

/**
 * @brief Get the Fast Transition R0 Key Lifetime value.  
 * See 802.11-2016 section 13.4.2.
 * 
 * @param apIndex - AP Index the setting applies to.
 * @param lifetime - R0 Key Lifetime.
 *
 * @return The status of the operation.
 * @retval RETURN_OK if successful.
 * @retval RETURN_ERR if any error is detected.
 */
INT wifi_getFTR0KeyLifetime(INT apIndex, UINT *lifetime);

/**
 * @brief Set the Fast Transition R0 Key Lifetime value.  
 * See 802.11-2016 section 13.4.2
 * 
 * @param apIndex - AP Index the setting applies to.
 * @param lifetime - R0 Key Lifetime.
 *
 * @return The status of the operation.
 * @retval RETURN_OK if successful.
 * @retval RETURN_ERR if any error is detected.
 */
INT wifi_setFTR0KeyLifetime(INT apIndex, UINT *lifetime);

/**
 * @brief Get the Fast Transition R0 Key Holder ID value.  
 * See 802.11-2016 section 13.3.
 * 
 * @param apIndex - AP Index the setting applies to.
 * @param keyHolderID - R0 Key Holder ID string.
 *
 * @return The status of the operation.
 * @retval RETURN_OK if successful.
 * @retval RETURN_ERR if any error is detected.
 */
INT wifi_getFTR0KeyHolderID(INT apIndex, UCHAR *keyHolderID);

/**
 * @brief Set the Fast Transition R0 Key Holder ID value.  
 * See 802.11-2016 section 13.3.
 * 
 * @param apIndex - AP Index the setting applies to.
 * @param keyHolderID - R0 Key Holder ID string.
 *
 * @return The status of the operation.
 * @retval RETURN_OK if successful.
 * @retval RETURN_ERR if any error is detected.
 */
INT wifi_setFTR0KeyHolderID(INT apIndex, UCHAR *keyHolderID);

/**
 * @brief Get the Fast Transition R1 Key Holder ID value.  
 * See 802.11-2016 section 13.3.
 * 
 * @param apIndex - AP Index the setting applies to.
 * @param keyHolderID - R0 Key Holder ID string.
 *
 * @return The status of the operation.
 * @retval RETURN_OK if successful.
 * @retval RETURN_ERR if any error is detected.
 */
INT wifi_getFTR1KeyHolderID(INT apIndex, UCHAR *keyHolderID);

/**
 * @brief Set the Fast Transition R1 Key Holder ID value.  
 * See 802.11-2016 section 13.3.
 * 
 * @param apIndex - AP Index the setting applies to.
 * @param keyHolderID - R0 Key Holder ID string.
 *
 * @return The status of the operation.
 * @retval RETURN_OK if successful.
 * @retval RETURN_ERR if any error is detected.
 */
INT wifi_setFTR1KeyHolderID(INT apIndex, UCHAR *keyHolderID);

/** @} */  //END OF GROUP WIFI_HAL_APIS

/**
 * @addtogroup WIFI_HAL_TYPES
 * @{
 */
typedef enum {
    FT_SUPPORT_DISABLED,
    FT_SUPPORT_FULL,
    FT_SUPPORT_ADAPTIVE    
} wifi_fastTrasitionSupport_t;

#define MAX_KEY_HOLDERS 8
typedef struct {
    mac_address_t   mac;
    nas_id_t        nasId;
    r0r1_key_t      key;
} wifi_r0KH_t;

typedef struct {
    mac_address_t   mac;
    mac_address_t   r1khId;
    r0r1_key_t      key;
} wifi_r1KH_t;

typedef struct {
    wifi_fastTrasitionSupport_t support;
    USHORT                      mobilityDomain;
    BOOL                        overDS;
    nas_id_t                    r0KeyHolder;
    USHORT                      r0KeyLifeTime;
    mac_address_t               r1KeyHolder;
    USHORT                      reassocDeadLine;
    BOOL                        pmkR1Push;
    UCHAR                       numR0KHs;
    wifi_r0KH_t                 r0KH[MAX_KEY_HOLDERS];
    UCHAR                       numR1KHs;
    wifi_r1KH_t                 r1KH[MAX_KEY_HOLDERS];
} wifi_FastTransitionConfig_t;

/** @} */  //END OF GROUP WIFI_HAL_TYPES

/**
 * @addtogroup WIFI_HAL_APIS
 * @{
 */
INT wifi_pushApFastTransitionConfig(INT apIndex, wifi_FastTransitionConfig_t *ftData);

/**
 * @brief Set the BTM capability to activated or deactivated,
 * same as enabled or disabled.  The word "activated" is used here because
 * that's what's used in the 802.11 specification.  When deactivate the
 * gateway ignores a BTM report request as defined in 802.11-2016 section
 * 11.11.10.3.  The AP (apIndex) BSS Transition bit in any Extended Capabilities
 * element sent out is set corresponding to the activate parameter.
 *
 * @param apIndex - AP Index the setting applies to.
 * @param activate - True for activate false for deactivate.
 * @return The status of the operation.
 * @retval RETURN_OK if successful.
 * @retval RETURN_ERR if any error is detected.
 */
INT wifi_setBSSTransitionActivation(UINT apIndex, BOOL activate);

/**
 * @description Get the BTM capability of activated or deactivated,
 * same as enabled or disabled.
 *
 * @param apIndex - AP Index the setting applies to.
 * @param activate - True for activate false for deactivate.
 * @return The status of the operation.
 * @retval RETURN_OK if successful.
 * @retval RETURN_ERR if any error is detected.
 */
INT wifi_getBSSTransitionActivation(UINT apIndex, BOOL *activate);

/* @description Set the neighbor report capability to activated or deactivated,
 * same as enabled or disabled.  The word "activated" is used here because
 * that's what's used in the 802.11 specification.  When deactivate the
 * gateway ignores a neighbor report request as defined in 802.11-2016 section
 * 11.11.10.3.
 *
 * @param apIndex - AP Index the setting applies to.
 * @param activate - True for activate false for deactivate.
 * @return The status of the operation.
 * @retval RETURN_OK if successful.
 * @retval RETURN_ERR if any error is detected.
 */
INT wifi_setNeighborReportActivation(UINT apIndex, BOOL activate);

/* @description Get the neighbor report capability of activated or deactivated,
 * same as enabled or disabled.
 *
 * @param apIndex - AP Index the setting applies to.
 * @param activate - True for activate false for deactivate.
 * @return The status of the operation.
 * @retval RETURN_OK if successful.
 * @retval RETURN_ERR if any error is detected.
 */
INT wifi_getNeighborReportActivation(UINT apIndex, BOOL *activate);

/** @} */  //END OF GROUP WIFI_HAL_APIS

#ifdef __cplusplus
}
#endif

#endif