/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\zakap                                            */
/*    Created:      Wed Jan 19 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// MotorL               motor         1               
// MotorR               motor         10              
// MotorArm             motor         7               
// Controller1          controller                    
// RangeFinderE         sonar         E, F            
// BumperC              bumper        C               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
using namespace vex;

#include <iostream>
using namespace std;

#include <cmath>

int main() {
  
  vexcodeInit();
  
  task::sleep(250);
  
  int wheelTrack = 28;
  double wheelDiam = 10.16;
  double targetDistance = 50;
  double targetAngle = 90;
  //MotorL.rotateTo((targetDistance/M_PI/wheelDiam*360*5), degrees, 360, dps, false);
  //MotorR.rotateTo((targetDistance/M_PI/wheelDiam*360*5), degrees, 360, dps);
  MotorL.resetRotation();
  MotorR.resetRotation();
  MotorL.rotateTo((targetAngle*wheelTrack/wheelDiam*5), degrees, 360, dps, false);
  MotorR.rotateTo(-(targetAngle*wheelTrack/wheelDiam*5), degrees, 360, dps);



}
