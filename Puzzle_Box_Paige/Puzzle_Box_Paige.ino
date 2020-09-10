// Include Libraries
#include <Wire.h>                 // i2C
#include <Servo.h>                // Servo
#include <Adafruit_LIS3DH.h>      // Accelerometer
#include <Adafruit_Sensor.h>      // Accelerometer



// All puzzle box definitions ----------------------------------------------
#define NUM_PUZZLES    3      // Number of puzzles to solve, change this depending on how many puzzles

// Puzzle Pins
#define PIN_PUZ0       A0     // Pin to indicate puzzle 0 solved
#define PIN_PUZ1       A1     // Pin to indicate puzzle 1 solved
#define PIN_PUZ2       A2     // Pin to indicate puzzle 2 solved

// Reset and Servo Pins
#define PIN_RESET           A7      // Pin to reset all puzzles to unsolved or solved
#define PIN_SERVO_LID       9       // Pin for the lid servo
#define PIN_SERVO_LID_PWR   8       // Pin for the lid servo power

// Arrays for LEDs and if puzzles are solved
const int puzzleLEDS[] = { PIN_PUZ0, PIN_PUZ1, PIN_PUZ2 };
boolean isPuz[] = { false, false, false };

// Servo
Servo myServo;                      // Servo Object
#define POS_SERVO_SOLVED    0       // Position servo should be in for box to be unlocked



// Paige's Pins ---------------------------------------------------------------
// Sensors
#define PIN_SPEED     2      // Pin for speed sensor signal, SPEED0
#define PIN_IR        5      // Pin for IR sensor signal, IR0
#define PIN_TV        A3     // Pin to turn on the TV



// Paige's Variables -----------------------------------------------------------
unsigned long prevTimeAccel;      // Track time for accelerometer count
unsigned long prevTimeSpeed;      // Track time for speed sensor count

// Accelerometer
Adafruit_LIS3DH lis = Adafruit_LIS3DH();    // Accelerometer object
boolean isDropped = false;                  // Flag for if the box has been dropped
int countDrop = 0;                          // Count for sensing how long the box has been dropping

// Speed Sensor
boolean isSpinning = false;       // Flag for if the magnet is spinning
int countSpeed = 0;               // Count for how many times the magnet has been detected spinning



// Setup -------------------------------------------------------------------------
void setup() {

  Serial.begin(9600);                 // initialize serial
  
  Serial.println("HELLO WORLD!");
  Serial.println("LNL/TA");
  Serial.println("Puzzle Box V02 - Paige Scrofani");
  Serial.println("V01_200505");
  Serial.println("\nInitializing...");

  pinMode(PIN_RESET, INPUT);          // Initialize the reset pin
  initPuzzleLEDs();                   // Initialize puzzle indicator LEDs
  initServo();                        // Initialize the lid servo
  

// Paiges's Setup
  initAccelerometer();                // Initialize the accelerometer
  initIR();                           // Initialize IR sensor
  initSpeed();                        // Initialize the speed sensor

  

  
  delay(500);                         // Delay to let everything settle
  blinkStartLEDs();                   // Blink LEDs to indicate box is starting
  
  prevTimeAccel = millis();           // Set time to now
  prevTimeSpeed = millis();           // Set time to now
}



// Loop ---------------------------------------------------------------------------
void loop() {
// if puzzle 0 not solved, check accelerometer, if dropped the puzzle is solved
  if(!isPuz[0]) {
    checkAccelerometer();
    
    if(isDropped) {
      solvedPuzzle(0);
    }
  }



// check if IR is sensed (HIGH is off state), if yes and puzzle not solved, puzzle is solved
  if(!isPuz[1] && !digitalRead(PIN_IR)) {
    solvedPuzzle(1);
    digitalWrite(PIN_TV,HIGH);
  }



  
// If puzzle 2 not solved, check speed sensor count, if spinning, puzzle is solved
  if(!isPuz[2]) {
    checkSpeed();

    if(isSpinning) {
      solvedPuzzle(2);
      isSpinning = false;          
    }             
  }



  
// If reset button is hit, turn off the LCD and reset all puzzles
  if(analogRead(PIN_RESET)<100) {
    setToSolvedPuzzles();
  }


} // End Loop
