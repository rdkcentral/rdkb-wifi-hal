
#include "wifi_hal.h"

INT wifi_getWifiTrafficStats(INT apIndex, wifi_trafficStats_t *output_struct) {
    INT returnValue;
    return returnValue;
}

INT wifi_getApAssociatedDevice(INT ap_index, mac_address_t *output_deviceMacAddressArray, UINT maxNumDevices, UINT *output_numDevices) {
    INT returnValue;
    return returnValue;
}

INT wifi_factoryResetAP(int apIndex) {
    INT returnValue;
    return returnValue;
}

INT wifi_deleteAp(INT apIndex) {
    INT returnValue;
    return returnValue;
}

INT wifi_getApName(INT apIndex, CHAR *output_string) {
    INT returnValue;
    return returnValue;
}

INT wifi_setApRtsThreshold(INT apIndex, UINT threshold) {
    INT returnValue;
    return returnValue;
}

INT wifi_removeApSecVaribles(INT apIndex) {
    INT returnValue;
    return returnValue;
}

INT wifi_disableApEncryption(INT apIndex) {
    INT returnValue;
    return returnValue;
}

INT wifi_getApNumDevicesAssociated(INT apIndex, ULONG *output_ulong) {
    INT returnValue;
    return returnValue;
}

INT wifi_kickApAssociatedDevice(INT apIndex, mac_address_t client_mac) {
    INT returnValue;
    return returnValue;
}

INT wifi_getApRadioIndex(INT apIndex, INT *output_int) {
    INT returnValue;
    return returnValue;
}

INT wifi_getApAclDevices(INT apIndex, mac_address_t *macArray, UINT maxArraySize, UINT* output_numEntries) {
    INT returnValue;
    return returnValue;
}

INT wifi_addApAclDevice(INT apIndex, mac_address_t DeviceMacAddress) {
    INT returnValue;
    return returnValue;
}

INT wifi_delApAclDevices(INT apINdex) {
    INT returnValue;
    return returnValue;
}

INT wifi_getApAclDeviceNum(INT apIndex, UINT *output_uint) {
    INT returnValue;
    return returnValue;
}

INT wifi_kickApAclAssociatedDevices(INT apIndex,BOOL enable) {
    INT returnValue;
    return returnValue;
}

INT wifi_setApMacAddressControlMode(INT apIndex, INT filterMode) {
    INT returnValue;
    return returnValue;
}

INT wifi_getApMacAddressControlMode(INT apIndex, INT *output_filterMode) {
    INT returnValue;
    return returnValue;
}

INT wifi_setApVlanID(INT apIndex, INT vlanId) {
    INT returnValue;
    return returnValue;
}

INT wifi_resetApVlanCfg(INT apIndex) {
    INT returnValue;
    return returnValue;
}

INT wifi_setApEnable(INT apIndex, BOOL enable) {
    INT returnValue;
    return returnValue;
}

INT wifi_getApEnable(INT apIndex, BOOL *output_bool) {
    INT returnValue;
    return returnValue;
}

INT wifi_getApStatus(INT apIndex, CHAR *output_string) {
    INT returnValue;
    return returnValue;
}

INT wifi_getApSsidAdvertisementEnable(INT apIndex, BOOL *output_bool) {
    INT returnValue;
    return returnValue;
}

INT wifi_setApSsidAdvertisementEnable(INT apIndex, BOOL enable) {
    INT returnValue;
    return returnValue;
}

INT wifi_getApRetryLimit(INT apIndex, UINT *output) {
    INT returnValue;
    return returnValue;
}

INT wifi_setApRetryLimit(INT apIndex, UINT number) {
    INT returnValue;
    return returnValue;
}

INT wifi_getApWmmEnable(INT apIndex, BOOL *output) {
    INT returnValue;
    return returnValue;
}

INT wifi_setApWmmEnable(INT apIndex, BOOL enable) {
    INT returnValue;
    return returnValue;
}

INT wifi_getApWmmUapsdEnable(INT apIndex, BOOL *output) {
    INT returnValue;
    return returnValue;
}

INT wifi_setApWmmUapsdEnable(INT apIndex, BOOL enable) {
    INT returnValue;
    return returnValue;
}

