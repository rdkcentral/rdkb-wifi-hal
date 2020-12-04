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

    description:

        This header file gives the function call prototypes and 
        structure definitions used for the RDK-Broadband 
        MoCA hardware abstraction layer
        
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

/**
* @defgroup MOCA_HAL MoCA HAL
*
* MoCA HAL is an abstraction layer, mainly for interacting with MoCA driver.
*
* @defgroup MOCA_HAL_TYPES  MOCA HAL Data Types
* @ingroup  MOCA_HAL
*
* @defgroup MOCA_HAL_APIS   MOCA HAL  APIs
* @ingroup  MOCA_HAL
*
**/

/**
 * @addtogroup MOCA_HAL_TYPES
 * @{
 */

#define kMoca_MaxCpeList		256
#define kMoca_MaxMocaNodes              16
#define MAC_PADDING			12 /**< RDKB expects 6 byte MAC, padding required for platforms handling as 18 bytes MAC */

#define STATUS_INPROGRESS   -1 /**< If ACA process already running */
#define STATUS_NO_NODE      -2 /**< If specified NODE not exist */
#define STATUS_INVALID_PROBE    -3 /**< If HAL API called with invalid probe TYPE */
#define STATUS_INVALID_CHAN     -4 /**< If HAL API called with invalid channel */

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

typedef enum
{
    PROBE_QUITE = 0,
    PROBE_EVM
}PROBE_TYPE;

#if 0
typedef enum
{
    STAT_SUCCESS =0,
    STAT_FAIL_BADCHANNEL,
    STAT_FAIL_NOEVMPROBE,
    STAT_FAIL,
    STAT_INPROGRESS
}ACA_STATUS;
#endif
/**********************************************************************
                STRUCTURE DEFINITIONS
**********************************************************************/
typedef struct {
    ULONG                           InstanceNumber; /**< Instance Number when Multiple MoCA interfaces exist. 0 - In the case of only one interface. */
    CHAR                            Alias[64]; /**< Set the Alias Name for the interface */
    BOOL                         	bEnabled; /**< Enable/Disable the interface. */
    BOOL                         	bPreferredNC; /**< Enable/Disable the Node's preference to be Network Coordinator */
    BOOL                         	PrivacyEnabledSetting; /**< Enable/Disable Link Privacy. A Password is required when Privacy is enabled */
    UCHAR                           FreqCurrentMaskSetting[128]; /**< Set of Frequencies that should be used for forming network (bitmask) */
    CHAR                            KeyPassphrase[18]; /**< Privacy Password. This field is valid only if the Link Privacy is enabled. */
    INT                             TxPowerLimit; /**< Maximum Transmission Power allowed */
    ULONG                           AutoPowerControlPhyRate; /**< AutoPowerControlPhyRate: PowerCtrlPhyTarget Used as a reference to achieve the PHY rate by adjusting  power. */
    ULONG                           BeaconPowerLimit; /**< Maximum Transmission Power Allowed when transmitting Beacons */
    ULONG                           MaxIngressBWThreshold; /**< Maximum Ingress Bandwidth Thresholds */
    ULONG                           MaxEgressBWThreshold; /**< Maximum Egress Bandwidth Thresholds */
    BOOL                            Reset; /**< Reset MoCA Configuration Parameters to Defaults */
    BOOL                            MixedMode; /**< Enable/Disable the Node to operate in mixed mode (1.0/1.1/2.0 versions).
                i.e Enable backward compatibility on the MoCA Protocol Versions. */
    BOOL                            ChannelScanning; /**< Enable/Disable the Node to operate in single frequency mode or scanning mode. */
    BOOL                            AutoPowerControlEnable; /**< Enable/Disable adjusting Power to achieve the Target PHY rate */
    BOOL                            EnableTabooBit; /**< Enable/Disable the Node to support Taboo Mask */
    UCHAR                           NodeTabooMask[128]; /**< Set of Frequencis to Avoid (bitmask) */
    UCHAR                           ChannelScanMask[128]; /**< Set of Frequencies to Scan for Beacons to form network (bitmask).
                Very often, this is same as FreqCurrentMaskSetting. */
} moca_cfg_t;

