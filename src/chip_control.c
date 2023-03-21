/**
 * TODO
 */
#include <string.h>
#include <stdint.h>
#include "ltc2943_sim.c"
#include "chip_control.h"


LTC2943_AdcMode_t ChipControl_GetAdcMode(){
    uint8_t read_buff = 0;
    bool success = ChipControl_ReadRegister(CONTROL_ADDR, &read_buff, 1); 
    if (!success || !read_buff){
        return -1;
    }
    return ChipControl_ReadAdcMode(read_buff);
}


bool ChipControl_SetAdcMode(LTC2943_AdcMode_t mode){
    uint8_t read_buff;
    // check current mode
    bool success = ChipControl_ReadRegister(CONTROL_ADDR, &read_buff, 1); 

    LTC2943_AdcMode_t curr_mode = ChipControl_WriteAdcMode(read_buff, mode);
    if (curr_mode == mode){
        success = true;
    }
    else {
         // set bits [7:6] to new mode 
         uint8_t write_buff = ChipControl_WriteAdcMode(read_buff, mode);
         success = ChipControl_WriteRegister(CONTROL_ADDR, &write_buff, 1);
    }
    return success;
}


LTC2943_AlccMode_t ChipControl_GetAlccMode(){
    uint8_t read_buff;
    bool success = ChipControl_ReadRegister(CONTROL_ADDR, &read_buff, 1); 
    if (!success || !read_buff){
        return -1;
    }
    return ChipControl_ReadAlccMode(read_buff); 
}


