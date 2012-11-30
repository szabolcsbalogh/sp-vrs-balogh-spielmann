#include "spi.h"
#include "mcu.h"

enum eDisplayCommand
{
	DISPLAY_ON = 0xAF,
	DISPLAY_OFF = 0xAE,

};

enum eDisplayPin
{
	RW_WR = GPIO_Pin_0,
	A0 = GPIO_Pin_1,
	DISPLAY_RESET = GPIO_Pin_2,
	CS = GPIO_Pin_3,
};

void display_init(void);
void display_on(void);
void display_pin_init(void);


void a0_low(void);
void a0_high(void);
void RW_WR_low(void);
void RW_WR_high(void);
void Reset_low(void);
void Reset_high(void);
