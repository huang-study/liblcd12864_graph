/*
 * @Author: your name
 * @Date: 2021-02-12 10:34:45
 * @LastEditTime: 2021-02-12 11:27:55
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \test\lcd12864\lcd12864_graph.h
 */
#ifndef __LCD12864_GRAPH_H
#define __LCD12864_GRAPH_H

#include "stdint.h"

/**
 * @note screen resolution
 */
#define LCD_RESOLUTION_X (128)
#define LCD_RESOLUTION_Y (64)

/**
 * @note screen pix operat option
 */
#define LCD_PIX_CLR (0)
#define LCD_PIX_SET (1)
#define LCD_PIX_GET (2)

/**
 * @param   x pix coord x
 *          y pix coord y
 *          opt pix operat
 *              #define LCD_PIX_CLR (0) clear pix 
 *              #define LCD_PIX_SET (1) set pix
 *              #define LCD_PIX_GET (2) get pix sta
 * @return pix state or operat resolve
 * @note if pix is no extant or opt err, then fucntion will return -1
 *          coord begin with 0(no mater x or y)
 */
int8_t lcd_pix(uint8_t x, uint8_t y, uint8_t opt);
/** 
 * @note refresh video memory to lcd model
 */
void lcd_refresh(void);

#endif /* __LCD12864_GRAPH_H */



