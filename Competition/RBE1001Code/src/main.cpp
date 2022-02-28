/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// MotorRb              motor         3               
// MotorLb              motor         10              
// Controller1          controller                    
// MotorLf              motor         9               
// MotorRf              motor         5               
// Claw                 motor         4               
// LiftR                motor         11              
// LiftL                motor         20              
// LineTrackerA         line          A               
// LineTrackerB         line          B               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include <iostream>
#include <cmath>
using namespace std;

using namespace vex;

// A global instance of competition
competition Competition;


// define your global instances of motors and other devices here

motor_group   Left(MotorLb, MotorLf);
motor_group   Right(MotorRb, MotorRf);
motor_group   Lift(LiftL, LiftR);

const double wheelDiameter = 10.4; // CM
const double wheelTrack = 25.75;
double circumference = wheelDiameter * M_PI;

void move(double distance) {
  cout << "hi";
  double circumference = wheelDiameter * M_PI;

  Right.spinFor(distance*360/circumference, degrees, false);
  Left.spinFor(distance*360/circumference, degrees);
}

void rotate(double angle) {
  Right.spinFor(fwd, (2*wheelTrack*M_PI*360/circumference)/(360/angle), degrees, 100, rpm, false);
  Left.spinFor(reverse, (2*wheelTrack*M_PI*360/circumference)/(360/angle), degrees, 100, rpm);
  
}

#include "vex.h"
using namespace vex;

const double WHEELTRACK {28.2};
const double WHEELDIAM {10.16};

void drive(double targetDistance, double speed = 600, rotationUnits unit = degrees)
{
  Left.resetRotation();
  Right.resetRotation();
  Left.rotateTo(targetDistance, unit, speed, dps, false);
  Right.rotateTo(targetDistance, unit, speed, dps);
}

void driveDistance(double targetDistance, double speed){
  drive(targetDistance / M_PI / WHEELDIAM * 360, speed);
}

void turn(double targetAngle, double speed = 600)
{
  Left.resetRotation();
  Right.resetRotation();
  Left.rotateTo((targetAngle*WHEELTRACK/WHEELDIAM), degrees, speed, dps, false);
  Right.rotateTo(-(targetAngle*WHEELTRACK/WHEELDIAM), degrees, speed, dps);
}

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


/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

double speed = 20.0; // 15

double DetermineEffort(double actual)
{
    double KP = 0.01; // .35
    double desired = 90;  
    double error = desired - actual;
    double effort = KP * error;
    return effort;

}

void WhiteLine ()
{
    while(true)
    {
      task::sleep(100);
      float rL = LineTrackerB.reflectivity();
      float rR = LineTrackerA.reflectivity(); 
      cout << "A is " << rR << endl;
      cout << "B is " << rL << endl;
    
        if(rR > 12 && rL > 12)
        {
            rotate(90);
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
          Right.spin(fwd, speed, rpm);
          Left.spin(fwd, speed, rpm);
        }
    }
}

void LineTracking ()
{
    while(true)
    {
      task::sleep(100);
      float rL = LineTrackerB.reflectivity();
      float rR = LineTrackerA.reflectivity(); 
      cout << "A is " << rR << endl;
      cout << "B is " << rL << endl;
    
        if(rR < 12 && rL < 12)
        {
            Left.spin(fwd, speed, rpm);
            Right.spin(fwd, speed, rpm);
            WhiteLine();
        }
        else if(rL < 12)
        {
            Left.spin(reverse, speed/2 + DetermineEffort(rL), rpm);
            Right.spin(fwd, speed/2.5 + DetermineEffort(rR), rpm);
        }
        else if(rR < 12)
        {
            Right.spin(reverse, speed/2 + DetermineEffort(rR), rpm);
            Left.spin(fwd, speed/2.5 + DetermineEffort(rL), rpm);
        }
        else
        { 
          Right.spin(fwd, speed, rpm);
          Left.spin(fwd, speed, rpm);
        }
    }
}

// void LineTracking(void) {
//     while(true)
//     {
//       task::sleep(100);
//       float rL = LineTrackerB.reflectivity();
//       float rR = LineTrackerA.reflectivity(); 
//       cout << "A is " << rR << endl;
//       cout << "B is " << rL << endl;
    
