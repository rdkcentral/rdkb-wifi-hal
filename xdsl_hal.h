/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2020 RDK Management
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

#ifndef _XDSL_HAL_H
#define _XDSL_HAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

/** Common definitions */
#define XDSL_MAX_LINES	1

/** Operational status of a line or channel */
typedef enum _IfStatus_t {
    IF_UP = 1,
    IF_DOWN,
    IF_UNKNOWN,
    IF_DORMANT,
    IF_NOTPRESENT,
    IF_LOWERLAYERDOWN,
    IF_ERROR
}IfStatus_t;

/** Status of the DSL physical link */
typedef enum _DslLinkStatus_t {
    LINK_UP = 1,
    LINK_INITIALIZING,
    LINK_ESTABLISHING,
    LINK_NOSIGNAL,
    LINK_DISABLED,
    LINK_ERROR
}DslLinkStatus_t;

/** DSL modulation types */
typedef enum  _DslModType_t {
    MOD_G_922_1_ANNEX_A = 1,
    MOD_G_922_1_ANNEX_B = 1 << 1,
    MOD_G_922_1_ANNEX_C = 1 << 2,
    MOD_T1_413          = 1 << 3,
    MOD_T1_413i2        = 1 << 4,
    MOD_ETSI_101_388    = 1 << 5,
    MOD_G_992_2         = 1 << 6,
    MOD_G_992_3_Annex_A = 1 << 7,
    MOD_G_992_3_Annex_B = 1 << 8,
    MOD_G_992_3_Annex_C = 1 << 9,
    MOD_G_992_3_Annex_I = 1 << 10,
    MOD_G_992_3_Annex_J = 1 << 11,
    MOD_G_992_3_Annex_L = 1 << 12,
    MOD_G_992_3_Annex_M = 1 << 13,
    MOD_G_992_4         = 1 << 14,
    MOD_G_992_5_Annex_A = 1 << 15,
    MOD_G_992_5_Annex_B = 1 << 16,
    MOD_G_992_5_Annex_C = 1 << 17,
    MOD_G_992_5_Annex_I = 1 << 18,
    MOD_G_992_5_Annex_J = 1 << 19,
    MOD_G_992_5_Annex_M = 1 << 20,
    MOD_G_993_1         = 1 << 21,
    MOD_G_993_1_Annex_A = 1 << 22,
    MOD_G_993_2_Annex_A = 1 << 23,
    MOD_G_993_2_Annex_B = 1 << 24,
    MOD_G_993_2_Annex_C = 1 << 25
}DslModType_t;

/* 
 * The line encoding method used in establishing 
 * the Layer 1 DSL connection between the CPE and the DSLAM. 
 */
typedef enum _DslLineEncoding_t {
    LINE_ENCODING_DMT = 1,
    LINE_ENCODING_CAP,
    LINE_ENCODING_2B1Q,
    LINE_ENCODING_43BT,
    LINE_ENCODING_PAM,
    LINE_ENCODING_QAM
}DslLineEncoding_t;

/* DSL VDSL2 profiles */
typedef enum _DslProfile_t {
    VDSL2_8a   = 1,
    VDSL2_8b,
    VDSL2_8c,
    VDSL2_8d,
    VDSL2_12a,
    VDSL2_12b,
    VDSL2_17a,
    VDSL2_30a,
    VDSL2_35b
}DslProfile_t; 

/*The power management state of the line */
typedef enum _DslPowerManagementState_t {
    POWER_L0 = 1,
    POWER_L1,
    POWER_L2,
    POWER_L3,
    POWER_L4
}DslPowerManagementState_t;
 
/* DSL line training status */
typedef enum _DslLineTrainingStatus_t {
    NOT_TRAINING      = 1,
    TRAINING          = 2,
    TRAINED           = 3
}DslLineTrainingStatus_t;

