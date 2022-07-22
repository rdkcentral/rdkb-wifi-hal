
#include "wifi_hal.h"


INT wifi_getRadioResetCount(INT radioIndex, ULONG *output_int) {
    INT returnValue;
    return returnValue;
}

INT wifi_factoryResetRadios() {
    INT returnValue;
    return returnValue;
}

INT wifi_factoryResetRadio(int radioIndex) {
    INT returnValue;
    return returnValue;
}

INT wifi_getRadioEnable(INT radioIndex, BOOL *output_bool) {
    INT returnValue;
    return returnValue;
}

INT wifi_setRadioEnable(INT radioIndex, BOOL enable) {
    INT returnValue;
    return returnValue;
}

INT wifi_getRadioStatus(INT radioIndex, BOOL *output_bool) {
    INT returnValue;
    return returnValue;
}

INT wifi_getRadioIfName(INT radioIndex, CHAR *output_string) {
    INT returnValue;
    return returnValue;
}

INT wifi_getRadioChannelsInUse(wifi_radio_index_t radioIndex, wifi_channels_list_t* channel_list) {
    INT returnValue;
    return returnValue;
}

INT wifi_getRadioDfsEnable(INT radioIndex, BOOL *output_bool) {
    INT returnValue;
    return returnValue;
}

INT wifi_setRadioDfsEnable(INT radioIndex, BOOL enabled) {
    INT returnValue;
    return returnValue;
}

INT wifi_getRadioMCS(INT radioIndex, INT *output_INT) {
    INT returnValue;
    return returnValue;
}

INT wifi_setRadioMCS(INT radioIndex, INT MCS) {
    INT returnValue;
    return returnValue;
}

INT wifi_getRadioTransmitPower(INT radioIndex, ULONG *output_ulong) {
    INT returnValue;
    return returnValue;
}

INT wifi_getRadioPercentageTransmitPower(INT radioIndex, ULONG *output_ulong) {
    INT returnValue;
    return returnValue;
}

INT wifi_setRadioTransmitPower(INT radioIndex, ULONG TransmitPower) {
    INT returnValue;
    return returnValue;
}

INT wifi_getRadioCarrierSenseThresholdRange(INT radioIndex, INT *output) {
    INT returnValue;
    return returnValue;
}

INT wifi_getRadioCarrierSenseThresholdInUse(INT radioIndex, INT *output) {
    INT returnValue;
    return returnValue;
}

INT wifi_setRadioCarrierSenseThresholdInUse(INT radioIndex, INT threshold) {
    INT returnValue;
    return returnValue;
}

INT wifi_applyRadioSettings(INT radioIndex) {
    INT returnValue;
    return returnValue;
}

INT wifi_setRadioCtsProtectionEnable(INT apIndex, BOOL enable) {
    INT returnValue;
    return returnValue;
}

INT wifi_setRadioObssCoexistenceEnable(INT apIndex, BOOL enable) {
    INT returnValue;
    return returnValue;
}

INT wifi_setRadioFragmentationThreshold(INT apIndex, UINT threshold) {
    INT returnValue;
    return returnValue;
}

INT wifi_setRadioSTBCEnable(INT radioIndex, BOOL STBC_Enable) {
    INT returnValue;
    return returnValue;
}

INT wifi_getRadioAMSDUEnable(INT radioIndex, BOOL *output_bool) {
    INT returnValue;
    return returnValue;
}

INT wifi_setRadioAMSDUEnable(INT radioIndex, BOOL amsduEnable) {
    INT returnValue;
    return returnValue;
}

INT wifi_getRadioUpTime(INT radioIndex, ULONG *uptime) {
    INT returnValue;
    return returnValue;
}

INT wifi_getRadioReverseDirectionGrantSupported(INT radioIndex, BOOL *output_bool) {
    INT returnValue;
    return returnValue;
}

INT wifi_getRadioAutoBlockAckEnable(INT radioIndex, BOOL *output_bool) {
    INT returnValue;
    return returnValue;
}

INT wifi_setRadioAutoBlockAckEnable(INT radioIndex, BOOL enable) {
    INT returnValue;
    return returnValue;
}

INT wifi_getRadioIGMPSnoopingEnable(INT radioIndex, BOOL *output_bool) {
    INT returnValue;
    return returnValue;
}

INT wifi_setRadioIGMPSnoopingEnable(INT radioIndex, BOOL enable) {
    INT returnValue;
    return returnValue;
}

INT wifi_setZeroDFSState(UINT radioIndex, BOOL enable, BOOL precac) {
    INT returnValue;
    return returnValue;
}

INT wifi_getZeroDFSState(UINT radioIndex, BOOL *enable, BOOL *precac) {
    INT returnValue;
    return returnValue;
}

INT wifi_setDownlinkMuType(INT radio_index, wifi_dl_mu_type_t mu_type) {
    INT returnValue;
    return returnValue;
}

INT wifi_getDownlinkMuType(INT radio_index, wifi_dl_mu_type_t *mu_type) {
    INT returnValue;
    return returnValue;
}

INT wifi_setUplinkMuType(INT radio_index, wifi_ul_mu_type_t mu_type) {
    INT returnValue;
    return returnValue;
}

INT wifi_getUplinkMuType(INT radio_index, wifi_ul_mu_type_t *mu_type) {
    INT returnValue;
    return returnValue;
}

INT wifi_setGuardInterval(INT radio_index, wifi_guard_interval_t guard_interval) {
    INT returnValue;
    return returnValue;
}

INT wifi_getGuardInterval(INT radio_index, wifi_guard_interval_t *guard_interval) {
    INT returnValue;
    return returnValue;
}

INT wifi_setBSSColor(INT radio_index, UCHAR color) {
    INT returnValue;
    return returnValue;
}

INT wifi_getBSSColor(INT radio_index, UCHAR *color) {
    INT returnValue;
    return returnValue;
}

INT wifi_getAvailableBSSColor(INT radio_index, INT maxNumberColors, UCHAR* colorList, INT *numColorReturned) {
    INT returnValue;
    return returnValue;
}

INT wifi_getMuEdca(INT radio_index, wifi_access_category_t ac, wifi_edca_t *edca) {
    INT returnValue;
    return returnValue;
}

INT wifi_setDownlinkDataAckType(INT radio_index,
                                wifi_dl_data_ack_type_t ack_type) {
    INT returnValue;
    return returnValue;
}

INT wifi_get80211axDefaultParameters(INT radio_index, wifi_80211ax_params_t    *params) {
    INT returnValue;
    return returnValue;
}

INT wifi_setRadioOperatingParameters(wifi_radio_index_t index, wifi_radio_operationParam_t *operationParam) {
    INT returnValue;
    return returnValue;
}

INT wifi_getRadioOperatingParameters(wifi_radio_index_t index, wifi_radio_operationParam_t *operationParam) {
    INT returnValue;
    return returnValue;
}

INT wifi_getScanResults(wifi_radio_index_t index, wifi_channel_t *channel, wifi_bss_info_t **bss, UINT *num_bss) {
    INT returnValue;
    return returnValue;
}

 )(wifi_radio_index_t index, wifi_bss_info_t **bss, UINT *num_bss) {
}

void wifi_scanResults_callback_register(wifi_scanResults_callback callback_proc) {
}
