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


struct LTC2943_Status_t status = {
    1,  // UNDERVOLTAGE_LOCKOUT 
    0,  // VOLTAGE  
    0,  // CHARGE_LOW 
    0,  // CHARGE_HIGH 
    0,  // TEMP 
    0,  // CHARGE 
    0   // CURRENT
};

struct LTC2943_Config_t config;
static uint8_t read_register;
struct LTC2943_AlertThresholdConfig_t alert_thr;
struct LTC2943_Measurement_t meas;

void LTC2943_Reset(){
    config.ADC_MODE     = SLEEP;
    config.ALCC_MODE    = ALERT;
    config.PRESCALER_M  = _4096;
    config.SHUTDOWN     = false;

    alert_thr.CHARGE_HIGH   = THR_MAX;
    alert_thr.CHARGE_LOW    = THR_MIN;   
    alert_thr.VOLTAGE_HIGH  = THR_MAX;
    alert_thr.VOLTAGE_LOW   = THR_MIN;  
    alert_thr.CURR_HIGH     = THR_MAX;
    alert_thr.CURR_LOW      = THR_MIN;   
    alert_thr.TEMP_HIGH     = THR_MAX;
    alert_thr.TEMP_LOW      = THR_MIN;   
                                      
    meas.CHARGE     = THR_MID;
    meas.VOLTAGE    = 3300;   // Power-up voltage (mV)
    meas.CURRENT    = 0;
    meas.TEMP       = 0;
}

void LTC2943_UintToBuff(uint32_t *data, uint8_t *write_buff, uint8_t size){
    uint8_t i;
    for (i = 0; i < size; i++){
        write_buff[i] = *data >> (8 * (size - i - 1));
    }
}

void LTC2943_BuffToUint(uint32_t *data, uint8_t *read_buff, uint8_t size){
    uint8_t i;
    for (i = 0; i < size; i++){
        *data |= read_buff[i]  << (8 * (size - i - 1));
    }
}

/**
 *  Convert reading from registers (U, V, W, X) to charge (mAh), where
 *  
 *  q = 0.34 * (50 / RSENSE) * (prescalerM / 4096) 
 *  (sourced from datasheet)
 */
float LTC2943_RegisterToCharge(uint16_t reg){
    return (float) reg/ (0.34 * 50 / RSENSE) * (config.PRESCALER_M / 4096);
}


/**
 *  Convert temperature (K) to register input  
 *  (sourced from datasheet)
 */
uint16_t LTC2943_ChargeToRegister(float value){
     uint32_t reg = value * (0.34 * 50 / RSENSE) * (config.PRESCALER_M / 4096); 
     if (reg > THR_MAX){
         reg = THR_MAX;
     } else if (reg < THR_MIN){
        reg = THR_MIN;
     }
     return  (uint16_t) reg;
}


/**
 *  Convert reading from registers (I, J, K, L, M) to voltage (mV), where
 *  Vsense = 23.6V * (RESULT / 65536)
 *  (sourced from datasheet)
 */
float LTC2943_RegisterToVoltage(uint16_t reg){
    return 23600 * ((float) reg / THR_MAX);
}


/**
 *  Convert voltage (mV) to reading for registers (I, J, K, L, M), where 
 *  Vsense = (RESULT * 65536) / 23.6V
 */
uint16_t LTC2943_VoltageToRegister(float value){
     uint32_t reg = (value * THR_MAX) / 23600;
     if (reg > THR_MAX){
        reg = THR_MAX;
     } else if (reg < THR_MIN){
        reg = THR_MIN;
     }
     return  (uint16_t) reg;
}


/**
 *  Convert reading from registers (O, P, Q, R, S, T) to current (mA), where
 *  RSENSE = 50mΩ
 *  
 *  I-bat = (60mV / RSENSE ) * (value - 7FFFh) / 7FFFhi (mA)
 *  (sourced from datasheet)
 */
float LTC2943_RegisterToCurrent(uint16_t reg){
    return (float) (60000 / RSENSE) * ((reg - THR_MID) / THR_MID);
}


/**
 *  Convert current to register input
 */
