#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <avr/io.h>
#include "TWI.h"

void TWI_VidMasterInit(void)
{
	/*Frequancy->200KHZ*/
	TWBR = 12;
	/*Prescaller value->1*/
	CLR_BIT(TWSR,TWPS0);
	CLR_BIT(TWSR,TWPS1);
	/*Enable I2C*/
	SET_BIT(TWCR,TWEN);
}
void TWI_VidSlaveInit(u8 Copy_u8Address)
{
	/*Enable ACK */
	SET_BIT(TWCR,TWEA);
	/*Write Address*/
	TWAR = Copy_u8Address<<1;
	/*Enable I2C*/
	SET_BIT(TWCR,TWEN);
}


void TWI_VidStartCondition(void)
{
	/*Clear Flag+ start condition*/
	SET_BIT(TWCR,TWSTA);
	SET_BIT(TWCR,TWINT);
	/*wait flag*/
	while(GET_BIT(TWCR,TWINT)==0);
	/*Check ACK"status code"0x08*/
}
void TWI_VidReStartCondition(void)
{
	/* Clear Flag + start condition */
	SET_BIT(TWCR,TWINT);
	SET_BIT(TWCR,TWSTA);
	/* wait flag */
	while(!GET_BIT(TWCR,TWINT));

}
void TWI_VidStopCondition(void)
{
	/*Clear Flag+ Stop condition*/
	SET_BIT(TWCR,TWSTO);
	SET_BIT(TWCR,TWINT);
}


void TWI_VidSlaveAddWrite(u8 Copy_u8SlaveAdd)
{
	/*write slave Address & 0 in TWDR*/
	TWDR=Copy_u8SlaveAdd<<1;
	CLR_BIT(TWDR,0);
	/*Clear Start Condition*/
	CLR_BIT(TWCR,TWSTA);
	/*Clear Flag*/
	SET_BIT(TWCR,TWINT);
	/*Check ACK"status code"0x18*/
	/*wait flag*/
	while(GET_BIT(TWCR,TWINT)==0);
}

void TWI_VidSlaveAddRead(u8 Copy_u8SlaveAdd)
{
	/*write slave Address & 1 in TWDR*/
	TWDR = Copy_u8SlaveAdd<<1;
	SET_BIT(TWDR,0);
	/*Clear Start Condition*/
	CLR_BIT(TWCR,TWSTA);
	/*Clear Flag*/
	SET_BIT(TWCR,TWINT);
	/*Check ACK"status code"0x40*/
	while(GET_BIT(TWCR,TWINT)==0);
}


void TWI_VidMasterSendData(u8 Copy_u8Data)
{
	/*write Data in TWDR*/
	TWDR = Copy_u8Data;
	/*Clear Flag*/
	SET_BIT(TWCR,TWINT);
	/*Check ACK"status code"0x28*/
	while(!GET_BIT(TWCR,TWINT));
}

u8 TWI_VidSlaveReadData(void)
{
	//Wait to receive own slave address
	while((TWSR & 0xf8)!=0x60);//0B1111 1000
	/*Clear flag*/
	SET_BIT(TWCR,TWINT);
	//Wait to receive correct message
	while((TWSR & 0xf8)!=0x80);
	/*Check ACK"status code"0x50*/
	/* Return Data */
	return TWDR;
}

u8 TWI_u8MasterRecieveData(void)
{
	/* Clear Flag */
	SET_BIT(TWCR, TWINT);
	/* Check ACK"status code"0x28 */
	while(!GET_BIT(TWCR, TWINT));
	return TWDR;
}










