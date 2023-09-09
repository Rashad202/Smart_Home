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
#include "ADC.h"
#include "TWI.h"

#include "KPD_Interface.h"
#include "LCD_Interface.h"
#include "EEPROM.h"



void StartProgram			 (void);
u16  GetPassword    		 (void);
void Room1    		     	 (void);
void Room2  		    	 (void);
void OpenDoor  				 (void);
void CloseDoor 				 (void);
void LCD_voidWrite_u32Number ( u32 Copy_u32Number);
void Control_Fan1 			 (void);
void Control_Light1 		 (void);
void Control_Fan2 			 (void);
void Control_Light2 	  	 (void);
void Control_TV (void);
u8 Exit_EditPassFlag = 1 ;
u8 EEPROM_PASSWORD = 0 ;
u8 ModeKey = 0 ;

int main(void)
{


LCD_voidInit();
KPD_voidInit();
UART_voidInit();
ADC_voidInit();
TWI_VidMasterInit();
EEPROM_VidWriteDataByte(1,123);

StartProgram();
DIO_voidSetPinDirection(DIO_PORTC,DIO_PIN2,DIO_OUTPUT);
DIO_voidSetPinDirection(DIO_PORTC,DIO_PIN3,DIO_OUTPUT);
DIO_voidSetPinValue(DIO_PORTC,DIO_PIN3,DIO_LOW);

LCD_voidSendCommand(LCD_CLEAR);
LCD_voidSetLocation (1,0);
LCD_voidSendString ("Enter Password :");
LCD_voidSetLocation (2,13);
LCD_voidSendString ("[1]");
u16 PASSWORD=0;
EEPROM_PASSWORD=EEPROM_u8ReadDataByte(1);
	while(1)
		{
		for ( u8 i=0 ; i < 3 ; i++ )
				{
					PASSWORD = GetPassword();
					if( PASSWORD == EEPROM_PASSWORD )
					{
						UART_voidSendData('Z');
						LCD_voidSendCommand(LCD_CLEAR);
						OpenDoor();
						LCD_voidSetLocation (1,1);
						LCD_voidSendString ("Door is OPened");
						LCD_voidSetLocation (2,3);
						LCD_voidSendString ("Welcome..");
						_delay_ms(500);
						LCD_voidSendCommand(LCD_CLEAR);
						while(1)
						{

							LCD_voidSetLocation (1,0);
							LCD_voidSendString ("1-Room1         ");
							LCD_voidSetLocation (2,0);
							LCD_voidSendString ("2-Room2         ");
							ModeKey =KPD_u8GetKeyValue();
							if ( ModeKey != KPD_KEY_NOT_PRESSED  )
							{
								if( ModeKey == '1' )
								{
									Room1();
								}
								else if( ModeKey == '2' )
								{
									Room2();
								}

							}

						}
					}
					else
					{
						if (i==2)
						{
							LCD_voidSendCommand(LCD_CLEAR);
							LCD_voidSetLocation (1,3);
							LCD_voidSendString ("7aramy !!");
							LCD_voidSetLocation (2,0);
							LCD_voidSendString ("Restart System..");
							UART_voidSendData('N');
							DIO_voidSetPinValue(DIO_PORTC,DIO_PIN3,DIO_HIGH);	// Buzzer ON

							break;
						}
						else
						{
							LCD_voidSendCommand(LCD_CLEAR);
							LCD_voidSetLocation (1,0);
							LCD_voidSendString ("Try again..");
							LCD_voidSetLocation (2,13);
							LCD_voidSendString ("[");
							LCD_voidWrite_u32Number(i+2);
							LCD_voidSendString ("]");
						}
					}
				}
			}

return 0;
}

/*----------------------------------------------------------------------------------------------------------------------*/
void StartProgram (void)
{
	LCD_voidSetLocation(1,0);
	LCD_voidSendString(" Welcome To MY");
	LCD_voidSetLocation(2,0);
	LCD_voidSendString("  Smart Home :) ");
	_delay_ms(600);
}


