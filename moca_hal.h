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
   Copyright [2014] [Cisco Systems, Inc.]
 
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

    module: moca_hal.h

        For CCSP Component:  MoCA_Provisioning_and_management

    ---------------------------------------------------------------

    copyright:

        Cisco Systems, Inc., 2014
        All Rights Reserved.

    ---------------------------------------------------------------

    description:

        This header file gives the function call prototypes and 
        structure definitions used for the RDK-Broadband 
        MoCA hardware abstraction layer

        NOTE:
        THIS VERSION IS AN EARLY DRAFT INTENDED TO GET COMMENTS FROM COMCAST.
        TESTING HAS NOT YET BEEN COMPLETED.  
       
    ---------------------------------------------------------------

    environment:

        This HAL layer is intended to support MoCA drivers 
        through an open API.  The current implementation created
        below this HAL supports MoCA.
        Changes may be needed to support other MoCA enviornments.

    ---------------------------------------------------------------

    author:

        Cisco

**********************************************************************/

#ifndef __MOCA_HAL_H__
#define __MOCA_HAL_H__


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

#ifndef STATUS_SUCCESS
#define STATUS_SUCCESS     0
#endif

#ifndef STATUS_FAILURE
#define STATUS_FAILURE     -1
#endif

#define kMoca_MaxCpeList		256
#define kMoca_MaxMocaNodes              16

/**********************************************************************
                ENUMERATION DEFINITIONS
**********************************************************************/
typedef enum 
{
    IF_STATUS_Up               = 1,
    IF_STATUS_Down,
    IF_STATUS_Unknown,
    IF_STATUS_Dormant,
    IF_STATUS_NotPresent,
    IF_STATUS_LowerLayerDown,
    IF_STATUS_Error
} moca_if_status_t;

/**********************************************************************
                STRUCTURE DEFINITIONS
**********************************************************************/
typedef struct {
	/* Instance Number when Multiple MoCA interfaces exist.
		0 - In the case of only one interface.  */
    ULONG                           InstanceNumber;
	/* Set the Alias Name for the interface */
    CHAR                            Alias[64];

	/* Enable/Disable the interface. */
    BOOL                         	bEnabled;
	/* Enable/Disable the Node's preference to be Network Coordinator */
    BOOL                         	bPreferredNC;
	/* Enable/Disable Link Privacy. A Password is required when 
		Privacy is enabled */
    BOOL                         	PrivacyEnabledSetting;
	/* Set of Frequencies that should be used for forming network (bitmask) */
    UCHAR                           FreqCurrentMaskSetting[128];
	/* Privacy Password. This field is valid only if the Link Privacy is 
		enabled. */
    CHAR                            KeyPassphrase[18];
	/* Maximum Transmission Power allowed */
    INT                             TxPowerLimit;
	/* AutoPowerControlPhyRate: PowerCtrlPhyTarget
		Used as a reference to achieve the PHY rate by adjusting power. */ 
    ULONG                           AutoPowerControlPhyRate;
	/* Maximum Transmission Power Allowed when transmitting
		Beacons */
    ULONG                           BeaconPowerLimit;

	/* Maximum Ingress/Egress Bandwidth Thresholds */
    ULONG                           MaxIngressBWThreshold;
    ULONG                           MaxEgressBWThreshold;

	/* Reset MoCA Configuration Parameters to Defaults */
    BOOL                            Reset;
	/* Enable/Disable the Node to operate in mixed mode (1.0/1.1/2.0 versions).
		i.e Enable backward compatibility on the MoCA Protocol Versions. */
    BOOL                            MixedMode;
	/* Enable/Disable the Node to operate in single frequency mode or scanning mode. */
    BOOL                            ChannelScanning;
	/* Enable/Disable adjusting Power to achieve the Target PHY rate */
    BOOL                            AutoPowerControlEnable;
	/* Enable/Disable the Node to support Taboo Mask */
    BOOL                            EnableTabooBit;
	/* Set of Frequencis to Avoid (bitmask) */
    UCHAR                           NodeTabooMask[128];
	/* Set of Frequencies to Scan for Beacons to form network (bitmask). 
		Very often, this is same as FreqCurrentMaskSetting. */
    UCHAR                           ChannelScanMask[128];
} moca_cfg_t;

