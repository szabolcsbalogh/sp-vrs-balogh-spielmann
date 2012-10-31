#include "adc.h"
#include "mcu.h"

void ADC_IO_Init(GPIO_TypeDef* GPIOx, uint32_t GPIO_Pin) {
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOx, &GPIO_InitStructure);
}

void ADC_Enable(ADC_TypeDef* ADCx) {
  ADC_InitTypeDef ADC_InitStructure;
  ADC_CommonInitTypeDef ADC_CommonInitStructure;

  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;
  ADC_CommonInit(&ADC_CommonInitStructure);

  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfConversion = 1;

  ADC_Init(ADCx, &ADC_InitStructure);

  /* Enable the specified ADC*/
  ADC_Cmd(ADCx, ENABLE);
}

uint16_t readADC(uint8_t channel, ADC_TypeDef* ADCx, uint8_t SampleTime) {
  ADC_RegularChannelConfig(ADCx, channel, 1, SampleTime);
  // Start the conversion
  ADC_SoftwareStartConv(ADCx);
  // Wait until conversion completion
  while (ADC_GetFlagStatus(ADCx, ADC_FLAG_EOC) == RESET);
  // Get the conversion value
  return (ADC_GetConversionValue(ADCx));
}

void ADCPeripheralInit() {
  ADC_Enable(ADC1); //Enable ADC1 to do the conversion
  ADC_IO_Init(GPIOA, GPIO_Pin_1); //PA1 connects to Accelerometer Z-axis
  //ADC_IO_Init(GPIOA, GPIO_Pin_3); //PA2 connects to Accelerometer X-axis
}



