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

/**
* @file voice_hal.h
* @author sky
* @brief For CCSP Component:  CcspTelcoVoIPAgent
*
* @description This header file gives the function call prototypes and structure 
* definitions used for the RDK-Broadband hardware abstraction layer for VoIP 
*/

/**********************************************************************

    module: voice_hal.h

        For CCSP Component:  CcspTelcoVoIPAgent

    ---------------------------------------------------------------

    description:

        This header file gives the function call prototypes and 
        structure definitions used for the RDK-Broadband 
        hardware abstraction layer for VoIP

    ---------------------------------------------------------------

    environment:

        This HAL layer is intended to support VoIP drivers 
        through an open API.  
        Changes may be needed to support different hardware enviornments.

    ---------------------------------------------------------------

    author:

        Sky

**********************************************************************/


#ifndef __voice_hal_H__
#define __voice_hal_H__

#include <stdint.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <stdint.h>

/**
 * @defgroup VOICE_HAL VOICE HAL
 *
 * @defgroup VOICE_HAL_TYPES  VOICE HAL Data Types
 * @ingroup  VOICE_HAL
 *
 * @defgroup VOICE_HAL_APIS   VOICE HAL APIs
 * @ingroup  VOICE_HAL
 *
 **/
/**********************************************************************
               CONSTANT DEFINITIONS
**********************************************************************/
/**
 * @addtogroup VOICE_HAL_TYPES
 * @{
 */

/* Curiously, rdk_error.h only defines RDK_SUCCESS.
 * Here, additional Voice specific error codes are defined.
 * Follow the general Posix format that negative integers are errors.
 */
#define RETURN_ERROR (-1)
#define RETURN_OK 0

#ifndef RDK_SUCCESS
#define RDK_SUCCESS (0)     /*No Error*/
#endif
#define RDK_FAILURE (-1)    /*any other failure*/
#define RDK_ERROR_PARAM (-2)   /* NULL pointers mainly */
#define RDK_ERROR_RANGE (-3)   /* Value provided, but out of permitted range */
#define RDK_ERROR_OOM (-4)   /* Out of memory, usually malloc failed */

#undef VOICE_UNSUPPORTED_PARAMS /*Writable Region specific parameter APIs disabled(Currently no datamodel to configure these) */

/**********************************************************************
                ENUMERATION DEFINITIONS
**********************************************************************/

typedef enum    /* telephone line state */
{
    VOICE_HAL_LINE_STATE_UP = 0,
    VOICE_HAL_LINE_STATE_INITIALIZING,
    VOICE_HAL_LINE_STATE_REGISTERING,
    VOICE_HAL_LINE_STATE_UNREGISTERING,
    VOICE_HAL_LINE_STATE_ERROR,
    VOICE_HAL_LINE_STATE_TESTING,
    VOICE_HAL_LINE_STATE_QUIESCENT,
    VOICE_HAL_LINE_STATE_DISABLED
} VoiceHalLineStatus_e;

typedef enum    /* telephone line state */
{
    VOICE_HAL_LINE_DISABLED = 0,
    VOICE_HAL_LINE_QUIESCENT,
    VOICE_HAL_LINE_ENABLED
} VoiceHalLineEnable_e;

typedef enum    /* telephone call status */
{
    VOICE_HAL_CALL_STATE_IDLE = 0,
    VOICE_HAL_CALL_STATE_CALLING,
    VOICE_HAL_CALL_STATE_RINGING,
    VOICE_HAL_CALL_STATE_CONNECTING,
    VOICE_HAL_CALL_STATE_INCALL,
    VOICE_HAL_CALL_STATE_HOLD,
    VOICE_HAL_CALL_STATE_DISCONNECTING
} VoiceHalCallState_e;

typedef enum
{
    VOICE_HAL_DIAG_STATE_TYPE_NONE = 0,
    VOICE_HAL_DIAG_STATE_TYPE_REQUESTED,
    VOICE_HAL_DIAG_STATE_TYPE_COMPLETE,
    VOICE_HAL_DIAG_STATE_TYPE_ERROR_INTERNAL,
    VOICE_HAL_DIAG_STATE_TYPE_ERROR_OTHER
} VoiceHalDiagnosticState_e;

typedef enum
{
    VOICE_HAL_NORMAL_DIGIT_MAP = 0,
    VOICE_HAL_EMERGENCY_DIGIT_MAP
}  VoiceHalDigitMap_e;

typedef enum
{
    VOICE_HAL_AF_INET_V4 = 0,
    VOICE_HAL_AF_INET_V6
}  VoiceHalIpAddressFamily_e;

typedef enum
{
    VOICE_HAL_IP_LINK_STATE_DOWN = 0,
    VOICE_HAL_IP_LINK_STATE_UP
}  VoiceHalIpLinkState_e;

typedef enum
{
    VOICE_HAL_S_TIMER = 0,
    VOICE_HAL_Z_TIMER
}  VoiceHalDigitTimer_e;

typedef enum
{
    VOICE_HAL_AUTH_UNAME = 0,
    VOICE_HAL_AUTH_PWD
}  VoiceHalAuthCredentialType_e;

typedef enum 
{
   VOICE_PROCESS_STATE_STOP = 0,
   VOICE_PROCESS_STATE_START,
   VOICE_PROCESS_STATE_RESTART,
   VOICE_PROCESS_STATE_FACTORY_DEFAULT
} VoiceProcessStateRequest_e;

typedef enum {
    VOICE_PROCESS_STATUS_STOPPED = 0,
    VOICE_PROCESS_STATUS_STARTING,
    VOICE_PROCESS_STATUS_STARTED,
    VOICE_PROCESS_STATUS_STOPPING,
    VOICE_PROCESS_STATUS_ERROR
} VoiceProcessStatus_e;

typedef  enum 
{
    VOICE_CALLING_FEATURE_CALL_WAITING = 0,
    VOICE_CALLING_FEATURE_MSG_WAIT_INDICATOR,
    VOICE_CALLING_FEATURE_CONF_CALL,
    VOICE_CALLING_FEATURE_HOLD,
    VOICE_CALLING_FEATURE_CALLER_ID,
}VoiceCallFeatureType_e;

