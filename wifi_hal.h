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

    module: wifi_hal.h

        For CCSP Component:  Wifi_Provisioning_and_management

    ---------------------------------------------------------------

    copyright:

        Cisco Systems, Inc., 2014
        All Rights Reserved.

    ---------------------------------------------------------------

    description:

        This header file gives the function call prototypes and 
        structure definitions used for the RDK-Broadband 
        Wifi hardware abstraction layer

        NOTE:
        THIS VERSION IS AN EARLY DRAFT INTENDED TO GET COMMENTS FROM COMCAST.
        TESTING HAS NOT YET BEEN COMPLETED.  
       
    ---------------------------------------------------------------

    environment:

        This HAL layer is intended to support Wifi drivers 
        through an open API.  The current implementation created
        below this HAL supports Qualcomm / Atheros Wifi.
        Changes may be needed to support other Wifi enviornments.

    ---------------------------------------------------------------

    author:

        Cisco

**********************************************************************/

#ifndef __WIFI_HAL_H__
#define __WIFI_HAL_H__


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


/**********************************************************************
                STRUCTURE DEFINITIONS
**********************************************************************/

typedef struct _wifi_basicTrafficStats
{
     ULONG wifi_BytesSent;
     ULONG wifi_BytesReceived;
     ULONG wifi_PacketsSent;
     ULONG wifi_PacketsReceived;
     ULONG wifi_Associations; 	
} wifi_basicTrafficStats_t;

typedef struct _wifi_trafficStats
{
     ULONG wifi_ErrorsSent;
     ULONG wifi_ErrorsReceived;
     ULONG wifi_UnicastPacketsSent;
     ULONG wifi_UnicastPacketsReceived;
     ULONG wifi_DiscardedPacketsSent;
     ULONG wifi_DiscardedPacketsReceived;
     ULONG wifi_MulticastPacketsSent;
     ULONG wifi_MulticastPacketsReceived;
     ULONG wifi_BroadcastPacketsSent;
     ULONG wifi_BroadcastPacketsRecevied;
     ULONG wifi_UnknownPacketsReceived;
} wifi_trafficStats_t;

typedef struct _wifi_device
{
     UCHAR wifi_devMacAddress[6];
     CHAR wifi_devIPAddress[64];
     BOOL wifi_devAssociatedDeviceAuthentiationState;
     INT  wifi_devSignalStrength;
     INT  wifi_devTxRate;
     INT  wifi_devRxRate;
} wifi_device_t;


/**********************************************************************************
 *
 *  Wifi Subsystem level function prototypes 
 *
**********************************************************************************/

/* wifi_init() function */
/**
* Description: Initializes the Wifi subsystem.  This includes initilization of all 
*  radios.  Implementation specifics may dictate what is actualy initializes since 
*  different hardware implementations may have different requirements.
*  Parameters : None
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
INT wifi_init();                                                    // Initializes the wifi subsystem (all radios)

/* wifi_reset() function */
/**
* Description: Resets the Wifi subsystem.  This includes reset of all AP varibles.
*  Implementation specifics may dictate what is actualy reset since 
*  different hardware implementations may have different requirements.
*  Parameters : None
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
INT wifi_reset();                                                   // resets the wifi subsystem, deletes all APs

/* wifi_down() function */
/**
* Description: 
*  Turns off transmit power to all radios.
*  Implementation specifics may dictate some functionality since 
*  different hardware implementations may have different requirements.
*  Parameters : None
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
INT wifi_down();                                                    // turns off transmit power for the entire Wifi subsystem, for all radios

/* wifi_factoryReset() function */
/**
* Description: 
*  Resets Implementation specifics may dictate some functionality since 
*  different hardware implementations may have different requirements.
*  Parameters : None
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
INT wifi_factoryReset();                                            // clears internal variables to implement a factory reset of the wifi subsystem

/* wifi_factoryResetRadios() function */
/**

* Description: 
*  Resets Implementation specifics may dictate some functionality since 
*  different hardware implementations may have different requirements.
*  Parameters : None
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
INT wifi_factoryResetRadios();

/* wifi_createInitialConfigFiles() function */
/**
* Description: 
*  This function creates wifi configuration files.  The format
*  and content of these files are implementation dependent.  This function call is 
*  used to trigger this task if necessary. Some implementations may not need this 
*  function. If an implementation does not need to create config files the function call can 
*  do nothing and return RETURN_OK. 
*  Parameters : None
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
INT wifi_createInitialConfigFiles();                                // creates initial implementation dependent configuration files that are later used for variable storage.  Not all implementations may need this function.  If not needed for a particular implementation simply return no-error (0)


/**********************************************************************************
 *
 *  Wifi radio level function prototypes
 *
**********************************************************************************/

