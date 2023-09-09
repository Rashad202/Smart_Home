#ifndef TWI_H_
#define TWI_H_

void TWI_VidMasterInit(void);

void TWI_VidSlaveInit(u8 Copy_u8Address);

void TWI_VidStartCondition(void);

void TWI_VidReStartCondition(void);

void TWI_VidStopCondition(void);

void TWI_VidSlaveAddWrite(u8 Copy_u8SlaveAdd);

void TWI_VidSlaveAddRead(u8 Copy_u8SlaveAdd);

void TWI_VidMasterSendData(u8 Copy_u8Data);

u8 TWI_VidSlaveReadData(void);

u8 TWI_u8MasterRecieveData(void);


#endif /* TWI_H_ */
