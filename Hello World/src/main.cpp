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
#define CMTOIN 2.54;
const double WHEELTRACK {28};
const double WHEELDIAM {10.16};

void drive(double targetDistance, double speed){
  MotorL.rotateTo((targetDistance / M_PI / WHEELDIAM * 360 * 5), degrees, speed, dps, false);
  MotorR.rotateTo((targetDistance / M_PI / WHEELDIAM * 360 * 5), degrees, speed, dps);
  MotorL.resetRotation();
  MotorR.resetRotation();
}

void turn(double targetAngle, double speed){
  MotorL.rotateTo((targetAngle*WHEELTRACK/WHEELDIAM*5), degrees, speed, dps, false);
  MotorR.rotateTo(-(targetAngle*WHEELTRACK/WHEELDIAM*5), degrees, speed, dps);
  MotorL.resetRotation();
  MotorR.resetRotation();
}

void driveSquare(double squareDistance, double speed){
  for(int i = 0; i<4; i++)
  {
  drive(squareDistance, speed);
  turn(90, speed);
  }

}


int main() {
  
  vexcodeInit();
  
  task::sleep(250);
  
  //int wheelTrack = 28;
  //double cmToIn = 2.54;
  //double wheelDiam = 10.16;
  double targetDistance = 50;
  double targetAngle = 360;
  double squareDistance = 20 * CMTOIN;
  double squareAngle = 90;
  double speed = 600;
  //MotorL.rotateTo((targetDistance/M_PI/wheelDiam*360*5), degrees, 360, dps, false);
  //MotorR.rotateTo((targetDistance/M_PI/wheelDiam*360*5), degrees, 360, dps);
  //Brain.Screen.print("hi");
  //MotorL.resetRotation();
  //MotorR.resetRotation();
  //MotorL.rotateTo((targetAngle*wheelTrack/wheelDiam*5), degrees, 360, dps, false);
  //MotorR.rotateTo(-(targetAngle*wheelTrack/wheelDiam*5), degrees, 360, dps);
driveSquare(squareDistance, speed);
  //make a square
  Controller1.ButtonA.pressed();
  

  





}
