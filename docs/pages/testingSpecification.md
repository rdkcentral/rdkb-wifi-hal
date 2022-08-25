# RDK-B Wifi HAL Testing Specification

# History

|Date|Author|Version|Comment|
|----|------|-------|-------|
|11/5/22|G. Weatherup| V0.2| Status Update 11/5/22|
|09/5/22|G. Weatherup| V0.1| Draft Revision|

## References

`HAL Unit Testing` - This document is based on the HAL Unit testing document and follows the principles defined there.

## WIFI Hal what is going to be tested

The following link contains the latest HAL Interface specification for RDK-B.

|Requirements for testing|Comment|Functions|
|------------------------|-------|---------|
|wifi_hal_ap.h| AP Interface|58|
|wifi_hal_client_mgt.h| Client Manager|31|
|wifi_hal_deprecated.h| Old Deprecated API's|105|
|wifi_hal_extender.h| Plume Mesh API / Extender API's|20|
|wifi_hal_generic.h| Generic Init / Reset / LED Control|7|
|wifi_hal.h| Main include hal|0|
|wifi_hal_radio.h| Configure / read & reset radio|34|
|wifi_hal_sta.h| STA VAP Control Interface|5|
|wifi_hal_telemetry.h| Wifi measure and Telemetry|10|
|wifi_hal_emu.h|  Not included by the main interface |18|
|Total| Total Number of Interfaces | 288 |

https://code.rdkcentral.com/r/plugins/gitiles/rdkb/components/opensource/ccsp/halinterface/+/refs/heads/rdk-next

## Level 1 Testing Requirements

- Mock all the interfaces
	- To prove that it's possible to build independently without hardware
	- This is also useful for checking that the interface comply with the correct include requirements for independence
	- The mocking framework will create `ExpectAndReturn` type functions for each of the functions which can be called to prove the interface positive & negative in the test skeleton
- Skeleton test creation
	- Create a test for each of the main modules, to prepare if to be filled out with Level 1 type tests.
- Write test cases for positive / negative, max , min, testing of each param for each interface.

## Level 2 Testing Module Testing

The purpose of the test level is to test the module functionality as much as possible from an operational point of view.

- Independent test application that will run without the RDK
- Start the HAL interface
- Application to start up the HAL and perform Black Box Testing

- Skeleton test creation
	- Create a test for each of the main functional areas to meet the below requirements, these will cover in the first instance the information below.

### Bootup

The test should be able test that the HAL interface is present, and that it's active and ready to be called.

If the independent API is developed.

### Factory Reset

The test should be able to trigger a factory reset from the command line, and check that the reset has occurred

- Trigger the factory reset
- Check that the factory reset has been 

### Set / Get Params

- Set params via the HAL interface and check that those params via the command line.
- More details to be provided

### Upgrade / Downgrade Wifi

- TBC on gary on this one, there's no actual downgrade that I know off, just a complete image replacement.

### Steering

- Don't know what this one was.

## Level 3 Testing

External Stimuli testing.. Does the interface in the case of Wifi perform externally correctly..

Examples of which are
	- is the SSID visible outside of the box
	- does the wifi come up when the box is reset
	- how much throughput is available on the interface, peer to peer
		- Control of the peer to peer devices

### Performance testing

- Setup two devices and perform a peer to peer performance test using iPerf.

# Framework proof of concept - Status 10/5/22

- Selection of unity testing framework to give examples of type of mocking and test  that will allow independent HAL Tests to be created

- CUnit wasn't used at this time, due to the unity framework having mocking capability and also skeleton generation, which will aid in the development of `HAL`  tests.
- 
- First sample code generated with unity framework, http://www.throwtheswitch.org

- Meeting organised with Dominic D'Souza to discuss Google Test (12/5/22)
	- How it's currently used on the RDK framework
	- How well is it suited to the requirements for the `HAL`
	- Should that be used in preference, can it be ran independently of `RDK` infrastructure

