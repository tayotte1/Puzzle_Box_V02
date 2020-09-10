// Include Libraries
#include <LiquidCrystal_I2C.h>    // LCD
#include <Wire.h>                 // i2C
#include <Servo.h>                // Servo

// All puzzle box definitions ----------------------------------------------
#define NUM_PUZZLES    4      // Number of puzzles to solve, change this depending on how many puzzles

// Puzzle Pins
#define PIN_PUZ0       A0     // Pin to indicate puzzle 0 solved
#define PIN_PUZ1       A1     // Pin to indicate puzzle 1 solved
#define PIN_PUZ2       A2     // Pin to indicate puzzle 2 solved
#define PIN_PUZ3       A3     // Pin to indicate puzzle 2 solved

// Reset and Servo Pins
#define PIN_RESET           A7     // Pin to reset all puzzles to unsolved or solved
#define PIN_SERVO_LID       9      // Pin for the lid servo
#define PIN_SERVO_LID_PWR   10     // Pin for the lid servo power


// Arrays for LEDs and if puzzles are solved
const int puzzleLEDS[] = { PIN_PUZ0, PIN_PUZ1, PIN_PUZ2, PIN_PUZ3 };
boolean isPuz[] = { false, false, false, false };

// Servo
Servo myServo;
#define POS_SERVO_INIT     90
#define POS_SERVO_SOLVED   0



// Matt's Pins ---------------------------------------------------------------
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

// LCD Buttons
#define PIN_BUTTON0     11    // Pin for button 0 signal, SWITCH6
#define PIN_BUTTON1     12    // Pin for button 1 signal, SWITCH7
#define PIN_BUTTON2     13    // Pin for button 2 signal, SWITCH8


// Matt's Variables -----------------------------------------------------------
// LCD
LiquidCrystal_I2C lcd(0x27,16,2);   // set the LCD address to 0x27 for a 16 chars and 2 line display
boolean isLCD = false;              // boolean for if the LCD is on or off
int lcdNumber = 0;
int Q = 1;
unsigned long prevTime;             // track time so can abort asking questions

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
  Serial.println("Puzzle Box V02 - Matt Capozza");
  Serial.println("V01_200713");
  Serial.println("\nInitializing...");

  pinMode(PIN_RESET, INPUT);        // Initialize the reset pin
  initPuzzleLEDs();                 // Initialize puzzle indicator LEDs
  initServo();                      // Initialize the lid servo do this last to give the capacitor time to charge


  // Matt's Setup
  initTouchSensors();               // Initialize touch sensors
  pinMode(PIN_SWITCH3, INPUT);      // Initialize the tool switch
  initButtons();                    // Initialize the LCD buttons
  initRotaryEncoder();              // Initialize the rotary encoder

  
  delay(500);                       // Delay to let everything settle
  blinkStartLEDs();                 // Blink LEDs to indicate box is starting
  Serial.println("Starting...");    // Debug printing
}// End Setup



// Loop ---------------------------------------------------------------------------
void loop() {
// For debugging purposes
  checkSwitches();

// if all three sensors are touched, puzzle is solved
  if( digitalRead(PIN_TOUCH0) && digitalRead(PIN_TOUCH1) && digitalRead(PIN_TOUCH2) && !isPuz[0] ) {
    solvedPuzzle(0);
  }



// check if found the tool
  if( digitalRead(PIN_SWITCH3) && !isPuz[1] ) {
    solvedPuzzle(1);
  }



// if solved the first and second puzzle and the lcd is not on
// turn on LCD, write the clue, set the cursor to month position, reset encoder value
  if( isPuz[0] && isPuz[1] ) {
    if(!isLCD) {
      lcdOn();
      lcdWrite("WELCOME TO","TRIVIA!");
      delay(5000);
      lcdWrite("Press A","");
      while(!digitalRead(PIN_BUTTON0)) {
        delay(10);
      }
      askQuestion();
      lcdWriteNumber(101);
      rotChange = false;
      isLCDWrite = false; 
    } else if(isPuz[2]) {
      askQuestion();
    }
                           
  }



// if rotary encoder enter pressed, the encoder has been changed, the first two puzzles have
// been completed, and the third puzzle is not completed check if correct value for date
  if( digitalRead(PIN_ROT_SWITCH) && rotChange && isPuz[0] && isPuz[1] && !isPuz[2] ) {
    Serial.println("Checking...");
    checkRotPress();
  }



// if the encoder has been turned and hasn't been written to the LCD, and the third puzzle hasn't been completed, update LCD 
  if( rotChange && !isLCDWrite && isPuz[0] && isPuz[1] && !isPuz[2] ) {
    lcdWriteNumber(encoderValue/4);      // Need to divide by 4 because each encoder notch counts as 4   
    isLCDWrite = true;
  }

  
// If reset button is hit, turn off the LCD and reset all puzzles
  if( analogRead(PIN_RESET)<100 ) {
    setToSolvedPuzzles();
  }

}// End Loop
