/**
 * @brief GD32 的 SPI 口初始化，包括硬件 SPI 配置
 *
 *
 */

#include "bsp_spi.h"

void spi0_gpio_init(void)
{
    /* 使能GPIOA和复用时钟 */
    rcu_periph_clock_enable(RCU_AF);
    rcu_periph_clock_enable(SPI_RCU);
    rcu_periph_clock_enable(SPI_CS_RCU);
	
    /* 配置SPI0引脚为复用功能 : SCK/PA5, MISO/PA6, MOSI/PA7 */
    gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7);

    /* 配置ESC CS引脚PB1, 用于EtherCAT从站控制器的通信 */
    gpio_init(SPI_CS_ESC_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, SPI_CS_ESC_PIN);
    gpio_bit_set(SPI_CS_ESC_PORT, SPI_CS_ESC_PIN);
	
    /* 配置FUNC CS引脚PB2, 用于其他功能模块的选择和通信 */
    gpio_init(SPI_CS_FUNC_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, SPI_CS_FUNC_PIN);
    gpio_bit_set(SPI_CS_FUNC_PORT, SPI_CS_FUNC_PIN);	
}

/**
 * @brief  STM32 硬件 SPI 初始化函数，配置 SPI 复用引脚、波特率等。
 * @param  None
 * @retval None
 */
void spi0_init(void)
{
    spi_parameter_struct spi_init_struct;

    /* 使能SPI0时钟 */
    rcu_periph_clock_enable(RCU_SPI0);

    /* deinitilize SPI and the parameters */
    spi_i2s_deinit(SPI0);
    spi_struct_para_init(&spi_init_struct);

    /* configure SPI0 parameter */
    spi_init_struct.trans_mode = SPI_TRANSMODE_FULLDUPLEX;
    spi_init_struct.device_mode = SPI_MASTER;
    spi_init_struct.frame_size = SPI_FRAMESIZE_8BIT;
    spi_init_struct.clock_polarity_phase = SPI_CK_PL_HIGH_PH_2EDGE; /* 模式3 */
    spi_init_struct.nss = SPI_NSS_SOFT;
    spi_init_struct.prescale = SPI_PSC_16;    /* 120Mhz / 16 */
    spi_init_struct.endian = SPI_ENDIAN_MSB; /* 高位在前 */
    spi_init(SPI0, &spi_init_struct);

    spi_crc_polynomial_set(SPI0, 7); /* configure SPI CRC function */

    /* 使能SPI外设 */
    spi_enable(SPI0);
}

/**
 * @brief  SPI 收发函数，SPI 发出一个 byte 的数据，同时采集 MISO 一个 byte 的数据。
 * @param  TxData 发送的1 byte数据
 * @retval MISO返回的1 byte数据
 */
uint8_t SPI0_ReadWriteByte(uint8_t TxData)
{
    uint8_t received_data;

    /* 发送数据 */
    while (RESET == spi_i2s_flag_get(SPI0, SPI_FLAG_TBE)) {} /* 等待发送区空 */
    spi_i2s_data_transmit(SPI0, TxData);                     /* 通过外设SPIx发送一个byte的数据 */

    /* 接收数据 */
    while (RESET == spi_i2s_flag_get(SPI0, SPI_FLAG_RBNE)) {} /* 等待接收完一个byte */
    received_data = spi_i2s_data_receive(SPI0);

    return received_data;
}
