/**
 * TODO
 */
#include <string.h>
#include <stdint.h>
#include "ltc2943_sim.c"
#include "chip_control.h"


/** Check if an alert bit has been set in the status register 
 */
static bool ChipControl_CheckAlert(uint8_t reg, LTC2943_AlertStatus_t alert){
    uint8_t bit_mask = (uint8_t) alert; 
    return ((reg & bit_mask) != 0);
}

/** Read in data from the battery gauge. 
 *  The LTC2943 uses a 14-bit ADC, so the data outputs are stored in a uint16_t 
 *  variable.
 */
static bool ChipControl_ReadRegister(uint8_t reg_addr, uint8_t *read_buff, uint8_t data_size){
    bool success = false;
    if (LTC2943_Write(LTC2943_I2C_ADDR, &reg_addr, 1) == 0){
        if (LTC2943_Read(LTC2943_I2C_ADDR, read_buff, data_size) == 0){
            success = true;
        }
    }
    return success;
}


/** Write data to the battery gauge.
 */
static bool ChipControl_WriteRegister(uint8_t reg_addr, uint8_t *data_buff, uint8_t data_size){
    bool success = false;
    uint8_t buff_size = data_size + 1;
    uint8_t write_buff[buff_size]; 
    write_buff[0] = reg_addr;
    memcpy((void *)(write_buff + 1), data_buff, data_size);

    if (LTC2943_REG_ADDR_WRITABLE[reg_addr] == 1){ 
       if (LTC2943_Write(LTC2943_I2C_ADDR, write_buff, buff_size) == 0){
            success = true;
       } 
    }
    return success;
}



LTC2943_AdcMode_t ChipControl_GetAdcMode(){
    uint8_t read_buff = 0;
    bool success = ChipControl_ReadRegister(CONTROL_ADDR, &read_buff, 1); 
    if (!success){
        return -1;
    }
    return LTC2943_ReadAdcMode(read_buff);
}


bool ChipControl_SetAdcMode(LTC2943_AdcMode_t mode){
    uint8_t read_buff;
    // check current mode
    bool success = ChipControl_ReadRegister(CONTROL_ADDR, &read_buff, 1); 

    LTC2943_AdcMode_t curr_mode = LTC2943_WriteAdcMode(read_buff, mode);
    if (curr_mode == mode){
        success = true;
    }
    else {
         // set bits [7:6] to new mode 
         uint8_t write_buff = LTC2943_WriteAdcMode(read_buff, mode);
         success = ChipControl_WriteRegister(CONTROL_ADDR, &write_buff, 1);
    }
    return success;
}


LTC2943_AlccMode_t ChipControl_GetAlccMode(){
    uint8_t read_buff;
    bool success = ChipControl_ReadRegister(CONTROL_ADDR, &read_buff, 1); 
    if (!success){
        return -1;
    }
    return LTC2943_ReadAlccMode(read_buff); 
}


bool ChipControl_SetAlccMode(LTC2943_AlccMode_t mode){
    uint8_t read_buff;
    // check current mode
    bool success = ChipControl_ReadRegister(CONTROL_ADDR, &read_buff, 1); 
    LTC2943_AlccMode_t curr_mode = LTC2943_ReadAlccMode(read_buff);
    if (curr_mode == mode){
         success = true;
    }
    else {
         // set bits [5:3] to new mode 
         uint8_t write_buff = LTC2943_WriteAlccMode(read_buff, mode);
         success = ChipControl_WriteRegister(CONTROL_ADDR, &write_buff, 1);
    }
    return success;

}

LTC2943_PrescalerM_t ChipControl_GetPrescalerM(){
    uint8_t read_buff;
    bool success = ChipControl_ReadRegister(CONTROL_ADDR, &read_buff, 1); 
    if (!success){
        return -1;
    }
    return LTC2943_ReadPrescalerM(read_buff); 
}

bool ChipControl_SetPrescalerM(LTC2943_PrescalerM_t nbit){
    uint8_t read_buff;
    // check current mode
    bool success = ChipControl_ReadRegister(CONTROL_ADDR, &read_buff, 1); 
    LTC2943_AlccMode_t curr_nbit = LTC2943_ReadPrescalerM(read_buff);
    if (curr_nbit == nbit){
         success = true;
    }
    else {
         // set bits [2:1] to new mode 
         uint8_t write_buff = LTC2943_WritePrescalerM(read_buff, nbit);
         success = ChipControl_WriteRegister(CONTROL_ADDR, &write_buff, 1);
    }
    return success;

}

static float ChipControl_GetCharge(uint8_t addr){
    bool success = false;
    uint8_t read_buff[2];
    success = ChipControl_ReadRegister(addr, read_buff, 2); 
    if (!success){
        return -1;
    }
    uint32_t reg = 0;
    LTC2943_BuffToUint(&reg, read_buff, 2);
    return LTC2943_RegisterToCharge((uint16_t)reg);
}


/** Set internal charge registers
 *      addr: charge register address 
 */
static bool ChipControl_SetCharge(uint8_t addr, float value){
    bool success = false;
    uint8_t write_buff[2];
    uint32_t reg = LTC2943_ChargeToRegister(value);
    LTC2943_UintToBuff(&reg, write_buff, 2);
    success = ChipControl_ReadRegister(addr, write_buff, 2); 
    return success;
}


/** Get internal voltage registers
 *      addr: voltage register address
 */
