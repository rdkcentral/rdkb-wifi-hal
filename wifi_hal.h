/*
 * If not stated otherwise in this file or this component's Licenses.txt file the
 * following copyright and licenses apply:
 *
 * Copyright 2015 RDK Management
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

/**********************************************************************
   Copyright [2015] [Comcast, Corp.]
 
   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at
 
       http://www.apache.org/licenses/LICENSE-2.0
 
   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
**********************************************************************/

/**********************************************************************

    module: wifi_hal.h

        For CCSP Component:  Wifi_Provisioning_and_management

    ---------------------------------------------------------------

    copyright:

        Comcast, Corp., 2015
        All Rights Reserved.

    ---------------------------------------------------------------

    description:

        This header file gives the function call prototypes and 
        structure definitions used for the RDK-Broadband 
        Wifi radio hardware abstraction layer

        NOTE:
        THIS VERSION IS AN EARLY DRAFT INTENDED TO GET COMMENTS FROM COMCAST.
        TESTING HAS NOT YET BEEN COMPLETED.  
       
    ---------------------------------------------------------------

    environment:

        This HAL layer is intended to support Wifi drivers 
        through an open API.  

    ---------------------------------------------------------------

    HAL version:

        The version of the Wifi HAL is specified in #defines below.

    --------------------------------------------------------------- 

    author:

        zhicheng_qiu@cable.comcast.com 
        Charles Moreman, moremac@cisco.com
		
    ---------------------------------------------------------------

	Notes:

	What is new for 2.2.0
	  1. Add Country Code support
	  2. Add more DCS function
	  3. Move RadiusSecret from struct wifi_radius_setting_t to wifi_getApSecurityRadiusServer function
	  4. Add wifi_getApSecuritySecondaryRadiusServer
	What is new for 2.2.1
	  1. Add wifi_setRadioTrafficStatsMeasure, wifi_setRadioTrafficStatsRadioStatisticsEnable
	What is new for 2.2.2
	  1. Add Band Steering HAL
**********************************************************************/

#ifndef __WIFI_HAL_H__
#define __WIFI_HAL_H__


#ifndef ULONG
#define ULONG unsigned long
#endif

#ifndef BOOL
#define BOOL  unsigned char
#endif

#ifndef CHAR
#define CHAR  char
#endif

#ifndef UCHAR
#define UCHAR unsigned char
#endif

#ifndef INT
#define INT   int
#endif

#ifndef UINT
#define UINT  unsigned int
#endif

#ifndef TRUE
#define TRUE     1
#endif

#ifndef FALSE
#define FALSE    0
#endif

#ifndef ENABLE
#define ENABLE   1
#endif

#ifndef RETURN_OK
#define RETURN_OK   0
#endif

#ifndef RETURN_ERR
#define RETURN_ERR   -1
#endif


#ifndef RADIO_INDEX_1
#define RADIO_INDEX_1 1
#define RADIO_INDEX_2 2
#define AP_INDEX_1 1
#define AP_INDEX_2 2
#define AP_INDEX_3 3
#define AP_INDEX_4 4
#define AP_INDEX_5 5
#define AP_INDEX_6 6
#define AP_INDEX_7 7
#define AP_INDEX_8 8
#define AP_INDEX_9 9
#define AP_INDEX_10 10
#define AP_INDEX_11 11
#define AP_INDEX_12 12
#define AP_INDEX_13 13
#define AP_INDEX_14 14
#define AP_INDEX_15 15
#define AP_INDEX_16 16
#endif

//defines for HAL version 2.2.1
#define WIFI_HAL_MAJOR_VERSION 2   // This is the major verion of this HAL.
#define WIFI_HAL_MINOR_VERSION 2   // This is the minor verson of the HAL.
#define WIFI_HAL_MAINTENANCE_VERSION 1   // This is the maintenance version of the HAL.

/**********************************************************************
                STRUCTURE DEFINITIONS
**********************************************************************/

//>> Deprecated: used for old RDKB code. 
typedef struct _wifi_basicTrafficStats
{
     ULONG wifi_BytesSent;
     ULONG wifi_BytesReceived;
     ULONG wifi_PacketsSent;
     ULONG wifi_PacketsReceived;
     ULONG wifi_Associations; 	
} wifi_basicTrafficStats_t;

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

typedef struct _wifi_radioTrafficStats
{
	 ULONG wifi_ErrorsSent;	
     ULONG wifi_ErrorsReceived;   
     ULONG wifi_DiscardPacketsSent; 
     ULONG wifi_DiscardPacketsReceived; 
	 ULONG wifi_PLCPErrorCount;	
	 ULONG wifi_FCSErrorCount;	
	 ULONG wifi_InvalidMACCount;	
	 ULONG wifi_PacketsOtherReceived;	
	 INT   wifi_Noise; 	
	 
} wifi_radioTrafficStats_t;	

typedef struct _wifi_ssidTrafficStats
{
     ULONG wifi_RetransCount;	
     ULONG wifi_FailedRetransCount; 	
     ULONG wifi_RetryCount;  
     ULONG wifi_MultipleRetryCount; 	
     ULONG wifi_ACKFailureCount;  	
     ULONG wifi_AggregatedPacketCount; 	
	 
} wifi_ssidTrafficStats_t;  

typedef struct _wifi_neighbor_ap
{
	 CHAR  ap_Radio[64];	
	 CHAR  ap_SSID[64];	
	 CHAR  ap_BSSID[64];	
	 CHAR  ap_Mode[64];	
	 UINT  ap_Channel;
	 INT   ap_SignalStrength;
	 CHAR  ap_SecurityModeEnabled[64];	
	 CHAR  ap_EncryptionMode[64];	
	 CHAR  ap_OperatingFrequencyBand[16];	
	 CHAR  ap_SupportedStandards[64];	
	 CHAR  ap_OperatingStandards[16];	
	 CHAR  ap_OperatingChannelBandwidth[16];	
	 UINT  ap_BeaconPeriod;	
	 INT   ap_Noise;	
	 CHAR  ap_BasicDataTransferRates[256];	
	 CHAR  ap_SupportedDataTransferRates[256];
	 UINT  ap_DTIMPeriod;
	 UINT  ap_ChannelUtilization;	
	 
} wifi_neighbor_ap_t;
//<<

typedef struct _wifi_radioTrafficStats2
{
     ULONG radio_BytesSent;	//The total number of bytes transmitted out of the interface, including framing characters.
     ULONG radio_BytesReceived;	//The total number of bytes received on the interface, including framing characters.
     ULONG radio_PacketsSent;	//The total number of packets transmitted out of the interface.
     ULONG radio_PacketsReceived; //The total number of packets received on the interface.

	 ULONG radio_ErrorsSent;	//The total number of outbound packets that could not be transmitted because of errors.
     ULONG radio_ErrorsReceived;    //The total number of inbound packets that contained errors preventing them from being delivered to a higher-layer protocol.
     ULONG radio_DiscardPacketsSent; //The total number of outbound packets which were chosen to be discarded even though no errors had been detected to prevent their being transmitted. One possible reason for discarding such a packet could be to free up buffer space.
     ULONG radio_DiscardPacketsReceived; //The total number of inbound packets which were chosen to be discarded even though no errors had been detected to prevent their being delivered. One possible reason for discarding such a packet could be to free up buffer space.
	 ULONG radio_PLCPErrorCount;	//The number of packets that were received with a detected Physical Layer Convergence Protocol (PLCP) header error.	
	 ULONG radio_FCSErrorCount;	//The number of packets that were received with a detected FCS error. This parameter is based on dot11FCSErrorCount from [Annex C/802.11-2012].
	 ULONG radio_InvalidMACCount;	//The number of packets that were received with a detected invalid MAC header error.
	 ULONG radio_PacketsOtherReceived;	//The number of packets that were received, but which were destined for a MAC address that is not associated with this interface.
	 INT   radio_NoiseFloor; 	//The noise floor for this radio channel where a recoverable signal can be obtained. Expressed as a signed integer in the range (-110:0).  Measurement should capture all energy (in dBm) from sources other than Wi-Fi devices as well as interference from Wi-Fi devices too weak to be decoded. Measured in dBm
	 ULONG radio_ChannelUtilization; //Percentage of time the channel was occupied by the radio's own activity (Activity Factor) or the activity of other radios.  Channel utilization MUST cover all user traffic, management traffic, and time the radio was unavailable for CSMA activities, including DIFS intervals, etc.  The metric is calculated and updated in this parameter at the end of the interval defined by "Radio Statistics Measuring Interval".  The calculation of this metric MUST only use the data collected from the just completed interval.  If this metric is queried before it has been updated with an initial calculation, it MUST return -1.  Units in Percentage
	 INT   radio_ActivityFactor; //Percentage of time that the radio was transmitting or receiving Wi-Fi packets to/from associated clients. Activity factor MUST include all traffic that deals with communication between the radio and clients associated to the radio as well as management overhead for the radio, including NAV timers, beacons, probe responses,time for receiving devices to send an ACK, SIFC intervals, etc.  The metric is calculated and updated in this parameter at the end of the interval defined by "Radio Statistics Measuring Interval".  The calculation of this metric MUST only use the data collected from the just completed interval.   If this metric is queried before it has been updated with an initial calculation, it MUST return -1. Units in Percentage
	 INT   radio_CarrierSenseThreshold_Exceeded; //Percentage of time that the radio was unable to transmit or receive Wi-Fi packets to/from associated clients due to energy detection (ED) on the channel or clear channel assessment (CCA). The metric is calculated and updated in this Parameter at the end of the interval defined by "Radio Statistics Measuring Interval".  The calculation of this metric MUST only use the data collected from the just completed interval.  If this metric is queried before it has been updated with an initial calculation, it MUST return -1. Units in Percentage
	 INT   radio_RetransmissionMetirc; //Percentage of packets that had to be re-transmitted. Multiple re-transmissions of the same packet count as one.  The metric is calculated and updated in this parameter at the end of the interval defined by "Radio Statistics Measuring Interval".   The calculation of this metric MUST only use the data collected from the just completed interval.  If this metric is queried before it has been updated with an initial calculation, it MUST return -1. Units  in percentage
	 INT   radio_MaximumNoiseFloorOnChannel; //Maximum Noise on the channel during the measuring interval.  The metric is updated in this parameter at the end of the interval defined by "Radio Statistics Measuring Interval".  The calculation of this metric MUST only use the data collected in the just completed interval.  If this metric is queried before it has been updated with an initial calculation, it MUST return -1.  Units in dBm
	 INT   radio_MinimumNoiseFloorOnChannel; //Minimum Noise on the channel. The metric is updated in this Parameter at the end of the interval defined by "Radio Statistics Measuring Interval".  The calculation of this metric MUST only use the data collected in the just completed interval.  If this metric is queried before it has been updated with an initial calculation, it MUST return -1. Units in dBm
	 INT   radio_MedianNoiseFloorOnChannel; //Median Noise on the channel during the measuring interval.   The metric is updated in this parameter at the end of the interval defined by "Radio Statistics Measuring Interval".  The calculation of this metric MUST only use the data collected in the just completed interval.  If this metric is queried before it has been updated with an initial calculation, it MUST return -1. Units in dBm
	 ULONG radio_StatisticsStartTime; 	 //The date and time at which the collection of the current set of statistics started.  This time must be updated whenever the radio statistics are reset.
	
} wifi_radioTrafficStats2_t;	//for radio only

typedef struct _wifi_radioTrafficStatsMeasure
{
	 INT   radio_RadioStatisticsMeasuringRate; //Input //"The rate at which radio related statistics are periodically collected.  Only statistics that explicitly indicate the use of this parameter MUST use the rate set in this parameter  Other parameter's are assumed to collect data in real-time or nearly real-time. Default value is 30 seconds.  This parameter MUST be persistent across reboots. If this parameter is changed,  then use of the new rate MUST be deferred until the start of the next interval and all metrics using this rate MUST return -1 until the completion of the next full interval Units in Seconds"
	 INT   radio_RadioStatisticsMeasuringInterval; //Input //The interval for which radio data MUST be retained in order and at the end of which appropriate calculations are executed and reflected in the associated radio object's.  Only statistics that explicitly indicate the use of this parameter MUST use the interval set in this parameter  Default value is 30 minutes.  This parameter MUST be persistent across reboots.   If this item is modified, then all metrics leveraging this interval as well as the metrics “Total number 802.11 packet of TX” and “Total number 802.11 packet of RX“ MUST be re-initialized immediately.  Additionally, the “Statistics Start Time” must be reset to the current time. Units in Seconds
} wifi_radioTrafficStatsMeasure_t;	//for radio only


