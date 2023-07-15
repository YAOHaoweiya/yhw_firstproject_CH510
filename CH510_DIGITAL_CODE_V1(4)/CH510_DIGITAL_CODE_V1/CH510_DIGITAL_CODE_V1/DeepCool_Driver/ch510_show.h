/**
  **************************************************************************
  * @file     ch560_show.h
  * @brief    ch560��ʾ���� .h �ļ�
  **************************************************************************
  */
	
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CH510_SHOW_H
#define __CH510_SHOW_H

#include "tm1668.h"
#include "tmr2_pwm.h"


#define TEMP_C 0x13 //�¶ȣ����϶�
#define TEMP_F 0x23	//�¶ȣ����϶�
#define Pw 0x4C			//���ʣ�w
#define ALL_MODE 0xFF //����ȫ��
#define START 0xAA //���ӿ�ʼ
#define STAND 0x00 //����
#define COUNTDOWN 0x06 //����ʱ
#define START_DELAY 100 //��ˮ�����ʱ����λms

void usage(int use);
void ch510_show_init(void);
void num_map(u8	*pData);//USB����ӳ��
//������ʾ
void stand_read(void);
static void number(u8 HUNDRED,u8 TEN,u8 ONE);
#endif /* __CH510_SHOW_H */
