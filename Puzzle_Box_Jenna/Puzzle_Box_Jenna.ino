// Include Libraries
#include <Wire.h>                 // i2C
#include <Servo.h>                // Servo
#include "MAX30105.h"             // Heart Rate
#include "heartRate.h"            // Heart Rate Math


// All puzzle box definitions ----------------------------------------------
#define NUM_PUZZLES    3      // Number of puzzles to solve, change this depending on how many puzzles

// Puzzle Pins
#define PIN_PUZ0       2      // Pin to indicate puzzle 0 solved
#define PIN_PUZ1       6      // Pin to indicate puzzle 1 solved
#define PIN_PUZ2       7      // Pin to indicate puzzle 2 solved

// Reset and Servo Pins
#define PIN_RESET           A7      // Pin to reset all puzzles to unsolved or solved
#define PIN_SERVO_LID       9       // Pin for the lid servo
#define PIN_SERVO_LID_PWR   5       // Pin for the lid servo power

// Arrays for LEDs and if puzzles are solved
const int puzzleLEDS[] = { PIN_PUZ0, PIN_PUZ1, PIN_PUZ2 };
boolean isPuz[] = { false, false, false };

// Servo
Servo myServo;                      // Servo Object
#define POS_SERVO_SOLVED    0       // Position servo should be in for box to be unlocked



// Jenna's Pins ---------------------------------------------------------------
// Sensors
#define PIN_SPEED       3      // Pin for speed sensor signal, SPEED0
#define PIN_POT0        A0     // Pin for potentiometer 0 signal
#define PIN_POT1        A1     // Pin for potentiometer 1 signal
#define PIN_POT2        A2     // Pin for potentiometer 2 signal
#define PIN_POT3        A3     // Pin for potentiometer 3 signal
#define PIN_POT4        A6     // Pin for potentiometer 4 signal


// Jenna's Variables -----------------------------------------------------------
// Speed Sensor
boolean isSpinning = false;       // Flag for if the magnet is spinning
int countSpeed = 0;               // Count for how many times the magnet has been detected spinning
unsigned long prevTimeSpeed;      // Track time for speed sensor count


// Potentiometers
#define V0            600         // Voltage for 0
#define V1            100         // Voltage for 1
#define V2            200         // Voltage for 2
#define V3            800         // Voltage for 3
#define V4            955         // Voltage for 4
#define V_RANGE       100         // Voltage range

// Heart Rate
MAX30105 particleSensor;
const byte RATE_SIZE = 2;         // Increase this for more averaging. 4 is good.
byte rates[RATE_SIZE];            // Array of heart rates
byte rateSpot = 0;                // Array iterator
long lastBeat = 0;                // Time at which the last beat occurred
float beatsPerMinute;             // current beats per minute
int beatAvg;                      // Average beats per minute
int countFinger = 0;              // Counts how many times a finger has been sensed
boolean isFinger = false;         // Flag for if finger is sensed





// Setup -------------------------------------------------------------------------
void setup() {

  Serial.begin(230400);                 // initialize serial at high rate for heart rate sensor
  
  Serial.println("HELLO WORLD!");
  Serial.println("LNL/TA");
  Serial.println("Puzzle Box V02 - Jenna Lowry");
  Serial.println("V01_200728");
  Serial.println("\nInitializing...");

  pinMode(PIN_RESET, INPUT);          // Initialize the reset pin
  initPuzzleLEDs();                   // Initialize puzzle indicator LEDs
  initServo();                        // Initialize the lid servo
  

// Jenna's Setup
  initSpeed();                        // Initialize the speed sensor
  initHeart();                        // Initialize heart rate monitor sensors

  
  delay(500);                         // Delay to let everything settle
  blinkStartLEDs();                   // Blink LEDs to indicate box is starting

  
  prevTimeSpeed = millis();           // Set time to now
  Serial.println("Starting...");
}



// Loop ---------------------------------------------------------------------------
void loop() {
  
// If puzzle 0 not solved, check speed sensor count, if spinning, puzzle is solved
  if(!isPuz[0]) {
    checkSpeed();

    if(isSpinning) {
      solvedPuzzle(0);
      isSpinning = false;          
    }             
  }



  
// if puzzle 1 isn't solved and potentiometers are correct, then puzzle is solved
  if(!isPuz[1]) {
    if(checkPot()) {
      solvedPuzzle(1);
    }
  }




// if puzzle 2 not solved, check heart rate, if above 90bpm then solved puzzle
  if(!isPuz[2] & isPuz[1] & isPuz[0]) {
    checkHeart();
    
    if(beatsPerMinute > 80.0) {
      solvedPuzzle(2);
    }
  }



// If reset button is hit, turn off the LCD and reset all puzzles
  if(analogRead(PIN_RESET)<100) {
    setToSolvedPuzzles();
  }



} // End Loop
