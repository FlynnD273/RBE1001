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
signature VisionF__ORANGE_DARK = signature (1, 8649, 9051, 8850, -1733, -1473, -1603, 9.9, 1);
signature VisionF__YELLOW_ALL = signature (2, -1, 961, 480, -4509, -3233, -3871, 3, 1);
signature VisionF__ORANGE_LIGHT = signature (3, 8809, 9959, 9384, -2455, -1171, -1813, 10, 1);
signature VisionF__SIG_4 = signature (4, 0, 0, 0, 0, 0, 0, 3, 0);
code VisionF__DORM1 = code (VisionF__ORANGE_LIGHT, VisionF__YELLOW_ALL );
code VisionF__DORM2 = code (VisionF__ORANGE_DARK, VisionF__YELLOW_ALL );
vision VisionF = vision (PORT15, 19, VisionF__ORANGE_DARK, VisionF__YELLOW_ALL, VisionF__ORANGE_LIGHT, VisionF__SIG_4);
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