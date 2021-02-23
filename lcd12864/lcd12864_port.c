/*
 * @Author: your name
 * @Date: 2021-02-03 23:11:40
 * @LastEditTime: 2021-02-16 17:27:51
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \test\lcd12864\lcd12864_port.c
 */
#include "./lcd12864_port.h"
#include "main.h" 

//#define LCD_USE_DATA_BUS
#define LCD_USE_SERIAL_BUS

#define LCD_GPIO_SET GPIO_PIN_SET
#define LCD_GPIO_RESET GPIO_PIN_RESET

#ifdef LCD_USE_DATA_BUS
#define LCD_RS_SET(sta) HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, (sta))
#define LCD_RW_SET(sta) HAL_GPIO_WritePin(LCD_RW_GPIO_Port, LCD_RW_Pin, (sta))
#define LCD_E_SET(sta)  HAL_GPIO_WritePin(LCD_E_GPIO_Port, LCD_E_Pin, (sta))
#endif /* #ifdef LCD_USE_DATA_BUS */

#ifdef LCD_USE_SERIAL_BUS

#define LCD_CS_SET(sta) HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, (sta))
#define LCD_SID_SET(sta) HAL_GPIO_WritePin(LCD_RW_GPIO_Port, LCD_RW_Pin, (sta))
#define LCD_SID_GET (GPIO_PIN_RESET == HAL_GPIO_ReadPin(LCD_RW_GPIO_Port, LCD_RW_Pin) ? 0 : 1)
#define LCD_SCK_SET(sta)  HAL_GPIO_WritePin(LCD_E_GPIO_Port, LCD_E_Pin, (sta))
#endif /* #ifdef LCD_USE_SERIAL_BUS */

void lcd_delay(uint32_t t)
{
#if 0
    HAL_Delay(t);
#else 
    uint32_t Delay = t * 168/4;
    do
    {
        __NOP();
    }
    while (Delay --);
#endif
}

#ifdef LCD_USE_DATA_BUS
void lcd_pin_init(void)
{
    HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LCD_PSB_GPIO_Port, LCD_PSB_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LCD_E_GPIO_Port, LCD_E_Pin, GPIO_PIN_RESET);
}
#endif /* #ifdef LCD_USE_DATA_BUS */

#ifdef LCD_USE_SERIAL_BUS
void lcd_pin_init(void)
{
    HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LCD_PSB_GPIO_Port, LCD_PSB_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LCD_E_GPIO_Port, LCD_E_Pin, GPIO_PIN_RESET);
}
#endif /* #ifdef LCD_USE_SERIAL_BUS */

#ifdef LCD_USE_DATA_BUS
void lcd_db_write(uint8_t w)
{
    HAL_GPIO_WritePin(LCD_D0_GPIO_Port, LCD_D0_Pin, (w&(0x01<<0)) == 0 ? GPIO_PIN_RESET : GPIO_PIN_SET);
    HAL_GPIO_WritePin(LCD_D1_GPIO_Port, LCD_D1_Pin, (w&(0x01<<1)) == 0 ? GPIO_PIN_RESET : GPIO_PIN_SET);
    HAL_GPIO_WritePin(LCD_D2_GPIO_Port, LCD_D2_Pin, (w&(0x01<<2)) == 0 ? GPIO_PIN_RESET : GPIO_PIN_SET);
    HAL_GPIO_WritePin(LCD_D3_GPIO_Port, LCD_D3_Pin, (w&(0x01<<3)) == 0 ? GPIO_PIN_RESET : GPIO_PIN_SET);
    HAL_GPIO_WritePin(LCD_D4_GPIO_Port, LCD_D4_Pin, (w&(0x01<<4)) == 0 ? GPIO_PIN_RESET : GPIO_PIN_SET);
    HAL_GPIO_WritePin(LCD_D5_GPIO_Port, LCD_D5_Pin, (w&(0x01<<5)) == 0 ? GPIO_PIN_RESET : GPIO_PIN_SET);
    HAL_GPIO_WritePin(LCD_D6_GPIO_Port, LCD_D6_Pin, (w&(0x01<<6)) == 0 ? GPIO_PIN_RESET : GPIO_PIN_SET);
    HAL_GPIO_WritePin(LCD_D7_GPIO_Port, LCD_D7_Pin, (w&(0x01<<7)) == 0 ? GPIO_PIN_RESET : GPIO_PIN_SET);
}
uint8_t lcd_db_read(void)
{
    uint8_t ret = 0;
    ret |= (GPIO_PIN_SET == HAL_GPIO_ReadPin(LCD_D0_GPIO_Port, LCD_D0_Pin) ? (0x01 << 0) : 0x00);
    ret |= (GPIO_PIN_SET == HAL_GPIO_ReadPin(LCD_D1_GPIO_Port, LCD_D1_Pin) ? (0x01 << 1) : 0x00);
    ret |= (GPIO_PIN_SET == HAL_GPIO_ReadPin(LCD_D2_GPIO_Port, LCD_D2_Pin) ? (0x01 << 2) : 0x00);
    ret |= (GPIO_PIN_SET == HAL_GPIO_ReadPin(LCD_D3_GPIO_Port, LCD_D3_Pin) ? (0x01 << 3) : 0x00);
    ret |= (GPIO_PIN_SET == HAL_GPIO_ReadPin(LCD_D4_GPIO_Port, LCD_D4_Pin) ? (0x01 << 4) : 0x00);
    ret |= (GPIO_PIN_SET == HAL_GPIO_ReadPin(LCD_D5_GPIO_Port, LCD_D5_Pin) ? (0x01 << 5) : 0x00);
    ret |= (GPIO_PIN_SET == HAL_GPIO_ReadPin(LCD_D6_GPIO_Port, LCD_D6_Pin) ? (0x01 << 6) : 0x00);
    ret |= (GPIO_PIN_SET == HAL_GPIO_ReadPin(LCD_D7_GPIO_Port, LCD_D7_Pin) ? (0x01 << 7) : 0x00);
    return ret;
}
#endif /* #ifdef LCD_USE_DATA_BUS */

