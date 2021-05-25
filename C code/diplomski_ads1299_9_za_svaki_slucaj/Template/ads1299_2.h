//#ifndef ADS1299_H
//#define ADS1299_H

// NAPOMENA: RESSET je SPI naredba

//spi_command 
		
		// system commands
#define		WAKEUP  0x02
#define		STANDBY  0x04
#define		RESSET  0x06
#define		START  0x08
#define		STOP  0x0a

		// read commands
#define		RDATAC  0x10
#define		SDATAC  0x11
#define		RDATA  0x12

		// register commands
#define		RREG  0x20					// samo prvi bajt -> broj registara koji moraju biti procitani-1(inicijalno nula)
#define		WREG  0x40						// samo prvi bajt -> broj registara u koje mora biti upisano-1 (inicijalno nula)


//adrese registara:

/*
*/

			// device settings
#define		ID  0x00

		// global settings
#define				CONFIG1 0x01
#define				CONFIG2 0x02
#define				CONFIG3 0x03
#define				LOFF  0x04

		// channel specific settings
#define				CHnSET  0x04
#define				CH1SET  CHnSET + 1
#define				CH2SET  CHnSET + 2
#define				CH3SET  CHnSET + 3
#define				CH4SET  CHnSET + 4
#define				CH5SET  CHnSET + 5
#define				CH6SET  CHnSET + 6
#define				CH7SET  CHnSET + 7
#define				CH8SET  CHnSET + 8
#define				BIAS_SENSP  0x0D
#define				BIAS_SENSN  0x0E
#define				LOFF_SENSP  0x0F
#define				LOFF_SENSN  0x10
#define				LOFF_FLIP  0x11

		// lead off status
#define				LOFF_STATP  0x12
#define				LOFF_STATN  0x13

		// other
#define				GPIO  0x14
#define				MISC1  0x15
#define				MISC2  0x16
#define				CONFIG4  0x17



/*
*/

// ID_bits - ID reg

#define		REV_ID3  0x80
#define		REV_ID2  0x40
#define		REV_ID1  0x20
#define		DEV_ID2  0x08
#define		DEV_ID1  0x04
#define		NU_CH2  0x02
#define		NU_CH1  0x01

#define		ID_const  0x10
#define		ID_ADS129x  REV_ID3
#define		ID_ADS129xR  (REV_ID3 | REV_ID2)

#define		ID_4CHAN  0
#define		ID_6CHAN  NU_CH1
#define		ID_8CHAN  DEV_ID1

#define		ID_ADS1294  (ID_ADS129x | ID_4CHAN)
#define		ID_ADS1296  (ID_ADS129x | ID_6CHAN)
#define		ID_ADS1298  (ID_ADS129x | ID_8CHAN)
#define		ID_ADS1294R  (ID_ADS129xR | ID_4CHAN)
#define		ID_ADS1296R  (ID_ADS129xR | ID_6CHAN)
#define		ID_ADS1298R  (ID_ADS129xR | ID_8CHAN)


/*
*/

// CONFIG1_bits 
//#define		HR 0x80         // promjenio sam iz 0x80 u 0x90!!!!!!! 
#define		DAISY_EN  0x40
#define		CLK_EN  0x20
#define		DR2  0x04
#define		DR1  0x02
#define		DR0  0x01

							// ADS1299
#define		CONFIG1_const  0x90    // tako pise u Datasheetu - kod Adama => CONFIG1_const = 0xE0

              // ADS1298
                /*
		HIGH_RES_32k_SPS = HR,
		HIGH_RES_16k_SPS = (HR | DR0),
		HIGH_RES_8k_SPS = (HR | DR1),
		HIGH_RES_4k_SPS = (HR | DR1 | DR0),
		HIGH_RES_2k_SPS = (HR | DR2),
		HIGH_RES_1k_SPS = (HR | DR2 | DR0),
		HIGH_RES_500_SPS = (HR | DR2 | DR1),
		LOW_POWR_250_SPS = (DR2 | DR1)
                */
                
                // ADS1299
