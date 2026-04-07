#ifndef __KEY_H__
#define __KEY_H__

#include <STC8H.h>

#include "Config.h"
#include "GPIO.h"
#include "STC8G_H_Delay.h"
#include "STC8G_H_GPIO.H"

void Key_Init();
bool Key_ScanBusy(u8* keyNum);

#endif  // __KEY_H__