uint16_t LTC2943_CurrentToRegister(float value){
     uint32_t reg = (value * RSENSE * THR_MID / 60000) + THR_MID; 
     if (reg > THR_MAX){
        reg = THR_MAX;
     } else if (reg < THR_MIN){
        reg = THR_MIN;
     }
     return (uint16_t) reg;
}


/**
 *  Convert reading from registers (U, V, W, X) to temperature (K), where
 *  
 *  T = 510K * (value / 0xfff) 
 *  (sourced from datasheet)
 */
float LTC2943_RegisterToTemperature(uint16_t reg){
    return (float) (reg / THR_MAX) * 510;
}


/**
 *  Convert temperature (K) to register input  
 *  (sourced from datasheet)
 */
uint16_t LTC2943_TemperatureToRegister(float value){
     uint32_t reg = (value * THR_MAX) / 510; 
     if (reg > THR_MAX){
         reg = THR_MAX;
     } else if (reg < THR_MIN){
        reg = THR_MIN;
     }
     return  (uint16_t) reg;
}


/** Extract the current ADC mode from the control register
 *  This value is located in bits [7:6]
 */
LTC2943_AdcMode_t LTC2943_ReadAdcMode(uint8_t reg){
    return (LTC2943_AdcMode_t)(reg >> 6);
}

/** Set the ADC mode in the control register
 *  This value is located in bits [7:6]
 */
uint8_t LTC2943_WriteAdcMode(uint8_t reg, LTC2943_AdcMode_t mode){
    uint8_t bit_mask = ~(BIT(7) || BIT(6));
    return (reg & bit_mask) | ((uint8_t)mode << 6);
}

/** Extract the current ALCC mode from the control register
 *  This value is located in bits [5:3]
 */
LTC2943_AlccMode_t LTC2943_ReadAlccMode(uint8_t reg){
    uint8_t bit_mask = (BIT(5) | BIT(4) | BIT(3)); 
    uint8_t mode = (reg & bit_mask) >> 3;
    return (LTC2943_AlccMode_t) mode; 
}

/** Set the ALCC mode in the control register
 *  This value is located in bits [5:3]
 */
uint8_t LTC2943_WriteAlccMode(uint8_t reg, LTC2943_AlccMode_t mode){
    uint8_t bit_mask = ~(BIT(5) || BIT(4) || BIT(3)); 
    return (reg & bit_mask) | (((uint8_t)mode << 3));
}

/** Extract the current PrescalerM from the control register
 *  This value is located in bits [2:1]
 */
LTC2943_PrescalerM_t LTC2943_ReadPrescalerM(uint8_t reg){
    uint8_t bit_mask = (BIT(2) | BIT(1)); 
    uint8_t nbit = (reg & bit_mask) >> 1;
    return (LTC2943_PrescalerM_t) nbit; 
}

/** Set the PrescalerM in the control register
 *  This value is located in bits [2:1]
 */
LTC2943_AdcMode_t LTC2943_WritePrescalerM(uint8_t reg, LTC2943_PrescalerM_t nbit){
    uint8_t bit_mask = ~(BIT(2) || BIT(1)); 
    return (reg & bit_mask) | (((uint8_t)nbit << 1));
}

/** Set the Shutdown status from the control register
 *  This value is located in bit [0]
 */
bool LTC2943_ReadShutdown(uint8_t reg){
    uint8_t bit_mask = BIT(0); 
    return (bool)(reg & bit_mask);
}

/** Set the current shutdown status from the control register
 *  This value is located in bit [0]
 */
bool LTC2943_WriteShutdown(uint8_t reg, bool shutdown){
    uint8_t bit_mask = ~BIT(0); 
    return (reg & bit_mask) | ((uint8_t) shutdown);
}

static uint8_t LTC2943_WriteAlerts(){
    uint8_t reg = 0 | (
        status.CURRENT << 6
    ) | (
        status.ACC_CHARGE << 5
    ) | (
        status.TEMP << 4
    ) | (
        status.CHARGE_HIGH << 3
    ) | (
        status.CHARGE_LOW << 2
    ) | (
        status.VOLTAGE << 1
    ) | (
        status.UNDERVOLTAGE_LOCKOUT
    );
    return reg;
}

