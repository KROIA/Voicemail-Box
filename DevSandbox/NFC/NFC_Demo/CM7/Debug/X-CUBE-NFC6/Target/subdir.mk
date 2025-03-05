################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../X-CUBE-NFC6/Target/analogConfigTbl_NFC08A1.c \
../X-CUBE-NFC6/Target/demo_ce.c \
../X-CUBE-NFC6/Target/logger.c \
../X-CUBE-NFC6/Target/ndef_demo.c \
../X-CUBE-NFC6/Target/ndef_dump.c \
../X-CUBE-NFC6/Target/nfc_conf.c 

OBJS += \
./X-CUBE-NFC6/Target/analogConfigTbl_NFC08A1.o \
./X-CUBE-NFC6/Target/demo_ce.o \
./X-CUBE-NFC6/Target/logger.o \
./X-CUBE-NFC6/Target/ndef_demo.o \
./X-CUBE-NFC6/Target/ndef_dump.o \
./X-CUBE-NFC6/Target/nfc_conf.o 

C_DEPS += \
./X-CUBE-NFC6/Target/analogConfigTbl_NFC08A1.d \
./X-CUBE-NFC6/Target/demo_ce.d \
./X-CUBE-NFC6/Target/logger.d \
./X-CUBE-NFC6/Target/ndef_demo.d \
./X-CUBE-NFC6/Target/ndef_dump.d \
./X-CUBE-NFC6/Target/nfc_conf.d 


# Each subdirectory must supply rules for building sources it contributes
X-CUBE-NFC6/Target/%.o X-CUBE-NFC6/Target/%.su X-CUBE-NFC6/Target/%.cyclo: ../X-CUBE-NFC6/Target/%.c X-CUBE-NFC6/Target/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DCORE_CM7 -DUSE_HAL_DRIVER -DSTM32H755xx -DUSE_PWR_LDO_SUPPLY -DUSE_PWR_DIRECT_SMPS_SUPPLY -DST25R3916B -c -I../X-CUBE-NFC6/App -I../X-CUBE-NFC6/Target -I../Core/Inc -I../../Drivers/BSP/custom -I../../Drivers/BSP/Components/ST25R3916 -I../../Drivers/BSP/NFC08A1 -I../../Middlewares/ST/ndef/Inc -I../../Middlewares/ST/ndef/Inc/message -I../../Middlewares/ST/ndef/Inc/poller -I../../Middlewares/ST/rfal/Inc -I../../Middlewares/ST/rfal/Src -I../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-X-2d-CUBE-2d-NFC6-2f-Target

clean-X-2d-CUBE-2d-NFC6-2f-Target:
	-$(RM) ./X-CUBE-NFC6/Target/analogConfigTbl_NFC08A1.cyclo ./X-CUBE-NFC6/Target/analogConfigTbl_NFC08A1.d ./X-CUBE-NFC6/Target/analogConfigTbl_NFC08A1.o ./X-CUBE-NFC6/Target/analogConfigTbl_NFC08A1.su ./X-CUBE-NFC6/Target/demo_ce.cyclo ./X-CUBE-NFC6/Target/demo_ce.d ./X-CUBE-NFC6/Target/demo_ce.o ./X-CUBE-NFC6/Target/demo_ce.su ./X-CUBE-NFC6/Target/logger.cyclo ./X-CUBE-NFC6/Target/logger.d ./X-CUBE-NFC6/Target/logger.o ./X-CUBE-NFC6/Target/logger.su ./X-CUBE-NFC6/Target/ndef_demo.cyclo ./X-CUBE-NFC6/Target/ndef_demo.d ./X-CUBE-NFC6/Target/ndef_demo.o ./X-CUBE-NFC6/Target/ndef_demo.su ./X-CUBE-NFC6/Target/ndef_dump.cyclo ./X-CUBE-NFC6/Target/ndef_dump.d ./X-CUBE-NFC6/Target/ndef_dump.o ./X-CUBE-NFC6/Target/ndef_dump.su ./X-CUBE-NFC6/Target/nfc_conf.cyclo ./X-CUBE-NFC6/Target/nfc_conf.d ./X-CUBE-NFC6/Target/nfc_conf.o ./X-CUBE-NFC6/Target/nfc_conf.su

.PHONY: clean-X-2d-CUBE-2d-NFC6-2f-Target