/**********************************************************************
                STRUCTURE DEFINITIONS
**********************************************************************/
typedef struct
{
    bool                       ResetStatistics;  /**< ResetStatistics */
    uint32_t                   PacketsSent; /**< Total number of RTP packets sent for this line. */
    uint32_t                   PacketsReceived; /**< Total number of RTP payload bytes received for this line. */
    uint32_t                   BytesSent; /**< Total number of RTP payload bytes sent for this line.  */
    uint32_t                   BytesReceived; /**< Total number of RTP payload bytes received for this line. */
    uint32_t                   PacketsLost; /**< Total number of RTP packets that have been lost for this line. */
    uint32_t                   IncomingCallsReceived; /**< Total incoming calls received. */
    uint32_t                   IncomingCallsAnswered; /**< Total incoming calls answered by the local user. */
    uint32_t                   IncomingCallsConnected; /**< Total incoming calls that successfully completed call setup signalling. */
    uint32_t                   IncomingCallsFailed; /**< Total incoming calls that failed to successfully complete call setup signalling. */
    uint32_t                   OutgoingCallsAttempted; /**< Total outgoing calls attempted. */
    uint32_t                   OutgoingCallsAnswered; /**< Total outgoing calls answered by the remote user. */
    uint32_t                   OutgoingCallsConnected; /**< Total outgoing calls that successfully completed call setup signalling. */
    uint32_t                   OutgoingCallsFailed; /**< Total outgoing calls that failed to successfully complete call setup signaling. */
#ifdef HUB4_SDK_L07
    uint32_t                   CallsDropped; /**< Total calls that were successfully connected (incoming or outgoing), but dropped unexpectedly while in progress without explicit user termination. */
    uint32_t                   TotalCallTime; /**<  Cumulative call duration in seconds. */
    uint32_t                   ServerDownTime; /**< The number of seconds the CPE is unable to maintain a connection to the server. SHOULD not include time in which overall network connectivity is unavailable. Applies only to SIP. */
#endif
    uint32_t                   ReceivePacketLossRate; /**< Current receive packet loss rate in percent, calculated as defined in [section 6.4-RFC3550] */
    uint32_t                   FarEndPacketLossRate; /**< Current far end receive packet lost rate in percent, calculated as defined in  [Section6.4/RFC3550]. */
    uint32_t                   ReceiveInterarrivalJitter; /**< Current receive interarrival jitter in microseconds. Calculated from J(i) as defined in [Section6.4/RFC3550], with units converted to microseconds. */
    uint32_t                   FarEndInterarrivalJitter; /**< Current Interarrival jitter in microseconds as reported from the far-end device via RTCP. Calculated from J(i) as defined in [Section64./RFC3550], with units converted to microseconds. */
    uint32_t                   RoundTripDelay; /**< Current round trip delay in microseconds calculated as defined in [section 6.4-RFC3550]. */
    uint32_t                   AverageReceiveInterarrivalJitter; /**< Average receive interarrival jitter in microseconds since the beginning of the current call. Calculated as the average of D(i,j) as defined in [Section6.4/RFC3550], with units converted to microseconds.*/
    uint32_t                   AverageFarEndInterarrivalJitter; /**< Average far-end interarrival jitter in microseconds since the beginning of the current call. Calculated as the average of the interarrival jitter values reported by the far-end, with units converted to microseconds. */
    uint32_t                   AverageRoundTripDelay; /**< Average round trip delay in microseconds since the beginning of the current call. Average of the RoundTripDelay statistic accumulated each time the delay is calculated. */
#if HUB4_SDK_L07
    uint32_t                   OverRuns; /**< Total number of times the receive jitter buffer has overrun for this line. */
    uint32_t                   UnderRuns; /**<  Total number of times the receive jitter buffer has underrun for this line. */
#endif
} TelcoVoipAgent_VoiceService_Stats_t;

typedef  struct 
{
    bool                EnableCallWaiting;
    bool                EnableMessageWaitingIndicator;
    bool                EnableConferenceCall;
    bool                HoldEnable;
    bool                EnableCallerId;
}
TelcoVoipAgent_Voice_Calling_Features_t, *pTelcoVoipAgent_Voice_Calling_Features_t;

#define VOICE_HAL_USERNAME_LENGTH    (40)
#define VOICE_HAL_PASSWORD_LENGTH    (40)

/* These values are expected to be UTF-8 to support non-UK deployments */
typedef  struct 
{
    uint8_t             UserName[VOICE_HAL_USERNAME_LENGTH];
    uint8_t             Password[VOICE_HAL_PASSWORD_LENGTH];
}
TelcoVoipAgent_Voice_Credentials_t, *pTelcoVoipAgent_Voice_Credentials_t;

/** @} */  //END OF GROUP VOICE_HAL_TYPES

/*****************************************************************************
 * 
 * Ccsp Telco voice HAL function prototypes
 * 
 *****************************************************************************/

/*****************************************************************************
 * 
 * Basic management
 * 
 *****************************************************************************/

/**
 * @addtogroup VOICE_HAL_APIS
 * @{
 */

/* voice_hal_Init :  */
/**
* @description Init the Voice Hal.
* @param None
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.

*
* @note This function must not suspend and must not invoke any blocking system
* calls. 
*
*/
int32_t   voice_hal_Init(void);

/* voice_hal_InitDB :  */
/**
* @description Retrieves the global information for all shared DBs and makes them accessible locally.
* @param None
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.

*
* @note This function must not suspend and must not invoke any blocking system
* calls. 
*
*/
int32_t   voice_hal_InitDB(void);

/* voice_hal_Deinit :  */
/**
* @description Releases all resources & closes all connections made during voice_hal_Init().
* @param None
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*
* @note This function must not suspend and must not invoke any blocking system
* calls. Since no sensible action can be taken on the RDK_FAILURE case, just log it & ignore.
*
*/
int32_t   voice_hal_Deinit(void);

/* voice_hal_DeinitDB :  */
/**
* @description Releases all resources & closes all connections made during voice_hal_InitDB().
* @param None
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.

*
* @note This function must not suspend and must not invoke any blocking system
* calls. Since no sensible action can be taken on the RDK_FAILURE case, just log it & ignore.
*
*/
int32_t   voice_hal_DeinitDB(void);

/* voice_hal_setVoiceProcessState /

    @description controls the voice process under HAL, to start, stop or restart *
    @param uint32_t service - input the voice service
    @param enum VoiceProcessStateRequest_e voice_state - can be in following states
    VOICE_PROCESS_STATE_STOP
    VOICE_PROCESS_STATE_START
    VOICE_PROCESS_STATE_RESTART *
    @return The status of the operation.
    @retval RDK_SUCCESS if successful.
    @retval RDK_FAILURE if any error is detected *
    @execution Synchronous.
    @sideeffect None.
    return RDK_SUCCESS;
    */
int32_t voice_hal_setVoiceProcessState(uint32_t service, VoiceProcessStateRequest_e voice_state);

/* voice_hal_getVoiceProcessState /

    @description Gets the voice process state that was previously set *
    @param uint32_t service - input the voice service
    @param enum VoiceProcessStateRequest_e *pvoice_state - can be in following states
    VOICE_PROCESS_STATE_STOP
    VOICE_PROCESS_STATE_START
    VOICE_PROCESS_STATE_RESTART *
    @return The status of the operation.
    @retval RDK_SUCCESS if successful.
    @retval RDK_FAILURE if any error is detected *
    @execution Synchronous.
    @sideeffect None.
    return RDK_SUCCESS;
    */
int32_t voice_hal_getVoiceProcessState(uint32_t service, VoiceProcessStateRequest_e *pvoice_state);

/* voice_hal_getVoiceProcessStatus /

    @description gets the current execution state of the voice process under HAL
    @param uint32_t service - input the voice service
    @param enum VoiceProcessStatus_e *pvoice_status - can be following
    VOICE_PROCESS_STATUS_STOPPED
    VOICE_PROCESS_STATUS_STARTING
    VOICE_PROCESS_STATUS_STARTED
    VOICE_PROCESS_STATUS_STOPPING *
    @return The status of the operation.
    @retval RDK_SUCCESS if successful.
    @retval RDK_FAILURE if any error is detected *
    @execution Synchronous.
    @sideeffect None.
    return RDK_SUCCESS;
    */
