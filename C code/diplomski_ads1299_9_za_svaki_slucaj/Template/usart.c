/* usart.c */
#include <usart.h>

// RX FIFO buffer
char RX_BUFFER[BUFSIZE];						// polje znakova sadrzi sve neprocesirane dolazne znakove	(FIFO queue)
																		// queue is filled with characters by USART2 ISR as they arrive



int RX_BUFFER_HEAD, RX_BUFFER_TAIL; // variables pointing to head (RX_BUFFER_HEAD) and tail (RX_BUFFER_TAIL)
																		// to implement queue functionality with static array

// TX state flag
uint8_t TxReady;




// init USART2
void USART2_Init(void)
{
		GPIO_InitTypeDef 		GPIO_InitStruct;
		USART_InitTypeDef 	USART_InitStruct;
		NVIC_InitTypeDef 		NVIC_InitStructure;
		
	// enable peripheral clocks (note: different bus interfaces for each peripheral!)
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	
	// map port B pins for alternate function
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11; // Pins 10 (TX) and 11 (RX) will be used for USART2
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF; // GPIO pins defined as alternate function
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz; // I/O pins speed (signal rise time)
		GPIO_InitStruct.GPIO_OType = GPIO_OType_PP; // push-pull output
		GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP; // activates pullup resistors
		GPIO_Init(GPIOD, &GPIO_InitStruct); // set chosen pins

	// set alternate function to USART2 (from multiple possible alternate function choices)
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource10, GPIO_AF_USART2); // pins will automatically be assigned
	// to TX/RX - refer to datasheet to see AF mappings
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource11, GPIO_AF_USART2);
	
	// use USART_InitStruct to config USART2 peripheral
	USART_InitStruct.USART_BaudRate = BAUDRATE; 									// set baudrate from define
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;			// 8 data bits
	USART_InitStruct.USART_StopBits = USART_StopBits_1; 					// 1 stop bit
	USART_InitStruct.USART_Parity = USART_Parity_No; 							// no parity check
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // no HW control flow
	USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; 	// enable both character transmit and receive
	USART_Init(USART2, &USART_InitStruct); 												// set USART2 peripheral

	// set interrupt triggers for USART2 ISR (but do not enable USART2 interrupts yet)
	USART_ITConfig(USART2, USART_IT_TXE, DISABLE);// should be disbled
	USART_ITConfig(USART2, USART_IT_TC, ENABLE); // transmission completed event (for reseting TxReady flag)
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE); // character received (to trigger buffering of new character)
	
	TxReady = 1; // USART2 is ready to transmit
	RX_BUFFER_HEAD = 0; RX_BUFFER_TAIL = 0; // clear rx buffer

	// prepare NVIC to receive USART2 IRQs
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn; 					// configure USART2 interrupts
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;		// max. priority
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;					 // max. priority
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 						// enable USART2 interrupt in NVIC
	NVIC_Init(&NVIC_InitStructure); 														// set NVIC for USART2 IRQ
	
	// enables USART2 interrupt generation
	USART_Cmd(USART2, ENABLE);
}


void USART2_SendChar(char c)
{
	while(!TxReady);
	USART_SendData(USART2, c);
	TxReady = 0;
}


void USART2_SendString(char *s)
{
	while(*s) USART2_SendChar(*s++);
}




int USART2_Dequeue(char* c)
{
	int ret;
	
	ret = 0;
	*c = 0;

	NVIC_DisableIRQ(USART2_IRQn);

	if (RX_BUFFER_HEAD != RX_BUFFER_TAIL)
	{
		*c = RX_BUFFER[RX_BUFFER_TAIL];
		RX_BUFFER_TAIL++;

	if (RX_BUFFER_TAIL == BUFSIZE) RX_BUFFER_TAIL = 0;
		ret = 1;
	}

	NVIC_EnableIRQ(USART2_IRQn);
	return ret;
}



void USART2_IRQHandler(void)
{
	
		static char rx_char;
		static char rx_head;

	// RX event
	if (USART_GetITStatus(USART2, USART_IT_RXNE) == SET)
	{
		USART_ClearITPendingBit(USART2, USART_IT_RXNE); // Ocisti pendingBit
		rx_char = USART_ReceiveData(USART2);        		// primi podatak s USART2

		// check for buffer overrun:
		rx_head = RX_BUFFER_HEAD + 1;
		
		if (rx_head == BUFSIZE) rx_head = 0;
		if (rx_head != RX_BUFFER_TAIL)
			{
		// adding new char will not cause buffer overrun:
				RX_BUFFER[RX_BUFFER_HEAD] = rx_char;
				RX_BUFFER_HEAD = rx_head; 					// update head
			}
	}


	// TX event
	if (USART_GetITStatus(USART2, USART_IT_TC) == SET) // jeli zavrseno slanje znaka s USART2?
	{
		USART_ClearITPendingBit(USART2, USART_IT_TC);
		TxReady = 1;
	}

}

//podaci dolaze preko ISR, koja se izvrsava svaki put kad se primi znak


 