/* wifi_initRadio() function */
/**
* Description: This function call initializes the specified radio.
*  Implementation specifics may dictate the functionality since 
*  different hardware implementations may have different initilization requirements.
* Parameters : radioIndex - The index of the radio. First radio is index 0. 2nd radio is index 1   - type INT
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
INT wifi_initRadio(INT radioIndex);                                 // Initializes the specified radio, 0 is the first radio index, 1 is the 2nd radio index


/* wifi_getBaseBSSID() function */
/**
* Description: This function call outputs a 32 byte or less string with the base mac address of this radio.
*  Each radio may support mulitiple BSSIDs with each BSSID having a mac address.  This funtion call  
*  outputs the base (lowest) mac address assocated with this radio.
* Parameters : 
*  radioIndex - The index of the radio. First radio is index 0. 2nd radio is index 1   - type INT
*  *output_string - a pointer to a 32 buffer that was preallocated by the caller.  This is where the output is written
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
INT wifi_getBaseBSSID(INT radioIndex, CHAR *output_string);         // Outputs a 32 byte or less status string with the base mac address of the radio.  The string buffer must be pre-allocated by caller.


/* wifi_getMaxBitRate() function */
/**
* Description: 
*  This fuction outputs a 32 byte or less string indicating the max bit rate of this radio in bps.
*  Parameters :
*  radioIndex - The index of the radio. First radio is index 0. 2nd radio is index 1   - type INT
*  *output_string - a pointer to a 32 buffer that was preallocated by the caller.  This is where the output is written
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
INT wifi_getMaxBitRate(INT radioIndex, CHAR *output_string);        // Outputs a 32 byte or less string indicating the max bit rate.  String buffer must be preallocated.

/* wifi_getChannel() function */
/**
* Description: 
*  This fuction outputs a value indicating the channel number currently in use on this radio
*  Parameters :
*  radioIndex - The index of the radio. First radio is index 0. 2nd radio is index 1   - type INT
*  *output_ulong - a pointer to a unsigned long value that was preallocated by the caller.  This is where the output is written
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
INT wifi_getChannel(INT radioIndex,ULONG *output_ulong);            // outputs the channel currently in use on this radio 

/* wifi_setChannel() function */
/**
* Description: 
*  This fuction sets a driver internal paramater correspdonding to the channel number to use on this radio
*  Parameters :
*  radioIndex - The index of the radio. First radio is index 0. 2nd radio is index 1   - type INT
*  channel - a unsigned long value that is used to pass the channel number
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
INT wifi_setChannel(INT radioIndex, ULONG channel);                 // sets an enviornment variable for this radio to a specfic channel


/* wifi_getAutoChannelEnable() function */
/**
* Description: 
*  This function outputs a bool value indicating if auto channel selection is currently in use on this radio
*  Parameters :
*  radioIndex - The index of the radio. First radio is index 0. 2nd radio is index 1   - type INT
*  *output_bool - a pointer to a bool value that was preallocated by the caller.  This is where the output is written. 1 == enabled, 0 == disabled
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
INT wifi_getAutoChannelEnable(INT radioIndex, BOOL *output_bool);   // gets the current status of the auto channel enable flag 1 == enabled, 0 == disabled

/* wifi_setAutoChannelEnable() function */
/**
* Description: 
*  This function enables or disables a driver level variable to indicate if auto channel selection is enabled on this radio
*  Parameters :
*  radioIndex - The index of the radio. First radio is index 0. 2nd radio is index 1  - type INT
*  enable - a BOOL value that enables auto channel selection on this radio.  1 == enabled, 0 == disabled
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
INT wifi_setAutoChannelEnable(INT radioIndex, BOOL enable);         // sets the auto channel enable enviornemnt flag cooresponding to this radio, 1 == enabled, 0 == disabled

/* wifi_getStandard() function */
/**
* Description: 
*  This function outputs the PHY level standards supported by this radio.
*  Parameters :
*  radioIndex - The index of the radio. First radio is index 0. 2nd radio is index 1   - type INT
*  *output_string - a pointer to a string that was preallocated by the caller.  This is where the output is written.
*     valid strings are formated as "a", "b", "g"(b&g clients),"g-"(only g),"n","ac", 
*  *gOnly - a pointer to a BOOL value.  1 indicates that the radio is in g-only mode, 0 indicates not in g-only mode
*  *nOnly - a pointer to a BOOL value.  1 indicates that the radio is in n-only mode, 0 indicates not in n-only mode
*  *acOnly - a pointer to a BOOL value.  1 indicates that the radio is in ac-only mode, 0 indicates not in ac-only mode
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
INT wifi_getStandard(INT radioIndex, CHAR *output_string, BOOL *gOnly, BOOL *nOnly, BOOL *acOnly); // Outputs a string formated as "a", "b", "g"(b&g clients),"g-"(only g),"n","ac", outputs BOOL flags for specific modes

/* wifi_getPossibleChannels() function */
/**
* Description: This function call outputs a 128 byte or less string with the supported radio channels on this radio.
*  Format is comma separated list of possible channels. String must be preallocaated by caller.
* Parameters : 
*  radioIndex - The index of the radio. First radio is index 0. 2nd radio is index 1   - type INT
*  *output_string - a pointer to a 128 buffer that was preallocated by the caller.  This is where the output is written
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
INT wifi_getPossibleChannels(INT radioIndex, CHAR *output_string);  // outputs a 128 byte or less string.  Format is comma separated list of possible channels. String must be preallocaated by caller.

/*******
 * NOTE: FILE FORMATING AND CREATION OF COMMENTS IS A WORK IN PROGRESS BELOW THIS POINT
**********/

