#ifndef DCMOTOR_INTERFACE_H
#define DCMOTOR_INTERFACE_H


#define DCMOTOR_PORT1      DIO_PORTC
#define DCMOTOR_PORT2      DIO_PORTD

#define DCMOTOR1_PIN1      DIO_PIN0
#define DCMOTOR1_PIN2      DIO_PIN1
#define DCMOTOR2_PIN1      DIO_PIN4
#define DCMOTOR2_PIN2      DIO_PIN5

void DCMOTOR_voidInit1(void);
void DCMOTOR_voidInit2(void);
void DCMOTOR_voidRotateCW1(void);
void DCMOTOR_voidRotateCW2(void);

void DCMOTOR_voidStop1(void);
void DCMOTOR_voidStop2(void);

#endif
