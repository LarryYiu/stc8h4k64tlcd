#ifndef __RTC_H__
#define __RTC_H__

#include "Config.h"
#include "STC8G_H_NVIC.h"
#include "STC8H.h"
#include "STC8H_RTC.h"

#define RTC_BASE_YEAR 2000

extern bit B_1S;
extern bit B_Alarm;

typedef struct
{
    u8 year;    // 0-99
    u8 month;   // 1-12
    u8 day;     // 1-31
    u8 hour;    // 0-23
    u8 minute;  // 0-59
    u8 second;  // 0-59
} RTC_DateTime_t;

typedef struct
{
    u8 hour;    // 0-23
    u8 minute;  // 0-59
    u8 second;  // 0-59
} RTC_Alarm_t;

void RTC_Config(const void* timeIn);

/**
 * @brief Set the RTC time, be aware that the year is represented as a two-digit
 * value (0-99) corresponding to the last two digits of the year (e.g., 23 for
 * 2023). This function does not extend the register access.
 *
 * @param dateTime Pointer to an RTC_DateTime_t structure containing the date
 * and time to set
 */
void RTC_SetTime(const RTC_DateTime_t* dateTime);

void RTC_GetTime(RTC_DateTime_t* dateTime);

void RTC_SetAlarm(const RTC_Alarm_t* alarmTime);

#endif  // __RTC_H__