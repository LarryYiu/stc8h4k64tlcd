/**
 * @brief This piece of code using I2C storting the ADC reading result into
 * AT24C02, and print the stored data from UART2 when receiving the command from
 * UART1.
 *
 * Some of the code are adapted from the codebase provided by the manufacturer
 * and course instructor.
 *
 * For the detail of ADC reading and average filtering, please refer to the
 * "__EXAMPLE__/adc_moving_average_filtering" folder.
 */
#include <stc8h.h>
#include <string.h>

#include "ADC.h"
#include "AT24C02.h"
#include "AppFunctionSetup.h"
#include "Config.h"
#include "STC8G_H_Delay.h"
#include "STC8G_H_UART.h"
#include "Utility.h"
/**
 * @brief Advance the page number and offset for AT24C02 storage
 * @param pageNum Pointer to the current page number
 * @param offset Pointer to the current offset within the page
 *
 * This function updates the page number and offset for storing data in the
 * AT24C02 EEPROM. If the offset exceeds the maximum allowed (1* in this case),
 * the page number is incremented and the offset is reset to 0.
 *
 * 1*: Since each page can store 2 float values (each float is 4 bytes, and the
 * page size is 8 bytes), the offset can only be 0 or 1. When offset reaches 1,
 * it means the current page is full, and we need to move to the next page for
 * storing the next float value.
 */
void advanceAddr(u8* pageNum, u8* offset)
{
    if (*offset >= 1)
    {
        *offset = 0;
        *pageNum = (*pageNum + 1) % (MAX_SAMPLE_STOREING / 2);
    }
    else
    {
        (*offset)++;
    }
}
/**
 * @brief Handle the print command received from UART1, then print the stored
 * data from AT24C02 to UART2.
 * @param saveCntIn The number of valid samples currently stored in AT24C02, or
 * then length of the data to be printed.
 */
void printHandler(u8 saveCntIn)
{
    bit isCommandMatched = FALSE;
    if (COM1.RX_TimeOut > 0)  // 超时计数
    {
        if (--COM1.RX_TimeOut == 0)
        {
            if (COM1.RX_Cnt > 0)
            {
#if (APP_DEBUG)
                u8 i;
                for (i = 0; i < COM1.RX_Cnt; i++) TX1_write2buff(RX1_Buffer[i]);
#endif  // APP_DEBUG
                isCommandMatched = strncmp(RX1_Buffer, COMMAND_PRINT_DATA,
                                           strlen(COMMAND_PRINT_DATA)) == 0;
            }
            COM1.RX_Cnt = 0;
        }
    }
    if (isCommandMatched)
    {
        if (saveCntIn == 0)
        {
            printf("No data stored yet!\n");
            return;
        }
        else
        {
            u8 i;
            u8 _pageNum = 0;
            u8 _offset = 0;
            float xdata _dat;
            for (i = 0; i < saveCntIn; i++)
            {
                AT24C02_ReadFloat(_pageNum, _offset, &_dat);
                printf("Data at page %bu offset %bu is %.3f\n", _pageNum,
                       _offset, _dat);
                advanceAddr(&_pageNum, &_offset);
            }
        }
    }
    return;
}

void main(void)
{
    float xdata voltRead = 0;
    u16 xdata adValueC0 = 0;
    float xdata voltCollection1[MAF_TOTAL_SAMPLE];
    float xdata voltCollection2[MAF_TOTAL_SAMPLE];
    bit processFirstCollection = FALSE;

    u8 xdata currLen = 0;
    u8 xdata fillLen = 0;
    u8 xdata offset = 0;

    float xdata resBuff = 0.0F;
    u8 pageNum = 0;
    u8 isFirstSlot = 0;
    u8 saveCnt = 1;

    App_Init();

    EA = 1;
#if (APP_DEBUG)
    PrintString1("STC8 UART1 Working!\r\n");
    printf("STC8 UART2 Working!\r\n");
#endif  // APP_DEBUG

    for (currLen = 0; currLen < MAF_TOTAL_SAMPLE; currLen++)
    {
        adValueC0 = Get_ADCResult(0);
        voltRead = V_REF / Get_ADCResult(15) * adValueC0;

        voltCollection1[currLen] = voltRead;
        voltCollection2[currLen] = voltRead;
    }
#if (APP_DEBUG)
    printf("Ad_First  = %.3f\n",
           ADC_AverageFilter(voltCollection1, MAF_TOTAL_SAMPLE,
                             MAF_MOVING_SAMPLE));
#endif  // APP_DEBUG

    resBuff =
        ADC_AverageFilter(voltCollection1, MAF_TOTAL_SAMPLE, MAF_MOVING_SAMPLE);

    AT24C02_WriteFloat(pageNum, isFirstSlot,
                       &resBuff);  // Write the first sample to AT24C02
    advanceAddr(
        &pageNum,
        &isFirstSlot);  // Update the page number and offset for the next write
    saveCnt++;  // Increment the count of valid samples stored in AT24C02
    while (1)
    {
        adValueC0 = Get_ADCResult(0);
        voltRead = V_REF / Get_ADCResult(15) * adValueC0;
        if (fillLen >= MAF_MOVING_SAMPLE)
        {
            if (processFirstCollection)
            {
                memcpy(voltCollection2, voltCollection1,
                       MAF_TOTAL_SAMPLE * sizeof(float));
#if (APP_DEBUG)
                printf("Ad_Col1  = %.3f\n",
                       ADC_AverageFilter(voltCollection1, MAF_TOTAL_SAMPLE,
                                         MAF_MOVING_SAMPLE));
#endif  // APP_DEBUG
                resBuff = ADC_AverageFilter(voltCollection1, MAF_TOTAL_SAMPLE,
                                            MAF_MOVING_SAMPLE);
                AT24C02_WriteFloat(pageNum, isFirstSlot, &resBuff);
                advanceAddr(&pageNum, &isFirstSlot);
                saveCnt = (saveCnt + 1) % MAX_SAMPLE_STOREING;
            }
            else
            {
                memcpy(voltCollection1, voltCollection2,
                       MAF_TOTAL_SAMPLE * sizeof(float));
#if (APP_DEBUG)
                printf("Ad_Col2  = %.3f\n",
                       ADC_AverageFilter(voltCollection2, MAF_TOTAL_SAMPLE,
                                         MAF_MOVING_SAMPLE));
#endif  // APP_DEBUG

                resBuff = ADC_AverageFilter(voltCollection2, MAF_TOTAL_SAMPLE,
                                            MAF_MOVING_SAMPLE);
                AT24C02_WriteFloat(pageNum, isFirstSlot, &resBuff);
                advanceAddr(&pageNum, &isFirstSlot);
                saveCnt = (saveCnt + 1) % MAX_SAMPLE_STOREING;
            }
            fillLen = 0;
            processFirstCollection = !processFirstCollection;
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
            offset = (offset + 1) % MAF_TOTAL_SAMPLE;
        }
        delay_ms(10);
        printHandler(saveCnt);
    }
}