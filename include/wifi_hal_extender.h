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

#ifndef __WIFI_HAL_EXTENDER_H__
#define __WIFI_HAL_EXTENDER_H__

#ifdef __cplusplus
extern "C"{
#endif

#include "wifi_hal_telemetry.h"
/**
 * @addtogroup WIFI_HAL_TYPES
 * @{
 */

typedef struct _wifi_channelStats {
    INT  ch_number;                        /**< each channel is only 20MHz bandwidth */
    BOOL ch_in_pool;                    /**< If ch_in_pool is FALSE, driver do not need to scan this channel */
    INT  ch_noise;                      /**< this is used to return the average noise floor in dbm */
    BOOL ch_radar_noise;                /**< if ch_number is in DFS channel, this is used to return if radar signal is present on DFS channel (5G only) */
    INT  ch_max_80211_rssi;             /**< max RSSI from the neighbor AP in dbm on this channel. */
    INT  ch_non_80211_noise;            /**< average non 802.11 noise */
    INT  ch_utilization;                /**< this is used to return the 802.11 utilization in percent */
    ULLONG ch_utilization_total;        /**<  Total time radio spent receiving or transmitting on that channel (ch_utilization_active) */
    ULLONG ch_utilization_busy;         /**<  Time radio detected that channel was busy (Busy = Rx + Tx + Interference) */
    ULLONG ch_utilization_busy_tx;      /**<  Time time radio spent transmitting on channel */
    ULLONG ch_utilization_busy_rx;      /**<  Time radio spent receiving on channel (Rx = Rx_obss + Rx_self + Rx_errr (self and obss errors) */
    ULLONG ch_utilization_busy_self;    /**< Time radio spend receiving on channel from its own connected clients */
    ULLONG ch_utilization_busy_ext;     /**< Time radio detected that extended channel was busy (40MHz extention channel busy */
} wifi_channelStats_t;                  //<!This data structure is for each channel

/* MCS/NSS/BW rate table and indexes that should be used for supported rates
----------------------------------------------
| type | bw         | nss        |  mcs     
----------------------------------------------
| OFDM | 0 (20Mhz)  | 0 (legacy) |  0 - 6M 
|      |            |            |  1 - 9M 
|      |            |            |  2 - 12M 
|      |            |            |  3 - 18M 
|      |            |            |  4 - 24M 
|      |            |            |  5 - 36M 
|      |            |            |  6 - 48M 
|      |            |            |  7 - 54M
----------------------------------------------
| CCK  | 0 (20Mhz)  | 0 (legacy) |  8 - L1M 
|      |            |            |  9 - L2M 
|      |            |            | 10 - L5.5M
|      |            |            | 11 - L11M 
|      |            |            | 12 - S2M 
|      |            |            | 13 - S5.5M
|      |            |            | 14 - S11M"
----------------------------------------------
| VHT  | 0 (20Mhz)  | 1 (chain1) |  1 - HT/VHT
|      | 1 (40Mhz)  | ...        |  2 - HT/VHT
|      | 2 (80MHz)  | 8 (chain8) |  3 - HT/VHT
|      | 2 (160MHz) |            |  4 - HT/VHT
|      |            |            |  5 - HT/VHT
|      |            |            |  6 - HT/VHT
|      |            |            |  7 - HT/VHT
|      |            |            |  8 - VHT 
|      |            |            |  9 - VHT 
----------------------------------------------
NOTE: The size of this table on 4x4 can be big - we could send only non zero elements!
*/
typedef struct _wifi_associated_dev_rate_info_rx_stats {
        // rate table index see table above
    UCHAR nss;                  /**< 0 equals legacy protocols (OFDM, CCK) 1 - n spatial stream (HT, VHT) */
    UCHAR mcs;                  /**< 0 - 7 (HT) - 9 (VHT) */
    USHORT bw;                  /**< 20, 40, 80, 160 ... (to be considered 5 , 10, 80+80) ... */
    ULLONG flags;               /**< Flag indicating data validation that HAS_BYTES, HAS_MSDUS, HAS_MPDUS, HAS_PPDUS, HAS_BW_80P80, HAS_RSSI_COMB, HAS_RSSI_ARRAY */
    ULLONG bytes;               /**< number of bytes received for given rate */
    ULLONG msdus;               /**< number of MSDUs received for given rate */
    ULLONG mpdus;               /**< number of MPDUs received for given rate */
    ULLONG ppdus;               /**< number of PPDUs received for given rate */
    ULLONG retries;             /**< number of retries received for given rate */
    UCHAR rssi_combined;        /**< Last RSSI received on give rate */
    /* Per antenna RSSI (above noise floor) for all widths (primary,secondary) 
        -----------------------------------------------
        | chain_num |  20MHz [pri20                   ]
        |           |  40MHZ [pri20,sec20             ] 
        |           |  80MHz [pri20,sec20,sec40,      ]
        |           | 160MHz [pri20,sec20,sec40,sec80 ]
        -----------------------------------------------
        |  1        |  rssi  [pri20,sec20,sec40,sec80 ]
        |  ...      |  ...
        |  8        |  rssi  [pri20,sec20,sec40,sec80 ]
        -----------------------------------------------    */
    UCHAR rssi_array[8][4];         //<! 8=antennas, 4=20+20+40+80 extension rssi
} wifi_associated_dev_rate_info_rx_stats_t;

typedef struct _wifi_associated_dev_rate_info_tx_stats {
        // rate table index see table above
    UCHAR nss;                      /**< 0 equals legacy protocols (OFDM, CCK) 1 - n spatial stream (HT, VHT) */
    UCHAR mcs;                      /**< 0 - 7 (HT) - 9 (VHT) */
    USHORT bw;                      /**< 20, 40, 80, 160 ... (to be considered 5 , 10, 80+80) ... */
    ULLONG flags;                   /**< Flag indicating data validation that HAS_BYTES, HAS_MSDUS, HAS_MPDUS, HAS_PPDUS, HAS_BW_80P80, HAS_RSSI_COMB, HAS_RSSI_ARRAY */
    ULLONG bytes;                   /**< number of bytes transmitted for given rate */
    ULLONG msdus;                   /**< number of MSDUs transmitted for given rate */
    ULLONG mpdus;                   /**< number of MPDUs transmitted for given rate */
    ULLONG ppdus;                   /**< number of PPDUs transmitted for given rate */
    ULLONG retries;                 /**< number of transmission retries for given rate */
    ULLONG attempts;                /**< number of attempts trying transmit on given rate */
} wifi_associated_dev_rate_info_tx_stats_t;

typedef struct wifi_associated_dev_tid_entry
{
    UCHAR  ac;                      /**< BE, BK. VI, VO (wifi_radioQueueType_t) */
    UCHAR  tid;                     /**< 0 - 16 */
    ULLONG ewma_time_ms;            /**< Moving average value based on last couple of transmitted msdus */
    ULLONG sum_time_ms;             /**< Delta of cumulative msdus times over interval */
    ULLONG num_msdus;               /**< Number of msdus in given interval */
} wifi_associated_dev_tid_entry_t;

typedef struct wifi_associated_dev_tid_stats
{
    wifi_associated_dev_tid_entry_t tid_array[16];
} wifi_associated_dev_tid_stats_t;

typedef struct _wifi_associated_dev_stats {
    ULLONG     cli_rx_bytes;               /**< The total number of bytes received from the client device, including framing characters. */
    ULLONG     cli_tx_bytes;               /**< The total number of bytes transmitted to the client device, including framing characters. */
    ULLONG     cli_rx_frames;              /**< The total number of frames received from the client */
    ULLONG     cli_tx_frames;              /**< The total number of frames transmitted to the client */
    ULLONG     cli_rx_retries;             /**< Number of rx retries */
    ULLONG     cli_tx_retries;             /**< Number of tx retries. cli_Retransmissions */
    ULLONG     cli_rx_errors;              /**< Number of numer of rx error */
    ULLONG     cli_tx_errors;              /**< Number of tx errors */
    double     cli_rx_rate;                /**< average rx data rate used */
    double     cli_tx_rate;                /**< average tx data rate used} wifi_associated_dev_t; */
    wifi_rssi_snapshot_t cli_rssi_bcn;      /**< RSSI from last 4 beacons received (STA) */
    wifi_rssi_snapshot_t cli_rssi_ack;      /**< RSSI from last 4 ack received     (AP) */
} wifi_associated_dev_stats_t;

/**
 * @brief Configuration per apIndex
 *
 * This defines the configuration for each @b apIndex added to a steering
 * group
 *
 * Channel utilization is to be sampled every @b utilCheckIntervalSec seconds,
 * and after collecting $b utilAvgCount samples, the steering event
 * @b WIFI_STEERING_EVENT_CHAN_UTILIZATION should be sent with the averaged value.
 *
 * Client active/inactive checking is done every @b inactCheckIntervalSec seconds
 * and if a given client is idle/inactive for @b inactCheckThresholdSec seconds then
 * it should be marked as inactive.  Whenever a client changes states between active
 * and inactive, the steering event @b WIFI_STEERING_EVENT_CLIENT_ACTIVITY should be
 * sent.
 */
typedef struct {
    INT         apIndex;

    UINT        utilCheckIntervalSec;   /**< Channel utilization check interval        */
    UINT        utilAvgCount;           /**< Number of samples to average           */

    UINT        inactCheckIntervalSec;  /**< Client inactive check interval        */
    UINT        inactCheckThresholdSec; /**< Client inactive threshold              */
} wifi_steering_apConfig_t;

/**
 * @brief Configuration per Client
 *
 * This defines the per-client, per-apIndex configuration settings.  The
 * high water mark + low water mark pairs define RSSI ranges, in which
 * given packet types (probe or auth) are responded to as long as the RSSI
 * of the request packet is within the defined range.
 *
 * The RSSI crossings define thresholds which result in steering events
 * being generated when a connected clients RSSI crosses above or below
 * the given threshold.
 *
 * authRejectReason, when non-zero, results in auth requests being
 * rejected with the given reason code.  When set to zero, auth requests
 * that do not fall in the RSSI hwm+lwm range will be silently ignored.
 *
 * @see https://supportforums.cisco.com/document/141136/80211-association-status-80211-deauth-reason-codes
 */
typedef struct {
    UINT        rssiProbeHWM;           /**< Probe response RSSI high water mark    */
    UINT        rssiProbeLWM;           /**< Probe response RSSI low water mark     */
    UINT        rssiAuthHWM;            /**< Auth response RSSI high water mark     */
    UINT        rssiAuthLWM;            /**< Auth response RSSI low water mark      */
    UINT        rssiInactXing;          /**< Inactive RSSI crossing threshold       */
    UINT        rssiHighXing;           /**< High RSSI crossing threshold           */
    UINT        rssiLowXing;            /**< Low RSSI crossing threshold            */
    UINT        authRejectReason;       /**< Inactive RSSI crossing threshold       */
} wifi_steering_clientConfig_t;

/**
 * @brief Wifi Disconnect Sources
 *
 * These are the possible sources of a wifi disconnect.
 * If the disconnect was initiated by the client, then @b DISCONNECT_SOURCE_REMOTE
 * should be used.
 * If initiated by the local AP, then @b DISCONNECT_SOURCE_LOCAL should be used.
 * If this information is not available, then @b DISCONNECT_SOURCE_UNKNOWN should be used.
 */
typedef enum {
    DISCONNECT_SOURCE_UNKNOWN               = 0,    /**< Unknown source             */
    DISCONNECT_SOURCE_LOCAL,                        /**< Initiated locally          */
    DISCONNECT_SOURCE_REMOTE                        /**< Initiated remotely         */
} wifi_disconnectSource_t;

/**
 * @brief Wifi Disconnect Types
 * These are the types of wifi disconnects.
 */
typedef enum {
    DISCONNECT_TYPE_UNKNOWN                 = 0,    /**< Unknown type               */
    DISCONNECT_TYPE_DISASSOC,                       /**< Disassociation             */
    DISCONNECT_TYPE_DEAUTH                          /**< De-authentication           */
} wifi_disconnectType_t;

/**
 * @brief Wifi Steering Event Types
 * These are the different steering event types that are sent by the wifi_hal
 * steering library.
 */
typedef enum {
    WIFI_STEERING_EVENT_PROBE_REQ           = 1,    /**< Probe Request Event                             */
    WIFI_STEERING_EVENT_CLIENT_CONNECT,             /**< Client association completed successfully Event */
    WIFI_STEERING_EVENT_CLIENT_DISCONNECT,          /**< Client Disconnect Event                         */
    WIFI_STEERING_EVENT_CLIENT_ACTIVITY,            /**< Client Active Change Event                      */
    WIFI_STEERING_EVENT_CHAN_UTILIZATION,           /**< Channel Utilization Event                       */
    WIFI_STEERING_EVENT_RSSI_XING,                  /**< Client RSSI Crossing Event                      */
    WIFI_STEERING_EVENT_RSSI,                       /**< Instant Measurement Event                       */
    WIFI_STEERING_EVENT_AUTH_FAIL                   /**< Client Auth Failure Event                       */
} wifi_steering_eventType_t;

/**
 * @brief RSSI Crossing Values
 * These are the RSSI crossing values provided in RSSI crossing events
 */
typedef enum {
    WIFI_STEERING_RSSI_UNCHANGED            = 0,    /**< RSSI hasn't crossed        */
    WIFI_STEERING_RSSI_HIGHER,                      /**< RSSI went higher           */
    WIFI_STEERING_RSSI_LOWER                        /**< RSSI went lower            */
} wifi_steering_rssiChange_t;

/**
 * @brief STA datarate information
 * These are STA capabilities values
 */
typedef struct {
    UINT                            maxChwidth;         /**< Max bandwidth supported                */
    UINT                            maxStreams;         /**< Max spatial streams supported          */
    UINT                            phyMode;            /**< PHY Mode supported                     */
    UINT                            maxMCS;             /**< Max MCS  supported                     */
    UINT                            maxTxpower;         /**< Max TX power supported                 */
    UINT                            isStaticSmps;       /**< Operating in Static SM Power Save Mode */
    UINT                            isMUMimoSupported;  /**< Supports MU-MIMO                       */
} wifi_steering_datarateInfo_t;

typedef struct {
    BOOL                            linkMeas;           /**< Supports link measurement      */
    BOOL                            neighRpt;           /**< Supports neighbor reports      */
    BOOL                            bcnRptPassive;      /**< Supports Passive 11k scans     */
    BOOL                            bcnRptActive;       /**< Supports Active 11k scans      */
    BOOL                            bcnRptTable;        /**< Supports beacon report table   */
    BOOL                            lciMeas;            /**< Supports LCI measurement       */
    BOOL                            ftmRangeRpt;        /**< Supports FTM Range report      */
} wifi_steering_rrmCaps_t;

/**
 * @brief Probe Request Event Data
 * This data is provided with @b WIFI_STEERING_EVENT_PROBE_REQ
 */
typedef struct {
    mac_address_t                   client_mac;     /**< Client MAC Address         */
    UINT                            rssi;           /**< RSSI of probe frame        */
    BOOL                            broadcast;      /**< TRUE if broadcast probe    */
    BOOL                            blocked;        /**< TRUE if response blocked   */
} wifi_steering_evProbeReq_t;

#ifdef WIFI_HAL_VERSION_3_PHASE2

/**
 * @brief Client Connect Event Data
 * This data is provided with @b WIFI_STEERING_EVENT_CLIENT_CONNECT
 */
typedef struct {
    mac_address_t                   client_mac;     /**< Client MAC Address                     */
    UINT                            isBTMSupported; /**< Client supports BSS TM                 */
    UINT                            isRRMSupported; /**< Client supports RRM                    */
    wifi_freq_bands_t               bandsCap;       /**< Bitmask with the frequencies that the Client is capable */
    wifi_steering_datarateInfo_t    datarateInfo;   /**< Client supported datarate information  */
    wifi_steering_rrmCaps_t         rrmCaps;        /**< Client supported RRM capabilites       */
} wifi_steering_evConnect_t;

#else
/**
 * @brief Client Connect Event Data
 * This data is provided with @b WIFI_STEERING_EVENT_CLIENT_CONNECT
 */
typedef struct {
    mac_address_t                   client_mac;     /**< Client MAC Address                     */
    UINT                            isBTMSupported; /**< Client supports BSS TM                 */
    UINT                            isRRMSupported; /**< Client supports RRM                    */
    BOOL                            bandCap2G;      /**< Client is 2.4GHz capable               */
    BOOL                            bandCap5G;      /**< Client is 5GHz capable                 */
    wifi_steering_datarateInfo_t    datarateInfo;   /**< Client supported datarate information  */
    wifi_steering_rrmCaps_t         rrmCaps;        /**< Client supported RRM capabilites       */
} wifi_steering_evConnect_t;
#endif

/**
 * @brief Client Disconnect Event Data
 * This data is provided with @b WIFI_STEERING_EVENT_CLIENT_DISCONNECT
 */
typedef struct {
    mac_address_t                   client_mac;     /**< Client MAC Address         */
    UINT                            reason;         /**< Reason code of disconnect  */
    wifi_disconnectSource_t         source;         /**< Source of disconnect       */
    wifi_disconnectType_t           type;           /**< Disconnect Type            */
} wifi_steering_evDisconnect_t;

/**
 * @brief Client Activity Change Event Data
 * This data is provided with @b WIFI_STEERING_EVENT_CLIENT_ACTIVITY
 */
typedef struct {
    mac_address_t                   client_mac;     /**< Client MAC Address         */
    BOOL                            active;         /**< TRUE if client is active   */
} wifi_steering_evActivity_t;

/**
 * @brief Channel Utilization Event Data
 * This data is provided with @b WIFI_STEERING_EVENT_CHAN_UTILIZATION
 */
typedef struct {
    UINT                            utilization;    /**< Channel Utilization 0-100  */
} wifi_steering_evChanUtil_t;

/**
 * @brief Client RSSI Crossing Event Data
 * This data is provided with @b WIFI_STEERING_EVENT_RSSI_XING
 */
typedef struct {
    mac_address_t                   client_mac;     /**< Client MAC Address         */
    UINT                            rssi;           /**< Clients current RSSI       */
    wifi_steering_rssiChange_t      inactveXing;    /**< Inactive threshold Value   */
    wifi_steering_rssiChange_t      highXing;       /**< High threshold Value       */
    wifi_steering_rssiChange_t      lowXing;        /**< Low threshold value        */
} wifi_steering_evRssiXing_t;

/**
 * @brief Client RSSI Measurement Event Data
 * This data is provided with @b WIFI_STEERING_EVENT_RSSI, which is sent in
 * response to a requset for the client's current RSSI measurement
 */
typedef struct {
    mac_address_t                   client_mac;     /**< Client MAC Address         */
    UINT                            rssi;           /**< Clients current RSSI       */
} wifi_steering_evRssi_t;

/**
 * @brief Auth Failure Event Data
 * This data is provided with @b WIFI_STEERING_EVENT_AUTH_FAIL
 */
typedef struct {
    mac_address_t                   client_mac;     /**< Client MAC Address         */
    UINT                            rssi;           /**< RSSI of auth frame         */
    UINT                            reason;         /**< Reject Reason              */
    BOOL                            bsBlocked;      /**< TRUE if purposely blocked  */
    BOOL                            bsRejected;     /**< TRUE if rejection sent     */
} wifi_steering_evAuthFail_t;

/**
 * @brief Wifi Steering Event
 * This is the data containing a single steering event.
 */
typedef struct {
    wifi_steering_eventType_t       type;           /**< Event Type                 */
    INT                             apIndex;        /**< apIndex event is from      */
    ULLONG                          timestamp_ms;   /**< Optional: Event Timestamp  */
    union {
        wifi_steering_evProbeReq_t      probeReq;   /**< Probe Request Data         */
        wifi_steering_evConnect_t       connect;    /**< Client Connect Data        */
        wifi_steering_evDisconnect_t    disconnect; /**< Client Disconnect Data     */
        wifi_steering_evActivity_t      activity;   /**< Client Active Change Data  */
        wifi_steering_evChanUtil_t      chanUtil;   /**< Channel Utilization Data   */
        wifi_steering_evRssiXing_t      rssiXing;   /**< Client RSSI Crossing Data  */
        wifi_steering_evRssi_t          rssi;       /**< Client Measured RSSI Data  */
        wifi_steering_evAuthFail_t      authFail;   /**< Auth Failure Data          */
    } data;
} wifi_steering_event_t;

// 802.11v BSS Transition Management Definitions
#define MAX_BTM_DEVICES     64
#define MAX_URL_LEN         512
#define MAX_CANDIDATES      64
#define MAX_VENDOR_SPECIFIC 32

// BSS Termination Duration subelement, ID = 4, 802.11 section 9.4.2.2.
// This is a subelement because it is specific to Neighbor Report, and BTM
// Request Frame.
typedef struct {
    ULONG               tsf;    // 8 octet TSF timer value.
    USHORT              duration;
} wifi_BTMTerminationDuration_t;

typedef struct {
    CHAR                condensedStr[3];  // 2 char country code from do11CountryString.
} wifi_CondensedCountryString_t;

typedef struct {
    USHORT              offset;
    USHORT              interval;
} wifi_TSFInfo_t;

typedef struct {
    UCHAR               preference;
} wifi_BSSTransitionCandidatePreference_t;

typedef struct {
    USHORT              bearing;
    UINT                dist;
    USHORT              height;
} wifi_Bearing_t;

// Wide Bandwidth Channel Element, ID = 194.  802.11-2016 section 9.4.2.161.
typedef struct {
    UCHAR               bandwidth;
    UCHAR               centerSeg0;
    UCHAR               centerSeg1;
} wifi_WideBWChannel_t;

typedef struct {
    UCHAR                   token;
    UCHAR                   mode;
    UCHAR                   type;
    union {
        UCHAR               lci;
        UCHAR               lcr;
    } u;
} wifi_Measurement_t;

// HT Capabilities Element, ID = 45.  802.11-2016 section 9.4.2.56.
typedef struct {
    
    USHORT                  info;           // Bitfield where bit 0 is info[0] bit 0.
    UCHAR                   ampduParams;
    UCHAR                   mcs[16];        // Bitfield where bit 0 is mcs[0] bit 0.
    USHORT                  extended;       // Bitfield where bit 0 is ele_HTExtendedCapabilities[0] bit 0.
    UINT                    txBeamCaps;     // Bitfield where bit 0 is ele_TransmitBeamFormingCapabilities[0] bit 0.
    UCHAR                   aselCaps;
} wifi_HTCapabilities_t;

// VHT Capabilities Element, ID = 191.  802.11-2016 section 9.4.2.158.
typedef struct {
    UINT                    info;
    // The Supported VHT-MCS and NSS Set field is 64 bits long, but is broken
    // into 4 16 bit fields for convenience.
    USHORT                  mcs;
    USHORT                  rxHighestSupportedRate;
    USHORT                  txVHTmcs;
    USHORT                  txHighestSupportedRate;
} wifi_VHTCapabilities_t;

// HT OperationElement, ID = 61, 802.11-2016 section 9.4.2.57.
typedef struct {
    UCHAR                   primary;
    UCHAR                   opInfo[5];   // Bitfield where bit 0 is ele_HTOperationInfo[0] bit 0;
    UCHAR                   mcs[16];
} wifi_HTOperation_t;

// VHT Operation Element, ID = 192.  802.11-2016 section 9.4.2.159.
typedef struct {
    wifi_WideBWChannel_t        opInfo;         // channel width, center of seg0, center of seg1
    USHORT                      mcs_nss;        // Bit field.
} wifi_VHTOperation_t;

// Secondary Channel Offset Element, ID = 62, 802.11-2016 section
// 9.4.2.20.
typedef struct {
    UCHAR                       secondaryChOffset;
} wifi_SecondaryChannelOffset_t;

// RM Enabled Capabilities Element, ID = 70, 802.11-2016 section
// 9.4.2.45.
typedef struct {
    // This is a bit field defined by table 9-157.  Bit 0 for all of the
    // capabilities is ele_RMEnabledCapabilities[5] bit 0.
    UCHAR                       capabilities[5];
} wifi_RMEnabledCapabilities_t;

// Vendor Specific Element, ID = 221.  802.11-2016 section 9.4.2.26.
typedef struct {
    // 3 or 5 octet OUI depending on format; see 802.11-2016 section 9.4.1.32.
    UCHAR           oui[5];
    // Vendor specific content.
    UCHAR           buff[MAX_VENDOR_SPECIFIC];
} wifi_VendorSpecific_t;

// Measurement Pilot Transmission Element, ID = 66, 802.11-2016 section
// 9.4.2.42.
typedef struct {
    UCHAR                       pilot;
    // Series of (sub)elements.  Table 9-155 only lists vendor specific.
    wifi_VendorSpecific_t                       vendorSpecific;
} wifi_MeasurementPilotTransmission_t;


typedef struct {
    bssid_t             bssid;
    //  32 bit optional value, bit fileds are
    //  b0, b1 for reachability
    //  b2 security
    //  b3 key scope
    //  b4 to b9 capabilities
    //  b10 mobility domain
    //  b11 high throughput
    //  b12 very high throughput
    //  b13 ftm
    //  b14 to b31 reserved
    UINT                info;
    UCHAR               opClass;
    UCHAR               channel;
    UCHAR               phyTable;
    BOOL                tsfPresent;
    wifi_TSFInfo_t      tsfInfo;
    BOOL                condensedCountrySringPresent;
    wifi_CondensedCountryString_t   condensedCountryStr;
    BOOL                bssTransitionCandidatePreferencePresent;
    wifi_BSSTransitionCandidatePreference_t         bssTransitionCandidatePreference;
    BOOL                btmTerminationDurationPresent;
    wifi_BTMTerminationDuration_t   btmTerminationDuration;
    BOOL                bearingPresent;
    wifi_Bearing_t      bearing;
    BOOL                wideBandWidthChannelPresent;
    wifi_WideBWChannel_t    wideBandwidthChannel;
    BOOL                htCapsPresent;
    wifi_HTCapabilities_t   htCaps;
    BOOL                vhtCapsPresent;
    wifi_VHTCapabilities_t  vbhtCaps;
    BOOL                    htOpPresent;
    wifi_HTOperation_t      htOp;
    BOOL                    vhtOpPresent;
    wifi_VHTOperation_t     vhtOp;
    BOOL                    secondaryChannelOffsetPresent;
    wifi_SecondaryChannelOffset_t   secondaryChannelOffset;
    BOOL                    rmEnabledCapsPresent;
    wifi_RMEnabledCapabilities_t    rmEnabledCaps;
    BOOL                            msmtPilotTransmissionPresent;
    wifi_MeasurementPilotTransmission_t     msmtPilotTransmission;
    BOOL                    vendorSpecificPresent;
    wifi_VendorSpecific_t   vendorSpecific;
    ssid_t                  target_ssid;
} wifi_NeighborReport_t;

// BSS Transition Management Request Frame, 802.11-2016 section 9.6.14.9.
typedef struct {
    UCHAR               token;              /**< set by STA to relate reports */
    UCHAR               requestMode;        /**< Requested instructions for the STA. */
    USHORT              timer;
    UCHAR               validityInterval;
    // The optional fields may include:
    // 1. BSS Termination Duration Subelement, ID = 4. 802.11-2016 Figure 9-300.
    // 2. Session Information URL.
    // 3. BSS Transition Candidate List Entries
    wifi_BTMTerminationDuration_t    termDuration;
    UCHAR               disassociationImminent;
    USHORT              urlLen;
    CHAR                url[MAX_URL_LEN];
    UCHAR               numCandidates;
    wifi_NeighborReport_t    candidates[MAX_CANDIDATES];
} wifi_BTMRequest_t;

// BSS Transition Management Query Frame, 802.11-2016 section 9.6.14.8.
// Received from non-AP STA.
typedef struct {
    UCHAR                   token;          /**< set by STA to relate reports */
    UCHAR                   queryReason;
    UCHAR                   numCandidates;
    wifi_NeighborReport_t   candidates[MAX_CANDIDATES];
} wifi_BTMQuery_t;

// BSS Transition Management Response Frame, 802.11-2016 section 9.6.14.10.
// Received from non-AP STA.
typedef struct {
    UCHAR               token;          /**< set by STA to relate reports */
    UCHAR               status;
    UCHAR               terminationDelay;
    bssid_t             target;
    UCHAR                   numCandidates;
    wifi_NeighborReport_t    candidates[MAX_CANDIDATES];
} wifi_BTMResponse_t;

// 802.11-2016 section 9.6.7.6
typedef struct {
    UCHAR                   token;       /**< set by STA to relate reports */
    UCHAR                   ssidLen;     /**< set length to 0 if ssid is not present, otherwise to length of ssid field */
    ssid_t                  ssid;
    UCHAR                   measCount;      /**< Request for LCI/LCR may come in any order */
    wifi_Measurement_t      measurements[2];
} wifi_NeighborRequestFrame_t;

// 802.11k Beacon request & report structures and function prototypes
#define MAX_REQUESTED_ELEMS     8
#define MAX_CHANNELS_REPORT            16

typedef struct {
    UCHAR               condition;
    UCHAR               threshold;
} wifi_BeaconReporting_t;

typedef struct {
    UCHAR               ids[MAX_REQUESTED_ELEMS];
} wifi_RequestedElementIDS_t;

typedef wifi_RequestedElementIDS_t  wifi_ExtdRequestedElementIDS_t;

// AP Channel Report Element, ID = 51, 802.11-2016 section 9.4.2.36.
typedef struct {
    UCHAR               opClass;
    UCHAR               channels[MAX_CHANNELS_REPORT];
} wifi_ChannelReport_t;

// 802.11-2016 section 9.4.2.21.7
typedef struct {
    UCHAR               opClass;
    UCHAR               channel;
    USHORT              randomizationInterval;
    USHORT              duration;
    UCHAR               mode;
    bssid_t             bssid;
    BOOL                ssidPresent;
    ssid_t              ssid;
    BOOL                beaconReportingPresent;
    wifi_BeaconReporting_t  beaconReporting;
    BOOL                reportingRetailPresent;
    UCHAR               reportingDetail;
    BOOL                wideBandWidthChannelPresent;
    wifi_WideBWChannel_t    wideBandwidthChannel;
    BOOL                requestedElementIDSPresent;
    wifi_RequestedElementIDS_t      requestedElementIDS;
    BOOL                extdRequestedElementIDSPresent;
    wifi_ExtdRequestedElementIDS_t  extdRequestedElementIDS;
    BOOL                channelReportPresent;
    wifi_ChannelReport_t    channelReport;
    BOOL                vendorSpecificPresent;
    wifi_VendorSpecific_t   vendorSpecific;
    USHORT               numRepetitions;
} wifi_BeaconRequest_t;

// 802.11-2016 section 9.4.2.22.7
typedef struct {
    UCHAR               opClass;
    UCHAR               channel;
    ULLONG              startTime;
    USHORT              duration;
    UCHAR               frameInfo;
    UCHAR               rcpi;
    UCHAR               rsni;
    bssid_t             bssid;
    UCHAR               antenna;
    UINT                tsf;
    BOOL                wideBandWidthChannelPresent;
    wifi_WideBWChannel_t    wideBandwidthChannel;
    USHORT              numRepetitions;
} wifi_BeaconReport_t;

/** @} */  //END OF GROUP WIFI_HAL_TYPES

/**
 * @addtogroup WIFI_HAL_APIS
 * @{
 */

/**
* @brief Get the radio channel information
* 
* like average noise floor in dbm,
* average non 802.11 noise, utilization in percent, radio detected that channel 
* was busy, Time that radio detected that extended channel was busy, Time that 
* radio spent receiving on channel (Rx = Rx_obss + Rx_self + Rx_errr(self and 
* obss errors)), Time radio spend receiving on channel from its own connected 
* clients,time radio spent transmitting on channel and Total time radio spent 
* receiving or transmitting on that channel (channel utilization active)
*
* @param[in]  radioIndex                The index of the radio
* @param[out] channelStatsArray         The array initially filled with requested channel numbers.
*                                       The same array is used as an output with channel statistics
*                                       details. Data for each channel must be written to the corresponding
*                                       element of the array. When array_size = 0, the API returns ONCHAN
*                                       stats in a single wifi_channelStats_t element.
* @param[in] sizeOfchannelStatsArray    The length of the output array
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
//Get the basic Radio channel traffic static info
INT wifi_getRadioChannelStats(INT radioIndex, wifi_channelStats_t *channelStatsArray, INT sizeOfchannelStatsArray);

#endif
/** @} */  //END OF GROUP WIFI_HAL_APIS

#ifdef __cplusplus
}
#endif