INT wifi_setApWmmOgAckPolicy(INT apIndex, INT cla, BOOL ackPolicy) {
    INT returnValue;
    return returnValue;
}

INT wifi_getApIsolationEnable(INT apIndex, BOOL *output) {
    INT returnValue;
    return returnValue;
}

INT wifi_setApIsolationEnable(INT apIndex, BOOL enable) {
    INT returnValue;
    return returnValue;
}

INT wifi_setApBeaconRate(INT apIndex, char *sBeaconRate) {
    INT returnValue;
    return returnValue;
}

INT wifi_getApBeaconRate(INT apIndex, char *output_BeaconRate) {
    INT returnValue;
    return returnValue;
}

INT wifi_getApMaxAssociatedDevices(INT apIndex, UINT *output) {
    INT returnValue;
    return returnValue;
}

INT wifi_setApMaxAssociatedDevices(INT apIndex, UINT number) {
    INT returnValue;
    return returnValue;
}

INT wifi_setApSecurityReset(INT apIndex) {
    INT returnValue;
    return returnValue;
}

INT wifi_getApSecurityMFPConfig(INT apIndex, CHAR *output_string) {
    INT returnValue;
    return returnValue;
}

INT wifi_setApSecurityMFPConfig(INT apIndex, CHAR *MfpConfig) {
    INT returnValue;
    return returnValue;
}

INT wifi_getApSecurityRadiusServer(INT apIndex, CHAR *IP_output, UINT *Port_output, CHAR *RadiusSecret_output) {
    INT returnValue;
    return returnValue;
}

INT wifi_setApSecurityRadiusServer(INT apIndex, CHAR *IPAddress, UINT port, CHAR *RadiusSecret) {
    INT returnValue;
    return returnValue;
}

INT wifi_getApSecuritySecondaryRadiusServer(INT apIndex, CHAR *IP_output, UINT *Port_output, CHAR *RadiusSecret_output) {
    INT returnValue;
    return returnValue;
}

INT wifi_setApSecuritySecondaryRadiusServer(INT apIndex, CHAR *IPAddress, UINT port, CHAR *RadiusSecret) {
    INT returnValue;
    return returnValue;
}

INT wifi_getApDASRadiusServer(INT apIndex, CHAR *IP_output, UINT *Port_output, CHAR *RadiusdasSecret_output) {
    INT returnValue;
    return returnValue;
}

INT wifi_setApDASRadiusServer(INT apIndex, CHAR *IPAddress, UINT port, CHAR *RadiusdasSecret) {
    INT returnValue;
    return returnValue;
}

INT wifi_enableGreylistAccessControl(BOOL enable) {
    INT returnValue;
    return returnValue;
}

INT wifi_getApSecurityRadiusSettings(INT apIndex, wifi_radius_setting_t *output) {
    INT returnValue;
    return returnValue;
}

INT wifi_setApSecurityRadiusSettings(INT apIndex, wifi_radius_setting_t *input) {
    INT returnValue;
    return returnValue;
}

INT wifi_getApWpsConfigurationState(INT apIndex, CHAR *output_string) {
    INT returnValue;
    return returnValue;
}

INT wifi_setApWpsEnrolleePin(INT apIndex, CHAR *pin) {
    INT returnValue;
    return returnValue;
}

INT wifi_setApWpsButtonPush(INT apIndex) {
    INT returnValue;
    return returnValue;
}

INT wifi_cancelApWPS(INT apIndex) {
    INT returnValue;
    return returnValue;
}

INT wifi_getApManagementFramePowerControl(INT apIndex, INT *output_dBm) {
    INT returnValue;
    return returnValue;
}

INT wifi_setApManagementFramePowerControl(INT apIndex, INT dBm) {
    INT returnValue;
    return returnValue;
}

 )(INT apIndex, wifi_associated_dev3_t *associated_dev) {
}

 )(INT apIndex, wifi_associated_dev_t *associated_dev) {
}

void wifi_newApAssociatedDevice_callback_register(wifi_newApAssociatedDevice_callback callback_proc) {
}

 )(INT apIndex, char *MAC, INT event_type) {
}

void wifi_apDisassociatedDevice_callback_register(wifi_apDisassociatedDevice_callback callback_proc) {
}

 )(int ap_index, char *mac, int reason) {
}

