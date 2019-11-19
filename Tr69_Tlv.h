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
#ifndef _TR69TLV_H_
#define _TR69TLV_H_

/**
* @defgroup tr69_hal TR69-TLV HAL
*
* Telemetry Key fields and data fields are stored in the database as TLV (Tag, Length, Value).
*
* - Tag - uniquely identifies the field.
* - Length - gives the size (in number of bytes) of the data associated with the field.
* - Value - contains the actual data associated with the field stored in network byte ordering.
*
* @defgroup TR69_HAL_TYPES Tr69-TLV HAL Data Types
* @ingroup  tr69_hal
*
**/

/**
 * @addtogroup TR69_HAL_TYPES
 * @{
 */
typedef struct _Tr69TlvData{
    char URL[256];
    char Username[50];
    char Password[128];
    int EnableCWMP;
    int Tr69Enable;
    int URLchanged;
    int FreshBootUp;
    char ConnectionRequestUsername[50];
    char ConnectionRequestPassword[128];
    int AcsOverRide;
	
}Tr69TlvData;

#endif
/**
 * @}
 */
