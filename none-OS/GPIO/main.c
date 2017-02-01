#include "S3C2440.h"
void __aeabi_uidiv(){;}


#define	GPB5_out	(1<<(5*2))
#define	GPB6_out	(1<<(6*2))
#define	GPB7_out	(1<<(7*2))
#define	GPB8_out	(1<<(8*2))

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

int main(void)
{
	unsigned char i;
	//GPFCON = 0X0;
	//GPFUP  = 0X0;
	
	GPBCON = GPB5_out | GPB6_out | GPB7_out | GPB8_out;

	while(1)
	{
		i++;
		
		if( i%2==1 )
			GPBDAT |=(1<<5);
		else
			GPBDAT &=~(1<<5);

		if( i%2==1 )
			GPBDAT |=(1<<6);
		else
			GPBDAT &=~(1<<6);

		if( i%2==1 )
			GPBDAT |=(1<<7);
		else
			GPBDAT &=~(1<<7);

		if( i%2==1 )
			GPBDAT |=(1<<8);
		else
			GPBDAT &=~(1<<8);
		delay(500);

	}
}