/** struct dsl_line - DSL line parameters */
typedef struct 
{
    bool Enable;
    char Status[64];                    /* The current operational state of the DSL line */
    unsigned int LastChange;
    bool Upstream;                      /* Whether the interface points towards the Internet (true) or towards End Devices (false) */
    char FirmwareVersion[64];           /* The version of the modem firmware currently installed for this interface */
    DslLinkStatus_t LinkStatus;         /* Status of the DSL physical link */
    char StandardsSupported[256];       /* The transmission system types or standards supported */
    unsigned char XTSE[17];
    char StandardUsed[64];              /* The currently used transmission system type, or the standard on this line instance */
    unsigned char XTSUsed[17];
    DslLineEncoding_t LineEncoding;     /* The line encoding method used in establishing the Layer 1 DSL connection between the CPE and the DSLAM */
    char AllowedProfiles[256];          /* VDSL2 profiles are allowed on the line. The bitmap is defined in enum dsl_profile */
    char CurrentProfile[64];            /* VDSL2 profile is currently in use on the line */
    DslPowerManagementState_t PowerManagementState; /* The power management state of the line */
    unsigned int SuccessFailureCause;   /* The success failure cause of the initialization */
    unsigned int UPBOKLER;
    char UPBOKLEPb[256];
    char UPBOKLERPb[256];
    int RXTHRSHds;
    unsigned int ACTRAMODEds;
    unsigned int ACTRAMODEus;
    unsigned int ACTINPROCds;
    unsigned int ACTINPROCus;
    unsigned int SNRMROCds;
    unsigned int SNRMROCus;
    unsigned int LastStateTransmittedDownstream;
    unsigned int LastStateTransmittedUpstream;
    int LineNumber;                     /* The line pair that the modem is using to connection */
    unsigned int UpstreamMaxBitRate;    /* The current maximum attainable data rate upstream (expressed in Kbps). */
    unsigned int DownstreamMaxBitRate;  /* The current maximum attainable data rate downstream (expressed in Kbps). */
    int UpstreamNoiseMargin;            /* The current signal-to-noise ratio margin (expressed in 0.1dB) in the upstream direction. */
    int DownstreamNoiseMargin;          /* The current signal-to-noise ratio margin (expressed in 0.1dB) in the downstream direction. */
    int UpstreamAttenuation;            /* The current upstream signal loss */
    int DownstreamAttenuation;          /* The current downstream signal loss */
    int UpstreamPower;                  /* The current output power at the CPE's DSL line (expressed in 0.1dBmV). */
    int DownstreamPower;                /* The current received power at the CPE's DSL line (expressed in 0.1dBmV). */
    unsigned int UPBOKLE;	            /* This parameter contains the estimated electrical loop length expressed in 0.1dB at 1MHz */
    char MREFPSDds[145];
    char MREFPSDus[145];
    unsigned int  LIMITMASK;
    unsigned int  US0MASK;
    int TRELLISds;                      /* Reports whether trellis coding is enabled in the downstream direction */
    int TRELLISus;	                    /* Reports whether trellis coding is enabled in the upstream direction */
    unsigned int ACTSNRMODEds;	        /* Reports whether the OPTIONAL virtual noise mechanism is in use in the downstream direction.*/
    int ACTSNRMODEus;	                /* Reports whether the OPTIONAL virtual noise mechanism is in use in the upstream direction */
    char VirtualNoisePSDds[97];
    char VirtualNoisePSDus[49];
    unsigned int ACTUALCE;	            /* Reports the actual cyclic extension, as the value of m, in use for the connection.*/     
    char SNRMpbus[24];	                /* The current signal-to-noise ratio margin of each upstream band */  
    char SNRMpbds[24];	                /* The current signal-to-noise ratio margin of each band. */
    char LATNds[24];                    /* Indicates the downstream line attenuation per usable band */
    char LATNus[24];                    /* Indicates the upstream line attenuation per usable band */
    char SATNds[24];                    /* Indicates the downstream signal attenuation per usable band */
    char SATNus[24];                    /* Indicates the upstream signal attenuation per usable band */
    unsigned int INMIATOds;             /* The Impulse Noise Monitoring (INM) Inter Arrival Time (IAT) Offset, measured in DMT symbols*/
    unsigned int INMIATSds;             /* The Impulse Noise Monitoring (INM) Inter Arrival Time (IAT) Step*/
    unsigned int INMCCds;               /* The Impulse Noise Monitoring (INM) Cluster Continuation value, measured in DMT symbols*/
    unsigned int INMINPEQMODEds;        /* The Impulse Noise Monitoring (INM) Equivalent Impulse Noise Protection (INP) Mode*/
    char XTURVendor[8+1];	            /* xTU-R vendor identifier as defined in G.994.1 and T1.413. MUST be represented as eight hexadecimal digits*/
    char XTURCountry[4+1];	            /* T.35 country code of the xTU-R vendor as defined in G.994.1. MUST be represented as eight hexadecimal digits */
    unsigned int XTURANSIStd;	        /* xTU-R T1.413 Revision Number as defined in T1.413 Issue 2. */
    unsigned int XTURANSIRev;	        /* xTU-R Vendor Revision Number as defined in T1.413 Issue 2. */
    char XTUCVendor[8+1];	            /* xTU-C vendor identifier as defined in G.994.1 and T1.413. */
    char XTUCCountry[4+1];	            /* T.35 country code of the xTU-C vendor as defined in G.994.1 */
    unsigned int XTUCANSIStd;	        /* xTU-C T1.413 Revision Number as defined in T1.413 Issue 2.*/
    unsigned int XTUCANSIRev;	        /* xTU-C Vendor Revision Number as defined in T1.413 Issue 2. */
}DslLineInfo_t;

