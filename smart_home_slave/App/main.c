/*
 * main.c
 *
 *  Created on: 10 Sep 2023
 *      Author: Rashad
 */
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
/* Include Header Files From MCAL Layer */
#include "../MCAL/DIO/DIO_Interface.h"
#include "../MCAL/ADC/ADC_Interface.h"
#include"../MCAL/TIMERS/TIMER1/TIMER1_Interface.h"
#include"../MCAL/GIE/GIE_Interface.h"
#include"../MCAL/USART/USART_Interface.h"
/* Include Header Files From HAL Layer */
#include "../HAL/LCD/LCD_Interface.h"
#include "../HAL/DCMOTOR/DCMOTOR_Interface.h"
#include <avr/delay.h>


void StartProgram				(void);
void UART_CallBack				(u8 Data);
void Open_Fan 			 		(u8 Copy_u32Number);
void Open_Light			 		(u8 Copy_u32Number);
void Close_Fan 					(u8 Copy_u32Number);
void Close_Light			 	(u8 Copy_u32Number);
void Open_TV 				 	(void);
void Open_Oven	 			 	(void);
void Close_TV 			 		(void);
void Close_Oven 			 	(void);
void Close_Condition 			(void);
void Open_Condition 		 	(void);
void Open_OutLight 			 	(void);
void Close_OutLight		 		(void);
void Open_Pump 	  			 	(void);
void Close_Pump 		 		(void);

