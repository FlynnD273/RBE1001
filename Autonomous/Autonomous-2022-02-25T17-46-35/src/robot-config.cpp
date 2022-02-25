#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor MotorsRMotorA = motor(PORT3, ratio18_1, true);
motor MotorsRMotorB = motor(PORT5, ratio18_1, true);
motor_group MotorsR = motor_group(MotorsRMotorA, MotorsRMotorB);
motor MotorsLMotorA = motor(PORT9, ratio18_1, false);
motor MotorsLMotorB = motor(PORT10, ratio18_1, false);
motor_group MotorsL = motor_group(MotorsLMotorA, MotorsLMotorB);
motor MotorsBMotorA = motor(PORT11, ratio18_1, false);
motor MotorsBMotorB = motor(PORT20, ratio18_1, true);
motor_group MotorsB = motor_group(MotorsBMotorA, MotorsBMotorB);
motor MotorC = motor(PORT4, ratio18_1, true);
line LineR = line(Brain.ThreeWirePort.B);
line LineL = line(Brain.ThreeWirePort.A);
sonar RangeR = sonar(Brain.ThreeWirePort.G);
/*vex-vision-config:begin*/
vision VisionF = vision (PORT15, 50);
/*vex-vision-config:end*/

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}