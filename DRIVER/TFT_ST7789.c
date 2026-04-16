#include "TFT_ST7789.h"

#include "TFT_DisplayDat.h"
#define LCD_W 320
#define LCD_H 240

void LCD_Writ_Bus(u8 dat)
{
    SPDAT = dat;
    B_SPI_Busy = 1;
    while (B_SPI_Busy);
}

void LCD_Write8(u8 dat) { LCD_Writ_Bus(dat); }

void LCD_Write16(u16 dat)
{
    LCD_Writ_Bus(dat >> 8);
    LCD_Writ_Bus(dat);
}

void LCD_WriteCommand(u8 dat)
{
    LCD_DC = 0;
    LCD_Writ_Bus(dat);
    LCD_DC = 1;
}

void LCD_Address_Set(u16 x1, u16 y1, u16 x2, u16 y2)
{
    LCD_WriteCommand(0x2a);  // 列地址设置
    LCD_Write16(x1);
    LCD_Write16(x2);
    LCD_WriteCommand(0x2b);  // 行地址设置
    LCD_Write16(y1);
    LCD_Write16(y2);
    LCD_WriteCommand(0x2c);  // 储存器写
}

void LCD_Fill(u16 xsta, u16 ysta, u16 xend, u16 yend, u16 color)
{
    u16 i, j;
    LCD_Address_Set(xsta, ysta, xend - 1, yend - 1);  // 设置显示范围
    for (i = ysta; i < yend; i++)
    {
        for (j = xsta; j < xend; j++)
        {
            LCD_Write16(color);
        }
    }
}

void LCD_DrawPoint(u16 x, u16 y, u16 color)
{
    LCD_Address_Set(x, y, x, y);  // 设置光标位置
    LCD_Write16(color);
}

void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2, u16 color)
{
    u16 t;
    int xerr = 0, yerr = 0, delta_x, delta_y, distance;
    int incx, incy, uRow, uCol;
    delta_x = x2 - x1;  // 计算坐标增量
    delta_y = y2 - y1;
    uRow = x1;  // 画线起点坐标
    uCol = y1;
    if (delta_x > 0)
    {
        incx = 1;  // 设置单步方向
    }
    else if (delta_x == 0)
    {
        incx = 0;  // 垂直线
    }
    else
    {
        incx = -1;
        delta_x = -delta_x;
    }
    if (delta_y > 0)
    {
        incy = 1;
    }
    else if (delta_y == 0)
    {
        incy = 0;  // 水平线
    }
    else
    {
        incy = -1;
        delta_y = -delta_y;
    }
    if (delta_x > delta_y)
    {
        distance = delta_x;  // 选取基本增量坐标轴
    }
    else
    {
        distance = delta_y;
    }
    for (t = 0; t < distance + 1; t++)
    {
        LCD_DrawPoint(uRow, uCol, color);  // 画点
        xerr += delta_x;
        yerr += delta_y;
        if (xerr > distance)
        {
            xerr -= distance;
            uRow += incx;
        }
        if (yerr > distance)
        {
            yerr -= distance;
            uCol += incy;
        }
    }
}

void LCD_ShowChar(u16 x, u16 y, u8 num, u16 fc, u16 bc, u8 sizey, u8 mode)
{
    u8 temp, sizex, t, m = 0;
    u16 i, TypefaceNum;  // 一个字符所占字节大小
    u16 x0 = x;
    sizex = sizey / 2;
    TypefaceNum = (sizex / 8 + ((sizex % 8) ? 1 : 0)) * sizey;
    num = num - ' ';                                      // 得到偏移后的值
    LCD_Address_Set(x, y, x + sizex - 1, y + sizey - 1);  // 设置光标位置
    for (i = 0; i < TypefaceNum; i++)
    {
        if (sizey == 16)
        {
            temp = ascii_1608[num][i];  // 调用8x16字体
        }
        else if (sizey == 24)
        {
            temp = ascii_2412[num][i];  // 调用12x24字体
        }
        else
        {
            return;
        }
        for (t = 0; t < 8; t++)
        {
            if (!mode)  // 非叠加模式
            {
                if (temp & (0x01 << t))
                {
                    LCD_Write16(fc);
                }
                else
                {
                    LCD_Write16(bc);
                }
                m++;
                if (m % sizex == 0)
                {
                    m = 0;
                    break;
                }
            }
            else  // 叠加模式
            {
                if (temp & (0x01 << t))
                {
                    LCD_DrawPoint(x, y, fc);  // 画一个点
                }
                x++;
                if ((x - x0) == sizex)
                {
                    x = x0;
                    y++;
                    break;
                }
            }
        }
    }
}

void LCD_ShowString(u16 x, u16 y, const u8* p, u16 fc, u16 bc, u8 sizey,
                    u8 mode)
{
    while (*p != '\0')
    {
        LCD_ShowChar(x, y, *p, fc, bc, sizey, mode);
        x += sizey / 2;
        p++;
    }
}

u32 mypow(u8 m, u8 n)
{
    u32 result = 1;
    while (n--)
    {
        result *= m;
    }
    return result;
}

