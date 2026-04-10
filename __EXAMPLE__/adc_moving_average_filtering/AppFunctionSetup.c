#include "AppFunctionSetup.h"

void App_Init()
{
    EAXSFR();
    UART_Config(UART1, 115200ul, UART_8bit_BRTx, BRT_Timer2, ENABLE, DISABLE,
                Priority_1, UART1_SW_P30_P31);
    UART_Config(UART2, 115200ul, UART_8bit_BRTx, 0, ENABLE, DISABLE, Priority_1,
                UART2_SW_P46_P47);
    Timer_Config(Timer0, TIM_16BitAutoReload, TIM_CLOCK_1T, DISABLE, 1000UL,
                 ENABLE, 0, Priority_0);
    Ext_Config(EXT_INT0, EXT_MODE_Fall, Priority_0);
    Ext_Config(EXT_INT1, EXT_MODE_Fall, Priority_0);
    GPIO_Config(GPIO_P4, GPIO_Pin_6 | GPIO_Pin_7, GPIO_PullUp);
    GPIO_Config(GPIO_P3, GPIO_Pin_All, GPIO_PullUp);
    GPIO_Config(GPIO_P1, GPIO_Pin_0, GPIO_HighZ);
    ADC_Config(31, 0, 1, ADC_SPEED_2X16T, ADC_RIGHT_JUSTIFIED, ENABLE, -1);
}