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

    module: ccsp_hal_ethsw.h

        For CCSP Component:  Ccsp Provisioning & Managment

    ---------------------------------------------------------------

    description:

        This header file defines the structures and function prototypes
        for Ethernet Switch control.
       
    ---------------------------------------------------------------

    environment:

        platform independent

    ---------------------------------------------------------------

    author:

        Cisco

**********************************************************************/

/**
* @file ccsp_hal_ethsw.h
* @author Cisco
* @brief For CCSP Component:  Ccsp Provisioning & Managment
*
* @description This header file defines the structures and function prototypes for Ethernet Switch control.
*/

#ifndef __CCSP_HAL_ETHSW_H__
#define __CCSP_HAL_ETHSW_H__

/**
* @defgroup ETHSW_HAL  Ethernet Switch HAL
*
* @defgroup ETHSW_HAL_TYPES  Ethernet Switch HAL Data Types
* @ingroup  ETHSW_HAL
*
* @defgroup ETHSW_HAL_APIS Ethernet Switch HAL  APIs
* @ingroup  ETHSW_HAL
*
**/


/**
 * @addtogroup ETHSW_HAL_TYPES
 * @{
 */

/**********************************************************************
               CONSTANT DEFINITIONS
**********************************************************************/

#ifndef ULONG
#define ULONG unsigned long
#endif

#ifndef CHAR
#define CHAR  char
#endif

#ifndef UCHAR
#define UCHAR unsigned char
#endif

#ifndef BOOLEAN
#define BOOLEAN  UCHAR
#endif

#ifndef INT
#define INT   int
#endif

#ifndef UINT
#define UINT unsigned int
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

#ifndef IPV4_ADDRESS_SIZE
#define  IPV4_ADDRESS_SIZE                          4
#endif

#ifndef IP_ADDRESS_LENGTH
#define  IP_ADDRESS_LENGTH                          IP_ADDRESS_SIZE
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
            UCHAR                   Dot[IPV4_ADDRESS_SIZE];                                 \
            ULONG                   Value;                                                  \
         }
#endif

#ifndef ETHWAN_DEF_INTF_NUM
/*
* ETH WAN Physical Interface Number Assignment - Should eventually move away from Compile Time
* Utilized by Auto WAN feature in provisioning Apps & CCSP Eth Agent with Ethernet WAN Feature, CcspHalExtSw_setEthWanPort()
* ETh WAN HAL is 0 based
*/
#if defined (ETH_6_PORTS)
#define ETHWAN_DEF_INTF_NUM 5
#elif defined (ETH_4_PORTS)
#define ETHWAN_DEF_INTF_NUM 3
#else
/* Default to Physical Port #1 for ETH WAN */
#define ETHWAN_DEF_INTF_NUM 0
#endif
#endif


/**********************************************************************
                STRUCTURE DEFINITIONS
**********************************************************************/

typedef enum
_CCSP_HAL_ETHSW_PORT
{
    CCSP_HAL_ETHSW_EthPort1  = 1,
    CCSP_HAL_ETHSW_EthPort2,
    CCSP_HAL_ETHSW_EthPort3,
    CCSP_HAL_ETHSW_EthPort4,
    CCSP_HAL_ETHSW_EthPort5,
    CCSP_HAL_ETHSW_EthPort6,
    CCSP_HAL_ETHSW_EthPort7,
    CCSP_HAL_ETHSW_EthPort8,

    CCSP_HAL_ETHSW_Moca1,
    CCSP_HAL_ETHSW_Moca2,

    CCSP_HAL_ETHSW_Wlan1,
    CCSP_HAL_ETHSW_Wlan2,
    CCSP_HAL_ETHSW_Wlan3,
    CCSP_HAL_ETHSW_Wlan4,

    CCSP_HAL_ETHSW_Processor1,
    CCSP_HAL_ETHSW_Processor2,

    CCSP_HAL_ETHSW_InterconnectPort1,
    CCSP_HAL_ETHSW_InterconnectPort2,

    CCSP_HAL_ETHSW_MgmtPort,
    CCSP_HAL_ETHSW_PortMax
}
CCSP_HAL_ETHSW_PORT, *PCCSP_HAL_ETHSW_PORT;


typedef enum
_CCSP_HAL_ETHSW_LINK_RATE
{
    CCSP_HAL_ETHSW_LINK_NULL      = 0,
    CCSP_HAL_ETHSW_LINK_10Mbps,
    CCSP_HAL_ETHSW_LINK_100Mbps,
    CCSP_HAL_ETHSW_LINK_1Gbps,
    CCSP_HAL_ETHSW_LINK_2_5Gbps,
    CCSP_HAL_ETHSW_LINK_5Gbps,
    CCSP_HAL_ETHSW_LINK_10Gbps,
    CCSP_HAL_ETHSW_LINK_Auto
}
CCSP_HAL_ETHSW_LINK_RATE, *PCCSP_HAL_ETHSW_LINK_RATE;


