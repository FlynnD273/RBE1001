using namespace vex;

extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern line LineTrackerA;
extern line LineTrackerB;
extern motor Claw;
extern signature Vision15__SIG_1;
extern signature Vision15__SIG_2;
extern signature Vision15__SIG_3;
extern signature Vision15__SIG_4;
extern signature Vision15__SIG_5;
extern signature Vision15__SIG_6;
extern signature Vision15__SIG_7;
extern vision Vision15;
extern sonar RangeFinderE;
extern motor_group Left;
extern motor_group Right;
extern motor_group Lift;
extern controller Controller1;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );