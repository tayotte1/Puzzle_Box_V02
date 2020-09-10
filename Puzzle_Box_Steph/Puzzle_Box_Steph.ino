// Include Libraries
#include <Servo.h>                // Servo
#include <Adafruit_NeoPixel.h>


// All puzzle box definitions ----------------------------------------------
#define NUM_PUZZLES    3      // Number of puzzles to solve, change this depending on how many puzzles

// Puzzle Pins
#define PIN_PUZ0       A0     // Pin to indicate puzzle 0 solved
#define PIN_PUZ1       A1     // Pin to indicate puzzle 1 solved
#define PIN_PUZ2       A2     // Pin to indicate puzzle 2 solved

// Reset and Servo Pins
#define PIN_RESET           A7     // Pin to reset all puzzles to unsolved or solved
#define PIN_SERVO_LID       9      // Pin for the lid servo
#define PIN_SERVO_LID_PWR   5      // Pin for the lid servo power

// Arrays for LEDs and if puzzles are solved
const int puzzleLEDS[] = { PIN_PUZ0, PIN_PUZ1, PIN_PUZ2 };
boolean isPuz[] = { false, false, false };

// Servo
Servo myServo;                      // Servo Object
#define POS_SERVO_SOLVED    0       // Position servo should be in for box to be unlocked



// Steph's Pins ---------------------------------------------------------------
// Sensors
#define PIN_STAB_SWITCH       2      // Pin for lance stabbing, SWITCH0
#define PIN_CURTAIN_SWITCH    4      // Pin for curtain openning, SWITCH1
#define PIN_GAME_SWTICH       3      // Pin for game button, SWITCH2
#define PIN_NEOPIX            6      // Pin for Neopixels

// Steph's Variables -----------------------------------------------------------
// Neopixels
#define NUM_PIXELS            12
#define WINNING_PIXEL         7
Adafruit_NeoPixel pixels(NUM_PIXELS, PIN_NEOPIX, NEO_GRB + NEO_KHZ800);   // Neopixel object
int atPixel = 0;                      // variable for which pixel is lit up
boolean isButtonPress = false;        // flag for if the button is pressed
boolean isWin = false;                // flag for if the round is won
boolean isGameOn = false;             // flag for if the game is currently on
boolean isGameStart = true;           // flag for if it is the first time the game is started
int gameLevel = -1;                   // variable for game level
int countRound = 0;                   // variable for counting how many times the light has gone around



// Setup -------------------------------------------------------------------------
void setup() {
  initServo();                          // Initialize the lid servo first to make it not move
  initNeopixels();                      // Initialize Neopixels first to make sure 

  
  Serial.begin(9600);                   // initialize serial
  
  Serial.println("HELLO WORLD!");
  Serial.println("LNL/TA");
  Serial.println("Puzzle Box V02 - Stephanie Ayotte");
  Serial.println("V01_200407");
  Serial.println("\nInitializing...");


  pinMode(PIN_RESET, INPUT);              // Initialize the reset pin
  initPuzzleLEDs();                       // Initialize puzzle indicator LEDs
  initServo();                            // Initialize the lid servo

// Steph's Setup
  pinMode(PIN_STAB_SWITCH, INPUT);        // Initialize the tool switch
  pinMode(PIN_CURTAIN_SWITCH, INPUT);     // Initialize the tool switch
  initGame();                             // Initialize the speed sensor

  blinkStartLEDs();                       // Blink LEDs to indicate box is starting

  Serial.println("Starting...");
}



// Loop ---------------------------------------------------------------------------
void loop() {
// if puzzle 0 not solved, check stab switch, if HIGH, then solved
  if(!isPuz[0] && digitalRead(PIN_STAB_SWITCH)) {
    solvedPuzzle(0);
  }



// If puzzle 1 not solved, check curtain switch, if HIGH, then solved
  if(!isPuz[1] && !digitalRead(PIN_CURTAIN_SWITCH)) {
    solvedPuzzle(1);
  }


  
// If puzzle 2 not solved, check if playing the game, if made it through all levels, solved puzzle
  if(!isPuz[2]) {
    if(isGameOn) {
      playGame();
    }

    if(gameLevel==3) {
      solvedPuzzle(2);           
    }             
  }


  
// If reset button is hit, turn off the LCD and reset all puzzles
  if(analogRead(PIN_RESET)<100) {
    setToSolvedPuzzles();
  }


} // End Loop
