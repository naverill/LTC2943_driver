#include "CppUTest/TestHarness.h"

extern "C"
{
  #include "chip_control.c"
  #include "ltc2943_sim.c"
  #include "ltc2943_config.h"
  #include "RuntimeErrorStub.h"
}


TEST_GROUP(LTC2943)
{
    void setup(){
        LTC2943_Initialise();
    }

    void tearDown()

};

TEST(LTC2942, GetAdcMode){
    LTC2943_AdcMode_t mode = ChipControl_GetAdcMode();
    LONGS_EQUAL(mode, SLEEP);
}

TEST(LTC2942, SetAdcMode){
    LTC2943_AdcMode_t mode = MANUAL; 
    bool success = ChipControl_SetAdcMode(mode);
    LONGS_EQUAL(success, true);
    LONGS_EQUAL(mode, config.ADC_MODE);
}

TEST(LTC2942, GetAlccMode){
    LTC2943_AlccMode_t mode = ChipControl_GetAlccMode();
    LONGS_EQUAL(mode, ALERT);
}

TEST(LTC2942, SetAlccMode){
    LTC2943_AlccMode_t mode = DISABLED; 
    bool success = ChipControl_SetAdcMode(mode);
    LONGS_EQUAL(mode, config.ALCC_MODE);
    LONGS_EQUAL(success, true);
}

TEST(LTC2942, GetPrescalerM){
    LTC2943_PrescalerM_t nbit = ChipControl_GetPrescalerM();
    LONGS_EQUAL(nbit, _4096);
}

TEST(LTC2942, SetPrescalerM){
    LTC2943_PrescalerM_t nbit = _1; 
    bool success = ChipControl_SetPrescalerM(nbit);
    LONGS_EQUAL(nbit, config.PRESCALER_M);
    LONGS_EQUAL(success, true);
}

TEST(LTC2942, GetAlerts){
    CHECK_EQUAL(1, ChipControl_GetAlert(UNDERVOLTAGE_LOCKOUT));
    CHECK_EQUAL(0, ChipControl_GetAlert(VOLTAGE));
    CHECK_EQUAL(0, ChipControl_GetAlert(CHARGE_LOW));
    CHECK_EQUAL(0, ChipControl_GetAlert(CHARGE_HIGH));
    CHECK_EQUAL(0, ChipControl_GetAlert(TEMP));
    CHECK_EQUAL(0, ChipControl_GetAlert(CHARGE));
    CHECK_EQUAL(0, ChipControl_GetAlert(CURRENT));

}

TEST(LTC2942, GetChargeMeas){
    float value = ChipControl_GetChargeMeasurement();
    LONGS_EQUAL(value, meas.CHARGE);
}

TEST(LTC2942, SetChargeMeas){
    float charge = 99;
    bool success = ChipControl_SetChargeMeasurement(charge);
    CHECK_EQUAL(success, true);
    LONGS_EQUAL(charge, meas.CHARGE)
}

TEST(LTC2942, GetChargeThrHigh){
    float value = ChipControl_GetChargeThresholdHigh();
    LONGS_EQUAL(value, alert_thr.CHARGE_HIGH);
}

TEST(LTC2942, SetChargeThrHigh){
    float charge = 99;
    bool success = ChipControl_SetChargeThresholdHigh(charge);
    CHECK_EQUAL(success, true);
    LONGS_EQUAL(charge, alert_thr.CHARGE_HIGH)
}

TEST(LTC2942, GetChargeThrLow){
    float value = ChipControl_GetChargeThresholdLow();
    LONGS_EQUAL(value, alert_thr.CHARGE_LOW);
}

TEST(LTC2942, SetChargeThrLow){
    float charge = 99;
    bool success = ChipControl_SetChargeThresholdLow(charge);
    CHECK_EQUAL(success, true);
    LONGS_EQUAL(charge, alert_thr.CHARGE_LOW)
}

TEST(LTC2942, GetVoltageMeas){
    float value = ChipControl_GetVoltageMeasurement();
    LONGS_EQUAL(value, meas.VOLTAGE);
}

TEST(LTC2942, GetVoltageThrHigh){
    float value = ChipControl_GetVoltageThresholdHigh();
    LONGS_EQUAL(value, alert_thr.VOLTAGE_HIGH);
}

TEST(LTC2942, SetVoltageThrHigh){
    float charge = 99;
    bool success = ChipControl_SetVoltageThresholdHigh(charge);
    CHECK_EQUAL(success, true);
    LONGS_EQUAL(charge, alert_thr.VOLTAGE_HIGH)
}

TEST(LTC2942, GetVoltageThrLow){
    float value = ChipControl_GetVoltageThresholdLow();
    LONGS_EQUAL(value, alert_thr.VOLTAGE_LOW);
}

TEST(LTC2942, SetVoltageThrLow){
    float charge = 99;
    bool success = ChipControl_SetVoltageThresholdLow(charge);
    CHECK_EQUAL(success, true);
    LONGS_EQUAL(charge, alert_thr.VOLTAGE_LOW)
}

TEST(LTC2942, GetCurrMeas){
    float value = ChipControl_GetCurrentMeasurement();
    LONGS_EQUAL(value, meas.CURRENT);
}

TEST(LTC2942, GetCurrThrHigh){
    float value = ChipControl_GetCurrentThresholdHigh();
    LONGS_EQUAL(value, alert_thr.CURR_HIGH);
}

TEST(LTC2942, SetCurrThrHigh){
    float charge = 99;
    bool success = ChipControl_SetCurrentThresholdHigh(charge);
    CHECK_EQUAL(success, true);
    LONGS_EQUAL(charge, alert_thr.CURRENT_HIGH)
}

TEST(LTC2942, GetCurrThrLow){
    float value = ChipControl_GetCurrentThresholdLow();
    LONGS_EQUAL(value, alert_thr.CURRENT_LOW);
}

TEST(LTC2942, SetCurrThrLow){
    float charge = 99;
    bool success = ChipControl_SetCurrentThresholdLow(charge);
    CHECK_EQUAL(success, true);
    LONGS_EQUAL(charge, alert_thr.CURRENT_LOW)
}

TEST(LTC2942, GetTempMeas){
    float value = ChipControl_GetTemperatureMeasurement();
    LONGS_EQUAL(value, meas.TEMP);
}

TEST(LTC2942, GetTempThrHigh){
    float value = ChipControl_GetTemperatureThresholdHigh();
    LONGS_EQUAL(value, alert_thr.TEMP_HIGH);
}

TEST(LTC2942, SetTempThrHigh){
    float charge = 99;
    bool success = ChipControl_SetTemperatureThresholdHigh(charge);
    CHECK_EQUAL(success, true);
    LONGS_EQUAL(charge, alert_thr.TEMP_HIGH)
}

TEST(LTC2942, GetTempThrLow){
    float value = ChipControl_GetTemperatureThresholdLow();
    LONGS_EQUAL(value, alert_thr.TEMP_LOW);
}

TEST(LTC2942, SetTempThrLow){
    float charge = 99;
    bool success = ChipControl_SetTemperatureThresholdLow(charge);
    CHECK_EQUAL(success, true);
    LONGS_EQUAL(charge, alert_thr.TEMP_LOW)
}
