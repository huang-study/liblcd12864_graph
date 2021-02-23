/*
 * @Author: your name
 * @Date: 2021-02-12 10:34:30
 * @LastEditTime: 2021-02-12 16:16:20
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \test\lcd12864\lcd12864_graph.c
 */
#include "lcd12864_graph.h"

#include "lcd12864.h"
#include "lcd12864_cmd.h"

char lcd_video_memory[LCD_RESOLUTION_Y][LCD_RESOLUTION_X / 8] = {0};

static uint8_t _change_byte_order(uint8_t val)
{
    uint8_t ret = 0;

    for(int i = 0; i < 8; i++){
        if(val & (0x01 << i)){
            ret |= (0x80 >> i);
        } 
    }
    return ret;
}

int8_t lcd_pix(uint8_t x, uint8_t y, uint8_t opt)
{
    int8_t ret = 0;
    if (LCD_RESOLUTION_X <= x)
    {
        return -1;
    }
    if (LCD_RESOLUTION_Y <= y)
    {
        return -2;
    }
    switch (opt)
    {
    case LCD_PIX_CLR:
        lcd_video_memory[y][x / 8] &= (~(0x01 << (x % 8)));
        ret = 0;
        break;
    case LCD_PIX_SET:
        lcd_video_memory[y][x / 8] |= (0x01 << (x % 8));
        ret = 0;
        break;
    case LCD_PIX_GET:
        ret = (lcd_video_memory[y][x / 8] & (0x01 << (x % 8)) == 0 ? 0 : 1);
        break;
    default:
        return -3;
    }
    return ret;
}
void lcd_refresh(void)
{ 
    unsigned char x, y;
    unsigned int tmp = 0;
    
    lcd_write_byte(LCD_CMD, 0x36);

    for (y = 0; y < 32; y++)
    { //32行
        lcd_write_byte(LCD_CMD, (0x80 + y)); /* 写入列地址 */
        lcd_write_byte(LCD_CMD, (0x80)); /* 写入行地址 */
        for (x = 0; x < 32; x++)
            //lcd_write_byte(LCD_DAT, lcd_video_memory[y+((x/16)*32)][x%16]); /* 写入数据 */
            lcd_write_byte(LCD_DAT, _change_byte_order(lcd_video_memory[y+((x/16)*32)][x%16])); /* 写入数据 */
        tmp += 16;
    }

    lcd_write_byte(LCD_CMD, 0x36); //扩充功能设定 
}
