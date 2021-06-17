#include <SPI.h>

// Define ALTERNATE_PINS to use non-standard GPIO pins for SPI bus

#ifdef ALTERNATE_PINS
  #define VSPI_MISO   2
  #define VSPI_MOSI   4
  #define VSPI_SCLK   0
  #define VSPI_SS     33

  #define HSPI_MISO   26
  #define HSPI_MOSI   27
  #define HSPI_SCLK   25
  #define HSPI_SS     32
#else
  #define VSPI_MISO   MISO
  #define VSPI_MOSI   MOSI
  #define VSPI_SCLK   SCK
  #define VSPI_SS     SS

  #define HSPI_MISO   12
  #define HSPI_MOSI   13
  #define HSPI_SCLK   14
  #define HSPI_SS     15
#endif

#if CONFIG_IDF_TARGET_ESP32S2
#define VSPI FSPI
#endif

const byte WAKEUP = 0b00000010;     // Wake-up from standby mode
const byte STANDBY = 0b00000100;   // Enter Standby mode
const byte RESET = 0b00000110;   // Reset the device
const byte START = 0b00001000;   // Start and restart (synchronize) conversions
const byte STOP = 0b00001010;   // Stop conversion
const byte RDATAC = 0b00010000;   // Enable Read Data Continuous mode (default mode at power-up) 
const byte SDATAC = 0b00010001;   // Stop Read Data Continuous mode
const byte RDATA = 0b00010010;   // Read data by command; supports multiple read back

//Register Read Commands
const byte RREG = 0b00100000;
const byte WREG = 0b01000000;


static const int spiClk = 1000000; // 1 MHz

//uninitalised pointers to SPI objects
SPIClass * vspi = NULL;
SPIClass * hspi = NULL;
void ADS_pwr_up();
void ADSwreg (char adress,char value);
void ADSrreg (char adress);

void setup() {
  //initialise two instances of the SPIClass attached to VSPI and HSPI respectively
  vspi = new SPIClass(VSPI);
  hspi = new SPIClass(HSPI);

  Serial.begin (115000);
  //clock miso mosi ss

#ifndef ALTERNATE_PINS
  //initialise vspi with default pins
  //SCLK = 18, MISO = 19, MOSI = 23, SS = 5
  vspi->begin();
#else
  //alternatively route through GPIO pins of your choice
  vspi->begin(VSPI_SCLK, VSPI_MISO, VSPI_MOSI, VSPI_SS); //SCLK, MISO, MOSI, SS
#endif

#ifndef ALTERNATE_PINS
  //initialise hspi with default pins
  //SCLK = 14, MISO = 12, MOSI = 13, SS = 15
  hspi->begin();
#else
  //alternatively route through GPIO pins
  hspi->begin(HSPI_SCLK, HSPI_MISO, HSPI_MOSI, HSPI_SS); //SCLK, MISO, MOSI, SS
#endif

  //set up slave select pins as outputs as the Arduino API
  //doesn't handle automatically pulling SS low
  pinMode(VSPI_SS, OUTPUT); //VSPI SS
  pinMode(HSPI_SS, OUTPUT); //HSPI SS

  delay(10);  //delay to ensure connection
  
  digitalWrite(VSPI_SS, LOW); //Low to communicated
  vspi->transfer(RESET);  
  digitalWrite(VSPI_SS, HIGH); //Low to communicated

  delay(10);  //delay to ensure connection

}

// the loop function runs over and over again until power down or reset
void loop() {
  //use the SPI buses
 getDeviceID();
//  hspiCommand();
  delay(100);
}

void getDeviceID() {
 // byte data = 0b01010101; // junk data to illustrate usage
// byte data = 0x20;

  //use it as you would the regular arduino SPI API

  ADS_pwr_up();
  vspi->beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE1));
  digitalWrite(VSPI_SS, LOW); //pull SS slow to prep other end for transfer
  vspi->transfer(0b00010001);  
  vspi->transfer(0b00100000);  
  vspi->transfer(0b00000001);
  byte pom =  vspi->transfer(0x00);
  
  digitalWrite(VSPI_SS, HIGH); //pull ss high to signify end of data transfer
  vspi->endTransaction();

  Serial.println(pom, BIN);
  

 // ADSrreg(0b00000000);
}
void ADSwreg (char adress,char value){
  char opcode1 = WREG + adress;
  digitalWrite(VSPI_SS, LOW);//pull SS slow to prep other end for transfer
  vspi->beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE1));
  vspi->transfer(SDATAC);  
  vspi->transfer(opcode1);  
  vspi->transfer(0b00000000); //writeing one register
  vspi->transfer(value);
  vspi->transfer(RDATAC); 
  vspi->endTransaction();
  digitalWrite(VSPI_SS, HIGH); //pull ss high to signify end of data transfer
  delay(0.001);
  
}

void ADSrreg (char adress){
  char opcode1 = RREG + adress;
  vspi->beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE1));
  digitalWrite(VSPI_SS, LOW); //pull SS slow to prep other end for transfer
  
  vspi->transfer(SDATAC);  
  vspi->transfer(opcode1);  
  vspi->transfer(0b00000000); 
  byte pom =  vspi->transfer(0x00);
  digitalWrite(VSPI_SS, HIGH); //pull ss high to signify end of data transfer
  vspi->endTransaction();
  
  Serial.println(pom, BIN);
  delay(0.001);
}

void ADS_pwr_up(){
  delay(40);
  vspi->transfer(0b00000010);
  delay(0.0012);
}
