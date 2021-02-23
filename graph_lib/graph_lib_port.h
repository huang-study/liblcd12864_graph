/*
 * @Author: your name
 * @Date: 2021-02-12 16:35:32
 * @LastEditTime: 2021-02-15 17:22:53
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \test\graph_lib\graph_lib_port.h
 */
#ifndef __GRAPH_LIB_PORT_H
#define __GRAPH_LIB_PORT_H

#include "lcd12864_graph.h"

#ifndef NULL
#define NULL ((void *)0)
#endif /* #ifndef NULL */

#define GRAPH_RESOLUTION_X LCD_RESOLUTION_X
#define GRAPH_RESOLUTION_Y LCD_RESOLUTION_Y

#define GRAPH_PIX_CLR LCD_PIX_CLR
#define GRAPH_PIX_SET LCD_PIX_SET
#define GRAPH_PIX_GET LCD_PIX_GET

int8_t graph_pix_opt(uint8_t x, uint8_t y, uint8_t opt);

#endif /* __GRAPH_LIB_PORT_H */
