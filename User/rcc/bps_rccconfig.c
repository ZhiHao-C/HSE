#include "bps_rccconfig.h"

unsigned char HSEstatus;
uint32_t HSIstatus;
void HSE_setSysCLK(uint32_t RCC_PLLMul_x)
{
	
	RCC_DeInit();                               //初始化
	RCC_HSEConfig(RCC_HSE_ON);                  //打开HSE
	HSEstatus=RCC_WaitForHSEStartUp();          //等待HSE稳定
	if(HSEstatus==SUCCESS)
	{
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);//闪存管理
		FLASH_SetLatency(FLASH_Latency_2);
		
		RCC_HCLKConfig(RCC_SYSCLK_Div1);//配置HCLK(AHB),PCLK1(APB1),PCLK2(APB2)是否选择分频
		RCC_PCLK1Config(RCC_SYSCLK_Div2);
		RCC_PCLK2Config(RCC_SYSCLK_Div1);
		
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_x);//设置PLL时钟来源 倍频为x1~x16
		RCC_PLLCmd(ENABLE);                                 //打开PLL
		
		
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY)==RESET );//等待PLL时钟就绪
		
		
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);//选择系统时钟来源
		while (RCC_GetSYSCLKSource()!=0x08);//等待切换状态完成
	}
}



void HSI_setSysCLK(uint32_t RCC_PLLMul_x)
{
	
	RCC_DeInit();                               //初始化
	RCC_HSICmd(ENABLE);                         //打开HSI
	HSIstatus = RCC->CR & RCC_CR_HSIRDY;          //等待HSI稳定
	if(HSIstatus==RCC_CR_HSIRDY)
	{
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);//闪存管理
		FLASH_SetLatency(FLASH_Latency_2);
		
		RCC_HCLKConfig(RCC_SYSCLK_Div1);//配置HCLK(AHB),PCLK1(APB1),PCLK2(APB2)是否选择分频
		RCC_PCLK1Config(RCC_SYSCLK_Div2);
		RCC_PCLK2Config(RCC_SYSCLK_Div1);
		
		RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_x);//设置PLL时钟来源 倍频为x1~x16
		RCC_PLLCmd(ENABLE);                                 //打开PLL
		
		
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY)==RESET );//等待PLL时钟就绪
		
		
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);//选择系统时钟来源
		while (RCC_GetSYSCLKSource()!=0x08);//等待切换状态完成
	}
}
