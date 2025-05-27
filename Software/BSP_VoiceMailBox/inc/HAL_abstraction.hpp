#ifndef HAL_ABSTRACTION_H
#define HAL_ABSTRACTION_H
/**
 * @brief This file encapsulates all HAL functions and types used in this project.
 * @details The goal of this is, to make the code more portable.
 *	        For example, if we want to use a different HAL library, we only need to change this file.
 * @author Alex Krieg
 */


/**
 * @note The main.h must be included only once here.
 *       This is because in a STM-Project, the STM-HAL library gets included by the codegenerator in the main.h file.
 */
#include "main.h"
#include "settings.h"

namespace VoiceMailBox
{
	enum class VMB_HAL_Status : uint32_t
	{
		OK = HAL_StatusTypeDef::HAL_OK,
		ERROR = HAL_StatusTypeDef::HAL_ERROR,
		BUSY = HAL_StatusTypeDef::HAL_BUSY,
		TIMEOUT = HAL_StatusTypeDef::HAL_TIMEOUT
	};

	// Renaming HAL types to VMB types
	using VMB_ADC_Handle = ADC_HandleTypeDef;
	using VMB_GPIO = GPIO_TypeDef;
	using VMB_GPIO_PinState = GPIO_PinState;
	using VMB_UART_Handle = UART_HandleTypeDef;
	using VMB_I2C_Handle = I2C_HandleTypeDef;
	using VMB_I2S_Handle = I2S_HandleTypeDef;


	/*
		ADC HAL Abstraction
	*/
#if defined(VMB_MICROCONTROLLER_BOARD__STM32F469I_DISCOVERY)
	static constexpr uint32_t VMB_ADC_RESOLUTION_12B = ADC_RESOLUTION_12B;
	static constexpr uint32_t VMB_ADC_RESOLUTION_10B = ADC_RESOLUTION_10B;
	static constexpr uint32_t VMB_ADC_RESOLUTION_8B = ADC_RESOLUTION_8B;
	static constexpr uint32_t VMB_ADC_RESOLUTION_6B = ADC_RESOLUTION_6B;
#elif defined(VMB_MICROCONTROLLER_BOARD__STM32NUCLEO_H755ZI_Q)
	static constexpr uint32_t VMB_ADC_RESOLUTION_16B = ADC_RESOLUTION_16B;
	static constexpr uint32_t VMB_ADC_RESOLUTION_14B = ADC_RESOLUTION_14B;
	static constexpr uint32_t VMB_ADC_RESOLUTION_12B = ADC_RESOLUTION_12B;
	static constexpr uint32_t VMB_ADC_RESOLUTION_10B = ADC_RESOLUTION_10B;
	static constexpr uint32_t VMB_ADC_RESOLUTION_8B = ADC_RESOLUTION_8B;
#endif

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
	inline uint32_t VMB_HAL_ADC_GetMaxValue(VMB_ADC_Handle* adc)
	{
#if defined(VMB_MICROCONTROLLER_BOARD__STM32F469I_DISCOVERY)
		switch (adc->Init.Resolution) {
			case VMB_ADC_RESOLUTION_12B:
				return 4095;
			case VMB_ADC_RESOLUTION_10B:
				return 1023;
			case VMB_ADC_RESOLUTION_8B:
				return 255;
			case VMB_ADC_RESOLUTION_6B:
				return 63;
		}
#elif defined(VMB_MICROCONTROLLER_BOARD__STM32NUCLEO_H755ZI_Q)
		switch (adc->Init.Resolution) {
		case VMB_ADC_RESOLUTION_16B:
			return 35535;
		case VMB_ADC_RESOLUTION_14B:
			return 16383;
		case VMB_ADC_RESOLUTION_12B:
			return 4095;
		case VMB_ADC_RESOLUTION_10B:
			return 1023;
		case VMB_ADC_RESOLUTION_8B:
			return 255;
		}
#endif
		return 0;
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
	inline VMB_HAL_Status VMB_HAL_I2S_DMAStop(VMB_I2S_Handle* hi2s)
	{
		return (VMB_HAL_Status)HAL_I2S_DMAStop(hi2s);
	}




	/*
		Utilities
	*/

	inline void VMB_HAL_Delay(uint32_t Delay)
	{
		HAL_Delay(Delay);
	}

	inline uint64_t VMB_HAL_UpdateTick(uint64_t setTickMask = -1)
	{
		static uint32_t DWT_LastCYCCNT = 0;
		static uint64_t DWT_Tick = 0;
	    uint32_t curr = DWT->CYCCNT;
	    uint32_t last = DWT_LastCYCCNT;

	    // Handle wraparound
	    uint32_t delta = (curr - last);

	    DWT_Tick += ((uint64_t)delta) ;
	    DWT_Tick &= setTickMask;

	    DWT_LastCYCCNT = curr;
	    return DWT_Tick / ((uint64_t)SystemCoreClock / 1000000L);
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
		VMB_HAL_UpdateTick(0);
	}
	inline uint32_t VMB_HAL_GetTickCount()
	{
		return DWT->CYCCNT;
	}
	inline uint64_t VMB_HAL_GetTickCountInUs()
	{
		return VMB_HAL_UpdateTick();
	}
	inline uint64_t VMB_HAL_GetTickCountInMs()
	{
		return VMB_HAL_UpdateTick() / 1000;
	}
	inline void VMB_HAL_ResetTickCounter()
	{
		DWT->CYCCNT = 0;
		VMB_HAL_UpdateTick(0);
	}

}
#endif
