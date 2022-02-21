#include <Arduino.h>
#include <RBE1001Lib.h>
#include <ESP32Servo.h>
#include <button.h>

//define the states in easy-to-read terms
enum {ALARM_OFF, ALARM_ARMED, ALARM_INTRUDER};
int currentState = ALARM_OFF; //start off with the alarm deactivated
Servo secServo;

Button armButton(BOOT_FLAG_PIN);

//Some pin definitions:
// const int buttonArmingPin = 32;
const int buttonDisarmingPin = 33;
const int photoPin  = 27;
const int piezoPin  = 26;
const int ledPin    = 14;
const int servoPin  = 25;


void HandleArmingButton(void)
{
  /*if(currentState == ALARM_OFF)
  {*/
    Serial.println("Arming!");

    //take action: light the LED
    digitalWrite(ledPin, HIGH);

    //take action: you get to ADD CODE HERE to move the servo!
    secServo.write(135);
    delay(100);
    currentState = ALARM_ARMED; //Don't forget to change the state!
  //}
}

void HandleLaserBroken(void)
{
  Serial.println("Tripped!");
  tone(piezoPin, 440);
  // digitalWrite(ledPin, LOW);
  // delay(500);
  // digitalWrite(ledPin, HIGH);
  currentState = ALARM_INTRUDER;
}

void HandleDisarmingButton(void)
{
  Serial.println("Disarming!");
  digitalWrite(ledPin, LOW);
  secServo.write(0);
  noTone(piezoPin);
  currentState = ALARM_OFF;
}

/*
 * Code for checking the button -- you don't need to edit this one
 */
bool CheckArmingButton(void)
{
  return armButton.CheckButtonPress() && currentState == ALARM_OFF;
}

/*
 * Code for checking the laser. YOU WILL NEED TO EDIT THIS ONE
 */
enum {LIGHT, DARK};

bool CheckIfLaserBroken(void)
{
  static int prevLaserSensorState = DARK; //the program starts with the laser off
  bool retVal = false;

  //add code here to detect the EVENT of the laser being broken. See the button checker above for hints
  int currLaserSensorState = prevLaserSensorState;

  int lightLevel = analogRead(photoPin);
  if (lightLevel < 2000) currLaserSensorState = LIGHT;

  if (lightLevel > 2200) currLaserSensorState = DARK;

  if(currentState == ALARM_ARMED && currLaserSensorState == DARK && prevLaserSensorState == LIGHT)
  {
    retVal = true;
  }
  
  prevLaserSensorState = currLaserSensorState;
  return retVal;
}

/*
 * You'll have to make your own disarming checker!
 */

bool CheckDisarmingButton(void) 
{
  static int prevButtonState = 0;

  bool retVal = false;
  int currButtonState = digitalRead(buttonDisarmingPin);
  if((currentState == ALARM_ARMED || currentState == ALARM_INTRUDER) && prevButtonState != currButtonState)
  {
      if(currButtonState == LOW) retVal = true;
  }

  prevButtonState = currButtonState;
  return retVal;
}

void setup(void) 
{
  Serial.begin(115200);
  Serial.println("Hello!");

  secServo.attach(servoPin);
  secServo.write(0);

  // pinMode(buttonArmingPin, INPUT_PULLUP); //if we use INPUT_PULLUP, we don't have to have an external pullup resistor
  pinMode(buttonDisarmingPin, INPUT_PULLUP); //if we use INPUT_PULLUP, we don't have to have an external pullup resistor
  pinMode(photoPin, INPUT);
  pinMode(piezoPin, OUTPUT);
  pinMode(ledPin, OUTPUT);


  delay(500);

  Serial.println("setup() complete");
}

void loop(void)
/*
 * Our loop() is just a set of checker-handler pairs.
 */
{
  if(CheckIfLaserBroken()) HandleLaserBroken();
  if(CheckDisarmingButton()) HandleDisarmingButton();
  if(CheckArmingButton()) HandleArmingButton();
}
