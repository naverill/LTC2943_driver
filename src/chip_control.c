/**
 * TODO
 */
#include "chip_control.h" 
#include "ltc2943_config.h"
#include "ltc2943_sim.c"


static bool ChipControl_ReadRegister(LTC2943_RegAddr_t reg_addr, uint8_t *read_buff, uint8_t data_size){
    /** Read in data from the battery gauge. 
     *
     * The LTC2943 uses a 14-bit ADC, so the data outputs are stored in a uint16_t 
     *  variable. 
     *  
     */
    bool success = false;
    if (LTC2932_Write(LTC2942_I2C_ADDR, &((uint8_t)reg_addr), 1) == 0){
        if (LTC2932_Read(LTC2942_I2C_ADDR, read_buff, data_size) == 0){
            success = true;
        }
    }
    return success;
}

static bool ChipControl_WriteRegister(LTC2943_RegAddr_t reg_addr, uint8_t *data_buff, uint8_t data_size){
    /** Write data to the battery gauge. 
     *
     */
    uint8_t buff_size = data_size + 1;
    uint8_t write_buff[buff_size]; 
    write_buff[0] = (uint8_t)reg_addr;
    memcpy(*write_buff + 1, data_buff, data_size)

    bool success = false;
    if (LTC2932_REG_ADDR_WRITEABLE[reg_addr] == 1){ 
       if (LTC2932_Write(LTC2942_I2C_ADDR, write_buff, buff_size) == 0){
            success = true;
       } 
    }
    return success;
}

LTC2943_AdcMode_t ChipControl_GetAdcMode(){
    /**
     *
     */
    uint8_t *read_buff;
    bool success = ChipControl_ReadRegister(CONTROL, read_buff, 1); 
    if (!success || !(*read_buff)){
        return NULL;
    }
    return ChipControl_CtrlRegToAdcMode(*read_buff) 
}

bool ChipControl_SetAdcMode(LTC2943_ADCMode_t mode){
    /**
     *
     */
    uint8_t *read_buff;
    // check current mode
    bool success = ChipControl_ReadRegister(CONTROL, read_buff, 1); 

    uint8_t reg = *read_buff;
    LTC2943_AdcMode_t curr_mode = ChipControl_WriteAdcMode(reg);
    if (curr_mode == mode){
        success = true;
    }
    else {
         // set bits [7:6] to new mode 
         uint8_t write_buff = ChipControl_WriteAdcMode(reg, mode);
         success = ChipControl_WriteRegister(CONTROL, &write_buff, 1);
    }
    return success;
}

LTC2943_AlccMode_t uint8_t ChipControl_GetAlccMode(){
    /**
     *
     */
    uint8_t *read_buff;
    bool success = ChipControl_ReadRegister(CONTROL, read_buff, 1); 
    if (!success || !(*read_buff)){
        return NULL;
    }
    return ChipControl_ReadAlccMode(*read_buff) 
}

bool ChipControl_SetAlccMode(LTC2943_ALCCMode_t mode){
    /**
     *
     */
    uint8_t *read_buff;
    // check current mode
    bool success = ChipControl_ReadRegister(CONTROL, read_buff, 1); 
    uint8_t reg = *read_buff;
    LTC2943_AlccMode_t curr_mode = ChipControl_ReadAlccMode(reg);
    if (curr_mode == mode){
         success = true;
    }
    else {
         // set bits [5:3] to new mode 
         uint8_t write_buff = ChipControl_WriteAlccMode(reg, mode);
         success = ChipControl_WriteRegister(CONTROL, write_buff, 1);
    }
    return success;

}

LTC2943_PrescalerM_t uint8_t ChipControl_GetPrescalerM(){
    /**
     *
     */
    uint8_t *read_buff;
    bool success = ChipControl_ReadRegister(CONTROL, read_buff, 1); 
    if (!success || !(*read_buff)){
        return NULL;
    }
    return ChipControl_ReadPrescalerM(*read_buff) 
}

bool ChipControl_SetPrescalerM(LTC2943_PrescalerM_t nbit){
    /**
     *
     */
    uint8_t *read_buff;
    // check current mode
    bool success = ChipControl_ReadRegister(CONTROL, read_buff, 1); 
    uint8_t reg = *read_buff;
    LTC2943_AlccMode_t curr_mode = ChipControl_ReadPrescalerM(reg);
    if (curr_mode == mode){
         success = true;
    }
    else {
         // set bits [2:1] to new mode 
         uint8_t write_buff = ChipControl_WriteAlccMode(reg, nbit);
         success = ChipControl_WriteRegister(CONTROL, write_buff, 1);
    }
    return success;

}

