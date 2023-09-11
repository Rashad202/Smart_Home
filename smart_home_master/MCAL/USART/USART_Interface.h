/*
 *<<<<<<<<<<<    USART_Interface.h   >>>>>>>>>>>>
 *
 *  Author : Rashad
 *  Layer  : MCAL
 *  SWC    : USART
 *
 */


#ifndef USART_INTERFACE_H
#define USART_INTERFACE_H
/*   Select Data Size      */
#define DATA_SIZE_5_BIT		                    0
#define DATA_SIZE_6_BIT		                    1
#define DATA_SIZE_7_BIT		                    2
#define DATA_SIZE_8_BIT		                    3
#define DATA_SIZE_9_BIT		                    4

/*   Select Normal or Double Speed Transsmition  */
#define     DOUBBLE_SPEED           0
#define     NORMAL_SPEED            1

/*    Select Parity Mode EVEN , ODD , DISABLE    */
#define     DISABLE                  0
#define     EVEN                     1
#define     ODD                      2

/*        Select STOP BIT  { ONE , TWO }         */
#define     ONE                      0
#define     TWO                      1



void USART_voidInit (void);


void USART_voidSendData (u8 Copy_u8Data);


void USART_voidRecieveData (u8 *Copy_Pu8Data);


void USART_voidAsyncSendData ( u8 Copy_u8Data , u8 *Copy_Pu8CallBackFunIndication_TXC );


void USART_voidAsyncRecieveData (u8 *Copy_Pu8Data);

#endif
