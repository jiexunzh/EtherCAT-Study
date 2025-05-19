#include "bsp_systick.h"
#include "bsp_led.h"

#include "applInterface.h"
#include "ECATSlave_V100.h"
#include "el9800hw.h"

uint32_t led_tick = 0;

int main(void)
{
	SysTick_init();
	led_init();

    HW_Init();
    MainInit();
    bRunApplication = TRUE;
	
    while (1)
	{
		if (nonBlock(led_tick, 500))
		{
			led_tick = get_tick();
			LED1_Toggle;
		}
		
		if (bRunApplication == TRUE)
		{
			MainLoop();
		}
		else
		{
			HW_Release();
		}		
    }
}