#ifdef LCD_USE_SERIAL_BUS
void lcd_data_write(uint8_t w)
{ 
    for(int i = 0; i < 8; i++){
        LCD_SCK_SET(LCD_GPIO_RESET);
        if(0 != (((0x80)>>i) & w)){
            LCD_SID_SET(LCD_GPIO_SET);
        }else {
            LCD_SID_SET(LCD_GPIO_RESET);
        }
        lcd_delay(5);
        LCD_SCK_SET(LCD_GPIO_SET);
        lcd_delay(5);
    }
    LCD_SCK_SET(LCD_GPIO_RESET);
}
uint8_t lcd_data_read(void)
{
    uint8_t ret = 0;
    
    LCD_SCK_SET(LCD_GPIO_RESET);
    lcd_delay(200);
    for(int i = 0; i < 8; i++){
        LCD_SCK_SET(LCD_GPIO_SET);
        lcd_delay(200);
        if(0 != LCD_SID_GET){
            ret |= ((0x80)>>i); 
        }
        LCD_SCK_SET(LCD_GPIO_RESET);
        lcd_delay(200);
    } 
    return ret;
}
#endif /* #ifdef LCD_USE_SERIAL_BUS */

#ifdef LCD_USE_DATA_BUS
void lcd_write_byte(uint8_t rs, uint8_t cont)
{
    LCD_RS_SET(rs == LCD_CMD ? LCD_GPIO_RESET : LCD_GPIO_SET);
    LCD_RW_SET(LCD_GPIO_RESET);
    lcd_delay(200);
    LCD_E_SET(LCD_GPIO_SET);
    lcd_db_write(cont);
    lcd_delay(200);
    LCD_E_SET(LCD_GPIO_RESET);
    lcd_delay(200);
}
uint8_t lcd_read_byte(uint8_t rs)
{
    uint8_t ret = 0;
    LCD_RS_SET(rs == LCD_CMD ? LCD_GPIO_RESET : LCD_GPIO_SET);
    LCD_RW_SET(LCD_GPIO_SET);
    lcd_delay(200);
    LCD_E_SET(LCD_GPIO_SET);
    lcd_db_write(0xFF); // 电平拉高，等待阅读
    lcd_delay(200);
    ret = lcd_db_read();
    LCD_E_SET(LCD_GPIO_RESET);
    lcd_delay(200);
    return ret;
}
#endif /* #ifdef LCD_USE_DATA_BUS */

#ifdef LCD_USE_SERIAL_BUS
void lcd_write_byte(uint8_t rs, uint8_t cont)
{
    lcd_data_write(0xF8 | (rs == LCD_CMD ? 0 : 0x02));
    lcd_data_write(cont & 0xF0);
    lcd_data_write((cont & 0xF)<<4);
}
uint8_t lcd_read_byte(uint8_t rs)
{
    uint8_t ret = 0;
    lcd_data_write(0xF8 | (0x04) | (rs == LCD_CMD ? 0 : 0x02));
    ret = (lcd_data_read() & 0xF0);
    ret |= ((lcd_data_read() & 0xF0) >> 4);
    return ret;
}
#endif /* #ifdef LCD_USE_SERIAL_BUS */


