/**
  **************************************************************************
  * @file     spi.h
  * @brief    at32f425Ӳ��SPI .h �ļ�
  **************************************************************************
  */
	
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SPI_H
#define __SPI_H

/* Includes ------------------------------------------------------------------*/
#include "at32f425.h"

/** @defgroup SPI���ú���
  * @{
  */
	
void spi_config(void);
void spi1_writ_byte(uint8_t dat);
	
/**
  * @}
 */
#endif /* __SPI_H */
