################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/main.c 

OBJS += \
./src/main.o 

C_DEPS += \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"D:\Final_WDG_AVR\gpio" -I"D:\Final_WDG_AVR\buzzer" -I"D:\Final_WDG_AVR\Exti" -I"D:\Final_WDG_AVR\GICR" -I"D:\Final_WDG_AVR\Lcd" -I"D:\Final_WDG_AVR\lib" -I"D:\Final_WDG_AVR\led_mrg" -I"D:\Final_WDG_AVR\src" -I"D:\Final_WDG_AVR\timer" -I"D:\Final_WDG_AVR\WDG_drv" -I"D:\Final_WDG_AVR\WDGMrh" -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega328p -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