typedef struct {
	/**< Interface Name (for example: moca0) */
    CHAR                            Name[64];           /**< Uniquely identifying the entry */
    UCHAR                           MacAddress[6 + MAC_PADDING]; /**< MAC Address of the Local Node */
    CHAR                            FirmwareVersion[64]; /**< Firmware Version of the MoCA Firmware */
    ULONG                           MaxBitRate; /**< Maximum PHY Rate that the Node can support */
    CHAR                            HighestVersion[64]; /**< Highest Version of the MoCA Protocol that the Local Node Supports */
    UCHAR                           FreqCapabilityMask[8]; /**< Frequencies that the Local Node supports (bitmask) */
    UCHAR                           NetworkTabooMask[128]; /**< Frequencies that the Local Node does not support (bitmask) */
    ULONG                           TxBcastPowerReduction; /**< Beacon Backoff in dB */
    BOOL                            QAM256Capable; /**< Local Node is QAM-256 Capable or Not */
    BOOL                           PacketAggregationCapability; /**< Local Node can aggregate Ethernet Packets for MoCA PDU transfers */
} moca_static_info_t;

#ifndef MOCA_VAR
typedef struct {
	/**< Current Status of the LoCAL Interface (Up/Down etc.) */
    moca_if_status_t                Status;
    ULONG                           LastChange; /**< Last Link Status Change (Up/Down/ etc.) */
    ULONG                           MaxIngressBW; /**< Maximum Ingress Bandwidth reached */
    ULONG                           MaxEgressBW; /**< Maximum Egress Bandwidth reached */
    CHAR                            CurrentVersion[64]; /**< Current Operating MoCA Protocol Version Valid Values: 1.0, 1.1, 2.0 */
    ULONG                           NetworkCoordinator; /**< Node ID of the Network Coordinator.
                Valid Values: 0-7 (Protocol: 1.0)
                Valid Values: 0-15 (Protocol: 1.1, 2.0) */
    ULONG                           NodeID; /**< Node ID of the Local Node.
                Valid Values: 0-7 (Protocol: 1.0)
                Valid Values: 0-15 (Protocol: 1.1, 2.0) */
    ULONG                           BackupNC; /**< Node ID of the Backup Network Coordinator
                Valid Values: 0-7 (Protocol: 1.0)
                Valid Values: 0-15 (Protocol: 1.1, 2.0) */
    BOOL                            PrivacyEnabled; /**< If Privacy is enabled on the network */
    UCHAR                           FreqCurrentMask[8]; /**< This should be same as the Configured Frequencies that the Node can operate */
    ULONG                           CurrentOperFreq; /**< The Current Frequency on which the Node formed the Network */
    ULONG                           LastOperFreq; /**< The Last Operating Frequency on which the Node formed the Network earlier */
    ULONG                           TxBcastRate; /**< Transmission Broadcast Rate */
    BOOL                            MaxIngressBWThresholdReached; /**< Flag Indicating that the Ingress Bandwidth reached the Maximum Threshold Set */
    BOOL                            MaxEgressBWThresholdReached; /**< Flag Indicating that the Egress Bandwidth reached the Maximum Threshold Set */
    ULONG                           NumberOfConnectedClients; /**< Number of Nodes on the MoCA Network
                - Cannot exceed the maximum supported by MoCA Protocol. */
    CHAR                            NetworkCoordinatorMACAddress[18]; /**< Network Coordinator MAC Address */
    ULONG			    LinkUpTime; /**< Indicate  the length of time this node has been connected to the MoCA network with at least one other node */


} moca_dynamic_info_t;
#endif

