/*
 * main.c
 *
 *  Created on: 10 Sep 2023
 *      Author: Rashad
 */
/* Include Header Files From LIB */
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
#include "avr/delay.h"
/* Include Header Files From MCAL Layer */
#include "../MCAL/DIO/DIO_Interface.h"
#include "../MCAL/ADC/ADC_Interface.h"
#include "../MCAL/I2C/I2C_Interface.h"
#include"../MCAL/TIMERS/TIMER1/TIMER1_Interface.h"
#include"../MCAL/GIE/GIE_Interface.h"
#include"../MCAL/USART/USART_Interface.h"
/* Include Header Files From HAL Layer */
#include "../HAL/LCD/LCD_Interface.h"
#include "../HAL/EEPROM/EEPROM_Interface.h"
#include "../HAL/KPAD/KPAD_Interface.h"
#include"../HAL/SERVO_MOTOR/SERVO_Interface.h"

void StartProgram			 (void);
u16  GetPassword    		 (void);
void Room1    		     	 (void);
void Room2  		    	 (void);
void Kitchen  		     	 (void);
void Reception  	    	 (void);
void Auto		  	    	 (void);
void More		  	    	 (void);
void OpenDoor  				 (void);
void CloseDoor 				 (void);
void Control_Fan 			 (u8 Copy_u32Number);
void Control_Light			 (u8 Copy_u32Number);

void Control_TV 			 (void);
void Control_Oven 			 (void);
u8 Exit_EditPassFlag = 1 ;
u8 EEPROM_PASSWORD = 0 ;
u8 ModeKey = 0 ;


void main()
{

		LCD_voidInit();
		KPAD_voidInit();
		USART_voidInit();
		ADC_voidInit();
		TIMER1_voidInit ();
		I2C_voidMasterInit(0);
		EEPROM_voidSendDataByte(1,123);
		DIO_voidSetPinDirection(DIO_PORTC,DIO_PIN3,DIO_OUTPUT);
		u16 PASSWORD = 0 ;
		EEPROM_PASSWORD=EEPROM_voidReadDataByte(1);
		StartProgram();
		LCD_voidClearLine(0);
		LCD_voidClearLine(1);
		LCD_voidGoTo_XY (0,0);
		LCD_voidWriteString (" Enter Password:");
		LCD_voidGoTo_XY (1,13);
		LCD_voidWriteString ("[1]");
		while (1)
			{
				for ( u8 i=0 ; i < 3 ; i++ )
				{
					PASSWORD = GetPassword();
					if( PASSWORD == EEPROM_PASSWORD )
					{
						USART_voidSendData('Z');
						LCD_voidClearLine(0);
						LCD_voidClearLine(1);
						DIO_voidSetPinValue(DIO_PORTC,DIO_PIN3,DIO_HIGH);		// Buzzer ON
						OpenDoor();
						_delay_ms(250);
						DIO_voidSetPinValue(DIO_PORTC,DIO_PIN3,DIO_LOW);		// Buzzer off
						LCD_voidGoTo_XY (0,1);
						LCD_voidWriteString ("Door is OPened");
						LCD_voidGoTo_XY (1,3);
						LCD_voidWriteString ("Welcome..");

						_delay_ms(300);

						while(1)
						{

							LCD_voidGoTo_XY (0,0);
							LCD_voidWriteString ("1-ROOM1 2-ROOM2");
							LCD_voidGoTo_XY (1,0);
							LCD_voidWriteString ("3-Kitchen 4-More");
							ModeKey = KPAD_u8GetPressedKey ();
							if ( ModeKey != 0xff  )
							{
								if( ModeKey == '1' )
								{
									Room1();
								}
								else if ( ModeKey == '2' )
								{
									Room2();
								}
								else if ( ModeKey == '3' )
								{
									Kitchen();
								}
								else if ( ModeKey == '4' )
								{
									More();
								}
							}
						}
					}
					else
					{
						if (i==2)
						{
							LCD_voidClearLine(0);
							LCD_voidClearLine(1);
							LCD_voidGoTo_XY (0,3);
							LCD_voidWriteString ("7aramy !!");
							LCD_voidGoTo_XY (1,0);
							LCD_voidWriteString ("Restart System..");
							USART_voidSendData('N');
							DIO_voidSetPinValue(DIO_PORTC,DIO_PIN3,DIO_HIGH);		// Buzzer ON
							CloseDoor();
							break;
						}
						else
						{
							LCD_voidClearLine(0);
							LCD_voidClearLine(1);
							LCD_voidGoTo_XY (0,0);
							LCD_voidWriteString ("Try again....");
							LCD_voidGoTo_XY (1,13);
							LCD_voidWriteString ("[");
							LCD_voidWrite_u32Number(i+2);
							LCD_voidWriteString ("]");
						}
					}
				}
			}
		}


