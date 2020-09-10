// Include Libraries
#include <LiquidCrystal_I2C.h>    // LCD
#include <Wire.h>                 // i2C
#include <Servo.h>                // Servo

// All puzzle box definitions ----------------------------------------------
#define NUM_PUZZLES    3      // Number of puzzles to solve, change this depending on how many puzzles

// Puzzle Pins
#define PIN_PUZ0       A0     // Pin to indicate puzzle 0 solved
#define PIN_PUZ1       A1     // Pin to indicate puzzle 1 solved
#define PIN_PUZ2       A2     // Pin to indicate puzzle 2 solved

// Reset and Servo Pins
#define PIN_RESET           A7     // Pin to reset all puzzles to unsolved or solved
#define PIN_SERVO_LID       9      // Pin for the lid servo
#define PIN_SERVO_LID_PWR   10     // Pin for the lid servo power


// Arrays for LEDs and if puzzles are solved
const int puzzleLEDS[] = { PIN_PUZ0, PIN_PUZ1, PIN_PUZ2 };
boolean isPuz[] = { false, false, false };

// Servo
Servo myServo;                      // Servo Object
#define POS_SERVO_SOLVED    0       // Position servo should be in for box to be unlocked



// CR's Pins ---------------------------------------------------------------
// Switch Pins
#define PIN_AXE         2      // Pin for switch for axe to press, SWITCH00

// Touch Sensors
#define PIN_TOUCH0      6      // Pin for touch 0 signal, TOUCH0
#define PIN_TOUCH1      7      // Pin for touch 1 signal, TOUCH1
#define PIN_TOUCH2      8      // Pin for touch 2 signal, TOUCH2

// Rotary Encoder
#define PIN_SWITCH1     3       // Rotary encoder pin A, ROT_EN0
#define PIN_SWITCH2     4       // Rotary encoder pin B, ROT_EN0
#define PIN_SWITCH3     5       // Rotary encoder switch pin, ROT_EN0



// CR's Variables -----------------------------------------------------------
// LCD
LiquidCrystal_I2C lcd(0x27,16,2);   // set the LCD address to 0x27 for a 16 chars and 2 line display
boolean isLCD = false;              // boolean for if the LCD is on or off




// Setup -------------------------------------------------------------------------
void setup() {
  initLCD();                        // Initialize the lcd, do this first to shut it off quickly
  
  Serial.begin(9600);               // Initialize serial
  
  Serial.println("HELLO WORLD!");
  Serial.println("LNL/TA");
  Serial.println("Puzzle Box V02 - Carol and Ron Ayotte");
  Serial.println("V01_200710");
  Serial.println("\nInitializing...");

  pinMode(PIN_RESET, INPUT);        // Initialize the reset pin
  initPuzzleLEDs();                 // Initialize puzzle indicator LEDs
  initServo();                      // Initialize the lid servo do this last to give the capacitor time to charge


  // CR's Setup
  pinMode(PIN_AXE, INPUT);          // Initialize the axe switch
  initTouchSensors();               // Initialize touch sensors

  
  delay(500);                       // Delay to let everything settle
  blinkStartLEDs();                 // Blink LEDs to indicate box is starting
  
}// End Setup



// Loop ---------------------------------------------------------------------------
void loop() {
// For debugging purposes
//  checkSwitches();

// if all three sensors are touched, and puzzle 0 isn't solved, then puzzle is solved
  if(digitalRead(PIN_TOUCH0) && digitalRead(PIN_TOUCH1) && digitalRead(PIN_TOUCH2) && !isPuz[0]) {
    solvedPuzzle(0);
  }



// check if axe switch is pressed, and puzzle 1 isn't solved, then puzzle is solved
  if(digitalRead(PIN_AXE) && !isPuz[1]) {
    solvedPuzzle(1);
  }



// if first and second puzzle solved and the lcd is not on
// turn on LCD, start the trivia, if return from trivia before finishing the game, then error and shut off lcd
  if(isPuz[0] && isPuz[1] && !isLCD) {
    lcdOn();
    askQuestions();                       
    lcdWriteBlink("Error!", " ", false);
    lcdOff();
  }


  
// If reset button is hit, turn off the LCD and reset all puzzles
  if(analogRead(PIN_RESET)<100) {
    setToSolvedPuzzles();
  }

}// End Loop