typedef struct _wifi_ssidTrafficStats2
{
     ULONG ssid_BytesSent;	//The total number of bytes transmitted out of the interface, including framing characters.
     ULONG ssid_BytesReceived;	//The total number of bytes received on the interface, including framing characters.
     ULONG ssid_PacketsSent;	//The total number of packets transmitted out of the interface.
     ULONG ssid_PacketsReceived; //The total number of packets received on the interface.

     ULONG ssid_RetransCount;	//The total number of transmitted packets which were retransmissions. Two retransmissions of the same packet results in this counter incrementing by two.
     ULONG ssid_FailedRetransCount; //The number of packets that were not transmitted successfully due to the number of retransmission attempts exceeding an 802.11 retry limit. This parameter is based on dot11FailedCount from [802.11-2012].	
     ULONG ssid_RetryCount;  //The number of packets that were successfully transmitted after one or more retransmissions. This parameter is based on dot11RetryCount from [802.11-2012].	
     ULONG ssid_MultipleRetryCount; //The number of packets that were successfully transmitted after more than one retransmission. This parameter is based on dot11MultipleRetryCount from [802.11-2012].	
     ULONG ssid_ACKFailureCount;  //The number of expected ACKs that were never received. This parameter is based on dot11ACKFailureCount from [802.11-2012].	
     ULONG ssid_AggregatedPacketCount; //The number of aggregated packets that were transmitted. This applies only to 802.11n and 802.11ac.	
	 
	 ULONG ssid_ErrorsSent;	//The total number of outbound packets that could not be transmitted because of errors.
     ULONG ssid_ErrorsReceived;    //The total number of inbound packets that contained errors preventing them from being delivered to a higher-layer protocol.
     ULONG ssid_UnicastPacketsSent;	//The total number of inbound packets that contained errors preventing them from being delivered to a higher-layer protocol.
     ULONG ssid_UnicastPacketsReceived;  //The total number of received packets, delivered by this layer to a higher layer, which were not addressed to a multicast or broadcast address at this layer.
     ULONG ssid_DiscardedPacketsSent; //The total number of outbound packets which were chosen to be discarded even though no errors had been detected to prevent their being transmitted. One possible reason for discarding such a packet could be to free up buffer space.
     ULONG ssid_DiscardedPacketsReceived; //The total number of inbound packets which were chosen to be discarded even though no errors had been detected to prevent their being delivered. One possible reason for discarding such a packet could be to free up buffer space.
     ULONG ssid_MulticastPacketsSent; //The total number of packets that higher-level protocols requested for transmission and which were addressed to a multicast address at this layer, including those that were discarded or not sent.
     ULONG ssid_MulticastPacketsReceived; //The total number of received packets, delivered by this layer to a higher layer, which were addressed to a multicast address at this layer.  
     ULONG ssid_BroadcastPacketsSent;  //The total number of packets that higher-level protocols requested for transmission and which were addressed to a broadcast address at this layer, including those that were discarded or not sent.
     ULONG ssid_BroadcastPacketsRecevied; //The total number of packets that higher-level protocols requested for transmission and which were addressed to a broadcast address at this layer, including those that were discarded or not sent.
     ULONG ssid_UnknownPacketsReceived;  //The total number of packets received via the interface which were discarded because of an unknown or unsupported protocol.

} wifi_ssidTrafficStats2_t;  //for ssid only


//Please do not edit the elements for this data structure 
typedef struct _wifi_neighbor_ap2
{
	 //CHAR  ap_Radio[64];	//The value MUST be the path name of a row in the Device.WiFi.Radio table. The Radio that detected the neighboring WiFi SSID.  
	 CHAR  ap_SSID[64];	//The current service set identifier in use by the neighboring WiFi SSID. The value MAY be empty for hidden SSIDs.
	 CHAR  ap_BSSID[64];	//[MACAddress] The BSSID used for the neighboring WiFi SSID.
	 CHAR  ap_Mode[64];	//The mode the neighboring WiFi radio is operating in. Enumeration of: AdHoc, Infrastructure
	 UINT  ap_Channel;	//The current radio channel used by the neighboring WiFi radio.
	 INT   ap_SignalStrength;	//An indicator of radio signal strength (RSSI) of the neighboring WiFi radio measured in dBm, as an average of the last 100 packets received.
	 CHAR  ap_SecurityModeEnabled[64];	//The type of encryption the neighboring WiFi SSID advertises. Enumeration of:None, WPA-WPA2 etc.
	 CHAR  ap_EncryptionMode[64];	//Comma-separated list of strings. The type of encryption the neighboring WiFi SSID advertises. Each list item is an enumeration of: TKIP, AES
	 CHAR  ap_OperatingFrequencyBand[16];	//Indicates the frequency band at which the radio this SSID instance is operating. Enumeration of:2.4GHz, 5GHz
	 CHAR  ap_SupportedStandards[64];	//Comma-separated list of strings. List items indicate which IEEE 802.11 standards this Result instance can support simultaneously, in the frequency band specified by OperatingFrequencyBand. Each list item is an enumeration of:
	 CHAR  ap_OperatingStandards[16];	//Comma-separated list of strings. Each list item MUST be a member of the list reported by theSupportedStandards parameter. List items indicate which IEEE 802.11 standard that is detected for thisResult.
	 CHAR  ap_OperatingChannelBandwidth[16];	//Indicates the bandwidth at which the channel is operating. Enumeration of:
	 UINT  ap_BeaconPeriod;	//Time interval (in ms) between transmitting beacons.
	 INT   ap_Noise;	//Indicator of average noise strength (in dBm) received from the neighboring WiFi radio.
	 CHAR  ap_BasicDataTransferRates[256];	//Comma-separated list (maximum list length 256) of strings. Basic data transmit rates (in Mbps) for the SSID. For example, if BasicDataTransferRates is "1,2", this indicates that the SSID is operating with basic rates of 1 Mbps and 2 Mbps.
	 CHAR  ap_SupportedDataTransferRates[256];	//Comma-separated list (maximum list length 256) of strings. Data transmit rates (in Mbps) for unicast frames at which the SSID will permit a station to connect. For example, if SupportedDataTransferRates is "1,2,5.5", this indicates that the SSID will only permit connections at 1 Mbps, 2 Mbps and 5.5 Mbps.
	 UINT  ap_DTIMPeriod;	//The number of beacon intervals that elapse between transmission of Beacon frames containing a TIM element whose DTIM count field is 0. This value is transmitted in the DTIM Period field of beacon frames. [802.11-2012]
	 UINT  ap_ChannelUtilization;	//Indicates the fraction of the time AP senses that the channel is in use by the neighboring AP for transmissions.
	 
} wifi_neighbor_ap2_t;	//COSA_DML_NEIGHTBOURING_WIFI_RESULT

typedef struct _wifi_diag_ipping_setting
{
	 CHAR  ipping_Interface[256];	//The value MUST be the path name of a row in the IP.Interface table. The IP-layer interface over which the test is to be performed. This identifies the source IP address to use when performing the test. Example: Device.IP.Interface.1. If an empty string is specified, the CPE MUST use the interface as directed by its routing policy (Forwarding table entries) to determine the appropriate interface.
	 CHAR  ipping_Host[256];	//Host name or address of the host to ping. In the case where Host is specified by name, and the name resolves to more than one address, it is up to the device implementation to choose which address to use.
	 UINT  ipping_NumberOfRepetitions;	//Number of repetitions of the ping test to perform before reporting the results.	
	 UINT  ipping_Timeout;	//Timeout in milliseconds for the ping test.	
	 UINT  ipping_DataBlockSize;	//Size of the data block in bytes to be sent for each ping.
	 UINT  ipping_DSCP;	//DiffServ codepoint to be used for the test packets. By default the CPE SHOULD set this value to zero.

} wifi_diag_ipping_setting_t;	

typedef struct _wifi_diag_ipping_result
{
	 CHAR  ipping_DiagnosticsState[64];	//Indicates availability of diagnostic data. Enumeration of:	Complete, Error_CannotResolveHostName, 	Error_Internal, Error_Other
	 UINT  ipping_SuccessCount;	//Result parameter indicating the number of successful pings (those in which a successful response was received prior to the timeout) in the most recent ping test.	
	 UINT  ipping_FailureCount;	//Result parameter indicating the number of failed pings in the most recent ping test.
	 UINT  ipping_AverageResponseTime;	//Result parameter indicating the average response time in milliseconds over all repetitions with successful responses of the most recent ping test. If there were no successful responses, this value MUST be zero.
	 UINT  ipping_MinimumResponseTime;	//Result parameter indicating the minimum response time in milliseconds over all repetitions with successful responses of the most recent ping test. If there were no successful responses, this value MUST be zero.
	 UINT  ipping_MaximumResponseTime;	//Result parameter indicating the maximum response time in milliseconds over all repetitions with successful responses of the most recent ping test. If there were no successful responses, this value MUST be zero.
	 
} wifi_diag_ipping_result_t;

//>> -------------------------------- wifi_ap_hal --------------------------------------------
//>> Deprecated: used for old RDKB code. 
typedef struct _wifi_device
{
     UCHAR wifi_devMacAddress[6];
     CHAR wifi_devIPAddress[64];
     BOOL wifi_devAssociatedDeviceAuthentiationState;
     INT  wifi_devSignalStrength;
     INT  wifi_devTxRate;
     INT  wifi_devRxRate;
} wifi_device_t;
//<<

//Please do not edit the elements for this data structure 
typedef struct _wifi_associated_dev
{
     //UCHAR cli_devMacAddress[6];
     //CHAR  cli_devIPAddress[64];
     //BOOL  cli_devAssociatedDeviceAuthentiationState;
     //INT   cli_devSignalStrength;
     //INT   cli_devTxRate;
     //INT   cli_devRxRate;
	 
	 UCHAR cli_MACAddress[6];		// The MAC address of an associated device.
	 CHAR  cli_IPAddress[64];		// IP of the associated device
	 BOOL  cli_AuthenticationState; // Whether an associated device has authenticated (true) or not (false).
	 UINT  cli_LastDataDownlinkRate; //The data transmit rate in kbps that was most recently used for transmission from the access point to the associated device.
	 UINT  cli_LastDataUplinkRate; 	// The data transmit rate in kbps that was most recently used for transmission from the associated device to the access point.
	 INT   cli_SignalStrength; 		//An indicator of radio signal strength of the uplink from the associated device to the access point, measured in dBm, as an average of the last 100 packets received from the device.
	 UINT  cli_Retransmissions; 	//The number of packets that had to be re-transmitted, from the last 100 packets sent to the associated device. Multiple re-transmissions of the same packet count as one.
	 BOOL  cli_Active; 				//	boolean	-	Whether or not this node is currently present in the WiFi AccessPoint network.
	
	 CHAR  cli_OperatingStandard[64];	//Radio standard the associated Wi-Fi client device is operating under. Enumeration of:
	 CHAR  cli_OperatingChannelBandwidth[64];	//The operating channel bandwidth of the associated device. The channel bandwidth (applicable to 802.11n and 802.11ac specifications only). Enumeration of:
	 INT   cli_SNR;		//A signal-to-noise ratio (SNR) compares the level of the Wi-Fi signal to the level of background noise. Sources of noise can include microwave ovens, cordless phone, bluetooth devices, wireless video cameras, wireless game controllers, fluorescent lights and more. It is measured in decibels (dB).
	 CHAR  cli_InterferenceSources[64]; //Wi-Fi operates in two frequency ranges (2.4 Ghz and 5 Ghz) which may become crowded other radio products which operate in the same ranges. This parameter reports the probable interference sources that this Wi-Fi access point may be observing. The value of this parameter is a comma seperated list of the following possible sources: eg: MicrowaveOven,CordlessPhone,BluetoothDevices,FluorescentLights,ContinuousWaves,Others
	 ULONG cli_DataFramesSentAck;	//The DataFramesSentAck parameter indicates the total number of MSDU frames marked as duplicates and non duplicates acknowledged. The value of this counter may be reset to zero when the CPE is rebooted. Refer section A.2.3.14 of CableLabs Wi-Fi MGMT Specification.
	 ULONG cli_DataFramesSentNoAck;	//The DataFramesSentNoAck parameter indicates the total number of MSDU frames retransmitted out of the interface (i.e., marked as duplicate and non-duplicate) and not acknowledged, but does not exclude those defined in the DataFramesLost parameter. The value of this counter may be reset to zero when the CPE is rebooted. Refer section A.2.3.14 of CableLabs Wi-Fi MGMT Specification.
	 ULONG cli_BytesSent;	//The total number of bytes transmitted to the client device, including framing characters.
	 ULONG cli_BytesReceived;	//The total number of bytes received from the client device, including framing characters.
	 INT   cli_RSSI;	//The Received Signal Strength Indicator, RSSI, parameter is the energy observed at the antenna receiver for transmissions from the device averaged over past 100 packets recevied from the device.
	 INT   cli_MinRSSI;	//The Minimum Received Signal Strength Indicator, RSSI, parameter is the minimum energy observed at the antenna receiver for past transmissions (100 packets).
	 INT   cli_MaxRSSI;	//The Maximum Received Signal Strength Indicator, RSSI, parameter is the energy observed at the antenna receiver for past transmissions (100 packets).
	 UINT  cli_Disassociations;	//This parameter  represents the total number of client disassociations. Reset the parameter evey 24hrs or reboot
	 UINT  cli_AuthenticationFailures;	//This parameter indicates the total number of authentication failures.  Reset the parameter evey 24hrs or reboot
	 
} wifi_associated_dev_t;	//~COSA_DML_WIFI_AP_ASSOC_DEVICE

