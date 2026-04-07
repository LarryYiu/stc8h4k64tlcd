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

void HC595_SendByte(u8 dat);
void HC595_Output();

#endif  // __74HC595_H__
