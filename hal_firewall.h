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

/*******************************************************************
		           FUNCTION PROTOTYPES
********************************************************************/

/*********************** FIREWALL DECLARATIONS ******************/
int firewall_service_init(struct custom_option *option);
int firewall_service_start(char *level,struct NetworkDetails *netDetails);
int firewall_service_restart(char *level,struct NetworkDetails *netDetails);
int firewall_service_stop(char *level);
int firewall_service_close();

/*********************** REMOTE MANAGEMENT DECLARATIONS ****************/

/** Getting Current HttpPort value from lighttpd Configuration file **/
int GetHttpPortValue(ULONG value);
/** Getting Current HttpsPort value from lighttpd Configuration file **/
int GetHttpsPortValue(ULONG value);
/** To Delete Wan2Lan log setup connection **/
int Wan2lan_log_deletion_setup(struct NetworkDetails *netDetails);
/** To Insert Wan2Lan log setup connection **/
int Wan2lan_log_insertion_setup(struct NetworkDetails *netDetails);
/** Getting Current WAN IP Address for Deletion purpose **/
int GettingWanIP_remotemgmt_deletion_logsetup();
/** Getting Curent WAN IP Address for Insertion purpose **/
int GettingWanIP_remotemgmt_insertion_logsetup();
/** To Delete Whole Remote Management Iptables Mapping setup Connection **/
int DeleteRemoteManagementIptablesRules();
/** To Insert Whole Remote Management Iptables Mapping Setup Connection **/
int AddRemoteManagementIptablesRules();
/** To Disable Httpsport to lighttpd configuration file **/
int DisablingHttps();
/** To Enable Httpsport to lighttpd configuration file **/
int EnablingHttps();
/** To Disable Httpport to lighttpd configuration file **/
int DisablingHttp();
/** To Enable Httpport to lighttpd configuration file **/
int EnablingHttp();
/** To Set New HttpPort Value to lighttpd web server **/
int SetHttpPort(unsigned long htttpport);
/** To Set New HttpsPort Value to lighttpd Web Server **/
int SetHttpsPort(unsigned long httpssport);
/** Remote Management Operations **/
int RemoteManagementiptableRulessetoperation(PCOSA_DML_RA_CFG pCfg);

/******************** BASIC ROUTING WAN2LAN CONNECTIONS **************/
int BasicRouting_Wan2Lan_SetupConnection();

/******************** DMZ DECLARATIONS ************************/

/** To Insert Lan2Wan log setup connection **/
int Lan2Wan_insertion_logsetup(struct NetworkDetails *netDetails);
/** To Delete Lan2Wan log setup connection **/
int Lan2Wan_Deletion_logsetup(struct NetworkDetails *netDetails);
/** Getting current LAN IP Address for Insertion Purposes **/
int GettingLanIP_Insertion_logsetup();
/** Getting Current LAN IP Address for Deletion Purposes **/
int GettingLanIP_Deletion_logsetup();
/** To Delete Whole DMZ Iptables Mapping Setup Connection **/
int DeleteDMZIptableRules();
/** To Add Whole DMZ Iptables Mapping Setup Connection **/
int  AddDMZIptableRules();
/** DMZ Operation **/
int DMZIptableRulesOperation(char dmzclientip[40]);

/******************** PORTFORWARDING DECLARATIONS ************************/

int port_forwarding_add_rule(UCHAR InternalClient[IPV4_ADDRESS_SIZE],char *prot,USHORT ExternalPort,USHORT ExternalPortEndRange);
int port_forwarding_delete_rule(UCHAR InternalClient[IPV4_ADDRESS_SIZE],char *prot,USHORT ExternalPort,USHORT ExternalPortEndRange);
int port_forwarding_disable();

/******************** PORTTRIGGERING DECLARATIONS ************************/

int port_triggering_add_rule(USHORT TriggerPortStart,USHORT TriggerPortEnd,char *prot,USHORT ForwardPortStart,USHORT ForwardPortEnd);
int port_triggering_delete_rule(USHORT TriggerPortStart,USHORT TriggerPortEnd,char *prot,USHORT ForwardPortStart,USHORT ForwardPortEnd);
int port_triggering_disable();
#endif
