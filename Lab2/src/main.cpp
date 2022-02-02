/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\zakap                                            */
/*    Created:      Wed Jan 26 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// MotorL               motor         10              
// MotorR               motor         1               
// RangeFinderE         sonar         E, F            
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

int main() {
double voltage = 10;
  double maxSpeed = 0;
  MotorL.spin(forward, voltage, volt);
  MotorR.spin(forward, voltage, volt);
  Brain.Timer.reset();
  while(true)
  {
    if(MotorL.velocity(rpm) > maxSpeed)
      maxSpeed = MotorL.velocity(rpm);
    printf("\n%f seconds, %f mm, %f RPM, Max %f RMP", Brain.Timer.value(), RangeFinderE.distance(mm), MotorL.velocity(rpm), maxSpeed);
    if(RangeFinderE.distance(mm) < 1000 && RangeFinderE.distance(mm) > 50)
      break;
    task::sleep(100);
  }
  MotorL.stop();
  MotorR.stop();
}
