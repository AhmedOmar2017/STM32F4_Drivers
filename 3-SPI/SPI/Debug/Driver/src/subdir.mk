################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Driver/src/HAL.c 

OBJS += \
./Driver/src/HAL.o 

C_DEPS += \
./Driver/src/HAL.d 


# Each subdirectory must supply rules for building sources it contributes
Driver/src/%.o Driver/src/%.su: ../Driver/src/%.c Driver/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F401RCTx -c -I../Inc -I"D:/courses/Done/Embedded & Electronics/Mastering Microcontroller and Embedded Driver Development/Drivers/code_updates/3-SPI/SPI/Driver/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Driver-2f-src

clean-Driver-2f-src:
	-$(RM) ./Driver/src/HAL.d ./Driver/src/HAL.o ./Driver/src/HAL.su

.PHONY: clean-Driver-2f-src

