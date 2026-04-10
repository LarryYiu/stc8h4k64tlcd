#ifndef __KEY_H__
#define __KEY_H__

#include <STC8H.h>

#include "Config.h"
#include "GPIO.h"
#include "STC8G_H_Delay.h"
#include "STC8G_H_GPIO.H"

#ifndef KEY_USE_BUSY_WAITING
#define KEY_USE_BUSY_WAITING TRUE
#endif  // KEY_USE_BUSY_WAITING

#ifndef KEY_NUM_KEYS
#define KEY_NUM_KEYS 4
#endif  // KEY_NUM_KEYS

#ifndef KEY_LONG_PRESS_THRESHOLD
#define KEY_LONG_PRESS_THRESHOLD 50  // 50 * 10ms = 500ms
#endif                               // KEY_LONG_PRESS_THRESHOLD

void Key_Init();
#if (KEY_USE_BUSY_WAITING)
bool Key_ScanBusy(u8* keyNum);
#else
#define KEY_NUM_BIT_PER_KEY 4
#define KEY_BITPLACE_PRESSED 3
#define KEY_BITPLACE_LONG_PRESSED 2
#define KEY_BITPLACE_PRESS_COUNT 1
#define KEY_BITPLACE_PRESSING 0
typedef struct
{
    u8 keyNum;
    u8 pressDuration;
    u8 pressCount;
    u8 lastReleaseDuration;
    u8 isPressing;
    u8 isLastPressing;
} Key_t;
u16 Key_Scan();
#endif

#endif  // __KEY_H__