int32_t voice_hal_getVoiceProcessStatus(uint32_t service, VoiceProcessStatus_e *pvoice_status);

/* voice_hal_getServiceVersion: */
/**
* @description Get a string identifying the voice software present
* @param char *service_version - output a pointer to a null-terminated string identifying the voice software version
* The returned string will be ASCII (7-bit, no Unicode/UTF-8)
* @param uint32_t *pLength - input/output the buffer length
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_getServiceVersion(char *service_version, uint32_t *pLength);

/* voice_hal_getConfigSoftwareVersion: */
/**
* @description Get a string identifying the software configuration version
* @param char *config_version - output a pointer to a null-terminated string identifying the software configuration version
* The returned string will be ASCII (7-bit, no Unicode/UTF-8)
* @param uint32_t *pLength - input/output the buffer length
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_getConfigSoftwareVersion(uint32_t service, char *config_version, uint32_t *pLength);

/*****************************************************************************
 * 
 * Service/profile/line/physical interface enumeration
 * 
 *****************************************************************************/

/* voice_hal_getCountServices: */
/**
* @description Get the count of voice services present. Used to enumerate through services
* @param uint32_t *serviceCount - output on return the number of voice services present
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_getCountServices(uint32_t *serviceCount);

/* voice_hal_getCountProfiles: */
/**
* @description Get the count of profiles present. Used to enumerate through profiles
* @param uint32_t service - input the voice service whose profiles are being queried
* @param uint32_t *profileCount - output on return the number of voice profiles present
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_getCountProfiles(uint32_t service, uint32_t *profileCount);

/* voice_hal_getCountLines: */
/**
* @description Get the count of voice lines present. Used to enumerate through servcies/profiles/lines
* @param uint32_t service - input the voice service whose profiles are being queried
* @param uint32_t profile - input the profile being queried
* @param uint32_t *lineCount - output on return the number of voice profiles present
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_getCountLines(uint32_t service, uint32_t profile, uint32_t *lineCount);

/* voice_hal_getCountPhyInterfaces: */
/**
* @description Get the count of physical interfaces present. Used to enumerate them in testing
* @param uint32_t service - input the voice service for which the number of interfaces is being queried
* @param uint32_t *phyCount - output on return the number of v present
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_getCountPhyInterfaces(uint32_t service, uint32_t *phyCount);

/***   Network interfaces     ***/

/* voice_hal_getBoundIfName: */
/**
* @description Get a string idntifying the interface to which this service is bound
* 
* @param uint32_t service - input the voice service being queried
* @param char *bound_if_name - output pointer to the name of the interface, 
*     or the special values 'Any_WAN', 'Any_LAN'.
* @param unsigned int *pLength - input/output the buffer length
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_getBoundIfName(uint32_t service, char *bound_if_name, uint32_t *pLength);

/* voice_hal_setBoundIfName: */
/**
* @description Set the interface to which the specified service is bound
* 
* @param uint32_t service - input the voice service being configured
* @param const char *bound_if_name - input the name of the interface, 
*     or the special values 'Any_WAN', 'Any_LAN'.
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_setBoundIfName(uint32_t service, const char *bound_if_name);

/* voice_hal_setIpAddressFamily: */
/**
* @description Set either IPv4 or IPv6 addressing for voice
* 
* @param uint32_t service - input the voice service being configured
* @param char *address_family - input the AF type, 
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_setIpAddressFamily(uint32_t service, const char *address_family);

/* voice_hal_getIpAddressFamily: */
/**
* @description get the address family for voice either IPv4 or IPv6
* 
* @param uint32_t service - input the voice service being configured
* @param char *p_address_family - output pointer to the AF type, 
* @param uint32_t *pLength - input/output the buffer length
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*    return RDK_SUCCESS;
*/
int32_t voice_hal_getIpAddressFamily(uint32_t service, char *address_family, uint32_t *pLength);

/*****************************************************************************
 * 
 *    Link state/address event handlers 
 * 
 *****************************************************************************/

/* voice_hal_setLinkState: */
/**
* @description In response to the link state event, set the link state to up or down
* 
* @param VoiceHalIpLinkState_e state - input either VOICE_HAL_IP_LINK_STATE_DOWN or VOICE_HAL_IP_LINK_STATE_UP
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_setLinkState(VoiceHalIpLinkState_e state);

/* voice_hal_setIpWanAddress: */
/**
* @description In response to the ipv4/ipv6_wan_ipaddr events, set the IPv6 WAN address
* 
* @param uint32_t service - input the voice service whose IP address is to be set
* @param const char *boundIpAddress - IP address of WAN interface
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_setIpWanAddress(uint32_t service, const char *boundIpAddress);

/* voice_hal_getIpWanAddress: */
/**
* @description Get the WAN address (IPv4 or IPv6)
* 
* @param uint32_t service - input the voice service whose IP address is to be retrieved
* @param char *boundIpAddress - IP address of WAN interface, space is allocated by the caller
* @param uint32_t *pLength - max input buffer length
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_getIpWanAddress(uint32_t service, char *boundIpAddress, uint32_t *pLength);



/*****************************************************************************
 * 
 *    Diagnostics 
 * 
 *****************************************************************************/

