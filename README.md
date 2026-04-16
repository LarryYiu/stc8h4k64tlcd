# Brief
This is a learning series of STC's STC8H chip
Which is very similar to the 8051 series, but with more features and better performance.


## Table of Contents

## ADC
This MCU has a built-in 16-bit ADC, which is used  to measure the voltage on this board.
for more details, please refer to `__EXAMPLE__/adc_moving_average_filtering/`.

## EEPROM and I2C
Unlike the STC89C52 chip using software I2C, this MCU has a built-in I2C module, which is used to communicate with the AT24C02 EEPROM. please refer to `__EXAMPLE__/at24c02_i2c/`.

## RTC
MCU has a built-in 32 kHz RTC, but an external 32.768 kHz crystal is used on the board for better accuracy.

## Touch Key
MCU does have built-in touch key function, but it does not have official library supoort, many codes are adapted from the community examples.