typedef struct {
    ULONG                           BytesSent; /**< Number of Bytes Sent & Received */
    ULONG                           BytesReceived; /**< Number of Bytes Sent & Received */

    ULONG                           PacketsSent; /**< Number of Packets Sent & Received */
    ULONG                           PacketsReceived; /**< Number of Packets Sent & Received */

    ULONG                           ErrorsSent; /**< Number of Errors in Sent & Received Packets */
    ULONG                           ErrorsReceived; /**< Number of Errors in Sent & Received Packets */

    ULONG                           UnicastPacketsSent; /**< Number of Unicast Packets Sent */
    ULONG                           UnicastPacketsReceived; /**< Number of Unicast Packets Received */

    ULONG                           DiscardPacketsSent; /**< Number of Packets Discard (Tx side) */
    ULONG                           DiscardPacketsReceived; /**< Number of Packets Discard (Rx side) */

    ULONG                           MulticastPacketsSent; /**< Number of Multicast Packets Sent */
    ULONG                           MulticastPacketsReceived; /**< Number of Multicast Packets Received */

    ULONG                           BroadcastPacketsSent; /**< Number of Broadcast Packets Sent */
    ULONG                           BroadcastPacketsReceived; /**< Number of Broadcast Packets Received */

    ULONG                           UnknownProtoPacketsReceived; /**< Number of Unknown Protocol Packets Received */

    ULONG                           ExtAggrAverageTx; /**< Aggregate Averages of Packet Counts (Tx) */
    ULONG                           ExtAggrAverageRx; /**< Aggregate Averages of Packet Counts (Rx) */
} moca_stats_t;


typedef struct {
    ULONG                           Map; /**< Number of MAP packets */
    ULONG                           Rsrv; /**< Number of Reservation Request Packets */
    ULONG                           Lc; /**< Number of Link Control Packets */
    ULONG                           Adm; /**< Number of Admission Request Packets */
    ULONG                           Probe; /**< Number of Probes */
    ULONG                           Async; /**< Number of Beacons */
} moca_mac_counters_t;

typedef struct {
    ULONG                           Tx; /**< Aggregate Tx Payload Data Units (Not MoCA Control Packets). */
    ULONG                           Rx; /**< Aggregate Rx Payload Data Units (Not MoCA Control Packets). */
} moca_aggregate_counters_t;

typedef struct {
	CHAR							mac_addr[6]; /**< MAC Address of the Node */
} moca_cpe_t;

typedef struct {
	/**< This Data Structure corresponds to information of 
		the associated device on the network. The term 
		'this Node' pertains to that particulard device for
		which the information in this data structure is 
		valid */ 

    UCHAR                           MACAddress[6 + MAC_PADDING]; /**< MAC Address of the Associated Device */
    ULONG                           NodeID; /**< Node ID of the Associated Device */
    BOOL                            PreferredNC; /**< Whether this Node is a Preferred NC. */
    CHAR                            HighestVersion[64]; /**< Highest MoCA Protocol Version that this Node supports */
    ULONG                           PHYTxRate; /**< Tx PHY Rate of this Node */
    ULONG                           PHYRxRate; /**< Rx PHY Rate of this Node */
    ULONG                           TxPowerControlReduction; /**< Tx Power Reduced by this Node */
    INT                             RxPowerLevel; /**< Rx Power Level read by this Node */
    ULONG                           TxBcastRate; /**< Tx Broadcast PHY Rate */
    INT                               RxBcastPowerLevel; /**< Rx Broadcast Power Level read by this Node */
    ULONG                           TxPackets; /**< Number of Transmitted Packets from this Node */
    ULONG                           RxPackets; /**< Number of Recieved Packets by this Node */
    ULONG                           RxErroredAndMissedPackets; /**< Number of (Rx) Error or Missed Packets by this Node */
    BOOL                            QAM256Capable; /**< Flag if this Node is capable of QAM-256 */
    BOOL                           PacketAggregationCapability; /**< Flag if this Node is capable of Packet Aggregation */
    ULONG                           RxSNR; /**< Receive Signal to Noise Ration */
    BOOL                            Active; /**< Flag if this Node is Active */
    ULONG                           RxBcastRate; /**< Recevie Broadcast PHY Rate */
    ULONG                           NumberOfClients; /**< Number of Clients connected to this Node */
} moca_associated_device_t;