#define		HIGH_RES_16k_SPS  CONFIG1_const
#define		HIGH_RES_8k_SPS  (CONFIG1_const | DR0)
#define		HIGH_RES_4k_SPS  (CONFIG1_const | DR1)
#define		HIGH_RES_2k_SPS  (CONFIG1_const | DR1 | DR0)
#define		HIGH_RES_1k_SPS  (CONFIG1_const | DR2)
#define		HIGH_RES_500_SPS  (CONFIG1_const | DR2 | DR0)
#define		HIGH_RES_250_SPS  (CONFIG1_const | DR2 | DR1)



/*
*/	
	
	
// CONFIG2_bits 
#define		INT_CAL  0x10					// da je testni signal interno generiran
#define		CAL_AMP0 0x04					// stavi vecu amplitudu
#define		CAL_FREQ1  0x02				// frekvencija testnog signala 2HZ
#define		CAL_FREQ0  0x01				// frekvencija testnog signala DC

		       // ADS1298
		//CONFIG2_const = 0x00,

           // ADS1299
#define		CONFIG2_const  0xC0
				
#define		INT_TEST_1HZ  INT_CAL 
#define		INT_TEST_2HZ  (INT_CAL | CAL_FREQ0)
#define		INT_TEST_DC  (INT_CAL | CAL_FREQ1 | CAL_FREQ0)



/*
*/	
	
// CONFIG3_bits 
#define		PD_REFBUF  0x80
#define		BIAS_MEAS  0x10
#define		BIASREF_INT  0x08
#define		PD_BIAS  0x04
#define		BIAS_LOFF_SENS  0x02
#define		BIAS_STAT  0x01

		        // ADS1298
		//CONFIG3_const = 0x40

           // ADS1299
		
#define		CONFIG3_const  0x60



/*
*/	
	
// LOFF_bits 
#define		COMP_TH2  0x80
#define		COMP_TH1  0x40
#define		COMP_TH0  0x20
#define		VLEAD_OFF_EN  0x10
#define		ILEAD_OFF1  0x08
#define		ILEAD_OFF0  0x04
#define		FLEAD_OFF1  0x02
#define		FLEAD_OFF0  0x01

#define		LOFF_const  0x00

#define		COMP_TH_95  0x00
#define		COMP_TH_92_5  COMP_TH0
#define		COMP_TH_90  COMP_TH1
#define		COMP_TH_87_5  (COMP_TH1 | COMP_TH0)
#define		COMP_TH_85  COMP_TH2
#define		COMP_TH_80  (COMP_TH2 | COMP_TH0)
#define		COMP_TH_75  (COMP_TH2 | COMP_TH1)
#define		COMP_TH_70  (COMP_TH2 | COMP_TH1 | COMP_TH0)

#define		ILEAD_OFF_6nA 0x00
#define		ILEAD_OFF_12nA  ILEAD_OFF0
#define		ILEAD_OFF_18nA  ILEAD_OFF1
#define		ILEAD_OFF_24nA  (ILEAD_OFF1 | ILEAD_OFF0)

#define		FLEAD_OFF_AC  FLEAD_OFF0
#define		FLEAD_OFF_DC  (FLEAD_OFF1 | FLEAD_OFF0)
	

/*
*/	
		
// CHnSET_bits {
#define		PDn  0x80
#define		PD_n  0x80
#define		GAINn2  0x40
#define		GAINn1  0x20
#define		GAINn0  0x10
#define		SRB2  0x08
#define		MUXn2  0x04
#define		MUXn1  0x02
#define		MUXn0  0x01

#define		CHnSET_const  0x00

#define		GAIN_1X  0x00
#define		GAIN_2X  GAINn0
#define		GAIN_4X  GAINn1
#define		GAIN_6X  (GAINn1|GAINn0)
#define		GAIN_8X  GAINn2
#define		GAIN_12X  (GAINn2 | GAINn0)
#define		GAIN_24X  (GAINn2 | GAINn1)

