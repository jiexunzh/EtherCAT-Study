/**
 * @brief GD32 �� SPI �ڳ�ʼ��������Ӳ�� SPI ����
 *
 *
 */

#include "bsp_spi.h"

void spi0_gpio_init(void)
{
    /* ʹ��GPIOA�͸���ʱ�� */
    rcu_periph_clock_enable(RCU_AF);
    rcu_periph_clock_enable(SPI_RCU);
    rcu_periph_clock_enable(SPI_CS_RCU);
	
    /* ����SPI0����Ϊ���ù��� : SCK/PA5, MISO/PA6, MOSI/PA7 */
    gpio_init(GPIOA, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7);

    /* ����ESC CS����PB1, ����EtherCAT��վ��������ͨ�� */
    gpio_init(SPI_CS_ESC_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, SPI_CS_ESC_PIN);
    gpio_bit_set(SPI_CS_ESC_PORT, SPI_CS_ESC_PIN);
	
    /* ����FUNC CS����PB2, ������������ģ���ѡ���ͨ�� */
    gpio_init(SPI_CS_FUNC_PORT, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ, SPI_CS_FUNC_PIN);
    gpio_bit_set(SPI_CS_FUNC_PORT, SPI_CS_FUNC_PIN);	
}

/**
 * @brief  STM32 Ӳ�� SPI ��ʼ������������ SPI �������š������ʵȡ�
 * @param  None
 * @retval None
 */
void spi0_init(void)
{
    spi_parameter_struct spi_init_struct;

    /* ʹ��SPI0ʱ�� */
    rcu_periph_clock_enable(RCU_SPI0);

    /* deinitilize SPI and the parameters */
    spi_i2s_deinit(SPI0);
    spi_struct_para_init(&spi_init_struct);

    /* configure SPI0 parameter */
    spi_init_struct.trans_mode = SPI_TRANSMODE_FULLDUPLEX;
    spi_init_struct.device_mode = SPI_MASTER;
    spi_init_struct.frame_size = SPI_FRAMESIZE_8BIT;
    spi_init_struct.clock_polarity_phase = SPI_CK_PL_HIGH_PH_2EDGE; /* ģʽ3 */
    spi_init_struct.nss = SPI_NSS_SOFT;
    spi_init_struct.prescale = SPI_PSC_16;    /* 120Mhz / 16 */
    spi_init_struct.endian = SPI_ENDIAN_MSB; /* ��λ��ǰ */
    spi_init(SPI0, &spi_init_struct);

    spi_crc_polynomial_set(SPI0, 7); /* configure SPI CRC function */

    /* ʹ��SPI���� */
    spi_enable(SPI0);
}

/**
 * @brief  SPI �շ�������SPI ����һ�� byte �����ݣ�ͬʱ�ɼ� MISO һ�� byte �����ݡ�
 * @param  TxData ���͵�1 byte����
 * @retval MISO���ص�1 byte����
 */
uint8_t SPI0_ReadWriteByte(uint8_t TxData)
{
    uint8_t received_data;

    /* �������� */
    while (RESET == spi_i2s_flag_get(SPI0, SPI_FLAG_TBE)) {} /* �ȴ��������� */
    spi_i2s_data_transmit(SPI0, TxData);                     /* ͨ������SPIx����һ��byte������ */

    /* �������� */
    while (RESET == spi_i2s_flag_get(SPI0, SPI_FLAG_RBNE)) {} /* �ȴ�������һ��byte */
    received_data = spi_i2s_data_receive(SPI0);

    return received_data;
}
