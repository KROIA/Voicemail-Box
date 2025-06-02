################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/home/dominik/Documents/studium/sem08/SA/Voicemail-Box/Software/BSP_VoiceMailBox/src/peripherals/ATCommandClient.cpp \
/home/dominik/Documents/studium/sem08/SA/Voicemail-Box/Software/BSP_VoiceMailBox/src/peripherals/Codec_TLV320AIC3104.cpp \
/home/dominik/Documents/studium/sem08/SA/Voicemail-Box/Software/BSP_VoiceMailBox/src/peripherals/analogPin.cpp \
/home/dominik/Documents/studium/sem08/SA/Voicemail-Box/Software/BSP_VoiceMailBox/src/peripherals/digitalPin.cpp \
/home/dominik/Documents/studium/sem08/SA/Voicemail-Box/Software/BSP_VoiceMailBox/src/peripherals/i2c.cpp \
/home/dominik/Documents/studium/sem08/SA/Voicemail-Box/Software/BSP_VoiceMailBox/src/peripherals/i2s.cpp \
/home/dominik/Documents/studium/sem08/SA/Voicemail-Box/Software/BSP_VoiceMailBox/src/peripherals/uart.cpp 

C_SRCS += \
/home/dominik/Documents/studium/sem08/SA/Voicemail-Box/Software/BSP_VoiceMailBox/src/peripherals/sdmmc.c 

C_DEPS += \
./BSP_VoiceMailBox/peripherals/sdmmc.d 

OBJS += \
./BSP_VoiceMailBox/peripherals/ATCommandClient.o \
./BSP_VoiceMailBox/peripherals/Codec_TLV320AIC3104.o \
./BSP_VoiceMailBox/peripherals/analogPin.o \
./BSP_VoiceMailBox/peripherals/digitalPin.o \
./BSP_VoiceMailBox/peripherals/i2c.o \
./BSP_VoiceMailBox/peripherals/i2s.o \
./BSP_VoiceMailBox/peripherals/sdmmc.o \
./BSP_VoiceMailBox/peripherals/uart.o 

CPP_DEPS += \
./BSP_VoiceMailBox/peripherals/ATCommandClient.d \
./BSP_VoiceMailBox/peripherals/Codec_TLV320AIC3104.d \
./BSP_VoiceMailBox/peripherals/analogPin.d \
./BSP_VoiceMailBox/peripherals/digitalPin.d \
./BSP_VoiceMailBox/peripherals/i2c.d \
./BSP_VoiceMailBox/peripherals/i2s.d \
./BSP_VoiceMailBox/peripherals/uart.d 


