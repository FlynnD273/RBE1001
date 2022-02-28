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

void openClawL ()
{
  Claw.rotateTo(70, degrees, 600, dps, false);
}

void closeClaw ()
{
  Claw.rotateTo(100, degrees, 600, dps, false);
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
    while(true)
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
    }
}

void WhiteLineTracking ()
{ 
    while(true)
    {
      task::sleep(100);
      float rL = LineTrackerB.reflectivity();
      float rR = LineTrackerA.reflectivity(); 
      //cout << "A is " << rR << endl;
      //cout << "B is " << rL << endl;
    
        if(rR < 12 && rL < 12)
        {
            Left.spin(fwd, speed, rpm);
            Right.spin(fwd, speed, rpm);
        }
        else if(rR < 12)
        {
            Left.spin(reverse, speed/2 + DetermineEffort(rL), rpm);
            Right.spin(fwd, speed/2.5 + DetermineEffort(rR), rpm);
        }
        else if(rL < 12)
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
    }
}

void RampToDorm()
{ 
  driveDistance(75, 250);
  openClawL();
        
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

bool tryDetectObject(vex::vision::object& detectedObj, signature sig)
{
  //takes a snapshot and searches for sig_s1
  //you’ll want to use the signature that you defined above
  Vision15.takeSnapshot(sig);
  detectedObj = Vision15.largestObject;
  //print the coordinates of the center of the object
  //printf stands for ’print formatted’ and the %d tells it to print
  //in integer format. The syntax can be found in online tutorials.
  if (Vision15.objectCount > 0)
  {
    return true;
  }

  return false;
}


trackColorState trackColor(signature sig, double width, double distance, double horizontalThreshold, double sizeThreshold)
{
  const double targetWidth = atan(width / 2 / distance) * RAD_TO_DEG / DEG_PER_PIX * 2;
  vex::vision::object obj;
  if (tryDetectObject(obj, sig) && obj.width > 2 && obj.height > 2)
  {
    const double rotationPower = (obj.centerX - CAM_WIDTH / 2) * K_PR;
    const double drivePower = (targetWidth - obj.width) * K_PD;
    Left.setVelocity(rotationPower + drivePower, rpm);
    Right.setVelocity(-rotationPower + drivePower, rpm);

    if (abs(obj.centerX - CAM_WIDTH / 2) < horizontalThreshold / 2 && abs(targetWidth - obj.width) < sizeThreshold)
    {
      return trackColorState::SUCCESSFUL;
    }
  }
  else
  {
    Left.setVelocity(0, rpm);
    Right.setVelocity(0, rpm);
    return trackColorState::LOST;
  }

  return trackColorState::PENDING;
}