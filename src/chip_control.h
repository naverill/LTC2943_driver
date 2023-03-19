#ifndef CHIP_CONTROL_H
#define CHIP_CONTROL_H

#include "ltc2943_sim.h"

uint8_t ChipControl_get_adc_mode();

bool ChipControl_set_adc_mode(LTC2943_ADCMode_t mode);

uint8_t ChipControl_get_alcc_mode();

bool ChipControl_set_alcc_mode(LTC2943_ALCCMode_t mode);

uint8_t ChipControl_get_alert();

bool ChipControl_set_threshold(LTC2943_AlertThreshold_t threshold, float64_t value);

bool ChipControl_check_threshold(LTC2943_AlertThreshold_t threshold);

float64_t ChipControl_get_measurement(LTC2943_Measurement_t meas);

#endif // CHIP_CONTROL_H
