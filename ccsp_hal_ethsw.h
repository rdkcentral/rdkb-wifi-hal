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

    copyright:

        Cisco Systems, Inc., 2014
        All Rights Reserved.

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


#ifndef __CCSP_HAL_ETHSW_H__
#define __CCSP_HAL_ETHSW_H__

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


/**********************************************************************
                STRUCTURE DEFINITIONS
**********************************************************************/

/* CcspHalEthSwInit :  */
/**
* Description: Do what needed to intialize the Eth hal.
* Parameters : None
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.

*
<<<<<<< HEAD
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
=======
* @note This function must not suspend and must not invoke any blocking system 
* calls. It should probably just send a message to a driver event handler task. 
>>>>>>> ARRISXB3-3443 : hal patches from RDKB to yocto branch
*
*/
INT
CcspHalEthSwInit
    (
        void
    );


/* CcspHalEthSwGetPortStatus :  */
/**
* Description: Retrieve the current port status -- link speed, duplex mode, etc.

* Parameters :
    PortId      -- Port ID as defined in CCSP_HAL_ETHSW_PORT
    pLinkRate   -- Receives the current link rate, as in CCSP_HAL_ETHSW_LINK_RATE
    pDuplexMode -- Receives the current duplex mode, as in CCSP_HAL_ETHSW_DUPLEX_MODE
    pStatus     -- Receives the current link status, as in CCSP_HAL_ETHSW_LINK_STATUS

*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.

*
<<<<<<< HEAD
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
=======
* @note This function must not suspend and must not invoke any blocking system 
* calls. It should probably just send a message to a driver event handler task. 
>>>>>>> ARRISXB3-3443 : hal patches from RDKB to yocto branch
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
* Description: Retrieve the current port config -- link speed, duplex mode, etc.

* Parameters :
    PortId      -- Port ID as defined in CCSP_HAL_ETHSW_PORT
    pLinkRate   -- Receives the current link rate, as in CCSP_HAL_ETHSW_LINK_RATE
    pDuplexMode -- Receives the current duplex mode, as in CCSP_HAL_ETHSW_DUPLEX_MODE

*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.

*
<<<<<<< HEAD
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
=======
* @note This function must not suspend and must not invoke any blocking system 
* calls. It should probably just send a message to a driver event handler task. 
>>>>>>> ARRISXB3-3443 : hal patches from RDKB to yocto branch
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
* Description: Set the port configuration -- link speed, duplex mode

* Parameters :
    PortId      -- Port ID as defined in CCSP_HAL_ETHSW_PORT
    LinkRate    -- Set the link rate, as in CCSP_HAL_ETHSW_LINK_RATE
    DuplexMode  -- Set the duplex mode, as in CCSP_HAL_ETHSW_DUPLEX_MODE

*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.

*
<<<<<<< HEAD
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
=======
* @note This function must not suspend and must not invoke any blocking system 
* calls. It should probably just send a message to a driver event handler task. 
>>>>>>> ARRISXB3-3443 : hal patches from RDKB to yocto branch
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
* Description: Retrieve the current port admin status.

* Parameters :
    PortId      -- Port ID as defined in CCSP_HAL_ETHSW_PORT
    pAdminStatus-- Receives the current admin status

*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.

*
<<<<<<< HEAD
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
=======
* @note This function must not suspend and must not invoke any blocking system 
* calls. It should probably just send a message to a driver event handler task. 
>>>>>>> ARRISXB3-3443 : hal patches from RDKB to yocto branch
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
* Description: Set the ethernet port admin status

* Parameters :
    AdminStatus -- set the admin status, as defined in CCSP_HAL_ETHSW_ADMIN_STATUS

*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.

*
<<<<<<< HEAD
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
=======
* @note This function must not suspend and must not invoke any blocking system 
* calls. It should probably just send a message to a driver event handler task. 
>>>>>>> ARRISXB3-3443 : hal patches from RDKB to yocto branch
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
* Description: Set the ethernet port configuration -- admin up/down, link speed, duplex mode

* Parameters :
    PortId      -- Port ID as defined in CCSP_HAL_ETHSW_PORT
    AgingSpeed  -- integer value of aging speed
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.

*
<<<<<<< HEAD
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
=======
* @note This function must not suspend and must not invoke any blocking system 
* calls. It should probably just send a message to a driver event handler task. 
>>>>>>> ARRISXB3-3443 : hal patches from RDKB to yocto branch
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
* Description: Query Moca and External switch port for the given MAC address

* Parameters :
<<<<<<< HEAD
    pMacAddr    -- Specifies the MAC address to search for -- 6 bytes
    pPortId     -- Receives the found port number that the MAC address is seen on values are: 0: MoCA, 1-4: Ethernet port

=======
    mac      -- MAC address to search for
    port      -- The return values are: 0: MoCA, 1-4: Ethernet port 
>>>>>>> ARRISXB3-3443 : hal patches from RDKB to yocto branch
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected or MAC address is not found
*
* @execution Synchronous.
* @sideeffect None.

*
<<<<<<< HEAD
* @note This function must not suspend and must not invoke any blocking system
* calls. It should probably just send a message to a driver event handler task.
=======
* @note This function must not suspend and must not invoke any blocking system 
* calls. It should probably just send a message to a driver event handler task. 
>>>>>>> ARRISXB3-3443 : hal patches from RDKB to yocto branch
*
*/
INT 
CcspHalEthSwLocatePortByMacAddress
	(
		unsigned char * mac, 
		INT * port
	);
#endif /* __CCSP_HAL_ETHSW_H__ */
 
