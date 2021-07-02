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
#ifndef __WIFI_HAL_TELEMETRY_H__
#define __WIFI_HAL_TELEMETRY_H__

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @addtogroup WIFI_HAL_TYPES
 * @{
 */
typedef struct _wifi_radioTrafficStats2
{
     ULONG radio_BytesSent;     /**< The total number of bytes transmitted out of the interface, including framing characters. */
     ULONG radio_BytesReceived; /**< The total number of bytes received on the interface, including framing characters. */
     ULONG radio_PacketsSent;   /**< The total number of packets transmitted out of the interface. */
     ULONG radio_PacketsReceived; /**< The total number of packets received on the interface. */

     ULONG radio_ErrorsSent;    /**< The total number of outbound packets that could not be transmitted because of errors. */
     ULONG radio_ErrorsReceived;    /**< The total number of inbound packets that contained errors preventing them from being delivered to a higher-layer protocol. */
     ULONG radio_DiscardPacketsSent; /**< The total number of outbound packets which were chosen to be discarded even though no errors had been detected to prevent their being transmitted. One possible reason for discarding such a packet could be to free up buffer space. */
     ULONG radio_DiscardPacketsReceived; /**< The total number of inbound packets which were chosen to be discarded even though no errors had been detected to prevent their being delivered. One possible reason for discarding such a packet could be to free up buffer space. */
     ULONG radio_PLCPErrorCount;    /**< The number of packets that were received with a detected Physical Layer Convergence Protocol (PLCP) header error.    */
     ULONG radio_FCSErrorCount;     /**< The number of packets that were received with a detected FCS error. This parameter is based on dot11FCSErrorCount from [Annex C/802.11-2012]. */
     ULONG radio_InvalidMACCount;   /**< The number of packets that were received with a detected invalid MAC header error. */
     ULONG radio_PacketsOtherReceived;  /**< The number of packets that were received, but which were destined for a MAC address that is not associated with this interface. */
     INT   radio_NoiseFloor;        /**< The noise floor for this radio channel where a recoverable signal can be obtained. Expressed as a signed integer in the range (-110:0).  Measurement should capture all energy (in dBm) from sources other than Wi-Fi devices as well as interference from Wi-Fi devices too weak to be decoded. Measured in dBm */
     ULONG radio_ChannelUtilization; /**< Percentage of time the channel was occupied by the radio's own activity (Activity Factor) or the activity of other radios.  Channel utilization MUST cover all user traffic, management traffic, and time the radio was unavailable for CSMA activities, including DIFS intervals, etc.  The metric is calculated and updated in this parameter at the end of the interval defined by "Radio Statistics Measuring Interval".  The calculation of this metric MUST only use the data collected from the just completed interval.  If this metric is queried before it has been updated with an initial calculation, it MUST return -1.  Units in Percentage */
     INT   radio_ActivityFactor; /**< Percentage of time that the radio was transmitting or receiving Wi-Fi packets to/from associated clients. Activity factor MUST include all traffic that deals with communication between the radio and clients associated to the radio as well as management overhead for the radio, including NAV timers, beacons, probe responses,time for receiving devices to send an ACK, SIFC intervals, etc.  The metric is calculated and updated in this parameter at the end of the interval defined by "Radio Statistics Measuring Interval".  The calculation of this metric MUST only use the data collected from the just completed interval.   If this metric is queried before it has been updated with an initial calculation, it MUST return -1. Units in Percentage */
     INT   radio_CarrierSenseThreshold_Exceeded; /**< Percentage of time that the radio was unable to transmit or receive Wi-Fi packets to/from associated clients due to energy detection (ED) on the channel or clear channel assessment (CCA). The metric is calculated and updated in this Parameter at the end of the interval defined by "Radio Statistics Measuring Interval".  The calculation of this metric MUST only use the data collected from the just completed interval.  If this metric is queried before it has been updated with an initial calculation, it MUST return -1. Units in Percentage */
     INT   radio_RetransmissionMetirc; /**< Percentage of packets that had to be re-transmitted. Multiple re-transmissions of the same packet count as one.  The metric is calculated and updated in this parameter at the end of the interval defined by "Radio Statistics Measuring Interval".   The calculation of this metric MUST only use the data collected from the just completed interval.  If this metric is queried before it has been updated with an initial calculation, it MUST return -1. Units  in percentage */
     INT   radio_MaximumNoiseFloorOnChannel; /**< Maximum Noise on the channel during the measuring interval.  The metric is updated in this parameter at the end of the interval defined by "Radio Statistics Measuring Interval".  The calculation of this metric MUST only use the data collected in the just completed interval.  If this metric is queried before it has been updated with an initial calculation, it MUST return -1.  Units in dBm */
     INT   radio_MinimumNoiseFloorOnChannel; /**< Minimum Noise on the channel. The metric is updated in this Parameter at the end of the interval defined by "Radio Statistics Measuring Interval".  The calculation of this metric MUST only use the data collected in the just completed interval.  If this metric is queried before it has been updated with an initial calculation, it MUST return -1. Units in dBm */
     INT   radio_MedianNoiseFloorOnChannel; /**< Median Noise on the channel during the measuring interval.   The metric is updated in this parameter at the end of the interval defined by "Radio Statistics Measuring Interval".  The calculation of this metric MUST only use the data collected in the just completed interval.  If this metric is queried before it has been updated with an initial calculation, it MUST return -1. Units in dBm */
     ULONG radio_StatisticsStartTime;   /**< The date and time at which the collection of the current set of statistics started.  This time must be updated whenever the radio statistics are reset. */
    
} wifi_radioTrafficStats2_t;    //for radio only

typedef struct _wifi_ssidTrafficStats2
{
     ULONG ssid_BytesSent;  /**< The total number of bytes transmitted out of the interface, including framing characters. */
     ULONG ssid_BytesReceived;  /**< The total number of bytes received on the interface, including framing characters. */
     ULONG ssid_PacketsSent;    /**< The total number of packets transmitted out of the interface. */
     ULONG ssid_PacketsReceived; /**< The total number of packets received on the interface. */

     ULONG ssid_RetransCount;   /**< The total number of transmitted packets which were retransmissions. Two retransmissions of the same packet results in this counter incrementing by two. */
     ULONG ssid_FailedRetransCount; /**< The number of packets that were not transmitted successfully due to the number of retransmission attempts exceeding an 802.11 retry limit. This parameter is based on dot11FailedCount from [802.11-2012]. */
     ULONG ssid_RetryCount;  /**< The number of packets that were successfully transmitted after one or more retransmissions. This parameter is based on dot11RetryCount from [802.11-2012]. */
     ULONG ssid_MultipleRetryCount; /**< The number of packets that were successfully transmitted after more than one retransmission. This parameter is based on dot11MultipleRetryCount from [802.11-2012]. */
     ULONG ssid_ACKFailureCount;  /**< The number of expected ACKs that were never received. This parameter is based on dot11ACKFailureCount from [802.11-2012]. */    
     ULONG ssid_AggregatedPacketCount; /**< The number of aggregated packets that were transmitted. This applies only to 802.11n and 802.11ac. */

     ULONG ssid_ErrorsSent; /**< The total number of outbound packets that could not be transmitted because of errors. */
     ULONG ssid_ErrorsReceived;    /**< The total number of inbound packets that contained errors preventing them from being delivered to a higher-layer protocol. */
     ULONG ssid_UnicastPacketsSent;    /**< The total number of inbound packets that contained errors preventing them from being delivered to a higher-layer protocol. */
     ULONG ssid_UnicastPacketsReceived;  /**< The total number of received packets, delivered by this layer to a higher layer, which were not addressed to a multicast or broadcast address at this layer. */
     ULONG ssid_DiscardedPacketsSent; /**< The total number of outbound packets which were chosen to be discarded even though no errors had been detected to prevent their being transmitted. One possible reason for discarding such a packet could be to free up buffer space. */
     ULONG ssid_DiscardedPacketsReceived; /**< The total number of inbound packets which were chosen to be discarded even though no errors had been detected to prevent their being delivered. One possible reason for discarding such a packet could be to free up buffer space. */
     ULONG ssid_MulticastPacketsSent; /**< The total number of packets that higher-level protocols requested for transmission and which were addressed to a multicast address at this layer, including those that were discarded or not sent. */
     ULONG ssid_MulticastPacketsReceived; /**< The total number of received packets, delivered by this layer to a higher layer, which were addressed to a multicast address at this layer.  */
     ULONG ssid_BroadcastPacketsSent;  /**< The total number of packets that higher-level protocols requested for transmission and which were addressed to a broadcast address at this layer, including those that were discarded or not sent. */
     ULONG ssid_BroadcastPacketsRecevied; /**< The total number of packets that higher-level protocols requested for transmission and which were addressed to a broadcast address at this layer, including those that were discarded or not sent. */
     ULONG ssid_UnknownPacketsReceived;  /**< The total number of packets received via the interface which were discarded because of an unknown or unsupported protocol. */

} wifi_ssidTrafficStats2_t;  //for ssid only

//Please do not edit the elements for this data structure 
typedef struct _wifi_neighbor_ap2
{
     CHAR  ap_SSID[64];     /**< The current service set identifier in use by the neighboring WiFi SSID. The value MAY be empty for hidden SSIDs. */
     CHAR  ap_BSSID[64];    /**< [MACAddress] The BSSID used for the neighboring WiFi SSID. */
     CHAR  ap_Mode[64];     /**< The mode the neighboring WiFi radio is operating in. Enumeration of: AdHoc, Infrastructure */
     UINT  ap_Channel;      /**< The current radio channel used by the neighboring WiFi radio. */
     INT   ap_SignalStrength;   /**< An indicator of radio signal strength (RSSI) of the neighboring WiFi radio measured indBm, as an average of the last 100 packets received. */
     CHAR  ap_SecurityModeEnabled[64];  /**< The type of encryption the neighboring WiFi SSID advertises. Enumeration of:None, WPA-WPA2 etc. */
     CHAR  ap_EncryptionMode[64];   /**< Comma-separated list of strings. The type of encryption the neighboring WiFi SSID advertises. Each list item is an enumeration of: TKIP, AES */
     CHAR  ap_OperatingFrequencyBand[16];   /**< Indicates the frequency band at which the radio this SSID instance is operating. Enumeration of:2.4GHz, 5GHz */
     CHAR  ap_SupportedStandards[64];   /**< Comma-separated list of strings. List items indicate which IEEE 802.11 standards thisResultinstance can support simultaneously, in the frequency band specified byOperatingFrequencyBand. Each list item is an enumeration of: */
     CHAR  ap_OperatingStandards[16];   /**< Comma-separated list of strings. Each list item MUST be a member of the list reported by theSupportedStandardsparameter. List items indicate which IEEE 802.11 standard that is detected for thisResult. */
     CHAR  ap_OperatingChannelBandwidth[16];    /**< Indicates the bandwidth at which the channel is operating. Enumeration of: */
     UINT  ap_BeaconPeriod;     /**< Time interval (inms) between transmitting beacons. */
     INT   ap_Noise;    /**< Indicator of average noise strength (indBm) received from the neighboring WiFi radio. */
     CHAR  ap_BasicDataTransferRates[256];  /**< Comma-separated list (maximum list length 256) of strings. Basic data transmit rates (in Mbps) for the SSID. For example, ifBasicDataTransferRatesis "1,2", this indicates that the SSID is operating with basic rates of 1 Mbps and 2 Mbps. */
     CHAR  ap_SupportedDataTransferRates[256];  /**< Comma-separated list (maximum list length 256) of strings. Data transmit rates (in Mbps) for unicast frames at which the SSID will permit a station to connect. For example, ifSupportedDataTransferRatesis "1,2,5.5", this indicates that the SSID will only permit connections at 1 Mbps, 2 Mbps and 5.5 Mbps. */
     UINT  ap_DTIMPeriod;   /**< The number of beacon intervals that elapse between transmission of Beacon frames containing a TIM element whose DTIM count field is 0. This value is transmitted in the DTIM Period field of beacon frames. [802.11-2012] */
     UINT  ap_ChannelUtilization;   /**< Indicates the fraction of the time AP senses that the channel is in use by the neighboring AP for transmissions. */
} wifi_neighbor_ap2_t;    //COSA_DML_NEIGHTBOURING_WIFI_RESULT

/*    Explanation:
                             these are actually 3 host-endian integers
                            in this example they are big-endian because
                             the piranha's host cpu is big-endian MIPS
                                    _____________|____________
                                   /             |            \
                                  |              |            |
                             _____|______    ____|____    ____|_____
                            |            |  |         |  |          |
     ap1       glastackrssi:75  74  73  77  2  3  68  1  0  0  0  136
                            ^^^^^^^^^^^^^^  ^^^^^^^^^^^  ^^^^^^^^^^^^
                                  |              |            |
                         last 4 rssi values      |      sample counter
                                                 |
                                         last 4 rssi's age
    
                                the "77" rssi is 1 second old
                                         ______|______
                                        /             \
                                        |             |
     ap1       glastackrssi:75  74  73  77  2  3  68  1  0  0  0  136
                                     |             |
                                     \____________/
                                           |
                                 the 2nd most recent rssi of "73"
                                 is 68 seconds old *in relation*
                                 to the 1st ("77") therefore it is
                                 68 + 1 seconds old *now*   */
typedef struct _wifi_rssi_snapshot {
    UCHAR  rssi[4];                               /**< Last 4 RSSI frames received */
    UCHAR  time_s[4];                                  /**< Time of when last 4 RSSI were received */
    USHORT count;                                      /**< Sequence numer of received managemant (bcn, ack) frames  */
} wifi_rssi_snapshot_t;

#ifdef WIFI_HAL_VERSION_3_PHASE2
typedef struct _wifi_apRssi {  
    CHAR  ap_BSSID[6];              /**< BSSID */
    wifi_channelBandwidth_t   ap_channelWidth;         /**< The channel width; 1 for 20Mhz, 2 for 40 MHz, 4 for 80 MHz, 8 for 160 MHz, 10 for 80+80Mhz */
    INT   ap_rssi;                  /**< RSSI of the neighboring AP in dBm. */
} wifi_apRssi_t;
#else
typedef struct _wifi_apRssi {  
    CHAR  ap_BSSID[6];              /**< BSSID */
    UINT   ap_channelWidth;         /**< The channel width; 1 for 20Mhz, 2 for 40 MHz, 4 for 80 MHz, 8 for 160 MHz, 10 for 80+80Mhz */
    INT   ap_rssi;                  /**< RSSI of the neighboring AP in dBm. */
} wifi_apRssi_t;
#endif

// VAP telemetry report structures and function prototypes
#define MAX_VAP (MAX_NUM_RADIOS*MAX_NUM_VAP_PER_RADIO)
/**
 * @brief VAP Telemetry information.
 *
 * Structure which holds the VAP Telemetry information.
 */
typedef struct {
    UINT                txOverflow;            // WiFi TX overflow counter.
} wifi_VAPTelemetry_t;

/** @} */  //END OF GROUP WIFI_HAL_TYPES

/**
 * @addtogroup WIFI_HAL_APIS
 * @{
 */
/* wifi_getRadioTrafficStats2() function */
/**
* @brief Get detail radio traffic static info.
*
* @param[in]  radioIndex      Index of Wi-Fi radio channel
* @param[out] output_struct   wifi_radioTrafficStats2_t *output_struct, all traffic stats info to be returned
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
INT wifi_getRadioTrafficStats2(INT radioIndex, wifi_radioTrafficStats2_t *output_struct);

/* wifi_getSSIDTrafficStats2() function */
/**
* @brief Get the basic SSID traffic static info.
*
* @param[in]  ssidIndex      SSID index
* @param[out] output_struct  SSID traffic status.
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
INT wifi_getSSIDTrafficStats2(INT ssidIndex, wifi_ssidTrafficStats2_t *output_struct);


#ifdef WIFI_HAL_VERSION_3_PHASE2
/**
* @brief Returns the Wifi scan status.
*
* @param[in]  radioIndex           Radio index
* @param[in]  scan                 Start a neighbour scan
* @param[out] neighbor_ap_array    Neighbour access point info to be returned
* @param[out] output_array_size    Length of the output array.
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
INT wifi_getNeighboringWiFiStatus(INT radioIndex, BOOL scan, wifi_neighbor_ap2_t **neighbor_ap_array, UINT *output_array_size);
#endif

/* wifi_getRadioBandUtilization() function */
/**
* @brief To read the radio band utilization.
*
* @param[in]  radioIndex         Radio Index
* @param[out] output_percentage  Radio band utilization percentage, to be returned
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
INT wifi_getRadioBandUtilization (INT radioIndex, INT *output_percentage);

INT wifi_getApAssociatedDeviceDiagnosticResult3(INT apIndex, wifi_associated_dev3_t **associated_dev_array, UINT *output_array_size);

#ifdef WIFI_HAL_VERSION_3_PHASE2
INT wifi_getApAssociatedClientDiagnosticResult(INT apIndex, mac_address_t mac_addr, wifi_associated_dev3_t *dev_conn);
#endif

/* wifi_setClientDetailedStatisticsEnable() function */
/**
* @brief This function enabled/disabled collection of detailed statistics of associated clients on Access Point. 
*
* @param[in] radioIndex          Radio Index
* @param[in] enable              enable/disable 
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
INT wifi_setClientDetailedStatisticsEnable(INT radioIndex, BOOL enable);

/**
* @brief This API returns the radio enabled status.
*
* The radio status switch in driver include Transmission status, background channel scan, capacity status etc
* Radio Status should be disabled by default.
* If driver do not support those switch, or switch has enabled by default, please just fillup with stumb function.
*
* @param[in]  radioIndex      Index of the radio array.
* @param[out] output_enable   Radio enabled status.
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
INT wifi_getRadioStatsEnable(INT radioIndex, BOOL *output_enable);

/**
* @brief This API is to enable/disable radio status.
*
* @param[in]  radioIndex      Index of the radio array.
* @param[out] output_enable   Radio enabled status.
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
INT wifi_setRadioStatsEnable(INT radioIndex, BOOL enable);

/* @description Get the VAP Telemetry data.
 *
 * @param[in] apIndex - Access Point index.
 * @param[out] telemetry - structure for vap telemetry data.
 *
 * @return The status of the operation.
 * @retval RETURN_OK if successful.
 * @retval RETURN_ERR if any error is detected.
 */
INT wifi_getVAPTelemetry(UINT apIndex, wifi_VAPTelemetry_t *telemetry);

/** @} */  //END OF GROUP WIFI_HAL_APIS

#ifdef __cplusplus
}
#endif

#endif