void wifi_apDeAuthEvent_callback_register(wifi_apDeAuthEvent_callback callback_proc) {
}

INT wifi_setInterworkingAccessNetworkType(INT apIndex, INT accessNetworkType) {
    INT returnValue;
    return returnValue;
}

INT wifi_getInterworkingAccessNetworkType(INT apIndex, UINT *output_uint) {
    INT returnValue;
    return returnValue;
}

INT wifi_setInterworkingAccessNetworkType(INT apIndex, INT accessNetworkType) {
    INT returnValue;
    return returnValue;
}

INT wifi_getInterworkingAccessNetworkType(INT apIndex, UINT *output_uint) {
    INT returnValue;
    return returnValue;
}

INT wifi_getApInterworkingServiceEnable(INT apIndex, BOOL *output_bool) {
    INT returnValue;
    return returnValue;
}

INT wifi_setApInterworkingServiceEnable(INT apIndex, BOOL input_bool) {
    INT returnValue;
    return returnValue;
}

INT wifi_getApInterworkingElement(INT apIndex, wifi_InterworkingElement_t *output_struct) {
    INT returnValue;
    return returnValue;
}

INT wifi_pushApInterworkingElement(INT apIndex, 
                                wifi_InterworkingElement_t    *infoEelement) {
    INT returnValue;
    return returnValue;
}

 )(unsigned int ap_index, mac_address_t sta, wifi_eapol_type_t type, void *data, unsigned int len) {
}

 )(unsigned int ap_index, mac_address_t sta, wifi_eapol_type_t type, void *data, unsigned int len) {
}

 )(unsigned int ap_index, mac_address_t sta, void *data, unsigned int len) {
}

 )(unsigned int ap_index, mac_address_t sta, void *data, unsigned int len) {
}

 )(unsigned int ap_index, mac_address_t sta, void *data, unsigned int len) {
}

 )(unsigned int ap_index, mac_address_t sta, void *data, unsigned int len) {
}

 )(INT apIndex, mac_address_t sta_mac, UCHAR *frame, UINT len, wifi_mgmtFrameType_t type, wifi_direction_t dir) {
}

 )(INT apIndex, mac_address_t sta_mac, UCHAR *frame, UINT len, wifi_dataFrameType_t type, wifi_direction_t dir) {
}

 )(INT apIndex, UCHAR *sta_mac, UCHAR *frame, UINT len, wifi_mgmtFrameType_t type, wifi_direction_t dir) {
}

 )(INT apIndex, UCHAR *sta_mac, UCHAR *frame, UINT len, wifi_dataFrameType_t type, wifi_direction_t dir) {
}

INT wifi_mgmt_frame_callbacks_register(wifi_receivedMgmtFrame_callback mgmtRxCallback) {
    INT returnValue;
    return returnValue;
}

INT wifi_enableCSIEngine(INT apIndex,
                         mac_address_t sta,
                         BOOL enable) {
    INT returnValue;
    return returnValue;
}

INT wifi_sendDataFrame(INT apIndex,
                       mac_address_t sta,
                       UCHAR    *data,
                       UINT    len,
                       BOOL     insert_llc,
                       UINT    eth_proto,
                       wifi_data_priority_t prio) {
    INT returnValue;
    return returnValue;
}

INT wifi_sendActionFrame(INT apIndex,
                                mac_address_t sta,
                                UINT frequency,
                                UCHAR *frame,
                                UINT len) {
    INT returnValue;
    return returnValue;
}

INT wifi_applyGASConfiguration(wifi_GASConfiguration_t *input_struct) {
    INT returnValue;
    return returnValue;
}

INT wifi_setCountryIe(INT apIndex, BOOL enabled) {
    INT returnValue;
    return returnValue;
}

INT wifi_getCountryIe(INT apIndex, BOOL *enabled) {
    INT returnValue;
    return returnValue;
}

INT wifi_setLayer2TrafficInspectionFiltering(INT apIndex, BOOL enabled) {
    INT returnValue;
    return returnValue;
}

INT wifi_getLayer2TrafficInspectionFiltering(INT apIndex, BOOL *enabled) {
    INT returnValue;
    return returnValue;
}