/* voice_hal_getTestState: */
/**
* @description get the state of the diagnostic test system - ready/busy/in error
* 
* @param uint32_t service - input the voice service being configured
* @param char *phy_interface - input the physical network interface being queried
* @param char *testState - output the AF type, 
* @param uint32_t *pLength - input/output buffer length
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_getTestState(uint32_t service, uint32_t phy_interface,
                               char *testState, uint32_t *pLength);

/* voice_hal_setTestState: */
/**
* @description set the state of the diagnostic test system - requested
* 
* @param uint32_t service - input the voice service being configured
* @param uint32_t phy_interface - input the physical network interface being queried
* @param char *testState - state of the diag test, 
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_setTestState(uint32_t service, uint32_t phy_interface,
                               char *testState);


/* voice_hal_getTestResult: */
/**
* @description get the result of the selected test
* 
* @param uint32_t service - input the voice service being queried
* @param uint32_t phy_interface - input the physical network interface being queried
* @param char *test_result - output the test result
* @param uint32_t *pLength - input/output buffer length
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_getTestResult(uint32_t service, uint32_t phy_interface, char *test_result, uint32_t *pLength);

/* voice_hal_setTestSelector: */
/**
* @description select the test to be performed
* 
* @param uint32_t service - input the voice service being queried
* @param uint32_t phy_interface - input the physical network interface being queried
* @param char *test_selector - input the GR-909 test to perform
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_setTestSelector(uint32_t service, uint32_t phy_interface, char *test_selector);

/* voice_hal_getTestSelector: */
/**
* @description read the number of the most recently performed test
* 
* @param uint32_t service - input the voice service being queried
* @param uint32_t phy_interface - input the physical network interface being queried
* @param uint32_t *test_selector - output the GR-909 test last started
* @param uint32_t *pLength - input/output buffer length
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_getTestSelector(uint32_t service, uint32_t phy_interface, char *testSelector, uint32_t *pLength);

/* voice_hal_getPOSTTipGroundVoltageACParameter: */
/**
* @description get the POST result for Tip Ground Voltage AC
*
* @param uint32_t service - input the voice service index
* @param uint32_t uiPhyInterface - input the uiPhyInterface index
* @param char* pValue - output the POST parameter value
* @param uint32_t* pLength - input/output the buffer size
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
* @retval RDK_ERROR_OOM if buffer length insufficient
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_getPOSTTipGroundVoltageACParameter(uint32_t service, uint32_t phy_interface, char *pValue, uint32_t *pLength);

/* voice_hal_getPOSTTipGroundVoltageDCParameter: */
/**
* @description get the POST result for Tip Ground Voltage DC
*
* @param uint32_t service - input the voice service index
* @param uint32_t uiPhyInterface - input the uiPhyInterface index
* @param char* pValue - output the POST parameter value
* @param uint32_t* pLength - input/output the buffer size
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
* @retval RDK_ERROR_OOM if buffer length insufficient
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_getPOSTTipGroundVoltageDCParameter(uint32_t service, uint32_t phy_interface, char *pValue, uint32_t *pLength);

/* voice_hal_getPOSTRingGroundVoltageACParameter: */
/**
* @description get the POST result for Ring Ground Voltage AC
*
* @param uint32_t service - input the voice service index
* @param uint32_t uiPhyInterface - input the uiPhyInterface index
* @param char* pValue - output the POST parameter value
* @param uint32_t* pLength - input/output the buffer size
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
* @retval RDK_ERROR_OOM if buffer length insufficient
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_getPOSTRingGroundVoltageACParameter(uint32_t service, uint32_t phy_interface, char *pValue, uint32_t *pLength);

/* voice_hal_getPOSTRingGroundVoltageDCParameter: */
/**
* @description get the POST result for Ring Ground Voltage DC
*
* @param uint32_t service - input the voice service index
* @param uint32_t uiPhyInterface - input the uiPhyInterface index
* @param char* pValue - output the POST parameter value
* @param uint32_t* pLength - input/output the buffer size
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
* @retval RDK_ERROR_OOM if buffer length insufficient
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_getPOSTRingGroundVoltageDCParameter(uint32_t service, uint32_t phy_interface, char *pValue, uint32_t *pLength);

/* voice_hal_getPOSTTipGroundImpedanceParameter: */
/**
* @description get the POST result for Tip Ground Impedance
*
* @param uint32_t service - input the voice service index
* @param uint32_t uiPhyInterface - input the uiPhyInterface index
* @param char* pValue - output the POST parameter value
* @param uint32_t* pLength - input/output the buffer size
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
* @retval RDK_ERROR_OOM if buffer length insufficient
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_getPOSTTipGroundImpedanceParameter(uint32_t service, uint32_t phy_interface, char *pValue, uint32_t *pLength);

/* voice_hal_getPOSTRingGroundImpedanceParameter: */
/**
* @description get the POST result for Ring Ground Impedance
*
* @param uint32_t service - input the voice service index
* @param uint32_t uiPhyInterface - input the uiPhyInterface index
* @param char* pValue - output the POST parameter value
* @param uint32_t* pLength - input/output the buffer size
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
* @retval RDK_ERROR_OOM if buffer length insufficient
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_getPOSTRingGroundImpedanceParameter(uint32_t service, uint32_t phy_interface, char *pValue, uint32_t *pLength);

/* voice_hal_getPOSTTipRingImpedanceParameter: */
/**
* @description get the POST result for Tip Ring Impedance
*
* @param uint32_t service - input the voice service index
* @param uint32_t uiPhyInterface - input the uiPhyInterface index
* @param char* pValue - output the POST parameter value
* @param uint32_t* pLength - input/output the buffer size
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
* @retval RDK_ERROR_OOM if buffer length insufficient
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_getPOSTTipRingImpedanceParameter(uint32_t service, uint32_t phy_interface, char *pValue, uint32_t *pLength);

/*****************************************************************************
 * 
 *    Calling features - call waiting, caller ID ...
 * 
 *****************************************************************************/

/* voice_hal_setCallingFeatures: */
/**
* @description enable or disable the calling features for this line
* 
* @param uint32_t service - input the voice service
* @param uint32_t profile - input the voice profile
* @param uint32_t line - input the voice line number
* @param VoiceCallFeatureType_e eFeature - input the voice calling feature type
* @param bool bStatus - input the voice calling feature status
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_setCallingFeatures(uint32_t service, uint32_t profile, uint32_t line, VoiceCallFeatureType_e eFeature, bool bStatus);

/* voice_hal_getCallingFeatures: */
/**
* @description read the calling features for this line
* 
* @param uint32_t service - input the voice service
* @param uint32_t profile - input the voice profile
* @param uint32_t line - input the voice line number
* @param VoiceCallFeatureType_e eFeature - input the voice calling feature type
* @param bool *pStatus - output the voice calling feature status
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_getCallingFeatures(uint32_t service, uint32_t profile, uint32_t line, VoiceCallFeatureType_e eFeature, bool *pStatus);

/*****************************************************************************
 * 
 *    Proxies and servers 
 * 
 *****************************************************************************/

