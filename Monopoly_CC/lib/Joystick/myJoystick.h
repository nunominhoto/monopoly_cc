#include <Arduino.h>

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


bool JoyNewPosition(float vx, float vy, float vxLast, float vyLast, float minDiff);

JoyPosition GetJoyPosition(float vx, float vy);