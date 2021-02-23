/*
 * @Author: your name
 * @Date: 2021-02-12 16:35:24
 * @LastEditTime: 2021-02-12 17:12:32
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \test\graph_lib\graph_lib_port.c
 */
#include "graph_lib_port.h"

 
int8_t graph_pix_opt(uint8_t x, uint8_t y, uint8_t opt)
{
    return lcd_pix(x, y, opt);
}

void graph_refresh(void)
{
    lcd_refresh();
}
