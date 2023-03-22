#ifndef CHIP_CONTROL_H
#define CHIP_CONTROL_H

#include <stdbool.h>
#include <stdint.h>
#include "ltc2943_config.h"

/**
 * 
 */
LTC2943_AdcMode_t ChipControl_GetAdcMode();

/**
 * 
 */
bool ChipControl_SetAdcMode(LTC2943_AdcMode_t mode);

/**
 * 
 */
LTC2943_AlccMode_t ChipControl_GetAlccMode();

/**
 * 
 */
bool ChipControl_SetAlccMode(LTC2943_AlccMode_t mode);

/**
 * 
 */
LTC2943_PrescalerM_t ChipControl_GetPrescalerM();

/**
 * 
 */
bool ChipControl_SetPrescalerM(LTC2943_PrescalerM_t nbit);

/**
 * Check if an alert has been flagged in the Status register
 */
bool ChipControl_GetAlert(LTC2943_AlertStatus_t alert);

/**
 * 
 */
float ChipControl_GetChargeMeasurement();

/**
 * 
 */
bool ChipControl_SetChargeMeasurement(float value);

/**
 * 
 */
bool ChipControl_SetChargeThresholdLow(float value);

/**
 * 
 */
bool ChipControl_SetChargeThresholdHigh(float value);

/**
 * 
 */
float ChipControl_GetVoltageMeasurement();

/**
 * 
 */
bool ChipControl_SetVoltageThresholdLow(float value);

/**
 * 
 */
bool ChipControl_SetVoltageThresholdHigh(float value);

/**
 * 
 */
float ChipControl_GetCurrentMeasurement();

/**
 * 
 */
bool ChipControl_SetCurrentThresholdLow(float value);

/**
 * 
 */
bool ChipControl_SetCurrentThresholdHigh(float value);

/**
 * 
 */
float ChipControl_GetTemperatureMeasurement();

/**
 * 
 */
bool ChipControl_SetTemperatureThresholdLow(float value);

/**
 * 
 */
bool ChipControl_SetTemperatureThresholdHigh(float value);

#endif // CHIP_CONTROL_H
