#include "S3C2440.h"
#include "timer.c"
void __aebiunwind_cpp_pr0(){;}

int main(viod)
{
	int freq;
	clk_init();
	key_init();
	buzzer_init();
	freq =2000;
	buzzer_freq_set(freq);
	while(1)
	{
		if((GPFDAT&0x01)==0)
		{
			if(freq <2000)
				freq+=200;
			delay(200);
			buzzer_freq_set(freq);
		}
		if((GPFDAT&0x02)==0)
		{
			if(freq <2000)
				freq-=200;
			delay(200);
			buzzer_freq_set(freq);
		}
	}
}