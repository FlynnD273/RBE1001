using namespace vex;

const double WHEELTRACK {28.2};
const double WHEELDIAM {10.16};
const double LIFT_HEIGHTS[] {0, 1, 2, 3};
const int LIFT_LEVELS = sizeof(LIFT_HEIGHTS)/sizeof(LIFT_HEIGHTS[0]);

void drive(double, double, rotationUnits);

void driveDistance(double, double);

void turn(double, double);

void liftToFloor(int);