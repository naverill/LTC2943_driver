/**
 * TODO
 */
#include "chip_control.h" 
#include "ltc2943_config.h"
#include "ltc2943_sim.c"


static bool ChipControl_ReadRegister(LTC2943_RegAddr_t reg_addr, uint8_t *data, uint8_t data_size){
    /** Read in data from the battery gauge. 
     *
     * The LTC2943 uses a 14-bit ADC, so the data outputs are stored in a uint16_t 
     *  variable. 
     *  
     */
    bool success = false;

    uint8_t read_buff[data_size];
    if (LTC2932_Write(LTC2942_I2C_ADDR, &((uint8_t)reg_addr), 1) == 0){
        if (LTC2932_Read(LTC2942_I2C_ADDR, &(read_buff), data_size) == 0){
            success = true;
            *data = &read_buff;
        }
    }
    return success;
}


static bool ChipControl_WriteRegister(LTC2943_RegAddr_t reg_addr, uint32_t *data, uint8_t data_size){
    bool success = false;
    uint8_t buff_size = data_size + 1;
    uint8_t write_buff[buff_size]; 
    write_buff[0] = (uint8_t)reg_addr;
    uint8_t i;
    for (i = 1; i < buff_size; i++){
        write_buff[i] = (*data >> 8 * (data_size - i));
    }

    if (LTC2932_REG_ADDR_WRITEABLE[reg_addr] == 1){ 
       if (LTC2932_Write(LTC2942_I2C_ADDR, &(write_buff), buff_size) == 0){
            success = true;
       } 
    }
    return success;
}


bool ChipControl_GetAdcMode(uint8_t *data){
    bool success = false;
    uint16_t *data;
    success = ChipControl_ReadRegister(CONTROL, data); 
    
    return success
}

bool ChipControl_SetAdcMode(LTC2943_ADCMode_t mode){

   data = (((uint16_t)(data[1] << 8) + data[2]))
}

uint8_t ChipControl_GetAlccMode(){

}

bool ChipControl_SetAlccMode(LTC2943_ALCCMode_t mode){

}

uint8_t ChipControl_GetAlert(){

}

bool ChipControl_SetThreshold(LTC2943_AlertThreshold_t threshold, float64_t value){

}

bool ChipControl_CheckThreshold(LTC2943_AlertThreshold_t threshold){

}

float64_t ChipControl_GetMeasurement(LTC2943_Measurement_t meas){

}

