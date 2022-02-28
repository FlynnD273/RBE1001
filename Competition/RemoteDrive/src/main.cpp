/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Flynn                                            */
/*    Created:      Mon Feb 21 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// MotorLiftL           motor         1               
// MotorLiftR           motor         2               
// MotorGrabber         motor         7               
// MotorDriveBL         motor         8               
// MotorDriveBR         motor         9               
// MotorDriveFL         motor         10              
// MotorDriveFR         motor         11              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

int main() 
{
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  MotorDriveBL.spin(forward);
  MotorDriveBR.spin(forward);
  MotorDriveFR.spin(forward);
  MotorDriveFL.spin(forward);
  MotorLiftL.spin(forward);
  MotorLiftR.spin(forward);


  while (true)
  {
    int forward = Controller1.Axis3.position(percent);
    int turn = Controller1.Axis4.position(percent) / 2;
    MotorLiftL.setVelocity(Controller1.Axis2.position(percent) / 5, percent);
    MotorLiftR.setVelocity(Controller1.Axis2.position(percent) / 5, percent);
    
    MotorDriveBL.setVelocity(-forward + turn, percent);
    MotorDriveFL.setVelocity(forward + turn, percent);

    MotorDriveBR.setVelocity(-forward - turn, percent);
    MotorDriveFR.setVelocity(forward - turn, percent);
  }
}
