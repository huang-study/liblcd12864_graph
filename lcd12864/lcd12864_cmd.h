/*
 * @Author: your name
 * @Date: 2021-02-10 16:32:51
 * @LastEditTime: 2021-02-10 16:38:50
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \test\lcd12864\lcd12864_cmd.h
 */
#ifndef __LCD12864_CMD_H
#define __LCD12864_CMD_H

#define LCD_CMD_CLC_DDRAM (0x01)
#define LCD_CMD_RES_DDRAM_ADD (0x02)

#define LCD_CMD_DDRAM_ADD_SET(add) (0x80 | (add & 0x7F))
#define LCD_CMD_CGRAM_ADD_SET(add) (0x40 | (add & 0x3F))




#endif /* __LCD12864_CMD_H */

