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
#ifndef __DHCPV4_EMU_API_H__
#define __DHCPV4_EMU_API_H__

#include <stdint.h>


#define GATEWAY 1
#define SUBNET_MASK 2
#define DHCP_STARTING_RANGE 4
#define DHCP_ENDING_RANGE 8
#define DHCP_LEASE_TIME 16
#define DNSMASQ_CONF_FILE_PATH "/etc/dnsmasq.conf"
#define FILE_SIZE 1024
#define SPACE 32
#define NEW_LINE 10
#define BUFFER_ADJUSTMENT 128
#define MAX_NUM_HOST 50
#define COSA_DML_ALIAS_NAME_LENGTH 64
#define IPV4_ADDRESS_SIZE 4
#define COSA_DML_IF_NAME_LENGTH 64
#define DHCP_PID "> /tmp/pidof"
#define DHCP_PATH "/tmp/pidof"
#define DHCPv4_PID "pidof "

#ifndef ULONG
#define ULONG unsigned long
#endif

#ifndef LONG
#define LONG  long
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

#ifndef ANSC_IPV4_ADDRESS
/*
 * While we're trying really hard to smooth the procedure of switch-over from IPv4 to IPv4, there
 * are many places where using the IP address as an integer for comparision and calculation is much
 * easier than array-based operation.
 */
#define  ANSC_IPV4_ADDRESS                                                                  \
         union                                                                              \
         {                                                                                  \
            unsigned char           Dot[IPV4_ADDRESS_SIZE];                                 \
            uint32_t                Value;                                                  \
         }
#endif

#include <stdbool.h>


struct hostDetails   
{
        char hostName[20];
};

struct ethernet_port_details
{
	char Name[64];
	UCHAR Mac[6];
};

typedef  struct
_HALCOSA_DML_ETH_STATS
{
    ULONG                           BytesSent;
    ULONG                           BytesReceived;
    ULONG                           PacketsSent;
    ULONG                           PacketsReceived;
    ULONG                           ErrorsSent;
    ULONG                           ErrorsReceived;
    ULONG                           UnicastPacketsSent;
    ULONG                           UnicastPacketsReceived;
    ULONG                           DiscardPacketsSent;
    ULONG                           DiscardPacketsReceived;
    ULONG                           MulticastPacketsSent;
    ULONG                           MulticastPacketsReceived;
    ULONG                           BroadcastPacketsSent;
    ULONG                           BroadcastPacketsReceived;
    ULONG                           UnknownProtoPacketsReceived;
}
HALCOSA_DML_ETH_STATS, *HALPCOSA_DML_ETH_STATS;

typedef  enum
_HALCOSA_DML_IF_STATUS
{
    HALCOSA_DML_IF_STATUS_Up               = 1,
    HALCOSA_DML_IF_STATUS_Down,
    HALCOSA_DML_IF_STATUS_Unknown,
    HALCOSA_DML_IF_STATUS_Dormant,
    HALCOSA_DML_IF_STATUS_NotPresent,
    HALCOSA_DML_IF_STATUS_LowerLayerDown,
    HALCOSA_DML_IF_STATUS_Error
}
HALCOSA_DML_IF_STATUS, *HALPCOSA_DML_IF_STATUS;

struct
_HALCOSA_DML_DHCPS_SADDR
{
    ULONG                           InstanceNumber;
    char                            Alias[COSA_DML_ALIAS_NAME_LENGTH];

    bool                            bEnabled;
    UCHAR                           Chaddr[6];
    ANSC_IPV4_ADDRESS               Yiaddr;
    char                            DeviceName[COSA_DML_ALIAS_NAME_LENGTH];
    char                            Comment[256];
    bool                            ActiveFlag;
};

typedef  struct _HALCOSA_DML_DHCPS_SADDR HALCOSA_DML_DHCPS_SADDR,  *HALPCOSA_DML_DHCPS_SADDR;

typedef  struct
_HALCOSA_DML_ETH_PORT_CFG
{
    ULONG                           InstanceNumber;
    char                            Alias[COSA_DML_IF_NAME_LENGTH];

    bool                            bEnabled;
    LONG                            MaxBitRate;
}
HALCOSA_DML_ETH_PORT_CFG,  *HALPCOSA_DML_ETH_PORT_CFG;