/*----------------------------------------------------------------------------------------------------------------------*/
void Room1    (void)
{

	u8 ActuatorKey = 0 ;
	LCD_voidSendCommand(LCD_CLEAR);
	UART_voidSendData('R');
	while(1)
	{
		LCD_voidSetLocation(1,0);
		LCD_voidSendString ("(1)Fan (2)Light ");
		LCD_voidSetLocation (2,0);
		LCD_voidSendString ("(3)TV ");
		ActuatorKey = KPD_u8GetKeyValue ();
		if ( ActuatorKey != 0xff  )
		{
			if ( ActuatorKey == '1' )
			{
				Control_Fan1();
			}
			else if ( ActuatorKey == '2' )
			{
				Control_Light1();

			}
			else if ( ActuatorKey == '3' )
			{
				Control_TV();
			}
			else
			{
				UART_voidSendData('#');
				ModeKey = 0 ;
				break;
			}
		}
	}



}

/*----------------------------------------------------------------------------------------------------------------------*/
void Room2    (void)
{

	u8 ActuatorKey = 0 ;
	LCD_voidSendCommand(LCD_CLEAR);
	UART_voidSendData('r');
	while(1)
	{
		LCD_voidSetLocation(1,0);
		LCD_voidSendString ("(1)AIR-Condition ");
		LCD_voidSetLocation(2,0);
		LCD_voidSendString ("(2)Light         ");
		ActuatorKey = KPD_u8GetKeyValue ();
		if ( ActuatorKey != 0xff  )
		{
			if ( ActuatorKey == '1' )
			{
				Control_Fan2();
			}
			else if ( ActuatorKey == '2' )
			{
				Control_Light2();

			}
			else
			{
				UART_voidSendData('#');
				ModeKey = 0 ;
				break;
			}
		}
	}



}



/*----------------------------------------------------------------------------------------------------------------------*/
void Control_Fan1 (void)
{
	u8 FanKey = 0 ;
	LCD_voidSendCommand(LCD_CLEAR);
	UART_voidSendData('F');
	LCD_voidSetLocation (1,0);
	LCD_voidSendString ("(1)Fan: ON ");
	LCD_voidSetLocation (2,0);
	LCD_voidSendString ("(0)Fan: OFF");
	while(1)
	{
		FanKey = KPD_u8GetKeyValue();
		if ( FanKey != 0xff  )
		{
			if ( FanKey == '1' )
			{
				UART_voidSendData('1');
				LCD_voidSendCommand(LCD_CLEAR);

				break;
			}
			else if ( FanKey == '0' )
			{
				UART_voidSendData('0');
				LCD_voidSendCommand(LCD_CLEAR);

				break;
			}
		}
	}


}
/*----------------------------------------------------------------------------------------------------------------------*/

void Control_Light1 (void)
{
	u8 LightKey = 0 ;
	LCD_voidSendCommand(LCD_CLEAR);
	UART_voidSendData('L');
	LCD_voidSetLocation (1,0);
	LCD_voidSendString ("(1)Light: ON ");
	LCD_voidSetLocation (2,0);
	LCD_voidSendString ("(0)Light: OFF");
	while(1)
	{
		LightKey = KPD_u8GetKeyValue();
		if ( LightKey != 0xff  )
		{
			if ( LightKey == '1' )
			{
				UART_voidSendData('1');
				LCD_voidSendCommand(LCD_CLEAR);

				break;
			}
			else if ( LightKey == '0' )
			{
				UART_voidSendData('0');
				LCD_voidSendCommand(LCD_CLEAR);

				break;
			}
		}
	}

}
/*----------------------------------------------------------------------------------------------------------------------*/
void Control_Fan2 (void)
{
	u8 FanKey = 0 ;
	LCD_voidSendCommand(LCD_CLEAR);
	UART_voidSendData('f');
	LCD_voidSetLocation (1,0);
	LCD_voidSendString ("(1)Fan: ON ");
	LCD_voidSetLocation (2,0);
	LCD_voidSendString ("(0)Fan: OFF");
	while(1)
	{
		FanKey = KPD_u8GetKeyValue();
		if ( FanKey != 0xff  )
		{
			if ( FanKey == '1' )
			{
				UART_voidSendData('1');
				LCD_voidSendCommand(LCD_CLEAR);

				break;
			}
			else if ( FanKey == '0' )
			{
				UART_voidSendData('0');
				LCD_voidSendCommand(LCD_CLEAR);

				break;
			}
		}
	}


}
/*----------------------------------------------------------------------------------------------------------------------*/

