using namespace vex;

extern brain Brain;

using signature = vision::signature;
using code = vision::code;

// VEXcode devices
extern motor_group MotorsR;
extern motor_group MotorsL;
extern motor_group MotorsLifter;
extern motor MotorClaw;
extern line LineR;
extern line LineL;
extern sonar RangeR;
extern signature VisionF__RED_MARKER;
extern signature VisionF__YELLOW_MARKER;
extern signature VisionF__SIG_3;
extern signature VisionF__SIG_4;
extern signature VisionF__SIG_5;
extern signature VisionF__SIG_6;
extern signature VisionF__SIG_7;
extern code VisionF__DORM;
extern vision VisionF;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );