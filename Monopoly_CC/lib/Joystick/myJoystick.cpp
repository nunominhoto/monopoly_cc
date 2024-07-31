#include "myJoystick.h"


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