typedef struct _wifi_radius_setting_t
{
	 INT  RadiusServerRetries; 			//Number of retries for Radius requests.
	 INT  RadiusServerRequestTimeout; 	//Radius request timeout in seconds after which the request must be retransmitted for the # of retries available.	
	 INT  PMKLifetime; 					//Default time in seconds after which a Wi-Fi client is forced to ReAuthenticate (def 8 hrs).	
	 BOOL PMKCaching; 					//Enable or disable caching of PMK.	
	 INT  PMKCacheInterval; 			//Time interval in seconds after which the PMKSA (Pairwise Master Key Security Association) cache is purged (def 5 minutes).	
	 INT  MaxAuthenticationAttempts; 	//Indicates the # of time, a client can attempt to login with incorrect credentials. When this limit is reached, the client is blacklisted and not allowed to attempt loging into the network. Settings this parameter to 0 (zero) disables the blacklisting feature.
	 INT  BlacklistTableTimeout; 		//Time interval in seconds for which a client will continue to be blacklisted once it is marked so.	
	 INT  IdentityRequestRetryInterval; //Time Interval in seconds between identity requests retries. A value of 0 (zero) disables it.	
	 INT  QuietPeriodAfterFailedAuthentication;  //The enforced quiet period (time interval) in seconds following failed authentication. A value of 0 (zero) disables it.	
	 //UCHAR RadiusSecret[64];			//The secret used for handshaking with the RADIUS server [RFC2865]. When read, this parameter returns an empty string, regardless of the actual value.
		 
} wifi_radius_setting_t;	

//typedef struct wifi_AC_parameters_record  // Access Catagoriy parameters.  see 802.11-2012 spec for descriptions
//{
//     INT CWmin;       // CWmin variable
//     INT CWmax;       // CWmax vairable
//     INT AIFS;        // AIFS
//     ULONG TxOpLimit;  // TXOP Limit
//} wifi_AC_parameters_record_t;


//typedef struct _wifi_qos
//{
//     wifi_AC_parameters_record_t BE_AcParametersRecord;      // Best Effort QOS parameters, ACI == 0
//     wifi_AC_parameters_record_t BK_AcParametersRecord;      // Background QOS parameters, ACI == 1
//     wifi_AC_parameters_record_t VI_AcParametersRecord;      // Video QOS parameters, ACI == 2
//     wifi_AC_parameters_record_t VO_AcParametersRecord;      // Voice QOS parameters, ACI == 3
//}  wifi_qos_t;

//<< -------------------------------- wifi_ap_hal --------------------------------------------

//---------------------------------------------------------------------------------------------------
//Wifi system api
//Get the wifi hal version in string, eg "2.0.0".  WIFI_HAL_MAJOR_VERSION.WIFI_HAL_MINOR_VERSION.WIFI_HAL_MAINTENANCE_VERSION
INT wifi_getHalVersion(CHAR *output_string);   //RDKB   

//---------------------------------------------------------------------------------------------------
//
// Wifi subsystem level APIs that are common to Client and Access Point devices.
//
//---------------------------------------------------------------------------------------------------

//clears internal variables to implement a factory reset of the Wi-Fi subsystem
INT wifi_factoryReset();	//RDKB

//Restore all radio parameters without touch access point parameters
INT wifi_factoryResetRadios(); //RDKB

//Restore selected radio parameters without touch access point parameters
INT wifi_factoryResetRadio(int radioIndex); 	//RDKB

//Set the system LED status
INT wifi_setLED(INT radioIndex, BOOL enable);	//RDKB

// Initializes the wifi subsystem (all radios)
INT wifi_init();                              //RDKB

// resets the wifi subsystem, deletes all APs
INT wifi_reset();                            //RDKB

// turns off transmit power for the entire Wifi subsystem, for all radios
INT wifi_down();                       		//RDKB

// creates initial implementation dependent configuration files that are later used for variable storage.  Not all implementations may need this function.  If not needed for a particular implementation simply return no-error (0)
INT wifi_createInitialConfigFiles();                                                                                    

// outputs the country code to a max 64 character string
INT wifi_getRadioCountryCode(INT radioIndex, CHAR *output_string);   
INT wifi_setRadioCountryCode(INT radioIndex, CHAR *CountryCode);       


//---------------------------------------------------------------------------------------------------
//Wifi Tr181 API

//Device.WiFi.

//Device.WiFi.RadioNumberOfEntries
//Get the total number of radios in this wifi subsystem
INT wifi_getRadioNumberOfEntries(ULONG *output); //Tr181

//Device.WiFi.SSIDNumberOfEntries
//Get the total number of SSID entries in this wifi subsystem 
INT wifi_getSSIDNumberOfEntries(ULONG *output); //Tr181

//Device.WiFi.AccessPointNumberOfEntries

//Device.WiFi.EndPointNumberOfEntries
//End points are managed by RDKB
//INT wifi_getEndPointNumberOfEntries(INT radioIndex, ULONG *output); //Tr181

//---------------------------------------------------------------------------------------------------
//
// Wifi radio level APIs that are common to Client and Access Point devices
//
//---------------------------------------------------------------------------------------------------

//Device.WiFi.Radio.
//Device.WiFi.Radio.{i}.Enable
//Get the Radio enable config parameter
INT wifi_getRadioEnable(INT radioIndex, BOOL *output_bool);	//RDKB

//Set the Radio enable config parameter
INT wifi_setRadioEnable(INT radioIndex, BOOL enable);		//RDKB

//Device.WiFi.Radio.{i}.Status
//Get the Radio enable status
INT wifi_getRadioStatus(INT radioIndex, BOOL *output_bool);	//RDKB

//Device.WiFi.Radio.{i}.Alias

//Device.WiFi.Radio.{i}.Name
//Get the Radio Interface name from platform, eg "wifi0"
INT wifi_getRadioIfName(INT radioIndex, CHAR *output_string); //Tr181

//Device.WiFi.Radio.{i}.LastChange

//Device.WiFi.Radio.{i}.LowerLayers

//Device.WiFi.Radio.{i}.Upstream

//Device.WiFi.Radio.{i}.MaxBitRate
//Get the maximum PHY bit rate supported by this interface. eg: "216.7 Mb/s", "1.3 Gb/s"
//The output_string is a max length 64 octet string that is allocated by the RDKB code.  Implementations must ensure that strings are not longer than this.
INT wifi_getRadioMaxBitRate(INT radioIndex, CHAR *output_string);	//RDKB

//Device.WiFi.Radio.{i}.SupportedFrequencyBands
//Get Supported frequency bands at which the radio can operate. eg: "2.4GHz,5GHz"
//The output_string is a max length 64 octet string that is allocated by the RDKB code.  Implementations must ensure that strings are not longer than this.
INT wifi_getRadioSupportedFrequencyBands(INT radioIndex, CHAR *output_string);	//RDKB

//Device.WiFi.Radio.{i}.OperatingFrequencyBand
//Get the frequency band at which the radio is operating, eg: "2.4GHz"
//The output_string is a max length 64 octet string that is allocated by the RDKB code.  Implementations must ensure that strings are not longer than this.
INT wifi_getRadioOperatingFrequencyBand(INT radioIndex, CHAR *output_string); //Tr181

//Device.WiFi.Radio.{i}.SupportedStandards
//Get the Supported Radio Mode. eg: "b,g,n"; "n,ac"
//The output_string is a max length 64 octet string that is allocated by the RDKB code.  Implementations must ensure that strings are not longer than this.
INT wifi_getRadioSupportedStandards(INT radioIndex, CHAR *output_string); //Tr181

//Device.WiFi.Radio.{i}.OperatingStandards
//Get the radio operating mode, and pure mode flag. eg: "ac"
//The output_string is a max length 64 octet string that is allocated by the RDKB code.  Implementations must ensure that strings are not longer than this.
INT wifi_getRadioStandard(INT radioIndex, CHAR *output_string, BOOL *gOnly, BOOL *nOnly, BOOL *acOnly);	//RDKB
//Set the radio operating mode, and pure mode flag. 
INT wifi_setRadioChannelMode(INT radioIndex, CHAR *channelMode, BOOL gOnlyFlag, BOOL nOnlyFlag, BOOL acOnlyFlag);	//RDKB

//Device.WiFi.Radio.{i}.PossibleChannels
//Get the list of supported channel. eg: "1-11"
//The output_string is a max length 64 octet string that is allocated by the RDKB code.  Implementations must ensure that strings are not longer than this.
INT wifi_getRadioPossibleChannels(INT radioIndex, CHAR *output_string);	//RDKB

//Device.WiFi.Radio.{i}.ChannelsInUse
//Get the list for used channel. eg: "1,6,9,11"
//The output_string is a max length 256 octet string that is allocated by the RDKB code.  Implementations must ensure that strings are not longer than this.
INT wifi_getRadioChannelsInUse(INT radioIndex, CHAR *output_string);	//RDKB

//Device.WiFi.Radio.{i}.Channel
//Get the running channel number 
INT wifi_getRadioChannel(INT radioIndex,ULONG *output_ulong);	//RDKB
//Set the running channel number 
INT wifi_setRadioChannel(INT radioIndex, ULONG channel);	//RDKB	//AP only

//Enables or disables a driver level variable to indicate if auto channel selection is enabled on this radio
//This "auto channel" means the auto channel selection when radio is up. (which is different from the dynamic channel/frequency selection (DFC/DCS))
INT wifi_setRadioAutoChannelEnable(INT radioIndex, BOOL enable); //RDKB

//Device.WiFi.Radio.{i}.AutoChannelSupported
//Check if the driver support the AutoChannel
INT wifi_getRadioAutoChannelSupported(INT radioIndex, BOOL *output_bool); //Tr181
//Get the AutoChannel enable status
INT wifi_getRadioAutoChannelEnable(INT radioIndex, BOOL *output_bool);	//Tr181
//Set the AutoChannel enable status
INT wifi_setRadioAutoChannelEnable(INT radioIndex, BOOL enable);	//Tr181

//Device.WiFi.Radio.{i}.X_COMCAST-COM_DCSSupported
//Check if the driver support the DCS
INT wifi_getRadioDCSSupported(INT radioIndex, BOOL *output_bool); 	//RDKB
//Device.WiFi.Radio.{i}.X_COMCAST-COM_DCSEnable
INT wifi_getRadioDCSEnable(INT radioIndex, BOOL *output_bool);		//RDKB
INT wifi_setRadioDCSEnable(INT radioIndex, BOOL enable);			//RDKB

//The output_string is a max length 256 octet string that is allocated by the RDKB code.  Implementations must ensure that strings are not longer than this.
//The value of this parameter is a comma seperated list of channel number
INT wifi_getRadioDCSChannelPool(INT radioIndex, CHAR *output_pool);			//RDKB
INT wifi_setRadioDCSChannelPool(INT radioIndex, CHAR *pool);			//RDKB

