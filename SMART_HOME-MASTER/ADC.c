#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <avr/io.h>
#include "ADC.h"
void ADC_voidInit(void){
	SET_BIT(ADMUX,6); // AVCC
	SET_BIT(ADCSRA,ADEN); // ENABLE ADC
	ADCSRA |= 0b111; // prescaler 128 > freq = 125Khz
}
u16  ADC_u16GetDigitalValue(u8 Copy_u8ChannelNum){
	ADMUX &= 0b11100000;
	ADMUX |= Copy_u8ChannelNum;
	SET_BIT(ADCSRA,ADSC); // Start conversion
	while(GET_BIT(ADCSRA, ADSC) == 1){}
	//while(READBIT(ADCSRA, ADIF) == 0){}
	//SETBIT(ADCSRA,ADIF);

	return ADC;
}
