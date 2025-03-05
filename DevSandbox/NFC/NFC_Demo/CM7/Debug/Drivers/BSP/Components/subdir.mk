################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/dominik/Documents/studium/sem08/SA/Voicemail-Box/Demos/NFC/NFC_Demo/Drivers/BSP/Components/ST25R3916/rfal_rfst25r3916.c \
/home/dominik/Documents/studium/sem08/SA/Voicemail-Box/Demos/NFC/NFC_Demo/Drivers/BSP/Components/ST25R3916/st25r3916.c \
/home/dominik/Documents/studium/sem08/SA/Voicemail-Box/Demos/NFC/NFC_Demo/Drivers/BSP/Components/ST25R3916/st25r3916_aat.c \
/home/dominik/Documents/studium/sem08/SA/Voicemail-Box/Demos/NFC/NFC_Demo/Drivers/BSP/Components/ST25R3916/st25r3916_com.c \
/home/dominik/Documents/studium/sem08/SA/Voicemail-Box/Demos/NFC/NFC_Demo/Drivers/BSP/Components/ST25R3916/st25r3916_irq.c \
/home/dominik/Documents/studium/sem08/SA/Voicemail-Box/Demos/NFC/NFC_Demo/Drivers/BSP/Components/ST25R3916/st25r3916_led.c \
/home/dominik/Documents/studium/sem08/SA/Voicemail-Box/Demos/NFC/NFC_Demo/Drivers/BSP/Components/ST25R3916/timer.c 

OBJS += \
./Drivers/BSP/Components/rfal_rfst25r3916.o \
./Drivers/BSP/Components/st25r3916.o \
./Drivers/BSP/Components/st25r3916_aat.o \
./Drivers/BSP/Components/st25r3916_com.o \
./Drivers/BSP/Components/st25r3916_irq.o \
./Drivers/BSP/Components/st25r3916_led.o \
./Drivers/BSP/Components/timer.o 

