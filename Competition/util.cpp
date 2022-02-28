#include "vex.h"
#include "cmath"
using namespace vex;

const double K_PR = 0.3;
const double K_PD = 1;
const double DEG_PER_PIX = 0.2;
const double RAD_TO_DEG = 180 / M_PI;
const int CAM_WIDTH = 320;
const int CAM_HEIGHT = 210;

void drive(double targetDistance, double speed = 600, rotationUnits unit = degrees)
{
  MotorsL.resetRotation();
  MotorsR.resetRotation();
  MotorsL.rotateTo(targetDistance, unit, speed, dps, false);
  MotorsR.rotateTo(targetDistance, unit, speed, dps);
}

void driveDistance(double targetDistance, double speed){
  drive(targetDistance / M_PI / WHEELDIAM * 360, speed);
}

void turn(double targetAngle, double speed = 600)
{
  MotorsL.resetRotation();
  MotorsR.resetRotation();
  MotorsL.rotateTo((targetAngle*WHEELTRACK/WHEELDIAM), degrees, speed, dps, false);
  MotorsR.rotateTo(-(targetAngle*WHEELTRACK/WHEELDIAM), degrees, speed, dps);
}

void liftToFloor(int index)
{
  if (index >= LIFT_LEVELS || index < 0) return;

  MotorsLifter.setPosition(LIFT_HEIGHTS[index], degrees);
}

bool tryDetectObject(vex::vision::object& detectedObj, signature sig)
{
  //takes a snapshot and searches for sig_s1
  //you’ll want to use the signature that you defined above
  VisionF.takeSnapshot(sig);
  detectedObj = VisionF.largestObject;
  //print the coordinates of the center of the object
  //printf stands for ’print formatted’ and the %d tells it to print
  //in integer format. The syntax can be found in online tutorials.
  if (VisionF.objectCount > 0)
  {
    return true;
  }

  return false;
}

enum trackColorState {SUCCESSFUL, PENDING, LOST};

trackColorState trackColor(signature sig, double width, double distance, double horizontalThreshold, double sizeThreshold)
{
  const double targetWidth = atan(width / 2 / distance) * RAD_TO_DEG / DEG_PER_PIX * 2;
  vex::vision::object obj;
  if (tryDetectObject(obj, sig) && obj.width > 2 && obj.height > 2)
  {
    const double rotationPower = (obj.centerX - CAM_WIDTH / 2) * K_PR;
    const double drivePower = (targetWidth - obj.width) * K_PD;
    MotorsL.setVelocity(rotationPower + drivePower, rpm);
    MotorsR.setVelocity(-rotationPower + drivePower, rpm);

    if (abs(obj.centerX - CAM_WIDTH / 2) < horizontalThreshold / 2 && abs(targetWidth - obj.width) < sizeThreshold)
    {
      return trackColorState::SUCCESSFUL;
    }
  }
  else
  {
    MotorsL.setVelocity(0, rpm);
    MotorsR.setVelocity(0, rpm);
    return trackColorState::LOST;
  }

  return trackColorState::PENDING;
}