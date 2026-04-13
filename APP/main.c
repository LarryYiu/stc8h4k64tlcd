#include <stc8h.h>
#include <string.h>

#include "AppFunctionSetup.h"
#include "Config.h"
#include "STC8G_H_Delay.h"

void main()
{
    u32 xdata sysT0Tick = 0;
    App_Init();
    EA = 1;

    printf("Init OK\r\n");
    while (1)
    {
        delay_ms(1);
        if (time0IntNum - sysT0Tick >= 200)
        {
            sysT0Tick = time0IntNum;

            if (KT_READ_DONE_FLAG)
            {
                KT_READ_DONE_FLAG = FALSE;
                if (TouchKey_IsAnyPressed())
                {
                    if (touchKeyStatus >> 7 & 0x0001)
                    {
                        printf("1\n");
                    }
                    else
                    {
                        printf("0\n");
                    }
                }
                else
                {
                    printf("0\n");
                }
                // printf("TK_cnt1 = %d \r\n", TK_DAT_BUFF[1]);
                // printf("TK_cnt7 = %u \r\n", TK_DAT_BUFF[7]);
                // printf("TK_cnt8 = %d \r\n", TK_DAT_BUFF[8]);
                // printf("TK_cnt9 = %d \r\n", TK_DAT_BUFF[9]);
            }
        }
    }
}