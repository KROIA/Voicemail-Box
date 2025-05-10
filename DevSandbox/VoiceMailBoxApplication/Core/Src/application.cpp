#include "application.h"
#include "LibVoiceMailBox.hpp"
#include "tests.hpp"

bool execTests()
{
	bool success = true;
	success &= VMB::testFat32File();
	success &= VMB::testWIFI();
	return success;
}

void setup()
{
	if (!execTests())
	{
		printf("Tests failed\n\r");
		while (1) 
		{
			HAL_Delay(1000);
		}
	}
	else
	{
		printf("Tests passed\n\r");
	}
}
void loop()
{

}




void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
	VMB::WiFiServerClient::on_HAL_UARTEx_RxEventCallback(huart, Size);
}
