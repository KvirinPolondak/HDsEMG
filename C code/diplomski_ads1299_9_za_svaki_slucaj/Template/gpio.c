/* gpio.c */

#include <gpio.h>

void gpio_init()
{
		GPIO_InitTypeDef GPIO_InitStruct;

		RCC_AHB1PeriphClockCmd(START_PIN_RCC_GPIOx, ENABLE);
		GPIO_InitStruct.GPIO_Pin = START_PIN_PinNumber;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_Init(START_PIN_GPIOx, &GPIO_InitStruct);

		RCC_AHB1PeriphClockCmd(DRDY_PIN_RCC_GPIOx, ENABLE);
		GPIO_InitStruct.GPIO_Pin = DRDY_PIN_PinNumber;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_Init(DRDY_PIN_GPIOx, &GPIO_InitStruct);
		
		RCC_AHB1PeriphClockCmd(CS_PIN_RCC_GPIOx, ENABLE);
		GPIO_InitStruct.GPIO_Pin = CS_PIN_PinNumber;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_Init(CS_PIN_GPIOx, &GPIO_InitStruct);	
	
}	


