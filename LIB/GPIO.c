#include "GPIO.h"

extern u8 code GPIO_PIN_LOOKUP_TABLE[8] = {GPIO_Pin_0, GPIO_Pin_1, GPIO_Pin_2,
                                           GPIO_Pin_3, GPIO_Pin_4, GPIO_Pin_5,
                                           GPIO_Pin_6, GPIO_Pin_7};

extern u8 code GPIO_GROUP_LOOKUP_TABLE[8] = {
    GPIO_P0, GPIO_P1, GPIO_P2, GPIO_P3, GPIO_P4, GPIO_P5, GPIO_P6, GPIO_P7};

void GPIO_Config(u8 pinGroup, u8 pinNumber, u8 pinMode)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.Pin = pinNumber;
    GPIO_InitStructure.Mode = pinMode;
    GPIO_Inilize(pinGroup, &GPIO_InitStructure);
}