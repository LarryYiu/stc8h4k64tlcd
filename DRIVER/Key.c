#include "Key.h"

#if (!KEY_USE_BUSY_WAITING)
Key_t xdata keys[4];
#endif  // KEY_USE_BUSY_WAITING

void Key_Init()
{
    GPIO_Config(GPIO_P3, GPIO_Pin_2, GPIO_PullUp);
    GPIO_Config(GPIO_P3, GPIO_Pin_3, GPIO_PullUp);
    GPIO_Config(GPIO_P3, GPIO_Pin_4, GPIO_PullUp);
    GPIO_Config(GPIO_P3, GPIO_Pin_5, GPIO_PullUp);
#if (!KEY_USE_BUSY_WAITING)
    keys[1] = (Key_t){
        .keyNum = 1,
        .pressDuration = 0,
        .pressCount = 0,
        .lastReleaseDuration = 0,
        .isPressing = FALSE,
        .isLastPressing = FALSE,
    };
    keys[2] = (Key_t){
        .keyNum = 2,
        .pressDuration = 0,
        .pressCount = 0,
        .lastReleaseDuration = 0,
        .isPressing = FALSE,
        .isLastPressing = FALSE,
    };
    keys[3] = (Key_t){
        .keyNum = 3,
        .pressDuration = 0,
        .pressCount = 0,
        .lastReleaseDuration = 0,
        .isPressing = FALSE,
        .isLastPressing = FALSE,
    };
    keys[4] = (Key_t){
        .keyNum = 4,
        .pressDuration = 0,
        .pressCount = 0,
        .lastReleaseDuration = 0,
        .isPressing = FALSE,
        .isLastPressing = FALSE,
    };
#endif  // !KEY_USE_BUSY_WAITING
}

#if (KEY_USE_BUSY_WAITING)
bool Key_ScanBusy(u8* keyNum)
{
    if (!P32)
    {
        delay_ms(10);
        while (!P32);
        *keyNum = 1;
        return TRUE;
    }
    else if (!P33)
    {
        delay_ms(10);
        while (!P33);
        *keyNum = 2;
        return TRUE;
    }
    else if (!P34)
    {
        delay_ms(10);
        while (!P34);
        *keyNum = 3;
        return TRUE;
    }
    else if (!P35)
    {
        delay_ms(10);
        while (!P35);
        *keyNum = 4;
        return TRUE;
    }

    return FALSE;
}
#else
// key4 0000 key3 0000 key2 0000 key1 0000
//[dataReady][longPressed][pressCount][isPressing]
void __Key_Reset(u8 index)
{
    keys[index].pressDuration = 0;
    keys[index].pressCount = 0;
    keys[index].lastReleaseDuration = 0;
    keys[index].isPressing = FALSE;
    keys[index].isLastPressing = FALSE;
}
u16 Key_Scan()
{
    u16 result = 0x00;
    u16 mask = 0x0001;
    u8 i;
    for (i = 0; i < KEY_NUM_KEYS; i++)
    {
        // if (keys[i].isPressing)
        // {
        //     result |= (mask << (KEY_NUM_KEYS * 4 + i + 1));
        // }
        bit dataReady = FALSE;
        if (keys[i].pressDuration >= KEY_LONG_PRESS_THRESHOLD)
        {
            mask = 0x0001 << KEY_BITPLACE_LONG_PRESSED
                          << i * KEY_NUM_BIT_PER_KEY;
            result |= mask;
        }
        if (keys[i].isLastPressing && !keys[i].isPressing)
        {
            mask = 0x0001 << KEY_BITPLACE_PRESS_COUNT
                          << i * KEY_NUM_BIT_PER_KEY;
            result |= mask;
        }

        if (dataReady)
        {
            mask = 0x0001 << KEY_BITPLACE_PRESSED << i * KEY_NUM_BIT_PER_KEY;
            result |= mask;
        }
    }
    return result;
}
#endif  // KEY_USE_BUSY_WAITING