static bool LTC2943_ReadRegister(uint8_t addr, uint8_t *dest, uint8_t size){
    uint32_t reg;
    bool success = false;
    if (addr == CONTROL_ADDR){
        reg = 0;
        reg = (uint32_t)LTC2943_WriteAdcMode(reg, config.ADC_MODE);
        reg = (uint32_t)LTC2943_WriteAlccMode(reg, config.ALCC_MODE);
        reg = (uint32_t)LTC2943_WritePrescalerM(reg, config.PRESCALER_M);
        reg = (uint32_t)LTC2943_WriteShutdown(reg, config.SHUTDOWN);
    }
    else if (addr == STATUS_ADDR){
        reg = (uint32_t)LTC2943_WriteAlerts();
    }
    else if (addr == CHARGE_ADDR){
        reg = (uint32_t)LTC2943_ChargeToRegister(meas.CHARGE);
    }
    else if (addr == VOLTAGE_ADDR){
        reg = (uint32_t)LTC2943_VoltageToRegister(meas.VOLTAGE);
    }
    else if (addr == CURR_ADDR){
        reg = (uint32_t)LTC2943_CurrentToRegister(meas.CURRENT);
    }
    else if (addr == TEMP_ADDR){
        reg = (uint32_t)LTC2943_TemperatureToRegister(meas.TEMP);
    }
    else if (addr == CHARGE_THR_HIGH_ADDR){
        reg = (uint32_t)LTC2943_ChargeToRegister(alert_thr.CHARGE_HIGH);
    }
    else if (addr == CHARGE_THR_LOW_ADDR){
        reg = (uint32_t)LTC2943_ChargeToRegister(alert_thr.CHARGE_LOW);
    }
    else if (addr == VOLTAGE_THR_HIGH_ADDR){
        reg = (uint32_t)LTC2943_VoltageToRegister(alert_thr.VOLTAGE_HIGH);
    }
    else if (addr == VOLTAGE_THR_LOW_ADDR){
        reg = (uint32_t)LTC2943_VoltageToRegister(alert_thr.VOLTAGE_LOW);
    }
    else if (addr == CURR_THR_HIGH_ADDR){
        reg = (uint32_t)LTC2943_CurrentToRegister(alert_thr.CURR_HIGH);
    }
    else if (addr == CURR_THR_LOW_ADDR){
        reg = (uint32_t)LTC2943_CurrentToRegister(alert_thr.CURR_LOW);
    }
    else if (addr == TEMP_THR_HIGH_ADDR){
        reg = (uint32_t)LTC2943_TemperatureToRegister(alert_thr.TEMP_HIGH);
    }
    else if (addr == CURR_THR_LOW_ADDR){
        reg = (uint32_t)LTC2943_TemperatureToRegister(alert_thr.TEMP_LOW);
    }
    else {
        success = false;
    }
    LTC2943_UintToBuff(&reg, dest, size);
    success = true;
    return success;
}


