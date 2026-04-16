#ifndef __EXTERNAL_H__
#define __EXTERNAL_H__

#include "Config.h"
#include "STC8G_H_Exti.h"
#include "STC8G_H_NVIC.h"

/**
 * @brief Configure external interrupt with specified edge detection mode and
 * priority. This function does not extend the register access.
 * @param extPort External interrupt port (0-3)
 * @param edgeDetectionMode can be EXT_MODE_RiseFall, EXT_MODE_Fall
 * @param priority Interrupt priority
 */
void Ext_Config(u8 extPort, bit edgeDetectionMode, u8 priority);

#endif  // __EXTERNAL_H__
