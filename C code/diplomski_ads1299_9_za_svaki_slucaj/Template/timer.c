#include "timer.h"

void TimInit(){
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
	
	RCC_APB1PeriphClockCmd(TIMER_RCC, ENABLE);

  NVIC_InitStructure.NVIC_IRQChannel = TIMER_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  TIM_TimeBaseStruct.TIM_Period = 65535;
  TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStruct.TIM_Prescaler = 0;
  TIM_TimeBaseInit(TIMER_PRIVATE, &TIM_TimeBaseStruct);
}


/*
 *
 */
void DelayMs(uint32_t ms){
	
	TIM_OCInitTypeDef TIM_OCInitStruct;
	uint32_t PrescalerVal;
	
	TIM_SetCounter(TIMER_PRIVATE, 0); // postavi counter u 0

	PrescalerVal = (uint16_t)((SystemCoreClock / 2) / 2000) - 1;
	TIM_PrescalerConfig(TIMER_PRIVATE, PrescalerVal, TIM_PSCReloadMode_Immediate);

	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_Timing;
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_Pulse = ms * 2;
	TIM_OC1Init(TIMER_PRIVATE, &TIM_OCInitStruct);
	TIM_OC1PreloadConfig(TIMER_PRIVATE, TIM_OCPreload_Disable);

	TIM_ITConfig(TIMER_PRIVATE, TIM_IT_CC1, ENABLE);
	TIM_Cmd(TIMER_PRIVATE, ENABLE);

	while(!(TIMER_PRIVATE->SR & TIM_IT_CC1)); // cekaj u petlji dok se ne odbroji

	TIM_Cmd(TIMER_PRIVATE, DISABLE);
}


/*
 * 
 */
void DelayUs(uint32_t us){
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
	uint32_t PrescalerVal;
	TIM_OCInitTypeDef TIM_OCInitStruct;
	
	TIM_SetCounter(TIMER_PRIVATE, 0);
  PrescalerVal = (uint16_t) ((SystemCoreClock / 2) / 2000000) - 1;
  TIM_PrescalerConfig(TIMER_PRIVATE, PrescalerVal, TIM_PSCReloadMode_Immediate);

  TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_Timing;
  TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStruct.TIM_Pulse = us * 2;
  TIM_OC1Init(TIMER_PRIVATE, &TIM_OCInitStruct);

  TIM_ITConfig(TIMER_PRIVATE, TIM_IT_CC1, ENABLE);
  TIM_Cmd(TIMER_PRIVATE, ENABLE);

  while(!(TIMER_PRIVATE->SR & TIM_IT_CC1));

  TIM_Cmd(TIMER_PRIVATE, DISABLE);
}



void TIM3_IRQHandler(void){
  TIM_ClearITPendingBit(TIMER_PRIVATE, TIM_IT_CC1);
}


//void CountingInit(){
//  TIM_OCInitTypeDef TIM_OCInitStruct;
//	uint32_t PrescalerVal;
//	
//	TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
//	
//	TIM_SetCounter(TIMER_PRIVATE, 0);
//  PrescalerVal = (uint16_t) ((SystemCoreClock / 2) / 2000000) - 1; // 41
//  TIM_PrescalerConfig(TIMER_PRIVATE, PrescalerVal, TIM_PSCReloadMode_Immediate);

//  TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_Timing;
//  TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
//  TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
//  TIM_OCInitStruct.TIM_Pulse = 65535; // max = 65536
//  TIM_OC1Init(TIMER_PRIVATE, &TIM_OCInitStruct);

//  TIM_ITConfig(TIMER_PRIVATE, TIM_IT_CC1, ENABLE); 
//}


//void CountingEnable(){
//	TIM_Cmd(TIMER_PRIVATE, ENABLE);
//}
//void CountingDisable(){
//  TIM_Cmd(TIMER_PRIVATE, DISABLE);
//}



