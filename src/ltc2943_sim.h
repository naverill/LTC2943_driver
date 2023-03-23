#ifndef LTC2943_SIM_H
#define LTC2943_SIM_H

#include <stdint.h>
#include <stdbool.h>
#include "ltc2943_config.h"

const bool SIMULATE = false;
const uint64_t THR_MAX = 0xFFFF;
const uint64_t THR_MIN = 0x0;
const uint64_t THR_MID = THR_MIN + (THR_MAX - THR_MIN) / 2; 

struct LTC2943_Config_t {
    uint8_t ADC_MODE;
    uint8_t ALCC_MODE;
    uint8_t PRESCALER_M; 
    bool SHUTDOWN;
};

struct LTC2943_AlertThresholdConfig_t {
    float CHARGE_HIGH;
    float CHARGE_LOW; 
    float VOLTAGE_HIGH;
    float VOLTAGE_LOW; 
    float CURR_HIGH;
    float CURR_LOW; 
    float TEMP_HIGH;
    float TEMP_LOW; 
};

struct LTC2943_Status_t {
    bool UNDERVOLTAGE_LOCKOUT;
    bool VOLTAGE;
    bool CHARGE_LOW;
    bool CHARGE_HIGH;
    bool TEMP;
    bool ACC_CHARGE;
    bool CURRENT;
};

struct LTC2943_Measurement_t {
    float CHARGE;
    float VOLTAGE;
    float CURRENT;
    float TEMP;
};

bool LTC2943_Initialise();   // Initialise the driver
bool LTC2943_Read(uint8_t address, uint8_t *dest, uint8_t dataSize); // Read data from the chip @address to dest
bool LTC2943_Write(uint8_t address, uint8_t *src, uint8_t dataSize); // Write data from src to the chip @address

void LTC2943_UintToBuff(uint32_t *data, uint8_t *write_buff, uint8_t size);

void LTC2943_BuffToUint(uint32_t *data, uint8_t *read_buff, uint8_t size);
float LTC2943_RegisterToCharge(uint16_t reg);
uint16_t LTC2943_ChargeToRegister(float value);
float LTC2943_RegisterToVoltage(uint16_t reg);
uint16_t LTC2943_VoltageToRegister(float value);
float LTC2943_RegisterToCurrent(uint16_t reg);
uint16_t LTC2943_CurrentToRegister(float value);
float LTC2943_RegisterToTemperature(uint16_t reg);
uint16_t LTC2943_TemperatureToRegister(float value);
LTC2943_AdcMode_t LTC2943_ReadAdcMode(uint8_t reg);
uint8_t LTC2943_WriteAdcMode(uint8_t reg, LTC2943_AdcMode_t mode);
LTC2943_AlccMode_t LTC2943_ReadAlccMode(uint8_t reg);
uint8_t LTC2943_WriteAlccMode(uint8_t reg, LTC2943_AlccMode_t mode);
LTC2943_PrescalerM_t LTC2943_ReadPrescalerM(uint8_t reg);
LTC2943_AdcMode_t LTC2943_WritePrescalerM(uint8_t reg, LTC2943_PrescalerM_t nbit);
bool LTC2943_ReadShutdown(uint8_t reg);
bool LTC2943_WriteShutdown(uint8_t reg, bool shutdown);
void LTC2943_Reset();

#endif // LTC2943_SIM_H