C_DEPS += \
./Drivers/BSP/Components/rfal_rfst25r3916.d \
./Drivers/BSP/Components/st25r3916.d \
./Drivers/BSP/Components/st25r3916_aat.d \
./Drivers/BSP/Components/st25r3916_com.d \
./Drivers/BSP/Components/st25r3916_irq.d \
./Drivers/BSP/Components/st25r3916_led.d \
./Drivers/BSP/Components/timer.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/Components/rfal_rfst25r3916.o: /home/dominik/Documents/studium/sem08/SA/Voicemail-Box/Demos/NFC/NFC_Demo/Drivers/BSP/Components/ST25R3916/rfal_rfst25r3916.c Drivers/BSP/Components/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DCORE_CM7 -DUSE_HAL_DRIVER -DSTM32H755xx -DUSE_PWR_LDO_SUPPLY -DUSE_PWR_DIRECT_SMPS_SUPPLY -DST25R3916B -c -I../Core/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I../X-CUBE-NFC6/App -I../X-CUBE-NFC6/Target -I../../Drivers/BSP/custom -I../../Drivers/BSP/Components/ST25R3916 -I../../Drivers/BSP/NFC08A1 -I../../Middlewares/ST/ndef/Inc -I../../Middlewares/ST/ndef/Inc/message -I../../Middlewares/ST/ndef/Inc/poller -I../../Middlewares/ST/rfal/Inc -I../../Middlewares/ST/rfal/Src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/BSP/Components/st25r3916.o: /home/dominik/Documents/studium/sem08/SA/Voicemail-Box/Demos/NFC/NFC_Demo/Drivers/BSP/Components/ST25R3916/st25r3916.c Drivers/BSP/Components/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DCORE_CM7 -DUSE_HAL_DRIVER -DSTM32H755xx -DUSE_PWR_LDO_SUPPLY -DUSE_PWR_DIRECT_SMPS_SUPPLY -DST25R3916B -c -I../Core/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I../X-CUBE-NFC6/App -I../X-CUBE-NFC6/Target -I../../Drivers/BSP/custom -I../../Drivers/BSP/Components/ST25R3916 -I../../Drivers/BSP/NFC08A1 -I../../Middlewares/ST/ndef/Inc -I../../Middlewares/ST/ndef/Inc/message -I../../Middlewares/ST/ndef/Inc/poller -I../../Middlewares/ST/rfal/Inc -I../../Middlewares/ST/rfal/Src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/BSP/Components/st25r3916_aat.o: /home/dominik/Documents/studium/sem08/SA/Voicemail-Box/Demos/NFC/NFC_Demo/Drivers/BSP/Components/ST25R3916/st25r3916_aat.c Drivers/BSP/Components/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DCORE_CM7 -DUSE_HAL_DRIVER -DSTM32H755xx -DUSE_PWR_LDO_SUPPLY -DUSE_PWR_DIRECT_SMPS_SUPPLY -DST25R3916B -c -I../Core/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I../X-CUBE-NFC6/App -I../X-CUBE-NFC6/Target -I../../Drivers/BSP/custom -I../../Drivers/BSP/Components/ST25R3916 -I../../Drivers/BSP/NFC08A1 -I../../Middlewares/ST/ndef/Inc -I../../Middlewares/ST/ndef/Inc/message -I../../Middlewares/ST/ndef/Inc/poller -I../../Middlewares/ST/rfal/Inc -I../../Middlewares/ST/rfal/Src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/BSP/Components/st25r3916_com.o: /home/dominik/Documents/studium/sem08/SA/Voicemail-Box/Demos/NFC/NFC_Demo/Drivers/BSP/Components/ST25R3916/st25r3916_com.c Drivers/BSP/Components/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DCORE_CM7 -DUSE_HAL_DRIVER -DSTM32H755xx -DUSE_PWR_LDO_SUPPLY -DUSE_PWR_DIRECT_SMPS_SUPPLY -DST25R3916B -c -I../Core/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I../X-CUBE-NFC6/App -I../X-CUBE-NFC6/Target -I../../Drivers/BSP/custom -I../../Drivers/BSP/Components/ST25R3916 -I../../Drivers/BSP/NFC08A1 -I../../Middlewares/ST/ndef/Inc -I../../Middlewares/ST/ndef/Inc/message -I../../Middlewares/ST/ndef/Inc/poller -I../../Middlewares/ST/rfal/Inc -I../../Middlewares/ST/rfal/Src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/BSP/Components/st25r3916_irq.o: /home/dominik/Documents/studium/sem08/SA/Voicemail-Box/Demos/NFC/NFC_Demo/Drivers/BSP/Components/ST25R3916/st25r3916_irq.c Drivers/BSP/Components/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DCORE_CM7 -DUSE_HAL_DRIVER -DSTM32H755xx -DUSE_PWR_LDO_SUPPLY -DUSE_PWR_DIRECT_SMPS_SUPPLY -DST25R3916B -c -I../Core/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I../X-CUBE-NFC6/App -I../X-CUBE-NFC6/Target -I../../Drivers/BSP/custom -I../../Drivers/BSP/Components/ST25R3916 -I../../Drivers/BSP/NFC08A1 -I../../Middlewares/ST/ndef/Inc -I../../Middlewares/ST/ndef/Inc/message -I../../Middlewares/ST/ndef/Inc/poller -I../../Middlewares/ST/rfal/Inc -I../../Middlewares/ST/rfal/Src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/BSP/Components/st25r3916_led.o: /home/dominik/Documents/studium/sem08/SA/Voicemail-Box/Demos/NFC/NFC_Demo/Drivers/BSP/Components/ST25R3916/st25r3916_led.c Drivers/BSP/Components/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DCORE_CM7 -DUSE_HAL_DRIVER -DSTM32H755xx -DUSE_PWR_LDO_SUPPLY -DUSE_PWR_DIRECT_SMPS_SUPPLY -DST25R3916B -c -I../Core/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I../X-CUBE-NFC6/App -I../X-CUBE-NFC6/Target -I../../Drivers/BSP/custom -I../../Drivers/BSP/Components/ST25R3916 -I../../Drivers/BSP/NFC08A1 -I../../Middlewares/ST/ndef/Inc -I../../Middlewares/ST/ndef/Inc/message -I../../Middlewares/ST/ndef/Inc/poller -I../../Middlewares/ST/rfal/Inc -I../../Middlewares/ST/rfal/Src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/BSP/Components/timer.o: /home/dominik/Documents/studium/sem08/SA/Voicemail-Box/Demos/NFC/NFC_Demo/Drivers/BSP/Components/ST25R3916/timer.c Drivers/BSP/Components/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DCORE_CM7 -DUSE_HAL_DRIVER -DSTM32H755xx -DUSE_PWR_LDO_SUPPLY -DUSE_PWR_DIRECT_SMPS_SUPPLY -DST25R3916B -c -I../Core/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -I../X-CUBE-NFC6/App -I../X-CUBE-NFC6/Target -I../../Drivers/BSP/custom -I../../Drivers/BSP/Components/ST25R3916 -I../../Drivers/BSP/NFC08A1 -I../../Middlewares/ST/ndef/Inc -I../../Middlewares/ST/ndef/Inc/message -I../../Middlewares/ST/ndef/Inc/poller -I../../Middlewares/ST/rfal/Inc -I../../Middlewares/ST/rfal/Src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-Components

clean-Drivers-2f-BSP-2f-Components:
	-$(RM) ./Drivers/BSP/Components/rfal_rfst25r3916.cyclo ./Drivers/BSP/Components/rfal_rfst25r3916.d ./Drivers/BSP/Components/rfal_rfst25r3916.o ./Drivers/BSP/Components/rfal_rfst25r3916.su ./Drivers/BSP/Components/st25r3916.cyclo ./Drivers/BSP/Components/st25r3916.d ./Drivers/BSP/Components/st25r3916.o ./Drivers/BSP/Components/st25r3916.su ./Drivers/BSP/Components/st25r3916_aat.cyclo ./Drivers/BSP/Components/st25r3916_aat.d ./Drivers/BSP/Components/st25r3916_aat.o ./Drivers/BSP/Components/st25r3916_aat.su ./Drivers/BSP/Components/st25r3916_com.cyclo ./Drivers/BSP/Components/st25r3916_com.d ./Drivers/BSP/Components/st25r3916_com.o ./Drivers/BSP/Components/st25r3916_com.su ./Drivers/BSP/Components/st25r3916_irq.cyclo ./Drivers/BSP/Components/st25r3916_irq.d ./Drivers/BSP/Components/st25r3916_irq.o ./Drivers/BSP/Components/st25r3916_irq.su ./Drivers/BSP/Components/st25r3916_led.cyclo ./Drivers/BSP/Components/st25r3916_led.d ./Drivers/BSP/Components/st25r3916_led.o ./Drivers/BSP/Components/st25r3916_led.su ./Drivers/BSP/Components/timer.cyclo ./Drivers/BSP/Components/timer.d ./Drivers/BSP/Components/timer.o ./Drivers/BSP/Components/timer.su

.PHONY: clean-Drivers-2f-BSP-2f-Components

