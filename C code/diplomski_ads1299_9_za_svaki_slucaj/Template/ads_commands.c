#include <main.h>
#include "ads_commands.h"
#include "ads1299_2.h"
#include "tm_stm32f4_gpio.h"
#include <stm32f4xx_rcc.h>
#include <defines.h>
#include <attributes.h>


// INICIJALIZACIJA GPIO pinova kao START, CS i DRDY

void gpio_init(){
	
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_AHB1PeriphClockCmd(START_PIN_RCC_GPIOx, ENABLE);
	GPIO_InitStruct.GPIO_Pin = START_PIN_PinNumber;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(START_PIN_GPIOx, &GPIO_InitStruct);
	
		
	RCC_AHB1PeriphClockCmd(CS_PIN_RCC_GPIOx, ENABLE);
	GPIO_InitStruct.GPIO_Pin = CS_PIN_PinNumber;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(CS_PIN_GPIOx, &GPIO_InitStruct);
	
	RCC_AHB1PeriphClockCmd(DRDY_PIN_RCC_GPIOx, ENABLE);
	GPIO_InitStruct.GPIO_Pin = DRDY_PIN_PinNumber;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;   			// ulazni pin
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(DRDY_PIN_GPIOx, &GPIO_InitStruct);
	
		
//	TM_GPIO_Init(GPIOA, pin_start|pin_cs, TM_GPIO_Mode_OUT, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_High);
//	TM_GPIO_Init(GPIOA, pin_drdy, TM_GPIO_Mode_IN, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_High);
}




void adc_send_command(int cmd) 
	{
  
	GPIO_WriteBit(CS_PIN_GPIOx, CS_PIN_PinNumber,Bit_RESET);
   TM_SPI_Send(SPI1, cmd);             	// salji jedan bajt preko SPI-ja
   DelayUs(3);
   GPIO_WriteBit(CS_PIN_GPIOx, CS_PIN_PinNumber,Bit_SET);
	}



	void adc_wreg(int reg1, int val)   // reg1 je npr. CONFIG1
{
  //see pages 40,43 of datasheet - 
	GPIO_WriteBit(CS_PIN_GPIOx, CS_PIN_PinNumber,Bit_RESET);
	TM_SPI_Send(SPI1,WREG|reg1);
	DelayUs(3);
	TM_SPI_Send(SPI1,0);	// number of registers to be read/written – 1
	DelayUs(3);
	TM_SPI_Send(SPI1,val);
	DelayUs(3);
	GPIO_WriteBit(CS_PIN_GPIOx, CS_PIN_PinNumber,Bit_SET);
}


int adc_rreg(int reg1)
	{
  uint8_t out = 0;
  GPIO_WriteBit(CS_PIN_GPIOx, CS_PIN_PinNumber,Bit_RESET);
	TM_SPI_Send(SPI1, RREG | reg1);
  DelayUs(5);
  TM_SPI_Send(SPI1,0);				// number of registers to be read/written – 1
															// u ovom slucaju 1-1=0
  DelayUs(5);
  out = TM_SPI_Send(SPI1,0);  // sada namjerno saljem nulu, samo da bih mogao primiti zeljeno
  //TM_SPI_ReadMulti(SPI1,(uint8_t*)out,0,1); 
	DelayUs(3);
  GPIO_WriteBit(CS_PIN_GPIOx, CS_PIN_PinNumber,Bit_SET);
  return(out);
	}


	
	
	
	



