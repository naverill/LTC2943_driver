#include <unity.h>
#include "chip_control.h"


void Test_GetAdcMode(){
    LTC2943_AdcMode_t mode = ChipControl_GetAdcMode();
    TEST_ASSERT_EQUAL_FLOAT(mode, SLEEP);
}

void Test_SetAdcMode(){
    LTC2943_AdcMode_t mode = MANUAL; 
    bool success = ChipControl_SetAdcMode(mode);
    TEST_ASSERT_TRUE(success);
    TEST_ASSERT_EQUAL_FLOAT(mode, config.ADC_MODE);
}

void Test_GetAlccMode(){
    LTC2943_AlccMode_t mode = ChipControl_GetAlccMode();
    TEST_ASSERT_EQUAL_FLOAT(mode, ALERT);
}

void Test_SetAlccMode(){
    LTC2943_AlccMode_t mode = DISABLED; 
    bool success = ChipControl_SetAdcMode(mode);
    TEST_ASSERT_EQUAL_FLOAT(mode, config.ALCC_MODE);
    TEST_ASSERT_TRUE(success);
}

void Test_GetPrescalerM(){
    LTC2943_PrescalerM_t nbit = ChipControl_GetPrescalerM();
    TEST_ASSERT_EQUAL_FLOAT(nbit, _4096);
}

void Test_SetPrescalerM(){
    LTC2943_PrescalerM_t nbit = _1; 
    bool success = ChipControl_SetPrescalerM(nbit);
    TEST_ASSERT_EQUAL_FLOAT(nbit, config.PRESCALER_M);
    TEST_ASSERT_TRUE(success);
}

void Test_GetAlerts(){
    TEST_ASSERT_EQUAL(1, ChipControl_GetAlert(UNDERVOLTAGE_LOCKOUT));
    TEST_ASSERT_EQUAL(0, ChipControl_GetAlert(VOLTAGE));
    TEST_ASSERT_EQUAL(0, ChipControl_GetAlert(CHARGE_LOW));
    TEST_ASSERT_EQUAL(0, ChipControl_GetAlert(CHARGE_HIGH));
    TEST_ASSERT_EQUAL(0, ChipControl_GetAlert(TEMP));
    TEST_ASSERT_EQUAL(0, ChipControl_GetAlert(CHARGE));
    TEST_ASSERT_EQUAL(0, ChipControl_GetAlert(CURRENT));

}

void Test_GetChargeMeas(){
    float value = ChipControl_GetChargeMeasurement();
    TEST_ASSERT_EQUAL_FLOAT(value, meas.CHARGE);
}

void Test_SetChargeMeas(){
    float charge = 99;
    bool success = ChipControl_SetChargeMeasurement(charge);
    TEST_ASSERT_TRUE(success);
    TEST_ASSERT_EQUAL_FLOAT(charge, meas.CHARGE);
}

void Test_GetChargeThrHigh(){
    float value = ChipControl_GetChargeThresholdHigh();
    TEST_ASSERT_EQUAL_FLOAT(value, alert_thr.CHARGE_HIGH);
}

void Test_SetChargeThrHigh(){
    float charge = 99;
    bool success = ChipControl_SetChargeThresholdHigh(charge);
    TEST_ASSERT_TRUE(success);
    TEST_ASSERT_EQUAL_FLOAT(charge, alert_thr.CHARGE_HIGH);
}

void Test_GetChargeThrLow(){
    float value = ChipControl_GetChargeThresholdLow();
    TEST_ASSERT_EQUAL_FLOAT(value, alert_thr.CHARGE_LOW);
}

void Test_SetChargeThrLow(){
    float charge = 99;
    bool success = ChipControl_SetChargeThresholdLow(charge);
    TEST_ASSERT_TRUE(success);
    TEST_ASSERT_EQUAL_FLOAT(charge, alert_thr.CHARGE_LOW);
}

void Test_GetVoltageMeas(){
    float value = ChipControl_GetVoltageMeasurement();
    TEST_ASSERT_EQUAL_FLOAT(value, meas.VOLTAGE);
}

void Test_GetVoltageThrHigh(){
    float value = ChipControl_GetVoltageThresholdHigh();
    TEST_ASSERT_EQUAL_FLOAT(value, alert_thr.VOLTAGE_HIGH);
}

void Test_SetVoltageThrHigh(){
    float charge = 99;
    bool success = ChipControl_SetVoltageThresholdHigh(charge);
    TEST_ASSERT_TRUE(success);
    TEST_ASSERT_EQUAL_FLOAT(charge, alert_thr.VOLTAGE_HIGH);
}

void Test_GetVoltageThrLow(){
    float value = ChipControl_GetVoltageThresholdLow();
    TEST_ASSERT_EQUAL_FLOAT(value, alert_thr.VOLTAGE_LOW);
}

void Test_SetVoltageThrLow(){
    float charge = 99;
    bool success = ChipControl_SetVoltageThresholdLow(charge);
    TEST_ASSERT_TRUE(success);
    TEST_ASSERT_EQUAL_FLOAT(charge, alert_thr.VOLTAGE_LOW);
}

void Test_GetCurrMeas(){
    float value = ChipControl_GetCurrentMeasurement();
    TEST_ASSERT_EQUAL_FLOAT(value, meas.CURRENT);
}

void Test_GetCurrThrHigh(){
    float value = ChipControl_GetCurrentThresholdHigh();
    TEST_ASSERT_EQUAL_FLOAT(value, alert_thr.CURR_HIGH);
}

void Test_SetCurrThrHigh(){
    float charge = 99;
    bool success = ChipControl_SetCurrentThresholdHigh(charge);
    TEST_ASSERT_TRUE(success);
    TEST_ASSERT_EQUAL_FLOAT(charge, alert_thr.CURR_HIGH);
}

void Test_GetCurrThrLow(){
    float value = ChipControl_GetCurrentThresholdLow();
    TEST_ASSERT_EQUAL_FLOAT(value, alert_thr.CURR_LOW);
}

void Test_SetCurrThrLow(){
    float charge = 99;
    bool success = ChipControl_SetCurrentThresholdLow(charge);
    TEST_ASSERT_TRUE(success);
    TEST_ASSERT_EQUAL_FLOAT(charge, alert_thr.CURR_LOW);
}

void Test_GetTempMeas(){
    float value = ChipControl_GetTemperatureMeasurement();
    TEST_ASSERT_EQUAL_FLOAT(value, meas.TEMP);
}

void Test_GetTempThrHigh(){
    float value = ChipControl_GetTemperatureThresholdHigh();
    TEST_ASSERT_EQUAL_FLOAT(value, alert_thr.TEMP_HIGH);
}

void Test_SetTempThrHigh(){
    float charge = 99;
    bool success = ChipControl_SetTemperatureThresholdHigh(charge);
    TEST_ASSERT_TRUE(success);
    TEST_ASSERT_EQUAL_FLOAT(charge, alert_thr.TEMP_HIGH);
}

void Test_GetTempThrLow(){
    float value = ChipControl_GetTemperatureThresholdLow();
    TEST_ASSERT_EQUAL_FLOAT(value, alert_thr.TEMP_LOW);
}

void Test_SetTempThrLow(){
    float charge = 99;
    bool success = ChipControl_SetTemperatureThresholdLow(charge);
    TEST_ASSERT_TRUE(success);
    TEST_ASSERT_EQUAL_FLOAT(charge, alert_thr.TEMP_LOW);
}
