
#ifndef EEPROM_H_
#define EEPROM_H_


void EEPROM_VidWriteDataByte(u16 Copy_u16ByteAddress,u8 Copy_u8ByteData);

u8 EEPROM_u8ReadDataByte(u16 Copy_u16ByteAddress);


#define Init_Address		0x50            //0b1010 0000      0b0101 0000   0x50

#define A2_PIN			    0

#endif /* EEPROM_H_ */