typedef struct {
	/* Interface Name (for example: moca0) */
    CHAR                            Name[64];           /* Uniquely identifying the entry */
	/* MAC Address of the Local Node */
    UCHAR                           MacAddress[18];
	/* Firmware Version of the MoCA Firmware */
    CHAR                            FirmwareVersion[64];
	/* Maximum PHY Rate that the Node can support */
    ULONG                           MaxBitRate;
	/* Highest Version of the MoCA Protocol that the Local Node Supports */
    CHAR                            HighestVersion[64];
	/* Frequencies that the Local Node supports (bitmask) */
    UCHAR                           FreqCapabilityMask[8];
	/* Frequencies that the Local Node does not support (bitmask) */
    UCHAR                           NetworkTabooMask[128];
	/* Beacon Backoff in dB */
    ULONG                           TxBcastPowerReduction;
	/* Local Node is QAM-256 Capable or Not */
    BOOL                            QAM256Capable;
	/* Local Node can aggregate Ethernet Packets for MoCA PDU transfers */
    BOOL                           PacketAggregationCapability;
} moca_static_info_t;

typedef struct {
	/* Current Status of the LoCAL Interface (Up/Down etc.) */
    moca_if_status_t                Status;
	/* Last Link Status Change (Up/Down/ etc.) */
    ULONG                           LastChange;

	/* Maximum Ingress/Egress Bandwidth reached */
    ULONG                           MaxIngressBW;
    ULONG                           MaxEgressBW;

	/* Current Operating MoCA Protocol Version 
		Valid Values: 1.0, 1.1, 2.0 */
    CHAR                            CurrentVersion[64];
	/* Node ID of the Network Coordinator.
		Valid Values: 0-7 (Protocol: 1.0)
		Valid Values: 0-15 (Protocol: 1.1, 2.0) */
    ULONG                           NetworkCoordinator;
	/* Node ID of the Local Node.
		Valid Values: 0-7 (Protocol: 1.0)
		Valid Values: 0-15 (Protocol: 1.1, 2.0) */
    ULONG                           NodeID;
	/* Node ID of the Backup Network Coordinator
		Valid Values: 0-7 (Protocol: 1.0)
		Valid Values: 0-15 (Protocol: 1.1, 2.0) */
    ULONG                           BackupNC;
	/* If Privacy is enabled on the network */
    BOOL                            PrivacyEnabled;
	/* This should be same as the Configured Frequencies that the 
		Node can operate */
    UCHAR                           FreqCurrentMask[8];
	/* The Current Frequency on which the Node formed the Network */
    ULONG                           CurrentOperFreq;
	/* The Last Operating Frequency on which the Node formed the Network earlier */
    ULONG                           LastOperFreq;
	/* Transmission Broadcast Rate */
    ULONG                           TxBcastRate;

	/* Flag Indicating that the Ingress/Egress Bandwidth reached the Maximum Threshold
		Set */
    BOOL                            MaxIngressBWThresholdReached;
    BOOL                            MaxEgressBWThresholdReached;

	/* Number of Nodes on the MoCA Network 
		- Cannot exceed the maximum supported by MoCA Protocol. */
    ULONG                           NumberOfConnectedClients;

	/* Network Coordinator MAC Address */
    CHAR                            NetworkCoordinatorMACAddress[18];
} moca_dynamic_info_t;

