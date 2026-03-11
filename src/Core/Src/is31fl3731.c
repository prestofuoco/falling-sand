// is31fl3731.c

#include "is31fl3731.h"

// write
static bool IS31_WriteReg(I2C_HandleTypeDef *hi2c, uint8_t reg, uint8_t data) {
    // parameters: i2c handle, device addr, reg addr, reg addr size, data ptr, data size, timeout (ms)
    HAL_StatusTypeDef status = HAL_I2C_Mem_Write(hi2c, IS31_I2C_ADDR, reg, I2C_MEMADD_SIZE_8BIT, &data, 1, 100);
    return (status == HAL_OK);
}

// switch between banks
static bool IS31_SelectBank(I2C_HandleTypeDef *hi2c, uint8_t bank) {
    return IS31_WriteReg(hi2c, IS31_REG_COMMAND, bank);
}


/* ---- begin public ----- */

bool IS31_Init(I2C_HandleTypeDef *hi2c) {
    // pull the SDB pin high
    HAL_GPIO_WritePin(LED_SDB_GPIO_Port, LED_SDB_Pin, GPIO_PIN_SET);
    HAL_Delay(10);

    // i2c ready check
    if (HAL_I2C_IsDeviceReady(hi2c, IS31_I2C_ADDR, 3, 100) != HAL_OK) {
        return false; 
    }

    // function mode
    if (!IS31_SelectBank(hi2c, IS31_BANK_FUNCTION)) {
        return false;
    }

    // clear
    IS31_WriteReg(hi2c, IS31_REG_SHUTDOWN, 0x00);
    HAL_Delay(10);
    IS31_WriteReg(hi2c, IS31_REG_SHUTDOWN, 0x01);

    // picture mode
    IS31_WriteReg(hi2c, IS31_REG_CONFIG, 0x00);
    IS31_SelectBank(hi2c, IS31_BANK_PICTURE);

    return true;
}

bool IS31_SetFrame(I2C_HandleTypeDef *hi2c, uint8_t frame) {
    // uint8 check
    if (frame > 7) {
        return false; 
    }

    // function mode
    IS31_SelectBank(hi2c, IS31_BANK_FUNCTION);

    // write frame
    bool success = IS31_WriteReg(hi2c, IS31_REG_PICTURFRAME, frame); 

    // picture mode
    IS31_SelectBank(hi2c, IS31_BANK_PICTURE); 
    
    return success;
}