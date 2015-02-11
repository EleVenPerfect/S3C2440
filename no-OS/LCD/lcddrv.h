/*
 * FILE: lcddrv.h
 * 操作LCD控制器、调色板等的底层函数接口
 */

#ifndef __LCDDRV_H__
#define __LCDDRV_H__

#include "types.h"
void init_port(void);
void Tft_Lcd_Init(void);
void Lcd_PowerEnable(int invpwren, int pwren);


#endif /*__LCDDRV_H__*/
