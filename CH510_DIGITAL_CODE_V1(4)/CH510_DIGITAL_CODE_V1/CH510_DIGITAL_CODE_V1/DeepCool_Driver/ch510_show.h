/**
  **************************************************************************
  * @file     ch560_show.h
  * @brief    ch560显示驱动 .h 文件
  **************************************************************************
  */
	
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CH510_SHOW_H
#define __CH510_SHOW_H

#include "tm1668.h"
#include "tmr2_pwm.h"


#define TEMP_C 0x13 //温度，摄氏度
#define TEMP_F 0x23	//温度，华氏度
#define Pw 0x4C			//功率，w
#define ALL_MODE 0xFF //测试全亮
#define START 0xAA //连接开始
#define STAND 0x00 //待机
#define COUNTDOWN 0x06 //倒计时
#define START_DELAY 100 //流水间隔延时，单位ms

void usage(int use);
void ch510_show_init(void);
void num_map(u8	*pData);//USB数据映射
//待机显示
void stand_read(void);
static void number(u8 HUNDRED,u8 TEN,u8 ONE);
#endif /* __CH510_SHOW_H */