INT wifi_setDownStreamGroupAddress(INT apIndex, BOOL disabled) {
    INT returnValue;
    return returnValue;
}

INT wifi_getDownStreamGroupAddress(INT apIndex, BOOL *disabled) {
    INT returnValue;
    return returnValue;
}

INT wifi_setBssLoad(INT apIndex, BOOL enabled) {
    INT returnValue;
    return returnValue;
}

INT wifi_getBssLoad(INT apIndex, BOOL *enabled) {
    INT returnValue;
    return returnValue;
}

INT wifi_setProxyArp(INT apIndex, BOOL enabled) {
    INT returnValue;
    return returnValue;
}

INT wifi_getProxyArp(INT apIndex, BOOL *enable) {
    INT returnValue;
    return returnValue;
}

INT wifi_pushApHotspotElement(INT apIndex, BOOL enabled) {
    INT returnValue;
    return returnValue;
}

INT wifi_getApHotspotElement(INT apIndex, BOOL *enabled) {
    INT returnValue;
    return returnValue;
}

INT wifi_pushApRoamingConsortiumElement(INT apIndex, wifi_roamingConsortiumElement_t *infoElement) {
    INT returnValue;
    return returnValue;
}

INT wifi_getApRoamingConsortiumElement(INT apIndex, wifi_roamingConsortiumElement_t *infoElement) {
    INT returnValue;
    return returnValue;
}

INT wifi_setP2PCrossConnect(INT apIndex, BOOL disabled) {
    INT returnValue;
    return returnValue;
}

INT wifi_getP2PCrossConnect(INT apIndex, BOOL *disabled) {
    INT returnValue;
    return returnValue;
}

INT wifi_getTWTsessions(INT ap_index, UINT maxNumberSessions, wifi_twt_sessions_t * twtSessions, UINT* numSessionReturned) {
    INT returnValue;
    return returnValue;
}

INT wifi_setBroadcastTWTSchedule(INT ap_index , wifi_twt_params_t twtParams, BOOL create, INT* sessionID) {
    INT returnValue;
    return returnValue;
}

INT wifi_setTeardownTWTSession(INT ap_index,  INT sessionID) {
    INT returnValue;
    return returnValue;
}

INT wifi_pushMultiPskKeys(INT apIndex, wifi_key_multi_psk_t *keys, INT keysNumber) {
    INT returnValue;
    return returnValue;
}

INT wifi_getMultiPskKeys(INT apIndex, wifi_key_multi_psk_t *keys, INT keysNumber) {
    INT returnValue;
    return returnValue;
}

INT wifi_getMultiPskClientKey(INT apIndex, mac_address_t mac, wifi_key_multi_psk_t *key) {
    INT returnValue;
    return returnValue;
}

INT wifi_createVAP(wifi_radio_index_t index, wifi_vap_info_map_t *map) {
    INT returnValue;
    return returnValue;
}

INT wifi_getRadioVapInfoMap(wifi_radio_index_t index, wifi_vap_info_map_t *map) {
    INT returnValue;
    return returnValue;
}

INT wifi_setApSecurity(INT ap_index, wifi_vap_security_t *security) {
    INT returnValue;
    return returnValue;
}

INT wifi_getApSecurity(INT ap_index, wifi_vap_security_t *security) {
    INT returnValue;
    return returnValue;
}

INT wifi_getAPCapabilities(INT ap_index, wifi_ap_capabilities_t *apCapabilities) {
    INT returnValue;
    return returnValue;
}

INT wifi_getApWpsConfiguration(INT ap_index, wifi_wps_t* wpsConfig) {
    INT returnValue;
    return returnValue;
}

INT wifi_setApWpsConfiguration(INT ap_index, wifi_wps_t* wpsConfig) {
    INT returnValue;
    return returnValue;
}

INT wifi_getLibhostapd(BOOL *output_bool) {
    INT returnValue;
    return returnValue;
}

INT wifi_updateLibHostApdConfig(int apIndex) {
    INT returnValue;
    return returnValue;
}

 )(INT apIndex, wifi_vapstatus_t status) {
}

INT wifi_vapstatus_callback_register(wifi_vapstatus_callback callback) {
    INT returnValue;
    return returnValue;
}