INT wifi_getRadioDCSScanTime(INT radioIndex, INT *output_interval_seconds, INT *output_dwell_milliseconds);
INT wifi_setRadioDCSScanTime(INT radioIndex, INT interval_seconds, INT dwell_milliseconds);

//Device.WiFi.Radio.{i}.X_COMCAST-COM_DfsSupported
//Get radio DFS support
INT wifi_getRadioDfsSupport(INT radioIndex, BOOL *output_bool);		//RDKB
//Device.WiFi.Radio.{i}.X_COMCAST-COM_DfsEnable					
INT wifi_getRadioDfsEnable(INT radioIndex, BOOL *output_bool);		//RDKB				
INT wifi_setRadioDfsEnable(INT radioIndex, BOOL enabled);			//RDKB				

//Device.WiFi.Radio.{i}.AutoChannelRefreshPeriod
//Check if the driver support the AutoChannelRefreshPeriod
INT wifi_getRadioAutoChannelRefreshPeriodSupported(INT radioIndex, BOOL *output_bool); //Tr181
//Get the DCS refresh period in seconds
INT wifi_getRadioAutoChannelRefreshPeriod(INT radioIndex, ULONG *output_ulong); //Tr181
//Set the DCS refresh period in seconds
INT wifi_setRadioAutoChannelRefreshPeriod(INT radioIndex, ULONG seconds); //Tr181

//Device.WiFi.Radio.{i}.OperatingChannelBandwidth
//Get the Operating Channel Bandwidth. eg "20MHz", "40MHz", "80MHz", "80+80", "160"
//The output_string is a max length 64 octet string that is allocated by the RDKB code.  Implementations must ensure that strings are not longer than this.
INT wifi_getRadioOperatingChannelBandwidth(INT radioIndex, CHAR *output_string); //Tr181
//Set the Operating Channel Bandwidth.
INT wifi_setRadioOperatingChannelBandwidth(INT radioIndex, CHAR *bandwidth); //Tr181	//AP only

//Device.WiFi.Radio.{i}.ExtensionChannel
//Get the secondary extension channel position, "AboveControlChannel" or "BelowControlChannel". (this is for 40MHz and 80MHz bandwith only)
//The output_string is a max length 64 octet string that is allocated by the RDKB code.  Implementations must ensure that strings are not longer than this.
INT wifi_getRadioExtChannel(INT radioIndex, CHAR *output_string); //Tr181
//Set the extension channel.
INT wifi_setRadioExtChannel(INT radioIndex, CHAR *string); //Tr181	//AP only

//Device.WiFi.Radio.{i}.GuardInterval
//Get the guard interval value. eg "400nsec" or "800nsec" 
//The output_string is a max length 64 octet string that is allocated by the RDKB code.  Implementations must ensure that strings are not longer than this.
INT wifi_getRadioGuardInterval(INT radioIndex, CHAR *output_string);	//Tr181
//Set the guard interval value.
INT wifi_setRadioGuardInterval(INT radioIndex, CHAR *string);	//Tr181

//Device.WiFi.Radio.{i}.MCS
//Get the Modulation Coding Scheme index, eg: "-1", "1", "15"
INT wifi_getRadioMCS(INT radioIndex, INT *output_INT); //Tr181
//Set the Modulation Coding Scheme index
INT wifi_setRadioMCS(INT radioIndex, INT MCS); //Tr181

//Device.WiFi.Radio.{i}.TransmitPowerSupported
//Get supported Transmit Power list, eg : "0,25,50,75,100"
//The output_list is a max length 64 octet string that is allocated by the RDKB code.  Implementations must ensure that strings are not longer than this.
INT wifi_getRadioTransmitPowerSupported(INT radioIndex, CHAR *output_list); //Tr181

//Device.WiFi.Radio.{i}.TransmitPower
//Get current Transmit Power, eg "75", "100"
//The transmite power level is in units of full power for this radio.
INT wifi_getRadioTransmitPower(INT radioIndex, ULONG *output_ulong);	//RDKB
//Set Transmit Power
//The transmite power level is in units of full power for this radio.
INT wifi_setRadioTransmitPower(INT radioIndex, ULONG TransmitPower);	//RDKB

//Device.WiFi.Radio.{i}.IEEE80211hSupported
//get 80211h Supported.  80211h solves interference with satellites and radar using the same 5 GHz frequency band
INT wifi_getRadioIEEE80211hSupported(INT radioIndex, BOOL *Supported);  //Tr181
//Device.WiFi.Radio.{i}.IEEE80211hEnabled
//Get 80211h feature enable
INT wifi_getRadioIEEE80211hEnabled(INT radioIndex, BOOL *enable);  //Tr181
//Set 80211h feature enable
INT wifi_setRadioIEEE80211hEnabled(INT radioIndex, BOOL enable);  //Tr181

//Device.WiFi.Radio.{i}.RegulatoryDomain

//Device.WiFi.Radio.{i}.X_COMCAST-COM_CarrierSenseThresholdRange		
//Indicates the Carrier Sense ranges supported by the radio. It is measured in dBm. Refer section A.2.3.2 of CableLabs Wi-Fi MGMT Specification.
INT wifi_getRadioCarrierSenseThresholdRange(INT radioIndex, INT *output);  //P3

//Device.WiFi.Radio.{i}.X_COMCAST-COM_CarrierSenseThresholdInUse
//The RSSI signal level at which CS/CCA detects a busy condition. This attribute enables APs to increase minimum sensitivity to avoid detecting busy condition from multiple/weak Wi-Fi sources in dense Wi-Fi environments. It is measured in dBm. Refer section A.2.3.2 of CableLabs Wi-Fi MGMT Specification.
INT wifi_getRadioCarrierSenseThresholdInUse(INT radioIndex, INT *output);	//P3
INT wifi_setRadioCarrierSenseThresholdInUse(INT radioIndex, INT threshold);	//P3

//Device.WiFi.Radio.{i}.X_COMCAST-COM_ChannelSwitchingCount
//This parameter indicates the total number of Channel Changes.  Reset the parameter every 24 hrs or reboot
//INT wifi_getRadioChannelSwitchingCount(INT radioIndex, INT *output); 	//P3

//Device.WiFi.Radio.{i}.BeaconPeriod	
//Time interval between transmitting beacons (expressed in milliseconds). This parameter is based ondot11BeaconPeriod from [802.11-2012].
INT wifi_getRadioBeaconPeriod(INT radioIndex, UINT *output); 
INT wifi_setRadioBeaconPeriod(INT radioIndex, UINT BeaconPeriod); 

//Device.WiFi.Radio.{i}.BasicDataTransmitRates
//Comma-separated list of strings. The set of data rates, in Mbps, that have to be supported by all stations that desire to join this BSS. The stations have to be able to receive and transmit at each of the data rates listed inBasicDataTransmitRates. For example, a value of "1,2", indicates that stations support 1 Mbps and 2 Mbps. Most control packets use a data rate in BasicDataTransmitRates.	
INT wifi_getRadioBasicDataTransmitRates(INT radioIndex, CHAR *output);
INT wifi_setRadioBasicDataTransmitRates(INT radioIndex, CHAR *TransmitRates);

//---------------------------------------------------------------------------------------------------
//Device.WiFi.Radio.{i}.Stats.

//Device.WiFi.Radio.{i}.Stats.BytesSent
//Device.WiFi.Radio.{i}.Stats.BytesReceived
//Device.WiFi.Radio.{i}.Stats.PacketsSent
//Device.WiFi.Radio.{i}.Stats.PacketsReceived
//Device.WiFi.Radio.{i}.Stats.ErrorsSent
//Device.WiFi.Radio.{i}.Stats.ErrorsReceived
//Device.WiFi.Radio.{i}.Stats.DiscardPacketsSent
//Device.WiFi.Radio.{i}.Stats.DiscardPacketsReceived
//Device.WiFi.Radio.{i}.Stats.PLCPErrorCount
//Device.WiFi.Radio.{i}.Stats.FCSErrorCount
//Device.WiFi.Radio.{i}.Stats.InvalidMACCount
//Device.WiFi.Radio.{i}.Stats.PacketsOtherReceived
//Device.WiFi.Radio.{i}.Stats.X_COMCAST-COM_NoiseFloor
//Device.WiFi.Radio.{i}.Stats.X_COMCAST-COM_ChannelUtilization
//Device.WiFi.Radio.{i}.Stats.X_COMCAST-COM_ActivityFactor
//Device.WiFi.Radio.{i}.Stats.X_COMCAST-COM_CarrierSenseThreshold_Exceeded
//Device.WiFi.Radio.{i}.Stats.X_COMCAST-COM_RetransmissionMetirc
//Device.WiFi.Radio.{i}.Stats.X_COMCAST-COM_MaximumNoiseFloorOnChannel
//Device.WiFi.Radio.{i}.Stats.X_COMCAST-COM_MinimumNoiseFloorOnChannel
//Device.WiFi.Radio.{i}.Stats.X_COMCAST-COM_MedianNoiseFloorOnChannel
//Device.WiFi.Radio.{i}.Stats.X_COMCAST-COM_StatisticsStartTime
//Get detail radio traffic static info
INT wifi_getRadioTrafficStats2(INT radioIndex, wifi_radioTrafficStats2_t *output_struct); //Tr181

//Device.WiFi.Radio.{i}.Stats.X_COMCAST-COM_RadioStatisticsMeasuringRate
//Device.WiFi.Radio.{i}.Stats.X_COMCAST-COM_RadioStatisticsMeasuringInterval
//Set radio traffic static Measureing rules
INT wifi_setRadioTrafficStatsMeasure(INT radioIndex, wifi_radioTrafficStatsMeasure_t *input_struct); //Tr181

//Device.WiFi.Radio.{i}.Stats.X_COMCAST-COM_RadioStatisticsEnable bool writable
INT wifi_setRadioTrafficStatsRadioStatisticsEnable(INT radioIndex, BOOL enable);

//-----------------------------------------------------------------------------------------------
//Device.WiFi.Radio.{i}.Stats.X_COMCAST-COM_ReceivedSignalLevel.{i}.

//Device.WiFi.Radio.{i}.Stats.X_COMCAST-COM_ReceivedSignalLevel.{i}.ReceivedSignalLevel
//Clients associated with the AP over a specific interval.  The histogram MUST have a range from -110to 0 dBm and MUST be divided in bins of 3 dBM, with bins aligning on the -110 dBm end of the range.  Received signal levels equal to or greater than the smaller boundary of a bin and less than the larger boundary are included in the respective bin.  The bin associated with the client?s current received signal level MUST be incremented when a client associates with the AP.   Additionally, the respective bins associated with each connected client?s current received signal level MUST be incremented at the interval defined by "Radio Statistics Measuring Rate".  The histogram?s bins MUST NOT be incremented at any other time.  The histogram data collected during the interval MUST be published to the parameter only at the end of the interval defined by "Radio Statistics Measuring Interval".  The underlying histogram data MUST be cleared at the start of each interval defined by "Radio Statistics Measuring Interval?. If any of the parameter's representing this histogram is queried before the histogram has been updated with an initial set of data, it MUST return -1. Units dBm
INT wifi_getRadioStatsReceivedSignalLevel(INT radioIndex, INT signalIndex, INT *SignalLevel); //Tr181

//-----------------------------------------------------------------------------------------------------
//This API is used to apply (push) all previously set radio level variables and make these settings active in the hardware
//Not all implementations may need this function.  If not needed for a particular implementation simply return no-error (0)
INT wifi_applyRadioSettings(INT radioIndex);  


//Radio reset count
INT wifi_getRadioResetCount(INT radioIndex, ULONG *output_int);

//---------------------------------------------------------------------------------------------------
//
// Wifi SSID level APIs common to Client and Access Point devices.
//
//---------------------------------------------------------------------------------------------------

//Device.WiFi.SSID.{i}.

//Get the radio index assocated with this SSID entry
INT wifi_getSSIDRadioIndex(INT ssidIndex, INT *radioIndex);

//Device.WiFi.SSID.{i}.Enable
//Get SSID enable configuration parameters (not the SSID enable status)
INT wifi_getSSIDEnable(INT ssidIndex, BOOL *output_bool); //Tr181
//Set SSID enable configuration parameters
INT wifi_setSSIDEnable(INT ssidIndex, BOOL enable); //Tr181

//Device.WiFi.SSID.{i}.Status
//Get the SSID enable status
INT wifi_getSSIDStatus(INT ssidIndex, CHAR *output_string); //Tr181