u8 ExitAutoData = 0 ;
void main()
{
	USART_voidInit ();
	LCD_voidInit ();
	ADC_voidInit ();
	DCMOTOR_voidInit1();
	DCMOTOR_voidInit2();



	u8 Access = 0;
	u8 ActuatorData = 0 ;
	u8 TVData = 0 ;
	u8 ModeData = 0 ;
	u8 LightData = 0 ;
	u8 FanData = 0 ;
	u8 OvenData = 0 ;
	u16 Digital_Signal_Temp=0;
	u16 Digital_Signal_LDR=0;
	u16 Analog_Signal_Temp=0;
	u16 Analog_Signal_LDR=0;
	u16 Temp_Value=0;


	DIO_voidSetPinDirection(DIO_PORTA,DIO_PIN2,DIO_INPUT);
	DIO_voidSetPinDirection(DIO_PORTA,DIO_PIN3,DIO_OUTPUT);
	DIO_voidSetPinDirection(DIO_PORTA,DIO_PIN4,DIO_OUTPUT);

	DIO_voidSetPinDirection(DIO_PORTC,DIO_PIN2,DIO_OUTPUT);
	DIO_voidSetPinDirection(DIO_PORTC,DIO_PIN3,DIO_OUTPUT);
	DIO_voidSetPinDirection(DIO_PORTC,DIO_PIN4,DIO_OUTPUT);
	DIO_voidSetPinDirection(DIO_PORTC,DIO_PIN5,DIO_OUTPUT);
	DIO_voidSetPinDirection(DIO_PORTC,DIO_PIN6,DIO_OUTPUT);
	DIO_voidSetPinDirection(DIO_PORTC,DIO_PIN7,DIO_OUTPUT);

	DIO_voidSetPinDirection(DIO_PORTD,DIO_PIN2,DIO_OUTPUT);
	DIO_voidSetPinDirection(DIO_PORTD,DIO_PIN3,DIO_OUTPUT);
	DIO_voidSetPinDirection(DIO_PORTD,DIO_PIN6,DIO_OUTPUT);
	DIO_voidSetPinDirection(DIO_PORTD,DIO_PIN7,DIO_OUTPUT);



		StartProgram();
		USART_voidSendData('x');
		USART_voidRecieveData (&Access);
		if( Access == 'Z' )
		{
			LCD_voidClearLine(0);
			LCD_voidClearLine(1);
			LCD_voidGoTo_XY ( 0 , 0 );
			LCD_voidWriteString ("   Welome To ");
			LCD_voidGoTo_XY (1,0);
			LCD_voidWriteString ("   You Home :)");
			while(1)
			{
				USART_voidRecieveData (&ModeData);
				if( ModeData == '1' )
				{
					LCD_voidClearLine(0);
					LCD_voidClearLine(1);
					LCD_voidGoTo_XY ( 0 , 0 );
					LCD_voidWriteString (" Room1 ");
					LCD_voidGoTo_XY ( 1 , 0 );
					LCD_voidWriteString ("Door is opened  ");
					DIO_voidSetPinValue(DIO_PORTD,DIO_PIN3,DIO_HIGH);
					_delay_ms(400);
					DIO_voidSetPinValue(DIO_PORTD,DIO_PIN3,DIO_LOW);
					LCD_voidClearLine(0);
					LCD_voidClearLine(1);

					while(1)
					{
						USART_voidRecieveData (&ActuatorData);

						/* Control Light */
						 if ( ActuatorData == 'L')
						{
							USART_voidRecieveData (&LightData);
							if ( LightData == '1' )
							{
								Open_Light(1);
							}
							else if ( LightData == '0' )
							{
								Close_Light(1);
							}
						}


						/* Control Fan */
						else if ( ActuatorData == 'F')
						{
							USART_voidRecieveData (&FanData);
							if ( FanData == '1' )
							{
								Open_Fan(1);
							}
							else if ( FanData == '0' )
							{
								Close_Fan(1);
							}
						}


						/* Exit from Manual Mode */
						else if ( ActuatorData == '#')
						{

							ModeData = 0 ;
							ActuatorData = 0 ;
							Close_Light(1);
							Close_Fan(1);
							LCD_voidClearLine(0);
							LCD_voidClearLine(1);
							break;
						}

					}
				}
				else if( ModeData == '2' )
				{
					LCD_voidClearLine(0);
					LCD_voidClearLine(1);
					LCD_voidGoTo_XY ( 0 , 0 );
					LCD_voidWriteString (" Room2 ");
					LCD_voidGoTo_XY ( 1 , 0 );
					LCD_voidWriteString ("Door is opened  ");
					DIO_voidSetPinValue(DIO_PORTA,DIO_PIN4,DIO_HIGH);
					_delay_ms(400);
					DIO_voidSetPinValue(DIO_PORTA,DIO_PIN4,DIO_LOW);
					LCD_voidClearLine(0);
					LCD_voidClearLine(1);

					while(1)
					{
						USART_voidRecieveData (&ActuatorData);

						/* Control Light */
						 if ( ActuatorData == 'L')
						{
							USART_voidRecieveData (&LightData);
							if ( LightData == '1' )
							{
								Open_Light(2);
							}
							else if ( LightData == '0' )
							{
								Close_Light(2);
							}
						}


						/* Control Fan */
						else if ( ActuatorData == 'F')
						{
							USART_voidRecieveData (&FanData);
							if ( FanData == '1' )
							{
								Open_Fan(2);
							}
							else if ( FanData == '0' )
							{
								Close_Fan(2);
							}
						}


						/* Exit from Manual Mode */
						else if ( ActuatorData == '#')
						{

							ModeData = 0 ;
							ActuatorData = 0 ;
							Close_Light(2);
							Close_Fan(2);
							LCD_voidClearLine(0);
							LCD_voidClearLine(1);
							break;
						}

					}
				}


				else if( ModeData == '3' )
				{
					LCD_voidClearLine(0);
					LCD_voidClearLine(1);
					LCD_voidGoTo_XY ( 0 , 0 );
					LCD_voidWriteString (" kitchen ");
					LCD_voidGoTo_XY ( 1 , 0 );
					LCD_voidWriteString ("Door is opened  ");
					DIO_voidSetPinValue(DIO_PORTD,DIO_PIN7,DIO_HIGH);
					_delay_ms(400);
					DIO_voidSetPinValue(DIO_PORTD,DIO_PIN7,DIO_LOW);
					LCD_voidClearLine(0);
					LCD_voidClearLine(1);

					while(1)
					{
						USART_voidRecieveData (&ActuatorData);

						/* Control Light */
						 if ( ActuatorData == 'L')
						{
							USART_voidRecieveData (&LightData);
							if ( LightData == '1' )
							{
								Open_Light(3);
							}
							else if ( LightData == '0' )
							{
								Close_Light(3);
							}
						}


						/* Control Fan */
						else if ( ActuatorData == 'O')
						{
							USART_voidRecieveData (&OvenData);
							if ( OvenData == '1' )
							{
								Open_Oven();
							}
							else if ( OvenData == '0' )
							{
								Close_Oven();
							}
						}


						/* Exit from Manual Mode */
						else if ( ActuatorData == '#')
						{

							ModeData = 0 ;
							ActuatorData = 0 ;
							Close_Light(3);
							Close_Oven();
							LCD_voidClearLine(0);
							LCD_voidClearLine(1);
							break;
						}

					}
				}
				else if( ModeData == '4' )
				{
					LCD_voidClearLine(0);
					LCD_voidClearLine(1);
					LCD_voidGoTo_XY ( 0 , 0 );
					LCD_voidWriteString (" Reception ");
					LCD_voidGoTo_XY ( 1 , 0 );
					LCD_voidWriteString ("Your Welcome... ");
					_delay_ms(250);
					LCD_voidClearLine(0);
					LCD_voidClearLine(1);

					while(1)
					{
						USART_voidRecieveData (&ActuatorData);

						/* Control Light */
						 if ( ActuatorData == 'L')
						{
							USART_voidRecieveData (&LightData);
							if ( LightData == '1' )
							{
								Open_Light(4);
							}
							else if ( LightData == '0' )
							{
								Close_Light(4);
							}
						}


						/* Control TV */
						else if ( ActuatorData == 'T')
						{
							USART_voidRecieveData (&TVData);
							if ( TVData == '1' )
							{
								Open_TV();
							}
							else if ( TVData == '0' )
							{
								Close_TV();
							}
						}


						/* Exit from Manual Mode */
						else if ( ActuatorData == '#')
						{
							LCD_voidClearDisplay();
							ModeData = 0 ;
							ActuatorData = 0 ;
							Close_Light(4);
							Close_TV();
							LCD_voidClearLine(0);
							LCD_voidClearLine(1);
							break;
						}

					}
				}
				else if ( ModeData == '5' )
				{
					USART_voidAsyncRecieveData (&UART_CallBack);
					LCD_voidClearLine(0);
					LCD_voidClearLine(1);
					LCD_voidGoTo_XY ( 0 , 0 );
					LCD_voidWriteString (" Auto Mode ");
					_delay_ms(250);
					LCD_voidClearLine(0);
					LCD_voidClearLine(1);
					while(1)
					{
					Digital_Signal_Temp =  ADC_u16ReadSynchronus ( ADC0 ) ;
					Analog_Signal_Temp = (Digital_Signal_Temp * 5000UL ) /1024 ;   // 5000 mv   to read Analog_Signal by mv.
					Temp_Value = Analog_Signal_Temp / 10 ;
					if (Temp_Value > 25)
					{
						Open_Condition();
					}
					else
					{
						Close_Condition();
					}

					/* Light System */
					Digital_Signal_LDR =  ADC_u16ReadSynchronus ( ADC1 ) ;
					Analog_Signal_LDR = (Digital_Signal_LDR * 5000UL ) /1024 ;   // 5000 mv   to read Analog_Signal by mv.

					if (Analog_Signal_LDR > 2400)
					{
						Open_OutLight();
					}
					else
					{
						Close_OutLight();
					}


					/* Gas System*/
					DIO_voidSetPinValue(DIO_PORTA,DIO_PIN2,DIO_HIGH);
					if(DIO_u8GetPinValue(DIO_PORTA,DIO_PIN2))
					{
						LCD_voidClearDisplay();
						LCD_voidWriteString(" Fire Fire !!!");
						Open_Pump();
						_delay_ms(150);

					}
					else
					{
						Close_Pump();
					}

					}

				}
			}





		}

		else if ( Access == 'N')
		{
			LCD_voidClearLine(0);
			LCD_voidClearLine(1);
			LCD_voidGoTo_XY (0,3);
			LCD_voidWriteString ("7aramy !!");
			LCD_voidGoTo_XY (1,0);
			LCD_voidWriteString ("Restart System..");
		}


}


