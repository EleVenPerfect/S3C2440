/*
 * FILE: lcddrv.h
 * ����LCD����������ɫ��ȵĵײ㺯���ӿ�
 */

#ifndef __LCDDRV_H__
#define __LCDDRV_H__

#include "types.h"
void init_port(void);
void Tft_Lcd_Init(void);
void Lcd_PowerEnable(int invpwren, int pwren);


#endif /*__LCDDRV_H__*/
