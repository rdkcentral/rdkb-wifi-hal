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
#ifndef __FIREWALL_EMU_API_H__
#define __FIREWALL_EMU_API_H__

#ifndef ULONG
#define ULONG unsigned long
#endif

#ifndef UCHAR
#define UCHAR unsigned char
#define BOOLEAN UCHAR
#endif

#ifndef  INTERFACE_SIZE
#define  INTERFACE_SIZE     16
#endif

#define ADD             	 1
#define DELETE        		 2
#define REPLACE         	 3
#define ENABLE          	 4
#define DISABLE         	 5
#define SITE			 1
#define SERVICE			 2
#define SERVICE_TYPE		 1
#define DEVICE_TYPE 		 2
#define SITE_TYPE 		 3
#define TRUSTEDSITE_TYPE 	 4
#define TRUSTEDSERVICE_TYPE 	 5

/****************************************************************
			ENUM DECLARATIONS
*****************************************************************/

typedef enum
{
    IPADDR_IPV4 = 1,
    IPADDR_IPV6 = 2,
}
COSA_DML_IPADDR_TYPE;

typedef enum
{
    PROTO_TCP = 1,
    PROTO_UDP = 2,
    PROTO_BOTH = 3,
}
COSA_DML_PROTO_TYPE;

typedef enum
{
    BLOCK_METHOD_URL = 1,
    BLOCK_METHOD_KEYWORD = 2,
}
COSA_DML_BLOCK_METHOD;

typedef enum
{
    MD_TYPE_BLOCK = 1,
    MD_TYPE_ALLOW = 2,
}
COSA_DML_MD_TYPE;


/*********************************************************
		STRUCTURE DEFINITIONS
**********************************************************/
struct custom_option
{
  int isHttpBlocked;
  int isHttpsBlocked;
  int isPingBlocked;
  int isIdentBlocked;
  int isMulticastBlocked;
  int isP2pBlocked;
  int isFirewallEnabled;
};


struct NetworkDetails
{
   char 		     UpLink_IF[INTERFACE_SIZE];
   char 		     UpLinkBr_IF[INTERFACE_SIZE];
   ANSC_IPV4_ADDRESS         WanIPAddress;
   ANSC_IPV4_MASK            WanSubnetMask;
   ANSC_IPV4_ADDRESS         LanIPAddress;
   ANSC_IPV4_MASK            LanSubnetMask;
};

struct
_COSA_DML_RA_CFG
{
    /*
     *  Extensions -- X_CISCO_COM_RemoteAccess
     */
    BOOLEAN                         bEnabled;
    char                            SupportedProtocols[64];
    BOOLEAN                         bFromAnyIp;
    ANSC_IPV4_ADDRESS               StartIp;
    ANSC_IPV4_ADDRESS               EndIp;
    BOOLEAN                         HttpEnable;
    ULONG                           HttpPort;
    BOOLEAN                         HttpsEnable;
    ULONG                           HttpsPort;
    BOOLEAN                         SSHEnable;
    ULONG                           SSHPort;
    BOOLEAN                         TelnetEnable;
    ULONG                           TelnetPort;
    BOOLEAN                         UpgradePermission;
    char                            StartIpV6[64];
    char                            EndIpV6[64];
}_struct_pack_;

typedef struct _COSA_DML_RA_CFG  COSA_DML_RA_CFG,  *PCOSA_DML_RA_CFG;


/*
 * .ManagedSites.
 */
typedef struct
_COSA_DML_MANAGEDSITES
{
    BOOL            Enable;
}
COSA_DML_MANAGEDSITES;

/*
 * .ManagedSites.BlockedURL.{i}.
 */