/* ------------------------------------------------------------- */
void StartProgram (void)
{
	LCD_voidClearDisplay();
	LCD_voidGoTo_XY (0,1);
	LCD_voidWriteString (" ITI Graduation");
	LCD_voidGoTo_XY (1,0);
	LCD_voidWriteString ("    Project ");
	_delay_ms(300);
	LCD_voidClearLine(0);
	LCD_voidClearLine(1);
	LCD_voidGoTo_XY (0,1);
	LCD_voidWriteString (" Hello Welcome  ");
	LCD_voidGoTo_XY (1,0);
	LCD_voidWriteString ("To MY Smart Home  ");
	_delay_ms(300);
}

/* ------------------------------------------------------------- */
u16 GetPassword (void)
{
	LCD_voidGoTo_XY (1,0);
	u16 Password = 0 ;
	u16 Copy_u8Temp = 0 ;
	u8 Local_u8PressedKey ;
	while(1)
	{
		Local_u8PressedKey = KPAD_u8GetPressedKey ();
		if ( Local_u8PressedKey != 0xff  )
		{
			if( Local_u8PressedKey >= '0' && Local_u8PressedKey <= '9' )
			{
				LCD_voidWriteChar('*');
				Copy_u8Temp = Copy_u8Temp*10 + (Local_u8PressedKey - '0') ;
				Password = Copy_u8Temp ;
			}
			else if ( Local_u8PressedKey == '=' )
			{
				break ;
			}
		}
	}
	return Password ;
}

/* ------------------------------------------------------------- */
void Room1 (void)
{
	u8 ActuatorKey = 0 ;
	USART_voidSendData('1');
	LCD_voidClearLine(0);
	LCD_voidClearLine(1);

	while(1)
	{
		LCD_voidGoTo_XY (0,0);
		LCD_voidWriteString ("(1)Light       ");
		LCD_voidGoTo_XY (1,0);
		LCD_voidWriteString ("(2)Fan         ");
		ActuatorKey = KPAD_u8GetPressedKey ();
		if ( ActuatorKey != 0xff  )
		{
			if ( ActuatorKey == '1' )
			{
				Control_Light(1);
			}
			else if ( ActuatorKey == '2' )
			{
				Control_Fan(1);
			}
			else
			{
				USART_voidSendData('#');
				ModeKey = 0 ;
				break;
			}
		}
	}
}
/* ------------------------------------------------------------- */
void Room2 (void)
{
	u8 ActuatorKey = 0 ;
	USART_voidSendData('2');
	LCD_voidClearLine(0);
	LCD_voidClearLine(1);

	while(1)
	{
		LCD_voidGoTo_XY (0,0);
		LCD_voidWriteString ("(1)Light       ");
		LCD_voidGoTo_XY (1,0);
		LCD_voidWriteString ("(2)Fan         ");
		ActuatorKey = KPAD_u8GetPressedKey ();
		if ( ActuatorKey != 0xff  )
		{
			if ( ActuatorKey == '1' )
			{
				Control_Light(2);
			}
			else if ( ActuatorKey == '2' )
			{
				Control_Fan(2);
			}
			else
			{
				USART_voidSendData('#');
				ModeKey = 0 ;
				break;
			}
		}
	}
}
/* ------------------------------------------------------------- */
void More(void)
{
	u8 ActuatorKey=0;
	while(1)
		{
			LCD_voidGoTo_XY (0,0);
			LCD_voidWriteString ("4-Reception       ");
			LCD_voidGoTo_XY (1,0);
			LCD_voidWriteString ("5-Auto          ");
			ActuatorKey = KPAD_u8GetPressedKey ();
			if ( ActuatorKey != 0xff  )
			{
				if ( ActuatorKey == '4' )
				{
					Reception();
				}
				else if ( ActuatorKey == '5' )
				{
					Auto();
				}
			}
		}
}


