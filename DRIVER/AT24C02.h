#ifndef __AT24C02_H__
#define __AT24C02_H__

#include "Config.h"
#include "I2C.h"

/**
 * @brief Writes a byte to the AT24C02 EEPROM at the specified page and byte
 * number.
 * @param pageNum The page number (0-3) to write to.
 * @param byteNum The byte number (0-7) within the page to write to.
 * @param dat A pointer to the byte data to be written.
 */
void AT24C02_WriteByte(u8 pageNum, u8 byteNum, const u8* dat);

/**
 * @brief Reads a byte from the AT24C02 EEPROM at the specified page and byte
 * number.
 * @param pageNum The page number (0-3) to read from.
 * @param byteNum The byte number (0-7) within the page to read from.
 * @param dat A pointer to the byte buffer to store the data read.
 */
void AT24C02_ReadByte(u8 pageNum, u8 byteNum, u8* dat);

/**
 * @brief Writes a float to the AT24C02 EEPROM at the specified page and bit
 * offset. One page can store two floats (8 bytes), so the offset determines
 * which float is written.
 * @param pageNum The page number (0-3) to write to.
 * @param offset The bit offset (0/1) within the page to write to.
 * @param dat A pointer to the float data to be written.
 */
void AT24C02_WriteFloat(u8 pageNum, bit offset, const float* dat);

/**
 * @brief Reads a float from the AT24C02 EEPROM at the specified page and bit
 * offset. One page can store two floats (8 bytes), so the offset determines
 * which float is read.
 * @param pageNum The page number (0-3) to read from.
 * @param offset The bit offset (0/1) within the page to read from.
 * @param dat A pointer to the float buffer to store the data read.
 */
void AT24C02_ReadFloat(u8 pageNum, bit offset, float* dat);

#endif  // __AT24C02_H__