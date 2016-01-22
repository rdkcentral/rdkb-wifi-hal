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

    module: platform_hal.h

        For CCSP Component:  CcspCMAgent

    ---------------------------------------------------------------

    copyright:

        Cisco Systems, Inc., 2014
        All Rights Reserved.

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
INT platform_hal_GetDeviceConfigStatus(CHAR *pValue);

INT platform_hal_GetTelnetEnable(BOOLEAN *pFlag);
INT platform_hal_SetTelnetEnable(BOOLEAN Flag);
INT platform_hal_GetSSHEnable(BOOLEAN *pFlag);
INT platform_hal_SetSSHEnable(BOOLEAN Flag);

INT platform_hal_GetSNMPEnable(CHAR* pValue);
INT platform_hal_SetSNMPEnable(CHAR* pValue);
INT platform_hal_GetWebUITimeout(ULONG *pValue);
INT platform_hal_SetWebUITimeout(ULONG value);
INT platform_hal_GetWebAccessLevel(INT userIndex, INT ifIndex, ULONG *pValue);
INT platform_hal_SetWebAccessLevel(INT userIndex, INT ifIndex, ULONG value);

INT platform_hal_PandMDBInit(void);
INT platform_hal_DocsisParamsDBInit(void);
INT platform_hal_GetModelName(CHAR* pValue);
INT platform_hal_GetSerialNumber(CHAR* pValue);
INT platform_hal_GetHardwareVersion(CHAR* pValue);
INT platform_hal_GetSoftwareVersion(CHAR* pValue, ULONG maxSize);
INT platform_hal_GetBootloaderVersion(CHAR* pValue, ULONG maxSize);
INT platform_hal_GetFirmwareName(CHAR* pValue, ULONG maxSize);
INT platform_hal_GetBaseMacAddress(CHAR *pValue);
INT platform_hal_GetHardware(CHAR *pValue);
INT platform_hal_GetHardware_MemUsed(CHAR *pValue);
INT platform_hal_GetHardware_MemFree(CHAR *pValue);
INT platform_hal_GetTotalMemorySize(ULONG *pulSize);
INT platform_hal_GetUsedMemorySize(ULONG *pulSize);
INT platform_hal_GetFreeMemorySize(ULONG *pulSize);
INT platform_hal_GetFactoryResetCount(ULONG *pulSize);
INT platform_hal_ClearResetCount(BOOLEAN bFlag);
#endif
 
