#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
line LineTrackerA = line(Brain.ThreeWirePort.A);
line LineTrackerB = line(Brain.ThreeWirePort.F);
motor Claw = motor(PORT4, ratio18_1, true);
motor LeftMotorA = motor(PORT9, ratio18_1, false);
motor LeftMotorB = motor(PORT10, ratio18_1, false);
motor_group Left = motor_group(LeftMotorA, LeftMotorB);
motor RightMotorA = motor(PORT5, ratio18_1, true);
motor RightMotorB = motor(PORT3, ratio18_1, true);
motor_group Right = motor_group(RightMotorA, RightMotorB);
motor LiftMotorA = motor(PORT11, ratio18_1, false);
motor LiftMotorB = motor(PORT20, ratio18_1, true);
motor_group Lift = motor_group(LiftMotorA, LiftMotorB);
controller Controller1 = controller(primary);

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