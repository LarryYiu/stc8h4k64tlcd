#ifndef __KEY_H__
#define __KEY_H__

#include <STC8H.h>

#include "Config.h"
#include "GPIO.h"
#include "STC8G_H_Delay.h"
#include "STC8G_H_GPIO.H"

#ifndef KEY_PORT
#define KEY_PORT P3
#endif  // KEY_PORT

#ifndef KEY_USE_BUSY_WAITING
#define KEY_USE_BUSY_WAITING FALSE
#endif  // KEY_USE_BUSY_WAITING

#ifndef KEY_NUM_KEYS
#define KEY_NUM_KEYS 4
#endif  // KEY_NUM_KEYS

#ifndef KEY_LONG_PRESS_THRESHOLD
#define KEY_LONG_PRESS_THRESHOLD 5  // 5 * 100ms = 500ms
#endif                              // KEY_LONG_PRESS_THRESHOLD

#ifndef KEY_CONTINUOUS_PRESS_THRESHOLD
#define KEY_CONTINUOUS_PRESS_THRESHOLD 3  // 2 * 100ms = 200ms
#endif                                    // KEY_CONTINUOUS_PRESS_THRESHOLD

void Key_Config();
#if (KEY_USE_BUSY_WAITING)
bool Key_Scan(u8* keyNum);
#else
// #define KEY_NUM_BIT_PER_KEY 4
// #define KEY_BITPLACE_PRESSED 3
// #define KEY_BITPLACE_LONG_PRESSED 2
// #define KEY_BITPLACE_PRESS_COUNT 1
// #define KEY_BITPLACE_PRESSING 0

/**
 * @brief Key state structure for non-busy-waiting mode. Stores the current
 * state of each key, including how long it has been pressed and how many times
 * it has been pressed.
 *
 * keyBit: The bit mask for the key's GPIO pin (1 << keyBit).
 *
 * pressDuration: How many consecutive scan intervals the key has been detected
 * as pressed.
 *
 * pressCount: The number of times the key has been pressed (short presses).
 *
 * lastReleaseDuration: How many consecutive scan intervals the key has been
 * detected as released since the last press.
 *
 * isPressing: Whether the key is currently being pressed.
 */
typedef struct
{
    u8 keyBit;
    u8 pressDuration;
    u8 pressCount;
    u8 lastReleaseDuration;
    u8 isPressing;
} Key_t;
extern Key_t xdata keys[4];

/**
 * @brief Scan the keys and update their states. Should be called periodically,
 * e.g., in a timer interrupt.
 */
void Key_Scan();

/**
 * @brief Check for key events and call the appropriate callbacks. Should be
 * called after Key_Scan has been called to update the key states.
 *
 * @param keyIndex The index of the key to check (0-based), according to the
 * order defined in keys[].
 * @param onShortPress Callback function to call when a short press is detected.
 * @param onLongPress Callback function to call when a long press is detected.
 */
void Key_Event(u8 keyIndex, void (*onShortPress)(u8 pressCount),
               void (*onLongPress)(u8 pressCount));
#endif

#endif  // __KEY_H__