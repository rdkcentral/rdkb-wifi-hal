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
#ifndef __WIFI_HAL_AP_H__
#define __WIFI_HAL_AP_H__

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @addtogroup WIFI_HAL_TYPES
 * @{
 */

typedef struct _wifi_trafficStats
{
     ULONG wifi_ErrorsSent;
     ULONG wifi_ErrorsReceived;
     ULONG wifi_UnicastPacketsSent;
     ULONG wifi_UnicastPacketsReceived;
     ULONG wifi_DiscardedPacketsSent;
     ULONG wifi_DiscardedPacketsReceived;
     ULONG wifi_MulticastPacketsSent;
     ULONG wifi_MulticastPacketsReceived;
     ULONG wifi_BroadcastPacketsSent;
     ULONG wifi_BroadcastPacketsRecevied;
     ULONG wifi_UnknownPacketsReceived;
} wifi_trafficStats_t;


typedef enum {
    wifi_ipv4_field_values_not_available,
    wifi_ipv4_field_values_available,
    wifi_ipv4_field_values_post_restricted,
    wifi_ipv4_field_values_single_nated_private,
    wifi_ipv4_field_values_double_nated_private,
    wifi_ipv4_field_values_port_restricted_single_nated,
    wifi_ipv4_field_values_port_restricted_double_nated,
    wifi_ipv4_field_values_not_known
} wifi_ipv4_field_values_t;

typedef enum {
    wifi_ipv6_field_values_not_available,
    wifi_ipv6_field_values_available,
    wifi_ipv6_field_values_not_known
} wifi_ipv6_field_values_t;

typedef struct {
    UCHAR   field_format;
}__attribute__((packed)) wifi_ipAddressAvailabality_t;

typedef enum {
    wifi_auth_id_reserved,
    wifi_auth_id_expanded_eap,
    wifi_auth_id_inner_auth_eap,
    wifi_auth_id_expanded_inner_auth_eap,
    wifi_auth_id_credential_type,
    wifi_auth_id_tunneled_eap,
}wifi_auth_id_t;

typedef struct {
    UCHAR  id;
    UCHAR   length;
    UCHAR   val[16];
}__attribute__((packed)) wifi_authMethod_t;

typedef struct {
    UCHAR   length;
    UCHAR   method;
    UCHAR   auth_param_count;
    wifi_authMethod_t   auth_method[16];
}__attribute__((packed)) wifi_eapMethod_t;

typedef struct {
    USHORT            data_field_length;
    UCHAR             encoding;
    UCHAR             realm_length;
    UCHAR             realm[256];
    UCHAR             eap_method_count;
    wifi_eapMethod_t  eap_method[16];
} __attribute__((packed))wifi_naiRealm_t;

typedef struct {
    USHORT nai_realm_count;
    wifi_naiRealm_t nai_realm_tuples[20];
}__attribute__((packed)) wifi_naiRealmElement_t;

typedef struct {
    UCHAR    length;
    UCHAR    language[3];
    UCHAR    name[256];
}__attribute__((packed)) wifi_venueName_t;

typedef struct {
    UCHAR            venueGroup;
    UCHAR            venueType;
    wifi_venueName_t venueNameTuples[16];
}__attribute__((packed)) wifi_venueNameElement_t;

typedef struct {
    UCHAR   PLMN[3];
}__attribute__((packed)) wifi_plmn_t;

typedef struct {
    UCHAR   iei;//copy zero for now.
    UCHAR   plmn_length;
    UCHAR number_of_plmns;
    wifi_plmn_t plmn[16];
}__attribute__((packed))wifi_3gpp_plmn_list_information_element_t;

typedef struct {
    UCHAR   gud;
    UCHAR   uhdLength;//Length of remaining fields
    wifi_3gpp_plmn_list_information_element_t plmn_information;
}__attribute__((packed)) wifi_3gppCellularNetwork_t;

typedef struct {
    UCHAR length;
    UCHAR domainName[255]; //max domain name allowed based on the spec.
}__attribute__((packed)) wifi_domainNameTuple_t;
  
typedef struct {
    wifi_domainNameTuple_t  domainNameTuple[4];
}__attribute__((packed)) wifi_domainName_t;

typedef struct {
    UCHAR length;
    UCHAR oui[15];
}__attribute__((packed)) wifi_ouiDuple_t;

typedef struct {
    wifi_ouiDuple_t ouiDuple[32];
}__attribute__((packed)) wifi_roamingConsortium_t;

typedef struct {
    USHORT capabilityList[64];
}__attribute__((packed)) wifi_capabilityListANQP_t;

typedef struct {
    UCHAR    wifiRoamingConsortiumCount;
    UCHAR    wifiRoamingConsortiumOui[3][15+1];//only 3 OIS is allowed in beacon and probe responses OIS length is variable between 3-15
    UCHAR    wifiRoamingConsortiumLen[3];
}__attribute__((packed)) wifi_roamingConsortiumElement_t;

//HS2 Related ANQP Elements start

//=========================================Start-HS-Operator Friendly Name=========================================================================
//HS2.0 Operator Name Duple #1     HS2.0 Operator Name Duple #2        ......    HS2.0 Operator Name Duple #n
//           variable                            variable                                      variable

//HS2.0 Operator name Duple
//Length                                  Language Code                                     Operator Name
//   1   (3+ operator name)                   3                                               variable

typedef struct _wifi_HS2_OperatorNameDuple_t // figure 9-595
{
    UCHAR length; //length is 3(language code)+number of octects in operator name field  eg. operatorName= aaaa length is 4+3 = 7
    UCHAR languageCode[3];
    UCHAR operatorName[252]; //based on spec the maximum length of operator name is 252
} __attribute__((packed)) wifi_HS2_OperatorNameDuple_t;

typedef struct
{
    wifi_HS2_OperatorNameDuple_t operatorNameDuple[16]; //putting 16 duples supported for now story RDKB-1317 does not tell how many duples we are supporting nor the spec (spec mentions n duples)
} __attribute__((packed)) wifi_HS2_OperatorFriendlyName_t;

//=========================================End-HS2-Operator Friendly Name=========================================================================

//=========================================Start-HS2-Wan Metrics Element=========================================================================
//WAN Info                 Downlink Speed           Uplink Speed     Downlink Load       Uplink Load        LMD
//   1                            4                       4                  1                1               2
typedef struct // figure 9-595
{
    UCHAR wanInfo;
    UINT downLinkSpeed;
    UINT upLinkSpeed;
    UCHAR downLinkLoad;
    UCHAR upLinkLoad;
    USHORT lmd;
} __attribute__((packed)) wifi_HS2_WANMetrics_t;

//WAN Info Bit fields
//        B0     B1                  B2                      B3                 B4    B7
//        Link Status              Symetric Link          At Capacity          Reserved
//Bits:        2                        1                    1                     4
typedef enum
{
    wifi_hs2_wan_info_reserved,
    wifi_hs2_wan_info_linkup,
    wifi_hs2_wan_info_linkdown,
    wifi_hs2_wan_info_link_in_test_state
} wifi_HS2_Wan_Info_Link_Status_t;

//=========================================End-HS2-Wan Metrics Element=========================================================================

//=========================================Start-HS2-Connection Capability Element=========================================================================

//Proto Port Tuple #1        Proto Port Tuple #2  ............. Proto Port Tuple #n
//         4                        4(optional)                   4(optional)

//Proto Port Tuple Format
//IP Protocol                             Port Number                  Status
//     1                                       2                         1

typedef struct // figure 9-595
{
    UCHAR ipProtocol;
    USHORT portNumber;
    UCHAR status;
} __attribute__((packed)) wifi_HS2_Proto_Port_Tuple_t;

typedef struct // figure 9-595
{
    wifi_HS2_Proto_Port_Tuple_t protoPortTuple[16];//putting 16 duples supported for now. story RDKB-1317 does not tell how many duples we are supporting nor the spec (spec mentions n duples)
} __attribute__((packed)) wifi_HS2_ConnectionCapability_t;

typedef enum
{
    wifi_hs2_connection_capability_closed,
    wifi_hs2_connection_capability_open,
    wifi_hs2_connection_capability_unknown,
    wifi_hs2_connection_capability_reserved
} wifi_HS2_ConnectionCapability_Status_t;

    //=========================================End-HS2-Connection Capability Element=========================================================================

    //=========================================Start-HS2-NAI Realm Query Element=========================================================================

    //NAI Realm Count                          NAI Home Realm                    NAI Home Realm   ....  NAI Home Realm
    //                                         Name Data #1                        Name Data #2            Name Data #n
    //      1                                   variable                         (variable optional)       (variable optional)

    //NAI Realm Encoding                                 NAI Home Realm Name Length              NAI Home Realm
    //         1                                                      1                               variable
typedef struct// figure 9-595
{
    UCHAR encoding;
    UCHAR length;
    UCHAR name[255];//per spec maximum length is 255
} __attribute__((packed)) wifi_HS2_NAI_Home_Realm_Data_t;

typedef struct// figure 9-595
{
    UCHAR realmCount;
    wifi_HS2_NAI_Home_Realm_Data_t homeRealmData[20];//as realm count is unsigned char we can put 255 realms here spec says n story does not define how many we support
} __attribute__((packed)) wifi_HS2_NAI_Home_Realm_Query_t;

//=========================================End-HS2-NAI Realm Query Element=========================================================================

//=========================================Start-HS-Capability List=========================================================================
//HS2.0 Capability #1     HS2.0 Capability #2        ......    HS2.0 Capability #n
//            1             0 or 1 (optional)                      0 or 1 (optional)
//=========================================End-HS-Capability List=========================================================================
typedef struct
{
    UCHAR capabilityList[64];
} __attribute__((packed)) wifi_HS2_CapabilityList_t;

typedef struct {
    unsigned char   descriptor;
    unsigned char   key_info[2];
    unsigned short  key_len;
    unsigned char   replay[8];
    unsigned char   nonce[32];
    unsigned char   init_vector[16];
    unsigned char   rsc[8];
    unsigned char   key_id[8];
    unsigned char   mic[16];
    unsigned short  len;
    unsigned char   data[0];
} wifi_eapol_key_frame_t;

typedef enum {
    wifi_eap_code_request = 1,
    wifi_eap_code_response,
    wifi_eap_code_success,
    wifi_eap_code_failure,
} wifi_eap_code_t;

typedef struct {
    unsigned char   code;
    unsigned char   id;
    unsigned short  len;
    unsigned char   data[0];
} __attribute__((__packed__)) wifi_eap_frame_t;

typedef enum {
    wifi_eapol_type_eap_packet,
    wifi_eapol_type_eapol_start,
    wifi_eapol_type_eapol_logoff,
    wifi_eapol_type_eapol_key,
} wifi_eapol_type_t;

typedef struct {
    unsigned char   version;
    unsigned char   type;
    unsigned short  len;
    unsigned char   data[0];
} __attribute__((__packed__)) wifi_8021x_frame_t;

typedef enum {
    wifi_direction_unknown,
    wifi_direction_uplink,
    wifi_direction_downlink
} wifi_direction_t;

/**
 * @brief RADIUS Server information.
 *
 * Structure which holds the the RADIUS server settings.
 */
typedef struct _wifi_radius_setting_t
{
     INT  RadiusServerRetries;          /**< Number of retries for Radius requests. */
     INT  RadiusServerRequestTimeout;   /**< Radius request timeout in seconds after which the request must be retransmitted for the # of retries available.     */
     INT  PMKLifetime;                  /**< Default time in seconds after which a Wi-Fi client is forced to ReAuthenticate (def 8 hrs)      */
     BOOL PMKCaching;                   /**< Enable or disable caching of PMK.     */
     INT  PMKCacheInterval;             /**< Time interval in seconds after which the PMKSA (Pairwise Master Key Security Association) cache is purged (def 5 minutes).     */
     INT  MaxAuthenticationAttempts;    /**< Indicates the # of time, a client can attempt to login with incorrect credentials. When this limit is reached, the client is blacklisted and not allowed to attempt loging into the network. Settings this parameter to 0 (zero) disables the blacklisting feature. */
     INT  BlacklistTableTimeout;        /**< Time interval in seconds for which a client will continue to be blacklisted once it is marked so.  */
     INT  IdentityRequestRetryInterval; /**< Time Interval in seconds between identity requests retries. A value of 0 (zero) disables it    */
     INT  QuietPeriodAfterFailedAuthentication;  /**< The enforced quiet period (time interval) in seconds following failed authentication. A value of 0 (zero) disables it. */
     //UCHAR RadiusSecret[64];          //<! The secret used for handshaking with the RADIUS server [RFC2865]. When read, this parameter returns an empty string, regardless of the actual value.
         
} wifi_radius_setting_t;

/**
 * @brief Represents the wifi scan modes.
 */
typedef enum
{
    WIFI_RADIO_SCAN_MODE_NONE = 0,
    WIFI_RADIO_SCAN_MODE_FULL,
    WIFI_RADIO_SCAN_MODE_ONCHAN,
    WIFI_RADIO_SCAN_MODE_OFFCHAN,
    WIFI_RADIO_SCAN_MODE_SURVEY
} wifi_neighborScanMode_t;

/**
 * @brief Eap types
 */
typedef enum {
    WIFI_EAP_TYPE_NONE = 0,
    WIFI_EAP_TYPE_IDENTITY = 1 /* RFC 3748 */,
    WIFI_EAP_TYPE_NOTIFICATION = 2 /* RFC 3748 */,
    WIFI_EAP_TYPE_NAK = 3 /* Response only, RFC 3748 */,
    WIFI_EAP_TYPE_MD5 = 4, /* RFC 3748 */
    WIFI_EAP_TYPE_OTP = 5 /* RFC 3748 */,
    WIFI_EAP_TYPE_GTC = 6, /* RFC 3748 */
    WIFI_EAP_TYPE_TLS = 13 /* RFC 2716 */,
    WIFI_EAP_TYPE_LEAP = 17 /* Cisco proprietary */,
    WIFI_EAP_TYPE_SIM = 18 /* RFC 4186 */,
    WIFI_EAP_TYPE_TTLS = 21 /* RFC 5281 */,
    WIFI_EAP_TYPE_AKA = 23 /* RFC 4187 */,
    WIFI_EAP_TYPE_PEAP = 25 /* draft-josefsson-pppext-eap-tls-eap-06.txt */,
    WIFI_EAP_TYPE_MSCHAPV2 = 26 /* draft-kamath-pppext-eap-mschapv2-00.txt */,
    WIFI_EAP_TYPE_TLV = 33 /* draft-josefsson-pppext-eap-tls-eap-07.txt */,
    WIFI_EAP_TYPE_TNC = 38 /* TNC IF-T v1.0-r3; note: tentative assignment;
                            * type 38 has previously been allocated for
                            * EAP-HTTP Digest, (funk.com) */,
    WIFI_EAP_TYPE_FAST = 43 /* RFC 4851 */,
    WIFI_EAP_TYPE_PAX = 46 /* RFC 4746 */,
    WIFI_EAP_TYPE_PSK = 47 /* RFC 4764 */,
    WIFI_EAP_TYPE_SAKE = 48 /* RFC 4763 */,
    WIFI_EAP_TYPE_IKEV2 = 49 /* RFC 5106 */,
    WIFI_EAP_TYPE_AKA_PRIME = 50 /* RFC 5448 */,
    WIFI_EAP_TYPE_GPSK = 51 /* RFC 5433 */,
    WIFI_EAP_TYPE_PWD = 52 /* RFC 5931 */,
    WIFI_EAP_TYPE_EKE = 53 /* RFC 6124 */,
    WIFI_EAP_TYPE_TEAP = 55 /* RFC 7170 */,
    WIFI_EAP_TYPE_EXPANDED = 254 /* RFC 3748 */
} wifi_eap_t;

/** @} */  //END OF GROUP WIFI_HAL_TYPES

/**
 * @addtogroup WIFI_HAL_APIS
 * @{
 */

/* wifi_getApAssociatedDevice() function */
/**
* @brief Gets the ApAssociatedDevice list for client MAC addresses
*
* @param[in]  apIndex                         - Access Point index
* @param[out] output_deviceMacAddressArray    - List of devices MAC, to be returned
* @param[in]  maxNumDevices                   - Max number of devices that can be returned
* @param[out] output_numDevices               - Number of entries returned in the array
*
* @return The status of the operation
* @retval WIFI_HAL_SUCCESS if successful
* @retval Error code if any error is detected (WIFI_HAL_ERROR, WIFI_HAL_UNSUPPORTED, etc)
*
* @execution Synchronous
* @sideeffect None
*
*/
INT wifi_getApAssociatedDevice(INT ap_index, mac_address_t *output_deviceMacAddressArray, UINT maxNumDevices, UINT *output_numDevices);

/* wifi_enableCSIEngine() function */
/*
 * Description: This function enables or disables CSI engine data for a specific STA on a VAP
 * If the MAC address is NULL mac address, enable argument MUST be false, otherwise function MUST return failure.
 * If the MAC address is NULL mac address, data engine for all STA(s) need to be disabled on this VAP
 *
 * Parameters :
 * apIndex  - Index of VAP
 * sta      - MAC address of the station associated in this VAP for which engine is being enabled/disabled
 * enable   - Enable or diable
 *
 * @return The status of the operation.
 * @retval RETURN_OK if successful.
 * @retval RETURN_ERR if any error is detected
 *
 * @execution Synchronous.
 * @sideeffect None.
 *
 */

INT wifi_enableCSIEngine(INT apIndex,
                         mac_address_t sta,
                         BOOL enable);


INT wifi_getWifiTrafficStats(INT apIndex, wifi_trafficStats_t *output_struct); //!< Outputs more detailed traffic stats per AP

/* wifi_factoryResetAP() function */
/**
* @brief Restore Access point paramters to default without change other AP nor Radio parameters (No need to reboot wifi)
*
* @param[in] apIndex  Access Point index
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
INT wifi_factoryResetAP(int apIndex); 

/* wifi_deleteAp() function */
/**
* @brief Deletes this access point entry on the hardware, clears all internal variables associated with this access point.
*
* @param[in] apIndex  Access Point index
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
INT wifi_deleteAp(INT apIndex);                                     // deletes this ap entry on the hardware, clears all internal variables associaated with this ap

/* wifi_getApName() function */
/**
* @brief Outputs a 16 byte or less name associated with the Access Point.
* String buffer must be pre-allocated by the caller.
*
* @param[in]  apIndex         Access Point index
* @param[out] output_string   Access Point name, to be returned
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
INT wifi_getApName(INT apIndex, CHAR *output_string);                 // Outputs a 16 byte or less name assocated with the AP.  String buffer must be pre-allocated by the caller

/* wifi_setApRtsThreshold() function */
/**
* @brief Sets the packet size threshold in bytes to apply RTS/CTS backoff rules.
*
* @param[in] apIndex    Access Point index
* @param[in] threshold  Packet size threshold 
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
INT wifi_setApRtsThreshold(INT apIndex, UINT threshold);              // sets the packet size threshold in bytes to apply RTS/CTS backoff rules. 

/* wifi_removeApSecVaribles() function */
/**
* @brief Deletes internal security variable settings for this access point.
*
* @param[in] apIndex  Access Point index
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
INT wifi_removeApSecVaribles(INT apIndex);                            // deletes internal security varable settings for this ap

/* wifi_disableApEncryption() function */
/**
* @brief Changes the hardware settings to disable encryption on this access point.
*
* @param[in] apIndex  Access Point index
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
INT wifi_disableApEncryption(INT apIndex);                            // changes the hardware settings to disable encryption on this ap

/* wifi_getApNumDevicesAssociated() function */
/**
* @brief Outputs the number of stations associated per Access Point.
*
* @param[in]  apIndex       Access Point index
* @param[out] output_ulong  Number of stations, to be returned
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
INT wifi_getApNumDevicesAssociated(INT apIndex, ULONG *output_ulong); // Outputs the number of stations associated per AP

#ifdef WIFI_HAL_VERSION_3_PHASE2
/* wifi_kickApAssociatedDevice() function */
/**
* @brief Manually removes any active wi-fi association with the device specified on this access point.
*
* @param[in] apIndex     Access Point index
* @param[in] client_mac  Client device MAC address
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
INT wifi_kickApAssociatedDevice(INT apIndex, mac_address_t client_mac);      // manually removes any active wi-fi association with the device specified on this ap
#endif

/* wifi_getApRadioIndex() function */
/**
* @brief Outputs the radio index for the specified access point.
*
* @param[in]  apIndex     Access Point index
* @param[out] output_int  Radio index, to be returned
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
INT wifi_getApRadioIndex(INT apIndex, INT *output_int);                // outputs the radio index for the specified ap

/* wifi_getApAclDevices() function */
/**
* @brief Get the ACL MAC list per Access Point.
*
* @param[in]  apIndex   Access Point index
* @param[out] macArray  Mac Array list, to be returned // in formate as "11:22:33:44:55:66\n11:22:33:44:55:67\n"
* @param[in] maxArraySize                     Array size
* @param[out] output_numEntries                size list returned
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
#ifdef WIFI_HAL_VERSION_3_PHASE2
INT wifi_getApAclDevices(INT apIndex, mac_address_t *macArray, UINT maxArraySize, UINT* output_numEntries);    // Get the ACL MAC list per AP
#endif

/* wifi_addApAclDevice() function */
/**
* @brief Adds the mac address to the filter list.
*
* @param[in] apIndex            Access Point index
* @param[in] DeviceMacAddress   Mac Address of a device
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
#ifdef WIFI_HAL_VERSION_3_PHASE2
INT wifi_addApAclDevice(INT apIndex, mac_address_t DeviceMacAddress);         // adds the mac address to the filter list
#endif


/**
* @brief Deletes all Device MAC address from the Access control filter list.
*
* @param[in]  apIndex           Access Point index
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous
* @sideeffect None
*
*/
INT wifi_delApAclDevices(INT apINdex);

/* wifi_getApAclDeviceNum() function */
/**
* @brief Outputs the number of devices in the filter list.
*
* @param[in]  apIndex      Access Point index
* @param[out] output_uint  Number of devices, to be returned
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
INT wifi_getApAclDeviceNum(INT apIndex, UINT *output_uint);           // outputs the number of devices in the filter list

/* wifi_kickApAclAssociatedDevices() function */
/**
* @brief Enable kick for devices on acl black list.
*
* @param[in] apIndex  Access Point index
* @param[in] enable   Enable/disable kick for devices on acl black list
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
INT wifi_kickApAclAssociatedDevices(INT apIndex,BOOL enable);         // enable kick for devices on acl black list

/* wifi_kickApAclAssociatedDevices() function */
/**
* @brief Enable kick for devices on acl black list.
*
* @param[in] apIndex  Access Point index
* @param[in] enable   Enable/disable kick for devices on acl black list
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
INT wifi_kickApAclAssociatedDevices(INT apIndex,BOOL enable);         // enable kick for devices on acl black list

/* wifi_setApMacAddressControlMode() function */
/**
* @brief Sets the mac address filter control mode.
*
* - 0 : filter as  disabled
* - 1 : filter as whitelist
* - 2 : filter as blacklist.
*
* @param[in] apIndex      Access Point index
* @param[in] filterMode   Mac Address filter control mode
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
INT wifi_setApMacAddressControlMode(INT apIndex, INT filterMode);     // sets the mac address filter control mode.  0 == filter disabled, 1 == filter as whitelist, 2 == filter as blacklist

/**
* @brief This function is to read the ACL mode.
*
* @param[in]  apIndex             Access Point index
* @param[out] output_filterMode   Mac Address control mode
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
INT wifi_getApMacAddressControlMode(INT apIndex, INT *output_filterMode);

/* wifi_setApVlanID() function */
/**
* @brief Sets the vlan ID for this access point to an internal environment variable.
*
* @param[in] apIndex Access Point index
* @param[in] vlanId  VLAN ID
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
INT wifi_setApVlanID(INT apIndex, INT vlanId);                        // sets the vlan ID for this ap to an internal environment variable


/* wifi_resetApVlanCfg() function */
/**
* @brief Reset the vlan configuration for this access point.
*
* @param[in] apIndex  Access Point index
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
INT wifi_resetApVlanCfg(INT apIndex);                                 // reset the vlan configuration for this ap

/* wifi_setApEnable() function */
/**
* @brief Sets the Access Point enable status variable for the specified access point.
*
* @param[in] apIndex  Access Point index
* @param[in] enable   Enable/Disable AP enable status variable
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
INT wifi_setApEnable(INT apIndex, BOOL enable);                       // sets the AP enable status variable for the specified ap.

/* wifi_getApEnable() function */
/**
* @brief Outputs the setting of the internal variable that is set by wifi_setEnable().
*
* @param[in]  apIndex      Access Point index
* @param[out] output_bool  AP enable status, to be returned
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
INT wifi_getApEnable(INT apIndex, BOOL *output_bool);                 // Outputs the setting of the internal variable that is set by wifi_setEnable().  


/* wifi_getApStatus() function */
/**
* @brief Outputs the AP "Enabled" "Disabled" status from driver.
*
* @param[in]  apIndex        Access Point index
* @param[out] output_string  AP status, to be returned
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
INT wifi_getApStatus(INT apIndex, CHAR *output_string);// Outputs the AP "Enabled" "Disabled" status from driver 


/* wifi_getApSsidAdvertisementEnable() function */
/**
* @brief Indicates whether or not beacons include the SSID name.
*
* Outputs 1 if SSID on the AP is enabled, else ouputs 0.
*
* @param[in]  apIndex      Access Point index
* @param[out] output_bool  SSID Advertisement enabled, to be returned
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
//Indicates whether or not beacons include the SSID name.
INT wifi_getApSsidAdvertisementEnable(INT apIndex, BOOL *output_bool);// outputs a 1 if SSID on the AP is enabled, else ouputs 0

/* wifi_setApSsidAdvertisementEnable() function */
/**
* @brief Sets an internal variable for ssid advertisement.
*
* Set to 1 to enable, set to 0 to disable.
*
* @param[in] apIndex  Access Point index
* @param[in] enable   SSID Advertisement enable value
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
INT wifi_setApSsidAdvertisementEnable(INT apIndex, BOOL enable);      // sets an internal variable for ssid advertisement.  Set to 1 to enable, set to 0 to disable

/* wifi_getApRetryLimit() function */
/**
* @brief Get the maximum number of retransmission for a packet.
*
* This corresponds to IEEE 802.11 parameter dot11ShortRetryLimit.
*
* @param[in]  apIndex  Access Point index
* @param[out] output   Maximum number of retransmission for a packet, to be returned
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
//The maximum number of retransmission for a packet. This corresponds to IEEE 802.11 parameter dot11ShortRetryLimit.
INT wifi_getApRetryLimit(INT apIndex, UINT *output); 

/* wifi_setApRetryLimit() function */
/**
* @brief Set the maximum number of retransmission for a packet.
*
* This corresponds to IEEE 802.11 parameter dot11ShortRetryLimit.
*
* @param[in] apIndex  Access Point index
* @param[in] number   Maximum number of retransmission for a packet
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
INT wifi_setApRetryLimit(INT apIndex, UINT number); 

/* wifi_getApWmmEnable() function */
/**
* @brief Indicates whether WMM support is currently enabled.
*
* When enabled, this is indicated in beacon frames.
*
* @param[in]  apIndex  Access Point index
* @param[out] output   WMM support enabled status, to be returned
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
//Whether WMM support is currently enabled. When enabled, this is indicated in beacon frames.
INT wifi_getApWmmEnable(INT apIndex, BOOL *output);                   

/* wifi_setApWmmEnable() function */
/**
* @brief Enables/disables WMM on the hardwawre for this AP.  enable==1, disable == 0.
*
* @param[in] apIndex  Access Point index
* @param[in] enable   WMM support enabled status
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
INT wifi_setApWmmEnable(INT apIndex, BOOL enable);                    // enables/disables WMM on the hardwawre for this AP.  enable==1, disable == 0

/* wifi_getApWmmUapsdEnable() function */
/**
* @brief Indicates whether U-APSD support is currently enabled.
*
* When enabled, this is indicated in beacon frames.
* U-APSD can only be enabled if WMM is also enabled.
*
* @param[in]  apIndex  Access Point index
* @param[out] output   U-APSD support enabled status, to be returned
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
//Whether U-APSD support is currently enabled. When enabled, this is indicated in beacon frames. Note: U-APSD can only be enabled if WMM is also enabled.
INT wifi_getApWmmUapsdEnable(INT apIndex, BOOL *output);               

/* wifi_setApWmmUapsdEnable() function */
/**
* @brief Enables/disables Automatic Power Save Delivery on the hardwarwe for this Access Point.
*
* @param[in] apIndex  Access Point index
* @param[in] enable   U-APSD enable/disable value
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
INT wifi_setApWmmUapsdEnable(INT apIndex, BOOL enable);               // enables/disables Automatic Power Save Delivery on the hardwarwe for this AP

/* wifi_setApWmmOgAckPolicy() function */
/**
* @brief Sets the WMM ACK policy on the hardware.
*
* AckPolicy false means do not acknowledge, true means acknowledge.
*
* @param[in] apIndex    Access Point index
* @param[in] class
* @param[in] ackPolicy  Acknowledge policy
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
// Sets the WMM ACK polity on the hardware. AckPolicy false means do not acknowledge, true means acknowledge
INT wifi_setApWmmOgAckPolicy(INT apIndex, INT cla, BOOL ackPolicy);
            
/* wifi_getApIsolationEnable() function */
/**
* @brief Get Access Point isolation value.
*
* A value of true means that the devices connected to the Access Point are isolated
* from all other devices within the home network (as is typically the case for a Wireless Hotspot).
*
* @param[in]  apIndex  Access Point index
* @param[out] output   Access Point Isolation enable, to be returned
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
//Enables or disables device isolation.    A value of true means that the devices connected to the Access Point are isolated from all other devices within the home network (as is typically the case for a Wireless Hotspot).    
INT wifi_getApIsolationEnable(INT apIndex, BOOL *output); 

/* wifi_setApIsolationEnable() function */
/**
* @brief Enables or disables device isolation.
*
* A value of true means that the devices connected to the Access Point are isolated
* from all other devices within the home network (as is typically the case for a Wireless Hotspot).
*
* @param[in] apIndex  Access Point index
* @param[in] enable   Access Point Isolation enable value 
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
INT wifi_setApIsolationEnable(INT apIndex, BOOL enable);


/**
* @brief Set Access Point Beacon TX rate.
*
* @param[in] apIndex      Access point index will be 0, 2,4,6,8 10, 12, 14(for 2.4G) only;
* @param[in] sBeaconRate  sBeaconRate could be "1Mbps"; "5.5Mbps"; "6Mbps"; "2Mbps"; "11Mbps"; "12Mbps"; "24Mbps"
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
INT wifi_setApBeaconRate(INT apIndex, char *sBeaconRate);

/**
* @brief Get Access Point  Beacon TX rate.
*
* @param[in]  apIndex             Index of Wi-Fi Access Point
* @param[out] output_BeaconRate   Beacon rate output
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
INT wifi_getApBeaconRate(INT apIndex, char *output_BeaconRate);
    

/* wifi_getApMaxAssociatedDevices() function */
/**
* @brief Get maximum associated devices with the Access Point index.
*
* The maximum number of devices that can simultaneously be connected to the access point.
* A value of 0 means that there is no specific limit.
*
* @param[in]  apIndex  Access Point index
* @param[out] output   Maximum associated devices, to be returned
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
//The maximum number of devices that can simultaneously be connected to the access point. A value of 0 means that there is no specific limit.            
INT wifi_getApMaxAssociatedDevices(INT apIndex, UINT *output);

/* wifi_setApMaxAssociatedDevices() function */
/**
* @brief Set maximum associated devices with the Access Point index.
*
* The maximum number of devices that can simultaneously be connected to the access point.
* A value of 0 means that there is no specific limit.
*
* @param[in] apIndex  Access Point index
* @param[in] number   Maximum associated devices
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
INT wifi_setApMaxAssociatedDevices(INT apIndex, UINT number);

/* wifi_setApSecurityReset() function */
/**
* @brief When set to true, this AccessPoint instance's WiFi security settings are reset to their factory default values.
*
* The affected settings include ModeEnabled, WEPKey, PreSharedKey and KeyPassphrase.
*
* @param[in] apIndex  Access Point index
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
//When set to true, this AccessPoint instance's WiFi security settings are reset to their factory default values. The affected settings include ModeEnabled, WEPKey, PreSharedKey and KeyPassphrase.
INT wifi_setApSecurityReset(INT apIndex);

/* wifi_getApSecurityMFPConfig() function */
/**
* @brief To retrive the MFPConfig for each VAP
*
* @param[in] apIndex  Access Point index
* @param[out] output_string. Preallocated buffer for 64bytes. Allowed output string are "Disabled", "Optional", "Required"
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
INT wifi_getApSecurityMFPConfig(INT apIndex, CHAR *output_string);

/* wifi_setApSecurityMFPConfig() function */
/**
* @brief the hal is used to set the MFP config for each VAP.
*        1. mfpconfig need to be saved into wifi config in persistent way (so that it could be automatically applied after the wifi or vap restart)
*        2. mfpconfig need to be applied right away.
*
* @param[in] apIndex  Access Point index
* @param[in] MfpConfig,  The allowed string for MFPConfig are "Disabled", "Optional", "Required"
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
INT wifi_setApSecurityMFPConfig(INT apIndex, CHAR *MfpConfig);


/* wifi_getApSecurityRadiusServer() function */
/**
* @brief Get the IP Address and port number of the RADIUS server, which are used for WLAN security.
*
* RadiusServerIPAddr is only applicable when ModeEnabled is an Enterprise type
* (i.e. WPA-Enterprise, WPA2-Enterprise or WPA-WPA2-Enterprise).
*  String is 64 bytes max.
*
* @param[in]  Index                 Access Point index
* @param[out] IP_output             IP Address, to be returned
* @param[out] Port_output           Port output, to be returned
* @param[out] RadiusSecret_output   Radius Secret output, to be returned
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
//The IP Address and port number of the RADIUS server used for WLAN security. RadiusServerIPAddr is only applicable when ModeEnabled is an Enterprise type (i.e. WPA-Enterprise, WPA2-Enterprise or WPA-WPA2-Enterprise).  String is 64 bytes max
INT wifi_getApSecurityRadiusServer(INT apIndex, CHAR *IP_output, UINT *Port_output, CHAR *RadiusSecret_output); 

/* wifi_setApSecurityRadiusServer() function */
/**
* @brief Set the IP Address and port number of the RADIUS server, which are used for WLAN security.
*
* RadiusServerIPAddr is only applicable when ModeEnabled is an Enterprise type
* (i.e. WPA-Enterprise, WPA2-Enterprise or WPA-WPA2-Enterprise). String is 64 bytes max.
*
* @param[in] apIndex       Access Point index
* @param[in] IPAddress     IP Address
* @param[in] port          Port 
* @param[in] RadiusSecret  Radius Secret
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
INT wifi_setApSecurityRadiusServer(INT apIndex, CHAR *IPAddress, UINT port, CHAR *RadiusSecret);

/* wifi_getApSecuritySecondaryRadiusServer() function */
/**
* @brief Get secondary IP Address, port number and RADIUS server.
*
* Used for WLAN security.
* RadiusServerIPAddr is only applicable when ModeEnabled is an Enterprise type
* (i.e. WPA-Enterprise, WPA2-Enterprise or WPA-WPA2-Enterprise).
* String is 64 bytes max.
*
* @param[in]   apIndex               Access Point index
* @param[out]  IP_output             IP Address, to be returned
* @param[out]  Port_output           Port,to be returned
* @param[out]  RadiusSecret_output   Radius Secret, to be returned
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
INT wifi_getApSecuritySecondaryRadiusServer(INT apIndex, CHAR *IP_output, UINT *Port_output, CHAR *RadiusSecret_output);

/* wifi_setApSecuritySecondaryRadiusServer() function */
/**
* @brief Set secondary IP Address, port number and RADIUS server, which are used for WLAN security.
*
* RadiusServerIPAddr is only applicable when ModeEnabled is an Enterprise type
* (i.e. WPA-Enterprise, WPA2-Enterprise or WPA-WPA2-Enterprise).
* String is 64 bytes max.
*
* @param[in]  apIndex       Access Point index
* @param[in]  IPAddress     IP Address
* @param[in]  port          Port
* @param[in]  RadiusSecret  Radius Secret
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
INT wifi_setApSecuritySecondaryRadiusServer(INT apIndex, CHAR *IPAddress, UINT port, CHAR *RadiusSecret);


/*wifi_getApDASRadiusServer function
* @brief Get the IP Address and port number of the RADIUS DAS server, which are used for WLAN security.
*
* Device.WiFi.AccessPoint.{i}.Security.RadiusDASIPAddr
* Device.WiFi.AccessPoint.{i}.Security.RadiusDASPort
* Device.WiFi.AccessPoint.{i}.Security.RadiusDASSecret

* @param[in] apIndex                 Access Point index
* @param[in] IP_output               IP Address
* @param[in] Port_output             Port
* @param[in] RadiusdasSecret_output  Radius DAS Secret
*
* Radius DAS Secret is not applicable for open ssid
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
INT wifi_getApDASRadiusServer(INT apIndex, CHAR *IP_output, UINT *Port_output, CHAR *RadiusdasSecret_output);

/* wifi_setApDASRadiusServer() function */
/**
* @brief Set the IP Address and port number of the RADIUS DAS server, which are used for WLAN security.
*
* Device.WiFi.AccessPoint.{i}.Security.RadiusDASIPAddr
* Device.WiFi.AccessPoint.{i}.Security.RadiusDASPort
* Device.WiFi.AccessPoint.{i}.Security.RadiusDASSecret
*
* @param[in] IPAddress     IP Address
* @param[in] port          Port
* @param[in] RadiusdasSecret  Radius Secret
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
INT wifi_setApDASRadiusServer(INT apIndex, CHAR *IPAddress, UINT port, CHAR *RadiusdasSecret); //Tr181

/**
* @brief This function is to enable or disable
grey list Access Control on all applicable VAP
*
* @param[in]  enable             enable access control if true, disable if false
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous
* @sideeffect None
*
* @note This function must not suspend and must not
invoke any blocking system
* calls.
*
*/
INT wifi_enableGreylistAccessControl(BOOL enable);

/* wifi_getApSecurityRadiusSettings() function */
/**
* @brief Get Access Point security radius settings.
*
* @param[in]   apIndex  Access Point index
* @param[out]  output   wifi_radius_setting_t info (*output), to be returned
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
INT wifi_getApSecurityRadiusSettings(INT apIndex, wifi_radius_setting_t *output);

/* wifi_setApSecurityRadiusSettings() function */
/**
* @brief Set Access Point security radius settings.
*
* @param[in] apIndex  Access Point index
* @param[in] input    wifi_radius_setting_t info
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
INT wifi_setApSecurityRadiusSettings(INT apIndex, wifi_radius_setting_t *input);

//-----------------------------------------------------------------------------------------------

/* wifi_getApWpsConfigurationState() function */
/**
* @brief Get WPS configuration state.
*
* Output string is either Not configured or Configured, max 32 characters.
*
* @param[in] apIndex        Access Point index
* @param[in] output_string  WPS configuration state, to be returned
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
INT wifi_getApWpsConfigurationState(INT apIndex, CHAR *output_string); // Output string is either Not configured or Configured, max 32 characters

/* wifi_setApWpsEnrolleePin() function */
/**
* @brief Sets the WPS pin for this Access Point.
*
* @param[in] apIndex  Access Point index
* @param[in]  pin     WPS enroll Pin
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
INT wifi_setApWpsEnrolleePin(INT apIndex, CHAR *pin);                 // sets the WPS pin for this AP

/* wifi_setApWpsButtonPush() function */
/**
* @brief This function is called when the WPS push button has been pressed for this AP.
*
* @param[in] apIndex  Access Point index
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
INT wifi_setApWpsButtonPush(INT apIndex);                             // This function is called when the WPS push button has been pressed for this AP

/* wifi_cancelApWPS() function */
/**
* @brief Cancels WPS mode for this Access Point.
*
* @param[in] apIndex  Access Point index
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
INT wifi_cancelApWPS(INT apIndex);                                    // cancels WPS mode for this AP

/* wifi_getApManagementFramePowerControl() function */
/**
* @brief Get the ApManagementFramePowerControl
*
* @param[in]  apIndex      Access Point index
* @param[out] output_dBm   ManagementFramePowerControl, to be returned 
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
INT wifi_getApManagementFramePowerControl(INT apIndex, INT *output_dBm);  // Get the RadioManagementFramePowerControl supported. 

/* wifi_setApManagementFramePowerControl() function */
/**
* @brief Sets the ApManagementFramePowerControl 
*
* @param[in] apIndex  Access Point index
* @param[in] dBm      RadioManagementFramePowerControl
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
INT wifi_setApManagementFramePowerControl(INT apIndex, INT dBm); // sets the RadioManagementFramePowerControl in db
/** @} */  //END OF GROUP WIFI_HAL_APIS

/**
 * @addtogroup WIFI_HAL_TYPES
 * @{
 */
#ifdef WIFI_HAL_VERSION_3_PHASE2
/* wifi_newApAssociatedDevice_callback() function */
/**
* @brief This call back will be invoked when new wifi client come to associate to Access Point.    
*
* @param[in] apIndex          Access Point Index
* @param[in] associated_dev   Associated device info
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
typedef INT(* wifi_newApAssociatedDevice_callback)(INT apIndex, wifi_associated_dev3_t *associated_dev);
#else

typedef struct _wifi_associated_dev
{
    UCHAR cli_MACAddress[6];        /**< The MAC address of an associated device. */
    CHAR  cli_IPAddress[64];        /**< IP of the associated device */
    BOOL  cli_AuthenticationState; /**< Whether an associated device has authenticated (true) or not (false). */
    UINT  cli_LastDataDownlinkRate; /**< The data transmit rate in kbps that was most recently used for transmission from the access point to the associated device. */
    UINT  cli_LastDataUplinkRate;     /**< The data transmit rate in kbps that was most recently used for transmission from the associated device to the access point. */
    INT   cli_SignalStrength;         /**< An indicator of radio signal strength of the uplink from the associated device to the access point, measured in dBm, as an average of the last 100 packets received from the device. */
    UINT  cli_Retransmissions;     /**< The number of packets that had to be re-transmitted, from the last 100 packets sent to the associated device. Multiple re-transmissions of the same packet count as one. */
    BOOL  cli_Active;                 /**<    boolean    -    Whether or not this node is currently present in the WiFi AccessPoint network. */

    CHAR  cli_OperatingStandard[64];    /**< Radio standard the associated Wi-Fi client device is operating under. Enumeration of: */
    CHAR  cli_OperatingChannelBandwidth[64];    /**< The operating channel bandwidth of the associated device. The channel bandwidth (applicable to 802.11n and 802.11ac specifications only). Enumeration of: */
    INT   cli_SNR;        /**< A signal-to-noise ratio (SNR) compares the level of the Wi-Fi signal to the level of background noise. Sources of noise can include microwave ovens, cordless phone, bluetooth devices, wireless video cameras, wireless game controllers, fluorescent lights and more. It is measured in decibels (dB). */
    CHAR  cli_InterferenceSources[64]; /**< Wi-Fi operates in two frequency ranges (2.4 Ghz and 5 Ghz) which may become crowded other radio products which operate in the same ranges. This parameter reports the probable interference sources that this Wi-Fi access point may be observing. The value of this parameter is a comma seperated list of the following possible sources: eg: MicrowaveOven,CordlessPhone,BluetoothDevices,FluorescentLights,ContinuousWaves,Others */
    ULONG cli_DataFramesSentAck;    /**< The DataFramesSentAck parameter indicates the total number of MSDU frames marked as duplicates and non duplicates acknowledged. The value of this counter may be reset to zero when the CPE is rebooted. Refer section A.2.3.14 of CableLabs Wi-Fi MGMT Specification. */
    ULONG cli_DataFramesSentNoAck;    /**< The DataFramesSentNoAck parameter indicates the total number of MSDU frames retransmitted out of the interface (i.e., marked as duplicate and non-duplicate) and not acknowledged, but does not exclude those defined in the DataFramesLost parameter. The value of this counter may be reset to zero when the CPE is rebooted. Refer section A.2.3.14 of CableLabs Wi-Fi MGMT Specification. */
    ULONG cli_BytesSent;    /**< The total number of bytes transmitted to the client device, including framing characters. */
    ULONG cli_BytesReceived;    /**< The total number of bytes received from the client device, including framing characters. */
    INT   cli_RSSI;    /**< The Received Signal Strength Indicator, RSSI, parameter is the energy observed at the antenna receiver for transmissions from the device averaged over past 100 packets recevied from the device. */
    INT   cli_MinRSSI;    /**< The Minimum Received Signal Strength Indicator, RSSI, parameter is the minimum energy observed at the antenna receiver for past transmissions (100 packets). */
    INT   cli_MaxRSSI;    /**< The Maximum Received Signal Strength Indicator, RSSI, parameter is the energy observed at the antenna receiver for past transmissions (100 packets). */
    UINT  cli_Disassociations;    /**< This parameter  represents the total number of client disassociations. Reset the parameter evey 24hrs or reboot */
    UINT  cli_AuthenticationFailures;    /**< This parameter indicates the total number of authentication failures.  Reset the parameter evey 24hrs or reboot */

    UINT cli_CapableNumSpatialStreams; /**< The number of spatial streams supported by the associated client device. */

} wifi_associated_dev_t;    //~COSA_DML_WIFI_AP_ASSOC_DEVICE


