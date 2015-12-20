//#include <stdio.h>
#include "s3c24xx.h"
#include "lcddrv.h"
#define PCLK            50000000    // init.c�е�clock_init��������PCLKΪ50MHz

void ClearScr(long color)
{   
    TPAL = (1<<24)|((color & 0xffffff));
}


void delay(int time)
{
	unsigned int val =(PCLK>>3)/1000-1;
	TCFG0 &=~(0xff<<8);
	TCFG0 |= 3<<8;
	TCFG1 &=~(0xf<<12);
	TCFG1 |= 0<<12;
	TCNTB3 =val;
	TCMPB3 =val>>1;

	TCON &=~(0xf<<16);
	TCON |=(0xb<<16);
	TCON &=~(2<<16);
	while(time--){
	while(TCNTO3>=val>>1);
	while(TCNTO3<val>>1);
	};	
}


int main()
{  
    unsigned int i =0xff;
	init_port();
	Tft_Lcd_Init(); 					 // ��ʼ��LCD������
	Lcd_PowerEnable(0, 1);               // ����LCD_PWREN��Ч�������ڴ�LCD�ĵ�Դ
	LCDCON1 |= 1;						 // ʹ��LCD����������ź�
	
	while(1)
    {
		i++;
		ClearScr(i); 
		delay(5);
	}
    return 0;
}
