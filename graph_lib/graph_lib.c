/*
 * @Author: your name
 * @Date: 2021-02-12 16:35:50
 * @LastEditTime: 2021-02-15 18:05:44
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \test\graph_lib\graph_lib.c
 */
#include "graph_lib.h"
#include "stdint.h"
#include "stddef.h"

#include "graph_lib_port.h"

#include "graph_front.h"

// 显存屏幕填充
void graph_fill(enum graph_pix_sta sta)
{
	unsigned char x, y;

	for (y = 0; y < GRAPH_RESOLUTION_Y; y++)
	{ 
		for (x = 0; x < GRAPH_RESOLUTION_X; x++)
		{
			graph_pix_opt(x, y, pix_off == sta ? GRAPH_PIX_CLR : GRAPH_PIX_SET);
		}
	}
}
// 绘制像素点，不反显，反显，自动反显三种操作方式
void graph_pix(int32_t x, int32_t y)
{ 
		graph_pix_opt(x, y, GRAPH_PIX_SET); 
}
// 画图部分
void graph_draw_celsius(int32_t x, int32_t y, uint32_t size)
{
	for(int i = 0; i < 16; i++){
		for(int j = 0; j < 8; j++){
			if(0 != (celsius_font_16[i] & ((0x01)<<j))){
				graph_pix(x+j, y+i);
			}
		}
	}
}
static void _graph_draw_ch_16(int32_t x, int32_t y, uint8_t ch)
{
	for(int i = 0; i < 16; i++){
		for(int j = 0; j < 8; j++){
			if(0 != (utf8_font_16[ch-32][i] & ((0x01)<<j))){
				graph_pix(x+j, y+i);
			}
		}
	}
}
static void _graph_draw_ch_24(int32_t x, int32_t y, uint8_t ch)
{
	
}
void graph_draw_text(int32_t x, int32_t y, uint8_t *str, uint32_t cnt, uint32_t size)
{
	if(NULL == str){
		return;
	}
	if(0 == cnt){
		return;
	}
	switch(size){
	case 16:
		for(int i = 0; i < cnt; i++){
			_graph_draw_ch_16(x+i*(16/2), y, str[i]);
		}
		break;
	case 24:
		for(int i = 0; i < cnt; i++){
			_graph_draw_ch_24(x+i*(24/2), y, str[i]);
		}
		break;
	}
}
// 显存画点
void graph_draw_dot(int32_t x, int32_t y, uint32_t degree)
{
	int32_t xCnt, yCnt;

	if (0 == degree)
		return;

	for (xCnt = 0; xCnt < (GRAPH_RESOLUTION_X > (x + degree) ? degree : (GRAPH_RESOLUTION_X - x)); xCnt++)
	{
		for (yCnt = 0; yCnt < (GRAPH_RESOLUTION_Y > (y + degree) ? degree : (GRAPH_RESOLUTION_Y - y)); yCnt++)
		{
			graph_pix(x + xCnt, y + yCnt);
		}
	}
}
// 画线，暂不能使用线粗，只能用单点，需要修改
void graph_draw_line(int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint32_t degree)
{ // https://blog.csdn.net/yuanwuwei/article/details/70182793 中点画线
	int dx, dy, e;
	dx = x2 - x1;
	dy = y2 - y1;

	if (dx >= 0)
	{
		if (dy >= 0) // dy>=0
		{
			if (dx >= dy) // 1/8 octant
			{
				e = dy - dx / 2;
				while (x1 <= x2)
				{
					graph_pix(x1, y1);
					if (e > 0)
					{
						y1 += 1;
						e -= dx;
					}
					x1 += 1;
					e += dy;
				}
			}
			else // 2/8 octant
			{
				e = dx - dy / 2;
				while (y1 <= y2)
				{
					graph_pix(x1, y1);
					if (e > 0)
					{
						x1 += 1;
						e -= dy;
					}
					y1 += 1;
					e += dx;
				}
			}
		}
		else
		{				  // dy<0
			dy = -dy;	  // dy=abs(dy)
			if (dx >= dy) // 8/8 octant
			{
				e = dy - dx / 2;
				while (x1 <= x2)
				{
					graph_pix(x1, y1);
					if (e > 0)
					{
						y1 -= 1;
						e -= dx;
					}
					x1 += 1;
					e += dy;
				}
			}
			else // 7/8 octant
			{
				e = dx - dy / 2;
				while (y1 >= y2)
				{
					graph_pix(x1, y1);
					if (e > 0)
					{
						x1 += 1;
						e -= dy;
					}
					y1 -= 1;
					e += dx;
				}
			}
		}
	}
	else //dx<0
	{
		dx = -dx;	 //dx=abs(dx)
		if (dy >= 0) // dy>=0
		{
			if (dx >= dy) // 4/8 octant
			{
				e = dy - dx / 2;
				while (x1 >= x2)
				{
					graph_pix(x1, y1);
					if (e > 0)
					{
						y1 += 1;
						e -= dx;
					}
					x1 -= 1;
					e += dy;
				}
			}
			else // 3/8 octant
			{
				e = dx - dy / 2;
				while (y1 <= y2)
				{
					graph_pix(x1, y1);
					if (e > 0)
					{
						x1 -= 1;
						e -= dy;
					}
					y1 += 1;
					e += dx;
				}
			}
		}
		else // dy<0
		{
			dy = -dy;	  // dy=abs(dy)
			if (dx >= dy) // 5/8 octant
			{
				e = dy - dx / 2;
				while (x1 >= x2)
				{
					graph_pix(x1, y1);
					if (e > 0)
					{
						y1 -= 1;
						e -= dx;
					}
					x1 -= 1;
					e += dy;
				}
			}
			else // 6/8 octant
			{
				e = dx - dy / 2;
				while (y1 >= y2)
				{
					graph_pix(x1, y1);
					if (e > 0)
					{
						x1 -= 1;
						e -= dy;
					}
					y1 -= 1;
					e += dx;
				}
			}
		}
	}
}
// 画圆，暂不能使用线粗，只能用单点，需要修改
void graph_draw_circule(int32_t x1, int32_t y1, int32_t r, uint32_t degree)
{ // https://www.cnblogs.com/iamfatotaku/p/12497354.html

	int d0, x = 0, y = r; //d0是判别式的值
						  //	_ScreenDrawCircule(x1, y1, r, degree, rever);
	d0 = 1.25 - r;		  //判别式的初始值，1.25可以改为1
		graph_pix(x1, y1 + r);
		graph_pix(x1, y1 - r);
		graph_pix(x1 + r, y1);
		graph_pix(x1 - r, y1);
	while (x < y)
	{
		if (d0 >= 0)
		{
			d0 = d0 + 2 * (x - y) + 5; //d0一定要先比x,y更新
			x += 1;					   //因为d0表达式中的x,y是上一个点
			y -= 1;
			graph_pix(x + x1, y + y1);	  //(x,y)
			graph_pix(-x + x1, y + y1);  //(-x,y)
			graph_pix(y + x1, x + y1);	  //(y,x)
			graph_pix(-y + x1, x + y1);  //(-y,x)
			graph_pix(x + x1, -y + y1);  //(x,-y)
			graph_pix(-x + x1, -y + y1); //(-x,-y)
			graph_pix(y + x1, -x + y1);  //(y,-y)
			graph_pix(-y + x1, -x + y1); //(-y,-x)
		}
		else
		{
			d0 = d0 + 2 * x + 3;
			x += 1;
			y = y;
			graph_pix(x + x1, (y + y1));	//(x,y)
			graph_pix(-x + x1, (y + y1));	//(-x,y)
			graph_pix(y + x1, (x + y1));	//(y,x)
			graph_pix(-y + x1, (x + y1));	//(-y,x)
			graph_pix(x + x1, (-y + y1));	//(x,-y)
			graph_pix(-x + x1, (-y + y1)); //(-x,-y)
			graph_pix(y + x1, (-x + y1));	//(y,-y)
			graph_pix(-y + x1, (-x + y1)); //(-y,-x)
		}
	}
}
void graph_draw_square(int32_t x1, int32_t y1, int32_t x2, int32_t y2, enum graph_fill_sta fill, uint32_t degree)
{
	uint32_t Cnt, xCnt;
	if (graph_filling == fill)
	{
		for (Cnt = 0; Cnt <= ((y2 - y1) >= 0 ? (y2 - y1) : (y1 - y2)); Cnt++)
		{
			for (xCnt = 0; xCnt <= ((x2 - x1) >= 0 ? (x2 - x1) : (x1 - x2)); xCnt++)
			{
				graph_pix(x1 + xCnt, y1 + Cnt);
			}
		}
	}
	else if (graph_no_fill == fill)
	{
		for (Cnt = 0; Cnt <= ((y2 - y1) >= 0 ? (y2 - y1) : (y1 - y2)); Cnt++)
		{
			graph_pix(x1, y1 + Cnt);
			graph_pix(x2, y1 + Cnt);
		}
		for (Cnt = 1; Cnt <= ((x2 - x1) >= 0 ? (x2 - x1) : (x1 - x2)) - 1; Cnt++)
		{
			graph_pix(x1 + Cnt, y1);
			graph_pix(x1 + Cnt, y2);
		}
	}
}
void graph_draw_squarelangth(int32_t x1, int32_t y1, int32_t length, uint32_t width, enum graph_fill_sta fill, uint32_t degree)
{
	graph_draw_square(x1, y1, x1 + length - 1, y1 + width - 1, fill, degree);
}
/********************************************
// fill_Picture
********************************************/
void graph_draw_BMP(uint32_t x, uint32_t y, uint32_t w, uint32_t h,const uint8_t *BMP)
{
	if(NULL == BMP){
		return;
	}
	for(int i = 0; i < h; i++){
		for(int j = 0; j < (w/8); j++){
			for(int k = 0; k < 8; k++){
				if(0 != (BMP[(i*(w/8)) + j] & ((0x01)<<k))){
					graph_pix(x+j*8+k, y+i);
				}
			}
		}
	}
}
