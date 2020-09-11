/**
* @file vlan_eth_hal.h
* @brief For CCSP Component:  VLAN Termination HAL Layer
*
* @description This file gives the function prototypes used for the RDK-Broadband
* Ethernet VLAN abstraction layer
*/

/*
 * If not stated otherwise in this file or this component's Licenses.txt file the
 * following copyright and licenses apply:
 *
 * Copyright 2019 RDK Management
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

    module: vlan_eth_hal.h

        For CCSP Component:  VLAN Termination HAL Layer

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

**********************************************************************/

#ifndef __VLAN_ETH_HAL_H__
#define __VLAN_ETH_HAL_H__

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
#define VLAN_ETH_HAL_MAJOR_VERSION 1        // This is the major verion of this HAL.
#define VLAN_ETH_HAL_MINOR_VERSION 0        // This is the minor verson of the HAL.
#define VLAN_ETH_HAL_MAINTENANCE_VERSION 1  // This is the maintenance version of the HAL.

/**********************************************************************
                ENUMERATION DEFINITIONS
**********************************************************************/
// Enumerator for VLAN interface status
typedef enum {
     VLAN_IF_UP = 1,
     VLAN_IF_DOWN,
     VLAN_IF_UNKNOWN,
     VLAN_IF_DORMANT,
     VLAN_IF_NOTPRESENT,
     VLAN_IF_LOWERLAYERDOWN,
     VLAN_IF_ERROR
}vlan_interface_status_e;

/**********************************************************************
                STRUCTURE DEFINITIONS
**********************************************************************/
typedef struct _VLAN_SKB_CONFIG
{
     char alias[32]; /* Indicates DATA or VOICE */
     unsigned int skbMark;  /* SKB Marking Value. */
     unsigned int skbPort; /* SKB Marking Port */
     unsigned int skbEthPriorityMark; /* SKB Ethernet Priority. */
}vlan_skb_config_t;

// Structure for VLAN configuration
typedef struct _vlan_configuration
{
     CHAR L2Interface[64]; /* L2interface like eth3, ptm0 */
     CHAR L3Interface[64]; /* L3 interface like erouter0. */
     INT VLANId; /* Vlan Id */
     UINT TPId; /* Vlan tag protocol identifier. */
     vlan_interface_status_e Status; /* vlan interface status */
     UINT skbMarkingNumOfEntries; /* Number of SKB marking entries. */
     vlan_skb_config_t *skb_config; /* SKB Marking Data. */
     BOOL doReconfigure; /* Reconfiguring the interface, FALSE -> Create and configure, TRUE -> Reconfigure interface. */
} vlan_configuration_t;

/**********************************************************************
 *
 *  VLAN ETH HAL function prototypes
 *
***********************************************************************/

/**
* @description This HAL is used to initialize the vlan hal client. Connected to rpc
* server to send/receive data.
* @param vlan_configuration_t config - vlanconfiguration data
*
* @return The status of the operation.
* @retval RETURN_OK if successful (or) RETURN_OK If interface is already exist with given config data
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
INT vlan_eth_hal_init();

/**
* @description This HAL is used to create and configure an vlan interface and assign the vlanID. This
* HAL also used to reconfigure the vlan interface incase if any update in SKB marking configuration.
* This is being handled by `config->doReconfigure` flag in the vlan_configuration_t. If this flag TRUE,
* indicates, reconfigure required and it will update vlan rules on the existing interface. If it FALSE,
* create and configure the vlan interface.
* @param vlan_configuration_t config - vlanconfiguration data
*
* @return The status of the operation.
* @retval RETURN_OK if successful (or) RETURN_OK If interface is already exist with given config data
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int vlan_eth_hal_configureInterface(vlan_configuration_t *config);

/**
* @description This HAL is used to deassociate an existing vlan interface
* @param const char *vlan_ifname - interface name
*
* @return The status of the operation.
* @retval RETURN_OK if successful (or) RETURN_OK If interface is not exist
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int vlan_eth_hal_deleteInterface(const char *vlan_ifname);

/**
* @description This HAL is used to get current status of an vlan interface
* @param vlan configuration data
*
* @return The status of the operation.
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int vlan_eth_hal_getInterfaceStatus(const char *vlan_ifname, vlan_interface_status_e *status);
#endif /*__VLAN_ETH_HAL_H__*/
