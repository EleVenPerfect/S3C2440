#define	MPLLCON		(*(volatile unsigned long *)0x4c000004)
#define	CLKDIVN		(*(volatile unsigned long *)0x4c000014)
#define	LOCKTIME	(*(volatile unsigned long *)0x4c000000)
#define S3C2440_MPLL_200MHZ     ((0x5c<<12)|(0x01<<4)|(0x02))
#define S3C2440_MPLL_300MHZ     ((0x44<<12)|(0x01<<4)|(0x01))
#define S3C2440_MPLL_400MHZ     ((0x7f<<12)|(0x02<<4)|(0x01))
#define S3C2440_VLOCKDIVN_124    0x03
#define S3C2440_VLOCKDIVN_148    0x04

void clock_init(void)
{
    // LOCKTIME = 0x00ffffff;   // 使用默认值即可
    CLKDIVN  = S3C2440_VLOCKDIVN_124;   // FCLK:HCLK:PCLK=1:2:4, HDIVN=01,PDIVN=1==0x03
										// FCLK:HCLK:PCLK=1:4:8, HDIVN=10,PDIVN=1==0x04

    /* 如果HDIVN非0，CPU的总线模式应该从“fast bus mode”变为“asynchronous bus mode” */
__asm__(
    "mrc    p15, 0, r1, c1, c0, 0\n"        /* 读出控制寄存器 */ 
    "orr    r1, r1, #0xc0000000\n"          /* 设置为“asynchronous bus mode” */
    "mcr    p15, 0, r1, c1, c0, 0\n"        /* 写入控制寄存器 */
    );


    MPLLCON = S3C2440_MPLL_200MHZ;  /* 现在，FCLK=200MHz,HCLK=100MHz,PCLK=50MHz */       
}
