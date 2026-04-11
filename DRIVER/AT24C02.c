#include "AT24C02.h"

void AT24C02_WriteByte(u8 pageNum, u8 byteNum, const u8* dat)
{
    I2C_WriteByte(pageNum * 8 + byteNum, dat);
}

void AT24C02_WriteFloat(u8 pageNum, bit offset, const float* dat)
{
    u8 xdata bytes[4];

    u8* p = (u8*)dat;
    bytes[0] = p[0];
    bytes[1] = p[1];
    bytes[2] = p[2];
    bytes[3] = p[3];
    I2C_WriteBytes(pageNum * 8 + offset * 4, bytes, 4);
}

void AT24C02_ReadByte(u8 pageNum, u8 byteNum, u8* dat)
{
    I2C_ReadByte(pageNum * 8 + byteNum, dat);
}

void AT24C02_ReadFloat(u8 pageNum, bit offset, float* dat)
{
    u8 xdata bytes[4];
    I2C_ReadBytes(pageNum * 8 + offset * 4, bytes, 4);
    *dat = *(float*)bytes;
}