#ifndef MOCA_VAR
typedef struct {
    /**< This data structure represents teh MoCA mesh PHY rate table.
       This table contains the unicast transmit PHY rate between all
       pair of nodes in the MoCA Network.*/
    
    ULONG                           RxNodeID; /**< The node ID of the receive MoCA node is used as one of the
    index to order the mesh PHY rate table. */

    ULONG                           TxNodeID; /**< The node ID of the transmit MoCA node is used as one of the
    index to order the mesh PHY rate table. */

    ULONG                           TxRate; /**< Indicate the transmit PHY rate in Mbps from the MoCA node
    identified by 'mocaMeshTxNodeIndex' to the MoCA node identified by 'mocaMeshRxNodeIndex'. */

    ULONG                           TxRateNper; /**< Only for MoCA 2.x */
    ULONG                           TxRateVlper; /**< Only for MoCA 2.x */

} moca_mesh_table_t;
#endif

typedef struct {
    /**< This Data Structure respresents the MoCA interface flow statistics
       table.  This table provides statistics of ingress PQoS flow in the
       MoCA interface. */ 

    ULONG                           FlowID; /**< Indicate the flow ID of a PQoS flow. */
    ULONG                           IngressNodeID; /**< Indicate the flow ID of a Ingress PQoS flow. */
    ULONG                           EgressNodeID; /**< Indicate the flow ID of a Egress PQoS flow. */
    ULONG                           FlowTimeLeft; /**< Indicate the LEASE_TIME_LEFT of the PQoS flow identified by
    'mocaIfFlowID' in which this MoCA interface is an ingress node for this PQoS flow. */
    char                            DestinationMACAddress[18]; /**< Indicate the Destination Address (DA) of Ethernet packets of
    the PQoS Flow for which this node is the ingress node */
    ULONG                           PacketSize; /**< Indicate the number of MoCA aggregation MoCA frames. */
    ULONG                           PeakDataRate; /**< Indicate the T_PEAK_DATA_RATE of the PQoS flow identified by
    'mocaIfFlowID' in which this MoCA interface is an ingress node for the PQoS flow. */
    ULONG                           BurstSize; /**< Indicate the T_BURST_SIZE of the PQoS flow identified by
    'mocaIfFlowID' in which this MoCA interface is an ingress node for this PQoS flow. */
    ULONG                           FlowTag; /**< Indicate the FLOW_TAG of the PQoS flow identified by 'mocaIfFlowID' in which this MoCA interface is an ingress node
    for this PQoS flow. The FLOW_TAG carries application specific content of this PQoS flow. */
    ULONG                           LeaseTime; /**< Indicate the T_LEASE_TIME of the PQoS flow identified by
    'mocaIfFlowID' in which this MoCA interface is an ingress node for this PQoS flow. */
} moca_flow_table_t;

typedef INT ( * moca_associatedDevice_callback)(ULONG ifIndex, moca_associated_device_t *moca_dev); //This call back will be invoked when new MoCA client is Actived or Inactived.moca_associated_device_t.Active is used to indicate activation/inactivation

typedef struct moca_assoc_pnc_info {
    ULONG   mocaNodeIndex; /**< The index of this node */
    BOOL        mocaNodePreferredNC; /**< Whether this Node is a Preferred NC. */
    ULONG    mocaNodeMocaversion; /**< The MoCA version of this node */
}moca_assoc_pnc_info_t;


typedef struct{
    INT TxNode; /**< The NODE ID of Transmit MOCA NODE. */
    INT RxNode; /**< The Node ID of Receive MOCA Node. */
    INT Channel; /**< The Primary channel or Secondary channel used to calculate the NPER and VLPER */
    UCHAR Mod[512]; /**< Subcarrier MODULATION used to calcuate the NPER and VLPER between two nodes */
    UCHAR Nper[512]; /**< Each NPER of between two nodes on Corresponding Channel */
    UCHAR Vlper[512]; /**< Each Vlper of between two nodes on Corresponding Channel */
}moca_scmod_stat_t;


