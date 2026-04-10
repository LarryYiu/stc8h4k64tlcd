#include "External.h"

void Ext_Config(u8 extPort, bit edgeDetectionMode, u8 priority)
{
    EXTI_InitTypeDef ext;
    ext.EXTI_Mode = edgeDetectionMode;
    Ext_Inilize(extPort, &ext);
    if (extPort == EXT_INT0)
        NVIC_INT0_Init(ENABLE, priority);
    else if (extPort == EXT_INT1)
        NVIC_INT1_Init(ENABLE, priority);
    else if (extPort == EXT_INT2)
        NVIC_INT2_Init(ENABLE, priority);
    else if (extPort == EXT_INT3)
        NVIC_INT3_Init(ENABLE, priority);
    else if (extPort == EXT_INT4)
        NVIC_INT4_Init(ENABLE, priority);
}