void Reception (void)
{
	u8 ActuatorKey = 0 ;
	USART_voidSendData('4');
	LCD_voidClearLine(0);
	LCD_voidClearLine(1);

	while(1)
	{
		LCD_voidGoTo_XY (0,0);
		LCD_voidWriteString ("(1)Light       ");
		LCD_voidGoTo_XY (1,0);
		LCD_voidWriteString ("(2)TV          ");
		ActuatorKey = KPAD_u8GetPressedKey ();
		if ( ActuatorKey != 0xff  )
		{
			if ( ActuatorKey == '1' )
			{
				Control_Light(3);
			}
			else if ( ActuatorKey == '2' )
			{
				Control_TV();
			}
			else
			{
				USART_voidSendData('#');
				ModeKey = 0 ;
				break;
			}
		}
	}
}
/* ------------------------------------------------------------- */
void Kitchen (void)
{
	u8 ActuatorKey = 0 ;
	USART_voidSendData('3');
	LCD_voidClearLine(0);
	LCD_voidClearLine(1);

	while(1)
	{
		LCD_voidGoTo_XY (0,0);
		LCD_voidWriteString ("(1)Light       ");
		LCD_voidGoTo_XY (1,0);
		LCD_voidWriteString ("(2)Oven         ");
		ActuatorKey = KPAD_u8GetPressedKey ();
		if ( ActuatorKey != 0xff  )
		{
			if ( ActuatorKey == '1' )
			{
				Control_Light(4);
			}
			else if ( ActuatorKey == '2' )
			{
				Control_Oven();
			}
			else
			{
				USART_voidSendData('#');
				ModeKey = 0 ;
				break;
			}
		}
	}
}
/* ------------------------------------------------------------- */
void Auto (void)
{
	u8 ExitAutoKey = 0 ;
	USART_voidSendData('5');
	LCD_voidClearLine(0);
	LCD_voidClearLine(1);
	LCD_voidGoTo_XY (0,0);
	LCD_voidWriteString ("  Home is");
	LCD_voidGoTo_XY (1,0);
	LCD_voidWriteString (" Auto Mode");
	while(1)
	{
		ExitAutoKey = KPAD_u8GetPressedKey ();
		if ( ExitAutoKey != 0xff  )
		{
			if ( ExitAutoKey == '#' )
			{
				USART_voidSendData('#');
				LCD_voidClearLine(0);
				LCD_voidClearLine(1);
				ModeKey = 0 ;
				break;
			}
		}
	}
}
/* ------------------------------------------------------------- */
void Control_TV (void)
{
	u8 TVKey = 0 ;
	USART_voidSendData('T');
	LCD_voidClearLine(0);
	LCD_voidClearLine(1);
	LCD_voidGoTo_XY (0,0);
	LCD_voidWriteString ("(1)TV: ON ");
	LCD_voidGoTo_XY (1,0);
	LCD_voidWriteString ("(0)TV: OFF");
	while(1)
	{
		TVKey = KPAD_u8GetPressedKey ();
		if ( TVKey != 0xff  )
		{
			if ( TVKey == '1' )
			{
				USART_voidSendData('1');
				LCD_voidClearLine(0);
				LCD_voidClearLine(1);
				break;
			}
			else if ( TVKey == '0' )
			{
				USART_voidSendData('0');
				LCD_voidClearLine(0);
				LCD_voidClearLine(1);
				break;
			}
		}
	}
}
/* ------------------------------------------------------------- */
void Control_Oven (void)
{
	u8 OvenKey = 0 ;
	USART_voidSendData('O');
	LCD_voidClearLine(0);
	LCD_voidClearLine(1);
	LCD_voidGoTo_XY (0,0);
	LCD_voidWriteString ("(1)Oven: ON ");
	LCD_voidGoTo_XY (1,0);
	LCD_voidWriteString ("(0)Oven: OFF");
	while(1)
	{
		OvenKey = KPAD_u8GetPressedKey ();
		if ( OvenKey != 0xff  )
		{
			if ( OvenKey == '1' )
			{
				USART_voidSendData('1');
				LCD_voidClearLine(0);
				LCD_voidClearLine(1);
				break;
			}
			else if ( OvenKey == '0' )
			{
				USART_voidSendData('0');
				LCD_voidClearLine(0);
				LCD_voidClearLine(1);
				break;
			}
		}
	}
}

