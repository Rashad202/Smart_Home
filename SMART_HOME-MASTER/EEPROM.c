#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include <avr/delay.h>
#include "DIO_Interface.h"
#include "TWI.h"
#include "EEPROM.h"



void EEPROM_VidWriteDataByte(u16 Copy_u16ByteAddress, u8 Copy_u8ByteData)
{
	/* START CONDITION */
	TWI_VidStartCondition();
    /* ADDRESS WITH WRITE */
	TWI_VidSlaveAddWrite(Init_Address | (A2_PIN<<2) | (Copy_u16ByteAddress >> 8));
    /* ADDRESS BYTE */
	TWI_VidMasterSendData((u8)Copy_u16ByteAddress);
    /* DATA BYTE */
	TWI_VidMasterSendData(Copy_u8ByteData);
    /* STOP CONDITION */
	TWI_VidStopCondition();

	_delay_ms(10);
}



u8 EEPROM_u8ReadDataByte(u16 Copy_u16ByteAddress)
{
	u8 Local_u8Data;
	TWI_VidStartCondition();

	TWI_VidSlaveAddWrite(Init_Address|(A2_PIN<<2)|(Copy_u16ByteAddress>>8));

	TWI_VidMasterSendData((u8)Copy_u16ByteAddress);

	TWI_VidStartCondition();

	TWI_VidSlaveAddRead(Init_Address|(A2_PIN<<2)|(Copy_u16ByteAddress>>8));

	Local_u8Data = TWI_u8MasterRecieveData();

	TWI_VidStopCondition();

	return Local_u8Data;

}

