/* voice_hal_getOutboundProxyAddresses: */
/**
* @description get a list of the resolved IP addresses from the FQDN of the configured outbound proxy
* 
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param uint32_t line - input the voice line number
* @param char **pProxyAddresses - output the list of resolved IP addresses as a null-terminated string
*             e.g. "192.168.0.1 192.168.20.10" etc
* @param uint32_t *pLength - input/output buffer length
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_getOutboundProxyAddresses(uint32_t service, uint32_t profile, uint32_t line, char *pProxyAddresses, uint32_t *pLength);

/* voice_hal_getOutboundProxy: */
/**
* @description get the name/address of the SIP outbound proxy
* 
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param char *ipNameAddress - output the name or IP address of Outbound proxy
*             e.g. "10.241.16.3" or "proxy.sky.com"
* @param uint32_t *pLength - input/output buffer length
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_getOutboundProxy(uint32_t service, uint32_t profile, char *ipNameAddress, uint32_t *pLength);
/* voice_hal_setOutboundProxy: */
/**
* @description set the name/address of the SIP outbound proxy
* 
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param char *ipNameAddress - input the name or IP address of Outbound proxy
*             e.g. "10.241.16.3" or "proxy.sky.com"
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_setOutboundProxy(uint32_t service, uint32_t profile, const char *ipNameAddress);
/* voice_hal_getOutboundProxyPort: */
/**
* @description get the port of the SIP outbound proxy
* 
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param uint32_t *port - output the port value of Outbound proxy
*             e.g. "888"
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_getOutboundProxyPort(uint32_t service, uint32_t profile, uint32_t *port);
/* voice_hal_setOutboundProxyPort: */
/**
* @description set the port of the SIP outbound proxy
* 
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param uint32_t port - input the port value of Outbound proxy
*             e.g. "888"
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_setOutboundProxyPort(uint32_t service, uint32_t profile, uint32_t port);
/* voice_hal_getProxyServer: */
/**
* @description get the name/address of the SIP proxy server
* 
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param char * proxyServer - output buffer to get proxy server name
*             e.g. "voip.sky.com"
* @param uint32_t *pLength - input/output buffer length
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_getProxyServer(uint32_t service, uint32_t profile, char * proxyServer, uint32_t *pLength);
/* voice_hal_setProxyServer: */
/**
* @description set the name/address of the SIP proxy server
* 
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param char * proxyServer - input buffer to set proxy server name
*             e.g. "voip.sky.com"
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_setProxyServer(uint32_t service, uint32_t profile, const char * proxyServer);
/* voice_hal_getProxyServerPort: */
/**
* @description get the port of the SIP proxy server
* 
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param uint32_t *port - output the port value of proxy server
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_getProxyServerPort(uint32_t service, uint32_t profile, uint32_t *port);
/* voice_hal_setProxyServerPort: */
/**
* @description set the port of the proxy server
* 
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param uint32_t port - input the port value of proxy server
*             e.g. "888"
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_setProxyServerPort(uint32_t service, uint32_t profile, uint32_t port);
/* voice_hal_getRegistrarServerPort: */
/**
* @description get the port of the Registrar server port
* 
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param uint32_t *port - output the port value of Registrar server port
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_getRegistrarServerPort(uint32_t service, uint32_t profile, uint32_t *port);
/* voice_hal_setRegistrarServerPort: */
/**
* @description set the port of the Registrar server port
* 
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param uint32_t port - input the port value of Registrar server port
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_setRegistrarServerPort(uint32_t service, uint32_t profile, uint32_t port);
/* voice_hal_setRegistrarServer: */
/**
* @description set the name/address of the SIP registrar server
* 
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param char *ipNameAddress - input the name or IP address as a null-terminated string
*             e.g. "10.241.16.3" or "proxy.sky.com"
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_setRegistrarServer(uint32_t service, uint32_t profile, const char *ipNameAddress);

/* voice_hal_getRegistrarServer: */
/**
* @description get the name/address of the SIP registrar server
* 
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param char **ipNameAddress - output the name or IP address as a null-terminated string
*             e.g. "10.241.16.3" or "proxy.sky.com"
* @param uint32_t *pLength - input/output buffer length
* Where a host name is supplied, it will meet RFC1123
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_getRegistrarServer(uint32_t service, uint32_t profile, char *ipNameAddress, uint32_t *pLength);

/* voice_hal_setLogServer: */
/**
* @description set the name/address and port of the voice logging server
* 
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param char *ipNameAddress - input the name or IP address as a null-terminated string
*             e.g. "10.241.16.3" or "proxy.sky.com"
* Where a host name is returned, it will meet RFC1123
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_setLogServer(uint32_t service, uint32_t profile, const char *ipNameAddress);

/* voice_hal_setLogServerPort: */
/**
* @description set the name/address and port of the voice logging server
* 
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param uint32_t ipPort - the IP port number
* Where a host name is returned, it will meet RFC1123
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_setLogServerPort(uint32_t service, uint32_t profile, uint32_t ipPort);

/* voice_hal_getLogServer: */
/**
* @description get the name/address and port of the voice logging server
* 
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param char *ipNameAddress - output the name or IP address as a null-terminated string
*             e.g. "10.241.16.3" or "proxy.sky.com"
* @param uint32_t *puiLength - Output/input the buffer size
* Where a host name is returned, it will meet RFC1123
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_getLogServer(uint32_t service, uint32_t profile, char *logServerName, uint32_t *puiLength);

/* voice_hal_getLogServerPort: */
/**
* @description get the name/address and port of the voice logging server
* 
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param uint16_t *ipPort - output the IP port number
* Where a host name is returned, it will meet RFC1123
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_getLogServerPort(uint32_t service, uint32_t profile, uint32_t *ipPort);

/* voice_hal_setUserAgentDomain: */
/**
* @description set the name/address of the CPE domain string
* 
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param char *ipDomain - input the CPE domain as a null-terminated string
*             e.g. "voip.sky.com"
* Where a host name is supplied, it will meet RFC1123
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_setUserAgentDomain(uint32_t service, uint32_t profile, const char *ipDomain);

/* voice_hal_getUserAgentDomain: */
/**
* @description get the name/address of the CPE domain string
* 
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param char **ipDomain - output the CPE domain as a null-terminated string
*             e.g. "voip.sky.com"
* @param uint32_t *pLength - input/output buffer length
* Where a host name is supplied, it will meet RFC1123 (no IDNA)
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_getUserAgentDomain(uint32_t service, uint32_t profile, char *ipDomain, uint32_t *pLength);

/* voice_hal_setConferencingUri: */
/**
* @description set the URI of the conferencing server
* 
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param char *pUri - input the URI as a null-terminated string
*             e.g. "sip:conf@sky.com"
* The domain name is supplied as a UTF-8 string meeting RFC1123 (no IDNA)
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_setConferencingUri(uint32_t service, uint32_t profile, const char *pUri);

/* voice_hal_getConferencingUri: */
/**
* @description set the URI of the conferencing server
* 
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param char **uri - output the URI as a null-terminated string
*             e.g. "sip:conf@sky.com"
* @param uint32_t *pLength - input/output buffer length
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_getConferencingUri(uint32_t service, uint32_t profile, char *uri, uint32_t *pLength);

/* voice_hal_setEnableNetworkDisconnect: */
/**
* @description set the enable/disable state of the network disconnect flag
* 
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param bool enableDisconnect
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_setEnableNetworkDisconnect(uint32_t service, uint32_t profile, bool enableDisconnect);

/* voice_hal_getEnableNetworkDisconnect: */
/**
* @description set the enable/disable state of the network disconnect flag
* 
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param bool *enableDisconnect - output the state of the disconnect flag
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_getEnableNetworkDisconnect(uint32_t service, uint32_t profile, bool *enableDisconnect);

/* voice_hal_setEnablePrackRequired: */
/**
* @description set the enable/disable state of the PRACK required
* 
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param bool enablePrackRequired
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_setEnablePrackRequired(uint32_t service, uint32_t profile, bool enablePrackRequired);

/* voice_hal_getEnablePrackRequired: */
/**
* @description set the enable/disable state of the PRACK required
* 
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param bool *enablePrackRequired - output the state of the PRACK required
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_getEnablePrackRequired(uint32_t service, uint32_t profile, bool *enablePrackRequired);

/*****************************************************************************
 * 
 *    Regionalisation 
 * 
 *****************************************************************************/