/* ------------------------------------------------------------- */
void Control_Light (u8 CopyNumber)
{
	u8 LightKey = 0 ;
	USART_voidSendData('L');
	LCD_voidClearLine(0);
	LCD_voidClearLine(1);
	LCD_voidGoTo_XY (0,0);
	LCD_voidWriteString ("(1)Light: ON ");
	LCD_voidGoTo_XY (1,0);
	LCD_voidWriteString ("(0)Light: OFF");
	switch(CopyNumber)
	{
		case 1 :
				while(1)
				{
					LightKey = KPAD_u8GetPressedKey ();
					if ( LightKey != 0xff  )
					{
						if ( LightKey == '1' )
						{
							USART_voidSendData('1');
							LCD_voidClearLine(0);
							LCD_voidClearLine(1);
							break;
						}
						else if ( LightKey == '0' )
						{
							USART_voidSendData('0');
							LCD_voidClearLine(0);
							LCD_voidClearLine(1);
							break;
						}
					}
				}
				break;
		case 2 :
				while(1)
				{
					LightKey = KPAD_u8GetPressedKey ();
					if ( LightKey != 0xff  )
					{
						if ( LightKey == '1' )
						{
							USART_voidSendData('1');
							LCD_voidClearLine(0);
							LCD_voidClearLine(1);
							break;
						}
						else if ( LightKey == '0' )
						{
							USART_voidSendData('0');
							LCD_voidClearLine(0);
							LCD_voidClearLine(1);
							break;
						}
					}
				}
				break;
		case 3 :
				while(1)
				{
					LightKey = KPAD_u8GetPressedKey ();
					if ( LightKey != 0xff  )
					{
						if ( LightKey == '1' )
						{
							USART_voidSendData('1');
							LCD_voidClearLine(0);
							LCD_voidClearLine(1);
							break;
						}
						else if ( LightKey == '0' )
						{
							USART_voidSendData('0');
							LCD_voidClearLine(0);
							LCD_voidClearLine(1);
							break;
						}
					}
				}
				break;
		case 4 :
				while(1)
				{
					LightKey = KPAD_u8GetPressedKey ();
					if ( LightKey != 0xff  )
					{
						if ( LightKey == '1' )
						{
							USART_voidSendData('1');
							LCD_voidClearLine(0);
							LCD_voidClearLine(1);
							break;
						}
						else if ( LightKey == '0' )
						{
							USART_voidSendData('0');
							LCD_voidClearLine(0);
							LCD_voidClearLine(1);
							break;
						}
					}
				}
				break;
		default :
				break;
	}
}

/* ------------------------------------------------------------- */
void Control_Fan	(u8 CopyNumber)
{
	u8 FanKey = 0 ;
	USART_voidSendData('F');
	LCD_voidClearLine(0);
	LCD_voidClearLine(1);
	LCD_voidGoTo_XY (0,0);
	LCD_voidWriteString ("(1)Fan: ON ");
	LCD_voidGoTo_XY (1,0);
	LCD_voidWriteString ("(0)Fan: OFF");
	switch(CopyNumber)
	{
		case 1:
				while(1)
				{
					FanKey = KPAD_u8GetPressedKey ();
					if ( FanKey != 0xff  )
					{
						if ( FanKey == '1' )
						{
							USART_voidSendData('1');
							LCD_voidClearLine(0);
							LCD_voidClearLine(1);
							break;
						}
						else if ( FanKey == '0' )
						{
							USART_voidSendData('0');
							LCD_voidClearLine(0);
							LCD_voidClearLine(1);
							break;
						}
					}
				}

				break;
		case 2:
				while(1)
				{
					FanKey = KPAD_u8GetPressedKey ();
					if ( FanKey != 0xff  )
					{
						if ( FanKey == '1' )
						{
							USART_voidSendData('1');
							LCD_voidClearLine(0);
							LCD_voidClearLine(1);
							break;
						}
						else if ( FanKey == '0' )
						{
							USART_voidSendData('0');
							LCD_voidClearLine(0);
							LCD_voidClearLine(1);
							break;
						}
					}
				}

				break;
		default :
			break;

	}
}

/* ------------------------------------------------------------- */
void OpenDoor (void)
{
		SERVO_voidRotateSpecificAngle_OC1A ( 90 );

}
/* ------------------------------------------------------------- */
void CloseDoor (void)
{
		SERVO_voidRotateSpecificAngle_OC1A ( 0 );

}

