/*
 * main.c
 *
 *  Created on: 4 Sep 2023
 *      Author: Rashad
 */


#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <avr/io.h>
#include <avr/delay.h>
//		   MCAL
#include "DIO_Interface.h"
#include "UART.h"
#include "GIE_Interface.h"
#include "ADC.h"
#include "LCD_Interface.h"
#include "SERVOMOTOR_Interface.h"

void StartProgram            (void);
void OpenLight               (void);
void CloseLight 			 (void);
void OpenFan 				 (void);
void CloseFan 				 (void);
void OpenLight2               (void);
void CloseLight2 			 (void);
void OpenFan2 				 (void);
void CloseFan2 				 (void);
void OpenWindow 			 (void);
void CloseWindow 			 (void);
void OpenTV 				 (void);
void CloseTV 	 			 (void);
u16 ADC_vSetFanAndCooler 	 (void);

u8 ExitAutoData = 0 ;

int main(void)
{

	LCD_voidInit();
	UART_voidInit();
	ADC_voidInit();
	DIO_voidSetPinDirection(DIO_PORTA,DIO_PIN3,DIO_OUTPUT);
	DIO_voidSetPinDirection(DIO_PORTA,DIO_PIN4,DIO_OUTPUT);

	DIO_voidSetPinDirection(DIO_PORTD,DIO_PIN3,DIO_OUTPUT);
	DIO_voidSetPinDirection(DIO_PORTD,DIO_PIN4,DIO_OUTPUT);
	DIO_voidSetPinDirection(DIO_PORTD,DIO_PIN5,DIO_OUTPUT);
	DIO_voidSetPinDirection(DIO_PORTD,DIO_PIN6,DIO_OUTPUT);
	u8 Access = 0;
	u8 ActuatorData = 0 ;
	u8 ADC_read = 0 ;
	u8 ModeData = 0 ;
	u8 LightData = 0 ;
	u8 FanData = 0 ;
	u8 TVData = 0 ;

	StartProgram();
	Access= UART_voidReciveData ();

	if( Access == 'Z' )
	{

		LCD_voidSendCommand(LCD_CLEAR);

		LCD_voidSetLocation ( 1 , 0 );
		LCD_voidSendString ("   Welome To ");
		LCD_voidSetLocation (2,0);
		LCD_voidSendString ("   My Home :)");
		while(1)
		{

			ModeData= UART_voidReciveData ();

			if ( ModeData == 'R')
			{
				LCD_voidSendCommand(LCD_CLEAR);

				LCD_voidSetLocation ( 1 , 0 );
				LCD_voidSendString (" Room1 ");
				_delay_ms(800);
				LCD_voidSendCommand(LCD_CLEAR);
				LCD_voidSetLocation ( 1 , 7 );
				LCD_voidSendChar('/');
				LCD_voidSetLocation ( 2 , 7 );
				LCD_voidSendChar('/');


				while(1)
				{
					ActuatorData= UART_voidReciveData ();
					/*---------------------------------------------------------------------------------------------------------------------*/

					/* Control Light */
					if ( ActuatorData == 'L')
					{
						LightData=UART_voidReciveData ();
						if ( LightData == '1' )
						{
							OpenLight();
						}
						else if ( LightData == '0' )
						{
							CloseLight();
						}
					}
					/*---------------------------------------------------------------------------------------------------------------------*/
					/* Control Fan */
					else if ( ActuatorData == 'F')
					{
						FanData=UART_voidReciveData ();
						if ( FanData == '1' )
						{
							OpenFan();

						}
						else if ( FanData == '0' )
						{
							CloseFan();

						}
					}

					/*---------------------------------------------------------------------------------------------------------------------*/
					/* Control TV */
					else if ( ActuatorData == 'T')
					{
						TVData=UART_voidReciveData ();
						if ( TVData == '1' )
						{
							OpenTV();
						}
						else if ( TVData == '0' )
						{
							CloseTV();
						}
					}
					/*---------------------------------------------------------------------------------------------------------------------*/
					/* Exit from Manual Mode */
					else if ( ActuatorData == '#')
					{
						LCD_voidSendCommand(LCD_CLEAR);
						ModeData = 0 ;
						ActuatorData = 0 ;
						CloseLight();
						CloseFan();
						CloseWindow();
						LCD_voidSendCommand(LCD_CLEAR);
						break;
					}



				}
			}
			else if ( ModeData =='r')
			{
			LCD_voidSendCommand(LCD_CLEAR);

				LCD_voidSetLocation ( 1 , 0 );
				LCD_voidSendString (" Room2 ");
				_delay_ms(800);
				LCD_voidSendCommand(LCD_CLEAR);
				CloseWindow();
				while(1)
				{
					if ((ADC_vSetFanAndCooler() > 20))//fan on AC off
						{
							OpenFan2();
							CloseWindow();
						}
						else if (ADC_vSetFanAndCooler() <= 20)//fan off AC on
						{
							CloseFan2();
							OpenWindow();
						}
					ActuatorData= UART_voidReciveData ();


					/*---------------------------------------------------------------------------------------------------------------------*/
					/* Control Light */
					if ( ActuatorData == 'l')
					{
						LightData=UART_voidReciveData ();
						if ( LightData == '1' )
						{
							OpenLight2();
						}
						else if ( LightData == '0' )
						{
							CloseLight2();
						}
					}
					/*---------------------------------------------------------------------------------------------------------------------*/
					/* Control Fan */
					else if ( ActuatorData == 'f')
					{
						FanData=UART_voidReciveData ();
						if ( FanData == '1' )
						{
							if ((ADC_vSetFanAndCooler() > 20))//fan on AC off
							{
								OpenFan2();
								CloseWindow();
							}
							else if (ADC_vSetFanAndCooler() <= 20)//fan off AC on
							{
								CloseFan2();
								OpenWindow();
							}
						}
						else if ( FanData == '0' )
						{
							!ADC_vSetFanAndCooler();
							CloseFan2();
							OpenWindow();
						}
					}
					/*---------------------------------------------------------------------------------------------------------------------*/

					/*---------------------------------------------------------------------------------------------------------------------*/
					/* Exit from  Mode */
					else if ( ActuatorData == '#')
					{
						LCD_voidSendCommand(LCD_CLEAR);
						ModeData = 0 ;
						ActuatorData = 0 ;
						CloseLight();
						CloseFan();
						CloseWindow();
						LCD_voidSendCommand(LCD_CLEAR);
						break;
					}

				}
			}


		}
	}
	else if ( Access == 'N')
	{
		LCD_voidSendCommand(LCD_CLEAR);

		LCD_voidSetLocation (1,3);
		LCD_voidSendString ("7aramy !!");
		LCD_voidSetLocation (2,0);
		LCD_voidSendString ("Restart System..");
	}

	return 0;
}

