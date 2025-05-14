#include "ax58100.h"

/* pb0 - pull up */
void ethercat_pdi_init(void)
{
    /* AX58100_INT引脚初始化配置 */
    rcu_periph_clock_enable(AX58100_INT_RCU);
    gpio_init(AX58100_INT_PORT, GPIO_MODE_IPU, GPIO_OSPEED_50MHZ, AX58100_INT_PIN); /* 配置成上拉输入 */
    gpio_exti_source_select(AX58100_INT_PORT_SOURCE, AX58100_INT_PIN_SOURCE);       /* PB0连接到中断线0 */

    exti_init(AX58100_INT_EXTI, EXTI_INTERRUPT, EXTI_TRIG_FALLING); /* 下降沿触发 */
    exti_interrupt_flag_clear(AX58100_INT_EXTI);                    /* 清中断标志，防止误触发 */
    nvic_irq_enable(AX58100_INT_EXTI_IRQn, 0x00, 0x00);		// 优先级应为最高，确保数据实时性
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

