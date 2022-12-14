// Imports
#include <Servo.h>

// Objects
Servo servoWrist;
Servo servoThumb;
Servo servoIndex;
Servo servoMiddle;
Servo servoRing;
Servo servoPinky;

// Variables
int index;
int indexUp;
int numDigits;
int fingerPos;
String myString;

// Setup code goes here
void setup() {
  // Starts the serial
  Serial.begin(9600);
  Serial.setTimeout(10);

  // Sets up the servos
  servoWrist .attach(7);
  servoThumb .attach(8);
  servoIndex .attach(9);
  servoMiddle.attach(10);
  servoRing  .attach(11);
  servoPinky .attach(12);

  // Servos go to the init position
  servoWrist .write(90);
  servoThumb .write(90);
  servoIndex .write(90);
  servoMiddle.write(90);
  servoRing  .write(90);
  servoPinky .write(90);

  // Initialize the built in LED
  pinMode(LED_BUILTIN, OUTPUT);
}

// Main loop code goes here
void loop() {
  // Idles when there is no data
  while (Serial.available() == 0) {
    // Turns the built in LED off when there is no serial data
    digitalWrite(LED_BUILTIN, LOW);
  }

  // Turns the built in LED on when there is serial data
  digitalWrite(LED_BUILTIN, HIGH);

  // Recieves the data
  myString = Serial.readStringUntil('\r');

  // Sets the digits per number
  numDigits = 3;

  // Sets up the indices
  index   = 0;
  indexUp = index + numDigits;

  // Thumb movement
  servoThumb.write(myString.substring(index, indexUp).toInt());

  // Increments the indices
  index   += numDigits;
  indexUp += numDigits;

  // Index movement
  servoIndex.write(myString.substring(index, indexUp).toInt());

  // Increments the indices
  index   += numDigits;
  indexUp += numDigits;

  // Middle movement
  servoMiddle.write(myString.substring(index, indexUp).toInt());

  // Increments the indices
  index   += numDigits;
  indexUp += numDigits;

  // Ring movement
  servoRing.write(myString.substring(index, indexUp).toInt());

  // Increments the indices
  index   += numDigits;
  indexUp += numDigits;

  // Pinky movement
  servoPinky.write(myString.substring(index, indexUp).toInt());

  // Increments the indices
  index   += numDigits;
  indexUp += numDigits;

  // Wrist movement
  servoWrist.write(myString.substring(index, indexUp).toInt());
}