#include <stc8h.h>
#include <string.h>

#include "AppFunctionSetup.h"
#include "Config.h"
#include "STC8G_H_Delay.h"

void onShortPress(u8 index)
{
    if (index == 0)
    {
        printf("Key1 Short Pressed, cnt: %bu\n", keys[0].pressCount);
    }
    else if (index == 1)
    {
        printf("Key2 Short Pressed, cnt: %bu\n", keys[1].pressCount);
    }
    else if (index == 2)
    {
        printf("Key3 Short Pressed, cnt: %bu\n", keys[2].pressCount);
    }
    else if (index == 3)
    {
        printf("Key4 Short Pressed, cnt: %bu\n", keys[3].pressCount);
    }
}

void onLongPress(u8 index)
{
    if (index == 0)
    {
        printf("Key1 Long Pressed, cnt: %bu\n", keys[0].pressDuration);
    }
    else if (index == 1)
    {
        printf("Key2 Long Pressed, cnt: %bu\n", keys[1].pressDuration);
    }
    else if (index == 2)
    {
        printf("Key3 Long Pressed, cnt: %bu\n", keys[2].pressDuration);
    }
    else if (index == 3)
    {
        printf("Key4 Long Pressed, cnt: %bu\n", keys[3].pressDuration);
    }
}

void main()
{
    u32 xdata sysRtcPrintf = 0;
    App_Init();
    EA = 1;
    printf("Starting Config Done!\n");

    while (1)
    {
        if (time0IntNum - sysRtcPrintf >= 100)
        {
            sysRtcPrintf = time0IntNum;
            Key_Event(0, onShortPress, onLongPress);
        }
    }
}