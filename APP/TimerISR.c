#include "Key.h"
#include "STC8G_H_Timer.h"

u32 xdata time0IntNum = 0;

void Timer0_ISR_Handler(void) interrupt TMR0_VECTOR
{
    time0IntNum++;
    if (time0IntNum % 100 == 0)
    {
        Key_Scan();  // scan keys every 100ms
    }
}

void Timer1_ISR_Handler(void) interrupt TMR1_VECTOR {}

void Timer2_ISR_Handler(void) interrupt TMR2_VECTOR {}

void Timer3_ISR_Handler(void) interrupt TMR3_VECTOR {}

void Timer4_ISR_Handler(void) interrupt TMR4_VECTOR {}
