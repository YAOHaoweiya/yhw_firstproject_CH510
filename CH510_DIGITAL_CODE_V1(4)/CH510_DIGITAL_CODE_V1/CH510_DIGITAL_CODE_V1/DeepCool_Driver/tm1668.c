#include "tm1668.h"
/*
    ��ʼ��������
*/
static void TM1668_Start(void)
{
	GPIOA->odt_bit.odt4=0;
}

/*
    ������������
*/
static void TM1668_End(void)
{
	GPIOA->odt_bit.odt4=1;
}



/*
	��ַ����ģʽд��n���ֽ����ݣ���SRAM��ʼ��ַ��ʼд
	p��д�������׵�ַ		nBytes��д�����ݸ���(<=14)		brightness����ʾ����
 */
void TM1668_WriteBytesAddrIncrease(unsigned char *p, unsigned char nBytes, unsigned char brightness)
{
	unsigned char i = 0;

	TM1668_Start();
	spi1_writ_byte(GRID7_SEG10);				/* ������ʾģʽ��7λ10�� */
	TM1668_End();

	TM1668_Start();
	spi1_writ_byte(CMD_DataWriteIncrease);	/* �������������ַ���� */
	TM1668_End();

	TM1668_Start();
	spi1_writ_byte(ADD_00H);					/* ������ʾ��ַ����ʼ��ַ */
	for (i = 0; i < nBytes; i++)
	{
		spi1_writ_byte(p[i]);
	}
	TM1668_End();

	TM1668_Start();
	spi1_writ_byte(brightness);				/* ��ʾ����������ȵ��� */
	TM1668_End();
}

/*
	��ַ�̶�ģʽд��n���ֽ����ݣ���SRAM��ʼ��ַ��ʼд
	p��д�������׵�ַ		nBytes��д�����ݸ���(<=14)		brightness����ʾ����
 */
void TM1668_WriteBytesAddrFixed(unsigned char *p, unsigned char nBytes, unsigned char brightness)
{
	unsigned char i = 0;

	TM1668_Start();
	spi1_writ_byte(GRID7_SEG10);				/* ������ʾģʽ��7λ10�� */
	TM1668_End();

	TM1668_Start();
	spi1_writ_byte(CMD_DataWriteFixed);		/* �������������ַ�̶� */
	TM1668_End();

	for (i = 0; i < nBytes; i++)
	{
		TM1668_Start();
		spi1_writ_byte(ADD_00H + i);			/* ������ʾ��ַ����ʼ��ַ */
		spi1_writ_byte(p[i]);
		TM1668_End();
	}

	TM1668_Start();
	spi1_writ_byte(brightness);				/* ��ʾ����������ȵ��� */
	TM1668_End();
}

/*
    ��ʼ����1668�ڲ���ʾ�Ĵ������㣬��ֹ�������룬���ر���ʾ
*/
void TM1668_Init(void)
{
	spi_config();
	
	unsigned char i = 0;

	TM1668_Start();
	spi1_writ_byte(GRID7_SEG10);				/* ������ʾģʽ��7λ10�� */
	TM1668_End();

	TM1668_Start();
	spi1_writ_byte(CMD_DataWriteIncrease);	/* �������������ַ���� */
	TM1668_End();

	TM1668_Start();
	spi1_writ_byte(ADD_00H);					/* ������ʾ��ַ����ʼ��ַ */
	for (i = 0; i < 14; i++)
	{
		spi1_writ_byte(0);
	}
	TM1668_End();

	TM1668_Start();
	spi1_writ_byte(DSP_OFF);				    /* ��ʾ����������ȵ��� */
	TM1668_End();
}
