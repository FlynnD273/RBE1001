using namespace vex;

extern brain Brain;

using signature = vision::signature;
using code = vision::code;

// VEXcode devices
extern motor_group MotorsR;
extern motor_group MotorsL;
extern motor_group MotorsB;
extern motor MotorC;
extern line LineR;
extern line LineL;
extern sonar RangeR;
extern signature VisionF__ORANGE_DARK;
extern signature VisionF__YELLOW_ALL;
extern signature VisionF__ORANGE_LIGHT;
extern signature VisionF__SIG_4;
extern signature VisionF__SIG_5;
extern signature VisionF__SIG_6;
extern signature VisionF__SIG_7;
extern code VisionF__DORM1;
extern code VisionF__DORM2;
extern vision VisionF;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );