#ifndef USART_CONFIG_H
#define USART_CONFIG_H

#define     CPU_CLK             8000000
#define     BAUD_RATE           9600

/*
 Set Data Size

   DATA_SIZE_5_BIT
   DATA_SIZE_6_BIT
   DATA_SIZE_7_BIT
   DATA_SIZE_8_BIT
   DATA_SIZE_9_BIT
 */
#define DATA_SIZE				DATA_SIZE_8_BIT

/*
     Select Normal or Double Speed Transsmition
     DOUBBLE_SPEED
     NORMAL_SPEED
*/

#define     SPEED            DOUBBLE_SPEED




/*
     Select Parity Mode
     EVEN
     ODD
     DISABLE

*/

#define     Parity_Mode             DISABLE



/*        Select STOP BIT  { ONE , TWO }         */

#define     STOP_BIT                ONE

#endif
