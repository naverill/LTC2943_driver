/**
 * LTC2943 simulator for testing purposes
 *
 * Control Register Format:
 * uint8[8] : [0]   - shutdown 
 *          : [1:2] - ALCC configure
 *          : [3:5] - Prescaler M
 *          : [6:7] - ADC Mode 
 *
 * Status Register Format:
 * uint8[8] : [0]   - Undervoltage Lockout
 *          : [1]   - Voltage
 *          : [2]   - Charge low
 *          : [3]   - Charge high 
 *          : [4]   - Temp 
 *          : [5]   - Accumulated Charge
 *          : [6]   - Current
 *          : [7]   - Reseved
 **/

#include <math.h>
#include <stdlib.h>
#include "LTC2943_sim.h"
#include "rand_gauss.h"
#include "LTC2943_config.h"

static LTC2943_Status status();
static LTC2943_Config config();
static LTC2943_AlertThreshold alert_thr();


/**
 * Reset battery gauge to default configuration
 */
static void LTC2943_Reset() {
    status = {1, 0, 0, 0, 0, 0};
    config.ADC_MODE = LTC2943_ADCMode.SLEEP;
    config.ALCC_MODE = LTC2943_ALCCMode.ALERT;
    config.PRESCALER_M = LTC2943_PrescalerM._4096; 
    alert_thr = {0xFFFF, 0x0, 0xFFFF, 0x0, 0xFFFF, 0x0, 0xFFFF, 0x0}
}


bool LTC2943_Initialise(){
  LTC2943_Reset();
  // Power-on reset signal
  // all registers to default state
  // alert mode enabled
  return 0;
}

bool LTC2943_Read(uint8_t address, uint8_t *dest, uint8_t dataSize){
   return 0;
}

bool LTC2973_Write(uint8_t address, uint8_t *src, uint8_t dataSize){

}


