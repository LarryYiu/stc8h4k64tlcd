#include "DigitalTube.h"

u8 code DT_TUBE_LOOKUP[8] = {0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf, 0xbf, 0x7f};

u8 code DT_SEG_LOOKUP[15] = {DIGIT_0,  DIGIT_1, DIGIT_2, DIGIT_3, DIGIT_4,
                             DIGIT_5,  DIGIT_6, DIGIT_7, DIGIT_8, DIGIT_9,
                             DIGIT_DP, DIGIT_r, DIGIT_E, DIGIT_o, DIGIT_MINUS};

void DT_Init()
{
    GPIO_config(GPIO_P7, GPIO_Pin_6, GPIO_PullUp);
    GPIO_config(GPIO_P7, GPIO_Pin_7, GPIO_PullUp);
    GPIO_config(GPIO_P4, GPIO_Pin_1, GPIO_PullUp);
}

void DT_DisplaySingle(u8 seg, u8 tube)
{
    HC595_SendByte(seg);
    HC595_SendByte(tube);
    HC595_Output();
}

void DT_DisplayMulti(u8* dtArr, u8 len, u8 dp, bool alignRight)
{
    u8 i = 0;
    if (dtArr[0] == DIGIT_r)
    {
        for (i = 0; i < len; i++)
        {
            DT_DisplaySingle(dtArr[i] | ((0x07 & (0x01 << i)) ? 0x80 : 0x00),
                             DT_TUBE_LOOKUP[len - i - 1]);
        }
        return;
    }
    else
    {
        if (alignRight)
        {
            for (i = 0; i < len; i++)
            {
                DT_DisplaySingle(dtArr[i] | ((dp & (0x01 << i)) ? 0x80 : 0x00),
                                 DT_TUBE_LOOKUP[DT_MAX_DIGIT - i - 1]);
            }
            return;
        }
        else
        {
            for (i = 0; i < len; i++)
            {
                DT_DisplaySingle(dtArr[i] | ((dp & (0x01 << i)) ? 0x80 : 0x00),
                                 DT_TUBE_LOOKUP[len - i - 1]);
            }
        }
    }
}

u8 DT_ProcessInt(int32 num, u8* dtArr)
{
    u8 len = 0;
    u8 i = 0;
    bool isNegative = num < 0;
    if (num == 0)
    {
        dtArr[0] = DT_SEG_LOOKUP[0];
        return 1;
    }
    if (num > 9999999 || num < -999999)
    {
        dtArr[0] = DT_SEG_LOOKUP[11];  // r
        dtArr[1] = DT_SEG_LOOKUP[11];  // r
        dtArr[2] = DT_SEG_LOOKUP[12];  // E
        return 3;
    }

    if (isNegative)
    {
        num = -num;
    }
    while (num > 0)
    {
        dtArr[len++] = DT_SEG_LOOKUP[num % 10];
        num /= 10;
    }
    if (isNegative)
    {
        dtArr[len++] = DT_SEG_LOOKUP[14];  // '-'
    }
    return len;
}

u8 DT_ProcessFloat(float num, u8* dtArr, u8* decimalPlaces)
{
    int32 xdata intNum;
    u16 multiplier = 1;
    u8 i;
    if (num == 0)
    {
        dtArr[0] = DT_SEG_LOOKUP[0];
        *decimalPlaces = 0x00;
        return 1;
    }
    if (num > 99999 || num < -9999)
    {
        dtArr[0] = DT_SEG_LOOKUP[11];  // r
        dtArr[1] = DT_SEG_LOOKUP[11];  // r
        dtArr[2] = DT_SEG_LOOKUP[12];  // E
        *decimalPlaces = 0x07;
        return 3;
    }

    if (*decimalPlaces > 3)
    {
        *decimalPlaces = 3;
    }

    for (i = 0; i < *decimalPlaces; i++)
    {
        multiplier *= 10;
    }
    intNum = (int32)(num * multiplier);
    *decimalPlaces = (0x01 << *decimalPlaces);
    return DT_ProcessInt(intNum, dtArr);
}