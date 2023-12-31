/*
 *<<<<<<<<<<<    USART_Private.h   >>>>>>>>>>>>
 *
 *  Author : Rashad
 *  Layer  : MCAL
 *  SWC    : USART
 *
 */
#ifndef USART_PRIVATE_H
#define USART_PRIVATE_H


/*============     [USART]      ============*/
#define     UDR_REG         (*(volatile u8 *)(0x2C))        // USART I/O Data Register – UDR


/*=======   USART [UCSRA]  =======*/
#define     UCSRA_REG       (*(volatile u8 *)(0x2B))        // USART Control and Status Register A – UCSRA

#define     UCSRA_MPCM                0             // Bit 0 – MPCM: Multi-processor Communication Mode
#define     UCSRA_U2X                 1             // Bit 1 – U2X: Double the USART Transmission Speed
#define     UCSRA_PE                  2             // Bit 2 – PE: Parity Error
#define     UCSRA_DOR                 3             // Bit 3 – DOR: Data OverRun
#define     UCSRA_FE                  4             // Bit 4 – FE: Frame Error
#define     UCSRA_UDRE                5             // Bit 5 – UDRE: USART Data Register Empty
#define     UCSRA_TXC                 6             // Bit 6 – TXC: USART Transmit Complete
#define     UCSRA_RXC                 7             // Bit 7 – RXC: USART Receive Complete


/*=======   USART [UCSRB]  =======*/
#define     UCSRB_REG       (*(volatile u8 *)(0x2A))        // USART Control and Status Register B – UCSRA

#define     UCSRB_TXB8                0             // Bit 0 – TXB8: Transmit Data Bit 8
#define     UCSRB_RXB8                1             // Bit 1 – RXB8: Receive Data Bit 8
#define     UCSRB_UCSZ2               2             // Bit 2 – UCSZ2: Character Size
#define     UCSRB_TXEN                3             // Bit 3 – TXEN: Transmitter Enable
#define     UCSRB_RXEN                4             // Bit 4 – RXEN: Receiver Enable
#define     UCSRB_UDRIE               5             // Bit 5 – UDRIE: USART Data Register Empty Interrupt Enable
#define     UCSRB_TXCIE               6             // Bit 6 – TXCIE: TX Complete Interrupt Enable
#define     UCSRB_RXCIE               7             // Bit 7 – RXCIE: RX Complete Interrupt Enable


/*=======   USART [UCSRC]  =======*/
#define     UCSRC_REG       (*(volatile u8 *)(0x40))        // USART Control and Status Register C – UCSRA

#define     UCSRC_UCPOL               0             // Bit 0 – UCPOL: Clock Polarity
#define     UCSRC_UCSZ0               1             // Bit 1 – UCSZ0: Character Size
#define     UCSRC_UCSZ1               2             // Bit 2 – UCSZ1: Character Size
#define     UCSRC_USBS                3             // Bit 3 – USBS: Stop Bit Select
#define     UCSRC_UPM0                4             // Bit 4 – UPM0: Parity Mode
#define     UCSRC_UPM1                5             // Bit 5 – UPM1: Parity Mode
#define     UCSRC_UMSE1               6             // Bit 6 – UMSEL: USART Mode Select
#define     UCSRC_URSEL               7             // Bit 7 – URSEL: Register Select


/*=======   USART [UBRRH] BITS  =======*/
#define 	UBRRH_URSEL                   7             // Bit 7 – URSEL: Register Select
#define     UBRRL_REG       (*(volatile u8 *)(0x29))        // USART Baud Rate Registers – UBRRL
#define     UBRRH_REG       (*(volatile u8 *)(0x40))        // USART Baud Rate Registers – UBRRH


#define NULL                  (void*)(0)


#endif
