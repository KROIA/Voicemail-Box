#include "peripherals/uart.hpp"
#include "peripherals/i2s.hpp"
/**
 * @brief
 *  This file contains the interrupt callback handlers used for the VoiceMailBox platform.
 *
 * @details
 *  When the HAL changes, you may need to replace the HAL given weak functions to call
 *	the static methods of the corresponding classes.
 */




//--------------------------------------------------------------------------
//	U A R T
//--------------------------------------------------------------------------
// Called when one byte is received
void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart)
{
	VoiceMailBox::UART::onITReceivedData(huart);
}
// Called when the transmission of one byte is complete
void HAL_UART_TxCpltCallback(UART_HandleTypeDef* huart)
{
	VoiceMailBox::UART::onITByteSent(huart);
}



//--------------------------------------------------------------------------
//	I 2 S
//--------------------------------------------------------------------------
// Called when the I2S RX buffer is half full
void HAL_I2SEx_TxRxHalfCpltCallback(I2S_HandleTypeDef* hi2s)
{
	VoiceMailBox::I2S::onI2S_TXRX_HalfCpltCallback(hi2s); // Call the static method to handle the callback
}
// Called when the I2S RX buffer is full
void HAL_I2SEx_TxRxCpltCallback(I2S_HandleTypeDef* hi2s)
{
	VoiceMailBox::I2S::onI2S_TXRX_CpltCallback(hi2s); // Call the static method to handle the callback
}