/*
 *  Static portion of Ethernet port info
 */
typedef  struct
_HALCOSA_DML_ETH_PORT_SINFO
{
    char                            Name[COSA_DML_IF_NAME_LENGTH];
    bool                            bUpstream;
    UCHAR                           MacAddress[6];
}
HALCOSA_DML_ETH_PORT_SINFO,  *HALPCOSA_DML_ETH_PORT_SINFO;


/*
 *  Dynamic portion of Ethernet port info
 */
typedef  struct
_HALCOSA_DML_ETH_PORT_DINFO
{
    HALCOSA_DML_IF_STATUS              Status;
    ULONG                           CurrentBitRate;
    ULONG                           LastChange;
    ULONG                           AssocDevicesCount;
}
HALCOSA_DML_ETH_PORT_DINFO,  *HALPCOSA_DML_ETH_PORT_DINFO;


typedef  struct
_HALCOSA_DML_ETH_PORT_FULL
{
    HALCOSA_DML_ETH_PORT_CFG           Cfg;
    HALCOSA_DML_ETH_PORT_SINFO         StaticInfo;
    HALCOSA_DML_ETH_PORT_DINFO         DynamicInfo;
}
HALCOSA_DML_ETH_PORT_FULL, *HALPCOSA_DML_ETH_PORT_FULL;


/*
 *  Procedure     : CcspHalGetConfigValues
 *  Purpose       : To Get current DHCPv4 parameter values from dnsmasq configuration file
 *
 *  Parameters    : 
 *     value_flag : To Get current value_flag status (subnet_mask,DHCP_starting & Ending Range,Lease Time)
 *     value      : Current DHCP parameter value should be stored 
 *     size       : size of value 
 *  Return_values : 
 *      value     : Current DHCP parameter value , to be returned
 *      size      : size of value, to be returned
 */

void CcspHalGetConfigValues(INT value_flag,CHAR *value, INT size);

/*
 *  Procedure     : CcspHalSetDHCPConfigValues
 *  Purpose       : To set current DHCPv4 parameter values to dnsmasq configuration file
 *
 *  Parameters    : 
 *     value_flag : To Get current value_flag status (subnet_mask,DHCP_starting & Ending Range,Lease Time)
 *     value      : Current DHCP parameter value should be stored 
 *  Return_values : The status of the operation
 *     @retval 0 , if successful
 *     @retval<0 , if any error is detected
 */

INT CcspHalSetDHCPConfigValues(INT value_flag,CHAR *value);


/*
 *  Procedure     : CcspHalInterfacesetval
 *  Purpose       : To set current DHCPv4 Router value to Emulator(Gateway)
 *
 *  Parameters    : 
 *     name       : To Get Interface Name 
 *     str        : To Get New Gateway IP Address
 *  Return_values : The status of the operation
 *     @retval 0 , if successful
 *     @retval<0 , if any error is detected
 */

INT CcspHalInterfacesetval(CHAR *name,CHAR *str);

/*
 *  Procedure     : CcspHalNetmasksetvalue
 *  Purpose       : To set current DHCPv4 Subnet value to Emulator
 *
 *  Parameters    : 
 *     name       : To Get Interface Name 
 *     str        : To Get New Subnet Mask Address
 *  Return_values : The status of the operation
 *     @retval 0 , if successful
 *     @retval<0 , if any error is detected
 */


INT CcspHalNetmasksetvalue(CHAR *name,CHAR *str);

/*
 *  Procedure     : CcspHalGetPIDbyName
 *  Purpose       : To Get DHCPv4 server PID (to known ,it should be in Enable or Disable state)
 *
 *  Parameters    : 
 *     pidName    : To get DHPCv4 server Name
 *  Return_values : The status of the operation
 *     @retval 0 , if successful
 *     @retval<0 , if any error is detected
 */

INT CcspHalGetPIDbyName(CHAR* pidName);

/*
 *  Procedure     : CcspHalNoofClientConnected
 *  Purpose       : To Get Total number of connected clients through Emulator(Gateway)
 *
 *  Parameters    : None
 *  Return_values : The status of the operation
 *     @retval 0 , if successful
 *     @retval<0 , if any error is detected
 */

ULONG CcspHalNoofClientConnected();

