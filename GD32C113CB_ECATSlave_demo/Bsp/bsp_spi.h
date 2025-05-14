#ifndef __HW_SPI_
#define __HW_SPI_

#include "gd32c11x.h"

#define SPI_RCU             RCU_GPIOA
#define SPI0_SCK_GPIO       GPIO_PIN_5 /* SPI0 SCK信号引脚定义*/
#define SPI0_SCK_GPIO_PORT  GPIOA      /* SPI0 SCK信号端口定义*/

#define SPI0_MISO_GPIO      GPIO_PIN_6 /* SPI0 MISO信号引脚定义*/
#define SPI0_MISO_GPIO_PORT GPIOA      /* SPI0 MISO信号端口定义*/

#define SPI0_MOSI_GPIO      GPIO_PIN_7 /* SPI0 MOSI信号引脚定义*/
#define SPI0_MOSI_GPIO_PORT GPIOA      /* SPI0 MOSI信号端口定义*/

#define SPI_CS_RCU          RCU_GPIOB
#define SPI_CS_ESC_PORT     GPIOB
#define SPI_CS_ESC_PIN      GPIO_PIN_1

#define SPI_CS_FUNC_PORT    GPIOB
#define SPI_CS_FUNC_PIN     GPIO_PIN_2

void spi0_gpio_init(void);
void spi0_init(void);
uint8_t SPI0_ReadWriteByte(uint8_t TxData);

#endif
