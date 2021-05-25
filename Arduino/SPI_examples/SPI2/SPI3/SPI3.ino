#include "SPI.h"
char buff[]="Hello Slave\n";

void setup() {
 SPI.begin();
}

void loop() {
 for(int i=0; i<sizeof buff; i++)
 {
  SPI.transfer(buff[i]);
 }
 delay(1000);  
}
