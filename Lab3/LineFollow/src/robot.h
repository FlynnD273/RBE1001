#include "vex.h"
using namespace vex;

const double WHEELTRACK {28.2};
const double WHEELDIAM {10.16};

void drive(double targetDistance, double speed = 600, rotationUnits unit = degrees)
{
  MotorL.resetRotation();
  MotorR.resetRotation();
  MotorL.rotateTo(targetDistance, unit, speed, dps, false);
  MotorR.rotateTo(targetDistance, unit, speed, dps);
}

void driveDistance(double targetDistance, double speed){
  drive(targetDistance / M_PI / WHEELDIAM * 360, speed);
}

void turn(double targetAngle, double speed = 600)
{
  MotorL.resetRotation();
  MotorR.resetRotation();
  MotorL.rotateTo((targetAngle*WHEELTRACK/WHEELDIAM), degrees, speed, dps, false);
  MotorR.rotateTo(-(targetAngle*WHEELTRACK/WHEELDIAM), degrees, speed, dps);
}