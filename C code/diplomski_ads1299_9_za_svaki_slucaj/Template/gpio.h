/* gpio.h */	

#ifndef GPIO_H
#define GPIO_H

#include <stm32f4xx.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>

#define START_PIN_RCC_GPIOx						RCC_AHB1Periph_GPIOA
#define DRDY_PIN_RCC_GPIOx						RCC_AHB1Periph_GPIOA
#define CS_PIN_RCC_GPIOx							RCC_AHB1Periph_GPIOA


#define START_PIN_GPIOx						GPIOA
#define DRDY_PIN_GPIOx						GPIOA
#define CS_PIN_GPIOx							GPIOA



#define START_PIN_PinNumber				GPIO_Pin_1
#define DRDY_PIN_PinNumber				GPIO_Pin_2
#define CS_PIN_PinNumber					GPIO_Pin_3


#define START_PIN_ID 1
#define DRDY_PIN_ID 2
#define CS_PIN 3


void gpio_init(void);

void GPIO_WriteBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, BitAction BitVal);


#endif


