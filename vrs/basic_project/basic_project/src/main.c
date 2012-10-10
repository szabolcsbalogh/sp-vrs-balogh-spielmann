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
	char s[128];
	if (data >= 'A' && data <= 'Z') {
		sprintf(s, "Prijal som znak %c\n",data);
		PutsUART1(s);
	}
	if (data >= 'a' && data <= 'z') {
		data += 'A'-'a';
		sprintf(s, "Prijal som znak %c\n",data);
		PutsUART1(s);
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
		PutsUART1(buf);
	}
}

void handleReceivedChar2(unsigned char data)
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
}

void handleReceivedChar3(unsigned char data)
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

	//initUSART1();	//configures all necessary to use USART1
	//initUSART2();
	initUSART3();
	initADC();

	RegisterCallbackUART1(&handleReceivedChar);	//register function to be called when interrupt occurs
	RegisterCallbackUART2(&handleReceivedChar2);
	RegisterCallbackUART3(&handleReceivedChar3);
	//PutsUART1("Running USART1...\n");			//write something to usart to see some effect

    while(1)
    {
    	tick++;
    	//PutsUART1("Running USART1...\n");
    	//PutsUART2("Running USART2...\n");
    	PutsUART3("Running USART3...\n");
    }

	return 0;
}

