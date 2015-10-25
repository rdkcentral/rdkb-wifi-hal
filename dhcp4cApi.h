#ifndef _DHCP4_CLIENT_API_
#define _DHCP4_CLIENT_API_

enum DHCPC_CMD{
	DHCPC_CMD_LEASE_TIME = 0,
	DHCPC_CMD_LEASE_TIME_REMAIN,
	DHCPC_CMD_RENEW_TIME_REMAIN,
	DHCPC_CMD_REBIND_TIME_REMAIN,
	DHCPC_CMD_CONFIG_ATTEMPTS,
	DHCPC_CMD_GET_IFNAME,
	DHCPC_CMD_FSM_STATE,
	DHCPC_CMD_IP_ADDR,
	DHCPC_CMD_IP_MASK,
	DHCPC_CMD_ROUTERS,
	DHCPC_CMD_DNS_SVRS,
	DHCPC_CMD_DHCP_SVR,
	
	DHCPC_CMD_MAX
};

enum DHCPC_MODULE{
	DHCPC_ECM = 0,
	DHCPC_EROUTER,
    DHCPC_EMTA
};

#define MAX_IPV4_ADDR_LIST_NUMBER	4

typedef struct{
	int	number;
	unsigned int addrList[MAX_IPV4_ADDR_LIST_NUMBER];
}ipv4AddrList_t;

int dhcp4c_get_ert_lease_time(unsigned int *pValue);
int dhcp4c_get_ert_remain_lease_time(unsigned int *pValue);
int dhcp4c_get_ert_remain_renew_time(unsigned int *pValue);
int dhcp4c_get_ert_remain_rebind_time(unsigned int *pValue);
int dhcp4c_get_ert_config_attempts(int *pValue);
int dhcp4c_get_ert_ifname(char *pName);
int dhcp4c_get_ert_fsm_state(int *pValue);
int dhcp4c_get_ert_ip_addr(unsigned int *pValue);
int dhcp4c_get_ert_mask(unsigned int *pValue);
int dhcp4c_get_ert_gw(unsigned int *pValue);
int dhcp4c_get_ert_dns_svrs(ipv4AddrList_t *pList);
int dhcp4c_get_ert_dhcp_svr(unsigned int *pValue);

int dhcp4c_get_ecm_lease_time(unsigned int *pValue);
int dhcp4c_get_ecm_remain_lease_time(unsigned int *pValue);
int dhcp4c_get_ecm_remain_renew_time(unsigned int *pValue);
int dhcp4c_get_ecm_remain_rebind_time(unsigned int *pValue);
int dhcp4c_get_ecm_config_attempts(int *pValue);
int dhcp4c_get_ecm_ifname(char *pName);
int dhcp4c_get_ecm_fsm_state(int *pValue);
int dhcp4c_get_ecm_ip_addr(unsigned int *pValue);
int dhcp4c_get_ecm_mask(unsigned int *pValue);
int dhcp4c_get_ecm_gw(unsigned int *pValue);
int dhcp4c_get_ecm_dns_svrs(ipv4AddrList_t *pList);
int dhcp4c_get_ecm_dhcp_svr(unsigned int *pValue);

int dhcp4c_get_emta_remain_lease_time(unsigned int *pValue);
int dhcp4c_get_emta_remain_renew_time(unsigned int *pValue);
int dhcp4c_get_emta_remain_rebind_time(unsigned int *pValue);

#endif


