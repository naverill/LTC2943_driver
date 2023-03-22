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
