#ifndef HAL_ABSTRACTION_H
#define HAL_ABSTRACTION_H

#include "main.h"
#include <stdint.h>


namespace VoiceMailBox
{
	//using VMB_HAL_Status = HAL_StatusTypeDef;
	enum class VMB_HAL_Status : uint32_t
	{
		OK = HAL_StatusTypeDef::HAL_OK,
		ERROR = HAL_StatusTypeDef::HAL_ERROR,
		BUSY = HAL_StatusTypeDef::HAL_BUSY,
		TIMEOUT = HAL_StatusTypeDef::HAL_TIMEOUT
	};
	using VMB_ADC_Handle = ADC_HandleTypeDef;
	using VMB_GPIO = GPIO_TypeDef;
	using VMB_GPIO_PinState = GPIO_PinState;
	using VMB_UART_Handle = UART_HandleTypeDef;
	using VMB_I2C_Handle = I2C_HandleTypeDef;
	using VMB_I2S_Handle = I2S_HandleTypeDef;


	/*
		ADC HAL Abstraction
	*/
	static constexpr uint32_t VMB_ADC_RESOLUTION_12B = ADC_RESOLUTION_12B;
	static constexpr uint32_t VMB_ADC_RESOLUTION_10B = ADC_RESOLUTION_10B;
	static constexpr uint32_t VMB_ADC_RESOLUTION_8B = ADC_RESOLUTION_8B;
	static constexpr uint32_t VMB_ADC_RESOLUTION_6B = ADC_RESOLUTION_6B;
	inline VMB_HAL_Status VMB_HAL_ADC_Start(VMB_ADC_Handle* adc)
	{
		return (VMB_HAL_Status)HAL_ADC_Start(adc);
	}
	inline VMB_HAL_Status VMB_HAL_ADC_Stop(VMB_ADC_Handle* adc)
	{
		return (VMB_HAL_Status)HAL_ADC_Stop(adc);
	}
	inline VMB_HAL_Status VMB_HAL_ADC_PollForConversion(VMB_ADC_Handle* adc, uint32_t timeout)
	{
		return (VMB_HAL_Status)HAL_ADC_PollForConversion(adc, timeout);
	}
	inline uint32_t VMB_HAL_ADC_GetValue(VMB_ADC_Handle* adc)
	{
		return HAL_ADC_GetValue(adc);
	}



	/*
		GPIO HAL Abstraction
	*/
	inline void VMB_HAL_GPIO_WritePin(VMB_GPIO* GPIOx, uint16_t GPIO_Pin, VMB_GPIO_PinState PinState)
	{
		HAL_GPIO_WritePin(GPIOx, GPIO_Pin, PinState);
	}
	inline void VMB_HAL_GPIO_TogglePin(VMB_GPIO* GPIOx, uint16_t GPIO_Pin)
	{
		HAL_GPIO_TogglePin(GPIOx, GPIO_Pin);
	}
	inline VMB_GPIO_PinState VMB_HAL_GPIO_ReadPin(VMB_GPIO* GPIOx, uint16_t GPIO_Pin)
	{
		return (VMB_GPIO_PinState)HAL_GPIO_ReadPin(GPIOx, GPIO_Pin);
	}


	/*
		UART HAL Abstraction
	*/
	inline VMB_HAL_Status VMB_HAL_UART_Transmit(VMB_UART_Handle* huart, uint8_t* pData, uint16_t Size, uint32_t Timeout)
	{
		return (VMB_HAL_Status)HAL_UART_Transmit(huart, pData, Size, Timeout);
	}
	inline VMB_HAL_Status VMB_HAL_UART_Receive(VMB_UART_Handle* huart, uint8_t* pData, uint16_t Size, uint32_t Timeout)
	{
		return (VMB_HAL_Status)HAL_UART_Receive(huart, pData, Size, Timeout);
	}
	inline VMB_HAL_Status VMB_HAL_UART_Transmit_IT(VMB_UART_Handle* huart, uint8_t* pData, uint16_t Size)
	{
		return (VMB_HAL_Status)HAL_UART_Transmit_IT(huart, pData, Size);
	}
	inline VMB_HAL_Status VMB_HAL_UART_Receive_IT(VMB_UART_Handle* huart, uint8_t* pData, uint16_t Size)
	{
		return (VMB_HAL_Status)HAL_UART_Receive_IT(huart, pData, Size);
	}
	inline VMB_HAL_Status VMB_HAL_UARTEx_ReceiveToIdle_DMA(VMB_UART_Handle* huart, uint8_t* rxBuffer, uint16_t Size)
	{
		return (VMB_HAL_Status)HAL_UARTEx_ReceiveToIdle_DMA(huart, rxBuffer, Size);
	}
	inline VMB_HAL_Status VMB_HAL_UART_Transmit_DMA(VMB_UART_Handle* huart, uint8_t* pData, uint16_t Size)
	{
		return (VMB_HAL_Status)HAL_UART_Transmit_DMA(huart, pData, Size);
	}


	/*
		I2C HAL Abstraction
	*/
	inline VMB_HAL_Status VMB_HAL_I2C_Mem_Write(VMB_I2C_Handle* hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t* pData, uint16_t Size, uint32_t Timeout)
	{
		return (VMB_HAL_Status)HAL_I2C_Mem_Write(hi2c, DevAddress, MemAddress, MemAddSize, pData, Size, Timeout);
	}
	inline VMB_HAL_Status VMB_HAL_I2C_Mem_Read(VMB_I2C_Handle* hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t* pData, uint16_t Size, uint32_t Timeout)
	{
		return (VMB_HAL_Status)HAL_I2C_Mem_Read(hi2c, DevAddress, MemAddress, MemAddSize, pData, Size, Timeout);
	}


	/*
		I2S HAL Abstraction
	*/
	inline VMB_HAL_Status VMB_HAL_I2SEx_TransmitReceive_DMA(VMB_I2S_Handle* hi2s, uint16_t* pTxData, uint16_t* pRxData, uint16_t Size)
	{
		return (VMB_HAL_Status)HAL_I2SEx_TransmitReceive_DMA(hi2s, pTxData, pRxData, Size);
	}




	/*
		Utilities
	*/

	inline void VMB_HAL_Delay(uint32_t Delay)
	{
		HAL_Delay(Delay);
	}
	inline void VMB_HAL_InitTickCounter()
	{
		// Setup Tick counter
		// Enable TRC (Trace)
		CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
		// Enable the cycle counter
		DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
		// Optional: Reset the counter to 0
		DWT->CYCCNT = 0;
	}
	inline uint32_t VMB_HAL_GetTickCount()
	{
		return DWT->CYCCNT;
	}
	inline uint32_t VMB_HAL_GetTickCountInMs()
	{
		return DWT->CYCCNT / (SystemCoreClock / 1000);
	}
	inline void VMB_HAL_ResetTickCounter()
	{
		DWT->CYCCNT = 0;
	}
}
#endif