/*
 * FILE: lcddrv.c
 * �ṩ����LCD����������ɫ��ȵĵײ㺯��
 */
#ifndef _LCDDRV_H_
#define _LCDDRV_H_
#include "s3c24xx.h"
#include "lcddrv.h"
#include "types.h"



#define GPB0_tout0  (2<<(0*2))
#define GPB0_out    (1<<(0*2))
#define GPB1_out    (1<<(1*2))

#define GPB0_MSK    (3<<(0*2))
#define GPB1_MSK    (3<<(1*2))

/******/
#define MVAL		(13)
#define MVAL_USED 	(0)			//0=each frame   1=rate by MVAL
#define INVVDEN		(1)			//0=normal       1=inverted
#define BSWP		(0)			//Byte swap control
#define HWSWP		(1)			//Half word swap control
#define PNRMODE		(3)			// ����ΪTFT��
#define BPPMODE		(12)			// ����Ϊ16bppģʽ

//TFT_SIZE
#define LCD_XSIZE_TFT 	(480)	
#define LCD_YSIZE_TFT 	(272)

#define SCR_XSIZE_TFT 	(480)
#define SCR_YSIZE_TFT 	(272)

//Timing parameter for 4.3' LCD
#define VBPD 		(2)			//��ֱͬ���źŵĺ��
#define VFPD 		(4)			//��ֱͬ���źŵ�ǰ��
#define VSPW 		(8)			//��ֱͬ���źŵ�����

#define HBPD 		(10)			//ˮƽͬ���źŵĺ��
#define HFPD 		(19)			//ˮƽͬ���źŵ�ǰ��
#define HSPW 		(30)			//ˮƽͬ���źŵ�����


#define CLKVAL_TFT 	(4) 			//�ṩtftʱ��10MHz
#define HOZVAL_TFT	(LCD_XSIZE_TFT-1)
#define LINEVAL_TFT	(LCD_YSIZE_TFT-1)	
/************/

#define M5D(n)				((n) & 0x1fffff)	// To get lower 21bits
volatile unsigned short LCD_BUFFER[1][1];



/*
 * ��ʼ������LCD������
 */
 void init_port(void)
 {
	GPCUP   = 0x00000000;   // ��ֹ�ڲ�����
    GPDUP   = 0x00000000;   // ��ֹ�ڲ�����
	GPCCON  = 0xaaaa02a9;   // GPIO�ܽ�����VD[23:8]
    GPDCON  = 0xaaaaaaaa;   // GPIO�ܽ�����VD[23:8]
 }
 
/*
 * ��ʼ��LCD������
 * ���������
 * type: ��ʾģʽ
 *      MODE_TFT_8BIT_240320  : 240*320 8bpp��TFT LCD
 *      MODE_TFT_16BIT_240320 : 240*320 16bpp��TFT LCD
 *      MODE_TFT_8BIT_640480  : 640*480 8bpp��TFT LCD
 *      MODE_TFT_16BIT_640480 : 640*480 16bpp��TFT LCD
 */
void Tft_Lcd_Init(void)
{
	LCDCON1=(CLKVAL_TFT<<8)|(MVAL_USED<<7)|(3<<5)|(12<<1)|0;
	LCDCON2=(VBPD<<24)|(LINEVAL_TFT<<14)|(VFPD<<6)|(VSPW);
	LCDCON3=(HBPD<<19)|(HOZVAL_TFT<<8)|(HFPD);
	LCDCON4=(MVAL<<8)|(HSPW);
	LCDCON5 = (1<<11) | (0<<10) | (1<<9) | (1<<8) | (0<<7) | (0<<6) | (1<<3)  |(BSWP<<1) | (HWSWP);

	LCDSADDR1=(((U32)LCD_BUFFER>>22)<<21)|M5D((U32)LCD_BUFFER>>1);
	LCDSADDR2=M5D( ((U32)LCD_BUFFER+(SCR_XSIZE_TFT*LCD_YSIZE_TFT*2))>>1 );
	LCDSADDR3=(((SCR_XSIZE_TFT-LCD_XSIZE_TFT)/1)<<11)|(LCD_XSIZE_TFT/1);
	LCDINTMSK|=(3); // MASK LCD Sub Interrupt
	TCONSEL &= (~7) ;     // Disable LPC3480
	TPAL = 0;
}

/*
 * �����Ƿ����LCD��Դ�����ź�LCD_PWREN
 * ���������
 *     invpwren: 0 - LCD_PWREN��ЧʱΪ��������
 *               1 - LCD_PWREN��ЧʱΪ��ת����
 *     pwren:    0 - LCD_PWREN�����Ч
 *               1 - LCD_PWREN�����Ч
 */
void Lcd_PowerEnable(int invpwren, int pwren)
{
    GPGUP  = (GPGUP & (~(1<<4))) | (1<<4);    // ��ֹ�ڲ�����    
	GPGCON = (GPGCON & (~(3<<8))) | (3<<8);   // GPG4����LCD_PWREN
    GPGDAT = GPGDAT|(1<<4);
    LCDCON5 = (LCDCON5 & (~(1<<5))) | (invpwren<<5);  // ����LCD_PWREN�ļ���: ����/��ת
    LCDCON5 = (LCDCON5 & (~(1<<3))) | (pwren<<3);     // �����Ƿ����LCD_PWREN
}    

#endif