void LCD_ShowIntNum(u16 x, u16 y, u16 num, u8 len, u16 fc, u16 bc, u8 sizey)
{
    u8 t, temp;
    u8 enshow = 0;
    u8 sizex = sizey / 2;
    for (t = 0; t < len; t++)
    {
        temp = (num / mypow(10, len - t - 1)) % 10;
        if (enshow == 0 && t < (len - 1))
        {
            if (temp == 0)
            {
                LCD_ShowChar(x + t * sizex, y, ' ', fc, bc, sizey, 0);
                continue;
            }
            else
            {
                enshow = 1;
            }
        }
        LCD_ShowChar(x + t * sizex, y, temp + 48, fc, bc, sizey, 0);
    }
}
void LCD_Fill_Black(u16 xsta, u16 ysta, u16 xend, u16 yend)
{
    u16 i, j;
    LCD_Address_Set(xsta, ysta, xend - 1, yend - 1);  // 设置显示范围
    for (i = ysta; i < yend; i++)
    {
        for (j = xsta; j < xend; j++)
        {
            // 一个数据2个字节
            LCD_Writ_Bus(0x00);
            LCD_Writ_Bus(0x00);
        }
    }
}

void LCD_Config()
{
    // GPIO_Config(GPIO_P7, GPIO_Pin_0, GPIO_PullUp);  // RST
    // GPIO_Config(GPIO_P4, GPIO_Pin_3, GPIO_PullUp);  // SCLK
    // GPIO_Config(GPIO_P4, GPIO_Pin_0, GPIO_PullUp);  // MOSI
    // GPIO_Config(GPIO_P6, GPIO_Pin_0, GPIO_PullUp);  // DC
    // P7_MODE_IO_PUT(GPIO_Pin_0);
    // P4_MODE_IO_PUT(GPIO_Pin_3);
    // P4_MODE_IO_PUT(GPIO_Pin_0);
    // P6_MODE_IO_PUT(GPIO_Pin_0);
    SPI_Config_Common();
}

void LCD_Init()
{
    LCD_RST = 0;  // reset
    delay_ms(200);
    LCD_RST = 1;
    delay_ms(200);

    LCD_WriteCommand(0x11);  // Sleep out
    delay_ms(120);           // Delay 120ms
    LCD_WriteCommand(0x36);

    LCD_Write8(0xA0);

    LCD_WriteCommand(0x3A);
    LCD_Write8(0x05);

    LCD_WriteCommand(0xB2);
    LCD_Write8(0x0C);
    LCD_Write8(0x0C);
    LCD_Write8(0x00);
    LCD_Write8(0x33);
    LCD_Write8(0x33);

    LCD_WriteCommand(0xB7);
    LCD_Write8(0x35);

    LCD_WriteCommand(0xBB);
    LCD_Write8(0x32);  // Vcom=1.35V

    LCD_WriteCommand(0xC2);
    LCD_Write8(0x01);

    LCD_WriteCommand(0xC3);
    LCD_Write8(0x15);  // GVDD=4.8V  gamma

    LCD_WriteCommand(0xC4);
    LCD_Write8(0x20);  // VDV, 0x20:0v

    LCD_WriteCommand(0xC6);
    LCD_Write8(0x0F);  // 0x0F:60Hz

    LCD_WriteCommand(0xD0);
    LCD_Write8(0xA4);
    LCD_Write8(0xA1);

    LCD_WriteCommand(0xE0);
    LCD_Write8(0xD0);
    LCD_Write8(0x08);
    LCD_Write8(0x0E);
    LCD_Write8(0x09);
    LCD_Write8(0x09);
    LCD_Write8(0x05);
    LCD_Write8(0x31);
    LCD_Write8(0x33);
    LCD_Write8(0x48);
    LCD_Write8(0x17);
    LCD_Write8(0x14);
    LCD_Write8(0x15);
    LCD_Write8(0x31);
    LCD_Write8(0x34);

    LCD_WriteCommand(0xE1);
    LCD_Write8(0xD0);
    LCD_Write8(0x08);
    LCD_Write8(0x0E);
    LCD_Write8(0x09);
    LCD_Write8(0x09);
    LCD_Write8(0x15);
    LCD_Write8(0x31);
    LCD_Write8(0x33);
    LCD_Write8(0x48);
    LCD_Write8(0x17);
    LCD_Write8(0x14);
    LCD_Write8(0x15);
    LCD_Write8(0x31);
    LCD_Write8(0x34);
    LCD_WriteCommand(0x21);

    LCD_WriteCommand(0x29);
}

void Page_Content_1()
{
    LCD_DrawLine(0, 30, 320, 30, WHITE);  // 分割线
    // LCD_Fill(0,0,100,66,RED);//test

    LCD_ShowString(X_Position + 4, Y_Position - 32, " T0 ", RED, WHITE, 24, 0);
    LCD_ShowString(X_Position + 4, Y_Position, " T1 ", RED, WHITE, 24, 0);
    LCD_ShowString(X_Position + 4, Y_Position + 32, " T2 ", RED, WHITE, 24, 0);
    LCD_ShowString(X_Position + 4, Y_Position + 32 * 2, " T3 ", RED, WHITE, 24,
                   0);
    LCD_ShowString(X_Position + 4, Y_Position + 32 * 3, " T4 ", RED, WHITE, 24,
                   0);

    LCD_ShowString(X_Position + 148 + 18, Y_Position - 32, "10ms", RED, WHITE,
                   24, 0);
    LCD_ShowString(X_Position + 148 + 18, Y_Position, "10ms", RED, WHITE, 24,
                   0);
    LCD_ShowString(X_Position + 148 + 18, Y_Position + 32, " 1s ", RED, WHITE,
                   24, 0);
    LCD_ShowString(X_Position + 148 + 18, Y_Position + 32 * 2, " 2s ", RED,
                   WHITE, 24, 0);
    LCD_ShowString(X_Position + 148 + 18, Y_Position + 32 * 3, " 4s ", RED,
                   WHITE, 24, 0);
    LCD_DrawLine(X_Position, Y_Position + 32 * 3 + 24 + 8, X_Position + 320,
                 Y_Position + 32 * 3 + 24 + 8, WHITE);  // 分割线
}