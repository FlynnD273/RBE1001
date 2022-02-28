// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// VisionSensor         vision        17              
// MotorR               motor         1               
// MotorL               motor         10              
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// visionSensor         vision        17              
// MotorR               motor         1               
// MotorL               motor         10              
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// visionSensor         vision        17              
// motorR               motor         1               
// MotorL               motor         10              
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// visionSensor         vision        17              
// motorR               motor         1               
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// visionSensor         vision        17              
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// vision               vision        17              
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Vision               vision        17              
// ---- END VEXCODE CONFIGURED DEVICES ----
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\zakap                                            */
/*    Created:      Wed Feb 09 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Vision17             vision        17              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include <cmath>

using namespace vex;

const double K_PR = 0.3;
const double K_PD = 1;
const double STANDOFF_DISTANCE = 40;
const double BALL_WIDTH = 5;
const double DEG_PER_PIX = 0.2;
const double RAD_TO_DEG = 180 / M_PI;
const int CAM_WIDTH = 320;
const int CAM_HEIGHT = 210;
const double TARGET_BALL_WIDTH = atan(BALL_WIDTH / 2 / STANDOFF_DISTANCE) * RAD_TO_DEG / DEG_PER_PIX * 2;

bool tryDetectObject(vex::vision::object& detectedObj)
{
  //takes a snapshot and searches for sig_s1
  //you’ll want to use the signature that you defined above
  VisionSensor.takeSnapshot(VisionSensor__GREEN_BALL);
  detectedObj = VisionSensor.largestObject;
  //print the coordinates of the center of the object
  //printf stands for ’print formatted’ and the %d tells it to print
  //in integer format. The syntax can be found in online tutorials.
  if (VisionSensor.objectCount > 0)
  {
    return true;
  }

  return false;
}

int main() {
  MotorR.spin(forward);
  MotorL.spin(forward);

  vexcodeInit();
  while (true)
  {
    vex::vision::object obj;
    if (tryDetectObject(obj) && obj.width > 4 && obj.height > 4)
    {
      const double rotationPower = (obj.centerX - CAM_WIDTH / 2) * K_PR;
      const double drivePower = (TARGET_BALL_WIDTH - obj.width) * K_PD;
      MotorL.setVelocity(rotationPower + drivePower, rpm);
      MotorR.setVelocity(-rotationPower + drivePower, rpm);
      printf("x: %d, y %d, w: %d, h: %d\n", obj.centerX, obj.centerY, obj.width, obj.height);
    }
    else
    {
      MotorL.setVelocity(0, rpm);
      MotorR.setVelocity(0, rpm);
    }
    wait(50, msec);
  }
}