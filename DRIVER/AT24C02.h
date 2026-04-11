#ifndef __AT24C02_H__
#define __AT24C02_H__

#include "Config.h"
#include "I2C.h"

void AT24C02_WriteByte(u8 pageNum, u8 byteNum, const u8* dat);
void AT24C02_ReadByte(u8 pageNum, u8 byteNum, u8* dat);
void AT24C02_WriteFloat(u8 pageNum, bit offset, const float* dat);
void AT24C02_ReadFloat(u8 pageNum, bit offset, float* dat);

#endif  // __AT24C02_H__