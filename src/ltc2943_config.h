#ifndef LCT2943_CONFIG_H
#define LCT2943_CONFIG_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#define BIT(nr)	((uint8_t)(1) << (nr))

const uint8_t LTC2943_I2C_ADDR = BIT(6) | BIT(5) | BIT(2);
const float RSENSE = 50; // default for sense resistor (mΩ)

typedef const uint8_t LTC2943_AdcMode_t;
LTC2943_AdcMode_t AUTO    = BIT(1) | BIT(0);  // continuously performing voltage, current and 
                                                 // temperature conversions
LTC2943_AdcMode_t SCAN    = BIT(1);   // voltage, current and temperature conversion measurements 
                    // are executed every 10 seconds.
LTC2943_AdcMode_t MANUAL  = BIT(0);   // Manual Mode: performing single conversions of voltage, current and 
                    // temperature then sleep
LTC2943_AdcMode_t SLEEP   = 0;

typedef const uint8_t LTC2943_PrescalerM_t; 
LTC2943_PrescalerM_t _1      = 0;
LTC2943_PrescalerM_t _4      = BIT(0);
LTC2943_PrescalerM_t _16     = BIT(1);
LTC2943_PrescalerM_t _64     = BIT(1) | BIT(0);
LTC2943_PrescalerM_t _256    = BIT(2);
LTC2943_PrescalerM_t _1024   = BIT(2) | BIT(0);
LTC2943_PrescalerM_t _4096   = BIT(2) | BIT(1);


typedef const uint8_t LTC2943_AlccMode_t; 
LTC2943_AlccMode_t ALERT           = BIT(1);    // Alert functionality enabled. Pin becomes logic output
LTC2943_AlccMode_t CHARGE_COMPLETE = BIT(0);    // Pin becomes logic input and accepts charge complete 
                                                // inverted signal to set accumulated charge register 
                                                // (C,D) to FFFFh. 
LTC2943_AlccMode_t DISABLED        = 0;         // Pin disabled 
LTC2943_AlccMode_t NOT_ALLOWED     = BIT(1) | BIT(0);


typedef const uint8_t LTC2943_RegAddr_t; 
LTC2943_RegAddr_t STATUS_ADDR             = 0x00; // A: Status
LTC2943_RegAddr_t CONTROL_ADDR            = 0x01; // B: Control
LTC2943_RegAddr_t CHARGE_ADDR             = 0x02; // C: Accumulated Charge  (mAh)
LTC2943_RegAddr_t VOLTAGE_ADDR            = 0x08; // I: Voltage  (V)
LTC2943_RegAddr_t CURR_ADDR               = 0x0E; // O: Current  (mV)
LTC2943_RegAddr_t TEMP_ADDR               = 0x14; // U: Temperature  (K) 
LTC2943_RegAddr_t CHARGE_THR_HIGH_ADDR    = 0x04; // E: Charge Threshold High  (mAh)
LTC2943_RegAddr_t CHARGE_THR_LOW_ADDR     = 0x06; // G: Charge Threshold Low  (mAh)
LTC2943_RegAddr_t VOLTAGE_THR_HIGH_ADDR   = 0x0A; // K: Voltage Threshold High  (V)
LTC2943_RegAddr_t VOLTAGE_THR_LOW_ADDR    = 0x0C; // M: Voltage Threshold Low  (V)
LTC2943_RegAddr_t CURR_THR_HIGH_ADDR      = 0x10; // Q: Current Threshold High   (mV) 
LTC2943_RegAddr_t CURR_THR_LOW_ADDR       = 0x12; // S: Current Threshold Low  (mV) 
LTC2943_RegAddr_t TEMP_THR_HIGH_ADDR      = 0x16; // W: Temperature Threshold High (K) 
LTC2943_RegAddr_t TEMP_THR_LOW_ADDR       = 0x17; // W: Temperature Threshold Low(K) 

typedef const uint8_t LTC2943_AlertStatus_t;
LTC2943_AlertStatus_t UNDERVOLTAGE_LOCKOUT    = BIT(0); // Indicates recovery from undervoltage
LTC2943_AlertStatus_t VOLTAGE                 = BIT(1); // Indicates one of the voltage limits was exceeded
LTC2943_AlertStatus_t CHARGE_LOW              = BIT(2); // Indicates that the ACR value exceeded the charge 
                                                        // threshold low limit
LTC2943_AlertStatus_t CHARGE_HIGH             = BIT(3); // Indicates that the ACR value exceeded the charge 
                                                        // threshold high limit
LTC2943_AlertStatus_t TEMP                    = BIT(4); // Indicates one of the temperature limits 
                                                        // was exceeded 
LTC2943_AlertStatus_t ACC_CHARGE              = BIT(5); // Indicates that the value of the ACR hit either 
                                                        // top or bottom (charge overflow/underflow) 
LTC2943_AlertStatus_t CURRENT_ALERT           = BIT(6); // Indicates one of the current limits was exceeded 


const bool LTC2943_REG_ADDR_WRITABLE[18] = {
    0, //   STATUS              
    1, //   CONTROL             
    1, //   CHARGE_      
    1, //   CHARGE_THR_HIGH_ 
    1, //   CHARGE_THR_LOW_  
    0, //   VOLTAGE_         
    1, //   VOLTAGE_THR_HIGH_
    1, //   VOLTAGE_THR_LOW_ 
    0, //   CURR_            
    1, //   CURR_THR_HIGH_   
    1, //   CURR_THR_LOW_    
    0, //   TEMP_            
    1, //   TEMP_THR_HIGH       
    1, //   TEMP_THR_LOW        
};

struct LTC2943_Config_t {
    float SUPPLY_VOLTAGE_MIN;
    float SUPPLY_VOLTAGE_MAX;
    float SCL_VOLTAGE_MIN;
    float SCL_VOLTAGE_MAX;
    float OPERATING_TEMP_RANGE_C_MIN; 
    float OPERATING_TEMP_RANGE_C_MAX; 
    float OPERATING_TEMP_RANGE_I_MIN; 
    float OPERATING_TEMP_RANGE_I_MAX; 
    float SURVIVAL_TEMP_RANGE_MIN;
    float SURVIVAL_TEMP_RANGE_MAX;
    uint32_t SCL_CLOCK_FREQ;
    uint32_t ADC_READ_WAIT;
    uint8_t ADC_MODE;
    uint8_t ALCC_MODE;
    uint8_t PRESCALER_M; 
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
    bool CURRENT_ALERT;
};

#endif // LCT2943_CONFIG_H
