#include "STC8G_H_Exti.h"

u8 WakeUpSource;

void INT0_ISR_Handler(void) interrupt INT0_VECTOR { WakeUpSource = 1; }

void INT1_ISR_Handler(void) interrupt INT1_VECTOR { WakeUpSource = 2; }

void INT2_ISR_Handler(void) interrupt INT2_VECTOR { WakeUpSource = 3; }

void INT3_ISR_Handler(void) interrupt INT3_VECTOR { WakeUpSource = 4; }

void INT4_ISR_Handler(void) interrupt INT4_VECTOR { WakeUpSource = 5; }
