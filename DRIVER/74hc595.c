#include "74hc595.h"

#include <STC8H.h>

void HC595_SendByte(u8 dat)
{
    u8 i;
    for (i = 0; i < 8; i++)
    {
        __PIN_HC595_SCK__ = LOW;
        __PIN_HC595_SI__ = dat & 0x80;
        dat <<= 1;
        __PIN_HC595_SCK__ = HIGH;
    }
}

void HC595_Output()
{
    __PIN_HC595_RCK__ = LOW;
    __PIN_HC595_RCK__ = HIGH;
}
