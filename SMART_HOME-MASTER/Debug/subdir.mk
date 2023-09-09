################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ADC.c \
../DIO_Program.c \
../EEPROM.c \
../KPD_Program.c \
../LCD_Program.c \
../SERVOMOTOR_Program.c \
../TWI.c \
../UART.c \
../main.c 

OBJS += \
./ADC.o \
./DIO_Program.o \
./EEPROM.o \
./KPD_Program.o \
./LCD_Program.o \
./SERVOMOTOR_Program.o \
./TWI.o \
./UART.o \
./main.o 

C_DEPS += \
./ADC.d \
./DIO_Program.d \
./EEPROM.d \
./KPD_Program.d \
./LCD_Program.d \
./SERVOMOTOR_Program.d \
./TWI.d \
./UART.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