#define		ELECTRODE_INPUT  0x00
#define		SHORTED  MUXn0
#define		RLD_INPUT  MUXn1
#define		MVDD  (MUXn1 | MUXn0)
#define		TEMP  MUXn2
#define		TEST_SIGNAL  (MUXn2 | MUXn0)
#define		RLD_DRP  (MUXn2 | MUXn1)
#define		RLD_DRN  (MUXn2 | MUXn1 | MUXn0)
//	};


/*
*/

// CH1SET_bits {
#define		PD_1  0x80
#define		GAIN12  0x40
#define		GAIN11  0x20
#define		GAIN10  0x10
#define		SRB2_1  0x08
#define		MUX12  	0x04
#define		MUX11  	0x02
#define		MUX10 	0x01

#define		CH1SET_const  0x61
	//};


/*
*/


//	enum CH2SET_bits {
#define		PD_2  0x80
#define		GAIN22  0x40
#define		GAIN21  0x20
#define		GAIN20  0x10
#define		SRB2_2  0x08
#define		MUX22  0x04
#define		MUX21  0x02
#define		MUX20  0x01

#define		CH2SET_const  0x61
//	};



/*
*/

//	enum CH3SET_bits {
#define		PD_3  0x80
#define		GAIN32  0x40
#define		GAIN31  0x20
#define		GAIN30  0x10
#define		SRB2_3  0x08
#define		MUX32  0x04
#define		MUX31 0x02
#define		MUX30  0x01

#define		CH3SET_const  0x61
//	};



/*
*/


//	enum CH4SET_bits {
#define		PD_4  0x80
#define		GAIN42  0x40
#define		GAIN41  0x20
#define		GAIN40  0x10
#define		SRB2_4  0x08
#define		MUX42  0x04
#define		MUX41 0x02
#define		MUX40  0x01

#define		CH4SET_const  0x61
//	};



/*
*/

//	enum CH5SET_bits {
#define		PD_5  0x80
#define		GAIN52  0x40
#define		GAIN51  0x20
#define		GAIN50  0x10
#define		SRB2_5  0x08
#define		MUX52  0x04
#define		MUX51  0x02
#define		MUX50  0x01

#define		CH5SET_const  0x61
	//};



/*
*/


//	enum CH6SET_bits {
#define		PD_6  0x80
#define		GAIN62  0x40
#define		GAIN61  0x20
#define		GAIN60  0x10
#define		SRB2_6  0x08
#define		MUX62  0x04
#define		MUX61  0x02
#define		MUX60  0x01

#define		CH6SET_const  0x61
//	};



/*
*/


//	enum CH7SET_bits {
#define		PD_7  0x80
#define		GAIN72  0x40
#define		GAIN71  0x20
#define		GAIN70  0x10
#define		SRB2_7  0x08
#define		MUX72  0x04
#define		MUX71  0x02
#define		MUX70  0x01

#define		CH7SET_const  0x61
//	};



/*
*/

	//enum CH8SET_bits {
#define		PD_8  0x80
#define		GAIN82  0x40
#define	GAIN81  0x20
#define		GAIN80  0x10
#define		SRB2_8  0x08
#define		MUX82  0x04
#define		MUX81  0x02
#define		MUX80  0x01

#define		CH8SET_const  0x61
//	};


/*
*/

//	enum BIAS_SENSP_bits {
#define		BIASP8  0x80
#define		BIASP7  0x40
#define		BIASP6  0x20
#define		BIASP5  0x10
#define		BIASP4  0x08
#define		BIASP3  0x04
#define		BIASP2  0x02
#define		BIASP1 	0x01

#define		BIAS_SENSP_const  0x00
//	};



/*
*/

	//enum BIAS_SENSN_bits {
