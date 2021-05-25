#include <main.h>


// Zelis li postaviti test signal?
//BitAction testSignal = Bit_SET;


void ads_setupSimple() {
 
  adc_send_command(SDATAC);
  DelayMs(250); //a delay is required to allow the device to respond to commands
  //check device
  ads_getMaxChannels();		// inicijaliziraj uredaj i provjeriu jeli sve u redu
  
	// All GPIO set to output 0x0000: (floating CMOS inputs can flicker on and off, creating noise)
  adc_wreg(GPIO, 0x00); // postavi GPIO registre
  
	//register CONFIG1 sets sample rate, daisy-chain, resolution (high vs power saving) and CLK connection
 
	if (gOscHz < 375) 
    adc_wreg(CONFIG1, HIGH_RES_250_SPS);	// promjenio sam iz 0x80 u 0x90 u ADS1299!!!!!!! 
  else if (gOscHz < 750) 
    adc_wreg(CONFIG1,HIGH_RES_500_SPS);
  else if (gOscHz < 1500) 
    adc_wreg(CONFIG1,HIGH_RES_1k_SPS);
  else if (gOscHz < 3000)
    adc_wreg(CONFIG1,HIGH_RES_2k_SPS);
  else if (gOscHz < 6000)
    adc_wreg(CONFIG1,HIGH_RES_4k_SPS);
  else if (gOscHz < 12000)
    adc_wreg(CONFIG1,HIGH_RES_8k_SPS);
  else  adc_wreg(CONFIG1,HIGH_RES_16k_SPS);

// CONFIG2 - ukljuci i postavi interni test signal
	  adc_wreg(CONFIG2, CONFIG2_const|INT_TEST_1HZ);  // generate internal test signals
																									 
// CONFIG3 - ukljuci buffer za referencu (referentnu vrijednost) -  nije isto sto i referentna elektroda
	// 				- interno generiraj BIASREF/ ukljuci BIAS buffer
	adc_wreg(CONFIG3, CONFIG3_const | PD_REFBUF | BIASREF_INT | PD_BIAS); //PD_REFBUF used for test signal
	DelayMs(150);				
	
	//To use RLD:  Power up the internal reference and wait for it to settle
						// adc_wreg(CONFIG3,char( RLDREF_INT | PD_RLD | PD_REFBUF | VREF_4V | CONFIG3_const));
						// delay(150);
						//You would also specify which channels to use for RLD
						// adc_wreg(RLD_SENSP, char(0x01));  // only use channel IN1P and IN1N
						// adc_wreg(RLD_SENSN, char(0x01));  // for the RLD Measurement

 
// POSTAVI KANALE KOJI CE SNIMATI 
  
	if (testSignal) {																							// ako je interni test signal doista ukljucen
    for (int i = 1; i <= gOscChannels; i++) 										// idi po kanalima i postavi pojacanje i testni signal 
      adc_wreg((CHnSET + i), (TEST_SIGNAL | GAIN_4X));
  
	}  else {																											// ako nije testni signal postavljen
    for (int i = 1; i <= gOscChannels; i++) 
      adc_wreg((CHnSET + i),(ELECTRODE_INPUT | GAIN_12X));			// normalan ulaz i pojacanje 12
  }
  
	if (gOscChannels < kOscMaxChannels) {													// kratko spoji ostale kanale npr. 6-8 (ne mozes birat)
																																//	mozes samo po redu odabirat	
		for (int i = (gOscChannels+1); i <= kOscMaxChannels; i++)
       adc_wreg(CHnSET + i, PDn | SHORTED);  //turn off unused amplifiers 
  }
  
	adc_send_command(RDATAC);  
}


