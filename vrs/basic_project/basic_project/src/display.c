/*
 * display.c
 *
 *  Created on: Nov 21, 2012
 *      Author: student
 */

#include "display.h"

void display_pin_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIOA->BSRRL = RW_WR;
}

void display_init(void)
{
	initSPI2();
	display_pin_init();

	display_on();
}

void display_on(void)
{
	device_Select();
	a0_low();
	Reset_high();
	RW_WR_low();

	readWriteSPI2(DISPLAY_ON);
	device_Unselect();
}

inline void a0_low(void)
{
	GPIOA->BSRRH = A0;
}

inline void a0_high(void)
{
	GPIOA->BSRRL = A0;
}

inline void RW_WR_low(void)
{
	GPIOA->BSRRH = RW_WR;
}

inline void RW_WR_high(void)
{
	GPIOA->BSRRL = RW_WR;
}

inline void Reset_low(void)
{
	GPIOA->BSRRH = DISPLAY_RESET;
}

inline void Reset_high(void)
{
	GPIOA->BSRRL = DISPLAY_RESET;
}
