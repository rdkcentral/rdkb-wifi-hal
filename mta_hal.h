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

    module: mta_hal.h

        For CCSP Component:  CcspMtaAgent

    ---------------------------------------------------------------

    copyright:

        Cisco Systems, Inc., 2014
        All Rights Reserved.

    ---------------------------------------------------------------

    description:

        This header file gives the function call prototypes and 
        structure definitions used for the RDK-Broadband 
        hardware abstraction layer for Cable Modem

        NOTE:
        THIS VERSION IS AN EARLY DRAFT INTENDED TO GET COMMENTS FROM COMCAST.
        TESTING HAS NOT YET BEEN COMPLETED.  
       
    ---------------------------------------------------------------

    environment:

        This HAL layer is intended to support cable modem drivers 
        through an open API.  
        Changes may be needed to support different hardware enviornments.

    ---------------------------------------------------------------

    author:

        Cisco

**********************************************************************/


#ifndef __MTA_HAL_H__
#define __MTA_HAL_H__

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

#define DECT_MAX_HANDSETS 5

/**********************************************************************
                STRUCTURE DEFINITIONS
**********************************************************************/

typedef struct
_MTAMGMT_MTA_DECT 
{
    ULONG                           RegisterDectHandset;
    ULONG                           DeregisterDectHandset;
    char                            HardwareVersion[64];
    char                            RFPI[64];
    char                            SoftwareVersion[64];
    char                            PIN[64];
}
MTAMGMT_MTA_DECT, *PMTAMGMT_MTA_DECT;

typedef  struct
_MTAMGMT_MTA_HANDSETS_INFO
{
    ULONG                           InstanceNumber;
    BOOLEAN                         Status;
    char                            LastActiveTime[64];
    char                            HandsetName[64];
    char                            HandsetFirmware[64];
    char                            OperatingTN[64];
    char                            SupportedTN[64];
}
MTAMGMT_MTA_HANDSETS_INFO,  *PMTAMGMT_MTA_HANDSETS_INFO;

typedef  struct
_MTAMGMT_MTA_DHCP_INFO
{
    ANSC_IPV4_ADDRESS               IPAddress;
    CHAR                            BootFileName[64];
    CHAR                            FQDN[64];
    ANSC_IPV4_ADDRESS               SubnetMask;
    ANSC_IPV4_ADDRESS               Gateway;
    ULONG                           LeaseTimeRemaining;
    CHAR                            RebindTimeRemaining[64];
    CHAR                            RenewTimeRemaining[64];
    ANSC_IPV4_ADDRESS               PrimaryDNS;
    ANSC_IPV4_ADDRESS               SecondaryDNS;
    CHAR                            DHCPOption3[64];
    CHAR                            DHCPOption6[64];
    CHAR                            DHCPOption7[64];
    CHAR                            DHCPOption8[64];
    CHAR                            PCVersion[64];
    CHAR                            MACAddress[64];
    ANSC_IPV4_ADDRESS               PrimaryDHCPServer;
    ANSC_IPV4_ADDRESS               SecondaryDHCPServer;
}
MTAMGMT_MTA_DHCP_INFO, *PMTAMGMT_MTA_DHCP_INFO;

typedef  struct
_MTAMGMT_MTA_SERVICE_FLOW
{
    ULONG                           SFID;                         /* Id */
    CHAR                            ServiceClass[256];            
    CHAR                            Direction[16];                /* Upstream, Downstream */
    ULONG                           ScheduleType;                 
    BOOLEAN                         DefaultFlow;                  
    ULONG                           NomGrantInterval;
    ULONG                           UnsolicitGrantSize;
    ULONG                           TolGrantJitter;
    ULONG                           NomPollInterval;
    ULONG                           MinReservedPkt;
    ULONG                           MaxTrafficRate;
    ULONG                           MinReservedRate;
    ULONG                           MaxTrafficBurst;
    CHAR                            TrafficType[64];              /* SIP, RTP */
    ULONG                           NumberOfPackets;              /* packet count */
}
MTAMGMT_MTA_SERVICE_FLOW, *PMTAMGMT_MTA_SERVICE_FLOW;

