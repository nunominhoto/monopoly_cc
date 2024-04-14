#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 53
#define RST_PIN 49

bool state;

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

  while (!Serial)
    ;

  Serial.println("\nI2c Scanner");

  SPI.begin();        // Init SPI bus
  mfrc522.PCD_Init(); // Init MFRC522 module

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);

  state = false;
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{

  if (mfrc522.PICC_IsNewCardPresent())
  {
    if (mfrc522.PICC_ReadCardSerial())
    {
      Serial.print(F("Card UID:"));
      dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);
      Serial.println();
    }
  }


  delay(300);
}
