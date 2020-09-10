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
#define PIN_SERVO_LID_PWR   10      // Pin for the lid servo power

// Arrays for LEDs and if puzzles are solved
const int puzzleLEDS[] = { PIN_PUZ0, PIN_PUZ1, PIN_PUZ2 };
boolean isPuz[] = { false, false, false };

// Servo
Servo myServo;                      // Servo Object
#define POS_SERVO_SOLVED    0       // Position servo should be in for box to be unlocked



// Paige's Pins ---------------------------------------------------------------
// Sensors
#define PIN_SPEED       3      // Pin for speed sensor signal, SPEED0
#define PIN_TOUCH0      6      // Pin for touch 0 signal, TOUCH0
#define PIN_TOUCH1      7      // Pin for touch 1 signal, TOUCH1
#define PIN_TOUCH2      8      // Pin for touch 2 signal, TOUCH2


// Paige's Variables -----------------------------------------------------------
unsigned long prevTimeAccel;      // Track time for accelerometer
unsigned long prevTimeAccel2;     // Track time for accelerometer
unsigned long prevTimeSpeed;      // Track time for speed sensor count

// Accelerometer
Adafruit_LIS3DH lis = Adafruit_LIS3DH();    // Accelerometer object
int countPos = 0;                           // Count for which orientation need to go to next
#define NUM_POS 15                          // Number of positions needed to go to
const int POS[] = { 5, 4, 6, 4, 5, 3, 6, 3, 5, 4, 6, 4, 5, 3, 6 };     // Positions needed to be put in


// Speed Sensor
boolean isSpinning = false;       // Flag for if the magnet is spinning
int countSpeed = 0;               // Count for how many times the magnet has been detected spinning



// Setup -------------------------------------------------------------------------
void setup() {

  Serial.begin(9600);                 // initialize serial
  
  Serial.println("HELLO WORLD!");
  Serial.println("LNL/TA");
  Serial.println("Puzzle Box V02 - Katie Ng Ross");
  Serial.println("V01_200723");
  Serial.println("\nInitializing...");

  pinMode(PIN_RESET, INPUT);          // Initialize the reset pin
  initPuzzleLEDs();                   // Initialize puzzle indicator LEDs
  initServo();                        // Initialize the lid servo
  

// Paiges's Setup
  initAccelerometer();                // Initialize the accelerometer
  initSpeed();                        // Initialize the speed sensor
  initTouchSensors();                 // Initialize touch sensors

  

  
  delay(500);                         // Delay to let everything settle
  blinkStartLEDs();                   // Blink LEDs to indicate box is starting
  
  prevTimeAccel = millis();           // Set time to now
  prevTimeSpeed = millis();           // Set time to now
  Serial.println("Starting...");
}



// Loop ---------------------------------------------------------------------------
void loop() {

// if all three sensors are touched, and puzzle 1 isn't solved, then puzzle is solved
  if(digitalRead(PIN_TOUCH0) && digitalRead(PIN_TOUCH1) && digitalRead(PIN_TOUCH2) && !isPuz[0]) {
    solvedPuzzle(0);
  }


  
// If puzzle 1 not solved, check speed sensor count, if spinning, puzzle is solved
  if(!isPuz[1]) {
    checkSpeed();

    if(isSpinning) {
      solvedPuzzle(1);
      isSpinning = false;          
    }             
  }



// if puzzle 2 not solved, check for the start of the gymnastics routine
  if(!isPuz[2]) {
    checkStartRoutine();
//    checkAccelerometer();
  }



// If reset button is hit, turn off the LCD and reset all puzzles
  if(analogRead(PIN_RESET)<100) {
    setToSolvedPuzzles();
  }

//  delay(20);

} // End Loop
