#ifndef __SPI_H__
#define __SPI_H__

#include "Config.h"
#include "STC8G_H_GPIO.h"
#include "STC8G_H_NVIC.h"
#include "STC8G_H_SPI.h"
#include "STC8G_H_Switch.h"

/**
 * @brief  Configure SPI by manually setting parameters. This function does not
 * extend the register access.
 *
 * @param  SPI_Enable: ENABLE or DISABLE the SPI module.
 *
 * @param  SS_Enable: ENABLE or DISABLE the Slave Select (SS) function.
 *
 * @param  shiftDirection: SPI_MSB or SPI_LSB to specify the first bit to
 * transmit.
 *
 * @param  masterSlave: SPI_Mode_Master or SPI_Mode_Slave to set the SPI mode.
 * @param  CPOL: Clock polarity (idle state of the clock). High
 * (leading-falling) or low (leading-rising). SPI_CPOL_High, SPI_CPOL_Low
 *
 * @param  CPHA: Clock phase (leading or trailing edge sampling).
 * SPI_CPHA_1Edge, SPI_CPHA_2Edge
 *
 * @param  clkFreq: SPI clock frequency, options include
 * SPI_Speed_4,SPI_Speed_16,SPI_Speed_64,SPI_Speed_2/SPI_Speed_32
 *
 * @param  priority: Interrupt priority level (0-3) for SPI interrupts, or a
 * negative value to disable priority.
 *
 * @param  SPI_Pins: Pin configuration for SPI, options include
 * SPI_P12_P13_P14_P15,SPI_P22_P23_P24_P25,SPI_P54_P40_P41_P43,SPI_P35_P34_P33_P32
 */
void SPI_Config_Manual(bit SPI_Enable, bit SS_Enable, bit shiftDirection,
                       bit masterSlave, bit CPOL, bit CPHA, u8 clkFreq,
                       int8 priority, u8 SPI_Pins);

void SPI_Config_Common();

#endif  // __SPI_H__