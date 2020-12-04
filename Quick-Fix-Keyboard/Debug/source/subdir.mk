################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/Circular_buffer.c \
../source/Command_logger.c \
../source/Command_process.c \
../source/DAC_config.c \
../source/Quick-Fix-Keyboard.c \
../source/Uart.c \
../source/analog_out.c \
../source/jinglebells.c \
../source/keypad.c \
../source/mtb.c \
../source/piyu_bole.c \
../source/rabta.c \
../source/semihost_hardfault.c \
../source/sin_trig.c \
../source/test_cbfifo.c \
../source/test_sin.c 

OBJS += \
./source/Circular_buffer.o \
./source/Command_logger.o \
./source/Command_process.o \
./source/DAC_config.o \
./source/Quick-Fix-Keyboard.o \
./source/Uart.o \
./source/analog_out.o \
./source/jinglebells.o \
./source/keypad.o \
./source/mtb.o \
./source/piyu_bole.o \
./source/rabta.o \
./source/semihost_hardfault.o \
./source/sin_trig.o \
./source/test_cbfifo.o \
./source/test_sin.o 

C_DEPS += \
./source/Circular_buffer.d \
./source/Command_logger.d \
./source/Command_process.d \
./source/DAC_config.d \
./source/Quick-Fix-Keyboard.d \
./source/Uart.d \
./source/analog_out.d \
./source/jinglebells.d \
./source/keypad.d \
./source/mtb.d \
./source/piyu_bole.d \
./source/rabta.d \
./source/semihost_hardfault.d \
./source/sin_trig.d \
./source/test_cbfifo.d \
./source/test_sin.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MKL25Z128VLK4_cm0plus -DCPU_MKL25Z128VLK4 -DSDK_OS_BAREMETAL -DFSL_RTOS_BM -DSDK_DEBUGCONSOLE=0 -DPRINTF_FLOAT_ENABLE=1 -DSDK_DEBUGCONSOLE_UART -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D__REDLIB__ -I"D:\MCUXpressoIDE_11.2.0_4120\Quick-Fix-Keyboard\board" -I"D:\MCUXpressoIDE_11.2.0_4120\Quick-Fix-Keyboard\source" -I"D:\MCUXpressoIDE_11.2.0_4120\Quick-Fix-Keyboard" -I"D:\MCUXpressoIDE_11.2.0_4120\Quick-Fix-Keyboard\drivers" -I"D:\MCUXpressoIDE_11.2.0_4120\Quick-Fix-Keyboard\CMSIS" -I"D:\MCUXpressoIDE_11.2.0_4120\Quick-Fix-Keyboard\utilities" -I"D:\MCUXpressoIDE_11.2.0_4120\Quick-Fix-Keyboard\startup" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


