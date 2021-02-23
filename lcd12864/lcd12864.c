/*
 * @Author: your name
 * @Date: 2021-02-03 23:46:55
 * @LastEditTime: 2021-02-16 17:27:44
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \test\lcd12864\lcd12864.c
 */
#include "lcd12864.h"
#include "lcd12864_cmd.h"

void lcd_init(void)
{
    // ���ų�ʼ��
    lcd_pin_init();
    // ��ʼ���ȴ� > 40ms
    lcd_delay(50);

    // �����趨 �ȴ� > 100us
    lcd_write_byte(LCD_CMD, 0x30);
    lcd_delay(1);
    // �ٴ��趨 �ȴ� > 37us
    lcd_write_byte(LCD_CMD, 0x30);
    lcd_delay(1);
    // ��ʾ״̬����,�رչ����ʾ �ȴ� > 100us
    lcd_write_byte(LCD_CMD, 0x0C);
    lcd_delay(1);
    // ����, �ȴ� 10 ms
    lcd_write_byte(LCD_CMD, 0x01);
    lcd_delay(1);
    // ���趨
    lcd_write_byte(LCD_CMD, 0x06);
}

static int8_t _lcd_get_ddram_add(uint8_t x, uint8_t y, uint8_t *ddram_add)
{
    uint8_t add = 0;
    if (NULL == ddram_add)
    {
        return -1;
    }
    if (0x7 >= x)
    {
        add |= x;
    }
    else
    {
        return -2;
    }

    switch (y)
    {
    case 0:
        break;
    case 1:
        add |= 0x10;
        break;
    case 2:
        add |= 0x8;
        break;
    case 3:
        add |= 0x18;
        break;
    default:
        return -3;
    }

    *ddram_add = add;
    return 0;
}
void lcd_clc_ddram(void)
{
    // ����, �ȴ� 10 ms
    lcd_write_byte(LCD_CMD, 0x01);
    lcd_delay(1);
}
void lcd_disp_char(uint8_t x, uint8_t y, char ch)
{
    uint8_t add = 0;

    // �����ַ
    if (0 != _lcd_get_ddram_add(x, y, &add))
    {
        return;
    }
    // ���õ�ַ
    lcd_write_byte(LCD_CMD, LCD_CMD_DDRAM_ADD_SET(add));
    // д����ʾ����
    lcd_write_byte(LCD_DAT, ch);
    return;
}
void lcd_disp_str(uint8_t x, uint8_t y, char *str, char num)
{
    uint8_t add = 0;

    // �����ַ
    if (0 != _lcd_get_ddram_add(x, y, &add))
    {
        return;
    }
    // ���õ�ַ
    lcd_write_byte(LCD_CMD, LCD_CMD_DDRAM_ADD_SET(add));
    // д����ʾ���� 
    for(int i = 0; i < num; i++)
    {
        if (x <= 0x0F) //X����ӦС��0xF
        {
            lcd_write_byte(LCD_DAT, str[i]); 
        }
    }
    return;
}
void lcd_disp_china(uint8_t x, uint8_t y, uint16_t ch)
{
    uint8_t add = 0;

    // �����ַ
    if (0 != _lcd_get_ddram_add(x, y, &add))
    {
        return;
    }
    // ���õ�ַ
    lcd_write_byte(LCD_CMD, LCD_CMD_DDRAM_ADD_SET(add));
    // д����ʾ����
    lcd_write_byte(LCD_DAT, ch >> 8);
    lcd_write_byte(LCD_DAT, ch & 0xFF);
}
#include "string.h"
void lcd_char_test(void)
{
    lcd_disp_str(0,0,"21-2-12", strlen("21-2-12"));
    lcd_disp_china(0, 1, 'ʱ');
    lcd_disp_china(1, 1, '��');
    lcd_disp_str(3,1,"12:00", strlen("12:00"));
    lcd_disp_china(0, 2, '��');
    lcd_disp_china(1, 2, '��');
    lcd_disp_str(3,2,"35 C`", strlen("35 C`"));
    lcd_disp_china(0, 3, '��');
    lcd_disp_china(1, 3, '��');
    lcd_disp_china(4, 3, '��');
    lcd_delay(1000);
}
