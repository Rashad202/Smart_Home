/*
 *<<<<<<<<<<<    TIMER_program.c   >>>>>>>>>>>>
 *
 *  Author : Rashad
 *  Layer  : MCAL
 *  SWC    : Timer
 *
 */
#include "../../../LIB/STD_TYPES.h"
#include "../../../LIB/BIT_MATH.h"
/* Include My own Header Files*/
#include "TIMER0_Interface.h"
#include "TIMER0_Private.h"
#include "TIMER0_Config.h"

void (*Global_PointerToFunction_OVF_T0) (void) = NULL ; 
void (*Global_PointerToFunction_CTC_T0) (void) = NULL ; 
u16 Global_u8PreloadValue = 0 ;
u16 Global_u8CompareMatchValue = 0 ;
u32 Global_u32Time_ms = 0 ;


void TIMER0_voidInit (void)
{

/*         TIMER0 Mode Selection        */
    #if (MODE == NORMAL_OVF)                             // OVF Normal Mode of Timer/Counter0
        CLR_BIT(TCCR0_REG,TIMER0_TCCR0_WGM00);
        CLR_BIT(TCCR0_REG,TIMER0_TCCR0_WGM01);
		SET_BIT(TIMSK_REG,TIMER0_TIMSK_TOIE0);          // Enable T0 OVF Interrupt [PIE].        

    #elif (MODE == PWM_PHASECORRECT)                     // PWM_Phase Correct Mode of Timer/Counter0
        SET_BIT(TCCR0_REG,TIMER0_TCCR0_WGM00);
        CLR_BIT(TCCR0_REG,TIMER0_TCCR0_WGM01);
        
        /*          OC0 Mode Selection          */
        #if ( OC0_MODE == DISCONNECTED )
            CLR_BIT(TCCR0_REG,TIMER0_TCCR0_COM00);
            CLR_BIT(TCCR0_REG,TIMER0_TCCR0_COM01);
        #elif ( OC0_MODE == SETonCOMPdownCounting_CLEARonCOMPupCounting )
            CLR_BIT(TCCR0_REG,TIMER0_TCCR0_COM00);
            SET_BIT(TCCR0_REG,TIMER0_TCCR0_COM01);
        #elif ( OC0_MODE == SETonCOMPupCounting_CLEARonCOMPdownCounting )
            SET_BIT(TCCR0_REG,TIMER0_TCCR0_COM00);
            SET_BIT(TCCR0_REG,TIMER0_TCCR0_COM01);
        #else 
            #error  Wrong selection of OC0 mode
        #endif

    #elif (MODE == CTC)                                  // CTC Mode of Timer/Counter0
        CLR_BIT(TCCR0_REG,TIMER0_TCCR0_WGM00);
        SET_BIT(TCCR0_REG,TIMER0_TCCR0_WGM01);
		SET_BIT(TIMSK_REG,TIMER0_TIMSK_OCIE0);          // Enable T0 CTC Interrupt [PIE]. 

    #elif (MODE == FAST_PWM)                             // Fast-PWM Mode of Timer/Counter0
        SET_BIT(TCCR0_REG,TIMER0_TCCR0_WGM00);
        SET_BIT(TCCR0_REG,TIMER0_TCCR0_WGM01);

        /*          OC0 Mode Selection          */
        #if ( OC0_MODE == DISCONNECTED )
            CLR_BIT(TCCR0_REG,TIMER0_TCCR0_COM00);
            CLR_BIT(TCCR0_REG,TIMER0_TCCR0_COM01);
        #elif ( OC0_MODE == SETonTOP_CLEARonCOMPARE )
            CLR_BIT(TCCR0_REG,TIMER0_TCCR0_COM00);
            SET_BIT(TCCR0_REG,TIMER0_TCCR0_COM01);
        #elif ( OC0_MODE == SETonCOMPARE_CLEARonTOP )
            SET_BIT(TCCR0_REG,TIMER0_TCCR0_COM00);
            SET_BIT(TCCR0_REG,TIMER0_TCCR0_COM01);
        #else 
            #error  Wrong selection of OC0 mode
        #endif

    #else 
        #error  Wrong selection of operation mode
    #endif 


/*     TIMER0 Prescaller Selection      */
    TCCR0_REG = ( TCCR0_REG & 0b11111000 );              // Clear Prescaller 

    #if( PRESCALER == NO_CLK_SOURCE_TIMER_STOPED )          
        CLR_BIT(TCCR0_REG,TIMER0_TCCR0_CS00);
        CLR_BIT(TCCR0_REG,TIMER0_TCCR0_CS01);
        CLR_BIT(TCCR0_REG,TIMER0_TCCR0_CS02);
    #elif ( PRESCALER == NOT_USE_PRESCALER )
        SET_BIT(TCCR0_REG,TIMER0_TCCR0_CS00);
        CLR_BIT(TCCR0_REG,TIMER0_TCCR0_CS01);
        CLR_BIT(TCCR0_REG,TIMER0_TCCR0_CS02);
    #elif ( PRESCALER == PRESCALER_DIVISION_BY_8 )
        CLR_BIT(TCCR0_REG,TIMER0_TCCR0_CS00);
        SET_BIT(TCCR0_REG,TIMER0_TCCR0_CS01);
        CLR_BIT(TCCR0_REG,TIMER0_TCCR0_CS02);
    #elif ( PRESCALER == PRESCALER_DIVISION_BY_64 )
        SET_BIT(TCCR0_REG,TIMER0_TCCR0_CS00);
        SET_BIT(TCCR0_REG,TIMER0_TCCR0_CS01);
        CLR_BIT(TCCR0_REG,TIMER0_TCCR0_CS02);
    #elif ( PRESCALER == PRESCALER_DIVISION_BY_256 )
        CLR_BIT(TCCR0_REG,TIMER0_TCCR0_CS00);
        CLR_BIT(TCCR0_REG,TIMER0_TCCR0_CS01);
        SET_BIT(TCCR0_REG,TIMER0_TCCR0_CS02);
    #elif ( PRESCALER == PRESCALER_DIVISION_BY_1024 )
        SET_BIT(TCCR0_REG,TIMER0_TCCR0_CS00);
        CLR_BIT(TCCR0_REG,TIMER0_TCCR0_CS01);
        SET_BIT(TCCR0_REG,TIMER0_TCCR0_CS02);
    #elif ( PRESCALER == EXTERNAL_CLK_SOURCE_FALLING_EDGE )
        CLR_BIT(TCCR0_REG,TIMER0_TCCR0_CS00);
        SET_BIT(TCCR0_REG,TIMER0_TCCR0_CS01);
        SET_BIT(TCCR0_REG,TIMER0_TCCR0_CS02);
    #elif ( PRESCALER == EXTERNAL_CLK_SOURCE_RAISING_EDGE )
        SET_BIT(TCCR0_REG,TIMER0_TCCR0_CS00);
        SET_BIT(TCCR0_REG,TIMER0_TCCR0_CS01);
        SET_BIT(TCCR0_REG,TIMER0_TCCR0_CS02);
    #else
        #error  Wrong selection of Prescaller mode
    #endif

}


