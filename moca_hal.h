/*
 * If not stated otherwise in this file or this component's Licenses.txt file the
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

#ifndef STATUS_NOT_AVAILABLE
#define STATUS_NOT_AVAILABLE     -2
#endif


#define kMoca_MaxCpeList		256
#define kMoca_MaxMocaNodes              16
#define MAC_PADDING			12 /* RDKB expects 6 byte MAC, padding required for platforms handling as 18 bytes MAC*/
/**********************************************************************
                ENUMERATION DEFINITIONS
**********************************************************************/
#ifndef MOCA_VAR
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
#endif

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
    UCHAR                           MacAddress[6 + MAC_PADDING];
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

#ifndef MOCA_VAR
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
	/*Indicate  the length of time this node has been connected
	to the MoCA network with at least one other node*/
    ULONG 							LinkUpTime;


} moca_dynamic_info_t;
#endif

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
    UCHAR                           MACAddress[6 + MAC_PADDING];
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
    INT                             RxPowerLevel;
	/* Tx Broadcast PHY Rate */
    ULONG                           TxBcastRate;
	/* Rx Broadcast Power Level read by this Node */
    INT                               RxBcastPowerLevel;
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

#ifndef MOCA_VAR
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
#endif

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

typedef INT ( * moca_associatedDevice_callback)(ULONG ifIndex, moca_associated_device_t *moca_dev); //This call back will be invoked when new MoCA client is Actived or Inactived.moca_associated_device_t.Active is used to indicate activation/inactivation

typedef struct moca_assoc_pnc_info {
	/* The index of this node */
    ULONG   mocaNodeIndex;
	/* Whether this Node is a Preferred NC. */
    BOOL        mocaNodePreferredNC;
	/* The MoCA version of this node */
    ULONG    mocaNodeMocaversion;
}moca_assoc_pnc_info_t;

void moca_associatedDevice_callback_register(moca_associatedDevice_callback callback_proc); //Callback registration function.