typedef enum
_CCSP_HAL_ETHSW_DUPLEX_MODE
{
    CCSP_HAL_ETHSW_DUPLEX_Auto    = 0,
    CCSP_HAL_ETHSW_DUPLEX_Half,
    CCSP_HAL_ETHSW_DUPLEX_Full
}
CCSP_HAL_ETHSW_DUPLEX_MODE, *PCCSP_HAL_ETHSW_DUPLEX_MODE;


typedef enum
_CCSP_HAL_ETHSW_LINK_STATUS
{
    CCSP_HAL_ETHSW_LINK_Up        = 0,
    CCSP_HAL_ETHSW_LINK_Down,
    CCSP_HAL_ETHSW_LINK_Disconnected
}
CCSP_HAL_ETHSW_LINK_STATUS, *PCCSP_HAL_ETHSW_LINK_STATUS;


typedef enum
_CCSP_HAL_ETHSW_ADMIN_STATUS
{
    CCSP_HAL_ETHSW_AdminUp        = 0,
    CCSP_HAL_ETHSW_AdminDown,
    CCSP_HAL_ETHSW_AdminTest
}
CCSP_HAL_ETHSW_ADMIN_STATUS, *PCCSP_HAL_ETHSW_ADMIN_STATUS;
/**
 * @}
 */


/**
 * @addtogroup ETHSW_HAL_APIS
 * @{
 */

/**********************************************************************
                STRUCTURE DEFINITIONS
**********************************************************************/

/* CcspHalEthSwInit :  */
/**
* @description Do what needed to intialize the Eth hal.
*
* @param None
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.

*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT
CcspHalEthSwInit
    (
        void
    );


/* CcspHalEthSwGetPortStatus :  */
/**
* @description Retrieve the current port status -- link speed, duplex mode, etc.

* @param PortId      -- Port ID as defined in CCSP_HAL_ETHSW_PORT
* @param pLinkRate   -- Receives the current link rate, as in CCSP_HAL_ETHSW_LINK_RATE
* @param pDuplexMode -- Receives the current duplex mode, as in CCSP_HAL_ETHSW_DUPLEX_MODE
* @param pStatus     -- Receives the current link status, as in CCSP_HAL_ETHSW_LINK_STATUS

*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.

*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT
CcspHalEthSwGetPortStatus
    (
        CCSP_HAL_ETHSW_PORT         PortId,
        PCCSP_HAL_ETHSW_LINK_RATE   pLinkRate,
        PCCSP_HAL_ETHSW_DUPLEX_MODE pDuplexMode,
        PCCSP_HAL_ETHSW_LINK_STATUS pStatus
    );


/* CcspHalEthSwGetPortCfg :  */
/**
* @description Retrieve the current port config -- link speed, duplex mode, etc.

* @param PortId      -- Port ID as defined in CCSP_HAL_ETHSW_PORT
* @param pLinkRate   -- Receives the current link rate, as in CCSP_HAL_ETHSW_LINK_RATE
* @param pDuplexMode -- Receives the current duplex mode, as in CCSP_HAL_ETHSW_DUPLEX_MODE

*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.

*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT
CcspHalEthSwGetPortCfg
    (
        CCSP_HAL_ETHSW_PORT         PortId,
        PCCSP_HAL_ETHSW_LINK_RATE   pLinkRate,
        PCCSP_HAL_ETHSW_DUPLEX_MODE pDuplexMode
    );


/* CcspHalEthSwSetPortCfg :  */
/**
* @description Set the port configuration -- link speed, duplex mode

* @param PortId      -- Port ID as defined in CCSP_HAL_ETHSW_PORT
* @param LinkRate    -- Set the link rate, as in CCSP_HAL_ETHSW_LINK_RATE
* @param DuplexMode  -- Set the duplex mode, as in CCSP_HAL_ETHSW_DUPLEX_MODE

*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.

*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT
CcspHalEthSwSetPortCfg
    (
        CCSP_HAL_ETHSW_PORT         PortId,
        CCSP_HAL_ETHSW_LINK_RATE    LinkRate,
        CCSP_HAL_ETHSW_DUPLEX_MODE  DuplexMode
    );


/* CcspHalEthSwGetPortAdminStatus :  */
/**
* @description Retrieve the current port admin status.

* @param PortId      -- Port ID as defined in CCSP_HAL_ETHSW_PORT
* @param pAdminStatus -- Receives the current admin status

*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.

*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT
CcspHalEthSwGetPortAdminStatus
    (
        CCSP_HAL_ETHSW_PORT           PortId,
        PCCSP_HAL_ETHSW_ADMIN_STATUS  pAdminStatus
    );


/* CcspHalEthSwSetPortAdminStatus :  */
/**
* @description Set the ethernet port admin status

* @param AdminStatus -- Set the admin status, as defined in CCSP_HAL_ETHSW_ADMIN_STATUS
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.

*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT
CcspHalEthSwSetPortAdminStatus
    (
        CCSP_HAL_ETHSW_PORT         PortId,
        CCSP_HAL_ETHSW_ADMIN_STATUS AdminStatus
    );


/* CcspHalEthSwSetAgingSpeed :  */
/**
* @description Set the ethernet port configuration -- admin up/down, link speed, duplex mode

* @param PortId      -- Port ID as defined in CCSP_HAL_ETHSW_PORT
* @param AgingSpeed  -- Integer value of aging speed
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.

*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT
CcspHalEthSwSetAgingSpeed
    (
        CCSP_HAL_ETHSW_PORT         PortId,
        INT                         AgingSpeed
    );

/* CcspHalEthSwLocatePortByMacAddress  :  */
/**
* @description Query Moca and External switch port for the given MAC address

* @param mac      -- MAC address to search for
* @param port     -- The return values are: 0: MoCA, 1-4: Ethernet port 
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected or MAC address is not found
*
* @execution Synchronous.
* @sideeffect None.

*
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
*
*/
INT 
CcspHalEthSwLocatePortByMacAddress
	(
		unsigned char * mac, 
		INT * port
	);


