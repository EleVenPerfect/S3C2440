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
    // LOCKTIME = 0x00ffffff;   // ʹ��Ĭ��ֵ����
    CLKDIVN  = S3C2440_VLOCKDIVN_124;   // FCLK:HCLK:PCLK=1:2:4, HDIVN=01,PDIVN=1==0x03
										// FCLK:HCLK:PCLK=1:4:8, HDIVN=10,PDIVN=1==0x04

    /* ���HDIVN��0��CPU������ģʽӦ�ôӡ�fast bus mode����Ϊ��asynchronous bus mode�� */
__asm__(
    "mrc    p15, 0, r1, c1, c0, 0\n"        /* �������ƼĴ��� */ 
    "orr    r1, r1, #0xc0000000\n"          /* ����Ϊ��asynchronous bus mode�� */
    "mcr    p15, 0, r1, c1, c0, 0\n"        /* д����ƼĴ��� */
    );


    MPLLCON = S3C2440_MPLL_200MHZ;  /* ���ڣ�FCLK=200MHz,HCLK=100MHz,PCLK=50MHz */       
}
