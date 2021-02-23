/*
 * @Author: your name
 * @Date: 2021-02-03 23:47:03
 * @LastEditTime: 2021-02-12 08:51:50
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \test\lcd12864\lcd12864.h
 */
#ifndef __LCD12864_H
#define __LCD12864_H

#include "lcd12864_port.h"

void lcd_init(void);
void lcd_clc_ddram(void);
void lcd_disp_char(uint8_t x, uint8_t y, char ch);
void lcd_disp_str(uint8_t x, uint8_t y, char *str, char num);
void lcd_disp_china(uint8_t x, uint8_t y, uint16_t ch);
void lcd_char_test(void);

#endif /* __LCD12864_H */