typedef struct {
	/* Number of Bytes Sent & Received */
    ULONG                           BytesSent;
    ULONG                           BytesReceived;

	/* Number of Packets Sent & Received */
    ULONG                           PacketsSent;
    ULONG                           PacketsReceived;

	/* Number of Errors in Sent & Received Packets */
    ULONG                           ErrorsSent;
    ULONG                           ErrorsReceived;

	/* Number of Unicast Packets Sent & Received */
    ULONG                           UnicastPacketsSent;
    ULONG                           UnicastPacketsReceived;

	/* Number of Packets Discard (Tx & Rx side) */
    ULONG                           DiscardPacketsSent;
    ULONG                           DiscardPacketsReceived;

	/* Number of Multicast Packets Sent & Received */
    ULONG                           MulticastPacketsSent;
    ULONG                           MulticastPacketsReceived;

	/* Number of Broadcast Packets Sent & Received */
    ULONG                           BroadcastPacketsSent;
    ULONG                           BroadcastPacketsReceived;

	/* Number of Unknown Protocol Packets Received */
    ULONG                           UnknownProtoPacketsReceived;

	/* Aggregate Averages of Packet Counts (Tx & Rx) */
    ULONG                           ExtAggrAverageTx;
    ULONG                           ExtAggrAverageRx;
} moca_stats_t;


typedef struct {
	/* Number of MAP packets */
    ULONG                           Map;
	/* Number of Reservation Request Packets */
    ULONG                           Rsrv;
	/* Number of Link Control Packets */
    ULONG                           Lc;
	/* Number of Admission Request Packets */
    ULONG                           Adm;
	/* Number of Probes */
    ULONG                           Probe;
	/* Number of Beacons */
    ULONG                           Async;
} moca_mac_counters_t;

typedef struct {
	/* Aggregate Tx Payload Data Units (Not MoCA Control Packets). */
    ULONG                           Tx;
	/* Aggregate Rx Payload Data Units (Not MoCA Control Packets). */
    ULONG                           Rx;
} moca_aggregate_counters_t;

typedef struct {
	/* MAC Address of the Node */
	CHAR							mac_addr[6];
} moca_cpe_t;

typedef struct {
	/* This Data Structure corresponds to information of 
		the associated device on the network. The term 
		'this Node' pertains to that particulard device for
		which the information in this data structure is 
		valid */ 

	/* MAC Address of the Associated Device */
    UCHAR                           MACAddress[18];
	/* Node ID of the Associated Device */
    ULONG                           NodeID;
	/* Whether this Node is a Preferred NC. */
    BOOL                            PreferredNC;
	/* Highest MoCA Protocol Version that this Node supports */
    CHAR                            HighestVersion[64];
	/* Tx PHY Rate of this Node */
    ULONG                           PHYTxRate;
	/* Rx PHY Rate of this Node */
    ULONG                           PHYRxRate;
	/* Tx Power Reduced by this Node */
    ULONG                           TxPowerControlReduction;
	/* Rx Power Level read by this Node */
    ULONG                           RxPowerLevel;
	/* Tx Broadcast PHY Rate */
    ULONG                           TxBcastRate;
	/* Rx Broadcast Power Level read by this Node */
    ULONG                           RxBcastPowerLevel;
	/* Number of Transmitted Packets from this Node */
    ULONG                           TxPackets;
	/* Number of Recieved Packets by this Node */
    ULONG                           RxPackets;
	/* Number of (Rx) Error or Missed Packets by this Node */
    ULONG                           RxErroredAndMissedPackets;
	/* Flag if this Node is capable of QAM-256 */
    BOOL                            QAM256Capable;
	/* Flag if this Node is capable of Packet Aggregation */
    BOOL                           PacketAggregationCapability;
	/* Receive Signal to Noise Ration */
    ULONG                           RxSNR;
	/* Flag if this Node is Active */
    BOOL                            Active;
	/* Recevie Broadcast PHY Rate */
    ULONG                           RxBcastRate;
	/* Number of Clients connected to this Node */
    ULONG                           NumberOfClients;
} moca_associated_device_t;

typedef struct {
    /* This data structure represents teh MoCA mesh PHY rate table.
       This table contains the unicast transmit PHY rate between all
       pair of nodes in the MoCA Network.*/
    
    /* The node ID of the receive MoCA node is used as one of the
    index to order the mesh PHY rate table.*/ 
    ULONG                           RxNodeID;

    /* The node ID of the transmit MoCA node is used as one of the
    index to order the mesh PHY rate table.*/
    ULONG                           TxNodeID;

    /*Indicate the transmit PHY rate in Mbps from the MoCA node
    identified by 'mocaMeshTxNodeIndex' to the MoCA node identified
    by 'mocaMeshRxNodeIndex'.*/
    ULONG                           TxRate;

} moca_mesh_table_t;

