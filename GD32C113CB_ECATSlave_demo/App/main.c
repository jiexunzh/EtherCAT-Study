#include "bsp_systick.h"
#include "bsp_led.h"

int main(void)
{
	SysTick_init();
	led_init();

    while (1)
	{
		LED_Toggle();
		delay_ms(500);
    }
}


