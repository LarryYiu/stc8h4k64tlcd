#ifndef __GPIO_H__
#define __GPIO_H__

#include "Config.h"
#include "STC8G_H_GPIO.h"

/**
 * @brief GPIO pin configuration function
 * @param pinGroup: GPIO pin group (e.g., P1x, P2x, etc.)
 * @param pinNumber: GPIO pin number within the group (0-7)
 * @param pinMode: GPIO pin mode, can be one of the following: GPIO_PullUp,
 * GPIO_HighZ, GPIO_OUT_OD, GPIO_OUT_PP
 */
void GPIO_Config(u8 pinGroup, u8 pinNumber, u8 pinMode);
#endif