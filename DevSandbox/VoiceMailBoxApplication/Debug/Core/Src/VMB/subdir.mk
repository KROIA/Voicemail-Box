################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Src/VMB/FAT32File.cpp 

OBJS += \
./Core/Src/VMB/FAT32File.o 

CPP_DEPS += \
./Core/Src/VMB/FAT32File.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/VMB/%.o Core/Src/VMB/%.su Core/Src/VMB/%.cyclo: ../Core/Src/VMB/%.cpp Core/Src/VMB/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F469xx -c -I../Core/Inc -I"E:/Dokumente/Weiterbildung/Studium Elektrotechnik/SA/Voicemail-Box/DevSandbox/VoiceMailBoxApplication/../../Software/LibVoiceMailBox/Inc" -I../FATFS/Target -I../FATFS/App -I../Middlewares/Third_Party/FatFs/src -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../USB_HOST/App -I../USB_HOST/Target -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Core/Inc/VMB -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-VMB

clean-Core-2f-Src-2f-VMB:
	-$(RM) ./Core/Src/VMB/FAT32File.cyclo ./Core/Src/VMB/FAT32File.d ./Core/Src/VMB/FAT32File.o ./Core/Src/VMB/FAT32File.su

.PHONY: clean-Core-2f-Src-2f-VMB

