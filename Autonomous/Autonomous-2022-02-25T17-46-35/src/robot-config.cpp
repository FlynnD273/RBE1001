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
signature VisionF__ORANGE_DARK = signature (1, 0, 0, 0, 0, 0, 0, 3, 1);
signature VisionF__YELLOW_ALL = signature (2, 0, 0, 0, 0, 0, 0, 3, 1);
signature VisionF__ORANGE_LIGHT = signature (3, 0, 0, 0, 0, 0, 0, 3, 0);
signature VisionF__SIG_4 = signature (4, -173, 171, -1, -2929, -2671, -2800, 6.6, 1);
signature VisionF__SIG_5 = signature (5, 3835, 4177, 4006, -2529, -2265, -2397, 7.4, 1);
code VisionF__DORM1 = code (VisionF__SIG_4, VisionF__SIG_5 );
code VisionF__DORM2 = code (VisionF__ORANGE_DARK, VisionF__YELLOW_ALL );
vision VisionF = vision (PORT15, 42, VisionF__ORANGE_DARK, VisionF__YELLOW_ALL, VisionF__ORANGE_LIGHT, VisionF__SIG_4, VisionF__SIG_5);
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