INT wifi_setRadioEnable(INT radioIndex, BOOL enable);               // sets an enviornment variable that indicates radio enable status.  1 enables, 0 disables radio
INT wifi_getRadioEnable(INT radioIndex, BOOL *output_bool);         // outputs 1 if radio is enabled, outputs 0 if radio is disabled
INT wifi_getRadioActive(INT radioIndex, BOOL *output_bool);         // outputs 1 if radio is active, outputs 0 if radio is not active
INT wifi_getTransmitPower(INT radioIndex, ULONG *output_ulong);     // outputs the transmit power in dBm
INT wifi_setTransmitPower(INT radioIndex, ULONG TransmitPower);     // sets the transmit power in dBm in the hardware
INT wifi_setDTIMInterval(INT apIndex, INT dtimInterval);            // sets the Delivery Traffic Indication Message Interval for the radio used by this ap, pushes this setting to the hardware
INT wifi_setCtsProtectionEnable(INT apIndex, BOOL enable);          // enables CTS protection for the radio used by this AP, pushes this setting to the hardware
INT wifi_setObssCoexistenceEnable(INT apIndex, BOOL enable);        // enables OBSS Coexistence - fall back to 20MHz if necessary for the radio used by this ap, pushes this setting to the hardware
INT wifi_setFragmentationThreshold(INT apIndex, UINT threshold);    // sets the fragmentation threshold in bytes for the radio used by this ap, pushes this setting to the hardware
INT wifi_getChannelMode(INT radioIndex, CHAR *output_string);	  // outputs to a 32 byte string, must be pre-allocataed by caller.  String will contain either "20","40" or "80.  If 40 then extension channel frequency will be indicated by either "PLUS" or "MINUS"
INT wifi_setChannelMode(INT radioIndex, CHAR *channelMode, BOOL gOnlyFlag, BOOL nOnlyFlag, BOOL acOnlyFlag);  // sets the channel mode enviornment variable.  32 charater max string may contain "11A",11B","11G","11NGHT20","11NAHT20","11NGHT40PLUS","11NGHT40MINUS","11NAHT40PLUS","11NAHT40MINUS","11ACVHT20","11ACVHT40PLUS","11ACVHT40MINUS","11ACVHT80"  
INT wifi_getCountryCode(INT radioIndex, CHAR *output_string);       // outputs the country code to a max 64 character string
INT wifi_setSTBCEnable(INT radioIndex, BOOL STBC_Enable);           // enable STBC mode in the hardwarwe, 0 == not enabled, 1 == enabled 
INT wifi_getAMSDUEnable(INT radioIndex, BOOL *output_bool);         // outputs A-MSDU enable status, 0 == not enabled, 1 == enabled 
INT wifi_setAMSDUEnable(INT radioIndex, BOOL amsduEnable);          // enables A-MSDU in the hardware, 0 == not enabled, 1 == enabled  
INT wifi_setShortGuardInterval(INT radioIndex, BOOL enable);        // enables short guard interval mode on the specified radio, 0 == not enabled, 1 == enabled 
INT wifi_getTxChainMask(INT radioIndex, INT *output_int);            // outputs the number of Tx streams
INT wifi_setTxChainMask(INT radioIndex, INT numStreams);            // sets the number of Tx streams to an enviornment variable  
INT wifi_getRxChainMask(INT radioIndex, INT *output_int);            // outputs the number of Rx streams
INT wifi_setRxChainMask(INT radioIndex, INT numStreams);            // sets the number of Rx streams to an enviornment variable
INT wifi_getChannelsInUse(INT radioIndex, CHAR *output_string);     // outputs the channels in use
INT wifi_scanApChannels(INT radioIndex, CHAR *scanData);            // outputs the scan data
INT wifi_getWifiEnableStatus(INT radioIndex, BOOL *output_bool);    // outputs the current state of the internal enviornement variable that indicates enable/disable status. enabled==1 or disabled==0
INT wifi_setWifiEnableStatus(INT radioIndex, BOOL enabled);         // sets the internal enviornment variable for wifi enable/disable
INT wifi_getSupportedFrequencyBands(INT radioIndex, CHAR *output_string);  // Outputs supported frequency bands to a max 10 character string
INT wifi_pushDefaultValues(INT radioIndex);                         // pushes the default values for this radio to the hardware. 
INT wifi_pushChannel(INT radioIndex, UINT channel);                 // push the channel number setting to the hardware
INT wifi_pushChannelMode(INT radioIndex);                           // push the channel mode enviornment variable that is set by "wifi_setChannelMode()" to the hardware
INT wifi_pushTxChainMask(INT radioIndex);                           // push the enviornment varible that is set by "wifi_setTxChainMask()" to the hardware
INT wifi_pushRxChainMask(INT radioIndex);                           // push the enviornment varible that is set by "wifi_setRxChainMask()" to the hardware