typedef struct
_COSA_DML_BLOCKEDURL
{
    ULONG           InstanceNumber;
    char            Alias[256];

    COSA_DML_BLOCK_METHOD BlockMethod;
    char            Site[1025];
    BOOL            AlwaysBlock;
    char            StartTime[64];
    char            EndTime[64];
    BOOL            StartTimeFlg;
    BOOL            EndTimeFlg;
    char            BlockDays[64];
    char            MAC[32];
    char            DeviceName[128];
}
COSA_DML_BLOCKEDURL;
/*
 * .ManagedSites.TrustedUser.{i}.
 */
typedef struct
_COSA_DML_TRUSTEDUSER
{
    ULONG                   InstanceNumber;
    char                    Alias[256];

    char                    HostDescription[64];
    COSA_DML_IPADDR_TYPE    IPAddressType;
    char                    IPAddress[64];
    BOOL                    Trusted;
}
COSA_DML_TRUSTEDUSER;

/*
 * .ManagedServices.
 */
typedef struct
_COSA_DML_MANAGED_SERVS
{
    BOOL            Enable;
}
COSA_DML_MANAGED_SERVS;

/*
 * .ManagedServices.Service.{i}.
 */
typedef struct
_COSA_DML_MS_SERV
{
    ULONG           InstanceNumber;
    char            Alias[256];

    char            Description[64];
    COSA_DML_PROTO_TYPE Protocol;
    ULONG           StartPort;
    ULONG           EndPort;
    BOOL            AlwaysBlock;
    char            StartTime[64];
    char            EndTime[64];
    char            BlockDays[64];
}
COSA_DML_MS_SERV;
/*
 * .ManagedServices.TrustedUser.{i}.
 */
typedef struct
_COSA_DML_MS_TRUSTEDUSER
{
    ULONG           InstanceNumber;
    char            Alias[256];

    char                    HostDescription[64];
    COSA_DML_IPADDR_TYPE    IPAddressType;
    char                    IPAddress[64];
    BOOL                    Trusted;
}
COSA_DML_MS_TRUSTEDUSER;

/*
 * .ManagedDevices.
 */
typedef struct
_COSA_DML_MANAGED_DEVS
{
    BOOL            Enable;
    BOOL            AllowAll;
}
COSA_DML_MANAGED_DEVS;
/*
 * .ManagedDevices.Device.{i}.
 */
typedef struct
_COSA_DML_MD_DEV
{
    ULONG           InstanceNumber;
    char            Alias[256];

    COSA_DML_MD_TYPE Type;
    char            Description[64];
    char            MACAddress[64];
    BOOL            AlwaysBlock;
    char            StartTime[64];
    char            EndTime[64];
    char            BlockDays[64];
}
COSA_DML_MD_DEV;

/*******************************************************************
		           FUNCTION PROTOTYPES
********************************************************************/

/*********************** FIREWALL DECLARATIONS ******************/
/* firewall_service_init() function */
/**
 * @description Initialize resources & retrieve configurations required for firewall service
 *
 * @param option - List of options to initialize firewall service
 *
 * @return The status of the operation
 * @retval 0 if successful
 * @retval < 0 if any error is detected
 *
 */
int firewall_service_init(struct custom_option *option);

/* firewall_service_start() function */
/**
 * @description Start firewall service (including nat & qos)
 *
 * @param level - Firewal levels (None, Low, Medium, High, or Custom)
 * @param netDetails - Newtwork Details (Interface name, IP Address & Subnet 
 Mask for WAN & LAN interface) 
 *
 * @return The status of the operation
 * @retval 0 if successful
 * @retval < 0 if any error is detected
 *
 */
int firewall_service_start(char *level,struct NetworkDetails *netDetails);

/* firewall_service_restart() function */
/**
 * @description Restart the firewall service
 *
 * @param level - Firewal levels (None, Low, Medium, High, or Custom)
 * @param netDetails - Newtwork Details (Interface name, IP Address & Subnet 
 Mask for WAN & LAN interface) 
 *
 * @return The status of the operation
 * @retval 0 if successful
 * @retval < 0 if any error is detected
 *
 */
