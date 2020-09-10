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
Servo myServo;                  // Servo object
#define POS_SERVO_SOLVED   0    // Position for the servo to go to when solved all puzzles



// Ryan's Pins ---------------------------------------------------------------
// Switch Pins
#define PIN_SWITCH3    5      // Pin for tool found signal, SWITCH3

// Touch Sensors
#define PIN_TOUCH0     6      // Pin for touch 0 signal, TOUCH0
#define PIN_TOUCH1     7      // Pin for touch 1 signal, TOUCH1
#define PIN_TOUCH2     8      // Pin for touch 2 signal, TOUCH2

// Rotary Encoder
#define PIN_ROT_A       2     // Rotary encoder pin A, ROT_EN0
#define PIN_ROT_B       3     // Rotary encoder pin B, ROT_EN0
#define PIN_ROT_SWITCH  4     // Rotary encoder switch pin, ROT_EN0



// Ryan's Variables -----------------------------------------------------------
// LCD
LiquidCrystal_I2C lcd(0x27,16,2);   // set the LCD address to 0x27 for a 16 chars and 2 line display
boolean isLCD = false;              // boolean for if the LCD is on or off
boolean isMonth = true;             // boolean for if entering the month of Lindsay's birthday, start true
boolean isDay = false;              // boolean for if entering the day of Lindsay's birthday, start false
boolean isYear = false;             // boolean for if entering the year of Lindsay's birthday
int lcdMonth = 00;                  // int for tracking what month is entered
int lcdDay = 00;                    // int for tracking what day is entered
int lcdYear = 2020;                 // int for tracking what year is entered

// Rotary Encoder
volatile int lastEncoded = 0;       // track last encoded value
volatile long encoderValue = 2;     // track the encoder value, start at 2 because the encoder starts at -2      
boolean rotChange = false;          // boolean for if the rotary encoder has been turned
boolean isLCDWrite = false;         // boolean for if we've written the update to the LCD



// Setup -------------------------------------------------------------------------
void setup() {
  initLCD();                        // Initialize the lcd, do this first to shut it off quickly
  Serial.begin(9600);               // Initialize serial
  
  Serial.println("HELLO WORLD!");
  Serial.println("LNL/TA");
  Serial.println("Puzzle Box V02 - Ryan Mak");
  Serial.println("V01_200522");
  Serial.println("\nInitializing...");

  pinMode(PIN_RESET, INPUT);        // Initialize the reset pin
  initPuzzleLEDs();                 // Initialize puzzle indicator LEDs
  initServo();                      // Initialize the lid servo do this last to give the capacitor time to charge


  // Ryan's Setup
  pinMode(PIN_SWITCH3, INPUT);      // Initialize the tool switch
  initRotaryEncoder();              // Initialize the rotary encoder
  initTouchSensors();               // Initialize touch sensors

  
  delay(500);                       // Delay to let everything settle
  blinkStartLEDs();                 // Blink LEDs to indicate box is starting
  
}// End Setup



// Loop ---------------------------------------------------------------------------
void loop() {
// For debugging purposes
//  checkSwitches();

// if all three sensors are touched, puzzle is solved
  if(digitalRead(PIN_TOUCH0) && digitalRead(PIN_TOUCH1) && digitalRead(PIN_TOUCH2) && !isPuz[0]) {
    solvedPuzzle(0);
  }



// check if found the tool
  if(digitalRead(PIN_SWITCH3) && !isPuz[1]) {
    solvedPuzzle(1);
  }



// if solved the first and second puzzle and the lcd is not on
// turn on LCD, write the clue, set the cursor to month position, reset encoder value
  if(isPuz[0] && isPuz[1] && !isLCD) {
    lcdOn();
    lcdWrite("LINDSAY'S BDAY:","01/01/2020");
    lcdWriteMonth(13); 
    rotChange = false;
    isLCDWrite = false;                        
  }



// if rotary encoder enter pressed check if correct value for date
  if(digitalRead(PIN_ROT_SWITCH) && rotChange && isPuz[0] && isPuz[1] ) {
    checkRotPress();
    Serial.println("Checking...");
  }



// if the encoder has been turned and hasn't been written to the LCD, update LCD 
  if(rotChange && !isLCDWrite) {
    if(isMonth) {
      lcdWriteMonth(encoderValue/4);      // Need to divide by 4 because each encoder notch counts as 4
    }
    if(isDay) {
      lcdWriteDay(encoderValue/4);
    }
    if(isYear) {
      lcdWriteYear(encoderValue/4);
    }
    isLCDWrite = true;
  }



  
// If reset button is hit, turn off the LCD and reset all puzzles
  if(analogRead(PIN_RESET)<100) {
    setToSolvedPuzzles();
  }

}// End Loop
