# ChipControl (LTC2943 driver)
This package contains a C implementation for a LTC2943 chip driver. This module can be use to access, monitor and configure the multicell battery gas gauge. 

# Dependencies
The module is tested and configured on:

* C++17
* CMake > 3.14
* Ubuntu 22.04

# Build Dependencies
Install Linux dependencies
```
sudo apt install build-essential libssl-dev g++         // C build requirements
```

# Build Test Suite
Add a directory `external` in the root directory and install Unity as a git submodule
```
mkdir external
cd external
git submodule add https://github.com/ThrowTheSwitch/Unity.git 
```

# Build
Build by making a build directory (i.e. build/), run cmake in that dir, and then use 
make to build the desired target.

```
> mkdir build && cd build
> cmake .. -DCMAKE_BUILD_TYPE=[Debug | Coverage | Release]
> make
> make test
> ./main # Run simulator
```

# Device APIs
The device provides a number of C APIs that can be used to access measurements:
```
bool LTC2943_Initialise(); // Initialise the driver
bool LTC2943_Read(uint8_t address, uint8_t *dest, uint8_t dataSize);  // Read data from the chip @address to dest
bool LTC2973_Write(uint8_t address, uint8_t *src, uint8_t dataSize);   // Write data from src to the chip @address
```

# ChipControl Module
The package contains a number of critical functions:

## Mode setting
The driver can be configured for a number of modes: Automatic, Scan, Manual, and Sleep. The driver allows monitorng and setting of the current mode to change the driver's operating mode. The modes have the following behaviours:
 

### Automatic
### Scan 
### Manual 
### Sleep 

## Threshold Setting
The driver maintains a number of operational and survival thresholds that can be used for monitoring and alerting mechanisms. The module allows configuration of thresholds for battery charge state, voltage, current and temperature.

## Alerting
The module allows for automated checking of measurements against configured thresholds in Automatic and Scan modes. In manual mode, the measurement alerts can be polled. Alerts for the past ... minutes are persisted in the driver.

# RTOS configuration
When modifying the software sensor interface to work in an RTOS environment, will be be necessary 
to adjust the code to properly communicate with the LTC2943 and interpret the data it provides. 
The ChipControl module was implemented following general embedded software principles. However, 
There are a number of steps that can be taken to optimise the implemented sensor interface for 
an RTOS environment. 

1. Determine the hardware requirements of the RTOS. 

    This involves identifying the microcontroller or microprocessor the RTOS will be 
    running on to determine the specific modifications required to successfully integrate the 
    sensor interface.

3. Modify the software sensor interface to work within the constraints of the RTOS. 

    This may include optimizing the code to work with the specific microcontroller or 
    microprocessor. Depending on the memory and comutational limitations, the reliance on 
    external libraries may need to be minimised and certain routines optimised. 

    Additionally, the real-time nature of the RTOS may require modifications to the way data is 
    collected and processed, in order to ensure that the system is always functioning optimally. 
    The I2C interface introduces timing complexity that may require the software to take into 
    account delays from read, write, and processing procedures.
    
4. Test the modified software sensor interface in a simulated RTOS environment. 

    This will help identify any of the issues or bugs identified above that may have been 
    introduced during the modification process. A basic simulation of the LTC2943 Battery
    Gauge has been developed, but testing and validation will require more extensive and 
    robust simulated environments. A more extensive unit test suite in a variety of 
    containerised environments will increase the rate at which issues are identified.

    It is important to ensure that any modifications made to the software sensor interface do not 
    introduce new bugs or issues into the system. Thorough and continual testing, both in a 
    simulated environment and in the actual RTOS environment, will ensure that the system remains 
    functional and reliable.

5. Deploy the modified software sensor interface in the actual RTOS environment. 
    Testing and deployment of the modified software sensor interface should be carried out with 
    the LTC2943 properly integrated into the system, to ensure accurate battery level monitoring. 
    Depending on the specific requirements of the system, additional sensors may need to be 
    integrated into the interface, and the code may need to be modified to accommodate 
    these new sensors.

