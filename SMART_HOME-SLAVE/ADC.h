
#ifndef ADC_H_
#define ADC_H_

#define 	ADC_REG		*(( volatile u16*)0x24)	/*Address to two bytes "LOW & HIGH"*/

void ADC_voidInit (void) ;
u16  ADC_u16GetDigitalValue(u8 Copy_u8ChannelNum);


#define channel_0		0
#define channel_1		1
#define channel_2		2
#define channel_3		3
#define channel_4		4
#define channel_5		5
#define channel_6		6
#define channel_7		7


#endif /* ADC_H_ */