/**********************************************************************************
 *
 *  Access Point level function prototypes (aka Virtual Access Point)
 *
**********************************************************************************/

INT wifi_createAp(INT apIndex, INT radioIndex, CHAR *essid, BOOL hideSsid);  // creates a new ap and pushes these parameters to the hardware
INT wifi_deleteAp(INT apIndex);                                     // deletes this ap entry on the hardware, clears all internal variables associaated with this ap
INT wifi_setEnable(INT apIndex, BOOL enable);                       // sets the AP enable status variable for the specified ap.
INT wifi_getEnable(INT apIndex, BOOL *output_bool);                 // Outputs the state of the internal variable that is set by wifi_setEnable().  
INT wifi_getApEnable(INT apIndex, BOOL *enableFlag);                // Outputs the actual status of the specified ap. 0 == not enabled, 1 == enabled 
INT wifi_getEnableOnLine(INT apIndex, BOOL *output_bool);           // Outputs a bool that indicates on the state of the Enable OnLine variable for this ap.
INT wifi_setEnableOnLine(INT apIndex, BOOL enabled);                // sets the on line enable variable for this ap.  If set the ap will not be enabled until all required network connetions are ready.
INT wifi_ifConfigUp(INT apIndex);                                   // sets internal variables to indiate that the ap is enabled, specific internal variabls are implementation dependendent,
INT wifi_ifConfigDown(INT apIndex);									// 
INT wifi_getStatus(INT apIndex, CHAR *output_string);               // Outputs a 32 byte or less AP status string.  The string buffer must be pre-allocated by caller.
INT wifi_getName(INT apIndex, CHAR *output_string);                 // Outputs a 16 byte or less name assocated with the AP.  String buffer must be pre-allocated by the caller

