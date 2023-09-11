
I am excited to announce that I have completed the 1-month Embedded Systems program conducted by Information Technology Institute (ITI) !

In my graduation project, I  build a simulation for a smart home using ATmega32. The project included multiple features, such as:
Smart Home System Controlled by Two MCUs AVR Microcontroller using USART and I2C Communication Protocols.
Components :-
 2 atmega32   --   EEPROM -- 2LCD16x2 -- Keypad --  Servo Motor  -- Buzzer  --  LM35 (Temp) --   DC Motors  --  LEDs"many Types" -- LDR  -- Gas Sensor
Software Architecture Layers :-
APP >>
	 main.c 
LIB >> 
	- STD_TYPES.h   		- BIT_MATH.h 
HAL >> 
	- LED 	- LCD  	-KPAD 	-EEPROM      -SERVO_MOTOR          -DC MOTOR
MCAL >> 
 	-DIO 	-ACD  	-GIE 	-TIMERS        -PWM 	       -USART        -I2C 



The system is divided into two parts :

->> User Interface 
->> Control Home 

This System is designed, developed and tested by Me.
The System of Home Full Controlled by the User. Master AVR will Display all Systems on LCD .

System Features :-
1- Security System :-
 A Password Saved in EEPROM by I2C Communication Protocol. at Start of System The Program ask  password. you have Three tries only to entre the correct password. after Three tries of Rong Password the System will Alarm by Turn On Buzzer and Close the System. if user entre the correct Password the System will start and Open The Door by Servo Motor and Buzzer Turn On.


Options Menu :
 in all options < Master will Send this Data to Slave. Slave will Run Functions to Turn ON or OFF the Target System. Slave will Show the Status of Home on LCD. 

1-Room1:
In this option , you can choose  by KYPAD " Light System  or Fan " to apply any action ( Turn ON or OFF ).
2-Room2:
In this option , you can choose  by KYPAD " Light System  or Fan " to apply any action ( Turn ON or OFF ).
3-Kitchen:
In this option , you can choose  by KYPAD " Light System  or Oven " to apply any action ( Turn ON or OFF ).
->>More option
4-Reception:
In this option , you can choose  by KYPAD " Light System  or TV " to apply any action ( Turn ON or OFF ).


5- Automatic Mode :
In this Mode The System of Home Full Controlled Automaticly by AVR. Slave When Recieve Automatic Mode will control the Home by Reading of all Sensors

->> Air conditioner 
Controlled by Reading of Temperature Sensor, if Temperature More than 25 C System Will Open Air conditioner and Turn ON Air Conditions "2 Dc Motor". else if Temperature Less than 25 C System Will Close Air conditioner .
->> Light OutDoor
Controlled by Reading of LDR Sensor, if Light of Sun is High System will Turn OFF the Light of Home, else if Light of Sun is Low System will Turn ON the Light of Home.
->> Gas Sensor Fire 
Fire Alarm System Controlled by Reading of Gas Sensor, if Gas Sensor starts, System Will Open The Water Pumb  and show (Fire Fire !! )(Water Pump ON)on LCD.

I am grateful to my instructors, Mohamed Ramadan and Ahmed Elsayed , for their guidance and support throughout the program and  for their unwavering support and invaluable knowledge during my 𝐈𝐓𝐈 training journey.

This program has given me a strong foundation in embedded systems engineering. I am confident that this knowledge will be valuable in my future career.



