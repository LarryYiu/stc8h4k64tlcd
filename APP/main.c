#include <stc8h.h>

#include "74hc595.h"
#include "Config.h"
#include "DigitalTube.h"
#include "Key.h"

void main()
{
    u8 xdata dat[8];
    float xdata num = 617.27878;
    u8 dp = 3;
    u8 len = DT_ProcessFloat(num, dat, &dp);
    u8 keyNum = 0;
    DT_Init();
    Key_Init();
    while (1)
    {
        DT_DisplayMulti(dat, len, dp, TRUE);
        if (Key_ScanBusy(&keyNum))
        {
            if (keyNum == 1)
            {
                num += 1.0;
            }
            else if (keyNum == 2)
            {
                num -= 1.0;
            }
            else if (keyNum == 3)
            {
                num *= 2.0;
            }
            else if (keyNum == 4)
            {
                num /= 2.0;
            }
            len = DT_ProcessFloat(num, dat, &dp);
        }
    }
}