//         if(rR < 12 && rL < 12)
//         {
//             MotorLf.spin(fwd, 0, rpm);
//             MotorLb.spin(fwd, 0, rpm);
//             MotorRf.spin(fwd, 0, rpm);
//             MotorRb.spin(fwd, 0, rpm);
//             rotate(-90);
//             break;
//         }
//         else if(rR < 12)
//         {
//             MotorLf.spin(reverse, speed/2 + DetermineEffort(rR), rpm);
//             MotorLb.spin(reverse, speed/2 + DetermineEffort(rR), rpm);
//             MotorRf.spin(fwd, speed/2.5 + DetermineEffort(rL), rpm);
//             MotorRb.spin(fwd, speed/2.5 + DetermineEffort(rL), rpm);
//         }
//         else if(rL < 12)
//         {
//             MotorRf.spin(reverse, speed/2 + DetermineEffort(rL), rpm);
//             MotorRb.spin(reverse, speed/2 + DetermineEffort(rL), rpm);
//             MotorLf.spin(fwd, speed/2.5 + DetermineEffort(rR), rpm);
//             MotorLb.spin(fwd, speed/2.5 + DetermineEffort(rR), rpm);
//         }
//         else
//         { 
//           MotorRf.spin(fwd, speed, rpm);
//           MotorRb.spin(fwd, speed, rpm);
//           MotorLf.spin(fwd, speed, rpm);
//           MotorLb.spin(fwd, speed, rpm);
//         }
//     }
// }








  // while (true)
  // {
  //   printf("Left: %lu\n", LineTrackerL.reflectivity());
  //   printf("Right: %lu\n", LineTrackerR.reflectivity());
  //   task::sleep(100);
  // }


// const double K_P { 5 };
// const double BASE_SPEED { -9};
// const int THRESHOLD { 12 };

//   task::sleep(500);
//   Left.spin(fwd, BASE_SPEED, rpm);
//   Right.spin(fwd), BASE_SPEED, rpm;
//   while(true){
//     /*while (LineTrackerB.reflectivity() < THRESHOLD || LineTrackerA.reflectivity() < THRESHOLD)
//     {*/
//       /*MotorR.spin(forward, LineTrackerR.reflectivity() * K_P + BASE_SPEED, volt);
//       MotorL.spin(forward, LineTrackerL.reflectivity() * K_P + BASE_SPEED, volt);*/
//       MotorLb.spin(fwd,/*LineTrackerB.reflectivity() * K_P + BASE_SPEED*/200, rpm);
//       Right.setVelocity(LineTrackerA.reflectivity() * K_P + BASE_SPEED, rpm);
//       printf("Left: %lu\n", LineTrackerB.reflectivity());
//       printf("Right: %lu\n", LineTrackerA.reflectivity());
//       printf("RPM: %lu\n", long(LineTrackerA.reflectivity() * K_P));
//       task::sleep(50);
//     //}
//   }
//   turn(90, 300);
//   printf("Done");
//   task::sleep(300);

// }
    // while(true)
    // {
    //   task::sleep(100);
    //   float rL = LineTrackerB.reflectivity();
    //   float rR = LineTrackerA.reflectivity(); 
    //   cout << "A is " << rR << endl;
    //   cout << "B is " << rL << endl;
      

    //   if(rR < 12 && rL < 12){
    //     rotate(-90);

    //   }

    //   else if(rR < 12) {
    //     Left.spin(reverse, speed/2 + DetermineEffort(rR), rpm);
    //     Right.spin(fwd, speed/2.5 + DetermineEffort(rL), rpm);
    //   }

    //   else if(rL < 12) {
    //     Right.spin(reverse, speed/2 + DetermineEffort(rL), rpm);
    //     Left.spin(fwd, speed/2.5 + DetermineEffort(rR), rpm);
    //   }
    //   else { 
    //     Right.spin(reverse, speed, rpm);
    //     Left.spin(reverse, speed, rpm);
    //   }
    // }

void autonomous(void) {
  vexcodeInit();
  Lift.spinFor(reverse, 180, degrees);
  LineTracking();
}

void spintoFirst (void) {
  Lift.spinToPosition(180, degrees);
}


void usercontrol(void) {
  // User control code here, inside the loop
  while( true ) {
    // int leftspeed = Controller1.Axis3.position();
    // int rightspeed = Controller1.Axis2.position();
    if (Controller1.ButtonL1.pressing()) {
      Lift.spin(fwd);      
    } 
    else if (Controller1.ButtonL2.pressing()) {
      Lift.spin(reverse);
    } 
    else {
      Lift.stop(hold);
    }
    if (Controller1.ButtonR1.pressing()) {
      Claw.spin(fwd);
    } 
    else if (Controller1.ButtonR2.pressing()) {
      Claw.spin(reverse);
    }
    else {
      Claw.stop(hold);
    }
  
    // Right.spin(fwd, rightspeed*0.75, percent);
    // Left.spin(fwd, leftspeed*0.75, percent);
         
    Left.spin(fwd, (Controller1.Axis3.value() + Controller1.Axis4.value())/2, pct); //(Axis3+Axis4)/2;
    Right.spin(fwd, (Controller1.Axis3.value() - Controller1.Axis4.value())/2, pct);//(Axis3-Axis4)/2;

    (Controller1.ButtonDown.pressed(autonomous));
    (Controller1.ButtonA.pressed(spintoFirst));
  }

}



  

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  //autonomous();
  //Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  
  // Run the pre-autonomous function.
  //pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    cout << "Left is " << LiftL.torque() << endl;
    cout << "Right is " << LiftR.torque() << endl;
    wait(100, msec);
  }
}
