using namespace vex;

extern brain Brain;

// VEXcode devices
extern line LineTrackerL;
extern line LineTrackerR;
extern motor MotorLf;
extern motor MotorRf;
extern motor MotorRb;
extern motor MotorLb;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );