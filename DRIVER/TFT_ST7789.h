#ifndef __TFT_ST7789_H__
#define __TFT_ST7789_H__

#include <STC8H.h>

#include "Config.h"
#include "GPIO.h"
#include "SPI.h"
#include "STC8G_H_Delay.h"
#include "STC8G_H_GPIO.h"
#include "STC8G_H_SPI.h"

#define X_Position 0
#define Y_Position 66

sbit LCD_RST = P7 ^ 0;  // RST
sbit LCD_SCL = P4 ^ 3;  // SCLK
sbit LCD_SDA = P4 ^ 0;  // MOSI
sbit LCD_DC = P6 ^ 0;   // DC

void LCD_Writ_Bus(u8 dat);      // 模拟SPI时序
void LCD_Write8(u8 dat);        // 写入一个字节
void LCD_Write16(u16 dat);      // 写入两个字节
void LCD_WriteCommand(u8 dat);  // 写入一个指令

void LCD_Address_Set(u16 x1, u16 y1, u16 x2, u16 y2);  // 设置坐标函数
void LCD_Fill(u16 xsta, u16 ysta, u16 xend, u16 yend,
              u16 color);                     // 指定区域填充颜色
void LCD_DrawPoint(u16 x, u16 y, u16 color);  // 在指定位置画一个点
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2,
                  u16 color);  // 在指定位置画一条线

void LCD_ShowChar(u16 x, u16 y, u8 num, u16 fc, u16 bc, u8 sizey,
                  u8 mode);  // 显示一个字符
void LCD_ShowString(u16 x, u16 y, const u8* p, u16 fc, u16 bc, u8 sizey,
                    u8 mode);  // 显示字符串
void LCD_ShowIntNum(u16 x, u16 y, u16 num, u8 len, u16 fc, u16 bc,
                    u8 sizey);  // 显示整数变量
void LCD_Fill_Black(u16 xsta, u16 ysta, u16 xend,
                    u16 yend);  // 全屏黑屏初始化显示，高刷新率

void LCD_Config();      // LCD引脚配置函数
void LCD_Init();        // LCD初始化
void Page_Content_1();  // 固定页面_1，显示一些固定不变的内容
#endif                  // __TFT_ST7789_H__