#include "spi.h"

/*SPI1���Ŷ���
* PA4---CS
* PA5---SCK
* PA6---MISO
* PA7---MOSI
*/

/******************************************************************************
      ����˵����spi GPIO��ʼ�����ú���
      ������ݣ���
      ����ֵ��  ��
******************************************************************************/
static void spi_gpio_config(void)
{
	gpio_init_type gpio_initstructure;//����gpio�ṹ��
	
  crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);//ʹ��gpioʱ��
  gpio_default_para_init(&gpio_initstructure);//gpio�ṹ������Ĭ��ֵ
	
	/* spi1 sck pin */
  gpio_initstructure.gpio_out_type       = GPIO_OUTPUT_PUSH_PULL;//�������ģʽ  
  gpio_initstructure.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;//�ϴ�����ƶ�/��������
  gpio_initstructure.gpio_pull           = GPIO_PULL_NONE;  //gpio��������
  gpio_initstructure.gpio_mode           = GPIO_MODE_MUX; //gpio����ģʽ
  gpio_initstructure.gpio_pins = GPIO_PINS_5;//PA5
  gpio_init(GPIOA, &gpio_initstructure);//��ֵ
  
  /* spi1 mosi pin */
  gpio_initstructure.gpio_pull           = GPIO_PULL_NONE;  
  gpio_initstructure.gpio_mode           = GPIO_MODE_MUX; 
  gpio_initstructure.gpio_pins = GPIO_PINS_7;//PA7 
  gpio_init(GPIOA, &gpio_initstructure);
  /*CS����*/
  gpio_initstructure.gpio_pull           = GPIO_PULL_UP;//����ģʽ 
  gpio_initstructure.gpio_mode           = GPIO_MODE_OUTPUT; //���ģʽ
  gpio_initstructure.gpio_pins = GPIO_PINS_4;//PA4
  gpio_init(GPIOA, &gpio_initstructure);
	
	GPIOA->odt_bit.odt4=1;
}

/******************************************************************************
      ����˵����spi1��ʼ�����ú���
      ������ݣ���
      ����ֵ��  ��
******************************************************************************/
void spi_config(void)
{
	spi_gpio_config();
	
  spi_init_type spi_init_struct;//����spi�ṹ��
  crm_periph_clock_enable(CRM_SPI1_PERIPH_CLOCK, TRUE);//ʹ��spiʱ��
	
  spi_default_para_init(&spi_init_struct);//Ĭ��spi����
	
  spi_init_struct.transmission_mode = SPI_TRANSMIT_HALF_DUPLEX_TX;//����˫��ֻ��ģʽ
  spi_init_struct.master_slave_mode =SPI_MODE_MASTER;//����ģʽ
  spi_init_struct.mclk_freq_division = SPI_MCLK_DIV_128;//128 ��Ƶ
  spi_init_struct.first_bit_transmission = SPI_FIRST_BIT_LSB;//�ȷ��͸�λ
  spi_init_struct.frame_bit_num = SPI_FRAME_8BIT;//һ֡���� 8bit ����
  spi_init_struct.clock_polarity = SPI_CLOCK_POLARITY_HIGH;//����ʱ��ʱ������ߵ�ƽ
  spi_init_struct.clock_phase = SPI_CLOCK_PHASE_2EDGE;//��һ��ʱ���ؽ������ݲ���
  spi_init_struct.cs_mode_selection = SPI_CS_SOFTWARE_MODE;//Ӳ�� CS ģʽ
  spi_init(SPI1, &spi_init_struct);
  spi_enable(SPI1, TRUE);//ʹ��SPI
}

/******************************************************************************
      ����˵����spi����д�뺯��
      ������ݣ�dat  Ҫд��Ĵ�������
      ����ֵ��  ��
******************************************************************************/
void spi1_writ_byte(uint8_t dat)
{
    spi_i2s_data_transmit(SPI1,dat);
    /*REST��ʾ�ǿ�*/
    while(spi_i2s_flag_get(SPI1, SPI_I2S_TDBE_FLAG) == RESET); //����ǿ�,��һֱ�ȴ�
    /*RSET��ʾ����*/
    while(spi_i2s_flag_get(SPI1, SPI_I2S_BF_FLAG) == TRUE);//���æµ,��һֱ�ȴ�
}
