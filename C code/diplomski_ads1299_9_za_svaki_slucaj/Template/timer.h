#include "stm32f4xx_gpio.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_exti.h"
#include <stm32f4xx_rcc.h>	
/*
 * timer/delay_s
 */
#define TIMER_RCC         RCC_APB1Periph_TIM3
#define TIMER_IRQn        TIM3_IRQn
#define TIMER_PRIVATE     TIM3

void TimInit(void);
void DelayMs(uint32_t ms);
void DelayUs(uint32_t us);