/*
 *  Procedure     : checkLan
 *  Purpose       : To check the Lan status
 *
 *  Parameters    : None
 *  Return_values : The status of the operation
 *     @retval TRUE , if successful
 *     @retval FALSE , if any error is detected
 */

bool checkLan();

/*
 *  Procedure     : CcspHalUpdateInterfaceval
 *  Purpose       : To set new Gateway IP address to Lighttpd WebServer
 *
 *  Parameters    : 
 *   newgatewayip : Having New Gateway IP Address
 *  Return_values : The status of the operation
 *     @retval 0 , if successful
 *     @retval<0 , if any error is detected
 */

INT CcspHalUpdateInterfaceval(CHAR *newgatewayip);

/*
 *  Procedure           : updateReservedIp
 *  Purpose             : It will edit the Existing Reserved IP in static Table Entry
 *
 *  Parameters          : 
 *   hostPtr            : Having connected clients details. 
 *   pDhcpStaticAddress : Having static table entry details.
 *  Return_values       : None
 */


void updateReservedIp(struct hostDetails *hostPtr,HALPCOSA_DML_DHCPS_SADDR pDhcpStaticAddress);

/*
 *  Procedure           : CcspHalDHCPv4ReservedClients
 *  Purpose             : To set Reserved IP in Static Entry Table 
 *
 *  Parameters          : 
 *   pDhcpStaticAddress : Having Static Table Entry.
 *  Return_values       : None
 */

void CcspHalDHCPv4ReservedClients(HALPCOSA_DML_DHCPS_SADDR pDhcpStaticAddress);

/*
 *  Procedure           : CcspHalDHCPv4DeleteReservedClients
 *  Purpose             : To delete Reserved IP in Static Entry Table 
 *
 *  Parameters          : 
 *   pDhcpStaticAddress : Having Static Table Entry.
 *  Return_values       : None
 */

void CcspHalDHCPv4DeleteReservedClients(HALPCOSA_DML_DHCPS_SADDR pDhcpStaticAddress);

/*
 *  Procedure           : RestartDnsmasq
 *  Purpose             : Restart the dnsmasq with updated configuration
 *
 *  Parameters          : None
 *  Return_values       : None
 */

void RestartDnsmasq();

/*
 *  Procedure           : GetInterfaceMacAddressValue
 *  Purpose             : To Get NULL MAC Address,If that interface is not there
 *
 *  Parameters          : 
 *   interface_details  : Having Mac Address Value is NULL
 *  Return_values       : None
 */

void GetInterfaceMacAddressValue(struct ethernet_port_details *interface_details);

/*
 *  Procedure           : CcspHalGetInterfaceDetails
 *  Purpose             : To Get all Interface Details(like Name,Mac Address).
 *
 *  Parameters          : 
 *   interface_details  : Having Interface Details of Static Information.
 *   ulIndex            : Instance Number of Interfaces
 *  Return_values       : None
 */

void CcspHalGetInterfaceDetails(ULONG ulIndex,struct ethernet_port_details *interface_details);

/*
 *  Procedure           : CcspHalGetInterfaceStatusDetails
 *  Purpose             : To Get all Interface Status Detail.
 *
 *  Parameters          : 
 *   pInfo              : Having Interface Status Detail.
 *   ulInstanceNumber   : Instance Number of Interfaces
 *  Return_values       : None
 */

void CcspHalGetInterfaceStatusDetails(ULONG ulInstanceNumber,HALPCOSA_DML_ETH_PORT_DINFO pInfo);

/*
 *  Procedure         : CcspHalSetInterfaceEnableDetails
 *  Purpose           : To check the LAN and WAN Enable Status in Emulator
 *
 *  Parameters        : 
 *     InstanceNumber : Having Instance Number of Interface
 *     enable         : Having current interface status
 *  Return_values     : The status of the operation
 *     @retval true , if successful
 *     @retval false , if any error is detected
 */
int CcspHalSetInterfaceEnableDetails(int index,bool enable);

/*
 *  Procedure         : CcspHalGetInterfaceEnableDetails
 *  Purpose           : To check the LAN and WAN Enable Status in Emulator
 *
 *  Parameters        : 
 *     InstanceNumber : Having Instance Number of Interface
 *  Return_values     : The status of the operation
 *     @retval true , if successful
 *     @retval false , if any error is detected
 */
