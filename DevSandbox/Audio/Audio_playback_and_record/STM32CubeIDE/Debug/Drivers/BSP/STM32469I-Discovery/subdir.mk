################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
E:/Dokumente/Weiterbildung/Studium\ Elektrotechnik/SA/Voicemail-Box/DevSandbox/Audio/Audio_playback_and_record/Drivers/BSP/STM32469I-Discovery/stm32469i_discovery.c \
E:/Dokumente/Weiterbildung/Studium\ Elektrotechnik/SA/Voicemail-Box/DevSandbox/Audio/Audio_playback_and_record/Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_audio.c \
E:/Dokumente/Weiterbildung/Studium\ Elektrotechnik/SA/Voicemail-Box/DevSandbox/Audio/Audio_playback_and_record/Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_lcd.c \
E:/Dokumente/Weiterbildung/Studium\ Elektrotechnik/SA/Voicemail-Box/DevSandbox/Audio/Audio_playback_and_record/Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_sdram.c \
E:/Dokumente/Weiterbildung/Studium\ Elektrotechnik/SA/Voicemail-Box/DevSandbox/Audio/Audio_playback_and_record/Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_ts.c 

OBJS += \
./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery.o \
./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_audio.o \
./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_lcd.o \
./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_sdram.o \
./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_ts.o 

C_DEPS += \
./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery.d \
./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_audio.d \
./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_lcd.d \
./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_sdram.d \
./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_ts.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/STM32469I-Discovery/stm32469i_discovery.o: E:/Dokumente/Weiterbildung/Studium\ Elektrotechnik/SA/Voicemail-Box/DevSandbox/Audio/Audio_playback_and_record/Drivers/BSP/STM32469I-Discovery/stm32469i_discovery.c Drivers/BSP/STM32469I-Discovery/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_USB_FS -DUSE_STM32469I_DISCOVERY -DUSE_HAL_DRIVER -DUSE_STM32469I_DISCO_REVC -DSTM32F469xx -DTS_MULTI_TOUCH_SUPPORTED -c -I../../Inc -I../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../Drivers/BSP/STM32469I-Discovery -I../../Drivers/BSP/Components/Common -I../../Utilities/Log -I../../Utilities/Fonts -I../../Utilities/CPU -I../../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc -I../../Middlewares/Third_Party/FatFs/src -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Drivers/BSP/STM32469I-Discovery/stm32469i_discovery.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_audio.o: E:/Dokumente/Weiterbildung/Studium\ Elektrotechnik/SA/Voicemail-Box/DevSandbox/Audio/Audio_playback_and_record/Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_audio.c Drivers/BSP/STM32469I-Discovery/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_USB_FS -DUSE_STM32469I_DISCOVERY -DUSE_HAL_DRIVER -DUSE_STM32469I_DISCO_REVC -DSTM32F469xx -DTS_MULTI_TOUCH_SUPPORTED -c -I../../Inc -I../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../Drivers/BSP/STM32469I-Discovery -I../../Drivers/BSP/Components/Common -I../../Utilities/Log -I../../Utilities/Fonts -I../../Utilities/CPU -I../../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc -I../../Middlewares/Third_Party/FatFs/src -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_audio.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_lcd.o: E:/Dokumente/Weiterbildung/Studium\ Elektrotechnik/SA/Voicemail-Box/DevSandbox/Audio/Audio_playback_and_record/Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_lcd.c Drivers/BSP/STM32469I-Discovery/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_USB_FS -DUSE_STM32469I_DISCOVERY -DUSE_HAL_DRIVER -DUSE_STM32469I_DISCO_REVC -DSTM32F469xx -DTS_MULTI_TOUCH_SUPPORTED -c -I../../Inc -I../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../Drivers/BSP/STM32469I-Discovery -I../../Drivers/BSP/Components/Common -I../../Utilities/Log -I../../Utilities/Fonts -I../../Utilities/CPU -I../../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc -I../../Middlewares/Third_Party/FatFs/src -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_lcd.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_sdram.o: E:/Dokumente/Weiterbildung/Studium\ Elektrotechnik/SA/Voicemail-Box/DevSandbox/Audio/Audio_playback_and_record/Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_sdram.c Drivers/BSP/STM32469I-Discovery/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_USB_FS -DUSE_STM32469I_DISCOVERY -DUSE_HAL_DRIVER -DUSE_STM32469I_DISCO_REVC -DSTM32F469xx -DTS_MULTI_TOUCH_SUPPORTED -c -I../../Inc -I../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../Drivers/BSP/STM32469I-Discovery -I../../Drivers/BSP/Components/Common -I../../Utilities/Log -I../../Utilities/Fonts -I../../Utilities/CPU -I../../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc -I../../Middlewares/Third_Party/FatFs/src -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_sdram.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_ts.o: E:/Dokumente/Weiterbildung/Studium\ Elektrotechnik/SA/Voicemail-Box/DevSandbox/Audio/Audio_playback_and_record/Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_ts.c Drivers/BSP/STM32469I-Discovery/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_USB_FS -DUSE_STM32469I_DISCOVERY -DUSE_HAL_DRIVER -DUSE_STM32469I_DISCO_REVC -DSTM32F469xx -DTS_MULTI_TOUCH_SUPPORTED -c -I../../Inc -I../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../Drivers/BSP/STM32469I-Discovery -I../../Drivers/BSP/Components/Common -I../../Utilities/Log -I../../Utilities/Fonts -I../../Utilities/CPU -I../../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc -I../../Middlewares/Third_Party/FatFs/src -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_ts.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-STM32469I-2d-Discovery

clean-Drivers-2f-BSP-2f-STM32469I-2d-Discovery:
	-$(RM) ./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery.cyclo ./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery.d ./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery.o ./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery.su ./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_audio.cyclo ./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_audio.d ./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_audio.o ./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_audio.su ./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_lcd.cyclo ./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_lcd.d ./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_lcd.o ./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_lcd.su ./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_sdram.cyclo ./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_sdram.d ./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_sdram.o ./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_sdram.su ./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_ts.cyclo ./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_ts.d ./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_ts.o ./Drivers/BSP/STM32469I-Discovery/stm32469i_discovery_ts.su

.PHONY: clean-Drivers-2f-BSP-2f-STM32469I-2d-Discovery

