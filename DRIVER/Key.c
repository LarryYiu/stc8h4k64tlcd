#include "Key.h"

#if (!KEY_USE_BUSY_WAITING)
Key_t xdata keys[KEY_NUM_KEYS];
u8 code KEY_PINS[KEY_NUM_KEYS] = {GPIO_Pin_2, GPIO_Pin_3, GPIO_Pin_4,
                                  GPIO_Pin_5};
#endif  // KEY_USE_BUSY_WAITING

void Key_Config()
{
    u8 i;
    // Modify this
    GPIO_Config(GPIO_P3, GPIO_Pin_2, GPIO_PullUp);
    GPIO_Config(GPIO_P3, GPIO_Pin_3, GPIO_PullUp);
    GPIO_Config(GPIO_P3, GPIO_Pin_4, GPIO_PullUp);
    GPIO_Config(GPIO_P3, GPIO_Pin_5, GPIO_PullUp);
#if (!KEY_USE_BUSY_WAITING)
    for (i = 0; i < KEY_NUM_KEYS; i++)
    {
        keys[i].keyBit = KEY_PINS[i];
        keys[i].pressDuration = 0;
        keys[i].pressCount = 0;
        keys[i].lastReleaseDuration = 0;
        keys[i].isPressing = FALSE;
    }
#endif  // !KEY_USE_BUSY_WAITING
}

#if (KEY_USE_BUSY_WAITING)
bool Key_Scan(u8* keyNum)
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
void Key_Scan()
{
    u8 i;
    for (i = 0; i < KEY_NUM_KEYS; i++)
    {
        if (!(KEY_PORT & keys[i].keyBit))
        {
            if (keys[i].isPressing)  // was pressing, still pressing
            {
                keys[i].pressDuration++;
            }
            else  // was not pressing, now pressing
            {
                if (keys[i].lastReleaseDuration <
                    KEY_CONTINUOUS_PRESS_THRESHOLD)
                {
                    keys[i].pressCount++;
                }
                else
                {
                    keys[i].pressCount =
                        1;  // reset press count if last release was long enough
                }
            }
            keys[i].isPressing = TRUE;
            keys[i].lastReleaseDuration = 0;
        }
        else
        {
            if (keys[i].lastReleaseDuration >= KEY_CONTINUOUS_PRESS_THRESHOLD)
            {
                keys[i].pressCount = 0;
            }

            keys[i].pressDuration = 0;
            keys[i].lastReleaseDuration++;
            keys[i].isPressing = FALSE;
        }
    }
}

void Key_Event(u8 keyIndex, void (*onShortPress)(u8 pressCount),
               void (*onLongPress)(u8 pressCount))
{
    if (keys[keyIndex].isPressing)
    {
        if (keys[keyIndex].pressDuration >= KEY_LONG_PRESS_THRESHOLD)
        {
            if (onLongPress)
            {
                onLongPress(keyIndex);
            }
        }
        else
        {
            if (onShortPress)
            {
                onShortPress(keyIndex);
            }
        }
        // add continuous press event if needed
    }
    else
    {
        return;
    }
}
#endif  // KEY_USE_BUSY_WAITING