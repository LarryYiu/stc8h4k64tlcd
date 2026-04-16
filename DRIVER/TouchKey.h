#ifndef __TOUCH_KEY_H__
#define __TOUCH_KEY_H__

#include <stc8h.h>

#include "Config.h"
#include "GPIO.h"
#include "STC8G_H_Delay.h"
#include "STC8G_H_GPIO.h"
#include "STC8G_H_NVIC.h"
#include "STC8G_H_Switch.h"

/**
 * MSB channel 15 ~ LSB channel 0, bit 0 ~ bit 15, 1 for enable, 0 for disable
 */
#ifndef TK_CHANNEL_ENABLED
#define TK_CHANNEL_ENABLED 0x0382  // TK7 TK1 TK8 TK9 default (on my board)
#endif                             // TK_CHANNEL_ENABLED

#ifndef TK_LOWPASS_ENABLED
#define TK_LOWPASS_ENABLED FALSE
#endif  // TK_LOWPASS_ENABLED

#ifndef TK_PRESS_THRESHOLD_MULTIPLIER
#define TK_PRESS_THRESHOLD_MULTIPLIER 0.5F
#endif  // TK_PRESS_THRESHOLD_MULTIPLIER

#ifndef TK_UNPRESS_THRESHOLD_MULTIPLIER
#define TK_UNPRESS_THRESHOLD_MULTIPLIER 0.666F
#endif  // TK_UNPRESS_THRESHOLD_MULTIPLIER

/**
 * TouchKey_t is used to store the state of each touch key, including:
 * - keyNum: the user defined key number for the application, the real indicator
 * of the TK0 - TK15 is the index of touch keys.
 */
typedef struct
{
    u8 keyNum;
    u8 pressDuration;
    u8 pressCount;
    u8 lastReleaseDuration;
    u8 isPressing;
    u8 isLastPressing;
} TouchKey_t;

/**
 * @brief touchKeyStatus is a 16-bit variable where each bit represents the
 * current status of a touch key (1 for pressed, 0 for not pressed).
 * MSB 15 ~ LSB 0 corresponds to TK15 ~ TK0. The status is updated in the
 * interrupt handler.
 */
extern u16 xdata touchKeyStatus;

/**
 * @brief currTouchKey is a structure that can be used to store the current
 * state of a touch key, such as which key is being pressed, how long it has
 * been pressed, and other related information.
 *
 * @note: In this implementation, we only support tracking one touch key at a
 * time for space saving, so this variable is not fully utilized. It can be
 * extended to a 16 element array if we want to track all keys simultaneously,
 * but that would consume more memory.
 */
extern TouchKey_t xdata currTouchKey;  // only support one for space saving

// For auto-calibration, not implemented yet
// extern u16 xdata TK_Neutral[16];
/**
 * @brief KT_READ_DONE_FLAG is a flag that indicates whether the touch key
 * scanning is completed for the current scan cycle. It is set to TRUE in the
 * interrupt handler when the scanning is done. The main loop can check this
 * flag to know when to read the touch key status and perform related actions.
 * After processing the touch key status, the main loop should set this flag
 * back to FALSE to wait for the next scan cycle.
 *
 * @note the flag is not essential if the timer is tuned properly.
 */
extern bit KT_READ_DONE_FLAG;

/**
 * @brief TouchKey_Config initializes the touch key channels and related GPIOs.
 * It should be called before using any touch key functions. This function WILL
 * configure the GPIO pins for the enabled touch key channels, set up the touch
 * key scanning parameters, and enable the touch key interrupt.
 */
void TouchKey_Config();

/**
 * @brief TouchKey_IsAnyPressed checks if any touch key is currently pressed.
 * @return TRUE if any touch key is pressed, FALSE otherwise.
 * Note: The touch key status is updated in the interrupt handler, so this
 * function should be called after the TK_READ_DONE_FLAG is set to TRUE to get
 * the latest status.
 */
bit TouchKey_IsAnyPressed();

/**
 * @brief TouchKey_GetPressedKeys returns a 16-bit bitmask representing the
 * pressed status of each touch key channel. Each bit corresponds to a touch key
 * channel, where bit 0 corresponds to TK0 and bit 15 corresponds to TK15. A bit
 * value of 1 indicates that the corresponding touch key is pressed, while a bit
 * value of 0 indicates that it is not pressed.
 */
u16 TouchKey_GetPressedKeys();

/**
 * @brief Get the raw data value of a specific touch key channel. Call after
 * TK_READ_DONE_FLAG is set to TRUE to get the latest data.
 *
 * @param channel The touch key channel number (0-15) to check.
 * @return The raw data value of the specified touch key channel.

 */
u16 TouchKey_GetRawData(u8 channel);

/**
 * @brief TouchKey_IsPressed checks if a specific touch key channel is currently
 * pressed. Call after TK_READ_DONE_FLAG is set to TRUE to get the latest
 * status.
 *
 * @param channel The touch key channel number (0-15) to check.
 * @return TRUE if the specified touch key channel is pressed, FALSE otherwise.
 */
u8 TouchKey_IsPressed(u8 channel);

#endif  // __TOUCH_KEY_H__