typedef struct
{
    unsigned int ErroredSecs;
    unsigned int SeverelyErroredSecs;
}DslLineError_t;

typedef struct
{
    unsigned int ErroredSecs;
    unsigned int SeverelyErroredSecs;
    unsigned int X_RDK_LinkRetrain;
    unsigned int X_RDK_InitErrors;
    unsigned int X_RDK_InitTimeouts;
    unsigned int X_RDK_SuccessfulRetrains;
}DslLineCurrentDay_t;

typedef struct
{
    unsigned int ErroredSecs;
    unsigned int SeverelyErroredSecs;
    unsigned int X_RDK_LinkRetrain;
}DslLineQuarterHour_t;

typedef struct
{
    unsigned long long BytesSent;
    unsigned long long BytesReceived;
    unsigned long long PacketsSent;
    unsigned long long PacketsReceived;
    unsigned int ErrorsSent;
    unsigned int ErrorsReceived;
    unsigned int DiscardPacketsSent;
    unsigned int DiscardPacketsReceived;
    unsigned int TotalStart;
    unsigned int ShowtimeStart;
    unsigned int LastShowtimeStart;
    unsigned int CurrentDayStart;
    unsigned int QuarterHourStart;
    DslLineError_t StatsTotal;
    DslLineError_t StatsShowtime;
    DslLineError_t StatsLastShowtime;
    DslLineCurrentDay_t StatsCurrentDay;
    DslLineQuarterHour_t StatsQuarterHour;
}DslLineStats_t;

typedef enum 
{
    LINK_ENCAP_G_992_3_Annex_K_ATM,
    LINK_ENCAP_G_992_3_Annex_K_PTM,
    LINK_ENCAP_G_993_2_Annex_K_ATM,
    LINK_ENCAP_G_993_2_Annex_K_PTM,
    LINK_ENCAP_G_994_1_Auto
}LinkEncapsulation_t;

typedef struct 
{
    bool Enable;
    char Status[64];                    /* The current operational state of the Channel */
    unsigned int LastChange;            /*The accumulated time in seconds since the channel entered its current operational state*/
    unsigned int LPATH;                 /*Reports the index of the latency path supporting the bearer channel.*/
    unsigned int INTLVDEPTH;            /*Reports the index of the latency path supporting the bearer channel.*/
    int INTLVBLOCK;                     /*Reports the interleaver block length in use on the latency path indicated in LPATH.*/
    unsigned int ActualInterleavingDelay; /*Reports the actual delay, in milliseconds, of the latency path due to interleaving.*/
    int ACTINP;                          /*Reports the actual impulse noise protection (INP) provided by the latency path indicated in LPATH*/
    bool INPREPORT;                      /*Reports whether the value reported in ACTINP was computed assuming the receiver does not use erasure decoding.*/
    int NFEC;                            /*Reports the size, in octets, of the Reed-Solomon codeword in use on the latency path indicated in LPATH.*/
    int RFEC;                            /*Reports the number of redundancy bytes per Reed-Solomon codeword on the latency path indicated in LPATH.*/
    int LSYMB;                           /*Reports the number of bits per symbol assigned to the latency path indicated in LPATH.*/
    unsigned int UpstreamCurrRate;       /*The current physical layer aggregate data rate (expressed in Kbps) of the upstream DSL connection.*/
    unsigned int DownstreamCurrRate;     /*The current physical layer aggregate data rate (expressed in Kbps) of the downstream DSL connection.*/
    unsigned int ACTNDR;
    unsigned int ACTINPREIN;
}DslChannel_t;