typedef  struct
_MTAMGMT_MTA_CALLS
{
    CHAR                            Codec[64];                    /* local side codec used for the call */
    CHAR                            RemoteCodec[64];              /* remote side codec used for the call */
    CHAR                            CallStartTime[64];            /* start time of a call */
    CHAR                            CallEndTime[64];              /* end time of a call */
    CHAR                            CWErrorRate[16];              /* ratio of useful signal to background noise */
    CHAR                            PktLossConcealment[16];       /* ratio of pkt lost to total expected */
    BOOLEAN                         JitterBufferAdaptive;         /* JBA used or not */
    BOOLEAN                         Originator;                   /* originating side of the call or not */
    ANSC_IPV4_ADDRESS               RemoteIPAddress;              /* remote IP */
    ULONG                           CallDuration;                 /* length of the call in minutes */
    CHAR                            CWErrors[16];                     /* code word errors on this channel */
    CHAR                            SNR[16];                          /* signal to noise ratio * 256 */
    CHAR                            MicroReflections[16];             /* return loss measurement */
    CHAR                            DownstreamPower[16];              /* downstream power in dbmv */
    CHAR                            UpstreamPower[16];                /* upstream power in dbmv */
    CHAR                            EQIAverage[16];                   /* EQI average */    
    CHAR                            EQIMinimum[16];                   /* EQI minimum */
    CHAR                            EQIMaximum[16];                   /* EQI maximum */
    CHAR                            EQIInstantaneous[16];             /* EQI instantaneous */
    CHAR                            MOS_LQ[16];                       /* mean opinion score of listening quality, 10-50 */
    CHAR                            MOS_CQ[16];                       /* mean opinion score of conversational quality, 10-50 */
    CHAR                            EchoReturnLoss[16];               /* residual echo return loss, in db */
    CHAR                            SignalLevel[16];                  /* voice signal relative level, in db */
    CHAR                            NoiseLevel[16];                   /* noise relative level, in db */
    CHAR                            LossRate[16];                     /* fraction of RTP data packet loss * 256 */
    CHAR                            DiscardRate[16];                  /* fraction of RTP data packet discarded * 256 */
    CHAR                            BurstDensity[16];                 /* fraction of bursting data packet * 256 */
    CHAR                            GapDensity[16];                   /* fraction of packets within inter-burst gap * 256 */
    CHAR                            BurstDuration[16];                /* mean duration of bursts, in milliseconds */
    CHAR                            GapDuration[16];                  /* mean duration of gaps, in milliseconds */
    CHAR                            RoundTripDelay[16];               /* most recent measured RTD, in milliseconds */
    CHAR                            Gmin[16];                         /* local gap threshold */
    CHAR                            RFactor[16];                      /* voice quality evaluation for this RTP session */
    CHAR                            ExternalRFactor[16];              /* voice quality evaluation for segment on network external to this RTP session */
    CHAR                            JitterBufRate[16];                /* adjustment rate of jitter buffer, in milliseconds */
    CHAR                            JBNominalDelay[16];               /* nominal jitter buffer length, in milliseconds */
    CHAR                            JBMaxDelay[16];                   /* maximum jitter buffer length, in milliseconds */
    CHAR                            JBAbsMaxDelay[16];                /* absolute maximum delay, in milliseconds */
    CHAR                            TxPackets[16];                    /* count of transmitted packets */
    CHAR                            TxOctets[16];                     /* count of transmitted octet packets */
    CHAR                            RxPackets[16];                    /* count of received packets */
    CHAR                            RxOctets[16];                     /* count of received octet packets */
    CHAR                            PacketLoss[16];                   /* count of lost packets */
    CHAR                            IntervalJitter[16];               /* stat variance of packet interarrival time, in milliseconds */
    CHAR                            RemoteIntervalJitter[16];         /* remote sie IntervalJitter (see local side) */
    CHAR                            RemoteMOS_LQ[16];                 /* remote side MOS_LQ (see local side) */
    CHAR                            RemoteMOS_CQ[16];                 /* remote side MOS_CQ (see local side) */
    CHAR                            RemoteEchoReturnLoss[16];         /* remote side EchoReturnLoss (see local side) */
    CHAR                            RemoteSignalLevel[16];            /* remote side SignalLevel (see local side) */
    CHAR                            RemoteNoiseLevel[16];             /* remote side NoiseLevel (see local side) */
    CHAR                            RemoteLossRate[16];               /* remote side LossRate (see local side) */
    CHAR                            RemotePktLossConcealment[16];     /* remote side PktLossConcealment (see local side) */
    CHAR                            RemoteDiscardRate[16];            /* remote side DiscardRate (see local side) */
    CHAR                            RemoteBurstDensity[16];           /* remote side BurstDensity (see local side) */
    CHAR                            RemoteGapDensity[16];             /* remote side GapDensity (see local side) */
    CHAR                            RemoteBurstDuration[16];          /* remote side BurstDuration (see local side) */
    CHAR                            RemoteGapDuration[16];            /* remote side GapDuration (see local side) */
    CHAR                            RemoteRoundTripDelay[16];         /* remote side RoundTripDelay (see local side) */
    CHAR                            RemoteGmin[16];                   /* remote side Gmin (see local side) */
    CHAR                            RemoteRFactor[16];                /* remote side RFactore (see local side) */
    CHAR                            RemoteExternalRFactor[16];        /* remote side ExternalRFactor (see local side) */
    BOOLEAN                         RemoteJitterBufferAdaptive;   /* remote side JitterBufferAdaptive (see local side) */
    CHAR                            RemoteJitterBufRate[16];          /* remote side JitterBufRate (see local side) */
    CHAR                            RemoteJBNominalDelay[16];         /* remote side JBNominalDelay (see local side) */
    CHAR                            RemoteJBMaxDelay[16];             /* remote side JBMaxDelay (see local side) */
    CHAR                            RemoteJBAbsMaxDelay[16];          /* remote side JBAbsMaxDelay (see local side) */
}
MTAMGMT_MTA_CALLS, *PMTAMGMT_MTA_CALLS;

