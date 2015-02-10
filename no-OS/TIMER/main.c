#include "S3C2440.h"
#include "serial.h"
#define PCLK            50000000    // init.c中的clock_init函数设置PCLK为50MHz

void key_init(void)
{
	GPFCON &=0xff0;
}

void buzzer_init(void)
{
	GPBCON &= ~3;
	GPBCON |= 1;
	GPBDAT &= ~1;
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


void buzzer_freq_sets(unsigned int freq)	
{	
	GPBCON &=~3;
	GPBCON |=2;
	TCFG0 &=~0xff;
	TCFG0 |=15;
	TCFG1 &=~0xf;
	TCFG1 |=2;
	TCNTB0 =freq;//(PCLK>>7)/freq当freq为实际频率时。本程序避免了除法运算
	TCMPB0 =TCNTB0>>1;
	TCON&=~0x1f;
	TCON |=0xb;
	TCON &=~2;
}
int main(void)
{
	unsigned int freq;
	uart0_init();
	key_init();
	buzzer_init();
	putccc('a');
	freq =1000;
	buzzer_freq_sets(freq);
	while(1)
	{
		if((GPFDAT&0x01)==0)
		{
			putccc('z');
			putccc(10);
			putccc(13);
			if(freq <2000)
				freq+=10;	
			buzzer_freq_sets(freq);
		}
		if((GPFDAT&0x02)==0)
		{
			putccc('x');
			putccc(10);
			putccc(13);
			if(freq >200)
				freq-=10;
			delay(200);
			buzzer_freq_sets(freq);
		}
		
		delay(200);
	}
	return  0;
}
