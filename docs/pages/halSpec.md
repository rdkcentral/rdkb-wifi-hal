
# RDKB Wifi HAL Documentation

## Version History

| Date | Author | Comment | Version |
| --- | --- | --- | --- |
| 07/28/22 | M. Kandasamy | Draft | 0.0.1 |

## Description
 Abstraction layer to the diverse functionalities a Wi-Fi-Driver provides in the several aspects of Configuration, Subscription and Commanding. Primarily used to maintain intercommunication between the user space and kernel layers. 
 The diagram below describes a high-level software architecture of the RDKB Wifi module stack.
![OneWifi-Internal-Architecture](images/OneWifi-Internal-Architecture.png)

# Component Runtime Execution Requirements

It should be statically loadable library. The lifetime of which shall exists throughout the lifetime of process.
Failure to meet these requirements will likely result in undefined and unexpected behaviour.

## Initialization and Startup

Initialize the Wifi subsystem using wifi_init() API before making any other WiFi HAL API calls. This includes initialization of all radios. Implementation specifics may dictate what initializes since different hardware implementations may have different requirements. In such architecture, Initialization of Few remote services involving initialization of a common Host-DB are implemented using constructor attributes. Here the Wifi driver is expected to be initialized from outside of the RDK middleware to perform some function before the RDK middleware is executing and ready.

During system start-up before RDK takes control, Wifi subsystem would be initialized in the LAN init sequence. The interface should be in blocked state when the component/sub-system is not ready. The init API needs to be in Wait state and keeps polling for every 10s once to check the component readiness state.

Wifi HAL API wifi_getHalCapability() call should return features/configuration supported by the HAL.

## Threading Model

WIFI HAL does not thread safe, any module which is invoking the WIFI HAL API
should ensure calls are made in a thread safe manner.
Different Wifi SOC vendors allowed to create internal threads to meet the requirements of underlaying Wifi driver module and meet the operational requirements. SOC should be responsible to synchronize between the calls, events, and clean-up the thread.

## Process Model

CccspWifiSsp agent process will take care of Initializing Wifi HAL library. At any point of time a single instance of CccspWifiSsp process will exist to Respond to any Wifi HAL related functionality to the application.

## Memory Model

WiFi HAL is responsible to pass message buffer and free it for transmit request. For Receive message HAL will pass message buffer in the callback and Wifi agent is responsible to copy to its internal buffer before callback is returned.

## Power Management Requirements

There is no requirement for the component to participate in power management.

## Asynchronous Notification Model

Asynchronous CEC transmit and receive operations following API's and callback registrations are used.
- For asynchronous management frames transmission - wifi_mgmt_frame_callbacks_register  
- For asynchronous notification on client connection - wifi_newApAssociatedDevice_callback_register
- For asynchronous notification on client deauthentication - wifi_apDeAuthEvent_callback_register
- For asynchronous notification on client dissocciation - wifi_apDisassociatedDevice_callback_register
- For asynchronous notification on client connection status - wifi_staConnectionStatus_callback_register
- For asynchronous notification on client scan results - wifi_scanResults_callback_register

## Blocking calls

Please see the blocking calls used in Wifi HAL:
- wifi_init()
- wifi_startNeighborScan()
- wifi_getHalCapability()
- wifi_setRadioOperatingParameters()
- wifi_createVAP()
- wifi_getRadioVapInfoMap()
- wifi_kickAssociatedDevice()
- wifi_startScan()
- wifi_connect()
- wifi_disconnect()

## Internal Error Handling

All the Wifi HAL APIs should return error synchronously as a return argument. HAL is responsible to handle system errors (e.g., failure of memory allocation, array boundary out of memory, return code check) internally.

## Persistence Model

WiFi HAL interface expected to persist VAP configuration set by calls to the HAL interface. This configuration should persist for device firmware upgrade and downgrade.
During the Wifi initialization VAP configuration shall be retrieved and applied to the WiFi driver.
A separate standalone config is maintained for the Reset case. A reset indicator is looked up while initialization and apply the configuration accordingly.

# Non functional requirements

Following non-functional requirement should be supported by the CEC HAL component.

## Logging and debugging requirements

Wi-Fi HAL component should log all the error and critical informative messages which helps to debug/triage the issues and understand the functional flow of the system.

The log files have naming convention depends upon the logs. There are few requirements of redirecting logs to specified files.
E.g.,
 1. Wifi initialization log file name - WiFilog.txt.0
 2. Wifi telemetry related log file name - wifihealth.txt
 3. Device Image version - version.txt
 4. Wifi HAL log file name - wifi_vendor_hal.log

## Memory and performance requirements

WiFi HAL should not contribute more to memory and CPU utilization while performing normal Wifi operations and in idle mode and STANDBY mode.

## Quality Control

WiFi HAL implementation should not introduce any warnings and errors while running with Coverity static analysis tool
There should not be any memory leaks/corruption introduced by HAL and underneath SOC software.
Basic WiFi sanity (CPU, Memory etc), regression and functionality test should be performed. 

## Licensing

 Licensed under the Apache License, Version 2.0 (the "License").
 you may not use this file except in compliance with the License.

## Build Requirements

WiFi HAL source code should be built under Linux Yocto environment and should be delivered as a shared library.

## Variability Management

Any new API introduced should be implemented by all SOC vendor and RDKB generic code will be compatible with specific version of WiFi HAL software. HAL evolution shall be managed by Compile time CFLAGS with revision info.

The capabilities of the HAL interface discovered by Feature defined Flags, version, and version history.

# Interface API Documentation

Covered as per Doxygen documentations format.

## Theory of operation and key concepts

Covered as per "Description" sections in the API documentation.

### Sequence Diagram - 1
![Sequence Diagram](images/Message_Sequence_Diagram.png)

### Sequence Diagram - 2 
![State Diagram](images/plantuml221250850097517383.png)

## Data Structures and Defines

 Refer Doxygen comments and documentation


