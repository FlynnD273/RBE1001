using namespace vex;

extern brain Brain;

// VEXcode devices
extern line LineTrackerA;
extern line LineTrackerB;
extern motor Claw;
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