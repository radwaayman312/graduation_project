#include "TYPES.h"
#include "MACROS.h"
#include"SYSTICK_INTERFACE.h"
#include"DELAY_INTERFACE.h"
#include "ADC_interface.h"
#include "ADC_private.h"
#include "ADC_config.h"

/****************/
void ADC1_voidInit(void)
{

	/* Configuring SMPR2 */
	ADC1 -> SMPR[2] = 0x0038;
	/*********************/
	/* Configuring SQR3 */
	ADC1 -> SQR[3] = 0x0001;
	/*********************/
	ADC1 -> CR2 = 0x0003;
	_delay_ms(100);
	ADC1 -> CR2 = 0x0003;
	ADC1 -> CR2=0x0007;
}

u32 IR(void)
{
	u32 Reading=0;
	ADC1->CR2|=0x40000000;
	while(!(ADC1->SR&2));
	Reading=ADC1->DR;
	_delay_ms(50);
	return Reading;
}

