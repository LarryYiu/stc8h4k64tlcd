#ifndef __I2C_H__
#define __I2C_H__

#include "Config.h"
#include "STC8G_H_I2C.h"
#include "STC8G_H_NVIC.h"
#include "STC8G_H_Switch.h"

#define I2C_WriteByte(addr, dat) I2C_WriteNbyte(DEV_ADDR, addr, dat, 1)
#define I2C_ReadByte(addr, dat) I2C_ReadNbyte(DEV_ADDR, addr, dat, 1)
#define I2C_ReadBytes(addr, dat, len) I2C_ReadNbyte(DEV_ADDR, addr, dat, len)
#define I2C_WriteBytes(addr, dat, len) I2C_WriteNbyte(DEV_ADDR, addr, dat, len)

/**
 * @brief Initializing I2C function, non software simulating. This function does
 * not extend the register access.
 *
 * @param i2cPins pin pair used by I2C, can be
 * I2C_P14_P15, I2C_P24_P25, I2C_P33_P32
 * @param isMaster I2C mode, master or slave,
 * I2C_Mode_Master, I2C_Mode_Slave
 * @param isEnabled enable I2C or not, ENABLE, DISABLE
 * @param isAutoSendEnabled enable MS_WDTA, ENABLE, DISABLE
 * @param 12cSpeed speed of i2c bus Fosc/2/(Speed*2+4), 0-63
 * @param priority priority of i2c interrupt,
 * Priority_0,Priority_1,Priority_2,Priority_3
 *
 * @return bit TRUE if successful, FALSE if error occurred
 */
bit I2C_Config(u8 i2cPins, bit isMaster, bit isEnabled, bit isAutoSendEnabled,
               u8 i2cSpeed, int8 priority);

#endif  // __I2C_H__