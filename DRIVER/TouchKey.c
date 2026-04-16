#include "TouchKey.h"

/**
 * @brief __TK_DAT_BUFF is an array that stores the raw data read from each
 * touch key channel during scanning. The index corresponds to the touch key
 * channel number (0-15). This data can be used for debugging, calibration, or
 * implementing advanced features like auto-calibration. The values are updated
 * in the interrupt handler when a scan is completed for each channel. Note that
 * the values in __TK_DAT_BUFF are the raw readings and may need to be processed
 * (e.g., low-pass filtered) before being used for touch detection, depending on
 * the configuration.
 */
u16 xdata __TK_DAT_BUFF[16];

/**
 * @brief The scanning stops at the last TKx, where x is the bit counting from
 * the MSB of TK_CHANNEL_ENABLED, so we can use this variable to check if the
 * scanning is done in the interrupt handler.
 */
u8 xdata __keyNumMSB = 0;

u16 code __TOUCH_KEY_INITIAL_VAL_LOOKUP_TABLE[16] = {
    0xffff, 15, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 25,
    15,     23, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff};

u16 xdata touchKeyStatus = 0x0000;
// u16 xdata TK_Neutral[16];
bit KT_READ_DONE_FLAG = FALSE;

u8 code __TOUCH_KEY_GPIO_LOOKUP_TABLE[16][2] = {
    {GPIO_P1, GPIO_Pin_0},  // TK0
    {GPIO_P1, GPIO_Pin_1},  // TK1
    {GPIO_P5, GPIO_Pin_4},  // TK2
    {GPIO_P1, GPIO_Pin_3},  // TK3
    {GPIO_P1, GPIO_Pin_4},  // TK4
    {GPIO_P1, GPIO_Pin_5},  // TK5
    {GPIO_P2, GPIO_Pin_6},  // TK6
    {GPIO_P2, GPIO_Pin_7},  // TK7
    {GPIO_P5, GPIO_Pin_0},  // TK8
    {GPIO_P5, GPIO_Pin_1},  // TK9
    {GPIO_P5, GPIO_Pin_2},  // TK10
    {GPIO_P5, GPIO_Pin_3},  // TK11
    {GPIO_P0, GPIO_Pin_0},  // TK12
    {GPIO_P0, GPIO_Pin_1},  // TK13
    {GPIO_P0, GPIO_Pin_2},  // TK14
    {GPIO_P0, GPIO_Pin_3}   // TK15
};

/**
 * [TSIF][TSDOV][/][/][TSDNCHN 3:0]
 * TSIF, Scan complete flag, set by hardware when scan complete, write 1 to
 * clear
 *
 * TSDOV, Data overflow flag, set by hardware when data overflow, write 1
 * to clear
 *
 * TSDNCHN, Current channel number being scanned, 0 ~ 15
 */
void TouchKey_ISR() interrupt TKSU_VECTOR
{
    u8 j = TSSTA2;

    if (j & 0x40)  // 数据溢出, 错误处理(略)
    {
        TSSTA2 |= 0x40;  // 写1清零
    }
    if (j & 0x80)  // 扫描完成
    {
        j &= 0x0f;
        TSSTA2 |= 0x80;  // 写1清零

#if (TK_LOWPASS_ENABLED)
        __TK_DAT_BUFF[j] = ((__TK_DAT_BUFF[j] * 3) >> 2) + TSDAT / 16;
#else
        // __TK_DAT_BUFF[j] = TSDAT / 4;
        __TK_DAT_BUFF[j] = TSDAT;
#endif  // TK_LOWPASS_ENABLED
        if ((__TOUCH_KEY_INITIAL_VAL_LOOKUP_TABLE[j] - __TK_DAT_BUFF[j]) >=
            (TK_PRESS_THRESHOLD_MULTIPLIER *
             __TOUCH_KEY_INITIAL_VAL_LOOKUP_TABLE[j]))
        {
            touchKeyStatus |= (0x0001 << j);
        }
        else if ((__TOUCH_KEY_INITIAL_VAL_LOOKUP_TABLE[j] - __TK_DAT_BUFF[j]) <=
                 (TK_UNPRESS_THRESHOLD_MULTIPLIER *
                  __TOUCH_KEY_INITIAL_VAL_LOOKUP_TABLE[j]))
        {
            touchKeyStatus &= ~(0x0001 << j);
        }
        if (j == __keyNumMSB)
        {
            KT_READ_DONE_FLAG = TRUE;
        }
    }
}

void __TK_GPIO_Config()
{
    u8 i;
    for (i = 0; i < 16; i++)
    {
        if ((TK_CHANNEL_ENABLED >> i) & 0x0001)
        {
            GPIO_Config(__TOUCH_KEY_GPIO_LOOKUP_TABLE[i][0],
                        __TOUCH_KEY_GPIO_LOOKUP_TABLE[i][1], GPIO_HighZ);
        }
    }
}

/**
 * TK1 TK7 TK8 TK9 4 touch key channels used on board
 */
void TouchKey_Config()
{
    u8 i;
    for (i = 0; i < 16; i++)
    {
        if (TK_CHANNEL_ENABLED & (0x8000 >> i))
        {
            __keyNumMSB = 15 - i;
            break;
        }
    }
    __TK_GPIO_Config();
    TSCHEN1 = (u8)(TK_CHANNEL_ENABLED & 0x00FF);         // TK7 ~ TK0
    TSCHEN2 = (u8)((TK_CHANNEL_ENABLED >> 8) & 0x00FF);  // TK15 ~ TK8
    TSCFG1 = (7 << 4) + 6;  // Configuration register 1, SCR and DT
    TSCFG2 = 0x01;          // Configuration register 2, TSVR
    TSRT = 0x00;            // Disable the led time-sharing
    IE2 |= 0x80;  // Enable touch key interrupt, IE2 bit 7 is EUSB idk why
    // PTKSU_Priority(0);
}

bit TouchKey_IsAnyPressed()
{
    return (bit)(touchKeyStatus && TouchKey_GetPressedKeys());
}

u16 TouchKey_GetPressedKeys() { return touchKeyStatus & TK_CHANNEL_ENABLED; }

u8 TouchKey_IsPressed(u8 channel)
{
    if (channel < 16 && channel >= 0)
    {
        if ((touchKeyStatus >> channel) & 0x0001 > 0)
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
    else
    {
        return FALSE;
    }
}

u16 TouchKey_GetRawData(u8 channel)
{
    if (channel < 16 && channel >= 0)
    {
        return __TK_DAT_BUFF[channel];
    }
    else
    {
        return 0;
    }
}