void Control_Light2 (void)
{
	u8 LightKey = 0 ;
	LCD_voidSendCommand(LCD_CLEAR);
	UART_voidSendData('l');
	LCD_voidSetLocation (1,0);
	LCD_voidSendString ("(1)Light: ON ");
	LCD_voidSetLocation (2,0);
	LCD_voidSendString ("(0)Light: OFF");
	while(1)
	{
		LightKey = KPD_u8GetKeyValue();
		if ( LightKey != 0xff  )
		{
			if ( LightKey == '1' )
			{
				UART_voidSendData('1');
				LCD_voidSendCommand(LCD_CLEAR);

				break;
			}
			else if ( LightKey == '0' )
			{
				UART_voidSendData('0');
				LCD_voidSendCommand(LCD_CLEAR);

				break;
			}
		}
	}

}
/*----------------------------------------------------------------------------------------------------------------------*/
void Control_TV (void)
{
	u8 WinKey = 0 ;
	LCD_voidSendCommand(LCD_CLEAR);
	UART_voidSendData('T');
	LCD_voidSetLocation (1,0);
	LCD_voidSendString ("(1)TV: ON ");
	LCD_voidSetLocation (2,0);
	LCD_voidSendString ("(0)TV: OFF");
	while(1)
	{
		WinKey = KPD_u8GetKeyValue();
		if ( WinKey != 0xff  )
		{
			if ( WinKey == '1' )
			{
				UART_voidSendData('1');
				LCD_voidSendCommand(LCD_CLEAR);

				break;
			}
			else if ( WinKey == '0' )
			{
				UART_voidSendData('0');
				LCD_voidSendCommand(LCD_CLEAR);

				break;
			}
		}
	}

}

/*----------------------------------------------------------------------------------------------------------------------*/

u16 GetPassword (void)
{
	LCD_voidSetLocation(2,0);
	u16 Password = 0 ;
	u16 Copy_u8Temp = 0 ;
	u8 Local_u8PressedKey ;
	while(1)
	{
		Local_u8PressedKey = KPD_u8GetKeyValue();
		if ( Local_u8PressedKey != KPD_KEY_NOT_PRESSED  )
		{
			if( Local_u8PressedKey >= '0' && Local_u8PressedKey <= '9' )
			{
				LCD_voidSendChar('*');
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


/*----------------------------------------------------------------------------------------------------------------------*/

void OpenDoor  				 (void)
{
	DIO_voidSetPinValue(DIO_PORTC,DIO_PIN2,DIO_HIGH);
	DIO_voidSetPinValue(DIO_PORTC,DIO_PIN3,DIO_HIGH);
	_delay_ms(800);
	DIO_voidSetPinValue(DIO_PORTC,DIO_PIN2,DIO_LOW);
	DIO_voidSetPinValue(DIO_PORTC,DIO_PIN3,DIO_LOW);

}
/*----------------------------------------------------------------------------------------------------------------------*/

void CloseDoor 				 (void)
{
	DIO_voidSetPinValue(DIO_PORTC,DIO_PIN2,DIO_LOW);
}
/*----------------------------------------------------------------------------------------------------------------------*/

void LCD_voidWrite_u32Number ( u32 Copy_u32Number)
{
    u8 Arr[20] ;
    u8 i=0 ;
    while ( Copy_u32Number > 0 )
    {
        Arr[i] = Copy_u32Number % 10 ;
        Copy_u32Number /= 10 ;
        i++;
    }
    i--;
    for( s16 j=i ; j>=0 ; j--)
    {
        LCD_voidSendChar( Arr[j] + '0' );
    }
}
