#include "Timer.h"

void Timer_Config(u8 timer, u8 mode, u8 clkSource, bit clkOut, u32 msIntr,
                  bit run, u8 prescaler, u8 priority)
{
    TIM_InitTypeDef tim;
    uint32 xdata timerLoader =
        MAIN_Fosc /
        (MAIN_Fosc / ((clkSource == TIM_CLOCK_12T ? 12 : 1) * msIntr));
    if (timerLoader > 65536UL)
    {
        timerLoader = 65536UL;
    }
    tim.TIM_Mode = mode;
    tim.TIM_ClkSource = clkSource;
    tim.TIM_ClkOut = clkOut;
    /*
     * T = (65536 - InitialValue) / Sysclk
     * Minimum InitialValue = 1, so Maximum T = 65535 / Sysclk
     * Maximum InitialValue = 65535, so Minimum T = 1 / Sysclk
     * for 1kHz interrupt, T = 1/1000s = 1ms,
     * InitialValue = 65536 - (Sysclk * T) = 65536 - (Sysclk / 1000)
     */
    tim.TIM_Value = 65536UL - timerLoader;
    tim.TIM_Run = run;
    if (prescaler)  // for timer 3/4, set prescaler value
    {
        tim.TIM_PS = prescaler;
    }
    Timer_Inilize(timer, &tim);
    if (priority)  // for timer 0/1/2, set priority value
    {
        switch (timer)
        {
            case 0:
                NVIC_Timer0_Init(ENABLE, priority);
                break;
            case 1:
                NVIC_Timer1_Init(ENABLE, priority);
                break;
            case 2:
                NVIC_Timer2_Init(ENABLE, priority);
                break;
            case 3:
                NVIC_Timer3_Init(ENABLE, priority);
                break;
            case 4:
                NVIC_Timer4_Init(ENABLE, priority);
                break;
        }
    }
    else
    {
        switch (timer)
        {
            case 0:
                NVIC_Timer0_Init(ENABLE, NULL);
                break;
            case 1:
                NVIC_Timer1_Init(ENABLE, NULL);
                break;
            case 2:
                NVIC_Timer2_Init(ENABLE, NULL);
                break;
            case 3:
                NVIC_Timer3_Init(ENABLE, NULL);
                break;
            case 4:
                NVIC_Timer4_Init(ENABLE, NULL);
                break;
        }
    }
}