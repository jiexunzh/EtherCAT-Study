#include "ax58100.h"

/* pb0 - pull up */
void ethercat_pdi_init(void)
{
    /* AX58100_INT���ų�ʼ������ */
    rcu_periph_clock_enable(AX58100_INT_RCU);
    gpio_init(AX58100_INT_PORT, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, AX58100_INT_PIN); /* ���ó��������� */
    gpio_exti_source_select(AX58100_INT_PORT_SOURCE, AX58100_INT_PIN_SOURCE);       /* PB0���ӵ��ж���0 */

    exti_init(AX58100_INT_EXTI, EXTI_INTERRUPT, EXTI_TRIG_FALLING); /* �½��ش��� */
    exti_interrupt_flag_clear(AX58100_INT_EXTI);                    /* ���жϱ�־����ֹ�󴥷� */
    nvic_irq_enable(AX58100_INT_EXTI_IRQn, 0x00, 0x00);		// ���ȼ�ӦΪ��ߣ�ȷ������ʵʱ��
    exti_interrupt_flag_clear(AX58100_INT_EXTI); 
}

/* pa3 - nopull */
void ethercat_sync0_init(void)
{
    rcu_periph_clock_enable(AX58100_SYNC0_RCU);
    gpio_init(AX58100_SYNC0_PORT, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, AX58100_SYNC0_PIN);
    gpio_exti_source_select(AX58100_SYNC0_PORT_SOURCE, AX58100_SYNC0_PIN_SOURCE);     

    exti_init(AX58100_SYNC0_EXTI, EXTI_INTERRUPT, EXTI_TRIG_FALLING); 
    exti_interrupt_flag_clear(AX58100_SYNC0_EXTI);                    
    nvic_irq_enable(AX58100_SYNC0_EXTI_IRQn, 0x00, 0x01);
    exti_interrupt_flag_clear(AX58100_SYNC0_EXTI);
}

/* pa4 - nopull */
void ethercat_sync1_init(void)
{
    rcu_periph_clock_enable(AX58100_SYNC1_RCU);
    gpio_init(AX58100_SYNC1_PORT, GPIO_MODE_IN_FLOATING, GPIO_OSPEED_50MHZ, AX58100_SYNC1_PIN);
    gpio_exti_source_select(AX58100_SYNC1_PORT_SOURCE, AX58100_SYNC1_PIN_SOURCE);     

    exti_init(AX58100_SYNC1_EXTI, EXTI_INTERRUPT, EXTI_TRIG_FALLING); 
    exti_interrupt_flag_clear(AX58100_SYNC1_EXTI);                    
    nvic_irq_enable(AX58100_SYNC1_EXTI_IRQn, 0x00, 0x02);
    exti_interrupt_flag_clear(AX58100_SYNC1_EXTI);
}

