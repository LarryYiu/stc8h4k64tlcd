#ifndef __APP_FUNCTION_SETUP_H__
#define __APP_FUNCTION_SETUP_H__

#include <stc8h.h>

#include "Config.h"
#include "GPIO.h"
#include "STC8G_H_Delay.h"
#include "STC8G_H_GPIO.h"
#include "STC8G_H_NVIC.h"
#include "STC8G_H_Switch.h"
#include "STC8G_H_Timer.h"
#include "STC8G_H_UART.h"
#include "Timer.h"
#include "TouchKey.h"
#include "UART.h"

#define MAF_TOTAL_SAMPLE 50
#define MAF_MOVING_SAMPLE 6
#define V_REF 1.19
#define MAX_SAMPLE_STOREING 30
#define APP_DEBUG FALSE
#define COMMAND_PRINT_DATA "Read ADC"

void App_Init();

#endif  // __APP_FUNCTION_SETUP_H__