#ifdef VOICE_UNSUPPORTED_PARAMS 
/* voice_hal_setProfileRegion: */
/**
* @description set the geographic region associated with this profile
* 
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param char *region - input as the ISO 3166-1 alpha-2 2 character null terminated string
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_setProfileRegion(uint32_t service, uint32_t profile, const char *region);

/* voice_hal_getProfileRegion: */
/**
* @description get the geographic region associated with this profile
* 
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param char *region - output as the ISO 3166-1 alpha-2 2 character null terminated string
* @param uint32_t *pLength - output/input the buffer size
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_getProfileRegion(uint32_t service, uint32_t profile, char *region, uint32_t *pLength);

/**
* @description set Tel URI feature code
* 
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param bool enable - input true to enable the feature, false otherwise
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_setTelUriFeatureCode(uint32_t service, uint32_t profile, bool enable);

/**
* @description get Tel URI feature code
* 
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param bool *enable - output true if the feature is enabled, false otherwise
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_getTelUriFeatureCode(uint32_t service, uint32_t profile, bool *enable);

/**
* @description enable emergency SIP URI user parameter
* 
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param bool enable - input true to enable the user parameter, false otherwise
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_setEnableEmergencySipUriUserParm(uint32_t service, uint32_t profile, bool enable);

/**
* @description get the state of the emergency SIP URI user parameter
* 
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param bool enable - output true if enabled, false otherwise
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_getEnableEmergencySipUriUserParm(uint32_t service, uint32_t profile, bool *enable);

/**
* @description enable/disable the local codec priority
* 
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param uint8_t localCodecPriority - enable local codec priority
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_setLocalCodecPriority(uint32_t service, uint32_t profile, uint8_t localCodecPriority);

/**
* @description set the maximum number of preferred codecs
* 
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param uint32_t maxPrefCodecs - input the maximum number of preferred codecs
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_setMaxPreferredCodecs(uint32_t service, uint32_t profile, uint32_t maxPrefCodecs);

/**
* @description get the maximum number of preferred codecs
* 
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param uint32_t *maxPrefCodecs - output the maximum number of preferred codecs
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_getMaxPreferredCodecs(uint32_t service, uint32_t profile, uint32_t *maxPrefCodecs);

/* voice_hal_getDigitMap: */
/**
* @description Get the map of permissible digits for normal or emergency use in this region
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param VoiceHalDigitMap_e map_type - input normal or emergency digit map
* @param char *digit_map_string - output a null-terminated string of the digit map
* @param uint32_t uiBufLen - input buffer size and output data length
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
#endif
int32_t voice_hal_getDigitMap(uint32_t service, uint32_t profile, VoiceHalDigitMap_e map_type, char *digit_map_string, uint32_t *uiBufLen);

/* voice_hal_setDigitMap: */
/**
* @description Set the map of permissible digits for normal or emergency use in this region
* @param char *digit_map_string - input null-terminated list of digits
* @param int lineIndex - the voice line to be configured (0 based)
* @param VoiceHalDigitMap_e map_type - input normal or emergency digit map
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_setDigitMap(uint32_t service, uint32_t profile, VoiceHalDigitMap_e map_type, const char *digit_map_string);

/* voice_hal_setSipDscpMark: */
/**
* @description set the diffserv code point applied to outgoing SIP packets
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param uint32_t dscp - input DSCP code point
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_setSipDscpMark(uint32_t service, uint32_t profile, uint32_t dscp);

/* voice_hal_getSipDscpMark: */
/**
* @description get the diffserv code point applied to outgoing SIP packets
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param uint32_t dscp - output DSCP code point
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_getSipDscpMark(uint32_t service, uint32_t profile, uint32_t *dscp);

/* voice_hal_setSipEthernetPriorityMark: */
/**
* @description set the ethernet priority code used for outgoing SIP packets
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param int32_t priority - input ethernet priority code
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_setSipEthernetPriorityMark(uint32_t service, uint32_t profile, int32_t priority);

/* voice_hal_getSipEthernetPriorityMark: */
/**
* @description get the ethernet priority code used for outgoing SIP packets
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param int32_t priority - output ethernet priority code
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_getSipEthernetPriorityMark(uint32_t service, uint32_t profile, int32_t *priority);

/* voice_hal_getSipSKBMark: */
/**
* @description get the ethernet mark used for outgoing SIP packets
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param uint32_t mark - ethernet mark value
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_getSipSKBMark(uint32_t service, uint32_t profile, uint32_t *mark);

/* voice_hal_setRtpDscpMark: */
/**
* @description set the diffserv code point applied to outgoing RTP packets
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param uint32_t dscp - input DSCP code point
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_setRtpDscpMark(uint32_t service, uint32_t profile, uint32_t dscp);

/* voice_hal_getDscpMark: */
/**
* @description get the diffserv code point applied to outgoing RTP packets
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param uint32_t dscp - output DSCP code point
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_getRtpDscpMark(uint32_t service, uint32_t profile, uint32_t *dscp);

/* voice_hal_setRtpEthernetPriorityMark: */
/**
* @description set the ethernet priority code used for outgoing RTP packets
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param int32_t priority - input ethernet priority code
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_setRtpEthernetPriorityMark(uint32_t service, uint32_t profile, int32_t priority);

/* voice_hal_getRtpEthernetPriorityMark: */
/**
* @description get the ethernet priority code used for outgoing RTP packets
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param int32_t priority - output ethernet priority code
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_getRtpEthernetPriorityMark(uint32_t service, uint32_t profile, int32_t *priority);

/* voice_hal_getRtpSKBMark: */
/**
* @description get the SKB(Socket Kernel Buffer) mark used for outgoing RTP packets
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param uint32_t mark - ethernet mark value
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_getRtpSKBMark(uint32_t service, uint32_t profile, uint32_t *mark);

#ifdef VOICE_UNSUPPORTED_PARAMS 
/* voice_hal_setConferencingOption: */
/**
* @description set the conferencing option
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param char *option - input the conferencing option string
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_setConferencingOption(uint32_t service, uint32_t profile, const char *option);

/* voice_hal_getConferencingOption: */
/**
* @description get the conferencing option string
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param char *option - output the conferencing option string
* @param uint32_t *pLength - output/input the buffer size
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_getConferencingOption(uint32_t service, uint32_t profile, char *option, uint32_t *pLength);

/* voice_hal_setEnableEuroFlashCallWaiting: */
/**
* @description enable/disable European flash call waiting
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param bool enable - input true to enable the feature, false otherwise
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_setEnableEuroFlashCallWaiting(uint32_t service, uint32_t profile, bool enable);

/* voice_hal_getEnableEuroFlashCallWaiting: */
/**
* @description get the state of the European flash call waiting flag
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param bool *enable - output true if feature enabled, false otherwise
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_getEnableEuroFlashCallWaiting(uint32_t service, uint32_t profile, bool *enable);

/* voice_hal_setEnableSipSubscribe: */
/**
* @description enable/disable SIP subscribe
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param bool enable - input true to enable the feature, false otherwise
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_setEnableSipSubscribe(uint32_t service, uint32_t profile, bool enable);

/* voice_hal_getEnableSipSubscribe: */
/**
* @description get the state of the SIP subscribe flag
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param bool enable - output true if the feature is enabled, false otherwise
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_getEnableSipSubscribe(uint32_t service, uint32_t profile, bool *enable);

/* voice_hal_setSessionExpires: */
/**
* @description set the session expiry timneout
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param uint32_t timeout - input session expiry timeout in seconds
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_setSessionExpires(uint32_t service, uint32_t profile, uint32_t timeout);

/* voice_hal_getSessionExpires: */
/**
* @description get the session expiry timneout
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param uint32_t timeout - output session expiry timeout in seconds
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_getSessionExpires(uint32_t service, uint32_t profile, uint32_t *timeout);

/* voice_hal_setMinSessionExpires: */
/**
* @description set the session minimum expiry timneout
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param uint32_t timeout - input session minimum expiry timeout in seconds
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_setMinSessionExpires(uint32_t service, uint32_t profile, uint32_t timeout);

/* voice_hal_getMinSessionExpires: */
/**
* @description get the session minimum expiry timneout
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param uint32_t *timeout - output session minimum expiry timeout in seconds
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_sgetMinSessionExpires(uint32_t service, uint32_t profile, uint32_t *timeout);

/* voice_hal_setHoldModeInactive: */
/**
* @description set the mode media attribute to inactive or sendonly
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param bool     enable  - input true to set to INACTIVE, false to use SENDONLY
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_setHoldModeInactive(uint32_t service, uint32_t profile, bool enable);

/* voice_hal_getHoldModeInactive: */
/**
* @description get the value of the mode media attribute
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param bool *enable - output true -> set to INACTIVE, false -> SENDONLY
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_getHoldModeInactive(uint32_t service, uint32_t profile, bool *enable);
#endif

/*****************************************************************************
 * 
 *    Voice Processing 
 * 
 *****************************************************************************/