- Proof of concept can now be achieved with the following minimal requirements

|Requirement|Comment|
|-----------|---|
|Toolchain|Access to the target toolchain is required to build the tests to run on the target hardware|
|`HAL` headers| This is the test requirements spec from both documentation and also from header definitions|
|`hal.so`| Can be provided by the 3rd Party Environment, or from `RDK` |
| `Ceedling` | `Unity Ceedling` - OpenSource framework scripts, available for download|
| `Mocking`| Using `CMock` it's possible to isolate the HAL from the `RDK` stack and mock up the complete framework.. This will allow detailed unit testing of the upper layers without the requirement for hardware. This can provide full test coverage of the upper layers. Example `HAL` - 'Mock' library has been generated.|

- This means that any development team using their own reference board can prove via the testing infrastructure that the will pass unit testing.

## Issues with the current `HAL` interface for rdk-b

### Header files don't include all their dependants

Some of the header files are required to build the sources, but the header files should contain their own dependants.

#### wifi_hal_generic.h Issue

The header files assume that `wifi_hal.h` is used, and they cannot independently included.

 ```
#include <wifi_hal_telemtry.h>
```

Generic is required

 ```
#include <wifi_hal_generic.h>
#include <wifi_hal_telemtry.h>
```

#### wifi_hal_extender.h

`wifi_hal_extender.h` uses `wifi_rssi_snapshot_t` type but this is only defined in `wifi_hal_telemtry.h` but not included.

`wifi_hal_extender.h` uses `wifi_neighborScanMode_t` type but this is only defined in `wifi_hal_ap.h` but not included.

### Missing types not included

Types are not included for the header file, the following list is required.

```
    - size_t
    - INT
    - BOOL
    - UINT
    - CHAR
    - UCHAR
    - ULONG
    - USHORT
```

### Wifi_hal_emu - incorrect definition

wifi_hal_emu.h has the incorrect definition for re-entrance, and uses the WIFI_HAL definition.

```
#ifndef __WIFI_HAL_H__
#define __WIFI_HAL_H__
```

should be

```
#ifndef __WIFI_HAL_EMU_H__
#define __WIFI_HAL_EMU_H__
```

## Example output of a framework run via Unity

- This is a framework basic example generating tests for each of the modules, although the detail is not yet filled out, the framework of tests is available.

- In reality it would be useful to prefix the tests with l1, l2 etc. so that it's clearer in the framework what test performs at which level.