#define		BIASN8  0x80
#define		BIASN7  0x40
#define		BIASN6  0x20
#define		BIASN5  0x10
#define		BIASN4  0x08
#define		BIASN3  0x04
#define		BIASN2  0x02
#define		BIASN1  0x01

#define		BIAS_SENSN_const  0x00
	//};



/*
*/

	//enum LOFF_SENSP_bits {
#define		LOFF8P  0x80
#define		LOFF7P  0x40
#define		LOFF6P  0x20
#define		LOFF5P  0x10
#define		LOFF4P  0x08
#define		LOFF3P  0x04
#define		LOFF2P  0x02
#define		LOFF1P  0x01

#define		LOFF_SENSP_const  0x00
	//};



/*
*/


	//enum LOFF_SENSN_bits {
#define		LOFF8N  0x80
#define		LOFF7N  0x40
#define		LOFF6N  0x20
#define		LOFF5N  0x10
#define		LOFF4N  0x08
#define		LOFF3N  0x04
#define		LOFF2N  0x02
#define		LOFF1N  0x01

#define		LOFF_SENSN_const  0x00
	//};



/*
*/


	//enum LOFF_FLIP_bits {
#define		LOFF_FLIP8  0x80
#define		LOFF_FLIP7  0x40
#define		LOFF_FLIP6  0x20
#define		LOFF_FLIP5  0x10
#define		LOFF_FLIP4  0x08
#define		LOFF_FLIP3  0x04
#define		LOFF_FLIP2  0x02
#define		LOFF_FLIP1  0x01

#define		LOFF_FLIP_const  0x00
	//};



/*
*/


	//enum LOFF_STATP_bits {
#define		IN8P_OFF  0x80
#define		IN7P_OFF  0x40
#define		IN6P_OFF  0x20
#define		IN5P_OFF  0x10
#define		IN4P_OFF  0x08
#define		IN3P_OFF  0x04
#define		IN2P_OFF  0x02
#define		IN1P_OFF  0x01

#define		LOFF_STATP_const  0x00
	//};



/*
*/


	//enum LOFF_STATN_bits {
#define		IN8N_OFF  0x80
#define		IN7N_OFF  0x40
#define		IN6N_OFF  0x20
#define		IN5N_OFF  0x10
#define		IN4N_OFF  0x08
#define		IN3N_OFF  0x04
#define		IN2N_OFF  0x02
#define		IN1N_OFF  0x01

#define		LOFF_STATN_const  0x00
	//};



/*
*/


//	enum GPIO_bits {
#define		GPIOD4  0x80
#define		GPIOD3  0x40
#define		GPIOD2  0x20
#define		GPIOD1  0x10
#define		GPIOC4  0x08
#define		GPIOC3  0x04
#define		GPIOC2  0x02
#define		GPIOC1  0x01

#define		GPIO_const  0x0F
//	};



/*
*/


	//enum PACE_bits {
#define		PACEE1  0x10
#define		PACEE0  0x08
#define		PACEO1  0x04
#define		PACEO0  0x02
#define		PD_PACE  0x01

#define		PACE_const  0x00

#define		PACEE_CHAN2  0x00
#define		PACEE_CHAN4  PACEE0
#define		PACEE_CHAN6  PACEE1
#define		PACEE_CHAN8  (PACEE1 | PACEE0)

#define		PACEO_CHAN1  0x00
#define		PACEO_CHAN3  PACEE0
#define		PACEO_CHAN5  PACEE1
#define		PACEO_CHAN7  (PACEE1 | PACEE0)
//	};



/*
*/


//enum RESP_bits {
#define		RESP_DEMOD_EN1  0x80
#define		RESP_MOD_EN1  0x40
#define		RESP_PH2  0x10
#define		RESP_PH1  0x08
#define		RESP_PH0  0x04
#define		RESP_CTRL1  0x02
#define		RESP_CTRL0  0x01

#define		RESP_const  0x20

