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
#include "timer.h"
#include "spi.h"
#include "mcp6s92.h"

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

	  ADC_Enable(ADC1); //Enable ADC1 to do the conversion
	  ADC_IO_Init(GPIOA, GPIO_Pin_1); //PA1 connects to Accelerometer Z-axis

}

int main(void)
{
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

	char s[1024];
  	uint16_t x_raw = 0;
  	double x_real = 0.0;
  	int gain_id = 0; // max 7
  	int gains[] = {1,2,4,5,8,10,16,32};
  	int gains_spi[] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07};

	initUSART2();
	RegisterCallbackUART2(&handleReceivedChar);
	PutsUART2("Running USART1 xx...\n");
	initBaseTimer();
	registerBaseTimerHandler(&handlerxx);

	adc_init();
	//initBaseTimer();
	initSPI2();
	initCS_Pin();
	device_Unselect();
	mcp6s92_setings(CMD_MCP6S92_WRITE_TO_REG,MCP6S92_CHANNEL_REG_ADDRESS,CHANNEL_0);

    while(1)
    {

    		mcp6s92_setings(CMD_MCP6S92_WRITE_TO_REG,MCP6S92_GAIN_REG_ADDRESS,gains_spi[gain_id]);
    		x_raw = readADC(1, ADC1, ADC_SampleTime_96Cycles);

    	    x_real = x_raw / 21845.0 / (double)gains[gain_id];
    		if(x_raw > 0.9*65535) {
    			//switch gain up
    			if(gain_id>0) gain_id--;
    			//PutsUART2("GD\n");
    		} else
    		if(x_raw < 0.40*65535) {
    			//switch gain down
    			//PutsUART2("GU\n");
    			if(gain_id<7) gain_id++;
    		}

    		sprintf(s,"U = %f V, raw = %d, gain=%d\n",x_real, x_raw, gains[gain_id]);
    		PutsUART2(s);

    	    delay_us(100000);
    }

	return 0;
}