//Device.WiFi.SSID.{i}.Alias

//Device.WiFi.SSID.{i}.Name
// Outputs a 32 byte or less string indicating the SSID name.  Sring buffer must be preallocated by the caller.
INT wifi_getSSIDName(INT apIndex, CHAR *output_string);        
// accepts a max 32 byte string and sets an internal variable to the SSID name          
INT wifi_setSSIDName(INT apIndex, CHAR *ssid_string);
// push the ssid name to the hardware //repleaced by wifi_applySSIDSettings
//INT wifi_pushSSIDName(INT apIndex, CHAR *ssid);                         

//Device.WiFi.SSID.{i}.LastChange

//Device.WiFi.SSID.{i}.LowerLayers

//Device.WiFi.SSID.{i}.BSSID
//Get the BSSID 
INT wifi_getBaseBSSID(INT ssidIndex, CHAR *output_string);	//RDKB

//Device.WiFi.SSID.{i}.MACAddress
//Get the MAC address associated with this Wifi SSID
INT wifi_getSSIDMACAddress(INT ssidIndex, CHAR *output_string); //Tr181

//Device.WiFi.SSID.{i}.SSID

//-----------------------------------------------------------------------------------------------
//Device.WiFi.SSID.{i}.Stats.
//Device.WiFi.SSID.{i}.Stats.BytesSent
//Device.WiFi.SSID.{i}.Stats.BytesReceived
//Device.WiFi.SSID.{i}.Stats.PacketsSent
//Device.WiFi.SSID.{i}.Stats.PacketsReceived

//Device.WiFi.SSID.{i}.Stats.RetransCount		
//Device.WiFi.SSID.{i}.Stats.FailedRetransCount	
//Device.WiFi.SSID.{i}.Stats.RetryCount	
//Device.WiFi.SSID.{i}.Stats.MultipleRetryCount	
//Device.WiFi.SSID.{i}.Stats.ACKFailureCount	
//Device.WiFi.SSID.{i}.Stats.AggregatedPacketCount	
	 
//Device.WiFi.SSID.{i}.Stats.ErrorsSent
//Device.WiFi.SSID.{i}.Stats.ErrorsReceived
//Device.WiFi.SSID.{i}.Stats.UnicastPacketsSent
//Device.WiFi.SSID.{i}.Stats.UnicastPacketsReceived
//Device.WiFi.SSID.{i}.Stats.DiscardPacketsSent
//Device.WiFi.SSID.{i}.Stats.DiscardPacketsReceived
//Device.WiFi.SSID.{i}.Stats.MulticastPacketsSent
//Device.WiFi.SSID.{i}.Stats.MulticastPacketsReceived
//Device.WiFi.SSID.{i}.Stats.BroadcastPacketsSent
//Device.WiFi.SSID.{i}.Stats.BroadcastPacketsReceived
//Device.WiFi.SSID.{i}.Stats.UnknownProtoPacketsReceived	

//Get the basic SSID traffic static info
INT wifi_getSSIDTrafficStats2(INT ssidIndex, wifi_ssidTrafficStats2_t *output_struct); //Tr181

//Apply SSID and AP (in the case of Acess Point devices) to the hardware
//Not all implementations may need this function.  If not needed for a particular implementation simply return no-error (0)
INT wifi_applySSIDSettings(INT ssidIndex);


//-----------------------------------------------------------------------------------------------
//Device.WiFi.NeighboringWiFiDiagnostic.	
//Device.WiFi.NeighboringWiFiDiagnostic.DiagnosticsState
//Device.WiFi.NeighboringWiFiDiagnostic.ResultNumberOfEntries

//-----------------------------------------------------------------------------------------------
//Device.WiFi.NeighboringWiFiDiagnostic.Result.{i}.	
//Device.WiFi.NeighboringWiFiDiagnostic.Result.{i}.Radio
//Device.WiFi.NeighboringWiFiDiagnostic.Result.{i}.SSID
//Device.WiFi.NeighboringWiFiDiagnostic.Result.{i}.BSSID
//Device.WiFi.NeighboringWiFiDiagnostic.Result.{i}.Mode						
//Device.WiFi.NeighboringWiFiDiagnostic.Result.{i}.Channel
//Device.WiFi.NeighboringWiFiDiagnostic.Result.{i}.SignalStrength
//Device.WiFi.NeighboringWiFiDiagnostic.Result.{i}.SecurityModeEnabled
//Device.WiFi.NeighboringWiFiDiagnostic.Result.{i}.EncryptionMode	
//Device.WiFi.NeighboringWiFiDiagnostic.Result.{i}.OperatingFrequencyBand
//Device.WiFi.NeighboringWiFiDiagnostic.Result.{i}.SupportedStandards		
//Device.WiFi.NeighboringWiFiDiagnostic.Result.{i}.OperatingStandards
//Device.WiFi.NeighboringWiFiDiagnostic.Result.{i}.OperatingChannelBandwidth
//Device.WiFi.NeighboringWiFiDiagnostic.Result.{i}.BeaconPeriod	
//Device.WiFi.NeighboringWiFiDiagnostic.Result.{i}.Noise
//Device.WiFi.NeighboringWiFiDiagnostic.Result.{i}.BasicDataTransferRates
//Device.WiFi.NeighboringWiFiDiagnostic.Result.{i}.SupportedDataTransferRates
//Device.WiFi.NeighboringWiFiDiagnostic.Result.{i}.DTIMPeriod
//Device.WiFi.NeighboringWiFiDiagnostic.Result.{i}.X_COMCAST-COM_ChannelUtilization

//Start the wifi scan and get the result into output buffer for RDKB to parser. The result will be used to manage endpoint list
//HAL funciton should allocate an data structure array, and return to caller with "neighbor_ap_array"
INT wifi_getNeighboringWiFiDiagnosticResult2(INT radioIndex, wifi_neighbor_ap2_t **neighbor_ap_array, UINT *output_array_size); //Tr181	

//>> Deprecated: used for old RDKB code. 
INT wifi_getSSIDTrafficStats(INT ssidIndex, wifi_ssidTrafficStats_t *output_struct); //Tr181
INT wifi_getBasicTrafficStats(INT apIndex, wifi_basicTrafficStats_t *output_struct);  // outputs basic traffic stats per AP
INT wifi_getWifiTrafficStats(INT apIndex, wifi_trafficStats_t *output_struct); // outputs more detailed traffic stats per AP
INT wifi_getNeighboringWiFiDiagnosticResult(wifi_neighbor_ap_t **neighbor_ap_array, UINT *output_array_size); //Tr181
INT wifi_getAllAssociatedDeviceDetail(INT apIndex, ULONG *output_ulong, wifi_device_t **output_struct); //RDKB
//<<

//>> -------------------- wifi_ap_hal -----------------------------------
//---------------------------------------------------------------------------------------------------
//
// Additional Wifi radio level APIs used for RDKB Access Point devices
//
//---------------------------------------------------------------------------------------------------

//Device.WiFi.X_RDKCENTRAL-COM_BandSteering object
//Device.WiFi.X_RDKCENTRAL-COM_BandSteering.Capability bool r/o
//To get Band Steering Capability
INT wifi_getBandSteeringCapability(BOOL *support); 

//Device.WiFi.X_RDKCENTRAL-COM_BandSteering.Enable bool r/w
//To get Band Steering enable status
INT wifi_getBandSteeringEnable(BOOL *enable);

//To turn on/off Band steering
INT wifi_setBandSteeringEnable(BOOL enable);

//Device.WiFi.X_RDKCENTRAL-COM_BandSteering.BandSetting.{i}.UtilizationThreshold int r/w
//to set and read the band steering BandUtilizationThreshold parameters 
INT wifi_getBandSteeringBandUtilizationThreshold (INT radioIndex, INT *pBuThreshold);
INT wifi_setBandSteeringBandUtilizationThreshold (INT radioIndex, INT buThreshold);

//Device.WiFi.X_RDKCENTRAL-COM_BandSteering.BandSetting.{i}.RSSIThreshold int r/w
//to set and read the band steering RSSIThreshold parameters 
INT wifi_getBandSteeringRSSIThreshold (INT radioIndex, INT *pRssiThreshold);
INT wifi_setBandSteeringRSSIThreshold (INT radioIndex, INT rssiThreshold);

//Device.WiFi.X_RDKCENTRAL-COM_BandSteering.BandSetting.{i}.PhyRateThreshold int r/w
//to set and read the band steering physical modulation rate threshold parameters 
INT wifi_getBandSteeringPhyRateThreshold (INT radioIndex, INT *pPrThreshold); //If chip is not support, return -1
INT wifi_setBandSteeringPhyRateThreshold (INT radioIndex, INT prThreshold); //If chip is not support, return -1

//Device.WiFi.X_RDKCENTRAL-COM_BandSteering.History string r/o
INT wifi_getBandSteeringLog(INT record_index, ULONG *pSteeringTime, CHAR *pClientMAC, INT *pSourceSSIDIndex, INT *pDestSSIDIndex, INT *pSteeringReason); //if no steering or redord_index is out of boundary, return -1. pSteeringTime returns the UTC time in seconds. pClientMAC is pre allocated as 64bytes. pSteeringReason returns the predefined steering trigger reason 
	

INT wifi_factoryResetAP(int apIndex); 	//Restore AP paramters to default without change other AP nor Radio parameters (No need to reboot wifi)
INT wifi_setRadioCtsProtectionEnable(INT apIndex, BOOL enable);          //P3 // enables CTS protection for the radio used by this AP
INT wifi_setRadioObssCoexistenceEnable(INT apIndex, BOOL enable);        // enables OBSS Coexistence - fall back to 20MHz if necessary for the radio used by this ap
INT wifi_setRadioFragmentationThreshold(INT apIndex, UINT threshold);    //P3 // sets the fragmentation threshold in bytes for the radio used by this ap
INT wifi_setRadioSTBCEnable(INT radioIndex, BOOL STBC_Enable);           // enable STBC mode in the hardwarwe, 0 == not enabled, 1 == enabled 
INT wifi_getRadioAMSDUEnable(INT radioIndex, BOOL *output_bool);         // outputs A-MSDU enable status, 0 == not enabled, 1 == enabled 
INT wifi_setRadioAMSDUEnable(INT radioIndex, BOOL amsduEnable);          // enables A-MSDU in the hardware, 0 == not enabled, 1 == enabled  
INT wifi_getRadioTxChainMask(INT radioIndex, INT *output_int);           //P2  // outputs the number of Tx streams
INT wifi_setRadioTxChainMask(INT radioIndex, INT numStreams);            //P2  // sets the number of Tx streams to an enviornment variable  
INT wifi_getRadioRxChainMask(INT radioIndex, INT *output_int);           //P2  // outputs the number of Rx streams
INT wifi_setRadioRxChainMask(INT radioIndex, INT numStreams);            //P2  // sets the number of Rx streams to an enviornment variable

//>> Deprecated: 
INT wifi_pushBridgeInfo(INT apIndex); 									 //P2  // Push the BridgeInfo environment variables to the hardware
INT wifi_pushRadioChannel(INT radioIndex, UINT channel);                 //P2  // push the channel number setting to the hardware  //Applying changes with wifi_applyRadioSettings().
INT wifi_pushRadioChannelMode(INT radioIndex);                           //P2  // push the channel mode enviornment variable that is set by "wifi_setChannelMode()" to the hardware  //Applying changes with wifi_applyRadioSettings().
INT wifi_pushRadioTxChainMask(INT radioIndex);                           //P2  // push the enviornment varible that is set by "wifi_setTxChainMask()" to the hardware //Applying changes with wifi_applyRadioSettings().
INT wifi_pushRadioRxChainMask(INT radioIndex);                           //P2  // push the enviornment varible that is set by "wifi_setRxChainMask()" to the hardware //Applying changes with wifi_applyRadioSettings().
//<<

INT wifi_pushSSID(INT apIndex, CHAR *ssid); 							 // push the enviornment varible that is set by "wifi_setSsidName" to the hardware    
INT wifi_pushSsidAdvertisementEnable(INT apIndex, BOOL enable);			 // push the enviornment varible that is set by "wifi_setApSsidAdvertisementEnable" to the hardware	
INT wifi_getRadioUpTime(INT radioIndex, ULONG *uptime);					 // get the number of seconds elapsed since radio is started	 


