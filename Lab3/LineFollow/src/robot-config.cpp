#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
line LineTrackerL = line(Brain.ThreeWirePort.B);
line LineTrackerR = line(Brain.ThreeWirePort.A);
motor MotorLf = motor(PORT9, ratio18_1, false);
motor MotorRf = motor(PORT5, ratio18_1, true);
motor MotorRb = motor(PORT3, ratio18_1, true);
motor MotorLb = motor(PORT10, ratio18_1, false);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}