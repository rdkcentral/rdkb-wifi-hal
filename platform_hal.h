/*
 * If not stated otherwise in this file or this component's Licenses.txt file the
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

        NOTE:
        THIS VERSION IS AN EARLY DRAFT.
        TESTING HAS NOT YET BEEN COMPLETED.  
       
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

/**********************************************************************
               CONSTANT DEFINITIONS
**********************************************************************/

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
* @param ifIndex - Interface Index
* @param pValue - Web Access Level, to be returned
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
* @param ifIndex - Interface Index
* @param value - Web Access Level
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
* @param pValue - Software version, to be returned
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
* @param pValue - Bootloader version, to be returned
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
* @param pValue - Firmware image name, to be returned
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
* @description Set Valid flag for firmware image flashed in the device
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
* @description Get FactoryPartnerID from the the device
*
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
* @description Get FactoryCmVariant from the the device
*
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
* @description Set FactoryCmVariant from the the device
*
*
* @return The status of the operation
* @retval RETURN_OK if successful
* @retval RETURN_ERR if any error is detected
*
* @sideeffect None
*/
INT platform_hal_setFactoryCmVariant(CHAR *pValue);
#endif
 
