################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/dominik/Documents/studium/sem08/SA/Voicemail-Box/DevSandbox/NFC/NFC_Demo/Drivers/BSP/NFC08A1/nfc08a1.c 

OBJS += \
./Drivers/BSP/NFC/nfc08a1.o 

C_DEPS += \
./Drivers/BSP/NFC/nfc08a1.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/NFC/nfc08a1.o: /home/dominik/Documents/studium/sem08/SA/Voicemail-Box/DevSandbox/NFC/NFC_Demo/Drivers/BSP/NFC08A1/nfc08a1.c Drivers/BSP/NFC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DCORE_CM7 -DUSE_HAL_DRIVER -DSTM32H755xx -DUSE_PWR_LDO_SUPPLY -DUSE_PWR_DIRECT_SMPS_SUPPLY -DST25R3916B -c -I../X-CUBE-NFC6/App -I../X-CUBE-NFC6/Target -I../Core/Inc -I../../Drivers/BSP/custom -I../../Drivers/BSP/Components/ST25R3916 -I../../Drivers/BSP/NFC08A1 -I../../Middlewares/ST/ndef/Inc -I../../Middlewares/ST/ndef/Inc/message -I../../Middlewares/ST/ndef/Inc/poller -I../../Middlewares/ST/rfal/Inc -I../../Middlewares/ST/rfal/Src -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-NFC

clean-Drivers-2f-BSP-2f-NFC:
	-$(RM) ./Drivers/BSP/NFC/nfc08a1.cyclo ./Drivers/BSP/NFC/nfc08a1.d ./Drivers/BSP/NFC/nfc08a1.o ./Drivers/BSP/NFC/nfc08a1.su

.PHONY: clean-Drivers-2f-BSP-2f-NFC

