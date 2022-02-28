using namespace vex;

const double WHEEL_TRACK {28.2};
const double WHEEL_DIAM {10.16};
const double LIFT_HEIGHTS[] {0, 120, 270, 420, 560, 720};
const int LIFT_LEVEL_COUNT = sizeof(LIFT_HEIGHTS)/sizeof(LIFT_HEIGHTS[0]);

class Toggler { bool value; bool prevState; public : bool getValue(); public : bool getValue(bool); };

void driveRotations(double, double, rotationUnits);

void driveDistance(double, double);

void turn(double, double);

void liftToFloor(int);

void openClaw();

void closeClaw();

void openClawL();

void DetermineEffort();

void BlackLineTracking();

void WhiteLineTracking();

void RampToDorm();

void DriveUntilWhite(bool isForwards);

bool tryDetectObject(vex::vision::object&, vex::vision::signature);

enum trackColorState {SUCCESSFUL, PENDING, LOST};

trackColorState trackColor(vex::vision::signature, double, double, double, double);