INT wifi_getRadioReverseDirectionGrantSupported(INT radioIndex, BOOL *output_bool);    //Get radio RDG enable Support
INT wifi_getRadioReverseDirectionGrantEnable(INT radioIndex, BOOL *output_bool);    //Get radio RDG enable setting
INT wifi_setRadioReverseDirectionGrantEnable(INT radioIndex, BOOL enable);			//Set radio RDG enable setting
INT wifi_getRadioDeclineBARequestEnable(INT radioIndex, BOOL *output_bool);			//Get radio ADDBA enable setting
INT wifi_setRadioDeclineBARequestEnable(INT radioIndex, BOOL enable);				//Set radio ADDBA enable setting
INT wifi_getRadioAutoBlockAckEnable(INT radioIndex, BOOL *output_bool);				//Get radio auto block ack enable setting
INT wifi_setRadioAutoBlockAckEnable(INT radioIndex, BOOL enable);					//Set radio auto block ack enable setting
INT wifi_getRadio11nGreenfieldSupported(INT radioIndex, BOOL *output_bool);			//Get radio 11n pure mode enable Support
INT wifi_getRadio11nGreenfieldEnable(INT radioIndex, BOOL *output_bool);			//Get radio 11n pure mode enable setting
INT wifi_setRadio11nGreenfieldEnable(INT radioIndex, BOOL enable);					//Set radio 11n pure mode enable setting
INT wifi_getRadioIGMPSnoopingEnable(INT radioIndex, BOOL *output_bool);				//Get radio IGMP snooping enable setting
INT wifi_setRadioIGMPSnoopingEnable(INT radioIndex, BOOL enable);					//Set radio IGMP snooping enable setting
//---------------------------------------------------------------------------------------------------
//
// Additional Wifi AP level APIs used for Access Point devices
//
//---------------------------------------------------------------------------------------------------


//AP HAL
INT wifi_createAp(INT apIndex, INT radioIndex, CHAR *essid, BOOL hideSsid);  // creates a new ap and pushes these parameters to the hardware
INT wifi_deleteAp(INT apIndex);                                     // deletes this ap entry on the hardware, clears all internal variables associaated with this ap
INT wifi_getApName(INT apIndex, CHAR *output_string);                 // Outputs a 16 byte or less name assocated with the AP.  String buffer must be pre-allocated by the caller
INT wifi_getApIndexFromName(CHAR *inputSsidString, INT *ouput_int);	 // Outputs the index number in that corresponds to the SSID string

INT wifi_getApBeaconType(INT apIndex, CHAR *output_string);           // Outputs a 32 byte or less string indicating the beacon type as "None", "Basic", "WPA", "11i", "WPAand11i"
INT wifi_setApBeaconType(INT apIndex, CHAR *beaconTypeString);        // Sets the beacon type enviornment variable. Allowed input strings are "None", "Basic", "WPA, "11i", "WPAand11i"
INT wifi_setApBeaconInterval(INT apIndex, INT beaconInterval);        // sets the beacon interval on the hardware for this AP
INT wifi_setApDTIMInterval(INT apIndex, INT dtimInterval);			  // Sets the DTIM interval for this AP	
INT wifi_getApRtsThresholdSupported(INT apIndex, BOOL *output_bool);  // Get the packet size threshold supported. 
INT wifi_setApRtsThreshold(INT apIndex, UINT threshold);              // sets the packet size threshold in bytes to apply RTS/CTS backoff rules. 

INT wifi_getApWpaEncryptoinMode(INT apIndex, CHAR *output_string);    // ouputs up to a 32 byte string as either "TKIPEncryption", "AESEncryption", or "TKIPandAESEncryption"
INT wifi_setApWpaEncryptionMode(INT apIndex, CHAR *encMode);          // sets the encyption mode enviornment variable.  Valid string format is "TKIPEncryption", "AESEncryption", or "TKIPandAESEncryption"
INT wifi_removeApSecVaribles(INT apIndex);                            // deletes internal security varable settings for this ap
INT wifi_disableApEncryption(INT apIndex);                            // changes the hardware settings to disable encryption on this ap
INT wifi_setApAuthMode(INT apIndex, INT mode);                        // set the authorization mode on this ap. mode mapping as: 1: open, 2: shared, 4:auto
INT wifi_setApBasicAuthenticationMode(INT apIndex, CHAR *authMode);   // sets an enviornment variable for the authMode. Valid strings are "None", "EAPAuthentication" or "SharedAuthentication"

INT wifi_getApNumDevicesAssociated(INT apIndex, ULONG *output_ulong); // Outputs the number of stations associated per AP
INT wifi_kickApAssociatedDevice(INT apIndex, CHAR *client_mac);  	// manually removes any active wi-fi association with the device specified on this ap

INT wifi_getApRadioIndex(INT apIndex, INT *output_int);                // outputs the radio index for the specified ap
INT wifi_setApRadioIndex(INT apIndex, INT radioIndex);                // sets the radio index for the specific ap

INT wifi_getApAclDevices(INT apIndex, CHAR *macArray, UINT buf_size);	// Get the ACL MAC list per AP
INT wifi_addApAclDevice(INT apIndex, CHAR *DeviceMacAddress);         // adds the mac address to the filter list
INT wifi_delApAclDevice(INT apIndex, CHAR *DeviceMacAddress);         // deletes the mac address from the filter list
INT wifi_getApAclDeviceNum(INT apIndex, UINT *output_uint);           // outputs the number of devices in the filter list
INT wifi_kickApAclAssociatedDevices(INT apIndex,BOOL enable);         // enable kick for devices on acl black list
INT wifi_setApMacAddressControlMode(INT apIndex, INT filterMode);     // sets the mac address filter control mode.  0 == filter disabled, 1 == filter as whitelist, 2 == filter as blacklist
INT wifi_setApVlanEnable(INT apIndex, BOOL VlanEnabled);              // enables internal gateway VLAN mode.  In this mode a Vlan tag is added to upstream (received) data packets before exiting the Wifi driver.  VLAN tags in downstream data are stripped from data packets before transmission.  Default is FALSE. 

INT wifi_setApVlanID(INT apIndex, INT vlanId);                        // sets the vlan ID for this ap to an internal enviornment variable
INT wifi_getApBridgeInfo(INT index, CHAR *bridgeName, CHAR *IP, CHAR *subnet);	// gets bridgeName, IP address and Subnet.
INT wifi_setApBridgeInfo(INT apIndex, CHAR *bridgeName, CHAR *IP, CHAR *subnet);   //sets bridgeName, IP address and Subnet to internal enviornment variables. bridgeName is a maximum of 32 characters, 
//INT wifi_pushApBridgeInfo(INT apIndex);                               // push the BridgeInfo enviornment variables to the hardware //Applying changes with wifi_applyRadioSettings()
INT wifi_resetApVlanCfg(INT apIndex);                                 // reset the vlan configuration for this ap
//INT wifi_setApBridging(INT apIndex, BOOL bridgeEnable);             // set the enviornment variables to control briding.  If isolation is requried then disable bridging.  //use wifi_setApIsolationEnable instead
//INT wifi_getApRouterEnable(INT apIndex, BOOL *output_bool);           //P4 // Outputs a bool that indicates if router is enabled for this ap
//INT wifi_setApRouterEnable(INT apIndex, BOOL routerEnabled);          //P4 // sets the routerEnabled variable for this ap

INT wifi_createHostApdConfig(INT apIndex, BOOL createWpsCfg);       // creates configuration variables needed for WPA/WPS.  These variables are implementation dependent and in some implementations these variables are used by hostapd when it is started.  Specific variables that are needed are dependent on the hostapd implementation. These variables are set by WPA/WPS security functions in this wifi HAL.  If not needed for a particular implementation this function may simply return no error.
INT wifi_startHostApd();                                            // starts hostapd, uses the variables in the hostapd config with format compatible with the specific hostapd implementation
INT wifi_stopHostApd();                                             // stops hostapd

//-----------------------------------------------------------------------------------------------
//Device.WiFi.AccessPoint.{i}.	
//Device.WiFi.AccessPoint.{i}.Enable
INT wifi_setApEnable(INT apIndex, BOOL enable);                       // sets the AP enable status variable for the specified ap.
INT wifi_getApEnable(INT apIndex, BOOL *output_bool);                 // Outputs the setting of the internal variable that is set by wifi_setEnable().  

//Device.WiFi.AccessPoint.{i}.Status
INT wifi_getApStatus(INT apIndex, CHAR *output_string);  				// Outputs the AP "Enabled" "Disabled" status from driver 

//Device.WiFi.AccessPoint.{i}.SSIDAdvertisementEnabled		
//Indicates whether or not beacons include the SSID name.
INT wifi_getApSsidAdvertisementEnable(INT apIndex, BOOL *output_bool);// outputs a 1 if SSID on the AP is enabled, else ouputs 0
INT wifi_setApSsidAdvertisementEnable(INT apIndex, BOOL enable);      // sets an internal variable for ssid advertisement.  Set to 1 to enable, set to 0 to disable
INT wifi_pushApSsidAdvertisementEnable(INT apIndex, BOOL enable);     // push the ssid advertisement enable variable to the hardware //Applying changs with wifi_applyRadioSettings()

//Device.WiFi.AccessPoint.{i}.RetryLimit		
//The maximum number of retransmission for a packet. This corresponds to IEEE 802.11 parameter dot11ShortRetryLimit.
INT wifi_getApRetryLimit(INT apIndex, UINT *output); 
INT wifi_setApRetryLimit(INT apIndex, UINT number); 

//Device.WiFi.AccessPoint.{i}.WMMCapability	
//Indicates whether this access point supports WiFi Multimedia (WMM) Access Categories (AC).
INT wifi_getApWMMCapability(INT apIndex, BOOL *output); 

//Device.WiFi.AccessPoint.{i}.UAPSDCapability		
//Indicates whether this access point supports WMM Unscheduled Automatic Power Save Delivery (U-APSD). Note: U-APSD support implies WMM support.
INT wifi_getApUAPSDCapability(INT apIndex, BOOL *output); 			
			
//Device.WiFi.AccessPoint.{i}.WMMEnable		
//Whether WMM support is currently enabled. When enabled, this is indicated in beacon frames.
INT wifi_getApWmmEnable(INT apIndex, BOOL *output);                   
INT wifi_setApWmmEnable(INT apIndex, BOOL enable);                    // enables/disables WMM on the hardwawre for this AP.  enable==1, disable == 0

//Device.WiFi.AccessPoint.{i}.UAPSDEnable		
//Whether U-APSD support is currently enabled. When enabled, this is indicated in beacon frames. Note: U-APSD can only be enabled if WMM is also enabled.
INT wifi_getApWmmUapsdEnable(INT apIndex, BOOL *output);               
INT wifi_setApWmmUapsdEnable(INT apIndex, BOOL enable);               // enables/disables Automatic Power Save Delivery on the hardwarwe for this AP

// Sets the WMM ACK polity on the hardware. AckPolicy false means do not acknowledge, true means acknowledge
INT wifi_setApWmmOgAckPolicy(INT apIndex, INT class, BOOL ackPolicy);  //RDKB
			
//Device.WiFi.AccessPoint.{i}.IsolationEnable	
//Enables or disables device isolation.	A value of true means that the devices connected to the Access Point are isolated from all other devices within the home network (as is typically the case for a Wireless Hotspot).	
INT wifi_getApIsolationEnable(INT apIndex, BOOL *output); //Tr181		
INT wifi_setApIsolationEnable(INT apIndex, BOOL enable); //Tr181					

//Device.WiFi.AccessPoint.{i}.MaxAssociatedDevices	
//The maximum number of devices that can simultaneously be connected to the access point. A value of 0 means that there is no specific limit.			
INT wifi_getApMaxAssociatedDevices(INT apIndex, UINT *output); //Tr181		
INT wifi_setApMaxAssociatedDevices(INT apIndex, UINT number); //Tr181					
					
//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_AssociatedDevicesHighWatermarkThreshold	
//The HighWatermarkThreshold value that is lesser than or equal to MaxAssociatedDevices. Setting this parameter does not actually limit the number of clients that can associate with this access point as that is controlled by MaxAssociatedDevices.	MaxAssociatedDevices or 50. The default value of this parameter should be equal to MaxAssociatedDevices. In case MaxAssociatedDevices is 0 (zero), the default value of this parameter should be 50. A value of 0 means that there is no specific limit and Watermark calculation algorithm should be turned off.			
INT wifi_getApAssociatedDevicesHighWatermarkThreshold(INT apIndex, UINT *output); //Tr181	//P3
INT wifi_setApAssociatedDevicesHighWatermarkThreshold(INT apIndex, UINT Threshold); //Tr181		//P3			