typedef INT(* wifi_newApAssociatedDevice_callback)(INT apIndex, wifi_associated_dev_t *associated_dev);

#endif
/** @} */  //END OF GROUP WIFI_HAL_TYPES

/**
 * @addtogroup WIFI_HAL_APIS
 * @{
 */
/* wifi_newApAssociatedDevice_callback_register() function */
/**
* @brief Callback registration function.    
*
* @param[in] callback_proc  wifi_newApAssociatedDevice_callback callback function
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
void wifi_newApAssociatedDevice_callback_register(wifi_newApAssociatedDevice_callback callback_proc);
/** @} */  //END OF GROUP WIFI_HAL_APIS

/**
 * @addtogroup WIFI_HAL_TYPES
 * @{
 */
/* wifi_apDisassociatedDevice_callback() function */
/**
* @brief This call back will be invoked when new wifi client disassociates from Access Point.    
*
* @param[in] apIndex          Access Point Index
* @param[in] MAC                 MAC address of disassociated device
* @param[in] event_type         type of disassociation, explicit or due to client inactivity
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
typedef INT ( * wifi_apDisassociatedDevice_callback)(INT apIndex, char *MAC, INT event_type);
/** @} */  //END OF GROUP WIFI_HAL_TYPES

/**
 * @addtogroup WIFI_HAL_APIS
 * @{
 */
