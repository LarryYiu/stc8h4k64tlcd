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

void UART_Config_Common()
{
    UART_Config(UART1, 115200ul, UART_8bit_BRTx, BRT_Timer2, ENABLE, DISABLE,
                Priority_1, UART1_SW_P30_P31);
    UART_Config(UART2, 115200ul, UART_8bit_BRTx, 0, ENABLE, DISABLE, Priority_1,
                UART2_SW_P46_P47);
    GPIO_Config(GPIO_P3, GPIO_Pin_0 | GPIO_Pin_1, GPIO_PullUp);
    GPIO_Config(GPIO_P4, GPIO_Pin_6 | GPIO_Pin_7, GPIO_PullUp);
}

/*****************************************************************
 * Code below adapted from STC8H_LIB, not modified.
 *****************************************************************/

#ifdef UART1
void UART1_ISR_Handler(void) interrupt UART1_VECTOR
{
    if (RI)
    {
        RI = 0;

        if (COM1.RX_Cnt >= COM_RX1_Lenth)
            COM1.RX_Cnt = 0;
        RX1_Buffer[COM1.RX_Cnt++] = SBUF;
        COM1.RX_TimeOut = TimeOutSet1;
    }

    if (TI)
    {
        TI = 0;

#if (UART_QUEUE_MODE == 1)
        if (COM1.TX_send != COM1.TX_write)
        {
            SBUF = TX1_Buffer[COM1.TX_send];
            if (++COM1.TX_send >= COM_TX1_Lenth)
                COM1.TX_send = 0;
        }
        else
            COM1.B_TX_busy = 0;
#else
        COM1.B_TX_busy = 0;
#endif
    }
}
#endif

#ifdef UART2
void UART2_ISR_Handler(void) interrupt UART2_VECTOR
{
    if (RI2)
    {
        CLR_RI2();

        if (COM2.RX_Cnt >= COM_RX2_Lenth)
            COM2.RX_Cnt = 0;
        RX2_Buffer[COM2.RX_Cnt++] = S2BUF;
        COM2.RX_TimeOut = TimeOutSet2;
    }

    if (TI2)
    {
        CLR_TI2();

#if (UART_QUEUE_MODE == 1)
        if (COM2.TX_send != COM2.TX_write)
        {
            S2BUF = TX2_Buffer[COM2.TX_send];
            if (++COM2.TX_send >= COM_TX2_Lenth)
                COM2.TX_send = 0;
        }
        else
            COM2.B_TX_busy = 0;
#else
        COM2.B_TX_busy = 0;
#endif
    }
}
#endif

#ifdef UART3
void UART3_ISR_Handler(void) interrupt UART3_VECTOR
{
    if (RI3)
    {
        CLR_RI3();

        if (COM3.RX_Cnt >= COM_RX3_Lenth)
            COM3.RX_Cnt = 0;
        RX3_Buffer[COM3.RX_Cnt++] = S3BUF;
        COM3.RX_TimeOut = TimeOutSet3;
    }

    if (TI3)
    {
        CLR_TI3();

#if (UART_QUEUE_MODE == 1)
        if (COM3.TX_send != COM3.TX_write)
        {
            S3BUF = TX3_Buffer[COM3.TX_send];
            if (++COM3.TX_send >= COM_TX3_Lenth)
                COM3.TX_send = 0;
        }
        else
            COM3.B_TX_busy = 0;
#else
        COM3.B_TX_busy = 0;
#endif
    }
}
#endif

#ifdef UART4
void UART4_ISR_Handler(void) interrupt UART4_VECTOR
{
    if (RI4)
    {
        CLR_RI4();

        if (COM4.RX_Cnt >= COM_RX4_Lenth)
            COM4.RX_Cnt = 0;
        RX4_Buffer[COM4.RX_Cnt++] = S4BUF;
        COM4.RX_TimeOut = TimeOutSet4;
    }

    if (TI4)
    {
        CLR_TI4();

#if (UART_QUEUE_MODE == 1)
        if (COM4.TX_send != COM4.TX_write)
        {
            S4BUF = TX4_Buffer[COM4.TX_send];
            if (++COM4.TX_send >= COM_TX4_Lenth)
                COM4.TX_send = 0;
        }
        else
            COM4.B_TX_busy = 0;
#else
        COM4.B_TX_busy = 0;
#endif
    }
}
#endif