INT wifi_getSSID(INT apIndex, CHAR *output_string);                 // Outputs a 32 byte or less string indicating the SSID name.  Sring buffer must be preallocated by the caller.
INT wifi_setSSID(INT apIndex, CHAR *ssid_string);                   // accepts a max 32 byte string and sets an internal variable to the SSID name 
INT wifi_pushSSID(INT apIndex, CHAR *ssid);                         // push the ssid name to the hardware

INT wifi_getSsidAdvertisementEnable(INT apIndex, BOOL *output_bool);// outputs a 1 if SSID on the AP is enabled, else ouputs 0
INT wifi_setSsidAdvertisementEnable(INT apIndex, BOOL enable);      // sets an internal variable for ssid advertisement.  Set to 1 to enable, set to 0 to disable
INT wifi_pushSsidAdvertisementEnable(INT apIndex, BOOL enable);     // push the ssid advertisement enable variable to the hardware

INT wifi_getBeaconType(INT apIndex, CHAR *output_string);           // Outputs a 32 byte or less string indicating the beacon type as "None", "Basic", "WPA, "11i", "WPAand11i"
INT wifi_setBeaconType(INT apIndex, CHAR *beaconTypeString);        // Sets the beacon type enviornment variable. Allowed input strings are "None", "Basic", "WPA, "11i", "WPAand11i"

INT wifi_setBasicEncryptionMode(INT apIndex, CHAR *encMode);        // sets an enviornment variable for the basic encryption mode.  Valid encMode strings are "None" or "WEPEncryption"
INT wifi_setBasicAuthenticationMode(INT apIndex, CHAR *authMode);   // sets an enviornment variable for the authMode. Valid strings are "None", "EAPAuthentication" or "SharedAuthentication"
INT wifi_getWpaEncryptoinMode(INT apIndex, CHAR *output_string);    // ouputs up to a 32 byte string as either "TKIPEncryption", "AESEncryption", or "TKIPandAESEncryption"
INT wifi_setWpaEncryptionMode(INT apIndex, CHAR *encMode);          // sets the encyption mode enviornment variable.  Valid string format is "TKIPEncryption", "AESEncryption", or "TKIPandAESEncryption"
INT wifi_getWpaRekeyInterval(INT apIndex, INT *output_int);         // outputs the rekey interval
INT wifi_setWpaRekeyInterval(INT apIndex, INT rekeyInterval);       // sets the internal variable for the rekey interval

