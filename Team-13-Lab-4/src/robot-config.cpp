#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
/*vex-vision-config:begin*/
signature VisionSensor__GREEN_BALL = signature (1, -7213, -4867, -6040, -1, 533, 266, 4.1, 0);
signature VisionSensor__SIG_2 = signature (2, 0, 0, 0, 0, 0, 0, 3, 0);
vision VisionSensor = vision (PORT17, 50, VisionSensor__GREEN_BALL, VisionSensor__SIG_2);
/*vex-vision-config:end*/
motor MotorR = motor(PORT1, ratio18_1, false);
motor MotorL = motor(PORT10, ratio18_1, true);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}