/* wifi_apDisassociatedDevice_callback_register() function */
/**
* @brief Callback registration function.    
*
* @param[in] callback_proc  wifi_apDisassociatedDevice_callback callback function
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
void wifi_apDisassociatedDevice_callback_register(wifi_apDisassociatedDevice_callback callback_proc);
/** @} */  //END OF GROUP WIFI_HAL_APIS

/**
 * @addtogroup WIFI_HAL_TYPES
 * @{
 */
/* wifi_apDeAuthEvent_callback() function */
/**
* @brief This call back will be invoked when DeAuth Event (reason 2 wrong password) comes from client.
*
* @param[in] apIndex          Access Point Index
* @param[in] MAC              MAC address of client device
* @param[in] reason           reason for Auth Event
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
typedef INT ( * wifi_apDeAuthEvent_callback)(int ap_index, char *mac, int reason);
/** @} */  //END OF GROUP WIFI_HAL_TYPES

/**
 * @addtogroup WIFI_HAL_APIS
 * @{
 */
/* wifi_apDeAuthEvent_callback_register() function */
/**
* @brief Callback registration function.
*
* @param[in] callback_proc  wifi_apDeAuthEvent_callback callback function
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous
* @sideeffect None
*/
void wifi_apDeAuthEvent_callback_register(wifi_apDeAuthEvent_callback callback_proc);