INT wifi_getWepKey(INT apIndex, INT keyIndex, CHAR *output_string); // output_string must be pre-allocated as 128 character string by caller
INT wifi_setWepKey(INT apIndex, INT keyIndex, CHAR *WepKey);        // sets an enviornment variable for the WepKey.  WepKey string must be a maximum of 128 characters
INT wifi_pushWepKey(INT apIndex, INT keyIndex);                     // push the Wep key to the hardware
INT wifi_getApWepKeyIndex(INT apIndex, ULONG *output_ulong);         // Outputs the WEP key index (1-4) for this AP
INT wifi_setApWepKeyIndex(INT apIndex, ULONG output_ulong);          // Sets an enviornment variable for the WEP key index (1-4) for this AP
INT wifi_pushWepKeyIndex(INT apIndex, UINT keyIndex);               // push the wep key index to the hardware

INT wifi_removeSecVaribles(INT apIndex);                            // deletes internal security varable settings for this ap
INT wifi_disableEncryption(INT apIndex);                            // changes the hardware settings to disable encryption on this ap
INT wifi_setAuthMode(INT apIndex, INT mode);                        // set the authorization mode on this ap

INT wifi_getBasicTrafficStats(INT apIndex, wifi_basicTrafficStats_t *output_struct);  // outputs basic traffic stats per AP
INT wifi_getWifiTrafficStats(INT apIndex, wifi_trafficStats_t *output_struct); // outputs more detailed traffic stats per AP
INT wifi_getNumDevicesAssociated(INT apIndex, ULONG *output_ulong); // outputs the number of stations assocated per AP
INT wifi_getAllAssociatedDeviceDetail(INT apIndex, ULONG *output_ulong, wifi_device_t ***output_struct); // Outputs the number of assocated devcies and the device details
INT wifi_getAssociatedDeviceDetail(INT apIndex, INT devIndex, wifi_device_t *output_struct); // Outputs device details of a single device with index devIndex 

INT wifi_kickAssociatedDevice(INT apIndex, wifi_device_t *device);  // manually removes any active wi-fi association with the device specified on this ap


INT wifi_getPreSharedKey(INT apIndex, CHAR *output_string);         // output_string must be pre-allocated as 64 character string by caller
INT wifi_setPreSharedKey(INT apIndex, CHAR *preSharedKey);          // sets an enviornment variable for the psk. Input string preSharedKey must be a maximum of 64 characters
INT wifi_getKeyPassphrase(INT apIndex, CHAR *output_string);        // outputs the passphrase, maximum 63 characters
INT wifi_setKeyPassphrase(INT apIndex, CHAR *passPhrase);           // sets the passphrase enviornment variable, max 63 characters
INT wifi_getWpsEnable(INT apIndex, BOOL *output_bool);              // outputs the WPS enable state of this ap in output_bool 
INT wifi_setWpsEnable(INT apIndex, BOOL enableValue);               // sets the WPS enable enviornment variable for this ap to the value of enableValue, 1==enabled, 0==disabled
INT wifi_getWpsDevicePIN(INT apIndex, ULONG *output_ulong);         // outputs the pin value, ulong_pin must be allocated by the caller
INT wifi_setWpsDevicePIN(INT apIndex, ULONG pin);                   // set an enviornment variable for the WPS pin for the selected AP
INT wifi_getWpsConfigMethodsEnabled(INT apIndex, CHAR *output_string); // Outputs a common separated list of the enabled WPS config methods, 64 bytes max
INT wifi_setWpsConfigMethodsEnabled(INT apIndex, CHAR *methodString); // sets an enviornment variable that specifies the WPS configuration method(s).  methodString is a comma separated list of methods "USBFlashDrive","Ethernet","Label","Display","ExternalNFCToken","NFCInterface","PushButton","Keypad"
INT wifi_getWpsConfigurationState(INT apIndex, CHAR *output_string); // Output string is either Not configured or Configured, max 32 characters
INT wifi_setWpsEnrolleePin(INT apIndex, CHAR *pin);                 // sets the WPS pin for this AP
INT wifi_setWpsButtonPush(INT apIndex);                             // This function is called when the WPS push button has been pressed for this AP
INT wifi_cancelWPS(INT apIndex);                                    // cancels WPS mode for this AP

