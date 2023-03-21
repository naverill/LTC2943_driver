#ifndef CHIP_CONTROL_H
#define CHIP_CONTROL_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include "ltc2943_sim.h"
#include "ltc2943_config.h"

LTC2943_AdcMode_t ChipControl_GetAdcMode();
bool ChipControl_SetAdcMode(LTC2943_AdcMode_t mode);
LTC2943_AlccMode_t uint8_t ChipControl_GetAlccMode();
bool ChipControl_SetAlccMode(LTC2943_AlccMode_t mode);
LTC2943_PrescalerM_t uint8_t ChipControl_GetPrescalerM();
bool ChipControl_SetPrescalerM(LTC2943_PrescalerM_t nbit);

/**
 * Check if an alert has been flagged in the Status register
 */
bool ChipControl_GetAlert(LTC2943_AlertStatus_t alert);
float ChipControl_GetChargeMeasurement();
bool ChipControl_SetChargeMeasurement(float value);
bool ChipControl_SetChargeThresholdLow(float value);
bool ChipControl_SetChargeThresholdHigh(float value);
float ChipControl_GetVoltageMeasurement();
bool ChipControl_SetVoltageThresholdLow(float value);
bool ChipControl_SetVoltageThresholdHigh(float value);
float ChipControl_GetCurrentMeasurement();
bool ChipControl_SetCurrentThresholdLow(float value);
bool ChipControl_SetCurrentThresholdHigh(float value);
float ChipControl_GetTemperatureMeasurement();
bool ChipControl_SetTemperatureThresholdLow(float value);
bool ChipControl_SetTemperatureThresholdHigh(float value);
static float ChipControl_GetCharge(uint8_t addr);

/** Set internal charge registers
 *      addr: charge register address 
 */
static bool ChipControl_SetCharge(uint8_t addr, float value);

/** Get internal voltage registers
 *      addr: voltage register address
 */
static float ChipControl_GetVoltage(uint8_t addr);

/** Set internal voltage registers
 *  
 */
static bool ChipControl_SetVoltage(uint8_t addr, float value);
static float ChipControl_GetCurrent(uint8_t addr);
static bool ChipControl_SetCurrent(uint8_t addr, float value);
static float ChipControl_GetTemperature(uint8_t addr);
static bool ChipControl_SetTemperature(uint8_t addr, float value);

/** Read in data from the battery gauge. 
 *  The LTC2943 uses a 14-bit ADC, so the data outputs are stored in a uint16_t 
 *  variable.
 */
static bool ChipControl_ReadRegister(uint8_t reg_addr, uint8_t *read_buff, uint8_t data_size);

/** Write data to the battery gauge.
 *
 */
static bool ChipControl_WriteRegister(uint8_t reg_addr, uint8_t *data_buff, uint8_t data_size);
static bool ChipControl_SetRegister(LTC2943_ThrAddr_t threshold, uint16_t value);

/**
 *  Convert reading from registers (I, J, K, L, M) to voltage (mV), where
 *  Vsense = 23.6V * (RESULT / 65536)
 *  (sourced from datasheet)
 */
static float ChipControl_RegisterToVoltage(uint16_t reg);

/**
 *  Convert voltage (mV) to reading for registers (I, J, K, L, M), where 
 *  Vsense = (RESULT * 65536) / 23.6V
 */
static uint16_t ChipControl_VoltageToRegister(float value);

/**
 *  Convert reading from registers (O, P, Q, R, S, T) to current (mA), where
 *  RSENSE = 50mΩ
 *  
 *  I-bat = (60mV / RSENSE ) * (value - 7FFFh) / 7FFFhi (mA)
 *  (sourced from datasheet)
 */
static float ChipControl_RegisterToCurrent(uint16_t reg);


/**
 *  Convert current to register input
 */
static uint16_t ChipControl_CurrentToRegister(float value);

/**
 *  Convert reading from registers (U, V, W, X) to temperature (K), where
 *  
 *  T = 510K * (value / 0xfff) 
 *  (sourced from datasheet)
 */
static float ChipControl_RegisterToTemperature(uint16_t reg);

/**
 *  Convert temperature (K) to register input  
 *  (sourced from datasheet)
 */
static uint16_t ChipControl_TemperatureToRegister(float value);

/**
 *  Convert reading from registers (U, V, W, X) to charge (mAh), where
 *  
 *  q = 0.34 * (50 / RSENSE) * (prescalerM / 4096) 
 *  (sourced from datasheet)
 */
static float ChipControl_RegisterToCharge(uint16_t reg);

/**
 *  Convert temperature (K) to register input  
 *  (sourced from datasheet)
 */
static uint16_t ChipControl_ChargeToRegister(float value);
static uint8_t *ChipControl_UintToBuff(void *data, uint8_t *write_buff);
static void ChipControl_BuffToUint(void *data, uint8_t *read_buff);

/** Extract the current ADC mode from the control register
 *  This value is located in bits [7:6]
 */
static LTC2943_AdcMode_t ChipControl_ReadAdcMode(uint8_t reg);

/** Extract the current ALCC mode from the control register
 *  This value is located in bits [5:3]
 */
static LTC2943_AlccMode_t ChipControl_ReadAlccMode(uint8_t reg);

/** Extract the current ALCC mode from the control register
 *  This value is located in bits [2:1]
 */
static LTC2943_ADCMode_t ChipControl_ReadPrescalerM(uint8_t reg);

/** Extract the current ALCC mode from the control register
 *  This value is located in bit [0]
 */
static bool ChipControl_ReadShutdown(uint8_t reg);

/** Set the ADC mode in the control register
 *  This value is located in bits [7:6]
 */
static uint8_t ChipControl_WriteAdcMode(uint8_t reg, LTC2943_AdcMode_t mode);

/** Set the ALCC mode in the control register
 *  This value is located in bits [5:3]
 */
static LTC2943_AlccMode_t ChipControl_WriteAlccMode(uint8_t reg, LTC2943_Alcc Mode_t mode);

/** Set the ALCC mode in the control register
 *  This value is located in bits [2:1]
 */
static LTC2943_AdcMode_t ChipControl_WritePrescalerM(uint8_t reg, LTC2943_PrescalerM_t nbit);

/** Extract the current ALCC mode from the control register
 *  This value is located in bit [0]
 */
static bool ChipControl_WriteShutdown(uint8_t reg, bool shutdown);


/** Check if an alert bit has been set in the status register 
 */
static bool ChipControl_CheckAlert(uint8_t reg, LTC2943_AlertStatus_t alert);


#endif // CHIP_CONTROL_H