void TIMER0_voidSetCallBack_OVF (void (*Local_PointerToFunction_OVF) (void))
{
    Global_PointerToFunction_OVF_T0 = Local_PointerToFunction_OVF ;
}


void TIMER0_voidSetCallBack_CTC (void (*Local_PointerToFunction_CTC) (void))
{
    Global_PointerToFunction_CTC_T0 = Local_PointerToFunction_CTC ;
}

void TIMER0_voidSetPreloadValue ( u8 Local_u8PreloadValue )
{
    #if (MODE == NORMAL_OVF)
        TCNT0_REG = Local_u8PreloadValue ;
        Global_u8PreloadValue = Local_u8PreloadValue ;
    #else
        // No Action
    #endif
}


void TIMER0_voidSetCompareMatchValue ( u8 Local_u8CompareMatchValue )
{
    #if (MODE == CTC)
        OCR0_REG = Local_u8CompareMatchValue ;
        Global_u8CompareMatchValue = Local_u8CompareMatchValue ;
    #elif ( MODE == FAST_PWM )
        OCR0_REG = Local_u8CompareMatchValue ;
    #elif (MODE == PWM_PHASECORRECT)
        OCR0_REG = Local_u8CompareMatchValue ;
    #endif
}

void TIMER0_voidSetCallBack_CTC_andRequiredTime_ms (void (*Local_PointerToFunction_CTC) (void),u32 Copy_u32Time_ms)
{
    TIMER0_voidSetCompareMatchValue (200);
    TIMER0_voidSetCallBack_CTC (Local_PointerToFunction_CTC);
    Global_u32Time_ms = Copy_u32Time_ms ;
}


