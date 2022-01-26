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
const double WHEELTRACK {28.2};
const double WHEELDIAM {10.16};

void drive(double targetDistance, double speed = 600, rotationUnits unit = degrees){
  MotorL.rotateTo(targetDistance, unit, speed, dps, false);
  MotorR.rotateTo(targetDistance, unit, speed, dps);
  MotorL.resetRotation();
  MotorR.resetRotation();
}

void driveDistance(double targetDistance, double speed){
  drive(targetDistance / M_PI / WHEELDIAM * 360 * 5, speed);
}

void turn(double targetAngle, double speed = 600){
  MotorL.rotateTo((targetAngle*WHEELTRACK/WHEELDIAM*5), degrees, speed, dps, false);
  MotorR.rotateTo(-(targetAngle*WHEELTRACK/WHEELDIAM*5), degrees, speed, dps);
  MotorL.resetRotation();
  MotorR.resetRotation();
}

void driveSquare(double squareDistance, double speed){
  for(int i = 0; i<4; i++)
  {
  driveDistance(squareDistance, speed);
  turn(90, speed);
  }

}
void driveStar(double squareDistance, double speed){
  for(int i = 0; i<5; i++)
  {
  driveDistance(squareDistance, speed);
  turn(144, speed);
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
//driveSquare(squareDistance, speed);
  //make a square
  /*int degrees = 0;
  bool wasPressed = false;
  while(true){
    bool isPressed = Controller1.ButtonY.pressing();
    if(isPressed){
      MotorL.spin(fwd);           
     MotorR.spin(fwd);
    }else{
      MotorR.stop();
      MotorL.stop();
    }
    if(wasPressed && !isPressed)
    {
        Brain.Screen.print(MotorL.position(turns));
        Brain.Screen.print (" ");
        MotorL.resetRotation();
    }
    wasPressed = isPressed;
    task::sleep(50);
    
  }*/
  while(true){
    if(Controller1.ButtonA.pressing()){
  drive(9.34, 600, turns);
  turn(90);
  drive(-2,600, turns);
  turn(-185);
  drive(10.5, 600, turns);
  turn(-81);
  drive(-6.58, 600, turns);
  turn(73);
  drive(-2,600,turns);
  turn(15);
  drive(-2,600,turns);
  }
  }

  /*while(true){
    if(Controller1.ButtonA.pressing())
  for(int c = 0; c < 6; c++){
      driveSquare(squareDistance, speed);
  }
  if(Controller1.ButtonB.pressing())
  for(int c = 0; c < 5; c++){
      driveStar(squareDistance, speed);
  }
  }*/

  

  





}