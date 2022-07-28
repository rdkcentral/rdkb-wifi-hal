
# RDKB Wifi HAL Documentation

## History

| Date | Author | Comment | Version |
| --- | --- | --- | --- |
| 28/07/22 | M. Kandasamy | Draft | 0.0.1 |

## Description

Abstraction layer to the diverse functionalities a WiFi-Driver provides in the several aspects of Configuration, Subscription and Commanding. Primarily used to maintain intercommunication between the user space and kernel layers.

# Component Runtime Execution Requirements

It is statically loaded library. The lifetime of which exists throughout the lifetime of process.

Failure to meet these requirements will likely result in undefined and unexpected behaviour.

## Initialization and Startup

No specific Initialization is required, unless housed in a Host-offload architecture. In such architecture, Initialization of Few remote services involving initialization of a common Host-DB are implemented using constructor attributes. So Type-2 is the closest option.

Is the RDK-B middleware expected to have complete control over the life cycle over the entity controlled by the interface?  

E.g., we have potential two types of entity for which an interface is being abstracted:

  1. An entity that only needs to exist from initialisation and termination by the and RDK MW manager. When initialised, all resources are acquired, any hardware is opened and configured as a result of calls to interface methods and when terminated all resources are released. Typically the implementation would be self-contained within the library exposing the HAL interface, very probably providing a direct mapping onto a Linux device through a dev node

  2. An entity for which the HAL interface is a proxy. Here the entity is expected to be initialized from outside of the RDK middleware to perform some function before the RDK middleware is executing and ready

The first type is relatively straight forward, the second is more problematic and needs to be called out and special cases need to be defined:

  1. What should happen when the component/sub-system is not ready. Should the interface block or return not ready. How should the client behave in both respects?  
A) The interface should block. The init. API may have go into Wait state and keeps polling every 10s to unblock.

  2. Certain subsystems may have responsibility during system startup before RDK takes control. e.g FrontPanel, Panel and HDMI need to display a splash, etc. What is then the behaviour of the interface and how should it affect this initial state. When is the control hand-over and what state is the sub-system left in at that point? When is the sub-system initialized?  
  A) No significant impact. No handover. It's dynamically put to use by the subsystem. The subsystem operation may have no impact but the User Requirements may not fulfilled. Subsystem is initialized in the LAN init sequence.
  
All these points and others need to be called out so that the system behaves
in a deterministic manner, every time.

## Threading Model

Is it a requirement for the methods exposed by the interface to be thread
safe?
A) Not necessarily.

Another point is to define whether the library exposing the interface is allowed to create threads. If it is allowed, explain the constraints, if any, around signal handling that the component needs to comply with. If the library is not allowed to create threads, and a separate thread of execution is required, it is likely that this dictates the need for a separate process and the proxy information above applies.
A) HAL is allowed to create threads. Subscription of several services and catering to those are implemented as separate threads.

## Process Model

Is it a requirement for the component to support multiple instantiation from multiple processes, or is there only ever one process that uses the interface?
A) Multiple processes can statically link and ride the HAL.

## Memory Model

If the interface is expected to allocate and return pointers to memory, what are the expected rules with respect to ownership, clean up and termination.
A) Bi-directional. Some APIs may allocate memory in HAL and expects upper layers to free it. while, some APIs free the memory in same functional block.

## Power Management Requirements

Is there a requirement for the component to participate in power management.  
A) Not applicable.

If so how?  
e.g.  
Is it explicit: The component is terminated by the client before entering a
low power state and it expected that the component puts any associated
hardware in a low power mode?  
Is it implicit, in that when the system, is put in a low power state the
associated hardware is put into a low power state by the operating system
cooperating with the drivers?  
etc.

## Asynchronous Notification Model

Must the component support asynchronous notifications?  
If yes what is the approach?  
Callbacks?  A) Yes
Blocked call? A) Yes
If callbacks, the component will be providing the execution context, what are
the threading rules?
A) Calling thread may have to read the return codes.
If messages are shared, what are responsibilities for managing the memory
allocation, etc.
A) In this case, memory is atmost shared between 2 layers. In many cases, Execution is sequential and
   upon successful execution, memory is handled likewise. Sometimes, Proper synchronisation is adopted with return codes.

## Blocking calls

Are any of the exposed methods allowed to block (sleep or make system calls
that can block)?  
A) Yes

Call out specific methods that are allowed to block.
A)  wifi_init()
    Following are Not allowed, but may block occasionally,
    wifi_startNeighborScan
    wifi_apDisassociatedDevice_callback_register
    wifi_newApAssociatedDevice_callback_register
    wifi_mgmt_frame_callbacks_register

How is a blocked call prematurely terminated? No manual possibility. It's automatically terminated after Fulfillment / wait for poll period.

## Internal Error Handling

If the component detects an internal error (e.g. out of memory) what should it
do?
A) This is not handled at component level. Rely on SIGKILL.

## Persistence Model

Is the sub-system interfaced to by the HAL interface expected to remember any
configuration set by calls to the HAL interface?
A) YES  
How and when is the expected configuration to be applied. Linked to
Initialization and startup above.
A) Predominantly during the subsystem init's.
If configuration is expected to be maintained, how is it reset back to
defaults and what implications are there w.r.t upgrading and downgrading of
the subsystem.
A) A seperate standalone config is maintained for the Reset case. Also, the Client abstracted
would always be in sync with the defaulted config.
How would this be managed?
A) A seperate reset indicator is looked up while initialisation and acted accordingly.