/* voice_hal_setReceiveGain: */
/**
* @description set the post-decoding gain to be applied
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param uint32_t line - input the telephone line number affected
* @param int32_t gain - input signed post-decode gain applied in 0.1 dB steps
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_setReceiveGain(uint32_t service, uint32_t profile, uint32_t line, int32_t gain);

/* voice_hal_getReceiveGain: */
/**
* @description get the post-decoding gain applied to the receive channel
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param uint32_t line - input the telephone line number affected
* @param int32_t *gain - output signed post-decode gain applied in 0.1 dB steps
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_getReceiveGain(uint32_t service, uint32_t profile, uint32_t line, int32_t *gain);

/* voice_hal_setTransmitGain: */
/**
* @description set the pre-encoding gain to be applied
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param uint32_t line - input the telephone line number affected
* @param int32_t gain - input signed pre-encode gain applied in 0.1 dB steps
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_setTransmitGain(uint32_t service, uint32_t profile, uint32_t line, int32_t gain);

/* voice_hal_getTransmitGain: */
/**
* @description get the pre-encoding gain applied to the transmit channel
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param uint32_t line - input the telephone line number affected
* @param int32_t *gain - output signed pre-encode gain applied in 0.1 dB steps
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_getTransmitGain(uint32_t service, uint32_t profile, uint32_t line, int32_t *gain);

/* voice_hal_setDisableLoopCurrentUntilRegistered: */
/**
* @description 
* @param uint32_t service - input the voice service to be disabled until registered
* @param bool disabled - input, true if loop current is to be disabled until line registered
*                                 false otherwise
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous
* @sideeffect None.
*
*/
int32_t voice_hal_setDisableLoopCurrentUntilRegistered(uint32_t service, bool disable);

/* voice_hal_getDisableLoopCurrentUntilRegistered: */
/**
* @description 
* @param uint32_t service - input the voice service whose status is being queried
* @param bool *disabled -= output, true if loop current is currently disabled until the line is registered 
*                                 false otherwise
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous
* @sideeffect None.
*
*/
int32_t voice_hal_getDisableLoopCurrentUntilRegistered(uint32_t service, bool *disabled);

/*****************************************************************************
 * 
 *    Logging
 * 
 *****************************************************************************/

/* voice_hal_setLoggingEnable: */
/**
* @description enable/disable Ccsp logging in the TelcoVoIPAgent module
* @param bool enable - input true enables TelcoVoIP logging, false disables it
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_setLoggingEnable(bool enable);

/* voice_hal_getLoggingEnable: */
/**
* @description enable/disable Ccsp logging in the TelcoVoIPAgent module
* @param bool *enable - input true TelcoVoIP logging is enabled, 
*                               false otherwise
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_getLoggingEnable(bool *enable);

/* voice_hal_setCCTKTraceGroup: */
/**
* @description set the CCTK trace group bitmask
* @param uint32_t service - input the voice affected
* @param char *bitmask - input trace group bitmask
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous
* @sideeffect None.
*
*/
int32_t voice_hal_setCCTKTraceGroup(uint32_t service, const char *bitmask);

/* voice_hal_getCCTKTraceGroup: */
/**
* @description get the CCTK trace group bitmask
* @param uint32_t service - input the voice affected
* @param char *bitmask - input trace group bitmask
* @param uint32_t *pLength - input/output the buffer length
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous
* @sideeffect None.
*
*/
int32_t voice_hal_getCCTKTraceGroup(uint32_t service, char *bitmask, uint32_t *pLength);

/* voice_hal_setCCTKTraceLevel: */
/**
* @description set the CCTK trace level
* @param uint32_t service - input the voice service affected
* @param char *logLevel - input trace log level as a null-terminated ASCII string
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous
* @sideeffect None.
*
*/
int32_t voice_hal_setCCTKTraceLevel(uint32_t service, const char *logLevel);

/* voice_hal_getCCTKTraceLevel: */
/**
* @description get the CCTK trace level
* @param uint32_t service - input the voice service affected
* @param char *traceLevel - input trace log level as a null-terminated ASCII string
* @param uint32_t *pLength - input/output the buffer size
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous
* @sideeffect None.
*
*/
int32_t voice_hal_getCCTKTraceLevel(uint32_t service, char *traceLevel, uint32_t *pLength);

/* voice_hal_setLoggingLevel: */
/**
* @description set the logging level for a voice service
* @param uint32_t service - input the voice service affected
* @param uint32_t uLevel - input the logging level to be applied
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous
* @sideeffect None.
*
*/
int32_t voice_hal_setLoggingLevel(uint32_t service, uint32_t uLevel);

/* voice_hal_getLoggingLevel: */
/**
* @description get the logging level for a voice service
* @param uint32_t service - input the voice service affected
* @param uint32_t *pLevel - output the logging level for the service
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous
* @sideeffect None.
*
*/
int32_t voice_hal_getLoggingLevel(uint32_t service, uint32_t *pLevel);

/* voice_hal_setModuleLogLevels: */
/**
* @description set logging levels for specific voice modules
* @param uint32_t service - input the voice service affected
* @param char *bitmask - input trace group bitmask
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous
* @sideeffect None.
*
*/
int32_t voice_hal_setModuleLogLevels(uint32_t service, const char *logLevels);

/* voice_hal_getModuleLogLevels: */
/**
* @description get logging levels for specific voice modules
* @param uint32_t service - input the voice service affected
* @param char *bitmask - output trace group bitmask
* @param uint32_t *pLength - input/output the buffer size
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous
* @sideeffect None.
*
*/
int32_t voice_hal_getModuleLogLevels(uint32_t service, char *logLevels, uint32_t *pLength);

/* voice_hal_getCallState: */
/**
* @description get the call state for a specific line
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param uint32_t line - input the telephone line number affected
* @param VoiceHalCallState_e *callState - output the state of the call
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
/* A very similar object - Device.Services.VoiceService.1.VoiceProfile.1.Line.1.CallState
 and InternetGatewayDevice.Services.VoiceService.1.VoiceProfile.1.Line.1.CallState
 What's the difference??
 */
