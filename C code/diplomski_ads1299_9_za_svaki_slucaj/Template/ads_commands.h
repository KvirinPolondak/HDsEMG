/* main.h */

//konstante definiraju pinove na STM32
#include <defines.h>
#include <attributes.h>

#define START_PIN_RCC_GPIOx						RCC_AHB1Periph_GPIOD
#define CS_PIN_RCC_GPIOx							RCC_AHB1Periph_GPIOD
#define DRDY_PIN_RCC_GPIOx						RCC_AHB1Periph_GPIOD


#define START_PIN_GPIOx						GPIOD
#define CS_PIN_GPIOx							GPIOD
#define DRDY_PIN_GPIOx						GPIOD

#define START_PIN_PinNumber				GPIO_Pin_0
#define CS_PIN_PinNumber					GPIO_Pin_1
#define DRDY_PIN_PinNumber				GPIO_Pin_2

#define START_PIN_ID 0
#define CS_PIN 1
#define DRDY_PIN_ID 2



#define LED3_ORANGE_RCC_GPIOx						RCC_AHB1Periph_GPIOD
#define LED4_GREEN_RCC_GPIOx						RCC_AHB1Periph_GPIOD
#define LED5_RED_RCC_GPIOx							RCC_AHB1Periph_GPIOD
#define LED6_BLUE_RCC_GPIOx							RCC_AHB1Periph_GPIOD

#define LED3_ORANGE_GPIOx						GPIOD
#define LED4_GREEN_GPIOx						GPIOD
#define LED5_RED_GPIOx							GPIOD
#define LED6_BLUE_GPIOx							GPIOD

#define LED3_ORANGE_PinNumber				GPIO_Pin_13
#define LED4_GREEN_PinNumber				GPIO_Pin_12
#define LED5_RED_PinNumber					GPIO_Pin_14
#define LED6_BLUE_PinNumber					GPIO_Pin_15

#define LED3_ORANGE_ID 1
#define LED4_GREEN_ID 2
#define LED5_RED_ID 3
#define LED6_BLUE_ID 4	


	//const int IPIN_PWDN = 2; //not required for TI demo kit
	//const int PIN_CLKSEL = 6;//6;//*optional
	//const int IPIN_RESET  =3;//*optional
	
	//#define pin_start 	GPIO_Pin_1  //  
	//#define pin_cs 			GPIO_Pin_2  //
	//#define pin_drdy		GPIO_Pin_3  //
	
	//const int PIN_DOUT = 11;//SPI out
	//const int PIN_DIN = 12;//SPI in
	//const int PIN_SCLK = 13;//SPI clock



	//function prototypes
	void gpio_init(void);							
	void gpio_led_state(uint8_t LED_ID, uint8_t state);
	void GPIO_WriteBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, BitAction BitVal);
	uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
	
	
	void adc_wreg(int reg1, int val); //write register
	void adc_send_command(int cmd); //send command
	int adc_rreg(int reg1); 					//read register