typedef struct {
    UINT NodeID; /**< The NodeID where we want to start the ACA testing */
    PROBE_TYPE Type; /**< The Probe Type could be Enum EVM=1 or Quite=0 */
    UINT Channel; /**< The Channel on which ACA test should start */
    UINT ReportNodes;/**< Specifies the MoCA Nodes that are requested to be part of the channel assessment: Setting bits
corresponding to Node IDs of these MoCA Nodes to 1 (LSB corresponds to Node ID 0x0).
                        For example:
                        0000 0000 0000 0101 can be represented as 0x0005, Node 0 and Node 2.     */
    BOOL ACAStart; /**< The ACAStart will indiacte to start the ACA process or not. 0 for no action , 1 for config and
start
                     the process */
}moca_aca_cfg_t;

typedef struct{
    moca_aca_cfg_t acaCfg; /**< the current configuration on ACA process started */
    INT stat;/**< SUCCESS=0, Fail-BADCHANNEL=1,Fail-NoEVMPROBE=2, Fail=3,In-Progress=4 */
    INT RxPower; /**< Total RX Power in DBM */
    INT ACAPowProfile[512]; /**< Power Profile Representation for each channel*/
    BOOL ACATrapCompleted; /**< mocaIfAcaStatusTrapCompleted ReadOnly parameter, 
                              it will be TRUE when PowerPorfile is ready */
}moca_aca_stat_t;
/** @} */  //END OF GROUP MOCA_HAL_TYPES

void moca_associatedDevice_callback_register(moca_associatedDevice_callback callback_proc); //Callback registration function.

/**
 * @addtogroup MOCA_HAL_APIS
 * @{
 */
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

/****************************************************************/
/* moca_SetIfAcaConfig() function */
/**
* @description Sets the MoCA Configuration Parameters to start the ACA process.
* @param ifIndex - Index of the MoCA Interface.
* @param moca_aca_cfg_t - Configuration Parameters required for MOCA ACA Process
*       \n UINT NodeID; * The NodeID where we want to start the ACA testing *
*       \n PROBE_TYPE Type; * The Probe Type could be Enum EVM=1 or Quite=0 *
*       \n UINT Channel; * The Channel on which ACA test should start *
*       \n UINT ReportNodes;* Specifies the MoCA Nodes that are requested to be part of the channel assessment: Setting
*       bits corresponding to Node IDs of these MoCA Nodes to 1 (LSB corresponds to Node ID 0x0).
                        For example:
                        0000 0000 0000 0101 can be represented as 0x0005, Node 0 and Node 2.     *
* 
*       \n BOOL ACAStart; * The ACAStart for normal configuration should be 0, if ACAStart is 1 then 
                            The Hal should start the process. *
* @return The status of the operation.
* @retval STATUS_SUCCESS if successful.
* @retval STATUS_FAILURE if any error is detected for unknown reason
* @retval STATUS_INPROGRESS if already the ACA process running.
* 
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system 
* calls. It should probably just send a message to a driver event handler task.
* ACAStart bit is set then ACA Process should get start. If user request ACA Start while ACA Process
* in progress, then HAL should send error saying ACA Is in progress. It should not start new one.
*
*/
int moca_setIfAcaConfig(int interfaceIndex, moca_aca_cfg_t acaCfg);
/****************************************************************/
/* moca_GetIfAcaConfig() function */
/**
* @description Gets the MoCA Configuration Parameters set before starting the ACA process.
* @param ifIndex - Index of the MoCA Interface.
* @param moca_aca_cfg_t - Applied Configuration Parameters for MOCA ACA Process
*       \n UINT NodeID; * The NodeID  *
*       \n PROBE_TYPE Type; * The Probe Type could be Enum EVM=1 or Quite=0 *
*       \n UINT Channel; * The Channel on which ACA test should start *
*   \n UINT ReportNodes;* Specifies the MoCA Nodes that are requested to be part of the channel assessment: Setting
*   bits corresponding to Node IDs of these MoCA Nodes to 1 (LSB corresponds to Node ID 0x0).
                        For example:
                        0000 0000 0000 0101 can be represented as 0x0005, Node 0 and Node 2.     *
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
int moca_getIfAcaConfig(int interfaceIndex, moca_aca_cfg_t *acaCfg);

/****************************************************************/
/* moca_cancelIfAca() function */
/**
* @description this function uses to cancel the ACA process which already running.
* @param ifIndex - Index of the MoCA Interface on which ACA process started.
* @return The status of the operation.
* @retval STATUS_SUCCESS if successful.
* @retval STATUS_FAILURE if any error is detected 
* 
* @execution ASynchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system 
* calls. It should probably just send a message to a driver event handler task. 
*/
int moca_cancelIfAca(int interfaceIndex);