/*----------------------------------------------------------------------------------------------------------------------*/

void StartProgram (void)
{
	LCD_voidSendCommand(LCD_CLEAR);
	LCD_voidSetLocation (1,1);
	LCD_voidSendString (" Welcome To MY");
	LCD_voidSetLocation (2,0);
	LCD_voidSendString ("  Smart Home :) ");
}

/*----------------------------------------------------------------------------------------------------------------------*/

void OpenLight (void)
{

	LCD_voidSetLocation ( 1 , 8 );
	LCD_voidSendString ("LED-ON");
	DIO_voidSetPinValue(DIO_PORTA,DIO_PIN3,DIO_HIGH);


}
/*----------------------------------------------------------------------------------------------------------------------*/

void CloseLight (void)
{
	LCD_voidSetLocation ( 1 , 8 );
	LCD_voidSendString ("LED-OFF");
	DIO_voidSetPinValue(DIO_PORTA,DIO_PIN3,DIO_LOW);


}
/*----------------------------------------------------------------------------------------------------------------------*/

void OpenFan (void)
{

	LCD_voidSetLocation ( 2 , 0 );
	LCD_voidSendString ("Fan-ON");
	DIO_voidSetPinValue(DIO_PORTA,DIO_PIN4,DIO_HIGH);

}

/*----------------------------------------------------------------------------------------------------------------------*/

void CloseFan (void)
{
	LCD_voidSetLocation ( 2 , 0 );
	LCD_voidSendString ("Fan-OFF");
	DIO_voidSetPinValue(DIO_PORTA,DIO_PIN4,DIO_LOW);
}
/*----------------------------------------------------------------------------------------------------------------------*/
void OpenLight2 (void)
{

	LCD_voidSetLocation ( 1 , 0 );
	LCD_voidSendString ("LED-ON ");
	DIO_voidSetPinValue(DIO_PORTD,DIO_PIN4,DIO_HIGH);


}
/*----------------------------------------------------------------------------------------------------------------------*/

void CloseLight2 (void)
{
	LCD_voidSetLocation ( 1 , 0 );
	LCD_voidSendString ("LED-OFF");
	DIO_voidSetPinValue(DIO_PORTD,DIO_PIN4,DIO_LOW);


}
/*----------------------------------------------------------------------------------------------------------------------*/

void OpenFan2 (void)
{

	LCD_voidSetLocation ( 2 , 0 );

	LCD_voidSendString ("Turn-ON ");
	DIO_voidSetPinValue(DIO_PORTD,DIO_PIN5,DIO_HIGH);

}

/*----------------------------------------------------------------------------------------------------------------------*/

void CloseFan2 (void)
{
	LCD_voidSetLocation ( 2 , 0 );
	LCD_voidSendString ("Turn-OFF");
	DIO_voidSetPinValue(DIO_PORTD,DIO_PIN5,DIO_LOW);
}
/*----------------------------------------------------------------------------------------------------------------------*/

void OpenTV (void)
{

	LCD_voidSetLocation ( 1 , 0 );
	LCD_voidSendString ("TV-ON");
	DIO_voidSetPinValue(DIO_PORTD,DIO_PIN6,DIO_HIGH);

}

/*----------------------------------------------------------------------------------------------------------------------*/

void CloseTV (void)
{
	LCD_voidSetLocation ( 1 , 0 );
	LCD_voidSendString ("TV-OFF");
	DIO_voidSetPinValue(DIO_PORTD,DIO_PIN6,DIO_LOW);
}
/*----------------------------------------------------------------------------------------------------------------------*/

void OpenWindow (void)
{
	DIO_voidSetPinValue(DIO_PORTD,DIO_PIN3,DIO_HIGH);
}
/*----------------------------------------------------------------------------------------------------------------------*/

void CloseWindow (void)
{
	DIO_voidSetPinValue(DIO_PORTD,DIO_PIN3,DIO_LOW);
}
u16 ADC_vSetFanAndCooler (void)
{
	u16 Local_u8ADCReading=0;
	u16 Local_u16AnalogReading=0;
	u32 Local_u8Temp=0;
	Local_u8ADCReading=ADC_u16GetDigitalValue(0);
	Local_u16AnalogReading = (u16)(((u32)Local_u8ADCReading * 5000UL) / 1024UL) ;
	Local_u8Temp   = Local_u16AnalogReading / 10 ;

	return Local_u8Temp;
}
