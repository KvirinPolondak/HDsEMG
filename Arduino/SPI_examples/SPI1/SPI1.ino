void setup() {
  pinMode(5, OUTPUT);    // sets the digital pin 13 as output
}

void loop() {
  digitalWrite(5, HIGH); // sets the digital pin 13 on
  delay(1000);            // waits for a second
  digitalWrite(5, LOW);  // sets the digital pin 13 off
  delay(1000);            // waits for a second
}
