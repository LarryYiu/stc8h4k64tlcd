## [07/04] Migrating digital tubes
### req: 74hc595
test the latching order: Done, seg->num
test a single number display: Done
short [-9999999, 9999999]: Done
float [-99999, 99999], up to 3 dp: Done
### req: a GPIO wrapper to setup the GPIO functions
Done
### opt: add key driver (busy waiting)
Done

## [08/04] Timer
### add Timer wrapper
Done

## [09/04] UART/Counter
### add UART config wrapper
done
### add counter wrapper
done

## [10/04] ADC
### add ADC config wrapper
done
### add ADC example: moving average filter
#### req: sorting algorithm -> Insertion Sort
done
#### req: MAF algorithm
done

## [11/04] I2C & AT24C02
### add I2C config wrapper and R/W wrapper for AT24C02
done
### add R/W example
done

## [13/04] Touch Key
### add touch key driver
done
### add RTC driver
### refine adc example reliability: add checksum mech, add redundant data check to prevent duplicate data wrting to EEPROM

