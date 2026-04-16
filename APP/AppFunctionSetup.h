#ifndef __APP_FUNCTION_SETUP_H__
#define __APP_FUNCTION_SETUP_H__

#include <stc8h.h>

#include "Config.h"
#include "GPIO.h"
#include "Key.h"
#include "RTC.h"
#include "STC8G_H_Delay.h"
#include "STC8G_H_GPIO.h"
#include "STC8G_H_NVIC.h"
#include "STC8G_H_Switch.h"
#include "STC8G_H_Timer.h"
#include "STC8G_H_UART.h"
#include "Timer.h"
#include "UART.h"

#ifndef APP_DEBUG
#define APP_DEBUG FALSE
#endif  // APP_DEBUG

void App_Init();

#endif  // __APP_FUNCTION_SETUP_H__