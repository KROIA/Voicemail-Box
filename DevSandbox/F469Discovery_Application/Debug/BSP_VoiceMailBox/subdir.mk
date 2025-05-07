################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
E:/Dokumente/Weiterbildung/Studium\ Elektrotechnik/SA/Voicemail-Box/Software/BSP_VoiceMailBox/src/BSP_VoiceMailBox.cpp \
E:/Dokumente/Weiterbildung/Studium\ Elektrotechnik/SA/Voicemail-Box/Software/BSP_VoiceMailBox/src/Platform.cpp 

OBJS += \
./BSP_VoiceMailBox/BSP_VoiceMailBox.o \
./BSP_VoiceMailBox/Platform.o 

CPP_DEPS += \
./BSP_VoiceMailBox/BSP_VoiceMailBox.d \
./BSP_VoiceMailBox/Platform.d 


# Each subdirectory must supply rules for building sources it contributes
BSP_VoiceMailBox/BSP_VoiceMailBox.o: E:/Dokumente/Weiterbildung/Studium\ Elektrotechnik/SA/Voicemail-Box/Software/BSP_VoiceMailBox/src/BSP_VoiceMailBox.cpp BSP_VoiceMailBox/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F469xx -c -I../Core/Inc -I../FATFS/Target -I../FATFS/App -I../USB_HOST/App -I../USB_HOST/Target -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"../BSP_VoiceMailBox/inc" -I"../Application/inc" -I"E:/Dokumente/Weiterbildung/Studium Elektrotechnik/SA/Voicemail-Box/DevSandbox/F469Discovery_Application/../../Software/BSP_VoiceMailBox/inc" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
BSP_VoiceMailBox/Platform.o: E:/Dokumente/Weiterbildung/Studium\ Elektrotechnik/SA/Voicemail-Box/Software/BSP_VoiceMailBox/src/Platform.cpp BSP_VoiceMailBox/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F469xx -c -I../Core/Inc -I../FATFS/Target -I../FATFS/App -I../USB_HOST/App -I../USB_HOST/Target -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"../BSP_VoiceMailBox/inc" -I"../Application/inc" -I"E:/Dokumente/Weiterbildung/Studium Elektrotechnik/SA/Voicemail-Box/DevSandbox/F469Discovery_Application/../../Software/BSP_VoiceMailBox/inc" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-BSP_VoiceMailBox

clean-BSP_VoiceMailBox:
	-$(RM) ./BSP_VoiceMailBox/BSP_VoiceMailBox.cyclo ./BSP_VoiceMailBox/BSP_VoiceMailBox.d ./BSP_VoiceMailBox/BSP_VoiceMailBox.o ./BSP_VoiceMailBox/BSP_VoiceMailBox.su ./BSP_VoiceMailBox/Platform.cyclo ./BSP_VoiceMailBox/Platform.d ./BSP_VoiceMailBox/Platform.o ./BSP_VoiceMailBox/Platform.su

.PHONY: clean-BSP_VoiceMailBox

