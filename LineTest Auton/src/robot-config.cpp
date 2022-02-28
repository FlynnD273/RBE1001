#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
line LineTrackerA = line(Brain.ThreeWirePort.A);
line LineTrackerB = line(Brain.ThreeWirePort.B);
motor LB = motor(PORT9, ratio18_1, false);
motor LF = motor(PORT10, ratio18_1, false);
motor RF = motor(PORT5, ratio18_1, true);
motor RB = motor(PORT3, ratio18_1, true);
motor LiftR = motor(PORT11, ratio18_1, true);
motor LiftL = motor(PORT20, ratio18_1, false);
motor Claw = motor(PORT4, ratio18_1, false);
/*vex-vision-config:begin*/
vision Vision15 = vision (PORT15, 50);
/*vex-vision-config:end*/
sonar RangeFinderE = sonar(Brain.ThreeWirePort.E);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}