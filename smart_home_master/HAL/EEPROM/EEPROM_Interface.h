#ifndef EEPROM_INTERFACE_H
#define EEPROM_INTERFACE_H

void EEPROM_voidSendDataByte ( u16 Copy_u16LocationAddress , u8 Copy_u8DataByte );


u8 EEPROM_voidReadDataByte ( u16 Copy_u16LocationAddress );


#endif