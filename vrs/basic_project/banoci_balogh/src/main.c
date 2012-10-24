/**
*****************************************************************************
**
**  File        : main.c
**
**  Abstract    : main function.
**
**  Functions   : main
**
**  Environment : Atollic TrueSTUDIO/STM32
**                STMicroelectronics STM32Lxx Standard Peripherals Library
**
**  Distribution: The file is distributed “as is,” without any warranty
**                of any kind.
**
**  (c)Copyright Atollic AB.
**  You may use this file as-is or modify it according to the needs of your
**  project. Distribution of this file (unmodified or modified) is not
**  permitted. Atollic AB permit registered Atollic TrueSTUDIO(R) users the
**  rights to distribute the assembled, compiled & linked contents of this
**  file as part of an application binary file, provided that it is built
**  using the Atollic TrueSTUDIO(R) toolchain.
**
**
*****************************************************************************
*/
/* Includes */
#include <stddef.h>
#include <stdio.h>
#include "mcu.h"
#include "usart.h"
#include "adc.h"
#include "pwm.h"
#include "i2c.h"
#include "ads1100.h"

uint16_t intensity=50;
volatile unsigned char prevch = '\0';

/**
**===========================================================================
**
**  Abstract: main program
**
**===========================================================================
*/

int tick = 0;


//this is a function handling received data
//it is not called automaticaly
void handleReceivedChar(unsigned char data)
{
	if(data == 'x') prevch = '\0';
	if(data >= '0' && data <= '9') {
		if(prevch == '\0') {
			intensity = (uint16_t)(data-'0') * 10 ;
			prevch = data;
		} else {
			intensity = (uint16_t)(prevch -'0') * 10 + (uint16_t)(data-'0') ;
			prevch = '\0';
		}
	}

}

/*void handleReceivedChar2(unsigned char data)
{
	char s[128];
	if (data >= 'A' && data <= 'Z') {
		sprintf(s, "Prijal som znak %c\n",data);
		PutsUART2(s);
	}
	if (data >= 'a' && data <= 'z') {
		data += 'A'-'a';
		sprintf(s, "Prijal som znak %c\n",data);
		PutsUART2(s);
	}

	//if (data == 'A')
	//{
	//	PutsUART1("Prijal som znak A");
	//}
	//else
	if (data == 'T' || data == 't')
	{
		char buf[20];
		sprintf(buf, "t=%d\n",tick);
		PutsUART2(buf);
	}
}*/

void handlerxx(long long timestamp) {

}

/*void handleReceivedChar3(unsigned char data)
{
	char s[128];
	if (data >= 'A' && data <= 'Z') {
		sprintf(s, "Prijal som znak %c\n",data);
		PutsUART3(s);
	}
	if (data >= 'a' && data <= 'z') {
		data += 'A'-'a';
		sprintf(s, "Prijal som znak %c\n",data);
		PutsUART3(s);
	}

	//if (data == 'A')
	//{
	//	PutsUART1("Prijal som znak A");
	//}
	//else
	if (data == 'T' || data == 't')
	{
		char buf[20];
		sprintf(buf, "t=%d\n",tick);
		PutsUART3(buf);
	}
}*/

int adc_init()
{
	  //HwInit();

	  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE); //enable clock for GPIOA
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); //enable clock for ADC1

	  ADCPeripheralInit();

}

int main(void)
{
	char s[1024];
  	uint16_t x_raw = 0;
  	uint16_t z_raw = 0;
  	uint16_t t = 0;
  	int laststate = 0;
  	uint16_t pressure;
  	double pr1;
  	double pr2;

	/**
	 * Zapojenie
	 * UART1
	 * fialova	pa10	rx
	 * hneda	pa9		tx
	 *
	 * UART2
	 * fialova	pa3		rx
	 * hneda	pa2		tx
	 *
	 * UART3
	 * fialova	pc11	rx
	 * hneda	pc10	tx
	 */

	//initUSART1();	//configures all necessary to use USART1
	initUSART2();
	//initUSART3();
	RegisterCallbackUART2(&handleReceivedChar);	//register function to be called when interrupt occurs
	//RegisterCallbackUART2(&handleReceivedChar2);
	//RegisterCallbackUART3(&handleReceivedChar3);
	PutsUART2("Running USART1 xx...\n");			//write something to usart to see some effect
	//adc_init();
	//TIM_Config();
	//PWM_Config(100);
	//initBaseTimer();
	//registerBaseTimerHandler(&handlerxx);
	//initPWM_Output();
	//TIM3->CCR1 = 100;

	/*GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	//GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);*/
	initI2C1();
	initADS1100();

    while(1)
    {
    		t++;
    		if(t>400) t = 0;
    		//TIM9->CCR3 = intensity;
    		//TIM9->CCR4 = intensity;
    		//PWM_SetDC(1,intensity);
    		//PWM_SetDC(2,intensity);
    	    //z_raw = readADC(3, ADC1, ADC_SampleTime_96Cycles);
    	    //x_raw = readADC(1, ADC1, ADC_SampleTime_96Cycles);
    	    //TIM9->CCR1 = (x_raw * 100 / 4096);
    	    //TIM9->CCR2 = (x_raw * 100 / 4096);
    	    //TIM3->CCR1 =  (t<200 ? ( t<100 ? t:(200-t) ) : 0);
    	    //PWM_SetDC(1,(t<200 ? ( t<100 ? t:(200-t) ) : 0)); // modre
    	    //PWM_SetDC(2,(t>200 ? ( t<300 ? (t-200):(400-t)) :0));
    	    //PWM_SetDC(3,0);
    	    //PWM_SetDC(4,0);
    		//if((GPIOA->IDR & 0x01) == 1 && laststate == 0 ) {
    		//	intensity += 10;
    		//	if(intensity>100) intensity=0;
    		//}
    		//laststate = (GPIOA->IDR & 0x01);

    		readDataADS1100(&pressure);
    		pr1 = (double)pressure/(double)(6553.5); //hodnota->V 6553.5
    		pr2 = (pr1/3.0+0.095)*1000/0.009; // V->Tlak

    		//prevod (vout/3.0 + 0.095)/0.009; (_15-115 kPa)
    		sprintf(s,"d:%u %f %f\n",pressure,pr1, pr2);
    		PutsUART2(s);

    	    delay_us(10000);
    }

	return 0;
}