static bool LTC2943_WriteRegister(uint8_t addr, uint32_t data){
    bool success = false;
    if (addr == CONTROL_ADDR){
        uint8_t reg = (uint8_t)data;
        config.ADC_MODE = LTC2943_ReadAdcMode(reg);
        config.ALCC_MODE = LTC2943_ReadAlccMode(reg);
        config.PRESCALER_M = LTC2943_ReadPrescalerM(reg);
        config.SHUTDOWN = LTC2943_ReadShutdown(reg);
        success = true; 
        
    }
    else if (addr == CHARGE_ADDR){
        uint16_t reg = (uint16_t)data;
        meas.CHARGE = LTC2943_RegisterToCharge(reg);
        success = true; 
         
    }
    else if (addr == CHARGE_THR_HIGH_ADDR){
        uint16_t reg = (uint16_t)data;
        alert_thr.CHARGE_HIGH = LTC2943_RegisterToCharge(reg);
        success = true; 
    
    }
    else if (addr == CHARGE_THR_LOW_ADDR){
        uint16_t reg = (uint16_t)data;
        alert_thr.CHARGE_LOW = LTC2943_RegisterToCharge(reg);
        success = true; 
        
    }
    else if (addr == VOLTAGE_THR_HIGH_ADDR){
        uint16_t reg = (uint16_t)data;
        alert_thr.VOLTAGE_HIGH = LTC2943_RegisterToVoltage(reg);
        success = true; 
        
    }
    else if (addr == VOLTAGE_THR_LOW_ADDR){
        uint16_t reg = (uint16_t)data;
        alert_thr.VOLTAGE_LOW = LTC2943_RegisterToVoltage(reg);
        success = true; 
        
    }
    else if (addr == CURR_THR_HIGH_ADDR){
        uint16_t reg = (uint16_t)data;
        alert_thr.CURR_HIGH = LTC2943_RegisterToCurrent(reg);
        success = true; 
        
    }
    else if (addr == CURR_THR_LOW_ADDR){
        uint16_t reg = (uint16_t)data;
        alert_thr.CURR_LOW = LTC2943_RegisterToCurrent(reg);
        success = true; 
        
    }
    else if (addr == TEMP_THR_HIGH_ADDR){
        uint16_t reg = (uint16_t)data;
        alert_thr.TEMP_HIGH = LTC2943_RegisterToTemperature(reg);
        success = true; 
        
    }
    else if (addr == CURR_THR_LOW_ADDR){
        uint16_t reg = (uint16_t)data;
        alert_thr.TEMP_LOW = LTC2943_RegisterToTemperature(reg);
        success = true; 
        
    }
    return success;
}

bool LTC2943_Initialise(){
    /** Simulate battery gauge:
     *      1. Powering-on reset signal
     *      2. Setting all registers to default state
     *      3. Enabling alert mode
     */
    LTC2943_Reset();
    return 0;
}

static void LTC2943_Simulate(){
    /** Simulate operation of the battery gauge by generating random
     * measurements for temperature, current, and voltage
     */
    meas.CHARGE = rand_gauss_range(CHARGE_MIN, CHARGE_MAX, CHARGE_ERR);
    meas.VOLTAGE = rand_gauss_range(VOLTAGE_MIN, VOLTAGE_MAX, VOLTAGE_ERR);
    meas.CURRENT = rand_gauss_range(CURR_MIN, CURR_MAX, CURR_ERR);
    meas.TEMP = rand_gauss_range(TEMP_MIN, TEMP_MAX, TEMP_ERR);

    status.UNDERVOLTAGE_LOCKOUT = meas.VOLTAGE < UNDERVOLTAGE_LOCKOUT_MIN; 
    status.CHARGE_LOW = meas.CHARGE < alert_thr.CHARGE_LOW;
    status.CHARGE_HIGH = meas.CHARGE > alert_thr.CHARGE_HIGH;
    status.VOLTAGE = (meas.VOLTAGE < alert_thr.VOLTAGE_LOW) |  (meas.VOLTAGE > alert_thr.VOLTAGE_HIGH);
    status.CURRENT = (meas.CURRENT < alert_thr.CURR_LOW) |  (meas.CURRENT > alert_thr.CURR_HIGH);
    status.TEMP = (meas.TEMP < alert_thr.TEMP_LOW) |  (meas.TEMP > alert_thr.TEMP_HIGH);
}

bool LTC2943_Read(uint8_t address, uint8_t *dest, uint8_t dataSize){
    /** Simulate battery gauge
     *
     */
    bool success = false;
    success = LTC2943_ReadRegister(read_register, dest, dataSize);

    if (SIMULATE){
        LTC2943_Simulate();
    }
    return success;
}

bool LTC2943_Write(uint8_t address, uint8_t *src, uint8_t dataSize){
    bool success = false;
    uint8_t reg_addr;
    // Hacky way of determining whether the buffer contains data or a register addr
    if (dataSize == 1){
        read_register = *src;        
        success = true;
    } else { 
        reg_addr = src[0]; 
        uint8_t size = dataSize - 1;
        uint32_t data;
        uint8_t data_buff[size];
        memcpy((void *)(src + 1), data_buff, size);
        LTC2943_BuffToUint(&data, data_buff, size);
        success = LTC2943_WriteRegister(reg_addr, data);
    }
    return success;
}
