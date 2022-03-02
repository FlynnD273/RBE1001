#include "vex.h"
#include "cmath"
using namespace vex;

bool Toggler::getValue ()
{
  return value;
}

bool Toggler::getValue (bool state)
{
  if (state && !prevState)
  {
    value = !value;
  }

  prevState = state;
  return value;
}

//Drive the robot based on a number of wheel rotations
void driveRotations(double rotationDegrees, double speed = 600, rotationUnits unit = degrees)
{
  Left.resetRotation();
  Right.resetRotation();
  Right.spin(fwd);
  Left.spin(fwd);
  Left.rotateTo(rotationDegrees, unit, speed, dps, false);
  Right.rotateTo(rotationDegrees, unit, speed, dps);
}

//Drive the robot forward by a number of centimeters
void driveDistance(double targetDistance, double speed = 600)
{
  driveRotations(targetDistance / M_PI / WHEEL_DIAM * 360, speed);
}

//Turn the robot a nummber of degrees
void turn(double targetAngle, double speed = 600)
{
  Left.resetRotation();
  Right.resetRotation();
  Left.rotateTo((targetAngle*WHEEL_TRACK/WHEEL_DIAM), degrees, speed, dps, false);
  Right.rotateTo(-(targetAngle*WHEEL_TRACK/WHEEL_DIAM), degrees, speed, dps);
}

//Lift the claw to a specific floor index. Rotations were determined experimentally
void liftToFloor(int index)
{
  if (index >= LIFT_LEVEL_COUNT || index < 0) return;

  Lift.rotateTo(LIFT_HEIGHTS[index], degrees, 500, dps, false);
}

void openClaw ()
{
  Claw.rotateTo(0, degrees, 600, dps, false);
}

void openClawSmall ()
{
  Claw.rotateTo(70, degrees, 600, dps, false);
}

void closeClaw ()
{
  Claw.rotateTo(90, degrees, 600, dps, false);
}

void closeClawSlow ()
{
  Claw.rotateTo(90,degrees,90,dps,false);
}


//Drive forward along a black line (used for the ramp)
void BlackLineTracking ()
{
  const double K_P { 2 };
  const double BASE_SPEED { 10 };
  const int THRESHOLD { 12 };

  Left.spin(fwd);
  Right.spin(fwd);

  while(true)
  {
    float rL = LineTrackerB.reflectivity();
    float rR = LineTrackerA.reflectivity(); 
  
    Left.setVelocity(rL * K_P + BASE_SPEED, rpm);
    Right.setVelocity(rR * K_P + BASE_SPEED, rpm);

    if(rR < THRESHOLD && rL < THRESHOLD)
    {
      break;
    }

    task::sleep(100);
  }
}

//Drive forward along a white line
void WhiteLineTracking ()
{ 
  const double K_P { 2.6 };
  const double BASE_SPEED { 37 };
  const int THRESHOLD { 12 };

  Left.spin(fwd);
  Right.spin(fwd);

  while(true)
  {
    float rL = LineTrackerB.reflectivity();
    float rR = LineTrackerA.reflectivity();

    Left.setVelocity(-rL * K_P + BASE_SPEED, rpm);
    Right.setVelocity(-rR * K_P + BASE_SPEED, rpm);

    if(rR > THRESHOLD && rL > THRESHOLD)
    {
      break;
    }

    task::sleep(100);
  }
}

//Drive backwards until both line sensors see white
void DriveBackwardsUntilWhite ()
{
  double speed = 20;
  float rL = LineTrackerB.reflectivity();
  float rR = LineTrackerA.reflectivity();

  while (rR < 12 && rL < 12)
  {
    rL = LineTrackerB.reflectivity();
    rR = LineTrackerA.reflectivity(); 
    Right.spin(reverse, speed, rpm);
    Left.spin(reverse, speed, rpm);
  }

  Right.stop();
  Left.stop();
}

void turnToLine (int speed = 100)
{ 
  int rL = LineTrackerB.reflectivity();
  int rR = LineTrackerA.reflectivity(); 

  if(speed > 0)
  {
    //Turn clockwise
    task::sleep(420);
    Left.spin(forward, speed, dps);
    Right.spin(reverse, speed, dps);
    do
    {
      rL = LineTrackerB.reflectivity();
      task::sleep(10);
    } 
    while(rL < 10);
  } 
  else 
  {
    //Turn counterclockwise
    task::sleep(420);
    Left.spin(reverse, -speed, dps);
    Right.spin(forward, -speed, dps);
    do
    {
      rR = LineTrackerA.reflectivity(); 
      task::sleep(10);
    }
    while(rR < 10);
  }

  Right.stop();
  Left.stop();
}