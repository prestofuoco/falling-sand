// is31fl3731.h

#ifndef IS31FL3731_H
#define IS31FL3731_H

#include "main.h"
#include <stdbool.h>

// STM32 HAL requires the address to be shifted left by 1 bit for the read/write bit
#define IS31_I2C_ADDR (0x74 << 1) 

// banked memory
#define IS31_REG_COMMAND      0xFD 
#define IS31_BANK_PICTURE     0x00 // pwm values
#define IS31_BANK_FUNCTION    0x0B // configuration settings

// function bank registers (bank set to 0x0B)
#define IS31_REG_CONFIG       0x00
#define IS31_REG_PICTURFRAME  0x01
#define IS31_REG_SHUTDOWN     0x0A
#define IS31_REG_AUDIOSYNC    0x06



/* ---- begin public ----- */

// initialize, boot, and mem clear
bool IS31_Init(I2C_HandleTypeDef *hi2c);

// selects which of the 8 picture frames to display
bool IS31_SetFrame(I2C_HandleTypeDef *hi2c, uint8_t frame);

#endif