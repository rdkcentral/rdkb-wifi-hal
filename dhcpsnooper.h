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
#ifndef __SNOOPER_HEADER__
#define __SNOOPER_HEADER__

//#define __686__
#define __HAVE_SYSEVENT_STARTUP_PARAMS__
#define __GET_REQUESTED_IP_ADDRESS__
#define __HAVE_SYSEVENT__

#include <stdbool.h>

#ifdef __HAVE_SYSEVENT__
#include <sysevent/sysevent.h>
#endif

#define kSnooper_events                     "snooper-update"

#define kSnooper_enable                     "snooper-enable"
#define kSnooper_circuit_enable             "snooper-circuit-enable"
#define kSnooper_remote_enable              "snooper-remote-enable"
#define kSnooper_debug_enable               "snooper-debug-enable"
#define kSnooper_log_enable                 "snooper-log-enable"
#define kSnooper_max_clients                "snooper-max-clients"

#define kSnooper_circuit_id0                "snooper-queue0-circuitID"
#define kSnooper_circuit_id1                "snooper-queue1-circuitID"
#define kSnooper_circuit_id2                "snooper-queue2-circuitID"
#define kSnooper_circuit_id3                "snooper-queue3-circuitID"
#define kSnooper_circuit_id4                "snooper-queue4-circuitID"

#define kSnooper_ssid_index0                 "snooper-ssid0-index"
#define kSnooper_ssid_index1                 "snooper-ssid1-index"
#define kSnooper_ssid_index2                 "snooper-ssid2-index"
#define kSnooper_ssid_index3                 "snooper-ssid3-index"
#define kSnooper_ssid_index4                 "snooper-ssid4-index"

#define kSnooper_circuit_id_len             30
#define kSnooper_MaxClients                 30

#define kSnooper_MaxRemoteLen   20
#define kSnooper_MaxMacAddrLen  18
#define kSnooper_MaxHostNameLen 64
#define kSnooper_MaxStatusLen   10
#define kSnooper_MaxIpAddrLen   20 
#define kSnooper_MaxCircuitLen  80

typedef struct 
{
    char remote_id[kSnooper_MaxRemoteLen];      // This is the client MAC address
    char circuit_id[kSnooper_MaxCircuitLen];    // This contains the SSID;AP-MAC;Security
    char ipv4_addr[kSnooper_MaxIpAddrLen];
    char dhcp_status[kSnooper_MaxStatusLen];
    char hostname[kSnooper_MaxHostNameLen];
    int rssi;
} snooper_client_list;

typedef struct
{
    bool snooper_enabled;
    bool snooper_debug_enabled;
    bool snooper_circuit_id_enabled;
    bool snooper_remote_id_enabled;

    int  snooper_first_queue;   
    int  snooper_num_queues;
    int  snooper_max_queues;
    int  snooper_dhcp_packets;

    int  snooper_max_clients;
    int  snooper_num_clients;

    snooper_client_list snooper_clients[kSnooper_MaxClients];

}  snooper_statistics_s;

#define kSnooper_Statistics           865889 // key used for shared memory
#define kSnooper_SharedMemSize        sizeof(snooper_statistics_s)

#endif
