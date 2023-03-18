#ifndef LTC2943_SIM_H
#define LTC2943_SIM_H

bool LTC2943_Initialise();   // Initialise the driver
bool LTC2943_Read(uint8_t address, uint8_t *dest, uint8_t dataSize); // Read data from the chip @address to dest
bool LTC2973_Write(uint8_t address, uint8_t *src, uint8_t dataSize); // Write data from src to the chip @address

static void LTC2943_Reset();

#endif // LTC2943_SIM_H
