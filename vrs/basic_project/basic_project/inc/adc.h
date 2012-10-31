
#include "stm32l1xx.h"



  #define  EVAL_RESISTOR_R36      130    /* value of resistor R36 is 1.3 Ohm
                                           EVAL_RESISTOR_RATIO * 1.3 = 130  */
  #define  IDD_MEASUREMENT_PIN       GPIO_Pin_5
  #define  IDD_MEASUREMENT_GPIO_CLK  RCC_AHBPeriph_GPIOA
  #define  IDD_MEASUREMENT_GPIO      GPIOA
  #define  IDD_MEASUREMENT_ADC_CHANNEL  ADC_Channel_5
  #define APOSTROPHE_OFF APOSTROPHE_OFF


#define EVAL_RESISTOR_RATIO    100    /* R36 is multiplied by 100 */
#define EVAL_MAX9938_GAIN      50     /* Ampli-op gain = 50 */
#define ADC_CONVERT_RATIO      806    /* (3300mV / 4095)* 1000 */




/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
ADC_InitTypeDef ADC_InitStructure;
GPIO_InitTypeDef GPIO_InitStructure;
/*__IO uint16_t ADCdata = 0;
__IO uint32_t VDDmV = 0, IDDrunuA = 0;
*/

/* Private function prototypes -----------------------------------------------*/
void initADC(void);