bool ChipControl_GetAlert(LTC2943_AlertStatus_t alert){
    /** Check if an alert has been flagged in the Status register
     *
     */
    uint8_t *read_buff;
    bool success = ChipControl_ReadRegister(STATUS, read_buff, 1); 
    if (!success || !(*read_buff)){
        return NULL;
    }
    return ChipControl_CheckAlert(*read_buff, alert) 
}

bool ChipControl_GetThreshold(LTC2943_AlertThreshold_t threshold){
    /**
     *
     */
    uint8_t *read_buff;
    bool success = ChipControl_ReadRegister(STATUS, read_buff, 1); 
    if (!success || !(*read_buff)){
        return NULL;
    }

}

bool ChipControl_SetThreshold(LTC2943_AlertThreshold_t threshold, float64_t value){
    /**
     *
     */

}

float64_t ChipControl_GetMeasurement(LTC2943_Measurement_t meas){
    /**
     *
     */

}

static void ChipControl_UintToBuff(void *data, uint8_t *write_buff){
    uint8_t i;
    uint8_t size = sizeof(data)
    for (i = 0; i < size; i++){
        write_buff[i] = (*data >> 8 * (size - i + 1);
    }
}

static LTC2943_AdcMode_t ChipControl_ReadAdcMode(uint8_t reg){
    /** Extract the current ADC mode from the control register
     *  This value is located in bits [7:6]
     */
    return (LTC2943_ADCMode_t)(reg >> 6);
}

static LTC2943_AlccMode_t ChipControl_ReadAlccMode(uint8_t reg){
    /** Extract the current ALCC mode from the control register
     *  This value is located in bits [5:3]
     */
    uint8_t bit_mask = ((BIT(2) BIT(1) || BIT(0)) << 3); 
    uint8_t mode = (reg & bit_mask) >> 3;
    return (LTC2943_AlccMode_t) mode; 
}

static LTC2943_ADCMode_t ChipControl_ReadPrescalerM(uint8_t reg){
    /** Extract the current ALCC mode from the control register
     *  This value is located in bits [2:1]
     */
    uint8_t bit_mask = ((BIT(1) || BIT(0)) << 1); 
    uint8_t nbit = (reg & bit_mask) >> 1;
    return (LTC2943_PrescalerM_t) nbit; 
}

static bool ChipControl_ReadShutdown(uint8_t reg){
    /** Extract the current ALCC mode from the control register
     *  This value is located in bit [0]
     */
    uint8_t bit_mask = BIT(0); 
    return (bool)(reg & bit_mask);
}


static uint8_t ChipControl_WriteAdcMode(uint8_t reg, LTC2943_AdcMode_t mode){
    /** Set the ADC mode in the control register
     *  This value is located in bits [7:6]
     */
    uint8_t bit_mask = ~((BIT(1) || BIT(0)) << 6)
    return (reg & bit_mask) | ((uint8_t)mode << 6);
}

static LTC2943_AlccMode_t ChipControl_WriteAlccMode(uint8_t reg, LTC2943_Alcc Mode_t mode){
    /** Set the ALCC mode in the control register
     *  This value is located in bits [5:3]
     */
    uint8_t bit_mask = ~((BIT(2) || BIT(1) || BIT(0)) << 3); 
    return (reg & bit_mask) | (((uint8_t)mode << 3));
}

static LTC2943_ADCMode_t ChipControl_WritePrescalerM(uint8_t reg, LTC2943_PrescalerM_t nbit){
    /** Set the ALCC mode in the control register
     *  This value is located in bits [2:1]
     */
    uint8_t bit_mask = ~((BIT(1) || BIT(0)) << 1); 
    return (reg & bit_mask) | (((uint8_t)nbit << 1));
}

static bool ChipControl_WriteShutdown(uint8_t reg, bool shutdown){
    /** Extract the current ALCC mode from the control register
     *  This value is located in bit [0]
     */
    uint8_t bit_mask = ~BIT(0); 
    return (reg & bit_mask) | ((uint8_t) shutdown);
}

static bool ChipControl_CheckAlert(uint8_t reg, LTC2943_AlertStatus_t alert){
    /** Check if an alert bit has been set in the status register 
     */
    uint8_t bit_mask = (uint8_t) alert; 
    return ((reg & bit_mask) != 0);
}
