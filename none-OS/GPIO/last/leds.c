#include "S3C2440.h"	//非官方头文件，仅对当前程序有效

#define	GPB5_out	(1<<(5*2))
#define	GPB6_out	(1<<(6*2))
#define	GPB7_out	(1<<(7*2))
#define	GPB8_out	(1<<(8*2))
						//设置GPIO

int atime(void)			//程序入口
{
	unsigned long i = 0;
	GPBCON = 0X0;
	GPBUP  = 0X0;

	GPBCON = GPB5_out | GPB6_out | GPB7_out | GPB8_out;

	while(1){
		i =GPFDAT;
		
		if( i&(1<<0) )
			GPBDAT |=(1<<5);
		else
			GPBDAT &=~(1<<5);

		if( i&(1<<1) )
			GPBDAT |=(1<<6);
		else
			GPBDAT &=~(1<<6);

		if( i&(1<<2) )
			GPBDAT |=(1<<7);
		else
			GPBDAT &=~(1<<7);

		if( i&(1<<4) )
			GPBDAT |=(1<<8);
		else
			GPBDAT &=~(1<<8);

	}

	return 0;
}