# Each subdirectory must supply rules for building sources it contributes
BSP_VoiceMailBox/peripherals/ATCommandClient.o: /home/dominik/Documents/studium/sem08/SA/Voicemail-Box/Software/BSP_VoiceMailBox/src/peripherals/ATCommandClient.cpp BSP_VoiceMailBox/peripherals/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F469xx -c -I../Core/Inc -I../FATFS/Target -I../FATFS/App -I../USB_HOST/App -I../USB_HOST/Target -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"../Application/inc" -I"/home/dominik/Documents/studium/sem08/SA/Voicemail-Box/Software/DevSandbox/F469Discovery_Application/../../BSP_VoiceMailBox/inc" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb -o "$@"
BSP_VoiceMailBox/peripherals/Codec_TLV320AIC3104.o: /home/dominik/Documents/studium/sem08/SA/Voicemail-Box/Software/BSP_VoiceMailBox/src/peripherals/Codec_TLV320AIC3104.cpp BSP_VoiceMailBox/peripherals/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F469xx -c -I../Core/Inc -I../FATFS/Target -I../FATFS/App -I../USB_HOST/App -I../USB_HOST/Target -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"../Application/inc" -I"/home/dominik/Documents/studium/sem08/SA/Voicemail-Box/Software/DevSandbox/F469Discovery_Application/../../BSP_VoiceMailBox/inc" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb -o "$@"
BSP_VoiceMailBox/peripherals/analogPin.o: /home/dominik/Documents/studium/sem08/SA/Voicemail-Box/Software/BSP_VoiceMailBox/src/peripherals/analogPin.cpp BSP_VoiceMailBox/peripherals/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F469xx -c -I../Core/Inc -I../FATFS/Target -I../FATFS/App -I../USB_HOST/App -I../USB_HOST/Target -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"../Application/inc" -I"/home/dominik/Documents/studium/sem08/SA/Voicemail-Box/Software/DevSandbox/F469Discovery_Application/../../BSP_VoiceMailBox/inc" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb -o "$@"
BSP_VoiceMailBox/peripherals/digitalPin.o: /home/dominik/Documents/studium/sem08/SA/Voicemail-Box/Software/BSP_VoiceMailBox/src/peripherals/digitalPin.cpp BSP_VoiceMailBox/peripherals/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F469xx -c -I../Core/Inc -I../FATFS/Target -I../FATFS/App -I../USB_HOST/App -I../USB_HOST/Target -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"../Application/inc" -I"/home/dominik/Documents/studium/sem08/SA/Voicemail-Box/Software/DevSandbox/F469Discovery_Application/../../BSP_VoiceMailBox/inc" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb -o "$@"
BSP_VoiceMailBox/peripherals/i2c.o: /home/dominik/Documents/studium/sem08/SA/Voicemail-Box/Software/BSP_VoiceMailBox/src/peripherals/i2c.cpp BSP_VoiceMailBox/peripherals/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F469xx -c -I../Core/Inc -I../FATFS/Target -I../FATFS/App -I../USB_HOST/App -I../USB_HOST/Target -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"../Application/inc" -I"/home/dominik/Documents/studium/sem08/SA/Voicemail-Box/Software/DevSandbox/F469Discovery_Application/../../BSP_VoiceMailBox/inc" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb -o "$@"
BSP_VoiceMailBox/peripherals/i2s.o: /home/dominik/Documents/studium/sem08/SA/Voicemail-Box/Software/BSP_VoiceMailBox/src/peripherals/i2s.cpp BSP_VoiceMailBox/peripherals/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F469xx -c -I../Core/Inc -I../FATFS/Target -I../FATFS/App -I../USB_HOST/App -I../USB_HOST/Target -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"../Application/inc" -I"/home/dominik/Documents/studium/sem08/SA/Voicemail-Box/Software/DevSandbox/F469Discovery_Application/../../BSP_VoiceMailBox/inc" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb -o "$@"
BSP_VoiceMailBox/peripherals/sdmmc.o: /home/dominik/Documents/studium/sem08/SA/Voicemail-Box/Software/BSP_VoiceMailBox/src/peripherals/sdmmc.c BSP_VoiceMailBox/peripherals/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F469xx -c -I../Core/Inc -I../FATFS/Target -I../FATFS/App -I../USB_HOST/App -I../USB_HOST/Target -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"../Application/inc" -I"/home/dominik/Documents/studium/sem08/SA/Voicemail-Box/Software/DevSandbox/F469Discovery_Application/../../BSP_VoiceMailBox/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb -o "$@"
BSP_VoiceMailBox/peripherals/uart.o: /home/dominik/Documents/studium/sem08/SA/Voicemail-Box/Software/BSP_VoiceMailBox/src/peripherals/uart.cpp BSP_VoiceMailBox/peripherals/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F469xx -c -I../Core/Inc -I../FATFS/Target -I../FATFS/App -I../USB_HOST/App -I../USB_HOST/Target -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"../Application/inc" -I"/home/dominik/Documents/studium/sem08/SA/Voicemail-Box/Software/DevSandbox/F469Discovery_Application/../../BSP_VoiceMailBox/inc" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -mthumb -o "$@"

clean: clean-BSP_VoiceMailBox-2f-peripherals

clean-BSP_VoiceMailBox-2f-peripherals:
	-$(RM) ./BSP_VoiceMailBox/peripherals/ATCommandClient.cyclo ./BSP_VoiceMailBox/peripherals/ATCommandClient.d ./BSP_VoiceMailBox/peripherals/ATCommandClient.o ./BSP_VoiceMailBox/peripherals/ATCommandClient.su ./BSP_VoiceMailBox/peripherals/Codec_TLV320AIC3104.cyclo ./BSP_VoiceMailBox/peripherals/Codec_TLV320AIC3104.d ./BSP_VoiceMailBox/peripherals/Codec_TLV320AIC3104.o ./BSP_VoiceMailBox/peripherals/Codec_TLV320AIC3104.su ./BSP_VoiceMailBox/peripherals/analogPin.cyclo ./BSP_VoiceMailBox/peripherals/analogPin.d ./BSP_VoiceMailBox/peripherals/analogPin.o ./BSP_VoiceMailBox/peripherals/analogPin.su ./BSP_VoiceMailBox/peripherals/digitalPin.cyclo ./BSP_VoiceMailBox/peripherals/digitalPin.d ./BSP_VoiceMailBox/peripherals/digitalPin.o ./BSP_VoiceMailBox/peripherals/digitalPin.su ./BSP_VoiceMailBox/peripherals/i2c.cyclo ./BSP_VoiceMailBox/peripherals/i2c.d ./BSP_VoiceMailBox/peripherals/i2c.o ./BSP_VoiceMailBox/peripherals/i2c.su ./BSP_VoiceMailBox/peripherals/i2s.cyclo ./BSP_VoiceMailBox/peripherals/i2s.d ./BSP_VoiceMailBox/peripherals/i2s.o ./BSP_VoiceMailBox/peripherals/i2s.su ./BSP_VoiceMailBox/peripherals/sdmmc.cyclo ./BSP_VoiceMailBox/peripherals/sdmmc.d ./BSP_VoiceMailBox/peripherals/sdmmc.o ./BSP_VoiceMailBox/peripherals/sdmmc.su ./BSP_VoiceMailBox/peripherals/uart.cyclo ./BSP_VoiceMailBox/peripherals/uart.d ./BSP_VoiceMailBox/peripherals/uart.o ./BSP_VoiceMailBox/peripherals/uart.su

.PHONY: clean-BSP_VoiceMailBox-2f-peripherals

