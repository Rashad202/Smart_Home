#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include<util/delay.h>

#include "../../MCAL/DIO/DIO_Interface.h"

#include"DCMOTOR_Interface.h"



void DCMOTOR_voidInit1(void)
{
	DIO_voidSetPinDirection(DCMOTOR_PORT1,DCMOTOR1_PIN1,DIO_OUTPUT);
	DIO_voidSetPinDirection(DCMOTOR_PORT1,DCMOTOR1_PIN2,DIO_OUTPUT);
}
void DCMOTOR_voidRotateCW1(void)
{
	DIO_voidSetPinValue(DCMOTOR_PORT1,DCMOTOR1_PIN1,DIO_HIGH);   //A
	DIO_voidSetPinValue(DCMOTOR_PORT1,DCMOTOR1_PIN2,DIO_LOW);    //B
}
void DCMOTOR_voidInit2(void)
{
	DIO_voidSetPinDirection(DCMOTOR_PORT2,DCMOTOR2_PIN1,DIO_OUTPUT);
	DIO_voidSetPinDirection(DCMOTOR_PORT2,DCMOTOR2_PIN2,DIO_OUTPUT);
}
void DCMOTOR_voidRotateCW2(void)
{
	DIO_voidSetPinValue(DCMOTOR_PORT2,DCMOTOR2_PIN1,DIO_HIGH);   //A
	DIO_voidSetPinValue(DCMOTOR_PORT2,DCMOTOR2_PIN2,DIO_LOW);    //B
}

void DCMOTOR_voidStop1(void)
{
	DIO_voidSetPinValue(DCMOTOR_PORT1,DCMOTOR1_PIN1,DIO_LOW);  //A
	DIO_voidSetPinValue(DCMOTOR_PORT1,DCMOTOR1_PIN2,DIO_LOW);  //B
}
void DCMOTOR_voidStop2(void)
{
	DIO_voidSetPinValue(DCMOTOR_PORT2,DCMOTOR2_PIN1,DIO_LOW);  //A
	DIO_voidSetPinValue(DCMOTOR_PORT2,DCMOTOR2_PIN2,DIO_LOW);  //B
}
