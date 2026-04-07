/**
 * @file DigitalTube.h
 * @brief Digital Tube driven by 74HC595. 8 numbers and 8 segments are
 * supported, driven by two 74HC595s serially connected. Pushing the segment
 * data to the first 74HC595 and the number data to the second 74HC595, then
 * outputting them together.
 */
#ifndef __DIGITALTUBE_H__
#define __DIGITALTUBE_H__

#include <STC8H.h>

#include "74hc595.h"
#include "Config.h"
#include "GPIO.h"

#define DT_MAX_DIGIT 8

#ifndef DT_ACTIVE_LOW
#define DT_ACTIVE_LOW FALSE
#endif

#if (DT_ACTIVE_LOW)
#define DIGIT_0 ~0x3f      // 0b11000000
#define DIGIT_1 ~0x06      // 0b11111001
#define DIGIT_2 ~0x5b      // 0b10100100
#define DIGIT_3 ~0x4f      // 0b10110000
#define DIGIT_4 ~0x66      // 0b10011001
#define DIGIT_5 ~0x6d      // 0b10010010
#define DIGIT_6 ~0x7d      // 0b10000010
#define DIGIT_7 ~0x07      // 0b11111000
#define DIGIT_8 ~0x7f      // 0b10000000
#define DIGIT_9 ~0x6f      // 0b10010000
#define DIGIT_DP ~0x80     // 0b01111111
#define DIGIT_r ~0x50      // 0b10101111
#define DIGIT_E ~0x79      // 0b10000110
#define DIGIT_o ~0x5c      // 0b10100011
#define DIGIT_MINUS ~0x40  // 0b10111111
#else
#define DIGIT_0 0x3f      // 0b00111111
#define DIGIT_1 0x06      // 0b00000110
#define DIGIT_2 0x5b      // 0b01011011
#define DIGIT_3 0x4f      // 0b01001111
#define DIGIT_4 0x66      // 0b01100110
#define DIGIT_5 0x6d      // 0b01101101
#define DIGIT_6 0x7d      // 0b01111101
#define DIGIT_7 0x07      // 0b00000111
#define DIGIT_8 0x7f      // 0b01111111
#define DIGIT_9 0x6f      // 0b01101111
#define DIGIT_DP 0x80     // 0b10000000
#define DIGIT_r 0x50      // 0b01010000
#define DIGIT_E 0x79      // 0b01111001
#define DIGIT_o 0x5c      // 0b01011100
#define DIGIT_MINUS 0x40  // 0b01000000
#endif                    // DT_ACTIVE_LOW

extern u8 code DT_TUBE_LOOKUP[8];
extern u8 code DT_SEG_LOOKUP[15];

void DT_Init();

void DT_DisplaySingle(u8 seg, u8 tube);

void DT_DisplayMulti(u8* dtArr, u8 len, u8 dp, bool alignRight);

u8 DT_ProcessInt(int32 num, u8* dtArr);

u8 DT_ProcessFloat(float num, u8* dtArr, u8* decimalPlaces);

#endif  // __DIGITALTUBE_H__