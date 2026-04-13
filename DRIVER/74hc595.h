#ifndef __74HC595_H__
#define __74HC595_H__

#include "Config.h"

#ifndef __PIN_HC595_SCK__
#define __PIN_HC595_SCK__ P77
#endif

#ifndef __PIN_HC595_RCK__
#define __PIN_HC595_RCK__ P76
#endif

#ifndef __PIN_HC595_SI__
#define __PIN_HC595_SI__ P41
#endif

/**
 * @brief Send a byte to the 74HC595.
 */
void HC595_SendByte(u8 dat);

/**
 * @brief Latch the data from the shift register to the output pins of the
 * 74HC595.
 *
 * RCK 1 -> 0 -> 1;
 */
void HC595_Output();

#endif  // __74HC595_H__
