/*
 * adc.h
 *
 *  Created on: Oct 10, 2012
 *      Author: student
 */
#include "mcu.h"

#ifndef ADC_H_
#define ADC_H_

void ADC_IO_Init(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin);

void ADC_Enable(ADC_TypeDef* ADCx);

uint16_t readADC(uint8_t channel, ADC_TypeDef* ADCx, uint8_t SampleTime) ;

void ADCPeripheralInit();



#endif /* ADC_H_ */
