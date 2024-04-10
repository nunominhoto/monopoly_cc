#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

bool state;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // put your setup code here, to run once:

  

  Wire.begin();

  Serial.begin(9600);

  while (!Serial);
  Serial.println("\nI2c Scanner");


  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Hello, World!");

  state = false;
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  byte error, address;
  int nDevices;

  Serial.println("Scanning...");


  digitalWrite(LED_BUILTIN, state);
  state = !state;
  delay(300); 
}