int firewall_service_restart(char *level,struct NetworkDetails *netDetails);

/* firewall_service_stop() function */
/**
 * @description Stop firewall service (including nat & qos)
 *
 * @param level - Firewal levels (None, Low, Medium, High, or Custom)
 *
 * @return The status of the operation
 * @retval 0 if successful
 * @retval < 0 if any error is detected
 *
 */
int firewall_service_stop(char *level);

/* firewall_service_close() function */
/**
 * @description Close resources initialized for firewall service
 *
 * @param None
 *
 * @return The status of the operation
 * @retval 0 if successful
 * @retval < 0 if any error is detected
 *
 */
int firewall_service_close();

/*********************** REMOTE MANAGEMENT DECLARATIONS ****************/

/* GetHttpPortValue() function */
/**
 * @description Getting Current HttpPort value from lighttpd Configuration file
 *
 * @param value - HTTP Port Value, will be updated in this variable from 
 lighttpd configuration file
 *
 * @return HTTP Port Value, to be returned
 * @retval HTTP Port Value
 *
 */
int GetHttpPortValue(ULONG value);

/* GetHttpsPortValue() function */
/**
 * @description Getting Current HttpsPort value from lighttpd Configuration file
 *
 * @param value - HTTPS Port Value, will be updated in this variable from 
 lighttpd configuration file
 *
 * @return HTTPS Port Value, to be returned
 * @retval HTTPS Port Value
 *
 */
int GetHttpsPortValue(ULONG value);

/* Wan2lan_log_deletion_setup() function */
/**
* @description To Delete Wan2Lan log setup connection
*
* @param netDetails - Newtwork Details (Interface name, IP Address & Subnet 
Mask for WAN & LAN interface)
*
* @return The status of the operation
* @retval 0 if successful
* @retval < 0 if any error is detected
*
*/
int Wan2lan_log_deletion_setup(struct NetworkDetails *netDetails);

/* Wan2lan_log_insertion_setup() function */
/**
* @description To Insert Wan2Lan log setup connection
*
* @param netDetails - Newtwork Details (Interface name, IP Address & Subnet 
Mask for WAN & LAN interface)
*
* @return The status of the operation
* @retval 0 if successful
* @retval < 0 if any error is detected
*
*/
int Wan2lan_log_insertion_setup(struct NetworkDetails *netDetails);

/* GettingWanIP_remotemgmt_deletion_logsetup() function */
/**
* @description Gets Current WAN IP Address for Deletion purpose
*
* @param None
*
* @return The status of the operation
* @retval 0 if successful
* @retval < 0 if any error is detected
*
*/
int GettingWanIP_remotemgmt_deletion_logsetup();

/* GettingWanIP_remotemgmt_insertion_logsetup() function */
/**
* @description Gets Current WAN IP Address for Insertion purpose
*
* @param None
*
* @return The status of the operation
* @retval 0 if successful
* @retval < 0 if any error is detected
*
*/
int GettingWanIP_remotemgmt_insertion_logsetup();

/* DeleteRemoteManagementIptablesRules() function */
/**
* @description To Delete Whole Remote Management Iptables Mapping setup Connection
*
* @param None
*
* @return The status of the operation
* @retval 0 if successful
* @retval < 0 if any error is detected
*
*/
int DeleteRemoteManagementIptablesRules();

/* AddRemoteManagementIptablesRules() function */
/**
* @description To Insert Whole Remote Management Iptables Mapping Setup Connection
*
* @param None
*
* @return The status of the operation
* @retval 0 if successful
* @retval < 0 if any error is detected
*
*/
int AddRemoteManagementIptablesRules();

/* DisablingHttps() function */
/**
* @description To Disable Httpsport to lighttpd configuration file
*
* @param None
*
* @return The status of the operation
* @retval 0 if successful
* @retval < 0 if any error is detected
*
*/
int DisablingHttps();

