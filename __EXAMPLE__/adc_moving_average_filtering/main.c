/**
 * @brief This is an example code for ADC moving average filtering. It collects
 * the ADC values of channel 0, a potentiometer in this case, and calculates the
 * moving average, with the maximum sample number defined by MAF_TOTAL_SAMPLE
 * (50) and the number replacing MAF_MOVING_SAMPLE (log_2(50) ≈ 6).
 */
#include <stc8h.h>
#include <string.h>

#include "ADC.h"
#include "AppFunctionSetup.h"
#include "Config.h"
#include "Utility.h"

void main(void)
{
    float voltRead = 0;
    u16 adValueC0 = 0;
    float xdata
        voltCollection1[MAF_TOTAL_SAMPLE];  // array1 to store adc results
    float xdata
        voltCollection2[MAF_TOTAL_SAMPLE];  // array2 to store adc results
    bit processFirstCollection =
        FALSE;  // flag indicates which array is being filled with new coming
                // adc results, then procceed to calculate the average when
                // enough samples are collected

    u8 currLen = 0;
    u8 fillLen = 0;
    u8 offset = 0;

    App_Init();

    EA = 1;

    PrintString1("STC8 UART1 Working!\r\n");
    printf("STC8 UART2 Working!\r\n");

    // collect initial adc samples to fill the array, then calculate the
    // average.
    for (currLen = 0; currLen < MAF_TOTAL_SAMPLE; currLen++)
    {
        adValueC0 = Get_ADCResult(0);
        voltRead = V_REF / Get_ADCResult(15) * adValueC0;

        voltCollection1[currLen] = voltRead;
        voltCollection2[currLen] = voltRead;
    }
    printf("Ad_First  = %.3f\n",
           ADC_AverageFilter(voltCollection1, MAF_TOTAL_SAMPLE,
                             MAF_MOVING_SAMPLE));

    while (1)
    {
        adValueC0 = Get_ADCResult(0);  // get the adc value of channel 0, which
                                       // is connected to the current sensor (a
                                       // potentiometer in this case)
        voltRead = V_REF / Get_ADCResult(15) *
                   adValueC0;  // convert the adc value to voltage according to
                               // the reference voltage and adc resolution (12
                               // bits for STC8H series)
        if (fillLen >= MAF_MOVING_SAMPLE)
        {
            if (processFirstCollection)
            {
                memcpy(
                    voltCollection2, voltCollection1,
                    MAF_TOTAL_SAMPLE *
                        sizeof(float));  // copy the whole array to another one
                                         // for average calculation, so that the
                                         // original array can be filled with
                                         // new coming adc results without being
                                         // affected by the sorting.
                printf("Ad_Col1  = %.3f\n",
                       ADC_AverageFilter(voltCollection1, MAF_TOTAL_SAMPLE,
                                         MAF_MOVING_SAMPLE));
            }
            else
            {
                memcpy(
                    voltCollection1, voltCollection2,
                    MAF_TOTAL_SAMPLE *
                        sizeof(float));  // copy the whole array to another one
                                         // for average calculation, so that the
                                         // original array can be filled with
                                         // new coming adc results without being
                                         // affected by the sorting.
                printf("Ad_Col2  = %.3f\n",
                       ADC_AverageFilter(voltCollection2, MAF_TOTAL_SAMPLE,
                                         MAF_MOVING_SAMPLE));
            }
            fillLen = 0;  // reset the fill length for the next collection
            processFirstCollection =
                !processFirstCollection;  // toggle the flag
        }
        else
        {
            if (processFirstCollection)
            {
                voltCollection1[offset] = voltRead;
            }
            else
            {
                voltCollection2[offset] = voltRead;
            }
            fillLen++;
            offset = (offset + 1) %
                     MAF_TOTAL_SAMPLE;  // move the offset for the next adc
                                        // result, and loop back to 0 when it
                                        // reaches the end of the array
        }
    }
}