INT wifi_setWmmEnable(INT apIndex, BOOL enable);                    // enables/disables WMM on the hardwawre for this AP.  enable==1, disable == 0
INT wifi_setWmmUapsdEnable(INT apIndex, BOOL enable);               // enables/disables Automatic Power Save Delivery on the hardwarwe for this AP
INT wifi_setWmmOgAckPolicy(INT apIndex, INT class, BOOL ackPolicy); // sets the wmm ack polity on the hardware. AckPolicy false means donot acknowledge, true means acknowledge

INT wifi_getIndexFromName(CHAR *inputSsidString, INT *output_int);   // outputs the index number in that corresponds to the ssid string

INT wifi_setBeaconInterval(INT apIndex, INT beaconInterval);        // sets the beacon interval on the hardware for this AP
INT wifi_setRtsThreshold(INT apIndex, UINT threshold);              // sets the packet size threshold in bytes to apply RTS/CTS backoff rules, pushes this setting to the hardware

INT wifi_setMaxStations(INT apIndex, INT maxStations);              // sets the hardware for the maximum number of stations that can connect to each AP
INT wifi_getRadioIndex(INT apIndex, INT *output_int);                // outputs the radio index for the specified ap
INT wifi_setRadioIndex(INT apIndex, INT radioIndex);                // sets the radio index for the specific ap

INT wifi_addAclDevice(INT apIndex, CHAR *DeviceMacAddress);         // adds the mac address to the filter list
INT wifi_delAclDevice(INT apIndex, CHAR *DeviceMacAddress);         // deletes the mac address from the filter list
INT wifi_getAclDeviceNum(INT apIndex, UINT *output_uint);           // outputs the number of devices in the filter list
INT wifi_kickAclAssociatedDevices(INT apIndex,BOOL enable);         // enable kick for devices on acl black list
INT wifi_setMacAddressControlMode(INT apIndex, INT filterMode);     // sets the mac address filter control mode.  0 == filter disabled, 1 == filter as whitelist, 2 == filter as blacklist

INT wifi_setVlanID(INT apIndex, INT vlanId);                        // sets the vlan ID for this ap to an internal enviornment variable
INT wifi_getBridgeInfo(INT index, CHAR *bridgeName, CHAR *IP, CHAR *subnet);	// gets bridgeName, IP address and Subnet.
INT wifi_setBridgeInfo(INT apIndex, CHAR *bridgeName, CHAR *IP, CHAR *subnet);   //sets bridgeName, IP address and Subnet to internal enviornment variables. bridgeName is a maximum of 32 characters, 
INT wifi_pushBridgeInfo(INT apIndex);                               // push the BridgeInfo enviornment variables to the hardware
INT wifi_resetVlanCfg(INT apIndex);                                 // reset the vlan configuration for this ap
INT wifi_setApBridging(INT apIndex, BOOL bridgeEnable);             // set the enviornment variables to control briding.  If isolation is requried then disable bridging.  
INT wifi_getRouterEnable(INT apIndex, BOOL *output_bool);           // Outputs a bool that indicates if router is enabled for this ap
INT wifi_setRouterEnable(INT apIndex, BOOL routerEnabled);          // sets the routerEnabled variable for this ap

/**********************************************************************************
 *
 *  Hostapd control function calls used for WPA/WPS security
 *
**********************************************************************************/
INT wifi_createHostApdConfig(INT apIndex, BOOL createWpsCfg);       // creates configuration variables needed for WPA/WPS.  These variables are implementation dependent and in some implementations these variables are used by hostapd when it is started.  Specific variables that are needed are dependent on the hostapd implementation. These variables are set by WPA/WPS security functions in this wifi HAL.  If not needed for a particular implementation this function may simply return no error.
INT wifi_startHostApd();                                            // starts hostapd, uses the variables in the hostapd config with format compatible with the specific hostapd implementation
INT wifi_stopHostApd();                                             // stops hostapd



#else
#error "! __WIFI_HAL_H__"
#endif
 