/* EnablingHttps() function */
/**
* @description To Enable Httpsport to lighttpd configuration file
*
* @param None
*
* @return The status of the operation
* @retval 0 if successful
* @retval < 0 if any error is detected
*
*/
int EnablingHttps();

/* DisablingHttp() function */
/**
* @description To Disable Httpport to lighttpd configuration file
*
* @param None
*
* @return The status of the operation
* @retval 0 if successful
* @retval < 0 if any error is detected
*
*/
int DisablingHttp();

/* EnablingHttp() function */
/**
* @description To Enable Httpport to lighttpd configuration file
*
* @param None
*
* @return The status of the operation
* @retval 0 if successful
* @retval < 0 if any error is detected
*
*/
int EnablingHttp();

/* SetHttpPort() function */
/**
* @description To Set New HttpPort Value to lighttpd web server
*
* @param htttpport - HTTP Port value
*
* @return The status of the operation
* @retval 0 if successful
* @retval < 0 if any error is detected
*
*/
int SetHttpPort(unsigned long htttpport);

/* SetHttpsPort() function */
/**
* @description To Set New HttpsPort Value to lighttpd Web Server
*
* @param httpssport - HTTPS Port value
*
* @return The status of the operation
* @retval 0 if successful
* @retval < 0 if any error is detected
*
*/
int SetHttpsPort(unsigned long httpssport);

/* RemoteManagementiptableRulessetoperation() function */
/**
* @description Execute Remote Management Operations
*
* @param pCfg - Elements of structure "PCOSA_DML_RA_CFG" need to be filled & passed as 
argument
*
* @return The status of the operation
* @retval 0 if successful
* @retval < 0 if any error is detected
*
*/
int RemoteManagementiptableRulessetoperation(PCOSA_DML_RA_CFG pCfg);

/******************** BASIC ROUTING WAN2LAN CONNECTIONS **************/
/* BasicRouting_Wan2Lan_SetupConnection() function */
/**
* @description Routing connection WAN2LAN setup
*
* @param None
*
* @return The status of the operation
* @retval 0 if successful
* @retval < 0 if any error is detected
*
*/
int BasicRouting_Wan2Lan_SetupConnection();

/******************** DMZ DECLARATIONS ************************/

/* Lan2Wan_insertion_logsetup() function */
/**
* @description To Insert Lan2Wan log setup connection
*
* @param netDetails - Newtwork Details (Interface name, IP Address & Subnet 
Mask for WAN & LAN interface) need to be passed
*
* @return The status of the operation
* @retval 0 if successful
* @retval < 0 if any error is detected
*
*/
int Lan2Wan_insertion_logsetup(struct NetworkDetails *netDetails);

/* Lan2Wan_Deletion_logsetup() function */
/**
* @description To Delete Lan2Wan log setup connection
*
* @param netDetails - Newtwork Details (Interface name, IP Address & Subnet 
Mask for WAN & LAN interface) need to be passed
*
* @return The status of the operation
* @retval 0 if successful
* @retval < 0 if any error is detected
*
*/
int Lan2Wan_Deletion_logsetup(struct NetworkDetails *netDetails);

/* GettingLanIP_Insertion_logsetup() function */
/**
* @description Gets current LAN IP Address for Insertion Purposes
*
* @param None
*
* @return The status of the operation
* @retval 0 if successful
* @retval < 0 if any error is detected
*
*/
int GettingLanIP_Insertion_logsetup();

/* GettingLanIP_Deletion_logsetup() function */
/**
* @description Gets Current LAN IP Address for Deletion Purposes
*
* @param None
*
* @return The status of the operation
* @retval 0 if successful
* @retval < 0 if any error is detected
*
*/
int GettingLanIP_Deletion_logsetup();

/* DeleteDMZIptableRules() function */
/**
* @description To Delete Whole DMZ Iptables Mapping Setup Connection
*
* @param None
*
* @return The status of the operation
* @retval 0 if successful
* @retval < 0 if any error is detected
*
*/
int DeleteDMZIptableRules();

