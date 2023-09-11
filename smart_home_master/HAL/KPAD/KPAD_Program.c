#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

/* Include Header Files From MCAL Layer */
#include "../../MCAL/DIO/DIO_Interface.h"

/* Include My own Header Files*/
#include "KPAD_Interface.h"
#include "KPAD_Private.h"
#include "KPAD_Config.h"

/* Global Arrays */
u8 KPAD_Au8ColumnsArr[KPAD_COLUMNS_NUM] = { KPAD_C0_PIN , KPAD_C1_PIN , KPAD_C2_PIN , KPAD_C3_PIN };
u8 KPAD_Au8RowsArr[KPAD_ROWS_NUM] = { KPAD_R0_PIN , KPAD_R1_PIN , KPAD_R2_PIN , KPAD_R3_PIN };
u8 KPAD_Au8KeysArr[KPAD_ROWS_NUM][KPAD_COLUMNS_NUM] = KPAD_KEYS ;





void KPAD_voidInit (void)
{
    /* Configer The Direction of Coloums Pins as DIO_OUTPUT */
    DIO_voidSetPinDirection (KPAD_PORT,KPAD_C0_PIN,DIO_OUTPUT);
    DIO_voidSetPinDirection (KPAD_PORT,KPAD_C1_PIN,DIO_OUTPUT);
    DIO_voidSetPinDirection (KPAD_PORT,KPAD_C2_PIN,DIO_OUTPUT);
    DIO_voidSetPinDirection (KPAD_PORT,KPAD_C3_PIN,DIO_OUTPUT);

    /* Configer The Direction of Rows Pins as DIO_INPUT */
    DIO_voidSetPinDirection (KPAD_PORT,KPAD_R0_PIN,DIO_INPUT);
    DIO_voidSetPinDirection (KPAD_PORT,KPAD_R1_PIN,DIO_INPUT);
    DIO_voidSetPinDirection (KPAD_PORT,KPAD_R2_PIN,DIO_INPUT);
    DIO_voidSetPinDirection (KPAD_PORT,KPAD_R3_PIN,DIO_INPUT);

    /* Activate Pull-Up Res in Pins of Rows */
	DIO_voidConfig_Pull_Up_Pin (KPAD_PORT,KPAD_R0_PIN,DIO_ON);
	DIO_voidConfig_Pull_Up_Pin (KPAD_PORT,KPAD_R1_PIN,DIO_ON);
	DIO_voidConfig_Pull_Up_Pin (KPAD_PORT,KPAD_R2_PIN,DIO_ON);
	DIO_voidConfig_Pull_Up_Pin (KPAD_PORT,KPAD_R3_PIN,DIO_ON);


    /* Deactivate Coloum Pins  */      
    DIO_voidSetPinValue (KPAD_PORT,KPAD_C0_PIN,DIO_HIGH);
    DIO_voidSetPinValue (KPAD_PORT,KPAD_C1_PIN,DIO_HIGH);
    DIO_voidSetPinValue (KPAD_PORT,KPAD_C2_PIN,DIO_HIGH);
    DIO_voidSetPinValue (KPAD_PORT,KPAD_C3_PIN,DIO_HIGH);
}





u8   KPAD_u8GetPressedKey (void)
{
    u8 Local_u8ColumnsIter ;
    u8 Local_u8RowsIter ;
    u8 Local_u8PinValue ;
    u8 Local_u8PressedKey = 0xff ; // return will be 0xff if not pressed any key 
    u8 Local_u8Flag = 0 ;
    for ( Local_u8ColumnsIter = 0 ; Local_u8ColumnsIter < KPAD_COLUMNS_NUM ; Local_u8ColumnsIter ++ )
    {
        /* Active the current Column */
        DIO_voidSetPinValue ( KPAD_PORT , KPAD_Au8ColumnsArr[Local_u8ColumnsIter] , DIO_LOW );

        for ( Local_u8RowsIter = 0 ; Local_u8RowsIter < KPAD_ROWS_NUM ; Local_u8RowsIter ++ )
        {
            /* Delay for Debounsing 
             * _delay_ms(50);
             * Read Row Pin */
            Local_u8PinValue = DIO_u8GetPinValue ( KPAD_PORT , KPAD_Au8RowsArr[Local_u8RowsIter] );

            /* Key Pressed */
            if ( Local_u8PinValue == 0 )
            {
                /* More Checking again for Debounsing */
                while ( Local_u8PinValue == 0 )
                {
                    /* Get pressed Key Value when i make sure that the DIO_LOW state is stable  */
                    Local_u8PressedKey = KPAD_Au8KeysArr[Local_u8RowsIter][Local_u8ColumnsIter] ;
                    /* Read Row Pin again for sure for Debounsing and exit while loop when change at pressed button 
                    whithout it the program will not extern about while loop */
                    Local_u8PinValue = DIO_u8GetPinValue ( KPAD_PORT , KPAD_Au8RowsArr[Local_u8RowsIter] );
                    Local_u8Flag = 1 ;
                }
                Local_u8PressedKey = KPAD_Au8KeysArr[Local_u8RowsIter][Local_u8ColumnsIter] ;
                break;
            }
        }
        /* Active the current Column */
        DIO_voidSetPinValue ( KPAD_PORT , KPAD_Au8ColumnsArr[Local_u8ColumnsIter] , DIO_HIGH );
        if ( Local_u8Flag == 1 )
        {
            break;
        }
    }
    return Local_u8PressedKey ;
}

