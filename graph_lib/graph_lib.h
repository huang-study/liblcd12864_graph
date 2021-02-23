/*
 * @Author: your name
 * @Date: 2021-02-12 16:35:42
 * @LastEditTime: 2021-02-15 17:57:25
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \test\graph_lib\graph_lib.h
 */
#ifndef __GRAPH_LIB_H
#define __GRAPH_LIB_H

#include "stdint.h"

enum graph_pix_sta
{ 
	pix_off = 0,
	pix_on
};

// enum disp_reverse
// {
// 	graph_no_reverse = 0, // 不反显（显示为点亮，否则为不点亮）
// 	graph_reverse,		 // 反显
// };

enum graph_fill_sta
{
    graph_filling=0,
    graph_no_fill
};
 
void graph_refresh(void);
// 显存屏幕填充
void graph_fill(enum graph_pix_sta sta);
// 绘制像素点，不反显，反显，自动反显三种操作方式
void graph_pix(int32_t x, int32_t y );
// 画图部分
void graph_draw_celsius(int32_t x, int32_t y, uint32_t size);
void graph_draw_text(int32_t x, int32_t y, uint8_t *str, uint32_t cnt, uint32_t size);
// 显存画点
void ScreenDrawDot(int32_t x, int32_t y, uint32_t degree);
// 画线，暂不能使用线粗，只能用单点，需要修改
void graph_draw_line(int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint32_t degree);
// 画圆，暂不能使用线粗，只能用单点，需要修改
void graph_draw_circule(int32_t x1, int32_t y1, int32_t r, uint32_t degree);
void graph_draw_square(int32_t x1, int32_t y1, int32_t x2, int32_t y2, enum graph_fill_sta fill, uint32_t degree);
void graph_draw_squarelangth(int32_t x1, int32_t y1, int32_t length, uint32_t width, enum graph_fill_sta fill, uint32_t degree);
/********************************************
// fill_Picture
********************************************/
void graph_draw_BMP(uint32_t x, uint32_t y, uint32_t w, uint32_t h,const uint8_t *BMP);

#endif /* __GRAPH_LIB_H */
