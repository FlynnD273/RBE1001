using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor MotorL;
extern motor MotorR;
extern motor MotorArm;
extern controller Controller1;
extern sonar RangeFinderE;
extern bumper BumperC;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );