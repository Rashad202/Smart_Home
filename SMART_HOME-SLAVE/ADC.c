#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <avr/io.h>
#include "ADC.h"


void ADC_voidInit (void)
{
	/* Select Vref = AVCC = 2.56V */
	CLR_BIT(ADMUX , REFS1);
	SET_BIT(ADMUX , REFS0);
	/* 	2- Select Right Adjust*/
	CLR_BIT(ADMUX , ADLAR);
	/* 	4- select CLK 'From 50 KHZ to 200 KHZ'---> Input CLK = 8 MHZ
	====> So We will select CLK / 64 */
	SET_BIT(ADCSRA , ADPS2);
	SET_BIT(ADCSRA , ADPS1);
	CLR_BIT(ADCSRA , ADPS0);
	/* 	1- Enable ADC*/
	SET_BIT(ADCSRA , ADEN);
}

u16  ADC_u16GetDigitalValue(u8 Copy_u8ChannelNum)
{
	u16 Local_u16ADCDigitalValue ;
	/*Clear MUX4......0*/
	ADMUX &= 0b11100000 ;
	/*Select Channel*/
	ADMUX |= Copy_u8ChannelNum ;
	/*Start conversion*/
	SET_BIT(ADCSRA , ADSC);
	/*Wait flag = 1*/
	while (GET_BIT(ADCSRA , ADIF) == 0);
	/*Clear flag*/
	SET_BIT(ADCSRA , ADIF);
	/* Read the digital value from ADC_REG ==> "High & Low" */
	Local_u16ADCDigitalValue = ADC_REG ;
	return Local_u16ADCDigitalValue ;
}