int32_t voice_hal_getCallState(uint32_t service, uint32_t profile, uint32_t line, VoiceHalCallState_e *callState);

/* voice_hal_getDirectoryNumber: */
/**
* @description get the directory number for the given line 
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param uint32_t line - input the telephone line number affected
* @param char  *directoryNumber - output a null terminated string giving the directory number
* @param uint32_t *pLength - input/output the buffer size
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_getDirectoryNumber(uint32_t service, uint32_t profile, uint32_t line, char *directoryNumber, uint32_t *pLength);

/* voice_hal_setDirectoryNumber: */
/**
* @description set the directory number for the given line 
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param uint32_t line - input the telephone line number affected
* @param char  *directoryNumber - input a null terminated string giving the directory number
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_setDirectoryNumber(uint32_t service, uint32_t profile, uint32_t line, char *buffer);

/* voice_hal_setLineEnable: */
/**
* @description enable/disable a specific telephone line
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param uint32_t line - input the telephone line number affected
* @param VoiceHalLineStatus_e eLineEnable - input true to enable the given ATA line, false othewrwise
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_setLineEnable(uint32_t service, uint32_t profile, uint32_t line, VoiceHalLineEnable_e eLineEnable);

/* voice_hal_getLineEnable: */
/**
* @description get the enable/disable state of a specific telephone line
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param uint32_t line - input the telephone line number affected
* @param VoiceHalLineStatus_e *peLineEnable - output true if the given ATA line is enabled, false othewrwise
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_getLineEnable(uint32_t service, uint32_t profile, uint32_t line, VoiceHalLineEnable_e *peLineEnable);

/* voice_hal_getAuthCredentials: */
/**
* @description get the username+password used to authenticate the connection to the server
*    This value always returns an empty string for password
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param uint32_t line - input the telephone line number affected
* @param VoiceHalAuthCredentialType_e   eAuthCredential - input the user credential type
* @param char*                   pBuffer  - output the user name OR Password buffer
* @param uint32_t *pLength - input/output buffer length
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
* @note On reading, the password field will always be empty.
*
*/
int32_t voice_hal_getAuthCredentials(uint32_t service, uint32_t profile, uint32_t line, VoiceHalAuthCredentialType_e eAuthCredential, char* pBuffer, uint32_t* pLength);

/* voice_hal_setAuthCredentials: */
/**
* @description set the username/password used to authenticate the connection to the server
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param uint32_t line - input the telephone line number affected
* @param VoiceHalAuthCredentialType_e   eAuthCredential - input the user credential type
* @param char*                   pBuffer  - input the user name OR Password buffer
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
* @note: this function is atomic. Either the call succeeds and both username and password are set, 
*     or the call fails and neither username nor password change
*
*/
int32_t voice_hal_setAuthCredentials(uint32_t service, uint32_t profile, uint32_t line, VoiceHalAuthCredentialType_e eAuthCredential, char* pBuffer);

/* voice_hal_getSipUri: */
/**
* @description get the URI by which the user agent will identify itself for this line
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param uint32_t line - input the ATA line number affected
* @param char *pSipUri - output pointer to a buffer holding the SIP URI
* @param uint32_t *pLength - input the size of the buffer
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_getSipURI(uint32_t service, uint32_t profile, uint32_t line, char *pSipUri, uint32_t *pLength);

/* voice_hal_setSipUri: */
/**
* @description set the URI by which the user agent identifies itself for this line 
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param uint32_t line - input the telephone line number affected
* @param char *buffer - input a buffer holding the new URI as a null terminated string
*
*  NOTE: If empty, the actual URI used in the SIP signaling SHOULD be automatically formed by the CPE as:
* "sip:UserName@Domain"
* Where UserName is username given for this line in AuthUserName, and Domain is the domain given for this profile in VoiceProfile.{i}.SIP.UserAgentDomain. If VoiceProfile.{i}.SIP.UserAgentDomain is an empty string, then the IP address of the CPE SHOULD be used for the domain.
* If URI is non-empty, but is a SIP or SIPS URI that contains no "@" character, then the actual URI used in the SIP 
* signaling SHOULD be automatically formed by the CPE by appending this 
* parameter with an "@" character followed by the value of 
* VoiceProfile.{i}.SIP.UserAgentDomain. If VoiceProfile.{i}.SIP.UserAgentDomain 
* is an empty string, then the IP address of the CPE SHOULD be used for the domain.
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_setSipUri(uint32_t service, uint32_t profile, uint32_t line, const char *buffer);

/* voice_hal_getLineStatus: */
/**
* @description get the status for a specific line
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param uint32_t line - input the telephone line number affected
* @param VoiceHalLineStatus_e *lineStatus - output the status of the line
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_getLineStatus(uint32_t service, uint32_t profile, uint32_t line, VoiceHalLineStatus_e *lineState);

/* voice_hal_setDigitTimer: */
/**
* @description Set the digit timer, 'S' or 'Z
* @param VoiceHalDigitTimer_e digit_timer - input select the S or Z digit timers
* @param int lineIndex - the voice line to be configured (0 based)
* @param timer_value - input the number of seconds to set the timer value
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_setDigitTimer(uint32_t service, uint32_t profile, VoiceHalDigitTimer_e digit_timer, uint32_t timer_value);

/* voice_hal_getDigitTimer: */
/**
* @description Get the digit timer, 'S' or 'Z
* @param VoiceHalDigitTimer_e *digit_timer - output value of the S or Z digit timers
* @param int lineIndex - the voice line to be configured (0 based)
* @param uint32_t *timer_value - output the number of seconds of the digit timer
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
*/
int32_t voice_hal_getDigitTimer(uint32_t service, uint32_t profile, VoiceHalDigitTimer_e digit_timer, uint32_t *timer_value);

/* voice_hal_getLineStats: */
/**
* @description Get the statistics for a single voice line
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param uint32_t line - input the telephone line number affected
* @param TelcoVoipAgent_VoiceService_Stats_t *output_stats_struct - return structure with line stats
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function will take some time to complete
*
*/
int32_t voice_hal_getLineStats(uint32_t service, uint32_t profile, uint32_t lineIndex, TelcoVoipAgent_VoiceService_Stats_t *output_stats_struct);

/* voice_hal_resetLineStats: */
/**
* @description Reset the voice line stats counters.
* @param uint32_t service - input the voice service affected
* @param uint32_t profile - input the voice profile affected
* @param uint32_t line - input the telephone line number affected
*
* @return The status of the operation.
* @retval RDK_SUCCESS if successful.
* @retval RDK_FAILURE if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function may take some time to complete.
* It is assumed (but not required) that the stats are read before reset.
*
*/
int32_t voice_hal_resetLineStats(uint32_t service, uint32_t profile, uint32_t lineIndex);

/* voice_hal_print_debug_counters: */
/**
* @description Prints global voice counters
*
* @execution Synchronous.
* @sideeffect None.
*
*/
void voice_hal_print_debug_counters();
/** @} */  //END OF GROUP VOICE_HAL_APIS

#endif /* __voice_hal_H__ */

