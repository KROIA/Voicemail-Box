################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/Users/Alex/Dokumente/Schule/EmbSys2/Audio_playback_and_record/Utilities/Log/lcd_log.c 

OBJS += \
./Utilities/lcd_log.o 

C_DEPS += \
./Utilities/lcd_log.d 


# Each subdirectory must supply rules for building sources it contributes
Utilities/lcd_log.o: D:/Users/Alex/Dokumente/Schule/EmbSys2/Audio_playback_and_record/Utilities/Log/lcd_log.c Utilities/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_USB_FS -DUSE_STM32469I_DISCOVERY -DUSE_HAL_DRIVER -DUSE_STM32469I_DISCO_REVC -DSTM32F469xx -DTS_MULTI_TOUCH_SUPPORTED -c -I../../Inc -I../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../Drivers/BSP/STM32469I-Discovery -I../../Drivers/BSP/Components/Common -I../../Utilities/Log -I../../Utilities/Fonts -I../../Utilities/CPU -I../../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc -I../../Middlewares/Third_Party/FatFs/src -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Utilities

clean-Utilities:
	-$(RM) ./Utilities/lcd_log.cyclo ./Utilities/lcd_log.d ./Utilities/lcd_log.o ./Utilities/lcd_log.su

.PHONY: clean-Utilities

