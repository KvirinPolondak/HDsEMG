#include "ADS1299.h"

ADS1299 ADS;
int count = 0;                         

void setup() {
  ADS.initialize(8,9,10,4,false); // (DRDY pin, RST pin, CS pin, SCK frequency in MHz);

  Serial.begin(115200);
  Serial.println("ADS1299-Arduino UNO Example 2");
  delay(1000);             

  ADS.verbose = true;      // when verbose is true, there will be Serial feedback
  //ADS.START();
  ADS.RESET();             // send RESET command to default all registers
  ADS.SDATAC();           // exit Read Data Continuous mode to communicate with ADS
  ADS.RREG(0x00);       
} // end of setup

void loop(){
 
}
_______________________________________________________________________________________

#include "pins_arduino.h"
#include "ADS1299.h"

void ADS1299::initialize(int _DRDY, int _RST, int _CS, int _FREQ, boolean _isDaisy){
   isDaisy = _isDaisy;
   DRDY = _DRDY;
   CS = _CS;
   int FREQ = _FREQ;
   int RST = _RST;
   
   delay(50);            // recommended power up sequence requiers Tpor (~32mS)   
   pinMode(RST,OUTPUT);
   digitalWrite(RST,LOW);
   delayMicroseconds(4);   // toggle reset pin
   digitalWrite(RST,HIGH);
   delayMicroseconds(20);   // recommended to wait 18 Tclk before using device (~8uS);
   

    // **** ----- SPI Setup ----- **** //
   
    // Set direction register for SCK and MOSI pin.
    // MISO pin automatically overrides to INPUT.
    // When the SS pin is set as OUTPUT, it can be used as
    // a general purpose output port (it doesn't influence
    // SPI operations).
   
    pinMode(13, OUTPUT);   //SCK
    pinMode(11, OUTPUT);   //MOSI
    pinMode(10, OUTPUT);   //CS
   
    digitalWrite(13, LOW);
    digitalWrite(11, LOW);
    digitalWrite(10, HIGH);
   
    // set as master and enable SPI
    SPCR |= _BV(MSTR);
    SPCR |= _BV(SPE);
    //set bit order
    SPCR &= ~(_BV(DORD)); ////SPI data format is MSB (pg. 25)
     // set data mode
    SPCR = (SPCR & ~SPI_MODE_MASK) | SPI_DATA_MODE; //clock polarity = 0; clock phase = 1 (pg. 8)
    // set clock divider
     switch (FREQ){
        case 8:
           DIVIDER = SPI_CLOCK_DIV_2;
           break;
        case 4:
           DIVIDER = SPI_CLOCK_DIV_4;
           break;
        case 1:
           DIVIDER = SPI_CLOCK_DIV_16;
           break;
        default:
           break;
     }
    SPCR = (SPCR & ~SPI_CLOCK_MASK) | (DIVIDER);  // set SCK frequency 
    SPSR = (SPSR & ~SPI_2XCLOCK_MASK) | (DIVIDER); // by dividing 16MHz system clock 
   
    // **** ----- End of SPI Setup ----- **** //
   
    // initalize the  data ready chip select and reset pins:
    pinMode(8, INPUT);

     digitalWrite(RST,HIGH);
}

//System Commands
void ADS1299::WAKEUP() {
    digitalWrite(CS, LOW);
    transfer(_WAKEUP);
    digitalWrite(CS, HIGH);
    delayMicroseconds(3);      //must wait 4 tCLK cycles before sending another command (Datasheet, pg. 35)
}

void ADS1299::STANDBY() {   // only allowed to send WAKEUP after sending STANDBY
    digitalWrite(CS, LOW);
    transfer(_STANDBY);
    digitalWrite(CS, HIGH);
}

void ADS1299::RESET() {     // reset all the registers to default settings
    digitalWrite(CS, LOW);
    transfer(_RESET);
    delayMicroseconds(12);    //must wait 18 tCLK cycles to execute this command (Datasheet, pg. 35)
    digitalWrite(CS, HIGH);
}

void ADS1299::START() {     //start data conversion
    digitalWrite(CS, LOW);
    transfer(_START);
    digitalWrite(CS, HIGH);
}

void ADS1299::STOP() {      //stop data conversion
    digitalWrite(CS, LOW);
    transfer(_STOP);
    digitalWrite(CS, HIGH);
}

void ADS1299::RDATAC() {
    digitalWrite(CS, LOW);
    transfer(_RDATAC);
    digitalWrite(CS, HIGH);
  delayMicroseconds(3);   
}
void ADS1299::SDATAC() {
    digitalWrite(CS, LOW);
    transfer(_SDATAC);
    digitalWrite(CS, HIGH);
  delayMicroseconds(3);   //must wait 4 tCLK cycles after executing this command (Datasheet, pg. 37)
}

byte ADS1299::RREG(byte _address) {      //  reads ONE register at _address
    byte opcode1 = _address + 0x20;    //  RREG expects 001rrrrr where rrrrr = _address
    digitalWrite(CS, LOW);    //  open SPI
    transfer(opcode1);            //  opcode1
    //delayMicroseconds(5);
    transfer(0x00);                //  opcode2
    //delayMicroseconds(5);
    regData[_address] = transfer(0x00);//  update mirror location with returned byte
    //delayMicroseconds(5);
    digitalWrite(CS, HIGH);          //  close SPI   
   
     if (verbose){                  //  verbose output
        Serial.print("ID :");
        printHex(_address);
        Serial.print(", ");
        printHex(regData[_address]);
        Serial.print(", ");
        for(byte j = 0; j<8; j++){
           Serial.print(bitRead(regData[_address], 7-j));
           if(j!=7) Serial.print(", ");
        }
        Serial.println();
     }
     return regData[_address];         // return requested register value
}


//SPI communication methods
byte ADS1299::transfer(byte _data) {
   cli();
  SPDR = _data;
  while (!(SPSR & _BV(SPIF)));
   sei();
  return SPDR;
}

// Used for printing HEX in verbose feedback mode
void ADS1299::printHex(byte _data){
   Serial.print("0x");
    if(_data < 0x10) Serial.print("0");
    Serial.print(_data, HEX);
}
_______________________________________________________________________________________

My output is random actually.

My wiring:

  SCK = 13
  MISO [DOUT] = 12
  MOSI [DIN] = 11
  CS = 10;
  RESET = 9;
  DRDY = 8;
