/**********************************************************************************/
/**************		Auther	:	 Ahmed Amr         ********************************/
/**************		SWC  	:	 UART			   ********************************/
/**************		Date  	:	 8/3/2022          ********************************/
/**************		Ver   	:	 V1                ********************************/
/**********************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include <avr/io.h>
#include "UART.h"

void UART_voidInit (void)
{
	u16 Local_u16BaudRate = 51 ;
	u8 Local_u8UCSRCValue = 0b10000000 ;

	/* 1- Select Baud Rate = 9600 ==> UBRRL & UBRRH = 51 */
	UBRRL = (u8) Local_u16BaudRate ;
	UBRRH = (u8) (Local_u16BaudRate >> 8);

	/* 2- Select Normal Speed */
	CLR_BIT(UCSRA , U2X);

	/* 3- Disable Multi-processor Communication Mode */
	CLR_BIT(UCSRA , MPCM);

	/* 4- Receiver and Transmitter Enable */
	SET_BIT(UCSRB , RXEN);
	SET_BIT(UCSRB , TXEN);

	/* 5- Select 8 bits Data */
	CLR_BIT(UCSRB , UCSZ2);
	SET_BIT(Local_u8UCSRCValue , UCSZ0);
	SET_BIT(Local_u8UCSRCValue , UCSZ1);

	/* 6- Select Asynchronous Mode */
	CLR_BIT(Local_u8UCSRCValue , UMSEL);

	/* 7- Disable Parity Mode */
	CLR_BIT(Local_u8UCSRCValue , UPM0);
	CLR_BIT(Local_u8UCSRCValue , UPM1);

	/* 8- Select 2 Stop Bit  */
	SET_BIT(Local_u8UCSRCValue , USBS);

	/* 9- Update The UCSRC Value */
	UCSRC = Local_u8UCSRCValue ;
}

void UART_voidSendData 	(u8 Copy_u8Data)
{
	/*Wait until the Transmitter Register is Empty*/
	while(GET_BIT(UCSRA , UDRE)==0);
	/*Send Data Byte*/
	UDR = Copy_u8Data ;
}

u8 UART_voidReciveData 	(void)
{
	/*Wait until the Transmitter Register is Empty*/
	while(GET_BIT(UCSRA , RXC)==0);
	/*Send Data Byte*/
	return UDR ;
}
