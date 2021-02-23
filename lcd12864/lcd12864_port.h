/*
 * @Author: your name
 * @Date: 2021-02-03 23:11:32
 * @LastEditTime: 2021-02-16 16:48:07
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \test\lcd12864\lcd12864_port.h
 */
#ifndef __LCD12864_PORT_H
#define __LCD12864_PORT_H

#include <stm32f4xx_hal.h>

#define LCD_CMD (0x00)
#define LCD_DAT (0x01)

void lcd_delay(uint32_t t);

void lcd_pin_init(void);

void lcd_write_byte(uint8_t rs, uint8_t cont);
uint8_t lcd_read_byte(uint8_t rs);



#endif /* __LCD12864_PORT_H */
