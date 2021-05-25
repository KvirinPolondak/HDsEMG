/* main.c */
#include <main.h>

//#define BUFSIZE 32  				// defining the FIFO size buffer for received characters
#define BAUDRATE 115200	 
#define txActiveChannelsOnly 
														
//NAPOMENA: RESSET je SPI naredba

int activeSerialPort = 0; 				//	data will be sent to serial port
int gNumActiveChan=8;							// 	broj aktivnih kanala	

BitAction isRDATAC = Bit_RESET;  	// 	na pocetku je postavljen u 0, znaci nije u RDATAC!!!!
																	//	njega postavlja naredba iz Matlaba ili Labviewa 
/*
	*/

void provjeri_naredbe() { //handle commands to ADS device
  
	uint8_t USART_Buffer[2];
	uint8_t  val=0;
	uint8_t  bias1=0;
	uint8_t  bias2=0;
	uint8_t  ch=0;
	
	uint8_t  adresa_ch=0;
	
	val= TM_USART_Getc(USART3);
	if (val < 1) return;  // PC njemu salje zeli li RDATAC, SDATAC ili RDATA
        	
/*** provjera naredbe za pokretanje/zaustavljanje kontinuiranog citanja ***/
	
	if ((val >= 0x10) && (val <= 0x12)) { 							// pokretanje kontinuiranog citanja
        if (val == RDATAC) isRDATAC = Bit_SET;		
        if (val == SDATAC) isRDATAC = Bit_RESET;
        if (val == RDATA)	 isRDATAC = Bit_RESET;
				adc_send_command(val);
        return;																			// kad je detektirao sto PC zeli, izlazi iz funkcije
  }
 
/*** ***/
	
	
	/*** provjera koje bias sklopke su ukljucene ***/
		
		if ((val >= 0x13) && (val <= 0x22)){		
		
					bias1=adc_rreg(BIAS_SENSP);
					bias2=adc_rreg(BIAS_SENSN);
			

			switch(val){
			
			
			case 0x13:	{
									adc_wreg(BIAS_SENSP, BIAS_SENSP_const|bias1|BIASP1);		// ukljuci BIAS1P
									adc_wreg(BIAS_SENSN, BIAS_SENSN_const|bias2|BIASN1);		// ukljuci BIAS1N																									
									break;	}
			
			case 0x14: 	{									
									adc_wreg(BIAS_SENSP, bias1&(~BIASP1));									// iskljuci BIAS1P
									adc_wreg(BIAS_SENSN, bias2&(~BIASN1));									// iskljuci BIAS1N
									break;	}																									
			
			case 0x15: 	{
									adc_wreg(BIAS_SENSP, BIAS_SENSP_const|bias1|BIASP2);		// ukljuci BIAS2P
									adc_wreg(BIAS_SENSN, BIAS_SENSN_const|bias2|BIASN2);		// ukljuci BIAS2N			 	
									break;	}
									 
			case 0x16: 	{
									adc_wreg(BIAS_SENSP, bias1&(~BIASP2));									// iskljuci BIAS2P
									adc_wreg(BIAS_SENSN, bias2&(~BIASN2));									// iskljuci BIAS2N
									break;	}																								
			
			
			case 0x17: 	{
									adc_wreg(BIAS_SENSP, BIAS_SENSP_const|bias1|BIASP3);		// ukljuci BIAS3P
									adc_wreg(BIAS_SENSN, BIAS_SENSN_const|bias2|BIASN3);		// ukljuci BIAS3N						
									break;	}
									 
			case 0x18:	{
									adc_wreg(BIAS_SENSP, bias1&(~BIASP3));									// iskljuci BIAS3P
									adc_wreg(BIAS_SENSN, bias2&(~BIASN3));									// iskljuci BIAS3N
									break;	}																								
			
			
			case 0x19: 	{
									adc_wreg(BIAS_SENSP, BIAS_SENSP_const|bias1|BIASP4);		// ukljuci BIAS4P
									adc_wreg(BIAS_SENSN, BIAS_SENSN_const|bias2|BIASN4);		// ukljuci BIAS4N	
									break;	}																														
			
			case 0x1A: 	{
									adc_wreg(BIAS_SENSP, bias1&(~BIASP4));									// iskljuci BIAS4P
									adc_wreg(BIAS_SENSN, bias2&(~BIASN4));									// iskljuci BIAS4N
									break;	}																								
			
			case 0x1B: 	{
									adc_wreg(BIAS_SENSP, BIAS_SENSP_const|bias1|BIASP5);		// ukljuci BIAS5P
									adc_wreg(BIAS_SENSN, BIAS_SENSN_const|bias2|BIASN5);		// ukljuci BIAS5N
									break;	}																															
			
			case 0x1C: 	{
									adc_wreg(BIAS_SENSP, bias1&(~BIASP5));									// iskljuci BIAS5P
									adc_wreg(BIAS_SENSN, bias2&(~BIASN5));									// iskljuci BIAS5N
									break;	}																								
			
			case 0x1D: 	{
									adc_wreg(BIAS_SENSP, BIAS_SENSP_const|bias1|BIASP6);		// ukljuci BIAS6P
									adc_wreg(BIAS_SENSN, BIAS_SENSN_const|bias2|BIASN6);		// ukljuci BIAS6N
									break;	}																											
			
									 
			case 0x1E: 	{
									adc_wreg(BIAS_SENSP, bias1&(~BIASP6));									// iskljuci BIAS6P
									adc_wreg(BIAS_SENSN, bias2&(~BIASN6));									// iskljuci BIAS6N
									break;	}																								
			
			case 0x1F: 	{adc_wreg(BIAS_SENSP, BIAS_SENSP_const|bias1|BIASP7);		// ukljuci BIAS7P
									 adc_wreg(BIAS_SENSN, BIAS_SENSN_const|bias2|BIASN7);		// ukljuci BIAS7N
										break; 	}																									
			
			case 0x20: 	{
									adc_wreg(BIAS_SENSP, bias1&(~BIASP7));									// iskljuci BIAS7P
									adc_wreg(BIAS_SENSN, bias2&(~BIASN7));									// iskljuci BIAS7N
									break;	}																									
			
			case 0x21: 	{adc_wreg(BIAS_SENSP, BIAS_SENSP_const|bias1|BIASP8);		// ukljuci BIAS8P
									adc_wreg(BIAS_SENSN, BIAS_SENSN_const|bias2|BIASN8);		// ukljuci BIAS8N
									break;	}																									
			
			case 0x22: 	{
									adc_wreg(BIAS_SENSP, bias1&(~BIASP8));									// iskljuci BIAS8P
									adc_wreg(BIAS_SENSN, bias2&(~BIASN8));									// iskljuci BIAS8N
									break;	}																								
			
										
			default: 		return;
			
			}		
	}
	
	/*** ***/
	
//	if (val==0xA4)  {	bias1=adc_rreg(BIAS_SENSP);
//										bias2=adc_rreg(BIAS_SENSN);
//										USART_Buffer[0]=bias1;
//										USART_Buffer[1]=bias2;		
//										TM_USART_Send(USART3, (uint8_t *)USART_Buffer, sizeof(USART_Buffer));

//										}
	
	
	
	if (val==0xA3)  {	ch=adc_rreg(CH2SET);
										USART_Buffer[0]=ch;		
										TM_USART_Send(USART3, (uint8_t *)USART_Buffer, sizeof(USART_Buffer)); 	
										return;
										}
	if (val==0xA4)  {	ch=adc_rreg(CH3SET);
										USART_Buffer[0]=ch;		
										TM_USART_Send(USART3, (uint8_t *)USART_Buffer, sizeof(USART_Buffer)); 	
										return;
										}
	
										
	/*** postavljanje kanala ***/	
	
	if ((val >= 0x23) && (val <= 0xA2)){				// ako je odabran neki od kanala
					
		if(val<=0x32)		  											adresa_ch=CH1SET;			// koji kanal je odabran
																						
		else if((val>=0x33) && (val<=0x42))  		adresa_ch=CH2SET;			
																						
		else if((val>=0x43) && (val<=0x52))  		adresa_ch=CH3SET;			
																						
		else if((val>=0x53) && (val<=0x62))  		adresa_ch=CH4SET;			
																					
		else if((val>=0x63) && (val<=0x72))  		adresa_ch=CH5SET;			
																					
		else if((val>=0x73) && (val<=0x82))  		adresa_ch=CH6SET;			
																						
		else if((val>=0x83) && (val<=0x92))  		adresa_ch=CH7SET;		
																					
		else 		adresa_ch=CH8SET;
					
		
		ch=adc_rreg(adresa_ch);
						
		
		val = (val&0xF);
			
									switch(val){
									
									
									case 0x3:	{
															adc_wreg(adresa_ch, ch&(~PD_1));					// iskljuci CHnSET PD1																					
															break;	}	
									
									case 0x4: {
															adc_wreg(adresa_ch, ch|PD_1);							// ukljuci CHnSET PD1																								
															break;	}																												
									
									case 0x5: {
															adc_wreg(adresa_ch, ch&(~SRB2_1));				// iskljuci CHnSET SRB2_1																					
															break;	}
															 
									case 0x6: {	adc_wreg(adresa_ch, ch|SRB2_1);						// ukljuci CHnSET SRB2_1																								
															break;	}	
									
									
									case 0x7: {	adc_wreg(adresa_ch, (ch|GAIN12|GAIN11)&(~GAIN10));	// ukljuci CHnSET GAIN 24																								
															break;	}
															 
									case 0x8:	{	adc_wreg(adresa_ch, (ch&(~GAIN11))|GAIN12|GAIN10);	// ukljuci CHnSET GAIN 12																								
															break;	}	
									
									
									case 0x9: {	adc_wreg(adresa_ch, (ch&(~GAIN11)&(~GAIN10))|GAIN12);	// ukljuci CHnSET GAIN 8																							
															break;	}						
									
									case 0xA: {	adc_wreg(adresa_ch, (ch&(~GAIN12))|GAIN11|GAIN10);		// ukljuci CHnSET GAIN 6																								
															break;	}
									
									case 0xB: {	adc_wreg(adresa_ch, (ch&(~GAIN12)&(~GAIN10))|GAIN11);	// ukljuci CHnSET GAIN 4																								
															break;	}					
									
									case 0xC: {	adc_wreg(adresa_ch, (ch&(~GAIN12)&(~GAIN11))|GAIN10);	// ukljuci CHnSET GAIN 2																								
															break;	}	
									
									case 0xD: {	adc_wreg(adresa_ch, ch&(~GAIN12)&(~GAIN11)&(~GAIN10));	// ukljuci CHnSET GAIN 1																								
															break;	}		
									
															 
									case 0xE: {	adc_wreg(adresa_ch, (ch&(~MUX12)&(~MUX11)&(~MUX10)));		// ukljuci CHnSET Elektrode																								
															break;	}	
									
									case 0xF: {	adc_wreg(adresa_ch, (ch&(~MUX12)&(~MUX11))|MUX10);			// ukljuci CHnSET kratki spoj																								
															break;	}		
									
									case 0x0: {	adc_wreg(adresa_ch, (ch&(~MUX12))|MUX11|MUX10);					// ukljuci CHnSET MVdd																								
															break;	}			
									
									case 0x1: {	adc_wreg(adresa_ch, (ch&(~MUX11)&(~MUX10))|MUX12);			// ukljuci CHnSET Temperatura																								
															break;	}	
									
									case 0x2: {	adc_wreg(adresa_ch, (ch&(~MUX11))|MUX12|MUX10);					// ukljuci CHnSET Testni signal																								
															break;	}	
									
																
									default: 		return;
									
								}		
	
	
	}
	
	/*** ***/

	
	/*** postavljanje CONFIG2 registra ***/
	
	if ((val >= 0xA5) && (val <= 0xAB)){		
		
					ch=adc_rreg(CONFIG2);
			

			switch(val){
			
			
			case 0xA5:	{
									adc_wreg(CONFIG2, ch&(~INT_CAL));												// testni je generiran izvana																								
									break;	}
			
			case 0xA6: 	{									
									adc_wreg(CONFIG2, ch|INT_CAL);												// testni je generiran iznutra
									break;	}	
			case 0xA7: 	{									
									adc_wreg(CONFIG2, ch&(~CAL_AMP0));										// amplituda prva
									break;}	
			case 0xA8: 	{									
									adc_wreg(CONFIG2, ch|CAL_AMP0);												// amplituda druga
									break;}	
			case 0xA9: 	{									
									adc_wreg(CONFIG2, ch&(~CAL_FREQ1)&(~CAL_FREQ0));			// frekvencija prva
									break;}						
			case 0xAA: 	{									
									adc_wreg(CONFIG2, (ch&(~CAL_FREQ1))|CAL_FREQ0);				// frekvencija druga
									break;}						
			case 0xAB: 	{									
									adc_wreg(CONFIG2, ch|CAL_FREQ1|CAL_FREQ0);						// frekvencija - DC
									break;}		
				
			default: return;
			}
	}									
									
	/*** ***/


/*** postavljanje CONFIG3 registra ***/
	
	if ((val >= 0xAC) && (val <= 0xB1)){		
		
					ch=adc_rreg(CONFIG3);
			

			switch(val){
			
			
			case 0xAC:	{
									adc_wreg(CONFIG3, ch&(~PD_REFBUF));										// iskljuci buffer za referencu 																							
									break;	}
			
			case 0xAD: 	{									
									adc_wreg(CONFIG3, ch|PD_REFBUF);											// ukljuci buffer za referencu
									break;	}	
			case 0xAE: 	{									
									adc_wreg(CONFIG3, ch&(~BIASREF_INT));									// referenca za BIAS vanjska 
									break;}	
			case 0xAF: 	{									
									adc_wreg(CONFIG3, ch|BIASREF_INT);										// referenca za BIAS unutarnja
									break;}	
			case 0xB0: 	{									
									adc_wreg(CONFIG3, ch&(~PD_BIAS));											// BIAS buffer je power down
									break;}						
			case 0xB1: 	{									
									adc_wreg(CONFIG3, ch|PD_BIAS);													// BIAS buffer je ukljucen
									break;}								
				
			default: return;
			}
	}									
									
	/*** ***/
	
}

