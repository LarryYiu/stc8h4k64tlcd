#ifndef __ADC_H__
#define __ADC_H__

#include "Config.h"
#include "STC8G_H_ADC.h"
#include "STC8G_H_GPIO.h"
#include "STC8G_H_NVIC.h"
#include "Utility.h"

/**
 * @brief ADC Configuration function
 *
 * @param sampleDuty sample time control for ADC analog signal, range: 0~31
 * (Note: SMPDUTY must not be set less than 10)
 * @param csCtl channel selection of time control for ADC, 0 (default), 1
 * @param csHold channel selection of hold time control for ADC,
 * 0, 1 (default), 2, 3
 * @param clkFreq ADC working clock frequency, ADC_SPEED_2X1T~ADC_SPEED_2X16T
 * @param resJustification ADC result adjustment, ADC_LEFT_JUSTIFIED,
 * ADC_RIGHT_JUSTIFIED
 * @param pwrOn ADC power control, ENABLE or DISABLE
 * @param priority ADC interrupt priority, Priority_0, Priority_1, Priority_2,
 * Priority_3
 */
void ADC_Config(u8 sampleDuty, bit csCtl, u8 csHold, u8 clkFreq,
                bit resJustification, bit pwrOn, int8 priority);

/**
 * @brief ADC average filter function, which will sort the data and drop the
 * specified number of the maximum and minimum data, then calculate the average
 * value of the remaining data and return it. This function does not extend the
 * register access.
 *
 * @param dat the data array to be processed
 * @param len the length of the data array
 * @param dropNum the number of the maximum and minimum data to be dropped
 * @return the average value of the remaining data after dropping the specified
 */
float ADC_AverageFilter(float* dat, u8 len, u8 dropNum);

/**
 * @brief ADC common configuration function, which will configure the ADC with
 * the default settings for this project.
 */
void ADC_Config_Common();
#endif  // __ADC_H__