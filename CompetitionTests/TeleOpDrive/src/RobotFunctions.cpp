#include "vex.h"
#include <cmath>

bool isLifterAuto = true;
int levelIndex = 0;
bool arrowPressed = false;
Toggler clawToggler = Toggler();

void manualLift ()
{
  if (abs(Controller1.Axis3.position(percent)) > 10 && isLifterAuto)
  {
    Lift.stop();
    Lift.spin(fwd);
    isLifterAuto = false;
  }

  if (!isLifterAuto)
  {
    Lift.setVelocity(Controller1.Axis3.position(percent) / 5, percent);

    if (levelIndex < LIFT_LEVEL_COUNT - 1 && LIFT_HEIGHTS[levelIndex + 1] < Lift.position(degrees))
    {
      levelIndex++;
    }
    else if (levelIndex > 0 && LIFT_HEIGHTS[levelIndex] > Lift.position(degrees))
    {
      levelIndex--;
    }
  }
}

void moveLift ()
{
  if (!arrowPressed)
  {
    if (Controller1.ButtonUp.pressing() && levelIndex < LIFT_LEVEL_COUNT - 1)
    {
      arrowPressed = true;
      if (levelIndex < LIFT_LEVEL_COUNT - 1)
      {
        liftToFloor(++levelIndex);
      }
      else if (!isLifterAuto)
      {
        liftToFloor(levelIndex);
      }
      isLifterAuto = true;
    }
    else if (Controller1.ButtonDown.pressing())
    {
      arrowPressed = true;
      if (!isLifterAuto)
      {
        liftToFloor(levelIndex);
      }
      else if (levelIndex > 0)
      {
        liftToFloor(--levelIndex);
      }
      isLifterAuto = true;
    }
    else if (Controller1.ButtonLeft.pressing())
    {
      arrowPressed = true;
      isLifterAuto = true;
      levelIndex = 1;
      liftToFloor(levelIndex);
    }
  }
  else if (!Controller1.ButtonDown.pressing() && !Controller1.ButtonUp.pressing())
  {
    arrowPressed = false;
  }

  manualLift();
}

void moveClaw ()
{
  if (clawToggler.getValue(Controller1.ButtonR1.pressing()))
  {
    Claw.rotateTo(100, degrees, 600, dps, false);
  }
  else
  {
    Claw.rotateTo(0, degrees, 600, dps, false);
  }
}

void drive ()
{
  const double forward = Controller1.Axis2.position(percent);
  const double turn = Controller1.Axis1.position(percent) / 3;

  Left.setVelocity(forward + turn, percent);
  Right.setVelocity(forward - turn, percent);
}