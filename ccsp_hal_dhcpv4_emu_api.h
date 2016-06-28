#ifndef __DHCPV4_EMU_API_H__
#define __DHCPV4_EMU_API_H__



#define GATEWAY 1
#define SUBNET_MASK 2
#define DHCP_STARTING_RANGE 4
#define DHCP_ENDING_RANGE 8
#define DHCP_LEASE_TIME 16
#define UDHCPD_CONF_FILE_PATH "/etc/udhcpd.conf"
#define FILE_SIZE 1024
#define SPACE 32
#define NEW_LINE 10
#define BUFFER_ADJUSTMENT 128
#define DHCP_PID "> /tmp/pidof"
#define DHCP_PATH "/tmp/pidof"
#define DHCPv4_PID "pidof "

#ifndef ULONG
#define ULONG unsigned long
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

#include <stdbool.h>

typedef struct config_values
{
        CHAR *gateway;
        CHAR *subnet;
        CHAR *start;
        CHAR *end;
        CHAR *lease_time;
}ConfigValues;


/*Getting the dhcpv4 configuration (starting and ending)values */
INT CcspHalGetConfigValue(CHAR *key, CHAR *value, INT size);


/*Getting the dhcpv4 configuration(lease time)value */
INT CcspHalGetConfigLeaseValue(CHAR *key, CHAR *value, INT size);


/*passing the inputs to  dhcpv4 configuration file */
INT CcspHal_change_config_value(CHAR *field_name, CHAR *field_value, CHAR *buf, UINT *nbytes);


/*Setting the inputs values to dhcpv4 configuration value  */
INT CcspHalSetDHCPConfigValues(UINT value_flag, ConfigValues *config_value);

/* setting the eth1 interface(ip address) */
INT CcspHalInterfacesetval(CHAR *name,CHAR *str);

/*setting the eth1 interface(netmask) */

INT CcspHalNetmasksetvalue(CHAR *name,CHAR *str);

/* Getting the process id of dhcp server */
INT CcspHalGetPIDbyName(CHAR* pidName);

/* Getting number of client connected devices*/
ULONG CcspHalNoofClientConnected();

/* checking the LAN connection*/
bool checkLan();

/* To Set New Gateway IP Address to Lighttpd Webserver */
INT CcspHalUpdateInterfaceval(CHAR *newgatewayip);



#endif



