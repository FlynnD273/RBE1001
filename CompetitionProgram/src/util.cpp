#include "vex.h"
#include "cmath"
using namespace vex;

const double K_PR = 0.3;
const double K_PD = 1;
const double DEG_PER_PIX = 0.2;
const double RAD_TO_DEG = 180 / M_PI;
const int CAM_WIDTH = 320;
const int CAM_HEIGHT = 210;

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

void driveRotations(double rotationDegrees, double speed = 600, rotationUnits unit = degrees)
{
  Left.resetRotation();
  Right.resetRotation();
  Right.spin(fwd);
  Left.spin(fwd);
  Left.rotateTo(rotationDegrees, unit, speed, dps, false);
  Right.rotateTo(rotationDegrees, unit, speed, dps);
}

void driveDistance(double targetDistance, double speed = 600)
{
  driveRotations(targetDistance / M_PI / WHEEL_DIAM * 360, speed);
}

void turn(double targetAngle, double speed = 600)
{
  Left.resetRotation();
  Right.resetRotation();
  Left.rotateTo((targetAngle*WHEEL_TRACK/WHEEL_DIAM), degrees, speed, dps, false);
  Right.rotateTo(-(targetAngle*WHEEL_TRACK/WHEEL_DIAM), degrees, speed, dps);
}

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
  Claw.rotateTo(85, degrees, 600, dps, false);
}

void closeClawSlow()
{
  Claw.rotateTo(100,degrees,90,dps,false);
}

double speed = 20;

double DetermineEffort(double actual) 
 {

    double KP = 0.02; // .35
    double desired = 90;  
    double error = desired - actual;
    double effort = KP * error;
    return effort;
}

void BlackLineTracking ()
{ 
    Left.spin(fwd);
    Right.spin(fwd);
    while(true)
    {
      task::sleep(100);
      float rL = LineTrackerB.reflectivity();
      float rR = LineTrackerA.reflectivity(); 
      //cout << "A is " << rR << endl;
      //cout << "B is " << rL << endl;
    
        const double K_P { 2 };
        const double BASE_SPEED { 10 };
        const int THRESHOLD { 12 };
        Left.setVelocity(rL * K_P + BASE_SPEED, rpm);
        Right.setVelocity(rR * K_P + BASE_SPEED, rpm);
        if(rR < THRESHOLD && rL < THRESHOLD)
          break;
    }
    /*while(true)
    {
      task::sleep(100);
       
      float rL = LineTrackerB.reflectivity();
      float rR = LineTrackerA.reflectivity(); 
      //cout << "A is " << rR << endl;
      //cout << "B is " << rL << endl;
    
        if(rR > 12 && rL > 12)
        {
            Right.spin(fwd, speed, rpm);
            Left.spin(fwd, speed, rpm);
        }
        else if(rL > 12)
        {
            Left.spin(reverse, speed/2 + DetermineEffort(rL), rpm);
            Right.spin(fwd, speed/2.5 + DetermineEffort(rR), rpm);
        }
        else if(rR > 12)
        {
            Right.spin(reverse, speed/2 + DetermineEffort(rR), rpm);
            Left.spin(fwd, speed/2.5 + DetermineEffort(rL), rpm);
        }
        else
        { 
          Right.stop();
          Left.stop();
          break;
        }
    }*/
}

void WhiteLineTracking (bool isFwd)
{ 
    Left.spin(fwd);
    Right.spin(fwd);
    if(!isFwd)
    {
      Left.spin(reverse);
      Right.spin(reverse);
    }
    while(true)
    {
      task::sleep(100);
      float rL = LineTrackerB.reflectivity();
      float rR = LineTrackerA.reflectivity(); 
      if(!isFwd)
      {
        rR = LineTrackerB.reflectivity();
        rL = LineTrackerA.reflectivity(); 
      }
      //cout << "A is " << rR << endl;
      //cout << "B is " << rL << endl;
    
        const double K_P { 2.6 };
        const double BASE_SPEED { 37 };
        const int THRESHOLD { 12 };
        Left.setVelocity(-rL * K_P + BASE_SPEED, rpm);
        Right.setVelocity(-rR * K_P + BASE_SPEED, rpm);
        /*if(rR < 12 && rL < 12)
        {
            Left.spin(fwd, speed, rpm);
            Right.spin(fwd, speed, rpm);
        }
        else if(rR < 12)
        {
            Left.spin(reverse, speed/1.5 + DetermineEffort(rL), rpm);
            //Right.spin(fwd, speed/3 + DetermineEffort(rR), rpm);
        }
        else if(rL < 12)
        {
            Right.spin(reverse, speed/1.5 + DetermineEffort(rR), rpm);
            //Left.spin(fwd, speed/3 + DetermineEffort(rL), rpm);
        }
        else
        { 
          Right.stop();
          Left.stop();
          break;
        }*/
        if(rR > THRESHOLD && rL > THRESHOLD)
          break;
    }
}

void DriveUntilWhite(bool isForwards)
{
  float rL = LineTrackerB.reflectivity();
  float rR = LineTrackerA.reflectivity(); 
  if(!isForwards)
  {
    while (rR < 12 && rL < 12)
  {
    rL = LineTrackerB.reflectivity();
    rR = LineTrackerA.reflectivity(); 
    Right.spin(reverse, speed, rpm);
    Left.spin(reverse, speed, rpm);
  }
  }else{
  while (rR < 12 && rL < 12)
  {
    rL = LineTrackerB.reflectivity();
    rR = LineTrackerA.reflectivity(); 
    Right.spin(fwd, speed, rpm);
    Left.spin(fwd, speed, rpm);
  }
  }
  Right.stop();
  Left.stop();
}

void turnToLine(int speed = 100)
{ 
  int rL = LineTrackerB.reflectivity();
  int rR = LineTrackerA.reflectivity(); 
  if(speed > 0)
  {
    printf("in if statemernt\n");
    printf("left line sensor: %i\n", rL);
    task::sleep(420);
    Left.spin(forward, speed, dps);
    Right.spin(reverse, speed, dps);
    do
    {
      rL = LineTrackerB.reflectivity();
      printf("Reached while loop\n");
      printf("linesensor value %i\n", rL);
      task::sleep(10);
    } while(rL < 10);
  } 
  else 
  {
    printf("in else statemernt\n");
    Left.spin(reverse, -speed, dps);
    Right.spin(forward, -speed, dps);
    while(rR < 10) 
    {
      printf("%i\n", rR);
      rR = LineTrackerA.reflectivity(); 
      task::sleep(100);
    }
  }
  printf("reached end\n");
  Right.stop();
  Left.stop();
}