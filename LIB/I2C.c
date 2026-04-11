#include "I2C.h"

bit I2C_Config(u8 i2cPins, bit isMaster, bit isEnabled, bit isAutoSendEnabled,
               u8 i2cSpeed, int8 priority)
{
    bit res = FALSE;
    I2C_InitTypeDef i2c;
    bit noPrio = priority < 0;
    i2c.I2C_Mode = isMaster;
    i2c.I2C_Enable = isEnabled;
    i2c.I2C_MS_WDTA = isAutoSendEnabled;
    i2c.I2C_Speed = i2cSpeed;
    I2C_Init(&i2c);
    if (noPrio)
    {
        res = NVIC_I2C_Init(isMaster, DISABLE, Priority_0);
    }
    else
    {
        res = NVIC_I2C_Init(isMaster, ENABLE, priority > 3 ? 3 : priority);
    }

    I2C_SW(i2cPins);
    return res;
}

// void I2C_WriteByte(u8 addr, const u8* dat)
// {
//     I2C_WriteNbyte(DEV_ADDR, addr, dat, 1);
// }

// void I2C_ReadByte(u8 addr, u8* dat)
// {
//     I2C_ReadNbyte(DEV_ADDR, addr, dat, 1);
// }