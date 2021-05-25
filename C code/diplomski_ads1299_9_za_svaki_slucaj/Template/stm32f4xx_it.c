/**
  ******************************************************************************
  * @file    IO_Toggle/stm32f4xx_it.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    19-September-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"


/** @addtogroup STM32F4_Discovery_Peripheral_Examples
  * @{
  */

/** @addtogroup IO_Toggle
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

extern volatile int measurement_complete;
extern volatile int sensor_status;
/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f4xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 

/**
  * @}
  */ 
/**
  * @brief  This function handles External line 0 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI0_IRQHandler(void){
	if(EXTI_GetITStatus(EXTI_Line0) != RESET && sensor_status == Bit_RESET){	
//		On(LED_PORT, LED_DESNA_STRAGA);
		sensor_status = Bit_SET;
  }
	else if(EXTI_GetITStatus(EXTI_Line0) != RESET && sensor_status == Bit_SET){
//		Off(LED_PORT, LED_DESNA_STRAGA);
		measurement_complete = Bit_SET;
	}
	EXTI_ClearITPendingBit(EXTI_Line0);
}
void EXTI1_IRQHandler(void){
	if(EXTI_GetITStatus(EXTI_Line1) != RESET){
		//OneToggle(LED_PORT, LED_LIJEVA_SPRIJEDA, 1000);
  }
	EXTI_ClearITPendingBit(EXTI_Line1);
	sensor_status = !sensor_status;
}
void EXTI2_IRQHandler(void){
	if(EXTI_GetITStatus(EXTI_Line2) != RESET){
		//OneToggle(LED_PORT, LED_LIJEVA_STRAGA, 1000);
  }
	EXTI_ClearITPendingBit(EXTI_Line2);
	sensor_status = !sensor_status;
}
void EXTI3_IRQHandler(void){
	if(EXTI_GetITStatus(EXTI_Line3) != RESET){
		//OneToggle(LED_PORT, LED_DESNA_SPRIJEDA, 1000);
  }
	EXTI_ClearITPendingBit(EXTI_Line3);
	sensor_status = !sensor_status;
}
void EXTI4_IRQHandler(void){
	if(EXTI_GetITStatus(EXTI_Line4) != RESET){
		//OneToggle(LED_PORT, LED_DESNA_SPRIJEDA, 1000);
  }
	EXTI_ClearITPendingBit(EXTI_Line4);
	sensor_status = !sensor_status;
}
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
