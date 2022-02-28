using namespace vex;

const double WHEEL_TRACK {28.2};
const double WHEEL_DIAM {10.16};
const double LIFT_HEIGHTS[] {0, 120, 270, 420, 560, 720};
const int LIFT_LEVEL_COUNT = sizeof(LIFT_HEIGHTS)/sizeof(LIFT_HEIGHTS[0]);

class Toggler { bool value; bool prevState; public : bool getValue(); public : bool getValue(bool); };

void drive(double, double, rotationUnits);

void driveDistance(double, double);

void turn(double, double);

void liftToFloor(int);