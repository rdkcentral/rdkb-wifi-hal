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

    module: platform_hal.h

        For CCSP Component:  CcspCMAgent

    ---------------------------------------------------------------

    description:

        This header file gives the function call prototypes and 
        structure definitions used for the RDK-Broadband 
        hardware abstraction layer for platform

    ---------------------------------------------------------------

    environment:

        This HAL layer is intended to support platform drivers
        through an open API.  
        Changes may be needed to support different hardware enviornments.

    ---------------------------------------------------------------

    author:

        Cisco

**********************************************************************/
/**
* @file platform_hal.h
* @author Cisco
* @brief For CCSP Component:  CcspPandM
*
* @description This header file gives the function call prototypes and structure definitions used for the RDK-Broadband hardware abstraction layer for platform.
*/


#ifndef __PLATFORM_HAL_H__
#define __PLATFORM_HAL_H__

/**
* @defgroup platform_hal Platform HAL
*
* @defgroup PLATFORM_HAL_TYPES  Platform HAL Data Types
* @ingroup  platform_hal
*
* @defgroup PLATFORM_HAL_APIS   Platform HAL  APIs
* @ingroup  platform_hal
*
**/


/**
 * @addtogroup PLATFORM_HAL_TYPES
 * @{
 */


/**********************************************************************
               CONSTANT DEFINITIONS
**********************************************************************/
#ifdef __cplusplus
extern "C"{
#endif

#ifndef CHAR
#define CHAR  char
#endif

#ifndef UCHAR
#define UCHAR unsigned char
#endif

#ifndef BOOLEAN
#define BOOLEAN  unsigned char
#endif

#ifndef INT
#define INT   int
#endif

#ifndef UINT
#define UINT  unsigned int
#endif

#ifndef ULONG
#define ULONG unsigned long
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

/**
 * @}
 */

//DHCPv6 Options
#define DHCPV6_OPT_82  82  // OPTION_SOL_MAX_RT: Solicite Maximum Retry Time
#define DHCPV6_OPT_23  23  // OPTION_SOL_MAX_RT: Solicite Maximum Retry Time
#define DHCPV6_OPT_95  95  // OPTION_SOL_MAX_RT: Solicite Maximum Retry Time
#define DHCPV6_OPT_24  24  // OPTION_DOMAIN_LIST
#define DHCPV6_OPT_83  83  // OPTION_INF_MAX_RT
#define DHCPV6_OPT_17  17  // OPTION_VENDOR_OPTS
#define DHCPV6_OPT_31  31  // OPTION_SNTP_SERVERS
#define DHCPV6_OPT_15  15  // User Class Option
#define DHCPV6_OPT_16  16  // Vendor Class Option
#define DHCPV6_OPT_20  20  // Reconfigure Accept Option


//DHCPv4 Options
#define DHCPV4_OPT_42  42  // NTP Server Addresses
#define DHCPV4_OPT_43  43  // Vendor Specific Information
#define DHCPV4_OPT_58  58  // DHCP Renewal (T1) Time
#define DHCPV4_OPT_59  59  // DHCP Rebinding (T2) Time
#define DHCPV4_OPT_60  60  // Class Identifier
#define DHCPV4_OPT_61  61  // Client Identifier
#define DHCPV4_OPT_100 100 // IEEE 1003.1 TZ String
#define DHCPV4_OPT_122 122 // CableLabs Client Configuration
#define DHCPV4_OPT_125 125 // Vendor-Identifying Vendor-Specific Information
#define DHCPV4_OPT_242 242 // Private Use
#define DHCPV4_OPT_243 243 // Private Use
#define DHCPV4_OPT_END 255 // DHCP Option End - used to check if option is valid

/**********************************************************************
                ENUMERATION DEFINITIONS
**********************************************************************/

typedef  enum {
   HOST_CPU=0,
   PEER_CPU=1,
   NOT_SUPPORTED_CPU=3,
} RDK_CPUS; // RDK_CPUS

#ifndef PLAT_PROC_MEM_MAX_LEN
#define PLAT_PROC_MEM_MAX_LEN   40
#endif

/**********************************************************************
                STRUCTURE DEFINITIONS
**********************************************************************/
typedef  struct
_PLAT_PROC_MEM_INFO
{
    CHAR                            dramPath[PLAT_PROC_MEM_MAX_LEN];
    CHAR                            emmcPath1[PLAT_PROC_MEM_MAX_LEN];
    CHAR                            emmcPath2[PLAT_PROC_MEM_MAX_LEN];
    CHAR                            emmcPath3[PLAT_PROC_MEM_MAX_LEN];
}
PLAT_PROC_MEM_INFO, *PPLAT_PROC_MEM_INFO;

/**
 * @addtogroup PLATFORM_HAL_APIS
 * @{
 */

/**********************************************************************************
 *
 *  Subsystem level function prototypes 
 *
**********************************************************************************/
/* platform_hal_GetDeviceConfigStatus() function */
/**
* @description Get the device configuration status
*
* @param pValue - Device Configuration status, to be returned
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @sideeffect None
*/
INT platform_hal_GetDeviceConfigStatus(CHAR *pValue);

/* platform_hal_GetTelnetEnable() function */
/**
* @description Get telnet enable status
*
* @param pFlag - Telnet enable value, to be returned
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @sideeffect None
*/
INT platform_hal_GetTelnetEnable(BOOLEAN *pFlag);

/* platform_hal_SetTelnetEnable() function */
/**
* @description Enable/Disable telnet 
*
* @param Flag - Telnet enable value
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @sideeffect None
*/
INT platform_hal_SetTelnetEnable(BOOLEAN Flag);

/* platform_hal_GetSSHEnable() function */
/**
* @description Get SSH enable status 
*
* @param pFlag - SSH enable value, to be returned
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @sideeffect None
*/
INT platform_hal_GetSSHEnable(BOOLEAN *pFlag);

/* platform_hal_SetSSHEnable() function */
/**
* @description Enable/diable SSH
*
* @param Flag - SSH enable value
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @sideeffect None
*/
INT platform_hal_SetSSHEnable(BOOLEAN Flag);

/* platform_hal_GetSNMPEnable() function */
/**
* @description Get SNMP Enable value from the device
*
* @param pValue - SNMP enable value, to be returned
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @sideeffect None
*/
INT platform_hal_GetSNMPEnable(CHAR* pValue);

/* platform_hal_SetSNMPEnable() function */
/**
* @description Set SNMP Enable value
*
* @param pValue - SNMP enable value
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @sideeffect None
*/
INT platform_hal_SetSNMPEnable(CHAR* pValue);

/* platform_hal_GetWebUITimeout() function */
/**
* @description Get WebUI timeout value
*
* @param pValue - WebUI timeout value, to be returned
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @sideeffect None
*/
INT platform_hal_GetWebUITimeout(ULONG *pValue);

/* platform_hal_SetWebUITimeout() function */
/**
* @description Set WebUI timeout value
*
* @param value - WebUI timeout value
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @sideeffect None
*/
INT platform_hal_SetWebUITimeout(ULONG value);

/* platform_hal_GetWebAccessLevel() function */
/**
* @description Get Web Access Level 
*
* @param userIndex - User Index
* @param ifIndex   - Interface Index
* @param pValue    - Web Access Level, to be returned
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @sideeffect None
*/
INT platform_hal_GetWebAccessLevel(INT userIndex, INT ifIndex, ULONG *pValue);

/* platform_hal_SetWebAccessLevel() function */
/**
* @description Set Web Access Level 
*
* @param userIndex - User Index
* @param ifIndex   - Interface Index
* @param value     - Web Access Level
*
* <table>
* <caption id="multi_row">Lan Level Vs Index table</caption>
* <tr><th>Lan Level	<th>User Index	<th>Interface Index
* <tr><td>HomeUser_Lan_Level <td>1 <td>1
* <tr><td>HomeUser_RfCM_Level <td>1 <td>2
* <tr><td>HomeUser_Mta_Level <td>1 <td>16
* <tr><td>HomeUser_WanRG_Level <td>1 <td>40
* <tr><td>CusAdmin_Lan_Level <td>5 <td>1
* <tr><td>CusAdmin_RfCM_Level <td>5 <td>2
* <tr><td>CusAdmin_Mta_Level <td>5 <td>16
* <tr><td>CusAdmin_WanRG_Level <td>5 <td>40
* <tr><td>AdvUser_Lan_Level <td>10 <td>1
* <tr><td>AdvUser_RfCM_Level <td>10 <td>2
* <tr><td>AdvUser_Mta_Level <td>10 <td>16
* <tr><td>AdvUser_WanRG_Level <td>10 <td>40
* </table>
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @sideeffect None
*/
INT platform_hal_SetWebAccessLevel(INT userIndex, INT ifIndex, ULONG value);

/* platform_hal_PandMDBInit() function */
/**
* @description Initialize PandM DB (Database) 
*
* @param None
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @sideeffect None
*/
INT platform_hal_PandMDBInit(void);

/* platform_hal_DocsisParamsDBInit() function */
/**
* @description Initialize Platform HAL docsis parameters DB 
*
* @param None
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @sideeffect None
*/
INT platform_hal_DocsisParamsDBInit(void);

/* platform_hal_GetModelName() function */
/**
* @description Get device model name 
*
* @param pValue - Device Model Name, to be returned
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @sideeffect None
*/
INT platform_hal_GetModelName(CHAR* pValue);

/* platform_hal_GetRouterRegion() function */
/**
* @description Get router region
*
* @param pValue - Router region name, to be returned
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @sideeffect None
*/
INT platform_hal_GetRouterRegion(CHAR* pValue);

/* platform_hal_GetSerialNumber() function */
/**
* @description Get device serial number 
*
* @param pValue - Device Serial Number, to be returned
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @sideeffect None
*/
INT platform_hal_GetSerialNumber(CHAR* pValue);

/* platform_hal_GetHardwareVersion() function */
/**
* @description Get hardware version of the device
*
* @param pValue - Hardware version, to be returned
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @sideeffect None
*/
INT platform_hal_GetHardwareVersion(CHAR* pValue);

/* platform_hal_GetSoftwareVersion() function */
/**
* @description Get software version flashed in the device
*
* @param pValue  - Software version, to be returned
* @param maxSize - Maximum size of the Software version string
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @sideeffect None
*/
INT platform_hal_GetSoftwareVersion(CHAR* pValue, ULONG maxSize);

/* platform_hal_GetBootloaderVersion() function */
/**
* @description Get bootloader version flashed in the device
*
* @param pValue  - Bootloader version, to be returned
* @param maxSize - Maximum size of the bootloader version string
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @sideeffect None
*/
INT platform_hal_GetBootloaderVersion(CHAR* pValue, ULONG maxSize);

/* platform_hal_GetFirmwareName() function */
/**
* @description Get firmware image name flashed in the device
*
* @param pValue  - Firmware image name, to be returned
* @param maxSize - Maximum size of the bootloader version string
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @sideeffect None
*/
INT platform_hal_GetFirmwareName(CHAR* pValue, ULONG maxSize);

/* platform_hal_GetBaseMacAddress() function */
/**
* @description Get base MAC Address of the device
*
* @param pValue - Base MAC Address, to be returned
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @sideeffect None
*/
INT platform_hal_GetBaseMacAddress(CHAR *pValue);

/* platform_hal_GetHardware() function */
/**
* @description Get total flash size of the hardware 
*
* @param pValue - Total flash size, to be returned
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @sideeffect None
*/
INT platform_hal_GetHardware(CHAR *pValue);

/* platform_hal_GetHardware_MemUsed() function */
/**
* @description Get total used memory of the flash 
*
* @param pValue - Total used memory, to be returned
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @sideeffect None
*/
INT platform_hal_GetHardware_MemUsed(CHAR *pValue);

/* platform_hal_GetHardware_MemFree() function */
/**
* @description Get total availabe memory of the flash 
*
* @param pValue - Total available memory, to be returned
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @sideeffect None
*/
INT platform_hal_GetHardware_MemFree(CHAR *pValue);

/* platform_hal_GetTotalMemorySize() function */
/**
* @description Get total memory size of the DRAM (Dynamic Random Access Memory) 
*
* @param pulSize - Total memory size of DRAM, to be returned
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @sideeffect None
*/
INT platform_hal_GetTotalMemorySize(ULONG *pulSize);

/* platform_hal_GetUsedMemorySize() function */
/**
* @description Get total used memory of the DRAM (Dynamic Random Access Memory) 
*
* @param pulSize - Total used memory of DRAM, to be returned
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @sideeffect None
*/
INT platform_hal_GetUsedMemorySize(ULONG *pulSize);

/* platform_hal_GetFreeMemorySize() function */
/**
* @description Get total available memory of the DRAM (Dynamic Random Access Memory) 
*
* @param pulSize - Total available memory of DRAM, to be returned
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @sideeffect None
*/
INT platform_hal_GetFreeMemorySize(ULONG *pulSize);

/* platform_hal_GetFactoryResetCount() function */
/**
* @description Get total number of times factory reset has been done on the device
* \n Device.DeviceInfo.FactoryResetCount
*
* @param pulSize - Factory reset count, to be returned
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @sideeffect None
*/
INT platform_hal_GetFactoryResetCount(ULONG *pulSize);

/* platform_hal_ClearResetCount() function */
/**
* @description Reset factory reset count on the device
* \n Device.DeviceInfo.ClearResetCount
*
* @param bFlag - Reset Factory reset count, if TRUE
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @sideeffect None
*/
INT platform_hal_ClearResetCount(BOOLEAN bFlag);

/* platform_hal_getTimeOffSet() function */
/**
* @description Get time offset from the device
* \n Device.DeviceInfo.TimeOffset
*
* @param timeOffSet - Time offset, to be returned
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @sideeffect None
*/
INT platform_hal_getTimeOffSet(CHAR *timeOffSet);

/* platform_hal_SetDeviceCodeImageTimeout() function */
/**
* @description Set HW watchdog timeout value. Default value is 60 minutes.
*
* @param seconds - Hardware watchdog timeout value in seconds
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @sideeffect None
*/
INT platform_hal_SetDeviceCodeImageTimeout(INT seconds);

/* platform_hal_SetDeviceCodeImageValid() function */
/**
* @description Set Valid flag for firmware image flashed in the device.
*
* @param flag - Image valid flag
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @sideeffect None
*/
INT platform_hal_SetDeviceCodeImageValid(BOOLEAN flag);
/* platform_hal_getFactoryPartnerId function */
/**
* @description Get FactoryPartnerID from the the device.
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @sideeffect None
*/
INT platform_hal_getFactoryPartnerId(CHAR *pValue);

/* platform_hal_getFactoryCmVariant function */
/**
* @description Get FactoryCmVariant from the the device.
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @sideeffect None
*/
INT platform_hal_getFactoryCmVariant(CHAR *pValue);

/* platform_hal_setFactoryCmVariant function */
/**
* @description Set FactoryCmVariant from the the device.
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @sideeffect None
*/
INT platform_hal_setFactoryCmVariant(CHAR *pValue);

/**
 * @addtogroup PLATFORM_HAL_TYPES
 * @{
 */

#define LED_BUFFER_SIZE 3

typedef  enum {
   LED_WHITE=0,
   LED_YELLOW=1, //This is also classified as Amber from RDKB perspective
   LED_GREEN=2,
   LED_RED=3,
   LED_BLUE=4,
   LED_RED_AND_GREEN=5,
   LED_YELLOW_AND_GREEN= 6,
   NOT_SUPPORTED=7
} LED_COLOR; // LED_COLOR


typedef struct _LEDMGMT_PARAMS
{
#ifdef FEATURE_RDKB_LED_MANAGER
    char * led_name;
    char * led_param;
#endif
    LED_COLOR  LedColor;  //!< LED_COLOR
    INT  State;	//!< 0 for Solid, 1 for Blink
    INT  Interval;	//!< In case fs State is blink then interval per second
}
LEDMGMT_PARAMS, *PLEDMGMT_PARAMS;

/**
 * @}
 */

/**
 * @addtogroup PLATFORM_HAL_APIS
 * @{
 */

#ifdef FEATURE_RDKB_LED_MANAGER
/* platfom_hal_initLed : */
/**
* @description: Initialises HAL layer and return file pointer to config file
* 
* @param buffer to hold the config file path
* @return returns status on successful initialisation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*/
int platform_hal_initLed (char * config_file_name);
#endif

/* platform_hal_setLed function */
/**
* @description Set Led behavior of the device
*
* @param LED identification and control parameters
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @sideeffect None
*/
INT platform_hal_setLed(PLEDMGMT_PARAMS pValue);

/* platform_hal_getLed function */
/**
* @description Get Led behavior of the device at time of call
*
* @pValue The Current Led Buffer to be populated
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @sideeffect None
*/
INT platform_hal_getLed(PLEDMGMT_PARAMS pValue);


/* platform_hal_getFanSpeed function */
/**
* @description Get the fan speed in RPMs
*
* @param fanIndex      - Fan index starting from 0.
* @return FanSpeed in unsigned int
*/
UINT platform_hal_getFanSpeed(UINT fanIndex);


/* platform_hal_getFanRPM fuction */
/**
* @description Get the fan speed
*
* @param fanIndex      - Fan index starting from 0.
* @return FanRPM in unsigned int
*/
UINT platform_hal_getRPM(UINT fanIndex);


/* platform_hal_getRotorLock function */
/**
* @description Get the status of rotor lock
*
* @param fanIndex      - Fan index starting from 0.
* @return The status of the rotor lock
* @rtnval 1 if locked
* @rtnval 0 if not locked
* @rtnval -1 if value not applicable
*/
INT platform_hal_getRotorLock(UINT fanIndex);


/* platform_hal_getFanStatus function */
/**
* @description Get the fan status
*
* @param fanIndex      - Fan index starting from 0.
* @return the fan status
* @rtnval 1 if fan is enabled
* @rtnval 0 if fan disabled
*/
BOOLEAN platform_hal_getFanStatus(UINT fanIndex);

/* platform_hal_setFanMaxOverride function */
/**
* @description Set the fax to maximum speed
*
* @param bOverrideFlag - Boolean value to enable/disalbe fan tur run in highspeed
*
* @return RETURN_OK on success setting/unsetting the fan to run in high speed mode
*/
INT platform_hal_setFanMaxOverride(BOOLEAN bOverrideFlag, UINT fanIndex);

/* platform_hal_SetSNMPOnboardRebootEnable() function */
/**
* @description Set SNMP Onboard Reboot Enable value 
*  to allow or ignore SNMP reboot
*
* @param pValue - SNMP Onboard Reboot Enable value ("disable", "enable")
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*/
INT platform_hal_SetSNMPOnboardRebootEnable(CHAR* pValue);

/* platform_hal_GetMACsecEnable() function */
/**
* @description Get MACsec enable status
*
* @param ethPort - Ethernet port (zero-based)
* @param pFlag   - MACsec enable value, to be returned
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*/
INT platform_hal_GetMACsecEnable(INT ethPort, BOOLEAN *pFlag);


/* platform_hal_SetMACsecEnable() function */
/**
* @description Enable/Disable MACsec
*
* @param ethPort - Ethernet port (zero-based)
* @param Flag    - MACsec enable value
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*/
INT platform_hal_SetMACsecEnable(INT ethPort, BOOLEAN Flag);


/* platform_hal_GetMACsecOperationalStatus() function */
/**
* @description Get MACsec operation status
*
* @param ethPort - Ethernet port (zero-based)
* @param pFlag   - MACsec operation status value, to be returned
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*/
INT platform_hal_GetMACsecOperationalStatus(INT ethPort, BOOLEAN *pFlag);

/* platform_hal_StartMACsec() function */
/**
* @description Start MACsec - Call should be Blocking
*
* @param ethPort    - Ethernet port (zero-based)
* @param timeoutSec - MACsec Start Timeout (0 means retry forever)
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*/
INT platform_hal_StartMACsec(INT ethPort, INT timeoutSec);

/* platform_hal_StopMACsec() function */
/**
* @description Stop MACsec - Call should be Blocking
*
* @param ethPort    - Ethernet port (zero-based)
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*/
INT platform_hal_StopMACsec(INT ethPort);

/*  platform_hal_GetMemoryPaths() function : */
/**
*@description Get the device specific processors DRAM and eMMC paths
* @param RDK_CPUS index - Index to which processor/CPU to request. Host is the primary RDK CPU
* @param PPLAT_PROC_MEM_INFO *ppinfo - Ponter to get the return array
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
* @note HAL function need to allocate the array of PPLAT_PROC_MEM_INFO and return with ppinfo.
*
*/
INT platform_hal_GetMemoryPaths(RDK_CPUS index, PPLAT_PROC_MEM_INFO *ppinfo);

/*
 * dhcpv4_req_opt_to_hal - is used to fill options to request values
 * from platform
 */

typedef struct dhcp_opt_list {
    int dhcp_opt;
    char * dhcp_opt_val;
    struct dhcp_opt_list * next;
} dhcp_opt_list;

/* 
 * platform_hal_GetDhcpv4Options ()
 * @description: This function fills in 2 list, 1 for request option and 1 for send option.
 * @params     : v4_req_opt_list - list to be filled for request dhcp options 
 *               v4_send_opt_list - list to be filled for send dhcp options
 * @return     : RETURN_OK for success or RETURN_ERR for failure
 *
 */
INT platform_hal_GetDhcpv4_Options ( dhcp_opt_list ** req_opt_list, dhcp_opt_list ** send_opt_list);

/*
 * platform_hal_GetDhcpv6Options ()
 * @description: This function fills in 2 list, 1 for request option and 1 for send option.
 * @params     : v6_req_opt_list - list to be filled for request dhcp options
 *               v6_send_opt_list - list to be filled for send dhcp options
 * @return     : RETURN_OK for success or RETURN_ERR for failure
 *
 */
INT platform_hal_GetDhcpv6_Options ( dhcp_opt_list ** req_opt_list, dhcp_opt_list ** send_opt_list);

typedef  enum {
   PSM_UNKNOWN=0,
   PSM_AC,
   PSM_BATT,
   PSM_HOT,
   PSM_COOLED,
   PSM_NOT_SUPPORTED,
} PSM_STATE, *PPSM_STATE; // Power Saving Mode State

/* platform_hal_SetLowPowerModeState() function */
/**
* @description Set Low Power Mode State value. Hysteresis currently not accounted for before call.
*
* @param seconds - Low Power Mode State.
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @sideeffect None
*/
INT platform_hal_SetLowPowerModeState(PPSM_STATE pState);

INT platform_hal_getCMTSMac(CHAR *pValue);

#ifdef __cplusplus
}
#endif

#endif

/**
 * @}
 */

 