INT wifi_setInterworkingAccessNetworkType(INT apIndex, INT accessNetworkType);   // P3
INT wifi_getInterworkingAccessNetworkType(INT apIndex, UINT *output_uint);   // P3

//-----------------------------------------------------------------------------------------------
//Access Network Type value to be included in the Interworking IE in the beaconds. (refer 8.4.2.94 of IEEE Std 802.11-2012). Possible values are: 0 - Private network;1 - Private network with guest access;2 - Chargeable public network;3 - Free public network;4 - Personal device network;5 - Emergency services only network;6-13 - Reserved;14 - Test or experimental;15 - Wildcard
INT wifi_setInterworkingAccessNetworkType(INT apIndex, INT accessNetworkType);   // P3
INT wifi_getInterworkingAccessNetworkType(INT apIndex, UINT *output_uint);   // P3

/** @} */  //END OF GROUP WIFI_HAL_APIS

/**
 * @addtogroup WIFI_HAL_TYPES
 * @{
 */

// Interworking Element structure; see 802.11-2016 section 9.4.2.92 for field definition.
typedef struct {
    BOOL            interworkingEnabled;
    UINT            accessNetworkType;
    BOOL            internetAvailable;
    BOOL            asra;
    BOOL            esr;
    BOOL            uesa;
    BOOL            venueOptionPresent;    /**< True when venue information has not been provided, e.g. the hostspot is in a residence. */
    UCHAR           venueGroup;
    UCHAR           venueType;
    BOOL            hessOptionPresent;
    mac_addr_str_t  hessid;    /**< Optional; use empty string to indicate no value provided. */
} wifi_InterworkingElement_t;

