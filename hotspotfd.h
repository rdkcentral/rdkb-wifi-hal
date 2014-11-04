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

// -----------------------------------------------------------------------------
//
//                   Copyright 2013 Cisco Systems, Inc.
//
//                           5030 Sugarloaf Parkway
//                               P.O.Box 465447
//                          Lawrenceville, GA 30042
//
//                            CISCO CONFIDENTIAL
//              Unauthorized distribution or copying is prohibited
//                            All rights reserved
//
// No part of this computer software may be reprinted, reproduced or utilized
// in any form or by any electronic, mechanical, or other means, now known or
// hereafter invented, including photocopying and recording, or using any
// information storage and retrieval system, without permission in writing
// from Cisco Systems, Inc.
//
// -----------------------------------------------------------------------------
#ifndef __HOTSPOTFD_HEADER__
#define __HOTSPOTFD_HEADER__

#define __HAVE_SYSEVENT_STARTUP_PARAMS__
#define __HAVE_SYSEVENT__

#ifdef __HAVE_SYSEVENT__
#include <sysevent/sysevent.h>
#endif

#include <stdbool.h>

#define kMax_IPAddressLength            40

#define kHotspotfd_events                   "hotspotfd-update"

#define kHotspotfd_primary                  "hotspotfd-primary"                // ip address of primary
#define khotspotfd_secondary                "hotspotfd-secondary"              // ip address of secondary
#define khotspotfd_keep_alive               "hotspotfd-keep-alive"             // time in secs between pings
#define khotspotfd_keep_alive_threshold     "hotspotfd-threshold"              // failed ping's before switching EP
#define khotspotfd_max_secondary            "hotspotfd-max-secondary"          // max. time allowed on secondary
#define kHotspotfd_tunnelEP                 "hotspotfd-tunnelEP"               // Indicates an EP change
#define khotspotfd_keep_alive_policy        "hotspotfd-policy"                 // ICMP ping pr NONE
#define khotspotfd_keep_alive_count         "hotspotfd-count"                  // pings per keep-alive interval

#define khotspotfd_dead_interval            "hotspotfd-dead-interval"          // pings per minute when both EP's are down

#define khotspotfd_enable                   "hotspotfd-enable"
#define khotspotfd_log_enable               "hotspotfd-log-enable"

#define kHotspotfd_primary_len                  kMax_IPAddressLength             
#define khotspotfd_secondary_len                kMax_IPAddressLength           
#define khotspotfd_keep_alive_len               3
#define khotspotfd_keep_alive_threshold_len     3
#define khotspotfd_max_secondary_len            5
#define kHotspotfd_tunnelEP_len                 kMax_IPAddressLength
#define khotspotfd_policy_len                   4
#define khotspotfd_keep_alive_count_len         1

typedef struct
{
    char primaryEP[kMax_IPAddressLength];
    bool primaryIsActive;
    bool primaryIsAlive;

    char secondaryEP[kMax_IPAddressLength];
    bool secondaryIsActive;
    bool secondaryIsAlive;

    unsigned int keepAlivesSent;
    unsigned int keepAlivesReceived;
    unsigned int keepAliveInterval;
    unsigned int keepAliveThreshold;
    unsigned int keepAliveCount;
    unsigned int secondaryMaxTime;
    unsigned int switchedBackToPrimary;
    
    unsigned int discardedChecksumCnt;
    unsigned int discaredSequenceCnt;
    unsigned int deadInterval;

}  hotspotfd_statistics_s;

#define kKeepAlive_Statistics           765889 // key used for shared memory
#define kKeepAlive_SharedMemSize        sizeof(hotspotfd_statistics_s)

#endif