//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_AssociatedDevicesHighWatermarkThresholdReached		
//Number of times the current total number of associated device has reached the HighWatermarkThreshold value. This calculation can be based on the parameter AssociatedDeviceNumberOfEntries as well. Implementation specifics about this parameter are left to the product group and the device vendors. It can be updated whenever there is a new client association request to the access point.	
INT wifi_getApAssociatedDevicesHighWatermarkThresholdReached(INT apIndex, UINT *output); //Tr181 //P3

//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_AssociatedDevicesHighWatermark	
//Maximum number of associated devices that have ever associated with the access point concurrently since the last reset of the device or WiFi module.	
INT wifi_getApAssociatedDevicesHighWatermark(INT apIndex, UINT *output); //Tr181	//P3

//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_AssociatedDevicesHighWatermarkDate		
//Date and Time at which the maximum number of associated devices ever associated with the access point concurrenlty since the last reset of the device or WiFi module (or in short when was X_COMCAST-COM_AssociatedDevicesHighWatermark updated). This dateTime value is in UTC.	
INT wifi_getApAssociatedDevicesHighWatermarkDate(INT apIndex, ULONG *output_in_seconds); //Tr181	//P3

					
//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_InterworkingServiceCapability	boolean	R	
//When true, indicates whether the access point supports interworking with external networks.	

//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_InterworkingServiceEnable	boolean	W	
//Enables or disables capability of the access point to intework with external network. When enabled, the access point includes Interworking IE in the beacon frames.	

//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_PasspointCapability	boolean	R	
//Indicates whether this access point supports Passpoint (aka Hotspot 2.0). The Passpoint enabled AccessPoint must use WPA2-Enterprise security and WPS must not be enabled.	

//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_PasspointEnable	boolean	W	
//Whether Passpoint (aka Hotspot 2.0) support is currently enabled. When enabled, Passpoint specific information elemenets are indicated in beacon frames.	

//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_MAC_FilteringMode	string	R	
//"The current operational state of the MAC Filtering Mode, Enumeration of:    Allow-ALL, Allow, Deny			

//-----------------------------------------------------------------------------------------------				  
//Device.WiFi.AccessPoint.{i}.Security.	

//Device.WiFi.AccessPoint.{i}.Security.ModesSupported	
//Comma-separated list of strings. Indicates which security modes this AccessPoint instance is capable of supporting. Each list item is an enumeration of: None,WEP-64,WEP-128,WPA-Personal,WPA2-Personal,WPA-WPA2-Personal,WPA-Enterprise,WPA2-Enterprise,WPA-WPA2-Enterprise
INT wifi_getApSecurityModesSupported(INT apIndex, CHAR *output); 			
			
//Device.WiFi.AccessPoint.{i}.Security.ModeEnabled	string	W	
//The value MUST be a member of the list reported by the ModesSupported parameter. Indicates which security mode is enabled.
INT wifi_getApSecurityModeEnabled(INT apIndex, CHAR *output);    
INT wifi_setApSecurityModeEnabled(INT apIndex, CHAR *encMode);        

//Device.WiFi.AccessPoint.{i}.Security.WEPKey	
//A WEP key expressed as a hexadecimal string.

//Device.WiFi.AccessPoint.{i}.Security.PreSharedKey		
//A literal PreSharedKey (PSK) expressed as a hexadecimal string.
INT wifi_getApSecurityPreSharedKey(INT apIndex, CHAR *output_string);         // output_string must be pre-allocated as 64 character string by caller
INT wifi_setApSecurityPreSharedKey(INT apIndex, CHAR *preSharedKey);          // sets an enviornment variable for the psk. Input string preSharedKey must be a maximum of 64 characters

//Device.WiFi.AccessPoint.{i}.Security.KeyPassphrase	string­(63)	W	
//A passphrase from which the PreSharedKey is to be generated, for WPA-Personal or WPA2-Personal or WPA-WPA2-Personal security modes.
INT wifi_getApSecurityKeyPassphrase(INT apIndex, CHAR *output_string);        // outputs the passphrase, maximum 63 characters
INT wifi_setApSecurityKeyPassphrase(INT apIndex, CHAR *passPhrase);           // sets the passphrase enviornment variable, max 63 characters

//Device.WiFi.AccessPoint.{i}.Security.RekeyingInterval	unsignedInt	W	
//The interval (expressed in seconds) in which the keys are re-generated.
//INT wifi_getApSecurityWpaRekeyInterval(INT apIndex, INT *output_int);         // outputs the rekey interval
//INT wifi_setApSecurityWpaRekeyInterval(INT apIndex, INT rekeyInterval);       // sets the internal variable for the rekey interval

//Device.WiFi.AccessPoint.{i}.Security.Reset	
//When set to true, this AccessPoint instance's WiFi security settings are reset to their factory default values. The affected settings include ModeEnabled, WEPKey, PreSharedKey and KeyPassphrase.
INT wifi_setApSecurityReset(INT apIndex);

//Device.WiFi.AccessPoint.{i}.Security.X_COMCAST-COM_KeyPassphrase	string­(63)	RW	
//A passphrase from which the PreSharedKey is to be generated, for WPA-Personal or WPA2-Personal or WPA-WPA2-Personal security modes.	If KeyPassphrase is written, then PreSharedKey is immediately generated. The ACS SHOULD NOT set both the KeyPassphrase and the PreSharedKey directly (the result of doing this is undefined). The key is generated as specified by WPA, which uses PBKDF2 from PKCS #5: Password-based Cryptography Specification Version 2.0 ([RFC2898]).	This custom parameter is defined to enable reading the Passphrase via TR-069 /ACS. When read it should return the actual passphrase			
//INT wifi_getApKeyPassphrase(INT apIndex, CHAR *output); //Tr181	
//INT wifi_setApKeyPassphrase(INT apIndex, CHAR *passphase); //Tr181	

//Device.WiFi.AccessPoint.{i}.Security.X_COMCAST-COM_WEPKey	string	RW	
//A WEP key expressed as a hexadecimal string.	WEPKey is used only if ModeEnabled is set to WEP-64 or WEP-128.	A 5 byte WEPKey corresponds to security mode WEP-64 and a 13 byte WEPKey corresponds to security mode WEP-128.	This custom parameter is defined to enable reading the WEPKey via TR-069/ACS. When read it should return the actual WEPKey.	If User enters 10 or 26 Hexadecimal characters, it should return keys as Hexadecimal characters.	If user enters 5 or 13 ASCII character key it should return key as ASCII characters.			

//-----------------------------------------------------------------------------------------------
//Device.WiFi.AccessPoint.{i}.Security.RadiusServerIPAddr	
//Device.WiFi.AccessPoint.{i}.Security.RadiusServerPort	
//Device.WiFi.AccessPoint.{i}.Security.RadiusSecret
//The IP Address and port number of the RADIUS server used for WLAN security. RadiusServerIPAddr is only applicable when ModeEnabled is an Enterprise type (i.e. WPA-Enterprise, WPA2-Enterprise or WPA-WPA2-Enterprise).  String is 64 bytes max
INT wifi_getApSecurityRadiusServer(INT apIndex, CHAR *IP_output, UINT *Port_output, CHAR *RadiusSecret_output); //Tr181	
INT wifi_setApSecurityRadiusServer(INT apIndex, CHAR *IPAddress, UINT port, CHAR *RadiusSecret); //Tr181	
INT wifi_getApSecuritySecondaryRadiusServer(INT apIndex, CHAR *IP_output, UINT *Port_output, CHAR *RadiusSecret_output); //Tr181	
INT wifi_setApSecuritySecondaryRadiusServer(INT apIndex, CHAR *IPAddress, UINT port, CHAR *RadiusSecret); //Tr181	

//Device.WiFi.AccessPoint.{i}.Security.X_COMCAST-COM_RadiusSettings.		
//Device.WiFi.AccessPoint.{i}.Security.X_COMCAST-COM_RadiusSettings.RadiusServerRetries	int	W	
//Device.WiFi.AccessPoint.{i}.Security.X_COMCAST-COM_RadiusSettings.RadiusServerRequestTimeout	int	W	
//Device.WiFi.AccessPoint.{i}.Security.X_COMCAST-COM_RadiusSettings.PMKLifetime	int	W	
//Device.WiFi.AccessPoint.{i}.Security.X_COMCAST-COM_RadiusSettings.PMKCaching	boolean	W	
//Device.WiFi.AccessPoint.{i}.Security.X_COMCAST-COM_RadiusSettings.PMKCacheInterval	int	W	
//Device.WiFi.AccessPoint.{i}.Security.X_COMCAST-COM_RadiusSettings.MaxAuthenticationAttempts	int	W	
//Device.WiFi.AccessPoint.{i}.Security.X_COMCAST-COM_RadiusSettings.BlacklistTableTimeout	int	W	
//Device.WiFi.AccessPoint.{i}.Security.X_COMCAST-COM_RadiusSettings.IdentityRequestRetryInterval	int	W	
//Device.WiFi.AccessPoint.{i}.Security.X_COMCAST-COM_RadiusSettings.QuietPeriodAfterFailedAuthentication	int	W		
INT wifi_getApSecurityRadiusSettings(INT apIndex, wifi_radius_setting_t *output); //Tr181	
INT wifi_setApSecurityRadiusSettings(INT apIndex, wifi_radius_setting_t *input); //Tr181	


//-----------------------------------------------------------------------------------------------
//Device.WiFi.AccessPoint.{i}.WPS.
//Device.WiFi.AccessPoint.{i}.WPS.Enable	
//Enables or disables WPS functionality for this access point.
INT wifi_getApWpsEnable(INT apIndex, BOOL *output_bool);              // outputs the WPS enable state of this ap in output_bool 
INT wifi_setApWpsEnable(INT apIndex, BOOL enableValue);               // sets the WPS enable enviornment variable for this ap to the value of enableValue, 1==enabled, 0==disabled

//Device.WiFi.AccessPoint.{i}.WPS.ConfigMethodsSupported	
//Comma-separated list of strings. Indicates WPS configuration methods supported by the device. Each list item is an enumeration of: USBFlashDrive,Ethernet,ExternalNFCToken,IntegratedNFCToken,NFCInterface,PushButton,PIN
INT wifi_getApWpsConfigMethodsSupported(INT apIndex, CHAR *output); //Tr181				

//Device.WiFi.AccessPoint.{i}.WPS.ConfigMethodsEnabled	string	W	
//Comma-separated list of strings. Each list item MUST be a member of the list reported by the ConfigMethodsSupported parameter. Indicates WPS configuration methods enabled on the device.
INT wifi_getApWpsConfigMethodsEnabled(INT apIndex, CHAR *output_string); // Outputs a common separated list of the enabled WPS config methods, 64 bytes max
INT wifi_setApWpsConfigMethodsEnabled(INT apIndex, CHAR *methodString); // sets an enviornment variable that specifies the WPS configuration method(s).  methodString is a comma separated list of methods USBFlashDrive,Ethernet,ExternalNFCToken,IntegratedNFCToken,NFCInterface,PushButton,PIN

INT wifi_getApWpsDevicePIN(INT apIndex, ULONG *output_ulong);         // outputs the pin value, ulong_pin must be allocated by the caller
INT wifi_setApWpsDevicePIN(INT apIndex, ULONG pin);                   // set an enviornment variable for the WPS pin for the selected AP
INT wifi_getApWpsConfigurationState(INT apIndex, CHAR *output_string); // Output string is either Not configured or Configured, max 32 characters
INT wifi_setApWpsEnrolleePin(INT apIndex, CHAR *pin);                 // sets the WPS pin for this AP
INT wifi_setApWpsButtonPush(INT apIndex);                             // This function is called when the WPS push button has been pressed for this AP
INT wifi_cancelApWPS(INT apIndex);                                    // cancels WPS mode for this AP

