#include "pwm_out.h"
#include "mcu.h"
#include "stm32l1xx_tim.h"
/*
TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
TIM_OCInitTypeDef  TIM_OCInitStructure;
GPIO_InitTypeDef GPIO_InitStructure;
uint16_t PrescalerValue = 0;

void initPWM_Output()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);

	  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

	  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_13;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;

	  GPIO_Init(GPIOB, &GPIO_InitStructure);

	  GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_TIM9);

	  PrescalerValue = (uint16_t) (SystemCoreClock / 100000) - 1;
	  TIM_TimeBaseStructure.TIM_Period = 100;
	  TIM_TimeBaseStructure.TIM_Prescaler = 0;//PrescalerValue;
	  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	  TIM_TimeBaseInit(TIM9, &TIM_TimeBaseStructure);

	  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	  TIM_OCInitStructure.TIM_Pulse = 0; // 500
	  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	  TIM_OC1Init(TIM9, &TIM_OCInitStructure);
	  TIM_OC2Init(TIM9, &TIM_OCInitStructure);

	  TIM_OC1PreloadConfig(TIM9, TIM_OCPreload_Enable);
	  TIM_OC2PreloadConfig(TIM9, TIM_OCPreload_Enable);

	  TIM_ARRPreloadConfig(TIM9, ENABLE);

	  TIM_Cmd(TIM9, ENABLE);
}
*/
