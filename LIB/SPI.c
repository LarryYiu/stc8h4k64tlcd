#include "SPI.h"

void SPI_Config_Manual(bit SPI_Enable, bit SS_Enable, bit shiftDirection,
                       bit masterSlave, bit CPOL, bit CPHA, u8 clkFreq,
                       int8 priority, u8 SPI_Pins)
{
    SPI_InitTypeDef SPI_InitStructure;

    SPI_InitStructure.SPI_Enable =
        SPI_Enable;                          // SPI enabler    ENABLE, DISABLE
    SPI_InitStructure.SPI_SSIG = SS_Enable;  // SS     ENABLE, DISABLE
    SPI_InitStructure.SPI_FirstBit =
        shiftDirection;  // first bit to transmit: SPI_MSB, SPI_LSB
    SPI_InitStructure.SPI_Mode =
        masterSlave;  // Mode: SPI_Mode_Master, SPI_Mode_Slave
    SPI_InitStructure.SPI_CPOL =
        CPOL;  // clock polarity: SPI_CPOL_High, SPI_CPOL_Low
               // idle state of the clock:
               // high(leading-falling) or low(leading-rising)
    SPI_InitStructure.SPI_CPHA =
        CPHA;  // clock phase: SPI_CPHA_1Edge, SPI_CPHA_2Edge
               // leading (starts on SS low) or trailing edge sampling datum
    SPI_InitStructure.SPI_Speed =
        clkFreq;  // SPI clock frequency
                  // SPI_Speed_4,SPI_Speed_16,SPI_Speed_64,SPI_Speed_2/SPI_Speed_32
    SPI_Init(&SPI_InitStructure);
    if (priority >= 0)
    {
        NVIC_SPI_Init(ENABLE, priority > 3 ? 3 : priority);
    }
    else
    {
        NVIC_SPI_Init(DISABLE, Priority_0);
    }

    SPI_SW(
        SPI_Pins);  // SPI_P12_P13_P14_P15,SPI_P22_P23_P24_P25,SPI_P54_P40_P41_P43,SPI_P35_P34_P33_P32

    //  SPI_SCK = 0;    // set clock to low initial state
    //  SPI_SI = 1;
}

void SPI_Config_Common()
{
    SPI_Config_Manual(ENABLE, ENABLE, SPI_MSB, SPI_Mode_Master, SPI_CPOL_High,
                      SPI_CPHA_2Edge, SPI_Speed_16, Priority_3,
                      SPI_P12_P13_P14_P15);
}
