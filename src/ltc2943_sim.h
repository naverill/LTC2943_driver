#ifndef LTC2943_SIM_H
#define LTC2943_SIM_H

#include <stdint.h>
#include <stdbool.h>
#include "ltc2943_config.h"

const bool SIMULATE = false;

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

#endif // LTC2943_SIM_H