typedef struct {
    /* This Data Structure respresents the MoCA interface flow statistics
       table.  This table provides statistics of ingress PQoS flow in the
       MoCA interface.*/ 

    /* Indicate the flow ID of a PQoS flow. */
    ULONG                           FlowID;
    /* Indicate the flow ID of a Ingress PQoS flow. */
    ULONG                           IngressNodeID;
    /* Indicate the flow ID of a Egress PQoS flow. */
    ULONG                           EgressNodeID;
    /* Indicate the LEASE_TIME_LEFT of the PQoS flow identified by
    'mocaIfFlowID' in which this MoCA interface is an ingress node
    for this PQoS flow.*/
    ULONG                           FlowTimeLeft;
    /* Indicate the Destination Address (DA) of Ethernet packets of
    the PQoS Flow for which this node is the ingress node */
    char                            DestinationMACAddress[18];
    /* Indicate the number of MoCA aggregation MoCA frames.*/
    ULONG                           PacketSize;
    /* Indicate the T_PEAK_DATA_RATE of the PQoS flow identified by
    'mocaIfFlowID' in which this MoCA interface is an ingress node
    for the PQoS flow.*/
    ULONG                           PeakDataRate;
    /* Indicate the T_BURST_SIZE of the PQoS flow identified by
    'mocaIfFlowID' in which this MoCA interface is an ingress node
    for this PQoS flow.*/
    ULONG                           BurstSize;
    /* Indicate the FLOW_TAG of the PQoS flow identified by
    'mocaIfFlowID' in which this MoCA interface is an ingress node
    for this PQoS flow. The FLOW_TAG carries application specific
    content of this PQoS flow.*/
    ULONG                           FlowTag;
    /* Indicate the T_LEASE_TIME of the PQoS flow identified by
    'mocaIfFlowID' in which this MoCA interface is an ingress node
    for this PQoS flow.*/
    ULONG                           LeaseTime;
} moca_flow_table_t;

/**********************************************************************************
 *
 *  MoCA Subsystem level function prototypes 
 *
**********************************************************************************/
/* moca_GetIfConfig() function */
/**
* Description: Gets the MoCA Configuration Parameters that were previously set.
* Parameters : 
*    ifIndex - Index of the MoCA Interface.
*    pmoca_config - Configuration Parameters
*		* Instance Number when Multiple MoCA interfaces exist.
*		*	0 - In the case of only one interface.
*		* Get the Alias Name for the interface
*		* Flag if the interface is Enabled.
*		* Flag if the Local Node's preference to be Network Coordinator
*		* Flag if Privacy is Enabled
*		* Current Frequency Mask (bitmask)
*		* Privacy password (Valid if Privacy is Enabled)
*		* Maximum Tx Power Limit
*		* AutoPowerControlPhyRate: PowerCtrlPhyTarget
*		*  	Used as a reference to achieve the PHY rate by adjusting power.
*		* Tx Power Limit for transmitting beacons
*		* Maximum Ingress/Egress Bandwidth Thresholds
*		* Reset Condition of the MoCA Node
*		* Flag if the Node is configured to operate in mixed mode (both 1.0 & 1.1 versions).
*		* Flag if the Node is Scanning
*		* Flag if the Auto Power Control is Enabled
*		* Node Taboo Mask (indicates what frequencies Node should avoid)
*		* Channel Scan Mask (indicated what frequencies Node should scan for beacons)
* 
* @return The status of the operation.
* @retval STATUS_SUCCESS if successful.
* @retval STATUS_FAILURE if any error is detected 
* 
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system 
* calls. It should probably just send a message to a driver event handler task. 
*
*/
INT moca_GetIfConfig(ULONG ifIndex, moca_cfg_t *pmoca_config);