/** @} */  //END OF GROUP WIFI_HAL_TYPES

/**
 * @addtogroup WIFI_HAL_APIS
 * @{
 */
/**
* @brief Get the Interworking Service enable/disable value for the AP.
*
* @param[in] apIndex        Index of the Access Point.
* @param[in] output_bool    Indication as to whether the AP Interworking Service is enabled (true) or disabled (false).
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*/
INT wifi_getApInterworkingServiceEnable(INT apIndex, BOOL *output_bool);

/**
 * @brief Set the Interworking Service enable/disable value for the AP.
 *
 * @param[in] apIndex        Index of the Access Point.
 * @param[in] input_bool        Value to set the Interworking Service enable to, true or false.
 *
 * @return The status of the operation
 * @retval RETURN_OK if successful
 * @retval RETURN_ERR if any error is detected
 */
INT wifi_setApInterworkingServiceEnable(INT apIndex, BOOL input_bool);

/**
 * @brief Get the Interworking Element that will be sent by the AP.
 *
 * @param[in] apIndex            Index of the Access Point.
 * @param[in] output_struct        Interworking Element.
 *
 * @return The status of the operation
 * @retval RETURN_OK if successful
 * @retval RETURN_ERR if any error is detected
 */
INT wifi_getApInterworkingElement(INT apIndex, wifi_InterworkingElement_t *output_struct);

