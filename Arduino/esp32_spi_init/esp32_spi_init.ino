void setup() {
 Serial.begin(115200);
}

void loop() {
 Serial.println(MOSI);//23
 Serial.println(MISO);//19
 Serial.println(SCK);//18
 Serial.println(SS);//5
 delay(500);
}