typedef struct
{
    unsigned int XTURFECErrors; /*Number of FEC errors detected*/
    unsigned int XTUCFECErrors; /*Number of FEC errors detected by the ATU-C*/
    unsigned int XTURHECErrors; /*Number of HEC errors detected*/
    unsigned int XTUCHECErrors; /*Number of HEC errors detected by the ATU-C*/
    unsigned int XTURCRCErrors; /*Number of CRC errors detected*/
    unsigned int XTUCCRCErrors; /*Number of CRC errors detected by the ATU-C*/
}DslChannelError_t;

typedef struct
{
    unsigned int XTUCFECErrors; /*Number of FEC errors detected*/
    unsigned int XTURFECErrors; /*Number of FEC errors detected by the ATU-C*/
    unsigned int XTURHECErrors; /*Number of HEC errors detected*/
    unsigned int XTUCHECErrors; /*Number of HEC errors detected by the ATU-C*/
    unsigned int XTURCRCErrors; /*Number of CRC errors detected*/
    unsigned int XTUCCRCErrors; /*Number of CRC errors detected by the ATU-C*/
    unsigned int X_RDK_LinkRetrain;
}DslChannelQuarterHour_t;


typedef struct
{
    unsigned int XTUCFECErrors; /*Number of FEC errors detected*/
    unsigned int XTURFECErrors; /*Number of FEC errors detected by the ATU-C*/
    unsigned int XTURHECErrors; /*Number of HEC errors detected*/
    unsigned int XTUCHECErrors; /*Number of HEC errors detected by the ATU-C*/
    unsigned int XTURCRCErrors; /*Number of CRC errors detected*/
    unsigned int XTUCCRCErrors; /*Number of CRC errors detected by the ATU-C*/
    unsigned int X_RDK_LinkRetrain;
    unsigned int X_RDK_InitErrors;
    unsigned int X_RDK_InitTimeouts;
    unsigned int X_RDK_SeverelyErroredSecs;
    unsigned int X_RDK_ErroredSecs;
}DslChannelCurrentDay_t;


typedef struct 
{
    unsigned long long BytesSent;
    unsigned long long BytesReceived;
    unsigned long long PacketsSent;
    unsigned long long PacketsReceived;
    unsigned int ErrorsSent;
    unsigned int ErrorsReceived;
    unsigned int DiscardPacketsSent;
    unsigned int DiscardPacketsReceived;
    unsigned int TotalStart;
    unsigned int ShowtimeStart;
    unsigned int LastShowtimeStart;
    unsigned int CurrentDayStart;
    unsigned int QuarterHourStart;
    DslChannelError_t StatsTotal;
    DslChannelError_t StatsShowtime;
    DslChannelError_t StatsLastShowtime;
    DslChannelCurrentDay_t  StatsCurrentDay;
    DslChannelQuarterHour_t StatsQuarterHour; 
}DslChannelStats_t;

/*  ADSL Diagnostics enum and structure  */

typedef enum
{
    ADSL_DIAG_STATE_None           = 1,
    ADSL_DIAG_STATE_Requested,
    ADSL_DIAG_STATE_Canceled,
    ADSL_DIAG_STATE_Complete,
    ADSL_DIAG_STATE_Error,
    ADSL_DIAG_STATE_Error_Internal,
    ADSL_DIAG_STATE_Error_Other,
} DslDiagState_t;

typedef enum
{
    ADSL_LINE_TEST                 = 1,
    SELTUER,
    SELTQLN,
    SELTP
} DslDiagTestType_t;

