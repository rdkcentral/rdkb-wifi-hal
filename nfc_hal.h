/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2021 RDK Management
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

#ifndef _NFC_HAL_H
#define _NFC_HAL_H

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

 /**
  * The following enum defines success / error codes for the HAL APIs.
  */
 typedef enum {
    e_OK = 0,
    e_Undefined,
    e_HandleInUse,
    e_HandleNotExist,
    e_AddressOutOfRange,
    e_SizeOutOfRange,
    e_CallbackExist,
    e_CallbackNotExist,
    e_LockTimeout,
    e_LockNotHeld,
    e_Err
} nfc_err_t;

 /**
  * The following type definitions and macros are used to inform the capabilities of an underlying NFC device / driver.
  */
 #define CAP_NFC_FORUM_TAG_ANY 0x00000000
#define CAP_NFC_FORUM_TAG_TYPE1 0x00000001
#define CAP_NFC_FORUM_TAG_TYPE2 0x00000002
#define CAP_NFC_FORUM_TAG_TYPE3 0x00000004
#define CAP_NFC_FORUM_TAG_TYPE4 0x00000008

typedef struct {
    UINT tag_flags;
    UINT memory_size;
    UINT memory_used;
} nfc_caps_t;

/**
 * The following enum defines Status codes for the underlying NFC device/driver.
 */
typedef enum {
    Disabled = 0,
    Enabled
} nfc_status_t;

/**
 * The following type definitions are used to hold information for memory mappings.
 */
typedef struct {
    UINT handle;
    CHAR* mem_ptr;
    UINT base_addr;
    UINT size;
} nfc_map_t; // a single mapping

typedef struct nfc_map_list_t {
    nfc_map_t* mapping;
    struct nfc_map_list_t* next;
} nfc_map_list_t; // list of all mappings

/**
 * The following enum defines callback events.
 */
typedef enum {
    DataRead = 0,
    DataWrite
} nfc_event_t;

typedef void (*callback_t)(nfc_event_t);


/**
 * @brief Reset the NFC device and driver clearing all state and setting back to power on defaults.  Any memory mappings existing prior to
calling this API shall be removed with all resources freed.
*/
nfc_err_t NFC_reset(void);

/**
 * @brief Toggle the enable / disable of the NFC device.  Disable does not clear all state nor does it remove any active mappings.  Disable only
prevents the local NFC device from participating in any further NFC interactions with external devices.
*
* @param Enable boolean value indicates enable/disable the NFC device.
* @return e_Ok on success else return corresponding error type.
*/
nfc_err_t NFC_enable(BOOLEAN enable);

/**
 * @brief Returns information about the capabilities of the underlying NFC device.
 *
 * @param caps Pointer to nfc_caps_t structure to store capabilities.
 * @return e_Ok on success else return corresponding error type.
 */
nfc_err_t NFC_get_caps(nfc_caps_t* caps);

/**
 * @brief Returns basic status about the NFC device.
 *
 * @return Returns the enable or disable status as enum type of nfc_status_t
 */
nfc_status_t NFC_get_status(void);

/**
 * @brief Retrieves pointer to mapped device memory as specified by the input parameters.
 *
 * @param handle [IN] A unique ID provided by the caller which is used by the HAL to associate with the mapped memory
 * @param mem_ptr [OUT] A pointer to the mapped memory that the caller may use to read/write
 * @param base_addr [IN] Specifies the base address of NFC device user memory to map
 * @param size [IN] Specifies how many bytes from the provided base_addr to map
 *
 * @return nfc_err_t [RET] Success or error condition
 */
nfc_err_t NFC_map_memory(UINT handle, unsigned char* mem_ptr, UINT base_addr, UINT size);

/**
 * @brief Instructs the driver to unmap the memory specified by the handle.  After this operation completes,  any references or pointers for the
previously mapped region shall be invalid and must no longer be used.
 *
 * @param handle [IN] ID provided by the caller specifying which region to unmap
 *
 * @return nfc_err_t [RET] Success or error condition
 */
nfc_err_t NFC_unmap_memory(UINT handle);

/**
 * @brief Instructs the driver to sync (apply) the content of the mapped memory to the device.   This makes it easier for the driver to know when
to commit the memory content to the physical device and allows any client of the HAL to control when that occurs.
 *
 * @param handle [IN] ID provided by the caller specifying which mapped region to synchronise / commit contents to the device
 *
 * @return nfc_err_t [RET] Success or error condition
 */
nfc_err_t NFC_sync_memory(UINT handle);

/**
 * @brief Returns a linked list of active mappings.
 *
 * @param maplist [OUT] Head of list of active mappings
 *
 * @return nfc_err_t [RET] Success or error condition
 */
nfc_err_t NFC_get_maplist(nfc_map_list_t* maplist);

/**
 * @brief The NFC HAL shall support asynchronous notifications through the registration of a callback handler. The callback mechanism shall
 * inform the reason for the notification which is alternatively referred to as an ‘event’.
 *
 * @param function [IN] The function to be called to handle notifications
 *
 * @return nfc_err_t [RET] Success or error condition
 */
nfc_err_t NFC_register_callback(callback_t function);

/**
 * @brief Get SSID Name of radio.
 *
 * @param ssid [OUT] String to store ssid name
 * @param ssid_length [IN] Length of the string to hold the ssid name
 *
 * @return nfc_err_t [RET] Success or error condition
 */
nfc_err_t NFC_get_Ssid(char* ssid, int ssid_length);

/**
 * @brief Get Network key (password/passphrase) of radio.
 *
 * @param networkkey [OUT] String to store network key
 * @param key_length [IN] Length of the string to hold the network key
 *
 * @return nfc_err_t [RET] Success or error condition
 */
nfc_err_t NFC_get_NetworkKey(char* networkKey, int key_length);

/**
 * @brief Get to know the status of WPS feature supported in platform
 *
 * @return TRUE if supports else return FALSE
 */
BOOLEAN NFC_doesWpsSupported(void);

/**
 * @brief Get to know the status of WPA3 feature supported in platform
 *
 * @return TRUE if supports else return FALSE
 */
BOOLEAN NFC_doesWpa3Supported(void);
#endif
