/* usart.h */
#ifndef USART_H
#define USART_H

#include <stm32f4xx.h> // common stuff
#include <stm32f4xx_rcc.h> // reset anc clocking
#include <stm32f4xx_gpio.h> // gpio control
#include <stm32f4xx_usart.h> // USART

#define BUFSIZE 32  				// defining the FIFO size buffer for received characters
#define BAUDRATE 115200			


void USART3_Init(void); 				// init USART1 peripheral
void USART3_SendChar(char c); 	// blocking send character
																// a high-level function that sends a single character through 
																// the USART1 interface
																// the function will block if USART1 is not ready to transmit and
																// will wait until it is ready

int USART3_Dequeue(char* c); 		// pop character from receive FIFO
																// the function fetches a single character from a queue 
																//	of received characters;
void USART3_SendString(char* s);


#endif