typedef  struct
_MTAMGMT_MTA_LINETABLE_INFO
{
    ULONG                           InstanceNumber;
    ULONG                           LineNumber;
    ULONG                           Status;                       /* 1 = OnHook; 2 = OffHook */
    CHAR                            HazardousPotential[64];       /* HEMF Test Passed, Not Started */
    CHAR                            ForeignEMF[64];               /* FEMF Test Passed, Not Started */
    CHAR                            ResistiveFaults[128];         /* Not Started */
    CHAR                            ReceiverOffHook[64];          /* Not Started */
    CHAR                            RingerEquivalency[64];        /* Not Started */
    CHAR                            CAName[64];
    ULONG                           CAPort;
    ULONG                           MWD;
    ULONG                           CallsNumber;
    PMTAMGMT_MTA_CALLS              pCalls;
    ULONG                           CallsUpdateTime;
}
MTAMGMT_MTA_LINETABLE_INFO, *PMTAMGMT_MTA_LINETABLE_INFO;

typedef  struct
_MTAMGMT_MTA_CALLP
{
    CHAR                            LCState[64];                  /* In Use, Idle, Out of Service */
    CHAR                            CallPState[64];               /* In Service, OOS */
    CHAR                            LoopCurrent[64];              /* Boosted */
}
MTAMGMT_MTA_CALLP,  *PMTAMGMT_MTA_CALLP;
    