/* AddDMZIptableRules() function */
/**
* @description To Add Whole DMZ Iptables Mapping Setup Connection
*
* @param None
*
* @return The status of the operation
* @retval 0 if successful
* @retval < 0 if any error is detected
*
*/
int  AddDMZIptableRules();

/* DMZIptableRulesOperation() function */
/**
* @description Execute DMZ Rules Operation
*
* @param dmzclientip - DMZ Client IP Address
*
* @return The status of the operation
* @retval 0 if successful
* @retval < 0 if any error is detected
*
*/
int DMZIptableRulesOperation(char dmzclientip[40]);

/******************** PORTFORWARDING DECLARATIONS ************************/

/* port_forwarding_add_rule() function */
/**
* @description Add iptable Rule For PortForwarding protocol TCP,UDP,TCP/UDP
*
* @param InternalClient - Internal Client IPv4 Address
* @param prot - Protocol (Eg:- tcp, udp, both )
* @param ExternalPort - External port for adding iptable rule
* @param ExternalPortEndRange - External port end range for adding iptable rule
*
* @return The status of the operation
* @retval 0 if successful
* @retval < 0 if any error is detected
*
*/
int port_forwarding_add_rule(UCHAR InternalClient[IPV4_ADDRESS_SIZE],char *prot,USHORT ExternalPort,USHORT ExternalPortEndRange);

/* port_forwarding_delete_rule() function */
/**
* @description Delete iptable Rule For PortForwarding protocol TCP,UDP,TCP/UDP
*
* @param InternalClient - Internal Client IPv4 Address
* @param prot - Protocol (Eg:- tcp, udp, both )
* @param ExternalPort - External port for deleting iptable rule
* @param ExternalPortEndRange - External port end range for deleting iptable rule
*
* @return The status of the operation
* @retval 0 if successful
* @retval < 0 if any error is detected
*
*/
int port_forwarding_delete_rule(UCHAR InternalClient[IPV4_ADDRESS_SIZE],char *prot,USHORT ExternalPort,USHORT ExternalPortEndRange);

/* port_forwarding_disable() function */
/**
* @description Delete PortForwarding iptable Rules
*
* @param None
*
* @return The status of the operation
* @retval 0 if successful
* @retval < 0 if any error is detected
*
*/
int port_forwarding_disable();

/******************** PORTTRIGGERING DECLARATIONS ************************/

/* port_triggering_add_rule() function */
/**
* @description Add iptable Rule For PortTriggering protocol TCP,UDP,TCP/UDP
*
* @param TriggerPortStart - Port trigger start value
* @param TriggerPortEnd - Port trigger end value
* @param prot - Protocol (eg:- tcp, udp, both)
* @param ForwardPortStart - Port forward start value
* @param ForwardPortEnd - Port forward end value
*
* @return The status of the operation
* @retval 0 if successful
* @retval < 0 if any error is detected
*
*/
int port_triggering_add_rule(USHORT TriggerPortStart,USHORT TriggerPortEnd,char *prot,USHORT ForwardPortStart,USHORT ForwardPortEnd);

/* port_triggering_delete_rule() function */
/**
* @description Delete iptable Rule For PortTriggering protocol TCP,UDP,TCP/UDP
*
* @param TriggerPortStart - Port trigger start value
* @param TriggerPortEnd - Port trigger end value
* @param prot - Protocol (eg:- tcp, udp, both)
* @param ForwardPortStart - Port forward start value
* @param ForwardPortEnd - Port forward end value
*
* @return The status of the operation
* @retval 0 if successful
* @retval < 0 if any error is detected
*
*/
int port_triggering_delete_rule(USHORT TriggerPortStart,USHORT TriggerPortEnd,char *prot,USHORT ForwardPortStart,USHORT ForwardPortEnd);

