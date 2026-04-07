#include "Key.h"

void Key_Init()
{
    GPIO_config(GPIO_P3, GPIO_Pin_2, GPIO_PullUp);
    GPIO_config(GPIO_P3, GPIO_Pin_3, GPIO_PullUp);
    GPIO_config(GPIO_P3, GPIO_Pin_4, GPIO_PullUp);
    GPIO_config(GPIO_P3, GPIO_Pin_5, GPIO_PullUp);
}

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