/**
* @file mso_mgmt_hal.h
* @brief MSO Management HAL
*
* @description This header file gives the function call prototypes and structure definitions used for the RDK-Broadband hardware abstraction layer for 
MSO Management.
*/

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
#ifndef __MSO_MGMT_HAL_H__
#define __MSO_MGMT_HAL_H__

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

/**********************************************************************
                STRUCTURE DEFINITIONS
**********************************************************************/

typedef enum
{
    Invalid_PWD,
    Good_PWD,
    Unique_PWD,
    Expired_PWD, 
    TimeError
}
mso_pwd_ret_status;

/* mso_validatepwd() function */
/**
* @description Validate whether the password passed in matches the password of the day for mso user.
* @param pwd - a pointer to a buffer that was preallocated by the caller. 
* 
* @return The status of the operation.
* @retval mso_pwd_ret_status
            Invalid_PWD,
            Good_PWD,
            Unique_PWD,
            Expired_PWD, 
            TimeError
*
* @execution Synchronous.
* @sideeffect None.
*/
mso_pwd_ret_status mso_validatepwd(char *pwd);

/* mso_set_pod_seed : */
/**
* @description Sets the PoD seed for mso password validation.
* @param 
*    CHAR* - PoD seed
*
* @return the status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected.
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system 
* calls. It should probably just send a message to a driver event handler task. 
* Newer Broadband Devices MUST decrypt the seed on demand when this HAL is called.
*/
INT mso_set_pod_seed(char *);

/* mso_get_pod_seed : */
/**
* @description Gets the PoD seed for mso password validation,
* @param 
*    CHAR* pSeed - a pointer to a buffer that was preallocated by the caller.  This is where the output is written
*
* @return the status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected.
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function retrieves the decrypted seed set in the Config file 
*       and SNMP OID rdkbEncryptedClientSeed. pSeed for security reasons MUST be manually
*       overwritten after use.
*/
INT mso_get_pod_seed(char* pSeed);

#endif