static float ChipControl_GetVoltage(uint8_t addr){
    bool success = false;
    uint8_t read_buff[2];
    success = ChipControl_ReadRegister(addr, read_buff, 2); 
    if (!success){
        return -1;
    }
    uint32_t reg = 0;
    LTC2943_BuffToUint(&reg, read_buff, 2);
    return LTC2943_RegisterToVoltage((uint16_t)reg);
}


/** Set internal voltage registers
 */
static bool ChipControl_SetVoltage(uint8_t addr, float value){
    bool success = false;
    uint8_t write_buff[2];
    uint32_t reg = LTC2943_VoltageToRegister(value);
    LTC2943_UintToBuff(&reg, write_buff, 2);
    success = ChipControl_ReadRegister(addr, write_buff, 2); 
    return success;
}


static float ChipControl_GetCurrent(uint8_t addr){
    bool success = false;
    uint8_t read_buff[2];
    success = ChipControl_ReadRegister(addr, read_buff, 2); 
    if (!success){
        return -1;
    }
    uint32_t reg = 0;
    LTC2943_BuffToUint(&reg, read_buff, 2);
    return LTC2943_RegisterToCurrent((uint16_t)reg);
}


static bool ChipControl_SetCurrent(uint8_t addr, float value){
    bool success = false;
    uint8_t write_buff[2];
    uint32_t reg = LTC2943_CurrentToRegister(value);
    LTC2943_UintToBuff(&reg, write_buff, 2);
    success = ChipControl_ReadRegister(addr, write_buff, 2); 
    return success;
}


static float ChipControl_GetTemperature(uint8_t addr){
    bool success = false;
    uint8_t read_buff[2];
    success = ChipControl_ReadRegister(addr, read_buff, 2); 
    if (!success){
        return -1;
    }
    uint32_t reg = 0;
    LTC2943_BuffToUint(&reg, read_buff, 2);
    return LTC2943_RegisterToTemperature((uint16_t)reg);
}


static bool ChipControl_SetTemperature(uint8_t addr, float value){
    bool success = false;
    uint8_t write_buff[2];
    uint32_t reg = LTC2943_TemperatureToRegister(value);
    LTC2943_UintToBuff(&reg, write_buff, 2);
    success = ChipControl_ReadRegister(addr, write_buff, 2); 
    return success;
}


bool ChipControl_GetAlert(LTC2943_AlertStatus_t alert){
    uint8_t read_buff;
    ChipControl_ReadRegister(STATUS_ADDR, &read_buff, 1); 
    return ChipControl_CheckAlert(read_buff, alert); 
}

float ChipControl_GetChargeMeasurement(){
    return ChipControl_GetCharge(CHARGE_ADDR);
}

bool ChipControl_SetChargeMeasurement(float value){
    return ChipControl_SetCharge(CHARGE_ADDR, value);
}

float ChipControl_GetChargeThresholdLow(){
    return ChipControl_GetCharge(CHARGE_THR_LOW_ADDR);
}

bool ChipControl_SetChargeThresholdLow(float value){
    return ChipControl_SetCharge(CHARGE_THR_LOW_ADDR, value);
}

float ChipControl_GetChargeThresholdHigh(){
    return ChipControl_GetCharge(CHARGE_THR_HIGH_ADDR);
}

bool ChipControl_SetChargeThresholdHigh(float value){
    return ChipControl_SetCharge(CHARGE_THR_HIGH_ADDR, value);
}


float ChipControl_GetVoltageMeasurement(){
    return ChipControl_GetVoltage(VOLTAGE_ADDR);
}

float ChipControl_GetVoltageThresholdLow(){
    return ChipControl_GetVoltage(VOLTAGE_THR_LOW_ADDR);
}

bool ChipControl_SetVoltageThresholdLow(float value){
    return ChipControl_SetVoltage(VOLTAGE_THR_LOW_ADDR, value);
}

float ChipControl_GetVoltageThresholdHigh(){
    return ChipControl_GetVoltage(VOLTAGE_THR_HIGH_ADDR);
}

bool ChipControl_SetVoltageThresholdHigh(float value){
    return ChipControl_SetVoltage(CHARGE_THR_HIGH_ADDR, value);
}


float ChipControl_GetCurrentMeasurement(){
    return ChipControl_GetCurrent(CURR_ADDR);
}

float ChipControl_GetCurrentThresholdLow(){
    return ChipControl_GetCurrent(CURR_THR_LOW_ADDR);
}

bool ChipControl_SetCurrentThresholdLow(float value){
    return ChipControl_SetCurrent(CURR_THR_LOW_ADDR, value);
}

float ChipControl_GetCurrentThresholdHigh(){
    return ChipControl_GetCurrent(CURR_THR_HIGH_ADDR);
}

bool ChipControl_SetCurrentThresholdHigh(float value){
    return ChipControl_SetCurrent(CHARGE_THR_HIGH_ADDR, value);
}


float ChipControl_GetTemperatureMeasurement(){
    return ChipControl_GetTemperature(TEMP_ADDR);
}

float ChipControl_GetTemperatureThresholdLow(){
    return ChipControl_GetTemperature(TEMP_THR_LOW_ADDR);
}

bool ChipControl_SetTemperatureThresholdLow(float value){
    return ChipControl_SetTemperature(TEMP_THR_LOW_ADDR, value);
}

float ChipControl_GetTemperatureThresholdHigh(){
    return ChipControl_GetTemperature(TEMP_THR_HIGH_ADDR);
}

bool ChipControl_SetTemperatureThresholdHigh(float value){
    return ChipControl_SetTemperature(TEMP_THR_HIGH_ADDR, value);
}


