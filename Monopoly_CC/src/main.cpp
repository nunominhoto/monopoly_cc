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
float vXLast = 0, vYLast = 0;
int B;

const byte ROWS = 4;
const byte COLS = 4;

enum JoyPosition
{
  Left,
  Up,
  Down,
  Right,
  Center,
};

enum AxisPosition
{
  Mid,
  Max,
  Min,
};

char hexaKeys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

byte rowPins[ROWS] = {22, 24, 26, 28};
byte colPins[COLS] = {23, 25, 27, 29};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

JoyPosition Movement, LastMovement;

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

JoyPosition GetJoyPosition(float vx, float vy)
{
  AxisPosition vxPos, vyPos;

#pragma region GetAxisPositions

  if (vx < 250)
  {
    vxPos = Min;
  }
  else if (vx > 750)
  {
    vxPos = Max;
  }
  else if (vx > 250 && vx < 750)
  {
    vxPos = Mid;
  }

  if (vy < 250)
  {
    vyPos = Min;
  }
  else if (vy > 750)
  {
    vyPos = Max;
  }
  else if (vy > 250 && vy < 750)
  {
    vyPos = Mid;
  }
#pragma endregion

#pragma region PositionReturn
  if (vxPos == Mid && vyPos == Mid)
    return Center;
  else if (vxPos == Max && vyPos == Mid)
    return Right;
  else if (vxPos == Min && vyPos == Mid)
    return Left;
  else if (vxPos == Mid && vyPos == Max)
    return Down;
  else if (vxPos == Mid && vyPos == Min)
    return Up;
#pragma endregion
}

bool JoyNewPosition(float vx, float vy, float vxLast, float vyLast, float minDiff)
{
  if (abs(vx - vxLast) > minDiff || abs(vy - vyLast) > minDiff)
    return true;
  else
    return false;
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
  // Output Input definition
  pinMode(LED_BUILTIN, OUTPUT);
  // pinMode(VRx, INPUT);
  // pinMode(VRy, INPUT);
  pinMode(AnalogButton, INPUT);
}

void loop()
{

  vX = analogRead(VRx);
  vY = analogRead(VRy);
  B = digitalRead(AnalogButton);

  if (JoyNewPosition(vX, vY, vXLast, vYLast, 50))
  {

    Movement = GetJoyPosition(vX, vY);

    if (Movement != LastMovement)
    {
      Serial.println((JoyPosition)Movement);
    }

    LastMovement = Movement;
    vXLast = vX;
    vYLast = vY;
  }

  // char customKey = customKeypad.getKey();

  // if (customKey){
  //   Serial.println(customKey);
  // }

  // if (mfrc522.PICC_IsNewCardPresent())
  // {
  //   if (mfrc522.PICC_ReadCardSerial())
  //   {
  //     Serial.print(F("Card UID:"));
  //     dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);
  //     Serial.println();
  //   }
  // }
}