//>>zqiu
//Ethernet HAL for client association/disassociation notification. 

/**
 * @}
 */

/**
 * @addtogroup ETHSW_HAL_TYPES
 * @{
 */

typedef struct _eth_device {
	UCHAR eth_devMacAddress[6];
	INT  eth_port; 		//!< which external port the device attached to. index start from 0
	INT  eth_vlanid; 	//!< what vlan ID the the port tagged.
	INT  eth_devTxRate; 	// optional
	INT  eth_devRxRate; 	// optional
	BOOLEAN eth_Active; 	//device is online/offline
} eth_device_t;
/**
 * @}
 */


/**
 * @addtogroup ETHSW_HAL_APIS
 * @{
 */

INT CcspHalExtSw_getAssociatedDevice(ULONG *output_array_size, eth_device_t **output_struct); //!< The HAL need to allocate array and return the array size by output_array_size

typedef INT ( * CcspHalExtSw_ethAssociatedDevice_callback)(eth_device_t *eth_dev); //!< This call back will be invoked when new Ethernet client come to associate to AP, or existing Ethernet client left. 

void CcspHalExtSw_ethAssociatedDevice_callback_register(CcspHalExtSw_ethAssociatedDevice_callback callback_proc); //!< Callback registration function.

//<<

/* CcspHalExtSw_getEthWanEnable() function */
/**
* @description Get EthernetWAN enable status.
*
* @param pFlag - Pointer to BOOLEAN to store current EthernetWAN enable value
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @sideeffect None
*/
INT
CcspHalExtSw_getEthWanEnable
  (
    BOOLEAN * pFlag
  );

/* CcspHalExtSw_setEthWanEnable() function */
/**
* @description Enable/Disable EthernetWAN functionality.
*
* @param Flag - EthernetWAN enable value
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @sideeffect None
*/
INT
CcspHalExtSw_setEthWanEnable
  (
    BOOLEAN Flag
  );

/* CcspHalExtSw_getEthWanPort() function */
/**
* @description Get EthernetWAN port number value.
*
* @param pPort - Pointer to UINT value to store current setting
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @sideeffect None
*/
INT
CcspHalExtSw_getEthWanPort
  (
    UINT * pPort
  );

/* CcspHalExtSw_setEthWanPort() function */
/**
* @description Set EthernetWAN interface/port number.
*
* @param Port - UINT value to set the setting
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @sideeffect None
*/
INT
CcspHalExtSw_setEthWanPort
  (
    UINT Port
  );

/**
 * @}
 */


/**
 * @addtogroup ETHSW_HAL_TYPES
 * @{
 */

/* 
* @brief Define callback function pointers which needs to be called
* from provisioning abstraction layer when any provisioning
* event occurs.
*/
typedef void ( *fpEthWanLink_Up ) ( ) ;            /**< RDKB expects this callback once EthWan link is UP */
typedef void ( *fpEthWanLink_Down ) ( ) ;  /**< RDKB expects this callback once EthWan link is Down */

/*! \var typedef struct __appCallBack 
*       \brief struct of pointers to the function pointers of callback functions.
*/

typedef struct __appCallBack
{
        fpEthWanLink_Up                    pGWP_act_EthWanLinkUP;
        fpEthWanLink_Down          pGWP_act_EthWanLinkDown;
}appCallBack;

/**
 * @}
 */

/**
 * @addtogroup ETHSW_HAL_APIS
 * @{
 */
void GWP_RegisterEthWan_Callback(appCallBack *obj); //!< This function will get used to register RDKB functions to the callback pointers

INT GWP_GetEthWanLinkStatus(); /**< Returns 1 if active, 0 for inactive */ // RDKB will call this

INT 
GWP_GetEthWanInterfaceName
	(
		unsigned char * Interface 
	); //!< This function will get used to retrieve the ETHWAN interface name. API returns 0 = success and 1 = fail

#endif /* __CCSP_HAL_ETHSW_H__ */

/**
 * @}
 */

 