/*
	*/

/*
	*/

void posalji_podatke(void) { 
  
	int numSerialBytes=1 + (3 * gNumActiveChan); 
  int i = 0;
	unsigned char serialBytes[27];			//inicijaliziraj polje npr. od 25 
	int ch;
	
	if ((!isRDATAC) || (gNumActiveChan < 1) )  return;					// ako ne zelimo citat kontinuirano ili su svi kanali KS
  if (GPIO_ReadInputDataBit(DRDY_PIN_GPIOx,DRDY_PIN_PinNumber) == 1) return;  // jer DRDY je aktivan nisko, mora bit nisko
	GPIO_WriteBit(CS_PIN_GPIOx, CS_PIN_PinNumber,Bit_RESET); 		// postavi CS u stanje LOW
          
    
	
			serialBytes[i++] =TM_SPI_Send(SPI1, 0);				 	//get 1st byte of header
      TM_SPI_Send(SPI1,0); 														//skip 2nd byte of header
      TM_SPI_Send(SPI1,0); 														//skip 3rd byte of header
     
		 
		 for (ch = 1; ch <= gNumActiveChan; ch++) {		// idi po polju koje reprezentira koji su kanali aktivni (idi po kanalu)
        
						serialBytes[i++] =TM_SPI_Send(SPI1,0);
            serialBytes[i++] =TM_SPI_Send(SPI1,0);
            serialBytes[i++] =TM_SPI_Send(SPI1,0); 
      }
       
		DelayUs(3); 
		GPIO_WriteBit(CS_PIN_GPIOx, CS_PIN_PinNumber,Bit_SET); 					// postavi CS u stanje HIGH
     
		TM_USART_Send(USART3, (uint8_t *)serialBytes, numSerialBytes);	// posalji podatke preko serije				
}



