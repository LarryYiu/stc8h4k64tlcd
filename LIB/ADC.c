#include "ADC.h"

void ADC_Config(u8 sampleDuty, bit csCtl, u8 csHold, u8 clkFreq,
                bit resJustification, bit pwrOn, int8 priority)
{
    ADC_InitTypeDef adc;

    adc.ADC_SMPduty = sampleDuty;
    adc.ADC_CsSetup = csCtl;
    adc.ADC_CsHold = csHold;
    adc.ADC_Speed = clkFreq;
    adc.ADC_AdjResult = resJustification;

    ADC_Inilize(&adc);
    ADC_PowerControl(pwrOn);
    if (priority < 0)
    {
        NVIC_ADC_Init(DISABLE, Priority_0);
    }
    else
    {
        NVIC_ADC_Init(ENABLE, priority);
    }
}

float ADC_AverageFilter(float* dat, u8 len, u8 dropNum)
{
    if (len == 0 || dropNum >= len)
    {
        return 0;
    }
    else
    {
        u8 i;
        u8 end = len - dropNum;
        float sum = 0;
        InsertionSort(dat, len);
        for (i = dropNum; i < end; i++)
        {
            sum += dat[i];
        }
        return sum / (end - dropNum);
    }
}