/* moca_SetIfConfig() function */
/**
* Description: Sets the MoCA Configuration Parameters.
* Parameters : 
*    ifIndex - Index of the MoCA Interface.
*    pmoca_config - Configuration Parameters
*		* Instance Number when Multiple MoCA interfaces exist.
*		*	0 - In the case of only one interface.
*		* Set the Alias Name for the interface
*		* Enable/Disable the interface.
*		* Enable/Disable the Node's preference to be Network Coordinator
*		* Enable/Disable Privacy
*		* Set of Frequencies that can be used for forming network (bitmask)
*		* Privacy password (Valid if Privacy is Enabled)
*		* Maximum Tx Power Limit
*		* AutoPowerControlPhyRate: PowerCtrlPhyTarget
*		*  	Used as a reference to achieve the PHY rate by adjusting power.
*		* Tx Power Limit for transmitting beacons
*		* Maximum Ingress/Egress Bandwidth Thresholds
*		* Reset MoCA Node
*		* Enable/Disable the Node to operate in mixed mode (both 1.0 & 1.1 versions).
*		* Enable/Disable the Node to operate in single frequency mode or scanning mode.
*		* Enable/Disable Auto Power Control.
*		* Set of Frequencis to Avoid (bitmask)
*		* Set of Frequencies to Scan for Beacons (bitmask)
* 
* @return The status of the operation.
* @retval STATUS_SUCCESS if successful.
* @retval STATUS_FAILURE if any error is detected 
* 
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system 
* calls. It should probably just send a message to a driver event handler task. 
*
*/
INT moca_SetIfConfig(ULONG ifIndex, moca_cfg_t *pmoca_config);

/* moca_IfGetDynamicInfo() function */
/**
* Description: Gets the Dynamic Status information on the interface & its 
*				associated network.
* Parameters: 
*	ifIndex - Index of the MoCA Interface.
* 	pmoca_dynamic_info_t - 
*		Dynamic Information on the interface and its associated network.
*		The Following information is expected.
* 		* Status of the Local Interface Inferface (Up/Down/ etc.)
*		* Last Link Status Change (Up/Down/ etc.)
*		* Maximum Ingress/Egress Bandwidth
*		* Current Version of the MoCA Protocol
*		* Node ID of the Network Coordinator
*		* Local Interface Node ID
*		* Node ID of the Backup Network Coordinator
*		* If Privacy is enabled on the network
*		* Current Frequency Mask
*		* Current Operating Frequency
*		* Last Operating Frequency
*		* Tx Broadcast Rate
*		* Flag if MaxIngress/MaxEgress Bandwidth Threshold Reached
*		* Number of Client Devices Connected
*		* Network Coordinator MAC Address
* 
* @return The status of the operation.
* @retval STATUS_SUCCESS if successful.
* @retval STATUS_FAILURE if any error is detected 
* 
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system 
* calls. It should probably just send a message to a driver event handler task. 
*
*/
INT moca_IfGetDynamicInfo(ULONG ifIndex, moca_dynamic_info_t *pmoca_dynamic_info);

/* moca_IfGetStaticInfo() function */
/**
* Description: Gets the Static Information from the Local Node
* Parameters : 
*    ifIndex - Index of the MoCA Interface.
*    pmoca_static_info - Static Information of the interface
*		* Interface Name (for example: moca0)
*		* MAC Address of the Interface
*		* Firmware Version of the MoCA Firmware
*		* Maximum PHY rate in Mbps
*		* Highest Version of MoCA Protocol that the Node Supports
*		* Frequencies that Node can Operate on (Bit Mask)
*		* Frequenies to Avoid on Network (Bit Mask)
*		* Beacon Backoff in dB
*		* Flag if Node is Capable of QAM-256.
*		* Flag that indicates if Node is capable of Packet Aggregation.
* 
* @return The status of the operation.
* @retval STATUS_SUCCESS if successful.
* @retval STATUS_FAILURE if any error is detected 
* 
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system 
* calls. It should probably just send a message to a driver event handler task. 
*
*/
INT moca_IfGetStaticInfo(ULONG ifIndex, moca_static_info_t *pmoca_static_info);

