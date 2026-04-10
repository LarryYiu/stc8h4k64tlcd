#ifndef __TIMER_H__
#define __TIMER_H__

#include "Config.h"
#include "STC8G_H_NVIC.h"
#include "STC8G_H_Timer.h"

/**
 * @brief Timer configuration function,
 *  Desired interrupt time = (65536 - thtl) * prescaler * clkSource / 24M
 * @param timer: Timer port (Timer0, Timer1, ... Timer4)
 * @param mode: Timer mode, can be one of the following:
 * TIM_16BitAutoReload
 * TIM_16Bit
 * TIM_8BitAutoReload
 * TIM_16BitAutoReloadNoMask
 * TIM_T1Stop
 * @param clkSource: Timer clock source, can be one of the following:
 * TIM_CLOCK_12T
 * TIM_CLOCK_1T
 * TIM_CLOCK_Ext
 * @param clkOut: Enable progammable clock output
 * @param thtl: Timer interrupt time in milliseconds (ms)
 * @param run: Whether to start the timer immediately
 * @param prescaler: Timer prescaler value, only applicable for Timer3 and
 * Timer4
 * @param priority: Timer interrupt priority
 */

//
void Timer_Config(u8 timer, u8 mode, u8 clkSource, bit clkOut, u32 thtl,
                  bit run, u8 prescaler, u8 priority);

#endif  // __TIMER_H__