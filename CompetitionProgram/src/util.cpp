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

void driveDegrees(double rotationDegrees, double speed = 600, rotationUnits unit = degrees)
{
  Left.resetRotation();
  Right.resetRotation();
  Left.rotateTo(rotationDegrees, unit, speed, dps, false);
  Right.rotateTo(rotationDegrees, unit, speed, dps);
}

void driveDistance(double targetDistance, double speed = 600)
{
  driveDegrees(targetDistance / M_PI / WHEEL_DIAM * 360, speed);
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