#ifndef LCD_H
#define LCD_H

/* MACROS For Used Ports & Pins */
#define 	LCD_DATA_PORT 			DIO_PORTB
#define 	LCD_CONTROL_PORT 		DIO_PORTD
#define 	RS 						DIO_PIN2
#define 	RW  					DIO_PIN3
#define 	EN  					DIO_PIN4

/* MACROS For LCD Command */
#define 	LCD_FUNC_SET 			0b00111000		// 8-bit data, 2-line display, 5 x 7 font		
#define 	LCD_ONOF 				0b00001111				
#define  	LCD_CLEAR 				0b00000001		/* replace all characters with ASCII 'space'*/
#define 	LCD_FunctionReset   	0b00110000      // reset the LCD
#define 	LCD_SetCursor       	0b10000000      // set cursor position


/* MACROS For LCD Line */
#define 	LCD_U8_LINE1 			1
#define 	LCD_U8_LINE2 			2



/*Functions*/
void LCD_voidInit ();
void LCD_voidSendCommand(u8 Copy_U8Command);
void LCD_voidSendChar (u8 Copy_U8Data);
void LCD_voidSendString (u8 *Copy_U8String);
void LCD_voidSetLocation (u8 Copy_U8LineNum , u8 Copy_U8CharNum);

#endif
