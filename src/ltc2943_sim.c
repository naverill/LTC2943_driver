/**
 * LTC2943 simulator for testing purposes
 *
 * Control Register Format:
 * uint8[8] : [0]   - shutdown 
 *          : [1:2] - ALCC configure
 *          : [3:5] - Prescaler M
 *          : [6:7] - ADC Mode 
 *
 * Status Register Format:
 * uint8[8] : [0]   - Undervoltage Lockout
 *          : [1]   - Voltage
 *          : [2]   - Charge low
 *          : [3]   - Charge high 
 *          : [4]   - Temp 
 *          : [5]   - Accumulated Charge
 *          : [6]   - Current
 *          : [7]   - Reseved
 **/

#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include "ltc2943_sim.h"
#include "rand_gauss.h"
#include "ltc2943_config.h"

static struct LTC2943_Status_t status = {
    1,  // UNDERVOLTAGE_LOCKOUT 
    0,  // VOLTAGE  
    0,  // CHARGE_LOW 
    0,  // CHARGE_HIGH 
    0,  // TEMP 
    0,  // ACC_CHARGE 
    0   // CURRENT_ALERT 
};

static struct LTC2943_Config_t config = {
    -0.3,   // SUPPLY_VOLTAGE_MIN 
    24.,    // SUPPLY_VOLTAGE_MAX 
    -0.3,   // SCL_VOLTAGE_MIN 
    6.,     // SCL_VOLTAGE_MAX 
    0.,     // OPERATING_TEMP_RANGE_C_MIN  
    70.,    // OPERATING_TEMP_RANGE_C_MAX  
    -40.,   // OPERATING_TEMP_RANGE_I_MIN  
    85.,    // OPERATING_TEMP_RANGE_I_MAX 
    -65.,   // SURVIVAL_TEMP_RANGE_MIN 
    150.,   // SURVIVAL_TEMP_RANGE_MAX 
    900,    // SCL_CLOCK_FREQ 
    100,    // ADC_READ_WAIT 
    SLEEP,  // ADC_MODE 
    ALERT,  // ALCC_MODE 
    _4096,  // PRESCALER_M  
};

static struct LTC2943_AlertThresholdConfig_t alert_thr = {
    0xFFFF, // CHARGE_HIGH
    0x0,      // CHARGE_LOW
    0xFFFF, // VOLTAGE_HIGH  
    0x0,      // VOLTAGE_LOW
    0xFFFF,   // CURR_HIGH
    0x0,      // CURR_LOW
    0xFFFF,   // TEMP_HIGH
    0x0,      // TEMP_LOW
};


bool LTC2943_Initialise(){
    /** Simulate battery gauge:
     *      1. Powering-on reset signal
     *      2. Setting all registers to default state
     *      3. Enabling alert mode
     */
    return 0;
}

bool LTC2943_Read(uint8_t address, uint8_t *dest, uint8_t dataSize){
    /** Simulate battery gauge
     *
     */
    bool success = false;
    return success;
}

bool LTC2943_Write(uint8_t address, uint8_t *src, uint8_t dataSize){
    bool success = false;
    return success;
}


