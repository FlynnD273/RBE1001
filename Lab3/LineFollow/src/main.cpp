/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Flynn                                            */
/*    Created:      Wed Feb 02 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LineTrackerL         line          H               
// LineTrackerR         line          G               
// MotorL               motor         10              
// MotorR               motor         1               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "robot.h"

using namespace vex;

const double K_P { 0.1 };
const double BASE_SPEED { -0.4 };
const int THRESHOLD { 25 };

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  // while (true)
  // {
  //   printf("Left: %lu\n", LineTrackerL.reflectivity());
  //   printf("Right: %lu\n", LineTrackerR.reflectivity());
  //   task::sleep(100);
  // }
  task::sleep(500);
  while (LineTrackerL.reflectivity() > THRESHOLD || LineTrackerR.reflectivity() > THRESHOLD)
  {
    MotorR.spin(forward, LineTrackerR.reflectivity() * K_P + BASE_SPEED, volt);
    MotorL.spin(forward, LineTrackerL.reflectivity() * K_P + BASE_SPEED, volt);
    printf("Left: %lu\n", LineTrackerL.reflectivity());
    printf("Right: %lu\n", LineTrackerR.reflectivity());
    task::sleep(50);
  }
  turn(90, 300);
  printf("Done");
}
