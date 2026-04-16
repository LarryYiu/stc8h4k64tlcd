#include "AppFunctionSetup.h"

void App_Init()
{
    EAXSFR();
    UART_Config_Common();
    Timer_Config_t0_1ms();
    RTC_Config(NULL);
    Key_Config();

    // other peripheral configurations can be added here
    GPIO_Config(GPIO_P0, GPIO_Pin_All, GPIO_PullUp);  // LEDs
}