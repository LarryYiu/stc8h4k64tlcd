#include "GPIO.h"

void GPIO_config(u8 pinGroup, u8 pinNumber, u8 pinMode)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.Pin = pinNumber;
    GPIO_InitStructure.Mode = pinMode;
    GPIO_Inilize(pinGroup, &GPIO_InitStructure);
    ;
}