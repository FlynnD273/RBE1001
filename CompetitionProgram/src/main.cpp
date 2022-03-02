// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LineTrackerA         line          A               
// LineTrackerB         line          F               
// Claw                 motor         4               
// Left                 motor_group   9, 10           
// Right                motor_group   5, 3            
// Lift                 motor_group   11, 20          
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LineTrackerA         line          A               
// LineTrackerB         line          F               
// Claw                 motor         4               
// Vision15             vision        15              
// Left                 motor_group   9, 10           
// Right                motor_group   5, 3            
// Lift                 motor_group   11, 20          
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LineTrackerA         line          A               
// LineTrackerB         line          F               
// Claw                 motor         4               
// Vision15             vision        15              
// Left                 motor_group   9, 10           
// Right                motor_group   5, 3            
// Lift                 motor_group   11, 20          
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LineTrackerA         line          A               
// LineTrackerB         line          E               
// Claw                 motor         4               
// Vision15             vision        15              
// Left                 motor_group   9, 10           
// Right                motor_group   5, 3            
// Lift                 motor_group   11, 20          
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LineTrackerA         line          A               
// LineTrackerB         line          E               
// Claw                 motor         4               
// Vision15             vision        15              
// Left                 motor_group   9, 10           
// Right                motor_group   5, 3            
// Lift                 motor_group   11, 20          
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LineTrackerA         line          A               
// LineTrackerE         line          E               
// Claw                 motor         4               
// Vision15             vision        15              
// Left                 motor_group   9, 10           
// Right                motor_group   5, 3            
// Lift                 motor_group   11, 20          
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LineTrackerA         line          A               
// LineTrackerB         line          B               
// Claw                 motor         4               
// Vision15             vision        15              
// Left                 motor_group   9, 10           
// Right                motor_group   5, 3            
// Lift                 motor_group   11, 20          
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include <iostream>
#include <cmath>
using namespace std;


using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Lift.setStopping(hold);
  Claw.setStopping(brake);
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
  
  //Close claw and lift before driving up ramp
  closeClaw();
  task::sleep(800);
  liftToFloor(2);
  //Drive up ramp
  BlackLineTracking();
  //Drive up to dorm, open claw
  driveDistance(73, 250);
  Claw.stop();
  openClawSmall();
  task::sleep(1000);
  //Move backwards until we reach the white line
  DriveUntilWhite(false);
  openClaw();
  
  //Move forwards to center the pivot, rotate onto the line
  driveDistance(11.8,150);
  Lift.rotateTo(400, degrees, 500, dps, false);
  turnToLine(70);
  //Drive until the intersection
  WhiteLineTracking(true);
  //Center the pivot and turn
  driveDistance(15,130);
  turn(30, 130);
  turnToLine(70);
  //Open claw and drive forwards
  openClaw();
  task::sleep(100);
  // driveDistance(13, 90);
  task::sleep(1000);
  //Close claw and drive backwards
  closeClawSlow();
  task::sleep(2000);
  // DriveUntilWhite(false);
  // driveDistance(-13, 90);
  //Center the pivot and turn onto the line
  driveDistance(-8,150);
  liftToFloor(1);
  task::sleep(500);
  driveDistance(8,150);
  driveDistance(-3,150);
  turn(30,130);
  turnToLine(70);
  turn(-5,130);
  //Drive up to the dorm and turn to face it
  driveDistance(84,100);
  liftToFloor(3);
  turn(40,100);
  driveDistance(-6,80);
  turn(50, 100);
  driveDistance(14,80);
  openClaw();
  //Drive backwards, orient the pivot, and move towards the line
  DriveUntilWhite(false);
  driveDistance(11.8, 150);
  turnToLine(-70);
  WhiteLineTracking(true);
  //Turns and drives
  liftToFloor(2);
  openClawSmall();
  turn(-100,130);
  driveDistance(-125, 500);
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  Left.spin(fwd);
  Right.spin(fwd);
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................
    drive();
    moveLift();
    moveClaw();
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