```
Test 'test_wifi_hal.c'
----------------------
Generating runner for test_wifi_hal.c...
Compiling test_wifi_hal_runner.c...
Compiling test_wifi_hal.c...
Compiling wifi_hal.c...
Linking test_wifi_hal.out...
Running test_wifi_hal.out...


Test 'test_wifi_hal_ap.c'
-------------------------
Generating runner for test_wifi_hal_ap.c...
Compiling test_wifi_hal_ap_runner.c...
Compiling test_wifi_hal_ap.c...
Linking test_wifi_hal_ap.out...
Running test_wifi_hal_ap.out...


Test 'test_wifi_hal_client_mgt.c'
---------------------------------
Generating runner for test_wifi_hal_client_mgt.c...
Compiling test_wifi_hal_client_mgt_runner.c...
Compiling test_wifi_hal_client_mgt.c...
Compiling wifi_hal_client_mgt.c...
Linking test_wifi_hal_client_mgt.out...
Running test_wifi_hal_client_mgt.out...


Test 'test_wifi_hal_emu.c'
--------------------------
Generating runner for test_wifi_hal_emu.c...
Compiling test_wifi_hal_emu_runner.c...
Compiling test_wifi_hal_emu.c...
Compiling wifi_hal_emu.c...
Linking test_wifi_hal_emu.out...
Running test_wifi_hal_emu.out...


Test 'test_wifi_hal_extender.c'
-------------------------------
Running test_wifi_hal_extender.out...


Test 'test_wifi_hal_generic.c'
------------------------------
Generating runner for test_wifi_hal_generic.c...
Compiling test_wifi_hal_generic_runner.c...
Compiling test_wifi_hal_generic.c...
Linking test_wifi_hal_generic.out...
Running test_wifi_hal_generic.out...


Test 'test_wifi_hal_radio.c'
----------------------------
Generating runner for test_wifi_hal_radio.c...
Compiling test_wifi_hal_radio_runner.c...
Compiling test_wifi_hal_radio.c...
Compiling wifi_hal_radio.c...
Linking test_wifi_hal_radio.out...
Running test_wifi_hal_radio.out...


Test 'test_wifi_hal_sta.c'
--------------------------
Generating runner for test_wifi_hal_sta.c...
Compiling test_wifi_hal_sta_runner.c...
Compiling test_wifi_hal_sta.c...
Compiling wifi_hal_sta.c...
Linking test_wifi_hal_sta.out...
Running test_wifi_hal_sta.out...


Test 'test_wifi_hal_telemetry.c'
--------------------------------
Generating runner for test_wifi_hal_telemetry.c...
Compiling test_wifi_hal_telemetry_runner.c...
Compiling test_wifi_hal_telemetry.c...
Linking test_wifi_hal_telemetry.out...
Running test_wifi_hal_telemetry.out...

--------------------
IGNORED TEST SUMMARY
--------------------
[test_wifi_hal.c]
  Test: test_wifi_hal_NeedToImplement
  At line (18): "Need to Implement wifi_hal"

[test_wifi_hal_ap.c]
  Test: test_wifi_hal_ap_NeedToImplement
  At line (18): "Need to Implement wifi_hal_ap"

[test_wifi_hal_client_mgt.c]
  Test: test_wifi_hal_client_mgt_NeedToImplement
  At line (18): "Need to Implement wifi_hal_client_mgt"

[test_wifi_hal_emu.c]
  Test: test_wifi_hal_emu_NeedToImplement
  At line (17): "Need to Implement wifi_hal_emu"

[test_wifi_hal_extender.c]
  Test: test_wifi_hal_extender_NeedToImplement
  At line (20): "Need to Implement wifi_hal_extender"

[test_wifi_hal_generic.c]
  Test: test_wifi_hal_generic_NeedToImplement
  At line (18): "Need to Implement wifi_hal_generic"

[test_wifi_hal_radio.c]
  Test: test_wifi_hal_radio_NeedToImplement
  At line (18): "Need to Implement wifi_hal_radio"

[test_wifi_hal_sta.c]
  Test: test_wifi_hal_sta_NeedToImplement
  At line (18): "Need to Implement wifi_hal_sta"

[test_wifi_hal_telemetry.c]
  Test: test_wifi_hal_telemetry_NeedToImplement
  At line (18): "Need to Implement wifi_hal_telemetry"

--------------------
OVERALL TEST SUMMARY
--------------------
TESTED:  9
PASSED:  0
FAILED:  0
IGNORED: 9
```


# Framework Next Steps - 12/5/22

## Google test

- Discuss GTest framework, and provide `mock` environement if this is deemed a sensible way forward after discussions with dominic

## Unity framework

- Add some specific L1 tests for a complete module, e.g. `wifi_hal_generic.h`  so that they can be ran on the target hardware correctly.
- Tidy the build environement to generate
	- doxygen comments from the source
	- re-structure the framework so that it could be deployed as an example
- Create better method to identify the target requirements, include path, toolchain path, target libraries etc. used in yocoto, and how this can be guarenteed to be references for future builds.

## General Steps

- Choose a framework, perform proof of concept, if that is required.
- Review for staged release delivery
- Engage with team to define and extend the hal tests for the team, so that all 288 functions can be covered.
- Consider methods for L3 testing coveage, will this use currently simple framework python scripts that sky already have. Or another method?

- Create example deployment package for delivery to `OEM` / `Soc` vendors, and write up documentaiton to support this.