/* moca_IfGetStats() function */
/**
* Description: Gets the Statistics on the Interface at Network Layer
* Parameters : 
*    ifIndex - Index of the MoCA Interface.
*    pmoca_stats - Statistics on the interface (Network layer)
*		* Number of Bytes Sent & Received
*		* Number of Packets Sent & Received
*		* Number of Errors in Sent & Received Packets
*		* Number of Unicast Packets Sent & Received
*		* Number of Packets Discard (Tx & Rx side)
*		* Number of Multicast Packets Sent & Received
*		* Number of Broadcast Packets Sent & Received
*		* Number of Unknown Protocol Packets Received
*		* Aggregate Averages of Packet Counts (Tx & Rx)
* 
* @return The status of the operation.
* @retval STATUS_SUCCESS if successful.
* @retval STATUS_FAILURE if any error is detected 
* 
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system 
* calls. It should probably just send a message to a driver event handler task. 
*
*/
INT moca_IfGetStats(ULONG ifIndex, moca_stats_t *pmoca_stats);

/* moca_GetNumAssociatedDevices() function */
/**
* Description: Gets the Number of Nodes on the MoCA network.
* Parameters : 
*    ifIndex - Index of the MoCA Interface.
*    pulCount - Number of Nodes on the network.
* 
* @return The status of the operation.
* @retval STATUS_SUCCESS if successful.
* @retval STATUS_FAILURE if any error is detected 
* 
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system 
* calls. It should probably just send a message to a driver event handler task. 
*
*/
INT moca_GetNumAssociatedDevices(ULONG ifIndex, ULONG *pulCount);

/* moca_IfGetExtCounter() function */
/**
* Description: Gets the Statistics on the Interface at MoCA MAC Layer.
* Parameters : 
*    ifIndex - Index of the MoCA Interface.
*    pmoca_mac_counters - MoCA MAC Layer Statiscs
*		* Number of MAP packets
*		* Number of Reservation Request Packets
*		* Number of Link Control Packets
*		* Number of Admission Request Packets
*		* Number of Probes
*		* Number of Beacons
*	** Please Note that this API is valid only if the Node is 
*		Network Coordinator.
* 
* @return The status of the operation.
* @retval STATUS_SUCCESS if successful.
* @retval STATUS_FAILURE if any error is detected 
* 
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system 
* calls. It should probably just send a message to a driver event handler task. 
*
*/
INT moca_IfGetExtCounter(ULONG ifIndex, moca_mac_counters_t *pmoca_mac_counters);

/* moca_IfGetExtAggrCounter() function */
/**
* Description: Gets the Aggregate DATA units Transferred (Tx & Rx)
* Parameters : 
*    ifIndex - Index of the MoCA Interface.
*    pmoca_aggregate_counts - Aggregate Tx/Rx Counters
*		* Aggregate Tx Payload Data Units (Not MoCA Control Packets).
*		* Aggregate Rx Payload Data Units (Not MoCA Control Packets).
*
* @return The status of the operation.
* @retval STATUS_SUCCESS if successful.
* @retval STATUS_FAILURE if any error is detected 
* 
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system 
* calls. It should probably just send a message to a driver event handler task. 
*
*/
INT moca_IfGetExtAggrCounter(ULONG ifIndex, moca_aggregate_counters_t *pmoca_aggregate_counts);

/* moca_GetMocaCPEs() function */
/**
* Description: Get MAC Address of all the Nodes Connected on MoCA Network.
* Parameters : 
*    ifIndex - Index of the MoCA Interface.
*    pmoca_cpes - List of MAC Addresses of MoCA Nodes.
*	 pnum_cpes - Number of MoCA Nodes in the List.
*
* @return The status of the operation.
* @retval STATUS_SUCCESS if successful.
* @retval STATUS_FAILURE if any error is detected 
* 
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system 
* calls. It should probably just send a message to a driver event handler task. 
*
*/
INT moca_GetMocaCPEs(ULONG ifIndex, moca_cpe_t *cpes, INT *pnum_cpes);