INT    wifi_pushApInterworkingElement(INT apIndex, 
                                wifi_InterworkingElement_t    *infoEelement);
/** @} */  //END OF GROUP WIFI_HAL_APIS

/**
 * @addtogroup WIFI_HAL_TYPES
 * @{
 */

typedef enum
{
    WIFI_MGMT_FRAME_TYPE_INVALID=-1,
    WIFI_MGMT_FRAME_TYPE_PROBE_REQ=0,
    WIFI_MGMT_FRAME_TYPE_PROBE_RSP=1,
    WIFI_MGMT_FRAME_TYPE_ASSOC_REQ=2,
    WIFI_MGMT_FRAME_TYPE_ASSOC_RSP=3,
    WIFI_MGMT_FRAME_TYPE_AUTH=4,
    WIFI_MGMT_FRAME_TYPE_DEAUTH=5,
    WIFI_MGMT_FRAME_TYPE_REASSOC_REQ=6,
    WIFI_MGMT_FRAME_TYPE_REASSOC_RSP=7,
    WIFI_MGMT_FRAME_TYPE_DISASSOC=8,
    WIFI_MGMT_FRAME_TYPE_ACTION=9,
} wifi_mgmtFrameType_t;

typedef enum
{
    WIFI_DATA_FRAME_TYPE_INVALID=-1,
    WIFI_DATA_FRAME_TYPE_8021x,
} wifi_dataFrameType_t;

typedef enum
{
    WIFI_FRAME_TYPE_INVALID=-1,
    WIFI_FRAME_TYPE_MGMT,
    WIFI_FRAME_TYPE_CTRL,
    WIFI_FRAME_TYPE_DATA,
} wifi_frameType_t;
  
typedef void (* wifi_received8021xFrame_callback)(unsigned int ap_index, mac_address_t sta, wifi_eapol_type_t type, void *data, unsigned int len);
typedef void (* wifi_sent8021xFrame_callback)(unsigned int ap_index, mac_address_t sta, wifi_eapol_type_t type, void *data, unsigned int len);

typedef void (* wifi_receivedAuthFrame_callback)(unsigned int ap_index, mac_address_t sta, void *data, unsigned int len);
typedef void (* wifi_sentAuthFrame_callback)(unsigned int ap_index, mac_address_t sta, void *data, unsigned int len);

typedef void (* wifi_receivedAssocReqFrame_callback)(unsigned int ap_index, mac_address_t sta, void *data, unsigned int len);
typedef void (* wifi_sentAssocRspFrame_callback)(unsigned int ap_index, mac_address_t sta, void *data, unsigned int len);

#ifdef WIFI_HAL_VERSION_3_PHASE2
typedef INT (* wifi_receivedMgmtFrame_callback)(INT apIndex, mac_address_t sta_mac, UCHAR *frame, UINT len, wifi_mgmtFrameType_t type, wifi_direction_t dir);
typedef INT (* wifi_receivedDataFrame_callback)(INT apIndex, mac_address_t sta_mac, UCHAR *frame, UINT len, wifi_dataFrameType_t type, wifi_direction_t dir);
#else
typedef INT (* wifi_receivedMgmtFrame_callback)(INT apIndex, UCHAR *sta_mac, UCHAR *frame, UINT len, wifi_mgmtFrameType_t type, wifi_direction_t dir);
typedef INT (* wifi_receivedDataFrame_callback)(INT apIndex, UCHAR *sta_mac, UCHAR *frame, UINT len, wifi_dataFrameType_t type, wifi_direction_t dir);
#endif
/** @} */  //END OF GROUP WIFI_HAL_TYPES

/**
 * @addtogroup WIFI_HAL_APIS
 * @{
 */

INT wifi_mgmt_frame_callbacks_register(wifi_receivedMgmtFrame_callback mgmtRxCallback);


/** @} */  //END OF GROUP WIFI_HAL_APIS


/**
 * @addtogroup WIFI_HAL_TYPES
 * @{
 */
#define WIFI_ETH_TYPE_IP 0x0800
#define WIFI_ETH_TYPE_ARP 0x0806
#define WIFI_ETH_TYPE_REVARP 0x8035
#define WIFI_ETH_TYPE_VLAN 0x8100
#define WIFI_ETH_TYPE_LOOPBACK 0x9000
#define WIFI_ETH_TYPE_IP6 0x86DD
#define WIFI_ETH_TYPE_EAPOL 0x888e

typedef enum {
    wifi_data_priority_be,
    wifi_data_priority_bk,
    wifi_data_priority_ee,
    wifi_data_priority_ca,
    wifi_data_priority_vi,
    wifi_data_priority_vo,
    wifi_data_prioirty_ic,
    wifi_data_priority_nc
} wifi_data_priority_t;
/** @} */  //END OF GROUP WIFI_HAL_TYPES

/**
 * @addtogroup WIFI_HAL_APIS
 * @{
 */
/* wifi_sendDataFrame() function */
/*
 * Description: This function sends data frame to a client associated in the specified VAP index
 * If the MAC address is NULL mac address, the data should be broadcast on the VAP
 *
 * Parameters :
 * apIndex - Index of VAP
 * sta - MAC address of the station associated in this VAP
 * data - Pointer to the data buffer. The data does not have any layer 2 information but has starts with layer 3.
 * len - length of data
 * insert_llc - whether LLC header should be inserted. If set to TRUE, HAL implementation MUST insert the following bytes before type field. DSAP = 0xaa, SSAP = 0xaa, Control = 0x03, followed by 3 bytes each = 0x00
 * eth_proto - ethernet protocol, the definitions are listed below.a
 * prio - priority of the frame with which scheduler should transmit the frame, please see the enumeration below.
 *
 * @return The status of the operation.
 * @retval RETURN_OK if successful.
 * @retval RETURN_ERR if any error is detected
 *
 * @execution Synchronous.
 * @sideeffect None.
 *
 */
INT wifi_sendDataFrame(INT apIndex,
                       mac_address_t sta,
                       UCHAR    *data,
                       UINT    len,
                       BOOL     insert_llc,
                       UINT    eth_proto,
                       wifi_data_priority_t prio);


/* @description transmit an action frame 
 * Transmits an action frame to STA from a specific VAP
 *
 * @param apIndex; index of the vAP to send the frame from.
 * @param staMAC; MAC address string of the peer device to send the frame to
 * @param frequency; frequency of the channel on which this action frame should be sent on (for public action frames that 
 *      can be sent tp a device on off channel
 * @param frame; pointer to the frame buffer
 * @param len; length of the buffer
 * @return The status of the operation.
 * @retval RETURN_OK if successful.
 * @retval RETURN_ERR if any error is detected.
 */

INT wifi_sendActionFrame(INT apIndex,
                                mac_address_t sta,
                                UINT frequency,
                                UCHAR *frame,
                                UINT len);


/* GAS Configuration */ 
#define GAS_CFG_TYPE_SUPPORTED 1

/* GAS Configuration */ 
typedef struct _wifi_GASConfiguration_t{   // Values correspond to the dot11GASAdvertisementEntry field definitions; see 802.11-2016 Annex C.3.
    UINT AdvertisementID;
    BOOL PauseForServerResponse;
    UINT ResponseTimeout;
    UINT ComeBackDelay;
    UINT ResponseBufferingTime;
    UINT QueryResponseLengthLimit;
}__attribute__((packed))wifi_GASConfiguration_t;

INT wifi_applyGASConfiguration(wifi_GASConfiguration_t *input_struct);

/* Passpoint R1 related APIs */

/***********************************************************************************
 * Description : Set Country code information element in Beacon and Probe Response
 * Parameters: AP Index, Enabled Status
 * Return: The status of the operation
 **********************************************************************************/
INT wifi_setCountryIe(INT apIndex, BOOL enabled);

/***********************************************************************************
 * Description : Get status of country code information element in Beacon 
                 and Probe Response
 * Parameters: AP Index, pointer to Enabled Status variable
 * Return: The status of the operation
 **********************************************************************************/
INT wifi_getCountryIe(INT apIndex, BOOL *enabled);

/***********************************************************************************
 * Description : Enable Traffic Inspection and Filtering 
 * Parameters: AP Index, Enabled Status
 * Return: The status of the operation
 **********************************************************************************/
INT wifi_setLayer2TrafficInspectionFiltering(INT apIndex, BOOL enabled);

/***********************************************************************************
 * Description : Get Traffic Inspection and Filtering status
 * Parameters: AP Index, pointer to Enabled Status variable
 * Return: The status of the operation
 **********************************************************************************/
INT wifi_getLayer2TrafficInspectionFiltering(INT apIndex, BOOL *enabled);

/***********************************************************************************
 * Description : Disable DGAF. When set to true, DGAF disabled bit should be set 
                 in HS2.0 Indication Information Element in Beacon and Probe
 * Parameters: AP Index, Disabled Status
 * Return: The status of the operation
 **********************************************************************************/
INT wifi_setDownStreamGroupAddress(INT apIndex, BOOL disabled);

/***********************************************************************************
 * Description : Status of Disable DGAF
 * Parameters: AP Index, pointer to Disabled Status variable
 * Return: The status of the operation
 **********************************************************************************/
INT wifi_getDownStreamGroupAddress(INT apIndex, BOOL *disabled);

/***********************************************************************************
 * Description : Enable BSS Load Information Element in Beacon/Probe Response
 * Parameters: AP Index, Enabled Status
 * Return: The status of the operation
 **********************************************************************************/
INT wifi_setBssLoad(INT apIndex, BOOL enabled);

/***********************************************************************************
 * Description : Get Status of BSS Load Information Element in Beacon/Probe Response
 * Parameters: AP Index, pointer to Enabled Status variable
 * Return: The status of the operation
 **********************************************************************************/
INT wifi_getBssLoad(INT apIndex, BOOL *enabled);

/***********************************************************************************
 * Description : Enable Proxy Arp function on device Driver
 * Parameters: AP Index, Enabled Status
 * Return: The status of the operation
 **********************************************************************************/
INT wifi_setProxyArp(INT apIndex, BOOL enabled);

