#include <Arduino.h>
#include <RBE1001Lib.h>
#include <button.h>

// declare the pin for the LED
const int LED_PIN = 33;
const int POT_PIN = 35;

// Create a button object for the built-in button on the ESP32
Button bootButton(BOOT_FLAG_PIN);

// Define two basic states. For this program, they will correspond to an LED state (on or off).
// "enum" stands for "enumerate". Basically, we define a new variable type called ROBOT_STATE.
// We prepend "ROBOT_" to everything to avoid conflicts with other variables that may be defined elsewhere.
enum SYSTEM_STATE {SYS_IDLE, SYS_ACTIVE};

// Declare a variable, robotState, of our new type, ROBOT_STATE. Initialize it to ROBOT_IDLE.
SYSTEM_STATE state = SYS_IDLE;

//
int count = 0;

/*
 * This is the standard setup function that is called when the ESP32 is rebooted.
 * It is used to initialize anything that needs to be done once.
 */
void setup() 
{
  // This will initialize the Serial at a baud rate of 115200 for prints
  // Be sure to set your Serial Monitor appropriately in platformio.ini
  Serial.begin(115200);

  // Set the LED pin to be an OUTPUT
  pinMode(LED_PIN, OUTPUT);

  // Set the potentiometer pin to be an OUTPUT
  pinMode(POT_PIN, INPUT);

  // Initialize the button object
  bootButton.Init();
}

/* Here is where all the fun happens. For each state, check for and respond to a button press.
 */ 
void loop()
{
  // Go through the state machine
  if(state == SYS_IDLE)
  {
    if(bootButton.CheckButtonPress()) //if the button was pressed, switch to ACTIVE
    {
      // Notify us that we're switching to ACTIVE
      Serial.println("Button press -> ACTIVE");

      // Turn the LED on
      // digitalWrite(LED_PIN, HIGH);
      // analogWrite(LED_PIN, 180);
      Serial.println(++count);
      // Finally, update the state
      state = SYS_ACTIVE;
    }
  }

  //note that we use else..if for each additional state, so it doesn't get confused
  else if(state == SYS_ACTIVE)
  {
    if(bootButton.CheckButtonPress()) //if the button was pressed, switch to IDLE
    {
      // Notify us that we're switching to IDLE
      Serial.println("Button press -> IDLE");

      // Turn the LED off
      // digitalWrite(LED_PIN, LOW);
      // analogWrite(LED_PIN, 80);

      // Finally, update the state
      state = SYS_IDLE;
    }

    Serial.println(analogRead(POT_PIN));
    delay(200);
  }
  analogWrite(LED_PIN, analogRead(POT_PIN) / 16);
}