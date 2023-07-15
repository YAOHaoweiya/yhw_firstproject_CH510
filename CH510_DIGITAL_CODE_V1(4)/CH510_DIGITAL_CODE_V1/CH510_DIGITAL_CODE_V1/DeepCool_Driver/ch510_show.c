#include "ch510_show.h"
#include "delay.h"
#include "string.h"
#include "stdlib.h"

const u8 TM1668_10X7_CODE[11]={0x3F,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x00};//数字0-9 和灭
const u8 USAGE_RATE[6]={0,0X01,0X03,0x07,0x0F,0x1F};//利用率 灯


static u8 led_data[14];

static u8 NOW_CRATE=0;//利用率 值

static u8 CH=0;//数字百位
static u8 CT=0;//数字十位
static u8 CO=0;//数字个位

static u16 stand_count=5000;


/******************************************************************************
      函数说明：数据清空
      入口数据：无
      返回值：  无
******************************************************************************/
static void data_clear(void)
{
	u8 i;
	//清空
	for(i=0;i<14;i++)
		led_data[i]=0x00;
}
/******************************************************************************
      函数说明：所有灯全灭
      入口数据：无
      返回值：  无
******************************************************************************/
static void all_led_off(void)
{
	data_clear();
	TM1668_WriteBytesAddrIncrease(led_data,14,DSP_14_16);	//显示一次修改
}
/******************************************************************************
      函数说明：所有灯全亮
      入口数据：无
      返回值：  无
******************************************************************************/
static void all_led_on(void)
{
	u8 i;
	//清空
	for(i=0;i<14;i++)
		led_data[i]=0xFF;
	TM1668_WriteBytesAddrIncrease(led_data,14,DSP_14_16);	//显示一次修改
}
/******************************************************************************
      函数说明：数码管数显初始化函数
      入口数据：无
      返回值：  无
******************************************************************************/
void ch510_show_init(void)
{
	TM1668_Init();

}


/******************************************************************************
      函数说明：数字显示
      入口数据：无
      返回值：  无
******************************************************************************/
static void number(u8 HUNDRED,u8 TEN,u8 ONE)
{
	//百位
	if(HUNDRED>0)
		led_data[2]=TM1668_10X7_CODE[HUNDRED];
	//十位
	if(HUNDRED>0|TEN>0)
		led_data[4]=TM1668_10X7_CODE[TEN];
	//个位
	led_data[6]=TM1668_10X7_CODE[ONE];
}
/*********************************************************************************************************
      函数说明：数据映射函数
      入口数据：*pData  数据形式：字符串 HLXDATA([cpuUsage],[cpuTemperature],0,0,[unit])
								cpuUsage:CPU利用率（0-100）  cpuTemperature:CPU温度（控制数字）
      返回值：  无
*********************************************************************************************************/
void num_map(u8	*pData)
{
	data_clear();
	if(*pData==0xFF) 
		{
			all_led_on();   
			tmr2_pwm_init(); 
			cpu_led_state(1);   
			TM1668_WriteBytesAddrIncrease(led_data,14,DSP_14_16);	//显示一次修改
			stand_count=5000;
			return;
		}
	 if(*pData==0x00) 
		{
			all_led_off();   
			tmr2_pwm_init(); 
			cpu_led_state(0);   
			TM1668_WriteBytesAddrIncrease(led_data,14,DSP_14_16);	//显示一次修改
			stand_count=5000;
			return;
		}
	
	u8 *ptail=pData;//用于验证数据是否为乱码
	if(*ptail=='H'&& *(ptail+1)=='L' && *(ptail+2)=='X' && *(ptail+3)=='D' && *(ptail+4)=='A' && *(ptail+5)=='T') __NOP();
	else return;
	
	char *phead=pData+8;
	char *token[3];
	const char s[2]=",";
	token[0]=strtok(phead,s);
	token[1]=strtok(NULL,s);
	token[2]=strtok(NULL,s)+4;
	NOW_CRATE=atoi(token[0]);
	int num=atoi(token[1]);
	CH=num/100%10;
	CT=num/10%10;
  CO=num/1%10;
	if(*(token[2])=='C') { led_data[8]=0x02;}
	else if(*(token[2])=='F') { led_data[8]=0x01;}

	usage(NOW_CRATE);//利用率显示函数
	number(CH,CT,CO);//数字显示函数
	tmr2_pwm_init();
	cpu_led_state(1);

	TM1668_WriteBytesAddrIncrease(led_data,14,DSP_14_16);	//显示一次修改
	stand_count=5000;
	phead=NULL;
	ptail=NULL;
}

void stand_read(void)
{
	stand_count--;
	delay_ms(1);
	if(stand_count==0)
	{
		stand_count=5000;
		all_led_off();
		cpu_led_state(0);
	}
	
}

void usage(int use)
{
	if(use==0) 
		led_data[0]=USAGE_RATE[0];
	else if(use>0&&use<=20)
		led_data[0]=USAGE_RATE[1];
	else if(use>20 && use<=40)
		led_data[0]=USAGE_RATE[2];
	else if(use>40 && use<=60)
		led_data[0]=USAGE_RATE[3];
	else if(use>60 && use<=80)
		led_data[0]=USAGE_RATE[4];
	else if(use>80)
		led_data[0]=USAGE_RATE[5];	
}
