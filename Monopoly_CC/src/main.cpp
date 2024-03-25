#include <Arduino.h>

bool state;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  state = false;
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED_BUILTIN, state);
  state = !state;
  delay(2000); 
}