/* moca_GetAssociatedDevices() function */
/**
* Description: Get Information on all the associated Devices on the network.
* Parameters : 
*    ifIndex - Index of the MoCA Interface.
*    ppdevice_array - Array of set of information for each Node on the network.
*		* MAC Address of the Associated Device 
*		* Node ID of the Associated Device
*		* Whether this Node is a Preferred NC.
*		* Highest MoCA Protocol Version that this Node supports
*		* Tx PHY Rate of this Node
*		* Rx PHY Rate of this Node
*		* Tx Power Reduced by this Node
*		* Rx Power Level read by this Node
*		* Tx Broadcast PHY Rate
*		* Rx Broadcast Power Level read by this Node
*		* Number of Transmitted Packets from this Node
*		* Number of Recieved Packets by this Node
*		* Number of (Rx) Error or Missed Packets by this Node
*		* Flag if this Node is capable of QAM-256
*		* Flag if this Node is capable of Packet Aggregation
*		* Receive Signal to Noise Ration
*		* Flag if this Node is Active
*		* Recevie Broadcast PHY Rate
*		* Number of Clients connected to this Node
*
* @return The status of the operation.
* @retval STATUS_SUCCESS if successful.
* @retval STATUS_FAILURE if any error is detected 
* 
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system 
* calls. It should probably just send a message to a driver event handler task. 
*
*/
INT moca_GetAssociatedDevices(ULONG ifIndex, moca_associated_device_t **ppdevice_array);


/* moca_FreqMaskToValue() function */
/**
* Description: A utility function that converts Mask Value to Frequency Number.
* Parameters : 
*    mask - Bit Mask of the Frequency.
*
* @return Frequency Value for the given Mask.
* 
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system 
* calls. It should probably just send a message to a driver event handler task. 
*
*/
//INT moca_FreqMaskToValue(UINT mask);
INT moca_FreqMaskToValue(UCHAR *mask);

/* moca_HardwareEquipped() function */
/**
* Description: Functio that returns whether the MoCA Hardware is Equipped or Not.
* Parameters : None.
*
* @return Flag Indicating whether the Hardware is Equipped or not.
* @retval TRUE if Hardware is present.
* @retval FALSE if Hardware is not present.
* 
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system 
* calls. It should probably just send a message to a driver event handler task. 
*
*/
BOOL moca_HardwareEquipped(void);

/* moca_IfGetMeshTable() function */
/**
* Description: Gets the MoCA Mesh Table.
* Parameters : 
*    ifIndex - Index of the MoCA Interface.
*    moca_mesh_table_t - pointer to a mesh table entry
*    pulCount - number of entries in the table
* @return The status of the operation.
* @retval STATUS_SUCCESS if successful.
* @retval STATUS_FAILURE if any error is detected 
* 
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system 
* calls. It should probably just send a message to a driver event handler task. 
*
*/
INT moca_GetFullMeshRates(ULONG ifIndex, moca_mesh_table_t *pDeviceArray, ULONG *pulCount);

/* moca_GetFlowStatistics() function */
/**
* Description: Gets the MoCA Flow Table.
* Parameters : 
*    ifIndex - Index of the MoCA Interface.
*    moca_flow_table_t - pointer to a flow table entry
*    pulCount - number of entries in the table
* @return The status of the operation.
* @retval STATUS_SUCCESS if successful.
* @retval STATUS_FAILURE if any error is detected 
* 
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system 
* calls. It should probably just send a message to a driver event handler task. 
*
*/
INT moca_GetFlowStatistics(ULONG ifIndex, moca_flow_table_t *pDeviceArray, ULONG *pulCount);

/* moca_GetResetCount() function */
/**
* Description: Gets the MoCA reset count.
*    resetcnt - number of reset 
* @return The status of the operation.
* @retval STATUS_SUCCESS if successful.
* @retval STATUS_FAILURE if any error is detected 
* 
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system 
* calls. It should probably just send a message to a driver event handler task. 
*
*/

INT moca_GetResetCount(ULONG *resetcnt);

#endif
 
