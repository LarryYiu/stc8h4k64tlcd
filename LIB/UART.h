#ifndef __UART_H__
#define __UART_H__

#include "Config.h"
#include "STC8G_H_NVIC.h"
#include "STC8G_H_Switch.h"
#include "STC8G_H_UART.h"

/**
 * @brief  UART configuration function
 * @param  uartPort: UART port number (UART1, UART2, UART3, UART4)
 * @param  baudrate: Desired baud rate (e.g., 9600, 115200)
 * @param  mode: UART mode (e.g., UART_8bit_BRTx)
 * @param  timerSelect: Timer selection for baud rate generation (0 for auto, or
 * specific timer), UART2 fixed on BRT_Timer2
 * BRT_Timer1
 * BRT_Timer2
 * BRT_Timer3
 * BRT_Timer4
 * @param  rxEnable: Enable or disable UART reception (ENABLE or DISABLE)
 * @param  doubleBaudrate: Enable or disable double baud rate (ENABLE or
 * DISABLE)
 * @param  priority: NVIC interrupt priority (e.g., Priority_0, Priority_1).
 * Need <STC8G_H_NVIC.h>
 * @param  pinSwitch: Pin switch configuration for UART (e.g., UART1_SW_P30_P31,
 * or -1 for no switch) Need <STC8G_H_Switch.h>
 */
void UART_Config(u8 uartPort, u32 baudrate, u8 mode, u8 timerSelect,
                 bit rxEnable, bit doubleBaudrate, u8 priority, int8 pinSwitch);

#endif  // __UART_H__