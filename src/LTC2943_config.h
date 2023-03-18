#include <stdio.h>
#include <linux/bitops.h>


const uint_8 LTC2942_I2C_ADDR = BIT(6) | BIT(5) | BIT(2);

enum LTC2943_Pins{
    SENSEP  = 0x01, // Sense+ Positive current Sense Input
    GND1    = 0x02, // Device Ground 1
    GND     = 0x03, // Device Ground 2
    SCL     = 0x04, // Serial Bus Clock Input
    SDA     = 0x05, // Serial Bus Data Input and Output
    ALCC    = 0x06, // Alert Output or Change Complete Input 
    GND3    = 0x07, // Device Ground 3
    SENSEN  = 0x08, // Negative Current Sense Input
    EPAD    = 0x09  // Exposed Pad
}

enum LTC2943_ADCMode {
    AUTO    = BIT(1) || BIT(0),  // continuously performing voltage, current and 
                                 // temperature conversions
    SCAN    = BIT(1),   // voltage, current and temperature conversion measurements 
                        // are executed every 10 seconds.
    MANUAL  = BIT(0),   // Manual Mode: performing single conversions of voltage, current and 
                        // temperature then sleep
    SLEEP   = 0
}

enum LTC2943_PrescalerM {
    _1      = 0,
    _4      = BIT(0),
    _16     = BIT(1),
    _64     = BIT(1) | BIT(0),
    _256    = BIT(2),
    _1024   = BIT(2) | BIT(0),
    _4096   = BIT(2) | BIT(1),
    _4096_   = BIT(3) | BIT(2) | BIT(1),
}

enum LTC2943_ALCCMode {
    ALERT           = BIT(1), // Alert functionality enabled. Pin becomes logic output
    CHARGE_COMPLETE = BIT(0), // Pin becomes logic input and accepts charge complete 
                              // inverted signal to set accumulated charge register 
                              // (C,D) to FFFFh. 
    DISABLED        = 0,      // Pin disabled 
    NOT_ALLOWED     = BIT(1) | BIT(0),
}

enum LTC2943_RegAddr {
    STATUS                  = 0x00, // Status (R)
    CONTROL                 = 0x01, // Control (R/W)
    ACC_CHARGE_MSB          = 0x02, // Accumulated Charge MSB (R/W)
    ACC_CHARGE_LSB          = 0x03, // Accumulated Charge LSB (R/W)
    CHARGE_THR_HIGH_LSB     = 0x04, // Charge Threshold High MSB (R/W)
    CHARGE_THR_HIGH_MSB     = 0x05, // Charge Threshold High LSB (R/W)
    CHARGE_THR_LOW_LSB      = 0x06, // Charge Threshold Low MSB (R/W)
    CHARGE_THR_LOW_MSB      = 0x07, // Charge Threshold Low LSB (R/W)
    VOLTAGE_MSB             = 0x08, // Voltage MSB (R)
    VOLTAGE_LSB             = 0x09, // Voltage LSB (R)
    VOLTAGE_THR_HIGH_LSB    = 0x0A, // Voltage Threshold High MSB (R/W)
    VOLTAGE_THR_HIGH_MSB    = 0x0B, // Voltage Threshold High LSB (R/W)
    VOLTAGE_THR_LOW_LSB     = 0x0C, // Voltage Threshold Low MSB (R/W)
    VOLTAGE_THR_LOW_MSB     = 0x0D, // Voltage Threshold Low LSB (R/W)
    CURR_MSB                = 0x0E, // Current MSB (R)
    CURR_LSB                = 0x0F, // Current LSB (R)
    CURR_THR_HIGH_MSB       = 0x10, // Current Threshold High MSB (R/W) 
    CURR_THR_HIGH_LSB       = 0x11, // Current Threshold High LSB  (R/)
    CURR_THR_LOW_MSB        = 0x12, // Current Threshold Low MSB (R/W) 
    CURR_THR_LOW_LSB        = 0x13, // Current Threshold Low LSB (R/W) 
    TEMP_MSB                = 0x14, // Temperature MSB (R) 
    TEMP_LSB                = 0x15, // Temperature MSB (R)
    TEMP_THR_HIGH           = 0x16, // Temperature Threshold High  (R/W) 
    TEMP_THR_LOW            = 0x16, // Temperature Threshold Low (R/W) 
}

enum LTC2943_StatusReg {
    UNDERVOLTAGE_LOCKOUT    = 0x00, // Indicates recovery from undervoltage
    VOLTAGE                 = 0x01, // Indicates one of the voltage limits was exceeded
    CHARGE_LOW              = 0x02, // Indicates that the ACR value exceeded the charge 
                                    // threshold low limit
    CHARGE_HIGH             = 0x03, // Indicates that the ACR value exceeded the charge 
                                    // threshold high limit
    TEMP                    = 0x04, // Indicates one of the temperature limits was exceeded 
    ACC_CHARGE              = 0x05, // Indicates that the value of the ACR hit either 
                                    // top or bottom (charge overflow/underflow) 
    CURRENT_ALERT           = 0x06, // Indicates one of the current limits was exceeded 
}

struct LTC2943_Config {
    const float SUPPLY_VOLTAGE_MIN = -0.3;
    const float SUPPLY_VOLTAGE_MAX = 24.;
    const float SCL_VOLTAGE_MIN = -0.3;
    const float SCL_VOLTAGE_MAX = 6.;
    const float OPERATING_TEMP_RANGE_C_MIN = 0.; 
    const float OPERATING_TEMP_RANGE_C_MAX = 70.; 
    const float OPERATING_TEMP_RANGE_I_MIN = -40.; 
    const float OPERATING_TEMP_RANGE_I_MAX = 85.; 
    const float SURVIVAL_TEMP_RANGE_MIN = -65.;
    const float SURVIVAL_TEMP_RANGE_MAX = 150.;
    const float SCL_CLOCK_FREQ = 900;
    const float ADC_READ_WAIT = 100;
    uint8_t ADC_MODE = LTC2943_ADCMode.SLEEP;
    uint8_t ALCC_MODE = LTC2943_ALCCMode.ALERT;
    uint8_t PRESCALER_M = LTC2943_PrescalerM._4096; 
}

struct LTC2943_AlertThreshold {
    float CHARGE_HIGH   = 0xFFFF;
    float CHARGE_LOW    = 0x0; 
    float VOLTAGE_HIGH  = 0xFFFF;
    float VOLTAGE_LOW   = 0x0; 
    float CURR_HIGH     = 0xFFFF;
    float CURR_LOW      = 0x0; 
    float TEMP_HIGH     = 0xFFFF;
    float TEMP_LOW      = 0x0; 
}

struct LTC2943_Status {
    bool UNDERVOLTAGE_LOCKOUT    = 1,
    bool VOLTAGE                 = 0,
    bool CHARGE_LOW              = 0,
    bool CHARGE_HIGH             = 0,
    bool TEMP                    = 0,
    bool ACC_CHARGE              = 0,
    bool CURRENT_ALERT           = 0,
}