/*
	*/


void adsSetup() { 																		//default settings for ADS1299
  
	int i;   
  
	adc_wreg(GPIO, 0);																	// Sve GPIO registre u 0x00:(kako ne bi CMOS ulazi hvatali vanjski sum)
	adc_wreg(CONFIG1,	HIGH_RES_250_SPS);
	adc_wreg(CONFIG3, CONFIG3_const | PD_REFBUF );
																											// ukljuci: buffer reference
	
	for (i = 1; i<=8; ++i) {																						
		adc_wreg((CHnSET + i), (ELECTRODE_INPUT | GAIN_24X)); //postavi da pocetno mjeri signal s elektroda
	}
	GPIO_WriteBit(START_PIN_GPIOx, START_PIN_PinNumber,Bit_SET);
}


/*
	*/


/*
	*/


void provjeri_naredbe(void);
void posalji_podatke(void);
void adsSetup(void);


int main(void)
{
	TimInit();
	
	gpio_init();																				// definicija GPIO pinova kao CS(izlaz), START(izlaz), DRDY(ulaz)
	
	TM_USART_Init(USART3, TM_USART_PinsPack_1, BAUDRATE);	// inicijaliziraj seriju: USART3 on pins TX = PB10, RX = PB11 */
			
		// inicijaliziraj SPI:	SCK = PA5, MOSI = PA7, MISO = PA6
	TM_SPI_InitFull(SPI1, TM_SPI_PinsPack_1, TM_SPIx_PRESCALER, TM_SPIx_MODE, TM_SPIx_MASTERSLAVE, TM_SPIx_FIRSTBIT);	// inicijaliziraj SPI1 i PinsPack_1
	GPIO_WriteBit(CS_PIN_GPIOx, CS_PIN_PinNumber,Bit_SET);
	
	//Ukljuci ADS1299	
	DelayMs(256); //--> cekaj da se ADS1299 ukljuci
	DelayMs(256);
		
	adc_send_command(SDATAC); // Posalji SDATAC naredbu (Zaustavi kontinuirani nacin rada)
	DelayMs(10);

	adsSetup(); 			//opcionalna naredba - postavlja inicijalno ADS1299	

	while(1)
{
	
	provjeri_naredbe();
	posalji_podatke(); 					//ima li novih uzoraka 
		
}



}

