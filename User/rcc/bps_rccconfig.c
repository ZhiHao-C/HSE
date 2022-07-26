#include "bps_rccconfig.h"

unsigned char HSEstatus;
uint32_t HSIstatus;
void HSE_setSysCLK(uint32_t RCC_PLLMul_x)
{
	
	RCC_DeInit();                               //��ʼ��
	RCC_HSEConfig(RCC_HSE_ON);                  //��HSE
	HSEstatus=RCC_WaitForHSEStartUp();          //�ȴ�HSE�ȶ�
	if(HSEstatus==SUCCESS)
	{
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);//�������
		FLASH_SetLatency(FLASH_Latency_2);
		
		RCC_HCLKConfig(RCC_SYSCLK_Div1);//����HCLK(AHB),PCLK1(APB1),PCLK2(APB2)�Ƿ�ѡ���Ƶ
		RCC_PCLK1Config(RCC_SYSCLK_Div2);
		RCC_PCLK2Config(RCC_SYSCLK_Div1);
		
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_x);//����PLLʱ����Դ ��ƵΪx1~x16
		RCC_PLLCmd(ENABLE);                                 //��PLL
		
		
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY)==RESET );//�ȴ�PLLʱ�Ӿ���
		
		
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);//ѡ��ϵͳʱ����Դ
		while (RCC_GetSYSCLKSource()!=0x08);//�ȴ��л�״̬���
	}
}



void HSI_setSysCLK(uint32_t RCC_PLLMul_x)
{
	
	RCC_DeInit();                               //��ʼ��
	RCC_HSICmd(ENABLE);                         //��HSI
	HSIstatus = RCC->CR & RCC_CR_HSIRDY;          //�ȴ�HSI�ȶ�
	if(HSIstatus==RCC_CR_HSIRDY)
	{
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);//�������
		FLASH_SetLatency(FLASH_Latency_2);
		
		RCC_HCLKConfig(RCC_SYSCLK_Div1);//����HCLK(AHB),PCLK1(APB1),PCLK2(APB2)�Ƿ�ѡ���Ƶ
		RCC_PCLK1Config(RCC_SYSCLK_Div2);
		RCC_PCLK2Config(RCC_SYSCLK_Div1);
		
		RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_x);//����PLLʱ����Դ ��ƵΪx1~x16
		RCC_PLLCmd(ENABLE);                                 //��PLL
		
		
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY)==RESET );//�ȴ�PLLʱ�Ӿ���
		
		
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);//ѡ��ϵͳʱ����Դ
		while (RCC_GetSYSCLKSource()!=0x08);//�ȴ��л�״̬���
	}
}