int CcspHalGetInterfaceEnableDetails(ULONG InstanceNumber,bool *enable);

/*
 *  Procedure            : CcspHalGetBridgePortNames
 *  Purpose              : To get Bridge Port Names
 *
 *  Parameters           : 
 *   ulBrgInstanceNumber : Having Instance number of Bridge
 *   ulIndex             : Having Instance number of port
 *   string              : Having Bridge_Port Names
 *  Return_values        : None
 */

void CcspHalGetBridgePortNames(ULONG ulBrgInstanceNumber,ULONG ulIndex,char *string);

/*
 *  Procedure         : GetBridgePortStatus
 *  Purpose           : To Get Bridge Port Current Status
 *
 *  Parameters        : 
 *     string         : Having Current Interface
 *  Return_values     : The status of the operation
 *     @retval up   , if successful
 *     @retval down , if any error is detected
 */

HALCOSA_DML_IF_STATUS GetBridgePortStatus(char *string);

/*
 *  Procedure              : CcspHalGetBridgePortStatus
 *  Purpose                : To Get Bridge Port Current Status
 *
 *  Parameters             : 
 *     ulBrgInstanceNumber : Having Instance Number of Bridge
 *     ulIndex             : Having Instance Number of Port
 *  Return_values          : The status of the operation
 *     @retval up    , if successful
 *     @retval down  , if any error is detected
 */

HALCOSA_DML_IF_STATUS CcspHalGetBridgePortStatus(ULONG ulBrgInstanceNumber,ULONG ulIndex);

/*
 *  Procedure         : GetBridgePortEnable
 *  Purpose           : To Get Bridge Port Enable Status
 *
 *  Parameters        : 
 *     string         : Having current Interface
 *  Return_values     : The status of the operation
 *     @retval true , if successful
 *     @retval false , if any error is detected
 */

bool GetBridgePortEnable(char *string);

/*
 *  Procedure              : CcspHalGetBridgePortEnable
 *  Purpose                : To Get Bridge Port Enable Status
 *
 *  Parameters             : 
 *     ulBrgInstanceNumber : Having Instance Number of Bridge
 *     ulIndex             : Having Instance Number of Port
 *  Return_values          : The status of the operation
 *     @retval true , if successful
 *     @retval false , if any error is detected
 */

bool CcspHalGetBridgePortEnable(ULONG ulIndex,ULONG ulBrgInstanceNumber);

/*
 *  Procedure           : CcspHalGetBridgePortStats
 *  Purpose             : To get Bridge Port Status Value is NULL
 *
 *  Parameters          : 
 *   pStats             : Having Bridge port stats details.
 *  Return_values       : None
 */

void CcspHalGetBridgePortStats(HALPCOSA_DML_ETH_STATS pStats);

/*
 *  Procedure           : CcspHaldhcpv4cGetGw
 *  Purpose             : To get WAN Default Gateway Address 
 *
 *  Parameters          : 
 *   Gateway_Address    : Having WAN Default Gateway Address
 *  Return_values       : None
 */

void CcspHaldhcpv4cGetGw(char Gateway_Address[120]);

/*
 *  Procedure           : CcspHalGetDNSServerValue
 *  Purpose             : To get primary and secondary DNSServer values
 *
 *  Parameters          : 
 *   InstanceNum        : Having Instance Number 
 *   DNSServer          : Having DNSServer Value
 *  Return_values       : None
 */

void CcspHalGetDNSServerValue(ULONG InstanceNum, char DNSServer[64]);

/*
 *  Procedure           : CcspHalGetWanAddressMode
 *  Purpose             : Whether DHCP is enabled or disabled
 *
 *  Parameters          : None
 *  Return_values       : Status of the Operation
 *     @retval true , if successful
 *     @retval false , if any error is detected
 */

bool CcspHalGetWanAddressMode();

/*
 *  Procedure           : CcspHalDhcpcGetInfo
 *  Purpose             : To get LeaseTimeRemaining information for connected clients
 *
 *  Parameters          : None
 *  Return_values       : LeaseTimeRemaining value
 */

int CcspHalDhcpcGetInfo();





#endif



