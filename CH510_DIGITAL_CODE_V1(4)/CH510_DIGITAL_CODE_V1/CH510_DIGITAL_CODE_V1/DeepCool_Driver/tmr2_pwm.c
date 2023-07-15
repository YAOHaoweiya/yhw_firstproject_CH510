#include "tmr2_pwm.h"

/**
  * @brief  configure the tmr2 pins.
  * @param  none
  * @retval none
  */
static void gpio_configuration(void)
{
  gpio_init_type gpio_init_struct;

  gpio_default_para_init(&gpio_init_struct);

  gpio_init_struct.gpio_pins = GPIO_PINS_0 ;
  gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
  gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
  gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_init(GPIOA, &gpio_init_struct);

  gpio_pin_mux_config(GPIOA, GPIO_PINS_SOURCE0, GPIO_MUX_2);
  
}

/**
  * @brief  configures the different peripheral clocks.
  * @param  none
  * @retval none
  */
static void crm_configuration(void)
{
  /* tmr2 clock enable */
  crm_periph_clock_enable(CRM_TMR2_PERIPH_CLOCK, TRUE);

  /* gpioa clock enable */
  crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);
}

void tmr2_pwm_init(void)
{
	tmr_output_config_type tmr_oc_init_structure;

	uint16_t c1dt_val = 0;
	uint16_t c2dt_val = 1000;
	uint16_t c3dt_val = 1000;
	uint16_t c4dt_val = 1000;
	uint16_t prescaler_value = 0;
	
  /* peripheral clocks configuration */
  crm_configuration();

  /* gpio configuration */
  gpio_configuration();

  /* compute the prescaler value */
  prescaler_value = (uint16_t)(system_core_clock / 24000000) - 1;

  /* tmr3 time base configuration */
  tmr_base_init(TMR2, 665, prescaler_value);//��ʼ�� TMR ���ڡ���Ƶ
  tmr_cnt_dir_set(TMR2, TMR_COUNT_UP);//���� TMR ��������������
  tmr_clock_source_div_set(TMR2, TMR_CLOCK_DIV1);//���� TMR ʱ��Դ��Ƶϵ��

  tmr_output_default_para_init(&tmr_oc_init_structure);//��ʼ�� tmr ���Ĭ�ϲ���
  tmr_oc_init_structure.oc_mode = TMR_OUTPUT_CONTROL_PWM_MODE_A;//���ͨ��ģʽ
  tmr_oc_init_structure.oc_idle_state = FALSE;//�������ͨ������״̬
  tmr_oc_init_structure.oc_polarity = TMR_OUTPUT_ACTIVE_HIGH;//�������ͨ������
  tmr_oc_init_structure.oc_output_state = TRUE;//�������ͨ��״̬
	
  tmr_output_channel_config(TMR2, TMR_SELECT_CHANNEL_1, &tmr_oc_init_structure);//���� TMR ���ͨ��
  tmr_channel_value_set(TMR2, TMR_SELECT_CHANNEL_1, c1dt_val);//���� TMR ͨ��ֵ
  tmr_output_channel_buffer_enable(TMR2, TMR_SELECT_CHANNEL_1, TRUE);//���û���� TMR ���ͨ��������


  tmr_period_buffer_enable(TMR2, TRUE);//���û���� TMR ���ڻ�����

  /* tmr enable counter */
  tmr_counter_enable(TMR2, TRUE);//���û���� TMR ������	
	
	tmr_channel_value_set(TMR2, TMR_SELECT_CHANNEL_1, 0);//���� TMR ͨ��ֵ
}

void cpu_led_state(uint8_t state)
{
	if(state==1){
		tmr_channel_value_set(TMR2, TMR_SELECT_CHANNEL_1, LIGHT);//���� TMR ͨ��ֵ
	}
	else
	{
		tmr_channel_value_set(TMR2, TMR_SELECT_CHANNEL_1, 0X00);//���� TMR ͨ��ֵ	
	}
}