typedef  struct
{   
    char                              DiagnosticsState[64];
    int                               ACTPSDds;
    int                               ACTPSDus;
    int                               ACTATPds;
    int                               ACTATPus;
    int                               HLINSCds;
    int                               HLINSCus;
    unsigned int                      HLINGds;
    unsigned int                      HLINGus;
    unsigned int                      HLOGGds;
    unsigned int                      HLOGGus;
    char                              HLOGpsds[2560];
    char                              HLOGpsus[2560];
    unsigned int                      HLOGMTds;
    unsigned int                      HLOGMTus;
    char                              LATNpbds[24];
    char                              LATNpbus[24];
    char                              SATNds[24];
    char                              SATNus[24];
    char                              HLINpsds[61430];
    char                              HLINpsus[61430];
    unsigned int                      QLNGds;
    unsigned int                      QLNGus;
    char                              QLNpsds[61430];
    char                              QLNpsus[61430];
    unsigned int                      QLNMTds;
    unsigned int                      QLNMTus;
    unsigned int                      SNRGds;
    unsigned int                      SNRGus;
    char                              SNRpsds[61430];
    char                              SNRpsus[61430];
    unsigned int                      SNRMTds;
    unsigned int                      SNRMTus;
    char                              BITSpsds[61430];
    char                              BITSpsus[61430];
}DslDiagAdslLineTest_t;

typedef  struct
{
    char                     DiagnosticsState[64];
    unsigned int             UERMaxMeasurementDuration;
    bool                     ExtendedBandwidthOperation;
    char                     UER[4096];
    unsigned int             UERScaleFactor;
    unsigned int             UERGroupSize;
    char                     UERVar[4096];
}
DslDiagSeltuer_t;

typedef  struct
{
    char                     DiagnosticsState[64];
    unsigned int             QLNMaxMeasurementDuration;
    bool                     ExtendedBandwidthOperation;
    char                     QLN[61430];
    unsigned int             QLNGroupSize;
}
DslDiagSeltqln_t;

typedef  struct
{
    char                     DiagnosticsState[64];
    bool                     CapacityEstimateEnabling;
    char                     CapacitySignalPSD[1024];
    char                     CapacityNoisePSD[1024];
    unsigned int             CapacityTargetMargin;
    char                     LoopTermination[24];
    unsigned int             LoopLength;
    char                     LoopTopology[256];
    char                     AttenuationCharacteristics[61430];
    bool                     MissingFilter;
    unsigned int             CapacityEstimate;
}
DslDiagSeltp_t;

typedef  struct
{
    DslDiagAdslLineTest_t     stDiagADSLLineTest;
    DslDiagSeltuer_t           stDiagSELTUER;
    DslDiagSeltqln_t           stDiagSELTQLN;
    DslDiagSeltp_t             stDiagSELTP;
}
DslDiagnosticsFull_t;

typedef  struct
{
     int           echotonoiseratio;
}
DslXRdkNlm_t;

/**
 * This callback sends to upper layer when it receives link status from  DSL driver
 *
 * @return 0 on success. Otherwise a negative value is returned
 */
typedef int (*dsl_link_status_callback)(char *ifname, DslLinkStatus_t dsl_status );

/**
 * This function initialize and start DSL driver
 *
 * @return 0 on success. Otherwise a negative value is returned
 */
int xdsl_hal_init( void );

/**
 * This function sets the function pointer which receives link status event from driver
 *
 * @param[in] link_status_cb - The function pointer which receives link status event from driver.
 *                             if NULL then need to deregister this callback
 *
 * @return 0 on success. Otherwise a negative value is returned
 */
int xdsl_hal_registerDslLinkStatusCallback(dsl_link_status_callback link_status_cb);

/**
 * This function gets the enable status of DSL line
 *
 * @param[in] lineNo - The line number which starts with 0
 * @param[out] enable status The output parameter to receive the data
 *
 * @return 0 on success. Otherwise a negative value is returned
 */
int xdsl_hal_dslGetLineEnable( int lineNo, unsigned char *enable );

/**
 * This function sets the enable/disble of DSL line
 *
 * @param[in] lineNo - The line number which starts with 0
 * @param[in] enable   - configure DSL line
 *
 * @return 0 on success. Otherwise a negative value is returned
 */
int xdsl_hal_dslSetLineEnable( int lineNo, unsigned char enable );

/**
 * This function sets the enable/disble for data gathering of DSL line
 *
 * @param[in] lineNo - The line number which starts with 0
 * @param[in] enable   - configure DSL line
 *
 * @return 0 on success. Otherwise a negative value is returned
 */
int xdsl_hal_dslSetLineEnableDataGathering( int lineNo, unsigned char enable );

/**
 * This function gets the number of DSL lines
 *
 * @return the number of DSL lines on success. Otherwise a negative value is returned.
 *
 */