/****************************************************************/
/* moca_getIfAcaStatus() function */
/**
* @description Gets the MoCA ACA status after the starting the ACA process.
* @param ifIndex - Index of the MoCA Interface.
* @param moca_aca_stat_t - Applied Configuration Parameters for MOCA ACA Process and
*        ACA Process stats.
*       moca_aca_cfg_t - Applied Configuration Parameters for MOCA ACA Process
*           \n UINT NodeID; * The NodeID  *
*           \n PROBE_TYPE Type; * The Probe Type could be Enum EVM=1 or Quite=0 *
*           \n UINT Channel; * The Channel on which ACA test should start *
*       \n UINT ReportNodes; * Specifies the MoCA Nodes that are requested to be part of the channel assessment: Setting
*       bits corresponding to Node IDs of these MoCA Nodes to 1 (LSB corresponds to Node ID 0x0).
                        For example:
                        0000 0000 0000 0101 can be represented as 0x0005, Node 0 and Node 2.     *
*   \n STATUS stat; * SUCCESS=0, Fail-BADCHANNEL=1,Fail-NoEVMPROBE=2, Fail=3,In-Progress=4 *
*   \n INT RxPower; * Total RX Power in DBM *
*   \n INT ACAPowProfile[512]; * Power Profile Representation for each channel in twos complement way*
*   \n BOOL ACATrapCompleted; * True for When Powerprofile ready *
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
int moca_getIfAcaStatus(int interfaceIndex,moca_aca_stat_t *pacaStat);

/****************************************************************/
/* moca_getIfScmod() function */
/**
* @description Gets the MoCA SCMODE status after the starting the ACA process.
* @param ifIndex - Index of the MoCA Interface.
* @param moca_scmod_stat_t - Status of test between Transmit and recieve node.
*   \n INT TxNode; * The NODE ID of Transmit MOCA NODE. *
*   \n INT RxNode;  * The Node ID of Receive MOCA Node. *
*   \n INT Channel;  The Primary channel or Secondary channel used to calculate the NPER and VLPER *
*   \n UCHAR Mod[512]; * Subcarrier MODULATION used to calcuate the NPER and VLPER between two nodes *
*   \n UCHAR Nper[512]; * Each NPER of between two nodes on Corresponding Channel *
*   \n UCHAR Vlper[512]; * Each Vlper of between two nodes on Corresponding Channel *
* @return The status of the operation.
* @retval STATUS_SUCCESS if successful.
* @retval STATUS_FAILURE if any error is detected 
* 
* @execution Synchronous.
* @sideeffect None.
* @note This function must not suspend and must not invoke any blocking system 
* calls. It should probably just send a message to a driver event handler task. 
*
*/

int moca_getIfScmod(int interfaceIndex,int *pnumOfEntries,moca_scmod_stat_t **ppscmodStat);


/** @} */  //END OF GROUP MOCA_HAL_APIS
#endif
 
