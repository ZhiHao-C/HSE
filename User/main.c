#include "stm32f10x.h"                  // Device header
#include "bps_led.h"
#include "bps_rccconfig.h"
void delay_ms(int n)//ÑÓÊ±º¯Êý
{
	int i;
	while (n--)
	{
		for(i=0;i<5520;i++);
	}
}



int main()
{
//	HSE_setSysCLK(RCC_PLLMul_9);
//	HSI_setSysCLK(RCC_PLLMul_9);
	LED_G_GPIO_Config();
	while (1)
	{
		led(on);
		delay_ms(500);
		led(off);
		delay_ms(500);
	}
}

