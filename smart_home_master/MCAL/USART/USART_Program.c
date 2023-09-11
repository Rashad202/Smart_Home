/*
 *<<<<<<<<<<<    USART_Program.c   >>>>>>>>>>>>
 *
 *  Author : Rashad
 *  Layer  : MCAL
 *  SWC    : USART
 *
 */
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

/* Include My own Header Files*/
#include "USART_Interface.h"
#include "USART_Private.h"
#include "USART_Config.h"

/* Global Pointer to Function */
void (*Global_PF_Vector_15)(void)  = NULL ;
/* Global Variables */
u8 Global_u8TXData = 0 ;
u8 *Global_u8RXData = 0 ;


void USART_voidInit (void)
{

/*          BAUD RATE Selection         */
    CLR_BIT(UBRRH_REG,UBRRH_URSEL);                    // access UBRRH to Configer the BAUD Rate
    u16 UBRR = 0 ;
    #if( SPEED == NORMAL_SPEED )                         // U2X = 1  Normal Speed Transsmition
        UBRR = ( CPU_CLK / ( BAUD_RATE * 8UL ) ) - 1 ;
    #elif( SPEED == DOUBBLE_SPEED )                      // U2X = 0  Double Speed Transsmition
        UBRR = ( CPU_CLK / ( BAUD_RATE * 16UL ) ) - 1 ;
    #endif
    UBRRL_REG = (u8)(UBRR);                     // first 8 Bit
    UBRRH_REG = (u8)(UBRR >> 8);                // second 8 Bit

/*        USART Initilization           */
    SET_BIT(UCSRC_REG,UCSRC_URSEL);             // Select UCSRC_REG
    CLR_BIT(UCSRC_REG,UCSRC_UMSE1);           // select Async Mode

/*         Select Parity Mode           */    
    #if ( Parity_Mode == DISABLE )              // Select Parity (Disable)
        CLR_BIT(UCSRC_REG,UCSRC_UPM0);
        CLR_BIT(UCSRC_REG,UCSRC_UPM1);
    #elif ( Parity_Mode == EVEN )               // Select Parity (EVEN)
        CLR_BIT(UCSRC_REG,UCSRC_UPM0);
          SET_BIT(UCSRC_REG,UCSRC_UPM1);
    #elif ( Parity_Mode == ODD )                // Select Parity (ODD)
          SET_BIT(UCSRC_REG,UCSRC_UPM0);
          SET_BIT(UCSRC_REG,UCSRC_UPM1);   
    #endif

/*          Select STOP BIT             */
    #if ( STOP_BIT == ONE )
    CLR_BIT(UCSRC_REG,UCSRC_USBS);             // select 1 Stop Bit
    #elif ( STOP_BIT == TWO )
      SET_BIT(UCSRC_REG,UCSRC_USBS);             // select 2 Stop Bit
    #endif

/*       Select Character Size          */

#if 	DATA_SIZE == DATA_SIZE_5_BIT
		CLR_BIT(UCSRC_REG , UCSRC_UCSZ0) ;
		CLR_BIT(UCSRC_REG , UCSRC_UCSZ1) ;
		CLR_BIT(UCSRB_REG , UCSRB_UCSZ2) ;
	#elif DATA_SIZE == DATA_SIZE_6_BIT
		SET_BIT(UCSRC_REG , UCSRC_UCSZ0) ;
		CLR_BIT(UCSRC_REG , UCSRC_UCSZ1) ;
		CLR_BIT(UCSRB_REG , UCSRB_UCSZ2) ;
	#elif DATA_SIZE == DATA_SIZE_7_BIT
		CLR_BIT(UCSRC_REG , UCSRC_UCSZ0) ;
		SET_BIT(UCSRC_REG , UCSRC_UCSZ1) ;
		CLR_BIT(UCSRB_REG , UCSRB_UCSZ2) ;
	#elif DATA_SIZE == DATA_SIZE_8_BIT
		SET_BIT(UCSRC_REG , UCSRC_UCSZ0) ;
		SET_BIT(UCSRC_REG , UCSRC_UCSZ1) ;
		CLR_BIT(UCSRB_REG , UCSRB_UCSZ2) ;
	#elif DATA_SIZE == DATA_SIZE_5_BIT
		SET_BIT(UCSRC_REG , UCSRC_UCSZ0) ;
		SET_BIT(UCSRC_REG , UCSRC_UCSZ1) ;
		SET_BIT(UCSRB_REG , UCSRB_UCSZ2) ;
	#else
		#error Wrong DATA_SIZE config
	#endif



/*          Enable RX & TX              */     
    SET_BIT(UCSRB_REG,UCSRB_TXEN);               // Enable TX 
    SET_BIT(UCSRB_REG,UCSRB_RXEN);               // Enable RX 

}

void USART_voidSendData (u8 Copy_u8Data)
{
    // Polling flag Data Register is Empty.
    while ( (GET_BIT(UCSRA_REG,UCSRA_UDRE)) == 0 );
    // Transsmit Data.
    UDR_REG = Copy_u8Data ;
    /* Data Transsmition is Complete So The Flag of [UCSRA_TXC] is Raised */
    /* Then we Need Clear This Flag by SET ONE , To Next Transsmition     */
    SET_BIT(UCSRA_REG,UCSRA_TXC);
}


void USART_voidRecieveData (u8 *Copy_Pu8Data)
{
    // Polling flag Data Recieve is Complete.
    while ( (GET_BIT(UCSRA_REG,UCSRA_RXC)) == 0 );
    // Recieve Data in Passing Pointer.
    *Copy_Pu8Data = UDR_REG ;
}


void USART_voidAsyncSendData ( u8 Copy_u8Data , u8 *Copy_Pu8CallBackFunIndication_TXC )
{
    SET_BIT(UCSRB_REG,UCSRB_UDRIE);                              // Enable UDRIE Data Register Empty Interrupt Enable.
    SET_BIT(UCSRB_REG,UCSRB_TXCIE);                              // Enable TXCIE Transmitt Complete Interrupt Enable.( For Indication )
    Global_u8TXData = Copy_u8Data ;                              // Assign Data to Global Variable to use it in ISR Fun.
    Global_PF_Vector_15 = Copy_Pu8CallBackFunIndication_TXC ;    // Assign The pointer that contain adderss of App CallBack Fun to Global pointer to Call it in ISR Fun.
}


void USART_voidAsyncRecieveData (u8 *Copy_Pu8Data)
{
    SET_BIT(UCSRB_REG,UCSRB_RXCIE);            // Enable RXCIE Recieve Complete Interrupt Enable.
    Global_u8RXData = Copy_Pu8Data ;           // assign Passing Pointer to Global Pointer to Read Revived Data on This Passing Pointer in ISR (RXCIE)
}

void __vector_13 (void)    __attribute__((signal));
void __vector_13 (void)
{
    *Global_u8RXData = UDR_REG ;        // Recieve Data in Passing Pointer.
}



void __vector_14 (void)    __attribute__((signal));
void __vector_14 (void)
{ 
    UDR_REG = Global_u8TXData ;         // Transsmit Data.
}


void __vector_15 (void)    __attribute__((signal));
void __vector_15 (void)
{
   Global_PF_Vector_15 () ; // Call App Function That Indicator to Transmittion Complete.
}
