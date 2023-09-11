/*
 *<<<<<<<<<<<    TIMER_Interface.h   >>>>>>>>>>>>
 *
 *  Author : Rashad
 *  Layer  : MCAL
 *  SWC    : Timer
 *
 */
#ifndef TIMER0_INTERFACE_H
#define TIMER0_INTERFACE_H

/*              TIMER0 Mode Selection            */
#define     NORMAL_OVF                   0
#define     PWM_PHASECORRECT             1
#define     CTC                          2
#define     FAST_PWM                     3

/*               OC0 Mode Selection                         */
#define     DISCONNECTED                                    0
#define     SETonTOP_CLEARonCOMPARE                         1
#define     SETonCOMPARE_CLEARonTOP                         2
#define     SETonCOMPdownCounting_CLEARonCOMPupCounting     3
#define     SETonCOMPupCounting_CLEARonCOMPdownCounting     4

/*          TIMER0 Prescaller Selection          */
#define     NO_CLK_SOURCE_TIMER_STOPED          0
#define     NOT_USE_PRESCALER                   1
#define     PRESCALER_DIVISION_BY_8             8
#define     PRESCALER_DIVISION_BY_64            64
#define     PRESCALER_DIVISION_BY_256           256
#define     PRESCALER_DIVISION_BY_1024          1024
#define     EXTERNAL_CLK_SOURCE_FALLING_EDGE    6
#define     EXTERNAL_CLK_SOURCE_RAISING_EDGE    7


void TIMER0_voidInit (void);


void TIMER0_voidSetCallBack_OVF (void (*Local_PointerToFunction_OVF) (void));


void TIMER0_voidSetCallBack_CTC (void (*Local_PointerToFunction_CTC) (void));


void TIMER0_voidSetPreloadValue ( u8 Copy_u8PreloadValue );


void TIMER0_voidSetCompareMatchValue ( u8 Copy_u8CompareMatchValue );


void TIMER0_voidSetBusyWait_ms ( u32 Copy_u32Time_ms );


void TIMER0_voidPWM ( u8 Local_u8CompareMatchValue );


void TIMER0_voidSetCallBack_CTC_andRequiredTime_ms (void (*Local_PointerToFunction_CTC) (void),u32 Copy_u32Time_ms);


#endif