bool ChipControl_SetAlccMode(LTC2943_AlccMode_t mode){
    uint8_t read_buff;
    // check current mode
    bool success = ChipControl_ReadRegister(CONTROL_ADDR, &read_buff, 1); 
    LTC2943_AlccMode_t curr_mode = ChipControl_ReadAlccMode(read_buff);
    if (curr_mode == mode){
         success = true;
    }
    else {
         // set bits [5:3] to new mode 
         uint8_t write_buff = ChipControl_WriteAlccMode(read_buff, mode);
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
    return ChipControl_ReadPrescalerM(read_buff); 
}

bool ChipControl_SetPrescalerM(LTC2943_PrescalerM_t nbit){
    uint8_t read_buff;
    // check current mode
    bool success = ChipControl_ReadRegister(CONTROL_ADDR, &read_buff, 1); 
    LTC2943_AlccMode_t curr_nbit = ChipControl_ReadPrescalerM(read_buff);
    if (curr_nbit == nbit){
         success = true;
    }
    else {
         // set bits [2:1] to new mode 
         uint8_t write_buff = ChipControl_WriteAlccMode(read_buff, nbit);
         success = ChipControl_WriteRegister(CONTROL_ADDR, &write_buff, 1);
    }
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


bool ChipControl_SetChargeThresholdLow(float value){
    return ChipControl_SetCharge(CHARGE_THR_LOW_ADDR, value);
}


bool ChipControl_SetChargeThresholdHigh(float value){
    return ChipControl_SetCharge(CHARGE_THR_HIGH_ADDR, value);
}


float ChipControl_GetVoltageMeasurement(){
    return ChipControl_GetVoltage(VOLTAGE_ADDR);
}

bool ChipControl_SetVoltageThresholdLow(float value){
    return ChipControl_SetVoltage(VOLTAGE_THR_LOW_ADDR, value);
}

bool ChipControl_SetVoltageThresholdHigh(float value){
    return ChipControl_SetVoltage(CHARGE_THR_HIGH_ADDR, value);
}


float ChipControl_GetCurrentMeasurement(){
    return ChipControl_GetCurrent(CURR_ADDR);
}

bool ChipControl_SetCurrentThresholdLow(float value){
    return ChipControl_SetCurrent(CURR_THR_LOW_ADDR, value);
}


bool ChipControl_SetCurrentThresholdHigh(float value){
    return ChipControl_SetCurrent(CHARGE_THR_HIGH_ADDR, value);
}


float ChipControl_GetTemperatureMeasurement(){
    return ChipControl_GetTemperature(TEMP_ADDR);
}

bool ChipControl_SetTemperatureThresholdLow(float value){
    return ChipControl_SetTemperature(TEMP_THR_LOW_ADDR, value);
}


bool ChipControl_SetTemperatureThresholdHigh(float value){
    return ChipControl_SetTemperature(TEMP_THR_HIGH_ADDR, value);
}


static float ChipControl_GetCharge(uint8_t addr){
    bool success = false;
    uint8_t read_buff[2];
    success = ChipControl_ReadRegister(addr, read_buff, 2); 
    if (!success){
        return -1;
    }
    uint64_t reg = 0;
    ChipControl_BuffToUint(&reg, read_buff, 2);
    return ChipControl_RegisterToCharge((uint16_t)reg);
}


static bool ChipControl_SetCharge(uint8_t addr, float value){
    bool success = false;
    uint8_t write_buff[2];
    uint64_t reg = ChipControl_ChargeToRegister(value);
    ChipControl_UintToBuff(&reg, write_buff, 2);
    success = ChipControl_ReadRegister(addr, write_buff, 2); 
    return success;
}


static float ChipControl_GetVoltage(uint8_t addr){
    bool success = false;
    uint8_t read_buff[2];
    success = ChipControl_ReadRegister(addr, read_buff, 2); 
    if (!success){
        return -1;
    }
    uint64_t reg = 0;
    ChipControl_BuffToUint(&reg, read_buff, 2);
    return ChipControl_RegisterToVoltage((uint16_t)reg);
}


static bool ChipControl_SetVoltage(uint8_t addr, float value){
    bool success = false;
    uint8_t write_buff[2];
    uint64_t reg = ChipControl_VoltageToRegister(value);
    ChipControl_UintToBuff(&reg, write_buff, 2);
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
    uint64_t reg = 0;
    ChipControl_BuffToUint(&reg, read_buff, 2);
    return ChipControl_RegisterToCurrent((uint16_t)reg);
}


static bool ChipControl_SetCurrent(uint8_t addr, float value){
    bool success = false;
    uint8_t write_buff[2];
    uint64_t reg = ChipControl_CurrentToRegister(value);
    ChipControl_UintToBuff(&reg, write_buff, 2);
    success = ChipControl_ReadRegister(addr, write_buff, 2); 
    if (!success){
        return NULL;
    }
    return success;
}


static float ChipControl_GetTemperature(uint8_t addr){
    bool success = false;
    uint8_t read_buff[2];
    success = ChipControl_ReadRegister(addr, read_buff, 2); 
    if (!success){
        return -1;
    }
    uint64_t reg = 0;
    ChipControl_BuffToUint(&reg, read_buff, 2);
    return ChipControl_RegisterToTemperature((uint16_t)reg);
}


static bool ChipControl_SetTemperature(uint8_t addr, float value){
    bool success = false;
    uint8_t write_buff[2];
    uint64_t reg = ChipControl_TemperatureToRegister(value);
    ChipControl_UintToBuff(&reg, write_buff, 2);
    success = ChipControl_ReadRegister(addr, write_buff, 2); 
    return success;
}


static bool ChipControl_ReadRegister(uint8_t reg_addr, uint8_t *read_buff, uint8_t data_size){
    bool success = false;
    if (LTC2943_Write(LTC2943_I2C_ADDR, &reg_addr, 1) == 0){
        if (LTC2943_Read(LTC2943_I2C_ADDR, read_buff, data_size) == 0){
            success = true;
        }
    }
    return success;
}


static bool ChipControl_WriteRegister(uint8_t reg_addr, uint8_t *data_buff, uint8_t data_size){
    bool success = false;
    uint8_t buff_size = data_size + 1;
    uint8_t write_buff[buff_size]; 
    write_buff[0] = reg_addr;
    memcpy((uint8_t *)(write_buff + 1), data_buff, data_size);

    if (LTC2943_REG_ADDR_WRITABLE[reg_addr] == 1){ 
       if (LTC2943_Write(LTC2943_I2C_ADDR, write_buff, buff_size) == 0){
            success = true;
       } 
    }
    return success;
}


static float ChipControl_RegisterToVoltage(uint16_t reg){
    return 23600 * ((float) reg / 0xfff);
}


static uint16_t ChipControl_VoltageToRegister(float value){
     uint32_t reg = (value * 0xfff) / 23600;
     if (reg > 0xfff){
        reg = 0xfff;
     } else if (reg < 0){
        reg = 0;
     }
     return  (uint16_t) reg;
}


static float ChipControl_RegisterToCurrent(uint16_t reg){
    return (float) (60000 / RSENSE) * ((reg - 0x7fff) / 0x7fff);
}


static uint16_t ChipControl_CurrentToRegister(float value){
     uint32_t reg = (value * RSENSE * 0x7fff / 60000) + 0x7fff; 
     if (reg > 0xffff){
        reg = 0xffff;
     } else if (reg < 0){
        reg = 0;
     }
     return (uint16_t) reg;
}


static float ChipControl_RegisterToTemperature(uint16_t reg){
    return (float) (reg / 0xffff) * 510;
}


static uint16_t ChipControl_TemperatureToRegister(float value){
     uint32_t reg = (value * 0xffff) / 510; 
     if (reg > 0xffff){
         reg = 0xffff;
     } else if (reg < 0){
        reg = 0;
     }
     return  (uint16_t) reg;
}


static float ChipControl_RegisterToCharge(uint16_t reg){
    return (float) reg/ (0.34 * 50 / RSENSE) * (config.PRESCALER_M / 4096);
}


static uint16_t ChipControl_ChargeToRegister(float value){
     uint32_t reg = value * (0.34 * 50 / RSENSE) * (config.PRESCALER_M / 4096); 
     if (reg > 0xffff){
         reg = 0xffff;
     } else if (reg < 0){
        reg = 0;
     }
     return  (uint16_t) reg;
}


static void ChipControl_UintToBuff(uint64_t *data, uint8_t *write_buff, uint8_t size){
    uint8_t i;
    for (i = 0; i < size; i++){
        write_buff[i] = *data >> (8 * (size - i - 1));
    }
}

static void ChipControl_BuffToUint(uint64_t *data, uint8_t *read_buff, uint8_t size){
    uint8_t i;
    for (i = 0; i < size; i++){
        *data |= read_buff[i]  << (8 * (size - i - 1));
    }
}

static LTC2943_AdcMode_t ChipControl_ReadAdcMode(uint8_t reg){
    return (LTC2943_AdcMode_t)(reg >> 6);
}

static LTC2943_AlccMode_t ChipControl_ReadAlccMode(uint8_t reg){
    uint8_t bit_mask = (BIT(5) | BIT(4) | BIT(3)); 
    uint8_t mode = (reg & bit_mask) >> 3;
    return (LTC2943_AlccMode_t) mode; 
}

static LTC2943_PrescalerM_t ChipControl_ReadPrescalerM(uint8_t reg){
    uint8_t bit_mask = (BIT(2) | BIT(1)); 
    uint8_t nbit = (reg & bit_mask) >> 1;
    return (LTC2943_PrescalerM_t) nbit; 
}

static bool ChipControl_ReadShutdown(uint8_t reg){
    uint8_t bit_mask = BIT(0); 
    return (bool)(reg & bit_mask);
}


static uint8_t ChipControl_WriteAdcMode(uint8_t reg, LTC2943_AdcMode_t mode){
    uint8_t bit_mask = ~(BIT(7) || BIT(6));
    return (reg & bit_mask) | ((uint8_t)mode << 6);
}

static uint8_t ChipControl_WriteAlccMode(uint8_t reg, LTC2943_AlccMode_t mode){
    uint8_t bit_mask = ~(BIT(5) || BIT(4) || BIT(3)); 
    return (reg & bit_mask) | (((uint8_t)mode << 3));
}

static LTC2943_AdcMode_t ChipControl_WritePrescalerM(uint8_t reg, LTC2943_PrescalerM_t nbit){
    uint8_t bit_mask = ~(BIT(2) || BIT(1)); 
    return (reg & bit_mask) | (((uint8_t)nbit << 1));
}

static bool ChipControl_WriteShutdown(uint8_t reg, bool shutdown){
    uint8_t bit_mask = ~BIT(0); 
    return (reg & bit_mask) | ((uint8_t) shutdown);
}

static bool ChipControl_CheckAlert(uint8_t reg, LTC2943_AlertStatus_t alert){
    uint8_t bit_mask = (uint8_t) alert; 
    return ((reg & bit_mask) != 0);
}