void TIMER0_voidSetBusyWait_ms ( u32 Copy_u32Time_ms )
{
    CLR_BIT(TIMSK_REG,TIMER0_TIMSK_OCIE0);              // Disable T0 CTC Interrupt [PIE].
    u32 Counter_CTC = 0 ;
    TIMER0_voidSetCompareMatchValue (200);
    Counter_CTC = ( Copy_u32Time_ms * 1000UL ) /200 ;     // Counter_CTC = (Required Time(ms) * 1000) / (Compare Match Value)
    u32 iter = 0 ;
    for ( iter =0 ; iter < Counter_CTC ; iter++)
    {
    	u8 Local_u8Flag ;
    	Local_u8Flag = GET_BIT(TIFR_REG,TIMER0_TIFR_OCF0);
    	while ( Local_u8Flag == 0 )
    	{
    		Local_u8Flag = GET_BIT(TIFR_REG,TIMER0_TIFR_OCF0);      // Polling in the CTC Flag
    	}
		SET_BIT(TIFR_REG,TIMER0_TIFR_OCF0);						    // Clear Flag
    }
    SET_BIT(TIMSK_REG,TIMER0_TIMSK_OCIE0);          // Enable T0 CTC Interrupt [PIE]. 
}


void TIMER0_voidPWM ( u8 Local_u8CompareMatchValue )
{
    TIMER0_voidSetCompareMatchValue ( Local_u8CompareMatchValue );
}
/*  // For Loop to Increase PWM and Decrease PWM used in APPLICATION.
    for ( u16 Counter=0 ; Counter <= 255 ; Counter++ )
    {
        TIMER0_voidPWM (Counter);
        _delay_ms(10);
    }
    for ( u16 Counter=0 ; Counter <= 255 ; Counter++ )
    {
        TIMER0_voidPWM (255-Counter);
        _delay_ms(10);
    }
*/



/**************     [ISR] to OVF     *************/
void __vector_11 (void)   __attribute__((signal));
void __vector_11 (void)
{
    static u16 counter = 0 ;
    counter ++ ;
    if ( counter == 3907 )
    {
        if(Global_PointerToFunction_OVF_T0 != NULL)
		{
    		Global_PointerToFunction_OVF_T0();                 // Action of OVF Application Function
		}
        counter = 0 ;                                       // For Next Period.
        TCNT0_REG = Global_u8PreloadValue ;                 // For Next Period Preload Value.
    }
}

/**************     [ISR] to CTC     *************/
void __vector_10 (void)   __attribute__((signal));
void __vector_10 (void)
{
    u32 Counter_CTC = 0 ;
    Counter_CTC = ( Global_u32Time_ms * 1000UL ) / (200) ;        // Counter_CTC = (Required Time(ms) * 1000) / (Compare Match Value)
    static u16 counter = 0 ;
    counter ++ ;
    if(Global_u32Time_ms == 0)
    {
        if ( counter == 5000 )
        {
            if(Global_PointerToFunction_CTC_T0 != NULL)
		    {
                Global_PointerToFunction_CTC_T0();                  // Action of CTC Application Function 
		    }                
            counter = 0 ;                                        // For Next Period.
            OCR0_REG = Global_u8CompareMatchValue ;              // For Next Period Compare Match Value.
        }
    }
    else
    {
        if ( counter == Counter_CTC )
        {
            if(Global_PointerToFunction_CTC_T0 != NULL)
		    {
                Global_PointerToFunction_CTC_T0();                  // Action of CTC Application Function 
		    }                
            counter = 0 ;                                        // For Next Period.
            OCR0_REG = Global_u8CompareMatchValue ;              // For Next Period Compare Match Value.
        }
    }
    
}
