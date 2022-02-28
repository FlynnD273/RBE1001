/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\evanp                                            */
/*    Created:      Wed Jan 19 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LineTrackerA         line          A               
// LineTrackerB         line          B               
// LB                   motor         9               
// LF                   motor         10              
// RF                   motor         5               
// RB                   motor         3               
// LiftR                motor         11              
// LiftL                motor         20              
// Claw                 motor         4               
// Vision15             vision        15              
// RangeFinderE         sonar         E, F            
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include <iostream>
#include <cmath>
using namespace std;

using namespace vex;

motor_group Right(RF, RB);
motor_group Left(LF, LB);
motor_group Lift(LiftR, LiftL);

const double wheelDiameter = 10.4; // CM
//const double GearRatio = 1/5;
const double wheelTrack = 25.4;
double circumference = wheelDiameter * M_PI;



void move(double distance) {
  cout << "hi";
  double circumference = wheelDiameter * M_PI;


  Right.spinFor(distance*360/circumference, degrees, false);
  Left.spinFor(distance*360/circumference, degrees);
}



void movevoltage (double voltage) { 
  
    Right.spin(reverse, voltage, volt);
    Left.spin(reverse, voltage, volt);
    
}

void rotate(double angle) {
  Right.spinFor(fwd, (1.25*wheelTrack*M_PI*360/circumference)/(360/angle), degrees, 50, rpm, false);
  Left.spinFor(reverse, (1.25*wheelTrack*M_PI*360/circumference)/(360/angle), degrees, 50, rpm);
  

}
double speed = 20.0; // 15

double DetermineEffort(double actual)
{
    double KP = 0.02; // .35
    double desired = 90;  
    double error = desired - actual;
    double effort = KP * error;
    return effort;

}

int intersectCount = 0;

double TARGET_DISTANCE = 21.5;
void WhiteLine ()
{
    while(true)
    {
      task::sleep(20);
      float rL = LineTrackerB.reflectivity();
      float rR = LineTrackerA.reflectivity(); 
      cout << "A is " << rR << endl;
      cout << "B is " << rL << endl;
      float distance = RangeFinderE.distance(distanceUnits::cm);
      cout << "Robot is " << distance << " cm from the object" << endl;
    
        // if((TARGET_DISTANCE-2) < distance && distance < (TARGET_DISTANCE+2))
        // {
        //     Left.stop();
        //     Right.stop();
        // }
        // else if(distance > TARGET_DISTANCE)
        // {
        //     continue;
        // }

        if(rR > 12 && rL > 12)
        {
          for(int i = 0; i<10; i++) {
            cout << "count is " << i << endl;
            Right.stop();
            Left.stop();
            if (intersectCount == 0) {
              Left.stop();
              Right.stop();
              wait(0.5, seconds);
              //Lift.spinFor(reverse, 160, degrees);
              Left.spinFor(fwd, 240, degrees, false);
              Right.spinFor(fwd, 240, degrees);
              Claw.spinFor(fwd, 35, degrees);
              Left.spinFor(reverse, 350, degrees, false);
              Right.spinFor(reverse, 350, degrees);
              intersectCount++;
              //i++;
            } 
            else if (intersectCount == 1 ) {
              Right.spinFor(reverse, 0*(1.25*wheelTrack*M_PI*360/circumference)/(360/(90)), degrees, 40, rpm, false);
              Left.spinFor(fwd, 2*(1.25*wheelTrack*M_PI*360/circumference)/(360/(90)), degrees, 40, rpm);
              intersectCount++;
            }
            else if (intersectCount == 2) {
              Left.stop();
              Right.stop();
              wait(0.5, sec);

              //intersectCount++;
            }
            else if (intersectCount == 3) {
              continue;
              intersectCount++;
            }
            else if (intersectCount == 4) {
              Right.spinFor(reverse, 2.25*(1.25*wheelTrack*M_PI*360/circumference)/(360/(90)), degrees, 40, rpm, false);
              Left.spinFor(fwd, 2.25*(1.25*wheelTrack*M_PI*360/circumference)/(360/(90)), degrees, 40, rpm);
              Lift.spinFor(reverse, 700, degrees);
              intersectCount++;
            }
            //rotate(-70);
        }
        }
        else if(rR > 12)
        {
            Left.spin(reverse, speed/2 + 0.5*DetermineEffort(rL), rpm);
            Right.spin(fwd, speed/3 + 0.5*DetermineEffort(rR), rpm);
        }
        else if(rL > 12)
        {
            Right.spin(reverse, speed/2 + 0.5*DetermineEffort(rR), rpm);
            Left.spin(fwd, speed/3 + 0.5*DetermineEffort(rL), rpm);
        }
        else
        { 
          Right.spin(fwd, speed, rpm);
          Left.spin(fwd, speed, rpm);
        }
    }
}

void LineTracking ()
{
    while(true)
    {
      task::sleep(100);
       
      float rL = LineTrackerB.reflectivity();
      float rR = LineTrackerA.reflectivity(); 
      cout << "A is " << rR << endl;
      cout << "B is " << rL << endl;
    
        if(rR < 12 && rL < 12)
        {
            // Left.spinFor(fwd, 770, degrees);
            // Right.spinFor(fwd, 770, degrees);
            // Claw.spinFor(fwd, 90, degrees);
            // Left.spinFor(reverse, 400, degrees);
            // Right.spinFor(reverse, 400, degrees);
            WhiteLine();
        }
        else if(rR < 12)
        {
            Left.spin(reverse, speed/2 + DetermineEffort(rL), rpm);
            Right.spin(fwd, speed/2.5 + DetermineEffort(rR), rpm);
        }
        else if(rL < 12)
        {
            Right.spin(reverse, speed/2 + DetermineEffort(rR), rpm);
            Left.spin(fwd, speed/2.5 + DetermineEffort(rL), rpm);
        }
        else
        { 
          Right.spin(fwd, speed, rpm);
          Left.spin(fwd, speed, rpm);
        }
    }
}

int main() {
  vexcodeInit();
  move(200);
  //Lift.spinFor(reverse, 20, degrees);
  // Lift.spinFor(fwd, 60, degrees);
  
  
  // Claw.spinFor(reverse, 90, degrees);
  // Claw.stop(hold);
  // //     // Lift.spinFor(fwd, 60, degrees);
  // Lift.spinFor(reverse, 350, degrees);

  // //Lift.spinFor(reverse, 260, degrees);

  //LineTracking();

    

}