typedef  struct
_MTAMGMT_MTA_DSXLOG
{
    CHAR                            Time[64];
    CHAR                            Description[128];
    ULONG                           ID;
    ULONG                           Level;
}
MTAMGMT_MTA_DSXLOG,  *PMTAMGMT_MTA_DSXLOG;
     
typedef  struct
_MTAMGMT_MTA_MTALOG_FULL 
{
    ULONG                           Index;
    ULONG                           EventID;
    CHAR                            EventLevel[64];
    CHAR                            Time[64];
    CHAR*                           pDescription;
}
MTAMGMT_MTA_MTALOG_FULL,  *PMTAMGMT_MTA_MTALOG_FULL;

typedef  struct
_MTAMGMT_MTA_BATTERY_INFO
{
    CHAR                            ModelNumber[32];
    CHAR                            SerialNumber[32];
    CHAR                            PartNumber[32];
    CHAR                            ChargerFirmwareRevision[32];
}
MTAMGMT_MTA_BATTERY_INFO,  *PMTAMGMT_MTA_BATTERY_INFO;


/**********************************************************************************
 *
 *  MTA Subsystem level function prototypes 
 *
**********************************************************************************/

/* mta_hal_InitDB :  */
/**
* Description: Retrieves the global information for all shared DBs and makes them accessible locally.
* Parameters : None
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
INT   mta_hal_InitDB(void);

/*  mta_hal_GetDHCPInfo : */
/**
* Description: Retrieve all the relevant DHCP info for MTA.
* Parameters : 
*     PMTAMGMT_MTA_DHCP_INFO pInfo - all DHCP info for MTA, to be returned
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
INT mta_hal_GetDHCPInfo(PMTAMGMT_MTA_DHCP_INFO pInfo);

/*  mta_hal_LineTableGetNumberOfEntries :  */
/**
* Description: Get number of entries in the line table.
* Parameters : None
*
* @return ULONG - number of entries
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
ULONG mta_hal_LineTableGetNumberOfEntries(void);

/* mta_hal_LineTableGetEntry : */
/**
* Description: Get entry of the line table at the given index
* Parameters : 
*    INT Index - index to the table entry
*    PMTAMGMT_MTA_LINETABLE_INFO pEntry - entry info, to be returned
*
* @return The status of the operation
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
INT   mta_hal_LineTableGetEntry(ULONG Index, PMTAMGMT_MTA_LINETABLE_INFO pEntry);

/*  mta_hal_TriggerDiagnostics : */
/**
* Description: Trigger GR909 Diagnostics
* Parameters : 
*     INT Index - line number to perform the GR909 diagnostics on
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
INT   mta_hal_TriggerDiagnostics(ULONG Index);

/*  mta_hal_GetServiceFlow :  */
/**
* Description: Get all the service flow info
* Parameters : 
*    ULONG* Count - number of service flow entries, to be returned
*    PMTAMGMT_MTA_SERVICE_FLOW *ppCfg - service flow info, to be returned
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
INT   mta_hal_GetServiceFlow(ULONG* Count, PMTAMGMT_MTA_SERVICE_FLOW *ppCfg);

/*  mta_hal_DectGetEnable : */
/**
* Description: Get info on if Dect is enabled
* Parameters : 
*     BOOLEAN* pBool - boolean value for enabled or not, to be returned
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
INT   mta_hal_DectGetEnable(BOOLEAN *pBool);

/*  mta_hal_DectSetEnable: */
/**
* Description: Set Dect to boolean value passed in
* Parameters : 
*     BOOLEAN* bBool - boolean value for enabled or not, to be returned
*
* @return The status of the operation.
* @retval RETURN_OK if successful.
* @retval RETURN_ERR if any error is detected
*
* @execution Synchronous.
* @sideeffect None.
*
* @note This function must not suspend and must not invoke any blocking system�
* calls. It should probably just send a message to a driver event handler task.�
*
*/
INT mta_hal_DectSetEnable(BOOLEAN bBool);

