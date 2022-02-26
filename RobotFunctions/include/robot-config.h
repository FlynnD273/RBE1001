using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor MotorLiftL;
extern motor MotorLiftR;
extern motor MotorGrabber;
extern motor MotorDriveBL;
extern motor MotorDriveBR;
extern motor MotorDriveFL;
extern motor MotorDriveFR;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );