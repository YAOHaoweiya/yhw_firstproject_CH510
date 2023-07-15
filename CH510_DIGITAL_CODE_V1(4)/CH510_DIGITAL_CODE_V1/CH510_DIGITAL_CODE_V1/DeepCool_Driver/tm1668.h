/**
  **************************************************************************
  * @file     tm1668.h
  * @brief   	tm1668����.h�ļ�
  **************************************************************************
  */
	
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TM1668_H
#define __TM1668_H

#include "spi.h"


/*******************************************************************************
                                ��ʾģʽ��������
*******************************************************************************/
#define GRID4_SEG13 0x00    /* 4λ13�� */
#define GRID5_SEG12 0x01    /* 5λ12�� */
#define GRID6_SEG11 0x02    /* 6λ11�� */
#define GRID7_SEG10 0x03    /* 7λ10�� */

/*******************************************************************************
                                ������������
*******************************************************************************/
#define CMD_DataWriteIncrease   0x40    /* ��ַ����д���� */
#define CMD_DataWriteFixed      0x44    /* �̶���ַд���� */


/*******************************************************************************
                                ��ʾ������������
*******************************************************************************/
#define DSP_01_16   0x88    /* ����������Ϊ1/16  */
#define DSP_02_16   0x89    /* ����������Ϊ2/16  */
#define DSP_04_16   0x8A    /* ����������Ϊ4/16  */
#define DSP_10_16   0x8B    /* ����������Ϊ10/16 */
#define DSP_11_16   0x8C    /* ����������Ϊ11/16 */
#define DSP_12_16   0x8D    /* ����������Ϊ12/16 */
#define DSP_13_16   0x8E    /* ����������Ϊ13/16 */
#define DSP_14_16   0x8F    /* ����������Ϊ14/16 8F*/
#define DSP_OFF     0x80    /* ��ʾ�� */

/*******************************************************************************
                                ��ַ��������
*******************************************************************************/
#define ADD_00H     0xC0    /* ��ʾ��ַ: GRID1     */
#define ADD_01H     0xC1    /* ��ʾ��ַ: GRID1     */
#define ADD_02H     0xC2    /* ��ʾ��ַ: GRID2     */
#define ADD_03H     0xC3    /* ��ʾ��ַ: GRID2     */
#define ADD_04H     0xC4    /* ��ʾ��ַ: GRID3     */
#define ADD_05H     0xC5    /* ��ʾ��ַ: GRID3     */
#define ADD_06H     0xC6    /* ��ʾ��ַ: GRID4     */
#define ADD_07H     0xC7    /* ��ʾ��ַ: GRID4     */
#define ADD_08H     0xC8    /* ��ʾ��ַ: GRID5     */
#define ADD_09H     0xC9    /* ��ʾ��ַ: GRID5     */
#define ADD_0AH     0xCA    /* ��ʾ��ַ: GRID6     */
#define ADD_0BH     0xCB    /* ��ʾ��ַ: GRID6     */
#define ADD_0CH     0xCC    /* ��ʾ��ַ: GRID7     */
#define ADD_0DH     0xCD    /* ��ʾ��ַ: GRID7     */


void TM1668_WriteBytesAddrIncrease(unsigned char *p, unsigned char nBytes, unsigned char brightness);
void TM1668_WriteBytesAddrFixed(unsigned char *p, unsigned char nBytes, unsigned char brightness);
void TM1668_Init(void);


#endif /* __TM1668_H */