#define		RESP_PH_22_5  0x00
#define		RESP_PH_45  RESP_PH0
#define		RESP_PH_67_5  RESP_PH1
#define		RESP_PH_90  (RESP_PH1 | RESP_PH0)
#define		RESP_PH_112_5  RESP_PH2
#define		RESP_PH_135  (RESP_PH2 | RESP_PH0)
#define		RESP_PH_157_5  (RESP_PH2 | RESP_PH1)

#define		RESP_NONE  0x00
#define		RESP_EXT  RESP_CTRL0
#define		RESP_INT_SIG_INT  RESP_CTRL1
#define		RESP_INT_SIG_EXT  (RESP_CTRL1 | RESP_CTRL0)
	//};



/*
*/

	//enum CONFIG4_bits {
#define		RESP_FREQ2  0x80
#define		RESP_FREQ1  0x40
#define		RESP_FREQ0  0x20
#define		SINGLE_SHOT  0x08
#define		WCT_TO_RLD  0x04
#define		PD_LOFF_COMP  0x02

#define		CONFIG4_const 0x00

#define		RESP_FREQ_64k_Hz 0x00
#define		RESP_FREQ_32k_Hz RESP_FREQ0
#define		RESP_FREQ_16k_Hz RESP_FREQ1
#define		RESP_FREQ_8k_Hz  (RESP_FREQ1 | RESP_FREQ0)
#define		RESP_FREQ_4k_Hz  RESP_FREQ2
#define		RESP_FREQ_2k_Hz  (RESP_FREQ2 | RESP_FREQ0)
#define		RESP_FREQ_1k_Hz  (RESP_FREQ2 | RESP_FREQ1)
#define		RESP_FREQ_500_Hz  (RESP_FREQ2 | RESP_FREQ1 | RESP_FREQ0)
//	};



/*
*/


	//enum WCT1_bits {
#define		aVF_CH6  0x80
#define		aVL_CH5  0x40
#define		aVR_CH7  0x20
#define		avR_CH4  0x10
#define		PD_WCTA  0x08
#define		WCTA2  0x04
#define		WCTA1  0x02
#define		WCTA0 0x01

#define		WCT1_const  0x00

#define		WCTA_CH1P  0x00
#define		WCTA_CH1N  WCTA0
#define		WCTA_CH2P  WCTA1
#define		WCTA_CH2N  (WCTA1 | WCTA0)
#define		WCTA_CH3P  WCTA2
#define		WCTA_CH3N  (WCTA2 | WCTA0)
#define		WCTA_CH4P  (WCTA2 | WCTA1)
#define		WCTA_CH4N  (WCTA2 | WCTA1 | WCTA0)
	//};



/*
*/

	//enum WCT2_bits {
#define		PD_WCTC  0x80
#define		PD_WCTB  0x40
#define		WCTB2  0x20
#define		WCTB1  0x10
#define		WCTB0  0x08
#define		WCTC2  0x04
#define		WCTC1  0x02
#define		WCTC0  0x01

#define		WCT2_const  0x00

#define		WCTB_CH1P  0x00
#define		WCTB_CH1N  WCTB0
#define		WCTB_CH2P  WCTB1
#define		WCTB_CH2N  (WCTB1 | WCTB0)
#define		WCTB_CH3P  WCTB2,
#define		WCTB_CH3N  (WCTB2 | WCTB0)
#define		WCTB_CH4P  (WCTB2 | WCTB1)
#define		WCTB_CH4N  (WCTB2 | WCTB1 | WCTB0)

#define		WCTC_CH1P  0x00
#define		WCTC_CH1N  WCTC0
#define		WCTC_CH2P  WCTC1
#define		WCTC_CH2N  (WCTC1 | WCTC0)
#define		WCTC_CH3P  WCTC2
#define		WCTC_CH3N  (WCTC2 | WCTC0)
#define		WCTC_CH4P  (WCTC2 | WCTC1)
#define		WCTC_CH4N  (WCTC2 | WCTC1 | WCTC0)
	//};



//#endif				/* ADS1299_H */	