/***********************************************************************************
 * Description : Get Status of Proxy Arp from Driver
 * Parameters: AP Index, pointer to Enabled Status variable 
 * Return: The status of the operation
 **********************************************************************************/
INT wifi_getProxyArp(INT apIndex, BOOL *enable);

/***********************************************************************************
 * Description : Set Hotspot 2.0 Status for the Access Point
 * Parameters: AP Index, HS20 Enabled status
 * Return: The status of the operation
 **********************************************************************************/
INT wifi_pushApHotspotElement(INT apIndex, BOOL enabled);

/***********************************************************************************
 * Description : Enable Traffic Inspection and Filtering 
 * Parameters: AP Index, pointer to Enabled Status variable
 * Return: The status of the operation
 **********************************************************************************/
INT wifi_getApHotspotElement(INT apIndex, BOOL *enabled);

/***********************************************************************************
 * Description : Push Roaming Consortium Information Element Contents to HAL 
 * Parameters: AP Index, pointer to wifi_roamingConsortiumElement_t
               the structure contains OI count, length of first 3 OIs,
               and first 3 OI as a hex string. When count > 0 and interworking is 
               enabled, Roaming Consortium Information Element should be present
               in Beacon and Probe Response with this information.
 * Return: The status of the operation
 **********************************************************************************/
INT wifi_pushApRoamingConsortiumElement(INT apIndex, wifi_roamingConsortiumElement_t *infoElement);

/***********************************************************************************
 * Description : Get Roaming Consortium Information Element Contents
 * Parameters: AP Index, pointer to wifi_roamingConsortiumElement_t
               If Roaming Consortium is not present, return count as 0,
               and length and OI fileds can be ignored
 * Return: The status of the operation
 **********************************************************************************/
INT wifi_getApRoamingConsortiumElement(INT apIndex, wifi_roamingConsortiumElement_t *infoElement);

/***********************************************************************************
 * Description : Disable P2P Cross Connect
                 When Set to True, Include P2P Information element in Beacon and Probe Response
                 Include P2P Manageability attribute with the Cross Connection Permitted field value 0
 * Parameters: AP Index, Disabled Status
 * Return: The status of the operation
 **********************************************************************************/
INT wifi_setP2PCrossConnect(INT apIndex, BOOL disabled);

/***********************************************************************************
 * Description : Get Disable P2P Cross Connect status
 * Parameters: AP Index, pointer to Disabled Status variable
 * Return: The status of the operation
 **********************************************************************************/
INT wifi_getP2PCrossConnect(INT apIndex, BOOL *disabled);

/* wifi_getAllTWTsessions() function */
/**
* @brief get all the TWT session(individual or Broadcast) connected to that AP Index .
*
* @param[in]  ap_index  access point index
* @param[in]  maxNumberSessions  maximum number of session to copy in the list 
* @param[out]  twtSessions  pointer to the sessions information
* @param[out]  numSessionReturned  num of seesion copied the list

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
INT wifi_getTWTsessions(INT ap_index, UINT maxNumberSessions, wifi_twt_sessions_t * twtSessions, UINT* numSessionReturned);

/* wifi_getBroadCastSession() function */
/**
* @brief Create or update a broadcast TWT Session  
*
* @param[in]  ap_index  access point index
* @param[in]  twtParams  twt params to create or update a broadcast TWT session
* @param[in]  create  Flag to indicate if it should create a new broadcast TWT Session
* @param[in/out]  sessionID  Input when create flag is false and session exist; and output when 
*                            create flag is true, in this case sessionID is the ID for the new session 
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
INT wifi_setBroadcastTWTSchedule(INT ap_index , wifi_twt_params_t twtParams, BOOL create, INT* sessionID);

/* wifi_teardownTWTSession() function */
/**
* @brief teardown the individual session or the broadcast session associate to the MAC
*
* @param[in]  ap_index  access point index
* @param[in] sessionID  TWT session to be teardown
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
INT wifi_setTeardownTWTSession(INT ap_index,  INT sessionID);

/** @} */  //END OF GROUP WIFI_HAL_APIS

/**
 * @addtogroup WIFI_HAL_TYPES
 * @{
 */

/**
 * _wifi_key_multi_psk structure is a container for multi psk keys.
 * It is based on hostapd wpa_psk_file implementation
 * https://w1.fi/cgit/hostap/tree/hostapd/hostapd.wpa_psk
 */
typedef struct _wifi_key_multi_psk {
	    CHAR wifi_keyId[64];   //<! Key identifier. for example "key-15" or "key_example"
	    CHAR wifi_psk[64];     //<! PSK is an ASCII passphrase of 8..63 characters
} wifi_key_multi_psk_t;
/** @} */  //END OF GROUP WIFI_HAL_TYPES

/* wifi_pushMultiPskKeys() function */
/**
  * @description Function sets the new set of multi psk keys.
  * Previously set keys are removed.
  * This API is for setting all keys except the primary key.
  * Primary key is set by wifi_setApSecurityKeyPassphrase.
  *
  * @param[in] apIndex - access point index
  * @param[in] keys - Array with all keys that client devices can associate with AP
  * @param[in] keysNumber - Number of elements in 'keys' array
  *
  * @return The status of the operation
  * @retval RETURN_OK if successful
  * @retval RETURN_ERR if any error is detected
  *
  * @sideeffect None
  */
INT wifi_pushMultiPskKeys(INT apIndex, wifi_key_multi_psk_t *keys, INT keysNumber);

/* wifi_getMultiPskKeys() function */
/**
  * @description Function gets all keys from multi psk config.
  * Implementation has to fill all active keys into wifi_key_multi_psk_t array.
  * The keys should be consecutively written starting at [0] element of the keys array.
  * This API is for getting all keys the except primary key.
  * Primary key can be get by wifi_getApSecurityKeyPassphrase.
  *
  * @param[in] apIndex - access point index
  * @param[out] keys - An array to which multi-psk keys active on the AP should be written to. If there are less present keys than 'keysNumber' the unused array elements should contain empty strings (""). Array is allocated by the caller.
  * @param[in] keysNumber - Number of elements in 'keys' array
  *
  * @return The status of the operation
  * @retval RETURN_OK if successful
  * @retval RETURN_ERR if any error is detected
  *
  * @sideeffect None
  */
INT wifi_getMultiPskKeys(INT apIndex, wifi_key_multi_psk_t *keys, INT keysNumber);

/* wifi_getMultiPskClientKey() function */
/**
  * @description Function gets multi psk key for the client mac address.
  * If wifi_key_multi_psk_t.wifi_keyID is null this means that
  * multi psk key was not used for authentication.
  *
  * @param[in] apIndex - access point index
  * @param[in] mac - client mac address
  * @param[out] key - multi psk key structure
  *
  * @return The status of the operation
  * @retval RETURN_OK if successful
  * @retval RETURN_ERR if any error is detected
  *
  * @sideeffect None
  */
INT wifi_getMultiPskClientKey(INT apIndex, mac_address_t mac, wifi_key_multi_psk_t *key);

/** @} */  //END OF GROUP WIFI_HAL_APIS

/**
 * @addtogroup WIFI_HAL_TYPES
 * @{
 */
typedef struct {
     wifi_GASConfiguration_t gas_config;
}__attribute__((packed))wifi_config_t;

typedef UINT wifi_vap_index_t;

/**
 * @brief Wifi onboarding methods
 */
typedef enum{
    WIFI_ONBOARDINGMETHODS_USBFLASHDRIVE = 0x0001,
    WIFI_ONBOARDINGMETHODS_ETHERNET = 0x0002,
    WIFI_ONBOARDINGMETHODS_LABEL = 0x0004,
    WIFI_ONBOARDINGMETHODS_DISPLAY = 0x0008,
    WIFI_ONBOARDINGMETHODS_EXTERNALNFCTOKEN = 0x0010,
    WIFI_ONBOARDINGMETHODS_INTEGRATEDNFCTOKEN = 0x0020,
    WIFI_ONBOARDINGMETHODS_NFCINTERFACE = 0x0040,
    WIFI_ONBOARDINGMETHODS_PUSHBUTTON = 0x0080,
    WIFI_ONBOARDINGMETHODS_PIN = 0x0100,
    WIFI_ONBOARDINGMETHODS_PHYSICALPUSHBUTTON = 0x0200,
    WIFI_ONBOARDINGMETHODS_PHYSICALDISPLAY = 0x0400,
    WIFI_ONBOARDINGMETHODS_VIRTUALPUSHBUTTON = 0x0800,
    WIFI_ONBOARDINGMETHODS_VIRTUALDISPLAY = 0x1000,
    WIFI_ONBOARDINGMETHODS_EASYCONNECT = 0x2000,
} wifi_onboarding_methods_t;

#define WIFI_AP_MAX_WPSPIN_LEN  9
typedef struct 
{
    BOOL enable;
    wifi_onboarding_methods_t methods;
    CHAR pin[WIFI_AP_MAX_WPSPIN_LEN];
} __attribute__((packed)) wifi_wps_t;

typedef enum {
    wifi_mfp_cfg_disabled,
    wifi_mfp_cfg_optional,
    wifi_mfp_cfg_required,
} wifi_mfp_cfg_t;

typedef enum {
    wifi_mac_filter_mode_black_list,
    wifi_mac_filter_mode_white_list,
} wifi_mac_filter_mode_t;

/**
 * @brief Wifi RADIUS Settings
 */
typedef struct {
#ifdef WIFI_HAL_VERSION_3_PHASE2
    ip_addr_t       ip;                 /**< The primary RADIUS server IP address. */
#else
    unsigned char   ip[45];
#endif
    unsigned short  port;               /**< The primary RADIUS server port. */
    char            key[64];            /**< The primary secret. */
    char            identity[64];       /**< The primary identity. */
#ifdef WIFI_HAL_VERSION_3_PHASE2
    ip_addr_t       s_ip;                 /**< The secondary RADIUS server IP address. */
#else
    unsigned char   s_ip[45];
#endif
    unsigned short  s_port;             /**< The secondary RADIUS server port. */
    char            s_key[64];          /**< The secondary secret. */
    ip_addr_t       dasip;
    USHORT          dasport;
    char            daskey[64];
    UINT            max_auth_attempts;
    UINT            blacklist_table_timeout;
    UINT            identity_req_retry_interval;
    UINT            server_retries;
    wifi_eap_t      eap_type;
} __attribute__((packed)) wifi_radius_settings_t;

