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


#ifndef  _BRIDGE_UTIL_OEM_H
#define  _BRIDGE_UTIL_OEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>
#include <pthread.h> 


#include "OvsAgentApi.h"
#include "OvsConfig.h"
#include "OvsDataTypes.h"
#include "feedback.h"
#include "gateway_config.h"
#include "ovsagent.h"

#define BRIDGE_UTIL_LOG_FNAME "/rdklogs/logs/bridgeUtils.log"

#define GRE_HANDLER_SCRIPT "/etc/utopia/service.d/service_multinet/handle_gre.sh" 


#define TOTAL_IFLIST_SIZE 	1024
#define BRIDGE_NAME_SIZE  	64
#define IFACE_NAME_SIZE  	64

#define IFLIST_SIZE		256
#define MAX_LOG_BUFF_SIZE	1024
#define TIMESTAMP           	64
extern int DeviceMode ; // router = 0, bridge = 2

extern int MocaIsolation_Val ;

extern int need_wifi_gw_refresh ;
extern int need_switch_gw_refresh ;
extern int syncMembers;
extern int BridgeOprInPropgress ;
extern FILE *logFp;
extern char log_buff[MAX_LOG_BUFF_SIZE];
extern char log_msg_wtime[MAX_LOG_BUFF_SIZE+TIMESTAMP];
extern char primaryBridgeName[64];
extern int PORT2ENABLE;

extern struct tm *timeinfo;
extern time_t utc_time;

#define bridge_util_log(fmt ...)    {\
				    		snprintf(log_buff, MAX_LOG_BUFF_SIZE-1,fmt);\
				    		if(logFp != NULL){ \
                                                snprintf(log_buff, MAX_LOG_BUFF_SIZE-1,fmt);\
                                                utc_time = time(NULL);\
                                                timeinfo = gmtime(&utc_time);\
                                                snprintf(log_msg_wtime, MAX_LOG_BUFF_SIZE+TIMESTAMP-1,"%04d-%02d-%02d %02d:%02d:%02d ::: %s",timeinfo->tm_year+1900,timeinfo->tm_mon+1,timeinfo->tm_mday,timeinfo->tm_hour,timeinfo->tm_min,timeinfo->tm_sec,log_buff);\
                                    		fprintf(logFp,"%s", log_msg_wtime);\
                                    		fflush(logFp);}\
                                 	}

enum Config {
	PRIVATE_LAN = 1,
	HOME_SECURITY = 2,
	HOTSPOT_2G = 3,
	HOTSPOT_5G = 4,
	LOST_N_FOUND = 6,
	HOTSPOT_SECURE_2G = 7,
	HOTSPOT_SECURE_5G = 8,
	MOCA_ISOLATION = 9,
	MESH_BACKHAUL = 10,
	ETH_BACKHAUL = 11,
	MESH = 12

}; 

enum INTERFACE_TYPE {
    IF_BRIDGE_BRIDGEUTIL = 1,
    IF_VLAN_BRIDGEUTIL = 2,
    IF_VLAN_LIST_BRIDGEUTIL = 3,
    IF_GRE_BRIDGEUTIL = 4,
    IF_MOCA_BRIDGEUTIL = 5,
    IF_WIFI_BRIDGEUTIL = 6,
    IF_ETH_BRIDGEUTIL = 7,
    IF_OTHER_BRIDGEUTIL
};

enum BridgeOpr {
	DELETE_BRIDGE = 0,
	CREATE_BRIDGE = 1
}; 

typedef struct bridgeDetails {

	char bridgeName[BRIDGE_NAME_SIZE];
	char vlan_name[BRIDGE_NAME_SIZE];
	int  vlanID;
	char ethIfList[IFLIST_SIZE];
	char MoCAIfList[IFLIST_SIZE];
	char GreIfList[IFLIST_SIZE];
	char WiFiIfList[IFLIST_SIZE];
	char VlanIfList[IFLIST_SIZE];

}bridgeDetails;

extern int updateBridgeInfo(bridgeDetails *bridgeInfo, char* ifNameToBeUpdated, int Opr , int type);
/*********************************************************************************************

    caller:  CreateBrInterface,DeleteBrInterface,SyncBrInterfaces
    prototype:

        int
        HandlePreConfigVendor
           (
		bridgeDetails *bridgeInfo,
		int InstanceNumber
	   );
    description :
		This function has OEM/SOC specific changes which needs to be configured before
		creating/updating/deleting bridge.

	Argument :
		bridgeDetails *bridgeInfo,   -- Bridge info
		int InstanceNumber 			-- Instance number
	return : When success returns 0
***********************************************************************************************/

int HandlePreConfigVendor(bridgeDetails *bridgeInfo,int Config) ;

/*********************************************************************************************

    caller:  CreateBrInterface,DeleteBrInterface,SyncBrInterfaces
    prototype:

        int
        HandlePostConfigVendor
            (
		bridgeDetails *bridgeInfo,
		int InstanceNumber
	    );
    description :
		This function has OEM/SOC specific changes which needs to be configured after
		creating/updating/deleting bridge

	Argument :
		bridgeDetails *bridgeInfo,   -- Bridge info
		int InstanceNumber 	-- Instance number
	return : When success returns 0
***********************************************************************************************/

int HandlePostConfigVendor(bridgeDetails *bridgeInfo,int Config) ;

#endif
