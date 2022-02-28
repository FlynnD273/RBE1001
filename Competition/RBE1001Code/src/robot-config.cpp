#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor MotorRb = motor(PORT3, ratio18_1, true);
motor MotorLb = motor(PORT10, ratio18_1, false);
controller Controller1 = controller(primary);
motor MotorLf = motor(PORT9, ratio18_1, false);
motor MotorRf = motor(PORT5, ratio18_1, true);
motor Claw = motor(PORT4, ratio18_1, false);
motor LiftR = motor(PORT11, ratio18_1, true);
motor LiftL = motor(PORT20, ratio18_1, false);
line LineTrackerA = line(Brain.ThreeWirePort.A);
line LineTrackerB = line(Brain.ThreeWirePort.B);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}