typedef enum {
    wifi_security_key_type_psk,
    wifi_security_key_type_pass,
    wifi_security_key_type_sae,
    wifi_security_key_type_psk_sae
} wifi_security_key_type_t;

typedef struct {
    wifi_security_key_type_t type;
    char    key[256];
} __attribute__((packed)) wifi_security_key_t;

/**
 * @brief Wifi encryption types
 */
typedef enum {
    wifi_encryption_none,
    wifi_encryption_tkip = 1,
    wifi_encryption_aes,
    wifi_encryption_aes_tkip,
} wifi_encryption_method_t;


/**
 * @brief Wifi security mode types
 */
typedef enum {
    wifi_security_mode_none = 0x00000001,
    wifi_security_mode_wep_64 = 0x00000002,
    wifi_security_mode_wep_128 = 0x00000004,
    wifi_security_mode_wpa_personal = 0x00000008,
    wifi_security_mode_wpa2_personal = 0x00000010,
    wifi_security_mode_wpa_wpa2_personal = 0x00000020,
    wifi_security_mode_wpa_enterprise = 0x00000040,
    wifi_security_mode_wpa2_enterprise = 0x00000080,
    wifi_security_mode_wpa_wpa2_enterprise = 0x00000100,
    wifi_security_mode_wpa3_personal = 0x00000200,
    wifi_security_mode_wpa3_transition = 0x00000400,
    wifi_security_mode_wpa3_enterprise = 0x00000800
} wifi_security_modes_t;

typedef struct {
    wifi_security_modes_t   mode;
    wifi_encryption_method_t    encr;
#if defined(WIFI_HAL_VERSION_3)
    wifi_mfp_cfg_t  mfp;
#else
    char    mfpConfig[32];
#endif
    BOOL  wpa3_transition_disable;
    UINT  rekey_interval;
    BOOL  strict_rekey;  // must be set for enterprise VAPs
    UINT  eapol_key_timeout;
    UINT  eapol_key_retries;
    UINT  eap_identity_req_timeout;
    UINT  eap_identity_req_retries;
    UINT  eap_req_timeout;
    UINT  eap_req_retries;
    BOOL  disable_pmksa_caching;
    union {
        wifi_radius_settings_t  radius;
        wifi_security_key_t key;
    } u;
} __attribute__((packed)) wifi_vap_security_t;

typedef struct {
    int capabilityInfoLength;
    wifi_capabilityListANQP_t capabilityInfo;
    int venueInfoLength;
    wifi_venueNameElement_t venueInfo;
    int roamInfoLength;
    wifi_roamingConsortium_t roamInfo;
    wifi_ipAddressAvailabality_t ipAddressInfo;
    int realmInfoLength;
    wifi_naiRealmElement_t realmInfo;
    int gppInfoLength;
    wifi_3gppCellularNetwork_t gppInfo;
    int domainInfoLength;
    wifi_domainName_t domainNameInfo;
    UCHAR  passpointStats[1024];
    UINT   domainRespCount;
    UINT   realmRespCount;
    UINT   gppRespCount;
    UINT   domainFailedCount;
    UINT   realmFailedCount;
    UINT   gppFailedCount;
    UCHAR  anqpParameters[4096];
} __attribute__((packed)) wifi_anqp_settings_t;

typedef struct {
    BOOL        enable;
    BOOL        gafDisable;
    BOOL        p2pDisable;
    BOOL        l2tif;
    BOOL        bssLoad;
    BOOL        countryIE;
    BOOL        proxyArp;

    int capabilityInfoLength;                           //should not be implemented in the hal
    wifi_HS2_CapabilityList_t capabilityInfo;           //should not be implemented in the hal
    int opFriendlyNameInfoLength;                       //should not be implemented in the hal
    wifi_HS2_OperatorFriendlyName_t opFriendlyNameInfo; //should not be implemented in the hal
    int connCapabilityLength;                           //should not be implemented in the hal
    wifi_HS2_ConnectionCapability_t connCapabilityInfo; //should not be implemented in the hal
    int realmInfoLength;                                //should not be implemented in the hal
    wifi_HS2_NAI_Home_Realm_Query_t realmInfo;          //should not be implemented in the hal
    wifi_HS2_WANMetrics_t wanMetricsInfo;               //should not be implemented in the hal
    UCHAR hs2Parameters[4096];                          //should not be implemented in the hal
} __attribute__((packed)) wifi_passpoint_settings_t;

typedef struct {
    wifi_InterworkingElement_t   interworking;
    wifi_roamingConsortiumElement_t roamingConsortium;
    wifi_anqp_settings_t        anqp;                   //should not be implemented in the hal
    wifi_passpoint_settings_t   passpoint;
} __attribute__((packed)) wifi_interworking_t;

typedef enum {
    wifi_vap_mode_ap,
    wifi_vap_mode_sta,
    wifi_vap_mode_monitor,
} wifi_vap_mode_t;

typedef struct {
    unsigned int period;        // period in seconds    
    wifi_channel_t  channel;    // channel to scan, 0 means scan all in the band
} __attribute__((packed)) wifi_scan_params_t;

typedef struct {
    ssid_t              ssid;
    bssid_t             bssid; // if bssid is set to all 0, scan the ssid with probes, otherwise connect to specified bssid
    BOOL                enabled;
    wifi_connection_status_t    conn_status;
    wifi_scan_params_t  scan_params;
    wifi_vap_security_t security;
    mac_address_t       mac;
} __attribute__((packed)) wifi_back_haul_sta_t;

#define WIFI_AP_MAX_SSID_LEN    33
typedef struct {
    CHAR    ssid[WIFI_AP_MAX_SSID_LEN];
    BOOL    enabled;
    BOOL    showSsid;
    BOOL    isolation;
    INT     mgmtPowerControl;
    UINT    bssMaxSta;
    BOOL    bssTransitionActivated;
    BOOL    nbrReportActivated;
    BOOL    rapidReconnectEnable;       //should not be implemented in the hal
    UINT    rapidReconnThreshold;       //should not be implemented in the hal
    BOOL    vapStatsEnable;             //should not be implemented in the hal
    wifi_vap_security_t security;
    wifi_interworking_t interworking;
    BOOL    mac_filter_enable;
    wifi_mac_filter_mode_t mac_filter_mode;
    BOOL    sec_changed;                //should not be implemented in the hal
    wifi_wps_t   wps;
    BOOL    wmm_enabled;
    BOOL    UAPSDEnabled;
    wifi_bitrate_t beaconRate;
    mac_address_t bssid;                    /**< The BSSID. This variable should only be used in the get API. It can't used to change the interface MAC */
    UINT   wmmNoAck;
    UINT   wepKeyLength;
    BOOL   bssHotspot;
    UINT   wpsPushButton;
    char   beaconRateCtl[32];
} __attribute__((packed)) wifi_front_haul_bss_t;

#define WIFI_BRIDGE_NAME_LEN  32

typedef struct {
    wifi_vap_index_t    vap_index;
    wifi_vap_name_t     vap_name;
    wifi_radio_index_t  radio_index;
    CHAR                bridge_name[WIFI_BRIDGE_NAME_LEN];
    wifi_vap_mode_t     vap_mode;
    union {
        wifi_front_haul_bss_t   bss_info;
        wifi_back_haul_sta_t    sta_info;
    } u;
} __attribute__((packed)) wifi_vap_info_t;

typedef struct {
    unsigned int        num_vaps;
    wifi_vap_info_t vap_array[MAX_NUM_VAP_PER_RADIO];
} __attribute__((packed)) wifi_vap_info_map_t;

/**
 * @brief Wifi AP Capabilities
 */
typedef struct {
    BOOL rtsThresholdSupported;                                 /**< if bRtsThresholdSupported is TRUE, packet size threshold to apply RTS/CTS backoff rules is supported. */
    wifi_security_modes_t securityModesSupported;               /**< The security modes supported (uses bitmask to return multiples modes). */
    wifi_onboarding_methods_t methodsSupported;                 /**< The on boarding methods supported (uses bitmask to return multiples values). */
    BOOL WMMSupported;                                          /**< if bWMMSupported is TRUE, WiFi Multimedia (WMM) Access Categories (AC) is supported. */
    BOOL UAPSDSupported;                                        /**< if bUAPSDSupported is TRUE, WMM Unscheduled Automatic Power Save Delivery (U-APSD) is supported. */
    BOOL interworkingServiceSupported;                          /**< if bInterworkingServiceSupported is TRUE, indicates whether the access point supports interworking with external networks. */
    BOOL BSSTransitionImplemented;                              /**< if BSSTransitionImplemented is TRUE, BTM implemented. */
} __attribute__((packed)) wifi_ap_capabilities_t;


/** @} */  //END OF GROUP WIFI_HAL_TYPES

/**
 * @addtogroup WIFI_HAL_APIS
 * @{
 */


INT wifi_getRadioVapInfoMap(wifi_radio_index_t index, wifi_vap_info_map_t *map);

INT wifi_setApSecurity(INT ap_index, wifi_vap_security_t *security);
INT wifi_getApSecurity(INT ap_index, wifi_vap_security_t *security);

INT wifi_getAPCapabilities(INT ap_index, wifi_ap_capabilities_t *apCapabilities);

INT wifi_getApWpsConfiguration(INT ap_index, wifi_wps_t* wpsConfig);
INT wifi_setApWpsConfiguration(INT ap_index, wifi_wps_t* wpsConfig);

INT wifi_getLibhostapd(BOOL *output_bool);
INT wifi_updateLibHostApdConfig(int apIndex);

/**
 * @brief VAP status possible values
 */
typedef enum {
    wifi_vapstatus_down,
    wifi_vapstatus_up
} wifi_vapstatus_t;

/* wifi_vapstatus_callback() function */
/**
* @brief This call back will be invoked when VAP status changes
*
* @param[in] apIndex          VAP Index
* @param[in] status           VAP status
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
typedef INT(* wifi_vapstatus_callback)(INT apIndex, wifi_vapstatus_t status);

/* wifi_vapstatus_callback_register() function */
/**
* @brief VAP Status call back registration function.
*
* @param[in] callback    wifi_vapstatus_callback callback function
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
INT wifi_vapstatus_callback_register(wifi_vapstatus_callback callback);


/** @} */  //END OF GROUP WIFI_HAL_APIS

#ifdef __cplusplus
}
#endif

#endif
