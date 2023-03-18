/**
 * LTC2943 simulator for testing purposes
 **/

#include <math.h>
#include <stdlib.h>
#include "LTC2943_sim.h"
#include "rand_gauss.h"

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


bool LTC2943_Initialise(){
  return 0;
}

bool LTC2943_Read(uint8_t address, uint8_t *dest, uint8_t dataSize){
   return 0;
}

bool LTC2973_Write(uint8_t address, uint8_t *src, uint8_t dataSize){

}