# Non functional requirements

Any non-functional requirements not specific to the operation of the
components and interfaces.
A) Retrieving revisions and capabilities.

## Logging and debugging requirements

Is the component expected to provide logging for debug and diagnostic
purposes?  
A) Yes
If yes, are there any rules (file naming conventions, etc.) that the component
should abide by?
A) No. Yet, there are few requirements of redirecting logs to specified files.

## Memory and performance requirements

Where memory and performance are of concern, Architecture may of imposed
limits on memory and CPU usage.
When the component is delivered, is there a requirement to state memory and
CPU usage statistics for auditing purposes
A) No

## Quality Control

Are there any requirements for the use of static code analysis tools:

e.g. Coverity, Black duck, etc.

Testing requirements: valgrind, etc. Any specific test to focus on, e.g.
longevity testing, etc.

What specific component tests should be run.
A) All sorts of coverity and memory analysis tools may prove beneficial.

## Licensing

Are there any licensing requirements?
A) YES. Common Repo is subjected to GPLV 2.0 license, While Additional OEM patches may not.

## Build Requirements

Any build requirements, specific tooling, library format, etc.
versions of specific support libraries. Ideally this would be a systemwide for
the RDK.
A) No. Regular ANSI C toolchain would be enough.

## Variability Management

How is evolution managed?
A) Compile time CFLAGS with revision info mentioned in Version and Version History.

What optional methods are there and how are the capabilities of the interface
discovered?
A) Feature defined Flags. Seperation of files in the build sequence with every introduced versions.
If a method is not supported by a component or component dependent hardware.

How is that managed?
A) Vendor specific Flags or device specific C defines.

Is there an expected approach for managing different interface library
versions?
A) all of the above

What approaches have been taken to make the interface extensible and amenable
to customization on a per product basis. For example, picture modes on TV
products are defined on a per product basis. The interface therefore
implements a discovery method to obtain and set product defined
configurations.  
Call out that this is expected and that at integration, work would be required
to define these product defined configuration.
A) The driving layers are expected to use the provisional APIs to retrieve the supported standards and act accordingly.

# Interface API Documentation

The information above mostly, but not only, details how the component/sub-
system behaves, realizes the interface, and the requirements/constrains that
it must abide by in doing so.  
This information below is more focused on how the interface should be used by
the client.

Any specific coding conventions that should be followed when extending the
interface.
A) Standard guidelines. Nothing specific.

## Theory of operation and key concepts

Describe anything useful to the stakeholders to help them understand the
expected operation of the interfaced component/s.  
For example,

If the component is expected to create instances of objects then describe
their life cycle and how they are identified.  
Is there an order in which methods are expected to be called?  
For example:

  1. Initialization/Open

  2. Configure

  3. Start

Are there specific methods that will only be called when in a specific state.  
Is there a state model?

State diagrams, sequence diagram, etc. are always a useful tool to describe
all the behavioural aspects of the components.### Example Diagrams

### Example Sequence Diagram

![Example Sequence Diagram](sequence1.png)

### Example sequenceDiagram using mermaid

[mermaid Diagrams](https://mermaid-js.github.io/mermaid)

```mermaid
sequenceDiagram
    participant Alice
    participant Bob
    Alice->>John: Hello John, how are you?
    loop Healthcheck
        John->>John: Fight against hypochondria
    end
    Note right of John: Rational thoughts <br/>prevail!
    John-->>Alice: Great!
    John->>Bob: How about you?
    Bob-->>John: Jolly good!
```

#### Example State Diagram

![Example State Diagram](state1.png)

### Example State Diagram using mermaid

[mermaid Diagrams](https://mermaid-js.github.io/mermaid)

```mermaid
stateDiagram-v2
    state if_state <<choice>>
    [*] --> IsPositive
    IsPositive --> if_state
    if_state --> False: if n < 0
    if_state --> True : if n >= 0
```

```
<div class="mermaid">
graph LR
  A --- B
  B-->C[fa:fa-ban forbidden]
  B-->D(fa:fa-spinner);
</div>
```

## Data Structures and Defines

Each data structure should have a description of its role.  
Each field should have a description if it adds value. unsigned int index;
//is an index . Adds no value. "//Is an index to the array of foobars, to
select the foobar. " adds value.

## For Each Method

* Description

  * Detailed semantic description on how to use.

* Argument description, range of valid values, array lengths, etc.
  
  * Be especially careful with string arrays. Ideally the function would define exactly the mutability of the array contents.
    The classic error is where the client passes a pointer to a character array that has been created on the caller stack. If this is unknown to the component it may simply store the pointer value to the string expecting it to be valid if used at a later time.

* Pre-conditions: What must be done before calling. What happens if the pre-condition is not met

* Post-conditions: What is the successful result

* Return values. All possible return values and why

* Error handling. Based on the error returned what should the Client do

* Is the method allowed to block?

* Is the method thread safe?

More on buffers:
char* is a mutable pointer to a mutable character/string.

const char*is a mutable pointer to an immutable character/string. You cannot change the contents of the location(s) this pointer points to. Also, compilers are required to give error messages when you try to do so. For the same reason, conversion from const char* to char* is deprecated.

char* const is an immutable pointer (it cannot point to any other location) but the contents of location at which it points are mutable.

const char* const is an immutable pointer to an immutable character/string.
