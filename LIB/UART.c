#include "UART.h"
void UART_Config(u8 uartPort, u32 baudrate, u8 mode, u8 timerSelect,
                 bit rxEnable, bit doubleBaudrate, u8 priority, int8 pinSwitch)
{
    COMx_InitDefine COMx_InitStructure;
    COMx_InitStructure.UART_Mode = mode;
    if (uartPort != UART2)
        COMx_InitStructure.UART_BRT_Use =
            timerSelect ? timerSelect : BRT_Timer2;
    COMx_InitStructure.UART_BaudRate = baudrate;
    COMx_InitStructure.UART_RxEnable = rxEnable;
    COMx_InitStructure.BaudRateDouble = doubleBaudrate;
    UART_Configuration(UART1, &COMx_InitStructure);
    if (uartPort == UART1)
    {
        NVIC_UART1_Init(ENABLE, priority);
        if (pinSwitch != -1)
            UART1_SW(pinSwitch);
    }
    else if (uartPort == UART2)
    {
        NVIC_UART2_Init(ENABLE, priority);
        if (pinSwitch != -1)
            UART2_SW(pinSwitch);
    }
    else if (uartPort == UART3)
    {
        NVIC_UART3_Init(ENABLE, priority);
        if (pinSwitch != -1)
            UART3_SW(pinSwitch);
    }
    else if (uartPort == UART4)
    {
        NVIC_UART4_Init(ENABLE, priority);
        if (pinSwitch != -1)
            UART4_SW(pinSwitch);
    }
}