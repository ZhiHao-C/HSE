#ifndef __BPS_RCCCONFIG_H__
#define __BPS_RCCCONFIG_H__

#include "stm32f10x.h" 

void HSE_setSysCLK(uint32_t RCC_PLLMul_x);
void HSI_setSysCLK(uint32_t RCC_PLLMul_x);

#endif