int xdsl_hal_getTotalNoOfLines(void);

/**
 * This function gets the number of DSL channels corresponding line
 *
 * @param[in] lineNo - The line number which starts with 0
 * @return the number of DSL channels on success. Otherwise a negative value is returned.
 *
 */
int xdsl_hal_getTotalNoofChannels(int lineNo);

/**
 * This function gets the DSL line information
 *
 * @param[in] lineNo - The line number which starts with 0
 * @param[out] lineInfo - The output parameter to receive the data
 *
 * @return 0 on success. Otherwise a negative value is returned
 */
int xdsl_hal_dslGetLineInfo(int lineNo, DslLineInfo_t *lineInfo);

/**
 * This function gets the statistics counters of a DSL line
 *
 * @param[in] lineNo - The line number which starts with 0
 * @param[out] lineStats The output parameter to receive the data
 *
 * @return 0 on success. Otherwise a negative value is returned
 */
int xdsl_hal_dslGetLineStats(int lineNo, DslLineStats_t *lineStats);

/**
 * This function gets the DSL channel information
 *
 * @param[in] lineNo - The line number which starts with 0
 * @param[in] channelNo - The channel number which starts with 0
 * @param[out] channelInfo The output parameter to receive the data
 *
 * @return 0 on success. Otherwise a negative value is returned
 */
int xdsl_hal_dslGetChannelInfo(int lineNo, int channelNo, DslChannel_t *channelInfo);

/**
 * This function gets the statistics counters of a DSL channel
 *
 * @param[in] lineNo - The line number which starts with 0
 * @param[in] channelNo - The channel number which starts with 0
 * @param[out] channelStats The output parameter to receive the data
 *
 * @return 0 on success. Otherwise a negative value is returned
 */
int xdsl_hal_dslGetChannelStats(int lineNo, int channelNo, DslChannelStats_t* channelStats);

/* ADSL Diagnostis */

/**
 * This function gets the Diagnostic of ADSL Line
 *
 * @param[in] channelNo - The channel number which starts with 0
 * @param[out] AdslLineTest The output parameter to receive the data
 *
 * @return 0 on success. Otherwise a negative value is returned
 */
int xdsl_hal_dslGetDiagnosticAdslLineTest(int lineNo, DslDiagAdslLineTest_t *AdslLineTest);

/**
 * This function gets the Diagnostic Seltuer
 *
 * @param[in] channelNo - The channel number which starts with 0
 * @param[out] DiagSeltuer The output parameter to receive the data
 *
 * @return 0 on success. Otherwise a negative value is returned
 */
int xdsl_hal_dslGetDiagnosticSeltuer(int lineNo, DslDiagSeltuer_t *DiagSeltuer);

/**
 * This function gets the Diagnostic Seltqln
 *
 * @param[in] channelNo - The channel number which starts with 0
 * @param[out] DiagSeltqln The output parameter to receive the data
 *
 * @return 0 on success. Otherwise a negative value is returned
 */
int xdsl_hal_dslGetDiagnosticSeltqln(int lineNo, DslDiagSeltqln_t *DiagSeltqln);

/**
 * This function gets the Diagnostic Seltp
 *
 * @param[in] channelNo - The channel number which starts with 0
 * @param[out] DiagSeltp The output parameter to receive the data
 *
 * @return 0 on success. Otherwise a negative value is returned
 */
int xdsl_hal_dslGetDiagnosticSeltp(int lineNo, DslDiagSeltp_t *DiagSeltp);

/**
 * This function starts the Line Diagnostics
 *
 * @param[in] lineNo - The line number which starts with 0
 * @param[in] DslDiagState_t The diagnostics state to start the test
 *
 * @return 0 on success. Otherwise a negative value is returned
 */
int xdsl_hal_dslDiagnosticTestStart(int lineNo, DslDiagTestType_t type);

/**
 * This function retrieves echotonoiseratio
 *
 * @param[in] DslXRdkNlm_t The diagnostics state to start the test
 *
 * @return 0 on success. Otherwise a negative value is returned
 */
int xdsl_hal_dslGetXRdk_Nlm(DslXRdkNlm_t *nlmInfo);

#ifdef __cplusplus
}
#endif
#endif /* _XDSL_HAL_H */






