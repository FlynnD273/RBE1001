using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor MotorRb;
extern motor MotorLb;
extern controller Controller1;
extern motor MotorLf;
extern motor MotorRf;
extern motor Claw;
extern motor LiftR;
extern motor LiftL;
extern line LineTrackerA;
extern line LineTrackerB;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );