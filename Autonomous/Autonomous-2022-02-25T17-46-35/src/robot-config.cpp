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
signature VisionF__RED_MARKER = signature (1, 7965, 8377, 8171, -237, 231, -3, 5.3, 1);
signature VisionF__YELLOW_MARKER = signature (2, 1061, 1381, 1221, -3795, -3533, -3664, 8.2, 1);
signature VisionF__SIG_3 = signature (3, 0, 0, 0, 0, 0, 0, 3, 0);
signature VisionF__SIG_4 = signature (4, 0, 0, 0, 0, 0, 0, 3, 0);
signature VisionF__SIG_5 = signature (5, 0, 0, 0, 0, 0, 0, 3, 0);
signature VisionF__SIG_6 = signature (6, 0, 0, 0, 0, 0, 0, 3, 0);
signature VisionF__SIG_7 = signature (7, 0, 0, 0, 0, 0, 0, 3, 0);
code VisionF__DORM = code (VisionF__RED_MARKER, VisionF__YELLOW_MARKER );
vision VisionF = vision (PORT15, 42, VisionF__RED_MARKER, VisionF__YELLOW_MARKER, VisionF__SIG_3, VisionF__SIG_4, VisionF__SIG_5, VisionF__SIG_6, VisionF__SIG_7);
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