/**********************************************************************************
 *
 *  MoCA Subsystem level function prototypes 
 *
**********************************************************************************/
/* moca_GetIfConfig() function */
/**
* @description Gets the MoCA Configuration Parameters that were previously set.
* @param ifIndex - Index of the MoCA Interface.
* @param pmoca_config - Configuration Parameters
*		\n\n Instance Number when Multiple MoCA interfaces exist.
*		\n 0 - In the case of only one interface.
*		\n Get the Alias Name for the interface
*		\n Flag if the interface is Enabled.
*		\n Flag if the Local Node's preference to be Network Coordinator
*		\n Flag if Privacy is Enabled
*		\n Current Frequency Mask (bitmask)
*		\n Privacy password (Valid if Privacy is Enabled)
*		\n Maximum Tx Power Limit
*		\n AutoPowerControlPhyRate: PowerCtrlPhyTarget
*		\n Used as a reference to achieve the PHY rate by adjusting power.
*		\n Tx Power Limit for transmitting beacons
*		\n Maximum Ingress/Egress Bandwidth Thresholds
*		\n Reset Condition of the MoCA Node
*		\n Flag if the Node is configured to operate in mixed mode (both 1.0 & 1.1 versions).
*		\n Flag if the Node is Scanning
*		\n Flag if the Auto Power Control is Enabled
*		\n Node Taboo Mask (indicates what frequencies Node should avoid)
*		\n Channel Scan Mask (indicated what frequencies Node should scan for beacons)
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
* @description Sets the MoCA Configuration Parameters.
* @param ifIndex - Index of the MoCA Interface.
* @param pmoca_config - Configuration Parameters
*		\n\n Instance Number when Multiple MoCA interfaces exist.
*		\n 0 - In the case of only one interface.
*		\n Set the Alias Name for the interface
*		\n Enable/Disable the interface.
*		\n Enable/Disable the Node's preference to be Network Coordinator
*		\n Enable/Disable Privacy
*		\n Set of Frequencies that can be used for forming network (bitmask)
*		\n Privacy password (Valid if Privacy is Enabled)
*		\n Maximum Tx Power Limit
*		\n AutoPowerControlPhyRate: PowerCtrlPhyTarget
*		\n Used as a reference to achieve the PHY rate by adjusting power.
*		\n Tx Power Limit for transmitting beacons
*		\n Maximum Ingress/Egress Bandwidth Thresholds
*		\n Reset MoCA Node
*		\n Enable/Disable the Node to operate in mixed mode (both 1.0 & 1.1 versions).
*		\n Enable/Disable the Node to operate in single frequency mode or scanning mode.
*		\n Enable/Disable Auto Power Control.
*		\n Set of Frequencis to Avoid (bitmask)
*		\n Set of Frequencies to Scan for Beacons (bitmask)
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
* @description Gets the Dynamic Status information on the interface & its 
*				associated network.
* @param ifIndex - Index of the MoCA Interface.
* @param pmoca_dynamic_info_t - 
*		Dynamic Information on the interface and its associated network.
*		The Following information is expected.
* 		\n Status of the Local Interface Inferface (Up/Down/ etc.)
*		\n Last Link Status Change (Up/Down/ etc.)
*		\n Maximum Ingress/Egress Bandwidth
*		\n Current Version of the MoCA Protocol
*		\n Node ID of the Network Coordinator
*		\n Local Interface Node ID
*		\n Node ID of the Backup Network Coordinator
*		\n If Privacy is enabled on the network
*		\n Current Frequency Mask
*		\n Current Operating Frequency
*		\n Last Operating Frequency
*		\n Tx Broadcast Rate
*		\n Flag if MaxIngress/MaxEgress Bandwidth Threshold Reached
*		\n Number of Client Devices Connected
*		\n Network Coordinator MAC Address
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
* @description Gets the Static Information from the Local Node
* @param ifIndex - Index of the MoCA Interface.
* @param pmoca_static_info - Static Information of the interface
*		\n Interface Name (for example: moca0)
*		\n MAC Address of the Interface
*		\n Firmware Version of the MoCA Firmware
*		\n Maximum PHY rate in Mbps
*		\n Highest Version of MoCA Protocol that the Node Supports
*		\n Frequencies that Node can Operate on (Bit Mask)
*		\n Frequenies to Avoid on Network (Bit Mask)
*		\n Beacon Backoff in dB
*		\n Flag if Node is Capable of QAM-256.
*		\n Flag that indicates if Node is capable of Packet Aggregation.
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
* @description Gets the Statistics on the Interface at Network Layer
* @param ifIndex - Index of the MoCA Interface.
* @param pmoca_stats - Statistics on the interface (Network layer)
*		\n\n Number of Bytes Sent & Received
*		\n Number of Packets Sent & Received
*		\n Number of Errors in Sent & Received Packets
*		\n Number of Unicast Packets Sent & Received
*		\n Number of Packets Discard (Tx & Rx side)
*		\n Number of Multicast Packets Sent & Received
*		\n Number of Broadcast Packets Sent & Received
*		\n Number of Unknown Protocol Packets Received
*		\n Aggregate Averages of Packet Counts (Tx & Rx)
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
* @description Gets the Number of Nodes on the MoCA network.
* @param ifIndex - Index of the MoCA Interface.
* @param pulCount - Number of Nodes on the network.
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
* @description Gets the Statistics on the Interface at MoCA MAC Layer.
* @param ifIndex - Index of the MoCA Interface.
* @param pmoca_mac_counters - MoCA MAC Layer Statiscs
*		\n\n Number of MAP packets
*		\n Number of Reservation Request Packets
*		\n Number of Link Control Packets
*		\n Number of Admission Request Packets
*		\n Number of Probes
*		\n Number of Beacons
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
* @description Gets the Aggregate DATA units Transferred (Tx & Rx)
* @param ifIndex - Index of the MoCA Interface.
* @param pmoca_aggregate_counts - Aggregate Tx/Rx Counters
*		\n\n Aggregate Tx Payload Data Units (Not MoCA Control Packets).
*		\n Aggregate Rx Payload Data Units (Not MoCA Control Packets).
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
* @description Get MAC Address of all the Nodes Connected on MoCA Network.
* @param ifIndex - Index of the MoCA Interface.
* @param pmoca_cpes - List of MAC Addresses of MoCA Nodes.
* @param pnum_cpes - Number of MoCA Nodes in the List.
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
* @description Get Information on all the associated Devices on the network.
* @param ifIndex - Index of the MoCA Interface.
* @param ppdevice_array - Array of set of information for each Node on the network.
*		\n\n MAC Address of the Associated Device 
*		\n Node ID of the Associated Device
*		\n Whether this Node is a Preferred NC.
*		\n Highest MoCA Protocol Version that this Node supports
*		\n Tx PHY Rate of this Node
*		\n Rx PHY Rate of this Node
*		\n Tx Power Reduced by this Node
*		\n Rx Power Level read by this Node
*		\n Tx Broadcast PHY Rate
*		\n Rx Broadcast Power Level read by this Node
*		\n Number of Transmitted Packets from this Node
*		\n Number of Recieved Packets by this Node
*		\n Number of (Rx) Error or Missed Packets by this Node
*		\n Flag if this Node is capable of QAM-256
*		\n Flag if this Node is capable of Packet Aggregation
*		\n Receive Signal to Noise Ration
*		\n Flag if this Node is Active
*		\n Recevie Broadcast PHY Rate
*		\n Number of Clients connected to this Node
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
* @description A utility function that converts Mask Value to Frequency Number.
* @param mask - Bit Mask of the Frequency.
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
* @description Functio that returns whether the MoCA Hardware is Equipped or Not.
* @param None.
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
* @description Gets the MoCA Mesh Table.
* @param ifIndex - Index of the MoCA Interface.
* @param moca_mesh_table_t - pointer to a mesh table entry
* @param pulCount - number of entries in the table
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
#ifndef MOCA_VAR
INT moca_GetFullMeshRates(ULONG ifIndex, moca_mesh_table_t *pDeviceArray, ULONG *pulCount);
#endif

/* moca_GetFlowStatistics() function */
/**
* @description Gets the MoCA Flow Table.
* @param ifIndex - Index of the MoCA Interface.
* @param moca_flow_table_t - pointer to a flow table entry
* @param pulCount - number of entries in the table
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
* @description Gets the MoCA reset count.
* @param resetcnt - number of reset 
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
 
