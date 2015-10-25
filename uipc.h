#ifndef _UNIX_SOCKET_IPC_H_
#define _UNIX_SOCKET_IPC_H_

#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <pthread.h>

#ifndef UIPC_DATA_MAX_SIZE
#define UIPC_DATA_MAX_SIZE	2048
#endif

#define UIPC_RCV_WAIT_FOREVER	-1
#ifndef UIPC_CLIENT_NAME
#define UIPC_CLIENT_NAME	"/var/uipcClnt"
#endif

typedef struct{
	short cmd;
	short length; /*length of data in bytes*/
	unsigned char data[UIPC_DATA_MAX_SIZE];
}uIpcData_t;

typedef void (*uIpcCmdHandler_t)(uIpcData_t *pData,struct sockaddr_un *pAddr);

/*APIs in server side*/
void uipc_svr_release_resources(void);
int uipc_svr_send_data(struct sockaddr_un *pClientAddr, uIpcData_t *pData);
int uipc_svr_init(char *svrFileName,uIpcCmdHandler_t func);

/*APIs in client side*/

int uipc_clnt_send_data(char *svrFileName,uIpcData_t *pData);
int uipc_clnt_send_and_recv_data(char *svrFileName, uIpcData_t *pData,int waitTime/*in secnds*/);

#endif
