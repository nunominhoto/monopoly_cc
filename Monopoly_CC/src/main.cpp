#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Keypad.h>

#define SS_PIN 53
#define RST_PIN 49

#define VRx A0
#define VRy A1 
#define AnalogButton 22

bool state;
float vX, vY;
int B;

const byte ROWS = 4; 
const byte COLS = 4; 

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {22, 24, 26, 28}; 
byte colPins[COLS] = {23, 25, 27, 29}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

LiquidCrystal_I2C lcd(0x27, 16, 2); // Create LCD instance
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance

/**
 * Helper routine to dump a byte array as hex values to Serial.
 */
void dump_byte_array(byte *buffer, byte bufferSize)
{
  for (byte i = 0; i < bufferSize; i++)
  {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}

void setup()
{
  // put your setup code here, to run once:

  Wire.begin();

  Serial.begin(9600);

  SPI.begin();        // Init SPI bus
  mfrc522.PCD_Init(); // Init MFRC522 module

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);

  state = false;
  //Output Input definition
  pinMode(LED_BUILTIN, OUTPUT);
  // pinMode(VRx, INPUT);
  // pinMode(VRy, INPUT);
  pinMode(AnalogButton, INPUT);

}

void loop()
{

  // vX = analogRead(VRx);
  // vY = analogRead(VRy);
  // B = digitalRead(AnalogButton);

  // Serial.println(" Vx | Vy | B ");
  // Serial.print(" ");
  // Serial.print(vX);
  // Serial.print(" | ");
  // Serial.print(vY);
  // Serial.print(" | ");
  // Serial.print(B);

  // Serial.println("");

  
  char customKey = customKeypad.getKey();
  
  if (customKey){
    Serial.println(customKey);
  }

  if (mfrc522.PICC_IsNewCardPresent())
  {
    if (mfrc522.PICC_ReadCardSerial())
    {
      Serial.print(F("Card UID:"));
      dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);
      Serial.println();
    }
  }

}