/* ------------------------------------------------------------- */
/* ------------------------------------------------------------- */
void StartProgram (void)
{
	LCD_voidClearLine(0);
	LCD_voidClearLine(1);
	LCD_voidGoTo_XY (0,1);
	LCD_voidWriteString (" Welcome To MY");
	LCD_voidGoTo_XY (1,0);
	LCD_voidWriteString ("  Smart Home  ");
}
/* ------------------------------------------------------------- */

void UART_CallBack (u8 Data)
{
	ExitAutoData = Data ;
}
/* ------------------------------------------------------------- */
void Open_Light (u8 CopyNumber)
{

	switch(CopyNumber)
	{
	case 1:
			LCD_voidGoTo_XY ( 0 , 0 );
			DIO_voidSetPinValue(DIO_PORTC,DIO_PIN3,DIO_HIGH);
			LCD_voidWriteString ("Light-ON ");
			break;
	case 2:
			LCD_voidGoTo_XY ( 0 , 0 );
			DIO_voidSetPinValue(DIO_PORTC,DIO_PIN4,DIO_HIGH);
			LCD_voidWriteString ("Light-ON ");
			break;
	case 3:
			LCD_voidGoTo_XY ( 0 , 0 );
			DIO_voidSetPinValue(DIO_PORTC,DIO_PIN5,DIO_HIGH);
			LCD_voidWriteString ("Light-ON ");
			break;
	case 4:
			LCD_voidGoTo_XY ( 0 , 0 );
			DIO_voidSetPinValue(DIO_PORTC,DIO_PIN6,DIO_HIGH);
			LCD_voidWriteString ("Light-ON ");
			break;

	}

}
/* ------------------------------------------------------------- */
void Close_Light (u8 CopyNumber)
{

	switch(CopyNumber)
	{
	case 1:
			LCD_voidGoTo_XY ( 0 , 0 );
			DIO_voidSetPinValue(DIO_PORTC,DIO_PIN3,DIO_LOW);
			LCD_voidWriteString ("Light-OFF");
			break;
	case 2:
			LCD_voidGoTo_XY ( 0 , 0 );
			DIO_voidSetPinValue(DIO_PORTC,DIO_PIN4,DIO_LOW);
			LCD_voidWriteString ("Light-OFF");
			break;
	case 3:
			LCD_voidGoTo_XY ( 0 , 0 );
			DIO_voidSetPinValue(DIO_PORTC,DIO_PIN5,DIO_LOW);
			LCD_voidWriteString ("Light-OFF");
			break;
	case 4:
			LCD_voidGoTo_XY ( 0 , 0 );
			DIO_voidSetPinValue(DIO_PORTC,DIO_PIN6,DIO_LOW);
			LCD_voidWriteString ("Light-OFF");
			break;

	}

}
/* ------------------------------------------------------------- */
void Open_Fan (u8 CopyNumber)
{

		switch(CopyNumber)
		{

		case 1:
				LCD_voidGoTo_XY ( 1 , 0 );
				DCMOTOR_voidRotateCW1();
				LCD_voidWriteString ("Fan-ON     ");
				break;
		case 2:
				LCD_voidGoTo_XY ( 1 , 0 );
				DCMOTOR_voidRotateCW2();
				LCD_voidWriteString ("Fan-ON   ");
				break;

		}

}
/* ------------------------------------------------------------- */
void Close_Fan (u8 CopyNumber)
{

		switch(CopyNumber)
		{

		case 1:
				LCD_voidGoTo_XY ( 1 , 0 );
				DCMOTOR_voidStop1();
				LCD_voidWriteString ("Fan-OFF    ");
				break;
		case 2:
				LCD_voidGoTo_XY ( 1 , 0 );
				DCMOTOR_voidStop2();
				LCD_voidWriteString ("Fan-OFF    ");
				break;

		}

}
/* ------------------------------------------------------------- */
void Open_OutLight (void)
{
	LCD_voidGoTo_XY ( 1 , 0 );
	LCD_voidWriteString ("OutLight-ON  ");
	DIO_voidSetPinValue(DIO_PORTA,DIO_PIN3,DIO_HIGH);
}
/* ------------------------------------------------------------- */
void Close_OutLight (void)
{
	LCD_voidGoTo_XY ( 1 , 0 );
	LCD_voidWriteString ("OutLight-OFF  ");
	DIO_voidSetPinValue(DIO_PORTA,DIO_PIN3,DIO_LOW);
}
/* ------------------------------------------------------------- */
void Open_Condition (void)
{
	LCD_voidGoTo_XY ( 0 , 0 );
	LCD_voidWriteString ("AIRCONDITION-ON  ");
	DIO_voidSetPinValue(DIO_PORTC,DIO_PIN2,DIO_HIGH);
}
/* ------------------------------------------------------------- */
void Close_Condition (void)
{
	LCD_voidGoTo_XY ( 0 , 0 );
	LCD_voidWriteString ("AIRCONDITION-OFF  ");
	DIO_voidSetPinValue(DIO_PORTC,DIO_PIN2,DIO_LOW);
}
/* ------------------------------------------------------------- */
void Open_Oven (void)
{
	LCD_voidGoTo_XY ( 1 , 0 );
	LCD_voidWriteString ("Oven-ON    ");
	DIO_voidSetPinValue(DIO_PORTD,DIO_PIN2,DIO_HIGH);
}
/* ------------------------------------------------------------- */
void Close_Oven (void)
{
	LCD_voidGoTo_XY ( 1 , 0 );
	LCD_voidWriteString ("Oven-OFF   ");
	DIO_voidSetPinValue(DIO_PORTD,DIO_PIN2,DIO_LOW);
}
/* ------------------------------------------------------------- */
void Open_TV (void)
{
	LCD_voidGoTo_XY ( 1 , 0 );
	LCD_voidWriteString ("TV-ON    ");
	DIO_voidSetPinValue(DIO_PORTD,DIO_PIN6,DIO_HIGH);
}
/* ------------------------------------------------------------- */
void Close_TV (void)
{
	LCD_voidGoTo_XY ( 1 , 0 );
	LCD_voidWriteString ("TV-OFF   ");
	DIO_voidSetPinValue(DIO_PORTD,DIO_PIN6,DIO_LOW);
}
/* ------------------------------------------------------------- */
void Open_Pump (void)
{
	LCD_voidGoTo_XY ( 1 , 0 );
	LCD_voidWriteString ("Water pump ON   ");
	DIO_voidSetPinValue(DIO_PORTC,DIO_PIN7,DIO_HIGH);
}
/* ------------------------------------------------------------- */
void Close_Pump (void)
{
	DIO_voidSetPinValue(DIO_PORTC,DIO_PIN7,DIO_LOW);
}
