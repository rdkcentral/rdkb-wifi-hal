/**********************************************************************
   Copyright [2016] [Comcast, Corp.]
 
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

    module: vlan_hal.h

        For CCSP Component:  VLAN_Provisioning_and_management

    ---------------------------------------------------------------

    copyright:

        Comcast, Corp., 2016
        All Rights Reserved.

    ---------------------------------------------------------------

    description:

        This header file gives the function call prototypes and 
        structure definitions used for the RDK-Broadband 
        VLAN abstraction layer

        NOTE:
        THIS VERSION IS AN EARLY DRAFT INTENDED TO GET COMMENTS FROM COMCAST.
        TESTING HAS NOT YET BEEN COMPLETED.  
       
    ---------------------------------------------------------------

    environment:

        This HAL layer is intended to support VLAN drivers 
        through the System Calls.  

    ---------------------------------------------------------------

    author:

	zhicheng_qiu@cable.comcast.com

**********************************************************************/

#ifndef __VLAN_HAL_H__
#define __VLAN_HAL_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

#ifndef RETURN_OK
#define RETURN_OK   0
#endif

#ifndef RETURN_ERR
#define RETURN_ERR   -1
#endif

//defines for HAL version 1.0
#define VLAN_HAL_MAJOR_VERSION 1   		// This is the major verion of this HAL.
#define VLAN_HAL_MINOR_VERSION 0   		// This is the minor verson of the HAL.
#define VLAN_HAL_MAINTENANCE_VERSION 1  // This is the maintenance version of the HAL.

//defines for charecter length for VLAN configurartion
#define VLAN_HAL_MAX_VLANGROUP_TEXT_LENGTH			32  
#define VLAN_HAL_MAX_VLANID_TEXT_LENGTH				32  
#define VLAN_HAL_MAX_INTERFACE_NAME_TEXT_LENGTH		32  

#define VLAN_HAL_MAX_LINE_BUFFER_LENGTH				120  

/**********************************************************************
                ENUMERATION DEFINITIONS
**********************************************************************/

/**********************************************************************
                STRUCTURE DEFINITIONS
**********************************************************************/

// Structure for VLANID Maintainance
typedef struct _vlan_vlanidconfiguration
{
     char groupName[VLAN_HAL_MAX_VLANGROUP_TEXT_LENGTH];
     char vlanID[VLAN_HAL_MAX_VLANID_TEXT_LENGTH];	 
     struct _vlan_vlanidconfiguration *nextlink;
	 	
} vlan_vlanidconfiguration_t;

/**********************************************************************
 *
 *  VLAN HAL function prototypes 
 *
***********************************************************************/

//This HAL is used to creat an new vlan group, and assig default vlanID. 
// If success, return 0
// If group is already exist and has expected vlanID, this HAL return 0
int vlan_hal_addGroup(const char *groupName, const char *default_vlanID);

//This HAL is used to delete existing vlan group, and delete correspond interface association. 
// If success, return 0
// If group is not exist, return 0,
int vlan_hal_delGroup(const char *groupName);

//This HAL is used to add interface to existing vlan group, and assign the vlanID. 
// If success, return 0
// If group is not exist, return -1
// If interface is already in group, and has expected vlan ID, return 0
int vlan_hal_addInterface(const char *groupName, const char *ifName, const char *vlanID);

//This HAL is used to deassociate existing interface from group. 
// If success, return 0
// If interface is not exist, return 0,
int vlan_hal_delInterface(const char *groupName, const char *ifName, const char *vlanID);

//This HAL is used dump the group setting, for debug purpose
int vlan_hal_printGroup(const char *groupName);
//This HAL is used dump all group setting. 
int vlan_hal_printAllGroup();

//This HAL is used to deassociate all existing interface from group. 
int vlan_hal_delete_all_Interfaces(const char *groupName);

//This HAL utility is used identify given bridge available in linux bridge
int _is_this_group_available_in_linux_bridge(char * br_name);

//This HAL utility is used identify given interface available in given bridge
int _is_this_interface_available_in_linux_bridge(char * if_name, char *vlanID);

//This HAL utility is used identify given interface available in anyone of linux bridge
int _is_this_interface_available_in_given_linux_bridge(char * if_name, char * br_name,char *vlanID);

//This HAL utility is used get the buffer from shell output
void _get_shell_outputbuffer(char * cmd, char * out, int len);

//This HAL utility is used store the VLAN ID, Group Name configuration
int insert_VLAN_ConfigEntry(char *groupName, char *vlanID);

//This HAL utility is used delete the VLAN ID, Group Name configuration
int delete_VLAN_ConfigEntry(char *groupName);

//This HAL utility is used delete the VLAN ID, Group Name configuration from link
int get_vlanId_for_GroupName(const char *groupName, char *vlanID);

//This HAL utility is used get the VLAN ID for corresponding Group Name from link
int print_all_vlanId_Configuration(void);

/*
Example usage on Puma6 platfom:
	Private network group (vlan100)
		brlan0      eth_1(external swith port 1), eth_2(port 2), eth_3(port 3),  MoCA.100 (MoCA vlan100),  ath0(2.4G vlan100), ath1 (5G vlan100)
		
vlan_hal_addGroup("brlan0", "100");					//brctl addbr brlan0
vlan_hal_addInterface("brlan0", "l2sd0", NULL);		//vconfig add l2sd0 100; brctl addif brlan0 l2sd0.100


	Xfinity Home VLAN (vlan101)
		brlan1	eth_4(port 4),  MoCA.101(MoCA vlan101), ath2(2.4G vlan101), ath3 (5G vlan101)
		
vlan_hal_addGroup("brlan1", "101");					//brctl addbr brlan1
vlan_hal_addInterface("brlan1", "l2sd0", NULL);		//vconfig add l2sd0 100; brctl addif brlan1 l2sd0.101


	Xfinity Wifi VLAN 2.4G (vlan102)
		brlan2     gretap0.102 (GRE vlan102),  MoCA.102(MoCA vlan102), ath4(2.4G vlan102)
		
vlan_hal_addGroup("brlan2", "102");					//brctl addbr brlan2
vlan_hal_addInterface("brlan2", "l2sd0", NULL);		//vconfig add l2sd0 102; brctl addif brlan1 l2sd0.102
vlan_hal_addInterface("brlan2", "gretap0", NULL);  //vconfig add gretap0 102; brctl addif brlan1 gretap0.102


	Xfinity Wifi VLAN 5G (vlan103)
		brlan3     gretap0.103 (GRE vlan103),  MoCA.103(MoCA vlan103), ath5(2.4G vlan103)
		
vlan_hal_addGroup("brlan3", "103");					//brctl addbr brlan3
vlan_hal_addInterface("brlan3", "l2sd0", NULL);		//vconfig add l2sd0 103; brctl addif brlan1 l2sd0.103
vlan_hal_addInterface("brlan3", "gretap0", NULL);  //vconfig add gretap0 103; brctl addif brlan1 gretap0.103

*/
#endif /*__VLAN_HAL_H__*/
