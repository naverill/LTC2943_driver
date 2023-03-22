#ifndef LTC2943_SIM_H
#define LTC2943_SIM_H

#include <stdint.h>
#include <stdbool.h>
#include "ltc2943_config.h"

struct LTC2943_Measurement_t {
    float CHARGE;
    float VOLTAGE;
    float CURRENT;
    float TEMP;
};

struct LTC2943_Status_t status = {
    1,  // UNDERVOLTAGE_LOCKOUT 
    0,  // VOLTAGE  
    0,  // CHARGE_LOW 
    0,  // CHARGE_HIGH 
    0,  // TEMP 
    0,  // ACC_CHARGE 
    0   // CURRENT
};

struct LTC2943_Config_t config = {
    SLEEP,      // ADC_MODE 
    ALERT,      // ALCC_MODE 
    _4096,      // PRESCALER_M  
    false,      // SHUTDOWN
};

struct LTC2943_AlertThresholdConfig_t alert_thr = {
    0xFFFF,   // CHARGE_HIGH
    0x0,      // CHARGE_LOW
    0xFFFF,   // VOLTAGE_HIGH  
    0x0,      // VOLTAGE_LOW
    0xFFFF,   // CURR_HIGH
    0x0,      // CURR_LOW
    0xFFFF,   // TEMP_HIGH
    0x0,      // TEMP_LOW
};

struct LTC2943_Measurement_t meas = {
    0x7fff, // CHARGE
    3300,   // Power-up voltage (mV)
    0,      // CURRENT
    0,      // TEMPERATURE
};

static uint8_t read_register;

bool LTC2943_Initialise();   // Initialise the driver
bool LTC2943_Read(uint8_t address, uint8_t *dest, uint8_t dataSize); // Read data from the chip @address to dest
bool LTC2943_Write(uint8_t address, uint8_t *src, uint8_t dataSize); // Write data from src to the chip @address

#endif // LTC2943_SIM_H