/*  mta_hal_DectGetRegistrationMode: */
/**
* Description: Set Dect to boolean value passed in
* Parameters : 
*     BOOLEAN* bBool - boolean value for enabled or not, to be returned
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
INT mta_hal_DectGetRegistrationMode(BOOLEAN* pBool);

/*  mta_hal_DectSetRegistrationMode: */
/**
* Description: Set Dect registration mode
* Parameters : 
*     BOOLEAN* bBool - boolean value for enabled or not, to be returned
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
INT mta_hal_DectSetRegistrationMode(BOOLEAN bBool);

/*  mta_hal_DectDeregisterDectHandset: */
/**
* Description: Deregister Dect Handset
* Parameters : 
*     ULONG* uValue - unsigned long value for 
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
INT mta_hal_DectDeregisterDectHandset(ULONG uValue);

/*  mta_hal_GetDect: */
/**
* Description: 
* Parameters : 
*     PMTAMGMT_MTA_DECT* pDect - 
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
INT mta_hal_GetDect(PMTAMGMT_MTA_DECT pDect);

/*  mta_hal_GetDectPIN: */
/**
* Description: 
* Parameters : 
*     char* pPINString -  
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
INT mta_hal_GetDectPIN(char* pPINString);

/*  mta_hal_SetDectPIN: */
/**
* Description: 
* Parameters : 
*     char* pPINString - 
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
INT mta_hal_SetDectPIN(char* pPINString);

/*  mta_hal_GetHandsets: */
/**
* Description: 
* Parameters : 
*     ULONG* pulCount  - 
*     PMTAMGMT_MTA_HANDSETS_INFO* ppHandsets -
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
INT mta_hal_GetHandsets(ULONG* pulCount, PMTAMGMT_MTA_HANDSETS_INFO* ppHandsets);

/*  mta_hal_GetCalls : */
/**
* Description: Retrieve all call info for the given instance number of LineTable
* Parameters : 
*    ULONG InstanceNumber - LineTable's instance number
*    ULONG *Count - number of entries(calls) for the call info array, to be returned
*    PMTAMGMT_MTA_CALLS *ppCfg - Array of call info, to be returned
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
INT   mta_hal_GetCalls(ULONG InstanceNumber, ULONG *Count, PMTAMGMT_MTA_CALLS *ppCfg);

/*  mta_hal_GetCALLP : */
/**
* Description:  Retrieve the CALLP status info for the line number
* Parameters : 
*    ULONG LineNumber - Line number for which to retrieve info on 
*    PMTAMGMT_MTA_CALLP pCallp - CallP info, to be returned
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
INT   mta_hal_GetCALLP(ULONG LineNumber, PMTAMGMT_MTA_CALLP pCallp);

/*  mta_hal_GetDSXLogs : */
/**
* Description:  Retrieve all DSX log entries
* Parameters : 
*    ULONG *Count - number of entries in the log, to be returned
*    PMTAMGMT_MTA_DSXLOG *ppDSXLog - array of log entries, to be returned
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
INT   mta_hal_GetDSXLogs(ULONG *Count, PMTAMGMT_MTA_DSXLOG *ppDSXLog);

/*  mta_hal_GetDSXLogEnable : */
/**
* Description: Get the value of if DSX log is enabled
* Parameters : 
*     BOOLEAN * pBool - boolean value of enable, to be returned
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
INT   mta_hal_GetDSXLogEnable(BOOLEAN *pBool);

/*  mta_hal_SetDSXLogEnable : */
/**
* Description: Set value of DSX enable to the value
* Parameters : 
*     BOOLEAN Bool - value to set DSX log enable to
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
INT   mta_hal_SetDSXLogEnable(BOOLEAN Bool);

/*  mta_hal_GetMtaLog : */
/**
* Description: Get all log entries from the MTA Log
* Parameters : 
*    ULONG *Count - number of entries in the log, to be returned
*    PMTAMGMT_MTA_MTALOG_FULL *ppCfg - array of log entries, to be returned
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
INT   mta_hal_GetMtaLog(ULONG *Count, PMTAMGMT_MTA_MTALOG_FULL *ppCfg);

/*  mta_hal_BatteryGetInstalled : */
/**
* Description: Check to see if the battery is installed
* Parameters : 
*     BOOLEAN* Val - TRUE/FALSE, value to be returned
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
INT mta_hal_BatteryGetInstalled(BOOLEAN* Val);

/*  mta_hal_BatteryGetTotalCapacity : */
/**
* Description: Get the total capacity of the battery
* Parameters : 
*     INT* Val - capacity in mAVHour, to be returned
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
INT mta_hal_BatteryGetTotalCapacity(ULONG* Val);

/*  mta_hal_BatteryGetActualCapacity : */
/**
* Description: Retrieve the actual capacity of the battery
* Parameters : 
*     INT* Val - capacity in mAVHour, to be returned
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
INT mta_hal_BatteryGetActualCapacity(ULONG* Val);

/*  mta_hal_BatteryGetRemainingCharge : */
/**
* Description: Retrieve the current charge remain in the battery
* Parameters : None
*     INT* Val - capacity in mAVHour, to be returned
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
INT mta_hal_BatteryGetRemainingCharge(ULONG* Val);

/* mta_hal_BatteryGetRemainingTime : */
/**
* Description: Get estimated battery remaining time if current usage continues
* Parameters : 
*     INT* Val - Remaining time in minutes, to be returned
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
INT mta_hal_BatteryGetRemainingTime(ULONG* Val);

/*  mta_hal_BatteryGetNumberofCycles : */
/**
* Description: Get max number of cycles the battery can be charge cycled
* Parameters : 
*     INT* Val - Max number of cycles, to be returned
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
INT mta_hal_BatteryGetNumberofCycles(ULONG* Val);

/*  mta_hal_BatteryGetPowerStatus : */
/**
* Description: Get power status of MTA
* Parameters : 
*    CHAR* Val - Status of "AC", "Battery", or "Unknown", to be returned
*    ULONG *len - string length, to be returned
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
INT mta_hal_BatteryGetPowerStatus(CHAR *Val, ULONG *len);

/*  mta_hal_BatteryGetCondition: */
/**
* Description: Get the battery condition
* Parameters : 
*    CHAR* Val - Status of "Good" or "Bad", to be returned
*    ULONG *len - string length, to be returned
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
INT mta_hal_BatteryGetCondition(CHAR *Val, ULONG *len);

/*  mta_hal_BatteryGetStatus: */
/**
* Description: Get the battery status
* Parameters : 
*    CHAR* Val - Status of "Missing", "Idle", "Charging", 
*                "Discharging", or "Unknown", to be returned
*    ULONG *len - string length, to be returned
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
INT mta_hal_BatteryGetStatus(CHAR* Val, ULONG *len);

/*  mta_hal_BatteryGetLife: */
/**
* Description: Get the battery life status
* Parameters : 
*    CHAR* Val - Values of "Need Replacement", or "Good", to be returned
*    ULONG *len - string length, to be returned
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
INT mta_hal_BatteryGetLife(CHAR* Val, ULONG *len);


/*  mta_hal_BatteryGetInfo: */
/**
* Description: Get the battery info
* Parameters : 
*    PMTAMGMT_MTA_BATTERY_INFO pInfo - battery info, to be returned
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
INT mta_hal_BatteryGetInfo(PMTAMGMT_MTA_BATTERY_INFO pInfo);

/*  mta_hal_BatteryGetPowerSavingModeStatus: */
/**
* Description: Get the battery Power Saving Mode Status
* Parameters : 
*    ULONG *pValue- Values of 1 for Enabled, 2 for Disabled
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
INT mta_hal_BatteryGetPowerSavingModeStatus(ULONG *pValue);

#endif /* __MTA_HAL_H__ */
 