//-----------------------------------------------------------------------------------------------
//Device.WiFi.AccessPoint.{i}.AssociatedDevice.{i}.	  
//Device.WiFi.AccessPoint.{i}.AssociatedDevice.{i}.X_COMCAST-COM_OperatingStandard	
//Device.WiFi.AccessPoint.{i}.AssociatedDevice.{i}.X_COMCAST-COM_OperatingChannelBandwidth	
//Device.WiFi.AccessPoint.{i}.AssociatedDevice.{i}.X_COMCAST-COM_SNR
//Device.WiFi.AccessPoint.{i}.AssociatedDevice.{i}.X_COMCAST-COM_InterferenceSources	//P3
//Device.WiFi.AccessPoint.{i}.AssociatedDevice.{i}.X_COMCAST-COM_DataFramesSentAck		//P3
//Device.WiFi.AccessPoint.{i}.AssociatedDevice.{i}.X_COMCAST-COM_DataFramesSentNoAck	//P3
//Device.WiFi.AccessPoint.{i}.AssociatedDevice.{i}.X_COMCAST-COM_BytesSent
//Device.WiFi.AccessPoint.{i}.AssociatedDevice.{i}.X_COMCAST-COM_BytesReceived
//Device.WiFi.AccessPoint.{i}.AssociatedDevice.{i}.X_COMCAST-COM_RSSI
//Device.WiFi.AccessPoint.{i}.AssociatedDevice.{i}.X_COMCAST-COM_MinRSSI				//P3
//Device.WiFi.AccessPoint.{i}.AssociatedDevice.{i}.X_COMCAST-COM_MaxRSSI				//P3
//Device.WiFi.AccessPoint.{i}.AssociatedDevice.{i}.X_COMCAST-COM_Disassociations		//P3
//Device.WiFi.AccessPoint.{i}.AssociatedDevice.{i}.X_COMCAST-COM_AuthenticationFailures	//P3
//HAL funciton should allocate an data structure array, and return to caller with "associated_dev_array"
INT wifi_getApAssociatedDeviceDiagnosticResult(INT apIndex, wifi_associated_dev_t **associated_dev_array, UINT *output_array_size); //Tr181	

//------------------------------------------------------------------------------------------------------
////SSID stearing APIs using blacklisting
//INT wifi_setSsidSteeringPreferredList(INT radioIndex,INT apIndex, INT *preferredAPs[32]);  // prevent any client device from assocating with this ipIndex that has previously had a valid assocation on any of the listed "preferred" SSIDs unless SsidSteeringTimeout has expired for this device. The array lists all APs that are preferred over this AP.  Valid AP values are 1 to 32. Unused positions in this array must be set to 0. This setting becomes active when committed.  The wifi subsystem must default to no preferred SSID when initalized.  
////Using the concept of an “preferred list” provides a solution to most use cases that requrie SSID Steering.  To implement this approach, the AP places the STA into the Access Control DENY list for a given SSID only if the STA has previously associated to one of the SSIDs in the “preferred list” that for SSID.
//INT wifi_setSsidSteeringTimout(INT radioIndex,INT apIndex, ULONG SsidSteeringTimout);  // only prevent the client device from assocatign with this apIndex if the device has connected to a preferred SSID within this timeout period - in units of hours.  This setting becomes active when committed.  


//This call back will be invoked when new wifi client come to associate to AP. 
typedef INT ( * wifi_newApAssociatedDevice_callback)(INT apIndex, wifi_associated_dev_t *associated_dev);
//Callback registration function.
void wifi_newApAssociatedDevice_callback_register(wifi_newApAssociatedDevice_callback callback_proc);

//-----------------------------------------------------------------------------------------------
//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_InterworkingService. 
//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_InterworkingService.AccessNetworkType	
//Access Network Type value to be included in the Interworking IE in the beaconds. (refer 8.4.2.94 of IEEE Std 802.11-2012). Possible values are: 0 - Private network;1 - Private network with guest access;2 - Chargeable public network;3 - Free public network;4 - Personal device network;5 - Emergency services only network;6-13 - Reserved;14 - Test or experimental;15 - Wildcard
//INT wifi_setAccessNetworkType(INT apIndex, INT accessNetworkType);   // P3

//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_InterworkingService.Internet	
//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_InterworkingService.VenueGroupCode	
//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_InterworkingService.VenueTypeCode	
//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_InterworkingService.HESSID	
//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_InterworkingService.DGAFEnable	
//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_InterworkingService.ANQPDomainID
//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_InterworkingService.VenueNamesNumberOfEntries	
//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_InterworkingService.OperatorNamesNumberOfEntries	
//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_InterworkingService.ConsortiumOIsNumberOfEntries	
//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_InterworkingService.DomainNamesNumberOfEntries	
//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_InterworkingService.3GPPNetworksNumberOfEntries	
//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_InterworkingService.NAIRealmsNumberOfEntries	

//-----------------------------------------------------------------------------------------------
//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_Passpoint.VenueNames.{i}.	
//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_Passpoint.VenueNames.{i}.LanguageCode
//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_Passpoint.VenueNames.{i}.VanueName

//-----------------------------------------------------------------------------------------------
//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_Passpoint.OperatorNames.{i}.	
//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_Passpoint.OperatorNames.{i}.LanguageCode
//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_Passpoint.OperatorNames.{i}.OperatorName

//-----------------------------------------------------------------------------------------------
//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_Passpoint.ConsortiumOIs.{i}.	
//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_Passpoint.ConsortiumOIs.{i}.OI	

//-----------------------------------------------------------------------------------------------
//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_Passpoint.DomainNames.{i}.	
//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_Passpoint.DomainNames.{i}.DomainName	

//-----------------------------------------------------------------------------------------------
//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_Passpoint.3GPPNetworks.{i}.	
//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_Passpoint.3GPPNetworks.{i}.MCC	
//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_Passpoint.3GPPNetworks.{i}.MNC	

//-----------------------------------------------------------------------------------------------
//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_Passpoint.NAIRealms.{i}.	
//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_Passpoint.NAIRealms.{i}.NAIRealmEncodingType	
//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_Passpoint.NAIRealms.{i}.NAIRealm	
//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_Passpoint.NAIRealms.{i}.EAPMethodsNumberOfEntries	

//-----------------------------------------------------------------------------------------------
//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_Passpoint.NAIRealms.{i}.EAPMethods.{i}.	
//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_Passpoint.NAIRealms.{i}.EAPMethods.{i}.EAPMethod	
//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_Passpoint.NAIRealms.{i}.EAPMethods.{i}.AuthenticationParametersNumberOfEntries	

//-----------------------------------------------------------------------------------------------
//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_Passpoint.NAIRealms.{i}.EAPMethods.{i}.AuthenticationParameters.{i}.	
//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_Passpoint.NAIRealms.{i}.EAPMethods.{i}.AuthenticationParameters.{i}.ID	
//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_Passpoint.NAIRealms.{i}.EAPMethods.{i}.AuthenticationParameters.{i}.Value	

//-----------------------------------------------------------------------------------------------
//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_Passpoint.WANMetrics.	
//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_Passpoint.WANMetrics.LinkStatus	
//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_Passpoint.WANMetrics.AtCapacity	
//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_Passpoint.WANMetrics.DownlinkSpeed	
//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_Passpoint.WANMetrics.UplinkSpeed	
//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_Passpoint.WANMetrics.DownlinkLoad	
//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_Passpoint.WANMetrics.UplinkLoad	

//-----------------------------------------------------------------------------------------------
//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_Passpoint.OSU.	
//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_Passpoint.OSU.OSUProvidersNumberOfEntries	

//-----------------------------------------------------------------------------------------------
//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_Passpoint.OSU.OSUProviders.{i}.	
//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_Passpoint.OSU.OSUProviders.{i}.OSUServerURI	
//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_Passpoint.OSU.OSUProviders.{i}.OSUMethodsList	
//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_Passpoint.OSU.OSUProviders.{i}.OSUNAI	
//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_Passpoint.OSU.OSUProviders.{i}.NamesNumberOfEntries	
//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_Passpoint.OSU.OSUProviders.{i}.IconsNumberOfEntries	
//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_Passpoint.OSU.OSUProviders.{i}ServiceDescriptionsNumberOfEntries	

//-----------------------------------------------------------------------------------------------
//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_Passpoint.OSU.OSUProviders.{i}.Names.{i}.	
//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_Passpoint.OSU.OSUProviders.{i}.Names.{i}.LanguageCode	
//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_Passpoint.OSU.OSUProviders.{i}.Names.{i}.OSUProviderFriendlyName	

//-----------------------------------------------------------------------------------------------
//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_Passpoint.OSU.OSUProviders.{i}.Icons.{i}.	
//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_Passpoint.OSU.OSUProviders.{i}.Icons.{i}.IconWidth	
//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_Passpoint.OSU.OSUProviders.{i}.Icons.{i}.IconHeight	
//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_Passpoint.OSU.OSUProviders.{i}.Icons.{i}.LanguageCode	

//-----------------------------------------------------------------------------------------------
//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_Passpoint.OSU.OSUProviders.{i}.ServiceDescriptions.{i}.	
//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_Passpoint.OSU.OSUProviders.{i}.ServiceDescriptions.{i}.LanguageCode	
//Device.WiFi.AccessPoint.{i}.X_COMCAST-COM_Passpoint.OSU.OSUProviders.{i}.ServiceDescriptions.{i}.ServiceDescription	

//-----------------------------------------------------------------------------------------------
//Device.IP.Diagnostics.	
//Device.IP.Diagnostics.IPPing.	
//Device.IP.Diagnostics.IPPing.DiagnosticsState	
//Device.IP.Diagnostics.IPPing.Interface
//Device.IP.Diagnostics.IPPing.Host	
//Device.IP.Diagnostics.IPPing.NumberOfRepetitions		
//Device.IP.Diagnostics.IPPing.Timeout	
//Device.IP.Diagnostics.IPPing.DataBlockSize	
//Device.IP.Diagnostics.IPPing.DSCP			

//Device.IP.Diagnostics.IPPing.SuccessCount	
//Device.IP.Diagnostics.IPPing.FailureCount		
//Device.IP.Diagnostics.IPPing.AverageResponseTime		
//Device.IP.Diagnostics.IPPing.MinimumResponseTime		
//Device.IP.Diagnostics.IPPing.MaximumResponseTime			

//Start the ping test and get the result
//INT wifi_getIPDiagnosticsIPPingResult(wifi_diag_ipping_setting_t *input, wifi_diag_ipping_result_t *result); //Tr181		
//--------------------------------------------------------------------------------------------------
// Wifi Airtime Management and QOS APIs to control contention based access to airtime
//INT wifi_clearDownLinkQos(INT apIndex);                             // clears the QOS parameters to the WMM default values for the downlink direction (from the access point to the stations.  This set must take affect when the api wifi_applySSIDSettings() is called.
//INT wifi_setDownLinkQos(INT apIndex, wifi_qos_t qosStruct);        // sets the QOS variables used in the downlink direction (from the access point to the stations).  Values must be allowable values per IEEE 802.11-2012 section 8.4.2.31.  Note:  Some implementations may requrie that all downlink APs on the same radio are set to the same QOS values. Default values are per the WMM spec.  This set must take affect when the api wifi_applySSIDSettings() is called.
//INT wifi_clearUpLinkQos(INT apIndex);                               // clears the QOS parameters to the WMM default values for the uplink direction (from the Wifi stations to the ap.  This must take affect when the api wifi_applySSIDSettings() is called.
//INT wifi_setUpLinkQos (INT apIndex, wifi_qos_t qosStruct);         // sets the QOS variables used in the uplink direction (from the Wifi stations to the AP). Values must be allowable values per IEEE 802.11-2012 section 8.4.2.31. The default values must be per the WMM spec.  This set must take affect when the api wifi_applySSIDSettings() is called.

//--------------------------------------------------------------------------------------------------
// Wifi Airtime Management and QOS APIs to control downlink queue prioritization
//INT wifi_getDownLinkQueuePrioritySupport (INT apIndex, INT *supportedPriorityLevels);  //This api is used to get the the number of supported downlink queuing priority levels for each AP/SSID.  If priority queuing levels for AP/SSIDs are not supported, the output should be set to 1. A value of 1 indicates that only the same priority level is supported for all AP/SSIDs.
//INT wifi_setDownLinkQueuePriority(INT apIndex, INT priorityLevel); // this sets the queue priority level for each AP/SSID in the downlink direction.  It is used with the downlink QOS api to manage priority access to airtime in the downlink direction.  This set must take affect when the api wifi_applySSIDSettings() is called.

//<< ------------------------------ wifi_ap_hal -----------------------

#else
#error "! __WIFI_HAL_H__"
#endif
