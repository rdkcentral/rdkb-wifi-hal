
#include "wifi_hal.h"

INT wifi_getRadioChannelStats(INT radioIndex, wifi_channelStats_t *input_output_channelStats_array, INT array_size) {
    INT returnValue;
    return returnValue;
}

INT wifi_getApAssociatedDeviceRxStatsResult(INT radioIndex, mac_address_t *clientMacAddress, wifi_associated_dev_rate_info_rx_stats_t **stats_array, UINT *output_array_size, ULLONG *handle) {
    INT returnValue;
    return returnValue;
}

INT wifi_getApAssociatedDeviceTxStatsResult(INT radioIndex, mac_address_t *clientMacAddress, wifi_associated_dev_rate_info_tx_stats_t **stats_array, UINT *output_array_size, ULLONG *handle) {
    INT returnValue;
    return returnValue;
}

INT wifi_getApAssociatedDeviceTidStatsResult(INT radioIndex,  mac_address_t *clientMacAddress, wifi_associated_dev_tid_stats_t *tid_stats,  ULLONG *handle) {
    INT returnValue;
    return returnValue;
}

INT wifi_getApAssociatedDeviceStats(INT apIndex, mac_address_t *clientMacAddress, wifi_associated_dev_stats_t *associated_dev_stats, ULLONG *handle) {
    INT returnValue;
    return returnValue;
}

INT wifi_getSSIDRadioIndex(INT ssidIndex, INT *radioIndex) {
    INT returnValue;
    return returnValue;
}

INT wifi_applySSIDSettings(INT ssidIndex) {
    INT returnValue;
    return returnValue;
}

INT wifi_startNeighborScan(INT apIndex, wifi_neighborScanMode_t scan_mode, INT dwell_time, UINT chan_num, UINT *chan_list) {
    INT returnValue;
    return returnValue;
}

INT wifi_setApCsaDeauth(INT apIndex, INT mode) {
    INT returnValue;
    return returnValue;
}

INT wifi_setApScanFilter(INT apIndex, INT mode, CHAR *essid) {
    INT returnValue;
    return returnValue;
}

INT wifi_steering_setGroup(UINT steeringGroupIndex, UINT numElements, wifi_steering_apConfig_t * cfgArray) {
    INT returnValue;
    return returnValue;
}

 )(INT apIndex, wifi_steer_trigger_data_t *data) {
}

void wifi_steerTriggered_callback_register(wifi_steerTriggered_callback callback_proc, CHAR *module) {
}

 )(UINT steeringgroupIndex, wifi_steering_event_t *event) {
}

INT wifi_steering_eventRegister(wifi_steering_eventCB_t event_cb) {
    INT returnValue;
    return returnValue;
}

INT wifi_steering_eventUnregister(void) {
    INT returnValue;
    return returnValue;
}

INT wifi_steering_clientSet(
                                UINT steeringgroupIndex,
                                INT apIndex,
                                mac_address_t client_mac,
                                wifi_steering_clientConfig_t *config) {
    INT returnValue;
    return returnValue;
}

INT wifi_steering_clientRemove(
                                UINT steeringgroupIndex,
                                INT apIndex,
                                mac_address_t client_mac) {
    INT returnValue;
    return returnValue;
}

INT wifi_steering_clientMeasure(
                                UINT steeringgroupIndex,
                                INT apIndex,
                                mac_address_t client_mac) {
    INT returnValue;
    return returnValue;
}

INT wifi_steering_clientDisconnect(
                                UINT steeringgroupIndex,
                                INT apIndex,
                                mac_address_t client_mac,
                                wifi_disconnectType_t type,
                                UINT reason) {
    INT returnValue;
    return returnValue;
}

 )(UINT apIndex,
                                                    mac_address_t peerMac,
                                                    wifi_BTMQuery_t *query,
                                                    UINT inMemSize,
                                                    wifi_BTMRequest_t *request) {
}

 )(UINT apIndex,
                                            mac_address_t peerMac,
                                            wifi_BTMResponse_t *response) {
}

 )(UINT apIndex,
                                                    CHAR *peerMac,
                                                    wifi_BTMQuery_t *query,
                                                    UINT inMemSize,
                                                    wifi_BTMRequest_t *request) {
}

 )(UINT apIndex,
                                            CHAR *peerMac,
                                            wifi_BTMResponse_t *response) {
}

INT wifi_BTMQueryRequest_callback_register(UINT apIndex,
                                            wifi_BTMQueryRequest_callback btmQueryCallback,
                                            wifi_BTMResponse_callback btmResponseCallback) {
    INT returnValue;
    return returnValue;
}

INT wifi_setBTMRequest(UINT apIndex,
                        mac_address_t    peerMac,
                        wifi_BTMRequest_t *request) {
    INT returnValue;
    return returnValue;
}

 )(UINT apIndex,
                                                    wifi_BeaconReport_t *out_struct,
                                                    UINT    *out_array_size,
                                                    UCHAR     *out_DialogToken) {
}

INT wifi_RMBeaconRequestCallbackRegister(UINT apIndex,
                                          wifi_RMBeaconReport_callback beaconReportCallback) {
    INT returnValue;
    return returnValue;
}

INT wifi_RMBeaconRequestCallbackUnregister(UINT apIndex,
                                            wifi_RMBeaconReport_callback beaconReportCallback) {
    INT returnValue;
    return returnValue;
}

INT wifi_cancelRMBeaconRequest(UINT apIndex, UCHAR dialogToken) {
    INT returnValue;
    return returnValue;
}

INT wifi_setRMBeaconRequest(UINT apIndex,
                             mac_address_t peer,
                             wifi_BeaconRequest_t *in_request,
                             UCHAR *out_DialogToken) {
    INT returnValue;
    return returnValue;
}

INT wifi_getRMCapabilities(mac_address_t peer, UCHAR out_Capabilities[5]) {
    INT returnValue;
    return returnValue;
}