/* port_triggering_disable() function */
/**
* @description Delete PortTriggering iptable Rules
*
* @param None
*
* @return The status of the operation
* @retval 0 if successful
* @retval < 0 if any error is detected
*
*/
int port_triggering_disable();


/******************************** Parental Control **********************/

/* do_parentalControl_Addrule_Sites() function */
/**
* @description Add ParentalControl_Sites Rule Chain
*
* @param None
*
* @return The status of the operation
* @retval 0 if successful
* @retval < 0 if any error is detected
*
*/
int do_parentalControl_Addrule_Sites();

/* do_parentalControl_Addrule_Services() function */
/**
* @description Add ParentalControl_Services Rule Chain
*
* @param None
*
* @return The status of the operation
* @retval 0 if successful
* @retval < 0 if any error is detected
*
*/
int do_parentalControl_Addrule_Services();

/* do_parentalControl_Addrule_Devices() function */
/**
* @description Add ParentalControl_Devices Rule Chain
*
* @param None
*
* @return The status of the operation
* @retval 0 if successful
* @retval < 0 if any error is detected
*
*/
int do_parentalControl_Addrule_Devices();

/* do_parentalControl_Delrule_Sites() function */
/**
* @description Delete ParentalControl_Sites Rule Chain
*
* @param None
*
* @return The status of the operation
* @retval 0 if successful
* @retval < 0 if any error is detected
*
*/
int do_parentalControl_Delrule_Sites();

/* do_parentalControl_Delrule_Services() function */
/**
* @description Delete ParentalControl_Services Rule Chain
*
* @param None
*
* @return The status of the operation
* @retval 0 if successful
* @retval < 0 if any error is detected
*
*/
int do_parentalControl_Delrule_Services();

/* do_parentalControl_Delrule_Devices() function */
/**
* @description Delete ParentalControl_Devices Rule Chain
*
* @param None
*
* @return The status of the operation
* @retval 0 if successful
* @retval < 0 if any error is detected
*
*/
int do_parentalControl_Delrule_Devices();

/* do_parentalControl_Sites() function */
/**
* @description Add or Delete Site/Keyword Restriction
*
* @param OPERATION - Add/Delete parental control sites
* @param i_BlockedURLs - URLs detail need to be blocked 
*
* @return The status of the operation
* @retval 0 if successful
* @retval < 0 if any error is detected
*
*/
int do_parentalControl_Sites(int OPERATION,COSA_DML_BLOCKEDURL *i_BlockedURLs);

/* do_parentalControl_Services() function */
/**
* @description Add or Delete Service Restriction
*
* @param OPERATION - Add/Delete parental control services
* @param i_MSServs - Managed Service's details need to be blocked 
*
* @return The status of the operation
* @retval 0 if successful
* @retval < 0 if any error is detected
*
*/
int do_parentalControl_Services(int OPERATION,COSA_DML_MS_SERV *i_MSServs);

/* do_parentalControl_Devices() function */
/**
* @description Add or Delete Device Restriction
*
* @param OPERATION - Add/Delete parental control devices
* @param i_MDDevs - Managed Devices's details need to be blocked 
*
* @return The status of the operation
* @retval 0 if successful
* @retval < 0 if any error is detected
*
*/
int do_parentalControl_Devices(int OPERATION,COSA_DML_MD_DEV *i_MDDevs);

/* CosaDmlTrustedUser_Accept() function */
/**
* @description Add or Delete Trusted Computer on Site and Service Restriction
*
* @param block_type - Block type (eg:- TRUSTEDSITE_TYPE, TRUSTEDSERVICE_TYPE)
* @param ipAddress - IP Address
* @param operation - Add/Delete parental control sites or services 
*
* @return The status of the operation
* @retval 0 if successful
* @retval < 0 if any error is detected
*
*/
void CosaDmlTrustedUser_Accept(int block_type,char  ipAddress[64],int operation);

#endif
