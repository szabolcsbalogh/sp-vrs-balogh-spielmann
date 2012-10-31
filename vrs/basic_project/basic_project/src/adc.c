/**
  * @brief  Configures the ADC1 channel5.
  * @param  None
  * @retval None
  */
#include "adc.h"
#include "mcu.h"
void initADC()
{
  /* Enable The HSI (16Mhz) */
  RCC_HSICmd(ENABLE);

  /* Enable the GPIOF or GPIOA Clock */
  RCC_AHBPeriphClockCmd(IDD_MEASUREMENT_GPIO_CLK, ENABLE);
  /* Configure PF.11 (ADC Channel11) or PA.05 (ADC Channe5) in analog mode */
  GPIO_InitStructure.GPIO_Pin =  IDD_MEASUREMENT_PIN;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_Init(IDD_MEASUREMENT_GPIO, &GPIO_InitStructure);

  /* Check that HSI oscillator is ready */
  while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);

  /* ADC1 Configuration ------------------------------------------------------*/

  /* Enable ADC1 clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);



  ADC_StructInit(&ADC_InitStructure);
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfConversion = 1;
  ADC_Init(ADC1, &ADC_InitStructure);

  /* ADC1 regular channel5 or channel1 configuration */
  ADC_RegularChannelConfig(ADC1, IDD_MEASUREMENT_ADC_CHANNEL, 1, ADC_SampleTime_192Cycles);

  /* Define delay between ADC1 conversions */
  ADC_DelaySelectionConfig(ADC1, ADC_DelayLength_Freeze);

  /* Enable ADC1 Power Down during Delay */
  ADC_PowerDownCmd(ADC1, ADC_PowerDown_Idle_Delay, ENABLE);

  /* Enable ADC1 */
  ADC_Cmd(ADC1, ENABLE);

  /* Wait until ADC1 ON status */
  while (ADC_GetFlagStatus(ADC1, ADC_FLAG_ADONS) == RESET)
  {
  }

  /* Start ADC1 Software Conversion */
  ADC_SoftwareStartConv(ADC1);

  /* Wait until ADC Channel 5 or 1 end of conversion */
  while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET)
  {
  }
}
