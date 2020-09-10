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
#define PIN_RESET           A7      // Pin to reset all puzzles to unsolved or solved
#define PIN_SERVO_LID       9       // Pin for the lid servo
#define PIN_SERVO_LID_PWR   10      // Pin for the lid servo power

// Arrays for LEDs and if puzzles are solved
const int puzzleLEDS[] = { PIN_PUZ0, PIN_PUZ1, PIN_PUZ2 };
boolean isPuz[] = { false, false, false };

// Servo
Servo myServo;                      // Servo Object
#define POS_SERVO_SOLVED    0       // Position servo should be in for box to be unlocked



// Emmy's Pins ---------------------------------------------------------------
// Pizza
#define PIN_PIZZA_SWITCH      A6     // Pin for PIZZA, SWITCH09
#define PIN_SERVO_PIZZA       5      // Pin for pizza servo, SERVO_PUZ_01

// Keyboard Keys
#define PIN_GAME_0            2       // Pin for playing the game, SWITCH00
#define PIN_GAME_1            7       // Pin for playing the game, SWITCH04
#define PIN_GAME_2            12      // Pin for playing the game, SWITCH07
#define PIN_GAME_3            3       // Pin for playing the game, SWITCH01
#define PIN_GAME_4            8       // Pin for playing the game, SWITCH05
#define PIN_GAME_5            13      // Pin for playing the game, SWITCH08
#define PIN_GAME_6            4       // Pin for playing the game, SWITCH02
#define PIN_GAME_7            11      // Pin for playing the game, SWITCH06
#define PIN_GAME_8            A3      // Pin for playing the game, SWITCH09


// Neopixels
#define PIN_NEOPIX            6       // Pin for Neopixels

// Touch Sensors
#define PIN_TOUCH0            A4      // Pin for touch 0 signal, TOUCH3
#define PIN_TOUCH1            A5      // Pin for touch 1 signal, TOUCH4

// Emmy's Variables -----------------------------------------------------------
//Pizza
#define POS_PIZZA_INIT        40
#define POS_PIZZA_FINAL       140

// Neopixels
#define NUM_PIXELS            9
Adafruit_NeoPixel pixels(NUM_PIXELS, PIN_NEOPIX, NEO_GRB + NEO_KHZ800);
const int PINS_GAME[] = {PIN_GAME_0,PIN_GAME_1,PIN_GAME_2,PIN_GAME_3,PIN_GAME_4,PIN_GAME_5,PIN_GAME_6,PIN_GAME_7,PIN_GAME_8};
boolean isButton[] = {false,false,false,false,false,false,false,false,false};

const int ROUND_0[] = {4,8,1,3,7};
const int ROUND_1[] = {5,0,-1,3,4,-1,1};
const int ROUND_2[] = {6,-1,4,8,-1,6,2,5,0};
const int ROUND_3[] = {-1,1,7,3,-1,2,8,5,-1,4};

#define ROUND_0_LENGTH    5
#define ROUND_1_LENGTH    7
#define ROUND_2_LENGTH    9
#define ROUND_3_LENGTH    10

#define ROUND_0_SPEED_ON    800
#define ROUND_0_SPEED_OFF   400
#define ROUND_1_SPEED_ON    600
#define ROUND_1_SPEED_OFF   350
#define ROUND_2_SPEED_ON    500
#define ROUND_2_SPEED_OFF   300
#define ROUND_3_SPEED_ON    300
#define ROUND_3_SPEED_OFF   250


const int ROUND_0H[] = {-1,-1,5,8,0,-1,1,2,1,4};
const int ROUND_1H[] = {8,3,4,7,-1,-1,-1,1,0,2,6,-1,1};
const int ROUND_2H[] = {6,-1,2,-1,8,-1,5,-1,3,-1,1,-1,4,-1,0,-1,7,-1,1};
const int ROUND_3H[] = {0,-1,-1,1,2,3,-1,4,-1,5,6,-1,7,-1,8};

#define ROUND_0H_LENGTH    10
#define ROUND_1H_LENGTH    13
#define ROUND_2H_LENGTH    19
#define ROUND_3H_LENGTH    15

#define ROUND_0H_SPEED_ON    450
#define ROUND_0H_SPEED_OFF   300
#define ROUND_1H_SPEED_ON    400
#define ROUND_1H_SPEED_OFF   300
#define ROUND_2H_SPEED_ON    300
#define ROUND_2H_SPEED_OFF   250
#define ROUND_3H_SPEED_ON    200
#define ROUND_3H_SPEED_OFF   150


const int ROUND_0E[] = {-1,4,-1,-1,-1,-1,4,6,2,1,7,-1,-1,8,-1,2};
const int ROUND_1E[] = {3,6,-1,-1,1,8,-1,0,-1,3,-1,-1,6,-1,7,2,-1,-1,-1};
const int ROUND_2E[] = {2,-1,5,2,-1,-1,-1,3,8,0,-1,7,-1,-1,1,8,-1,4,-1};
const int ROUND_3E[] = {0,-1,-1,1,2,6,8,2,3,-1,-1,-1,-1,-1,-1,1,6,-1,-1,7,-1,2,5,4,7,3,-1};

#define ROUND_0E_LENGTH    16
#define ROUND_1E_LENGTH    19
#define ROUND_2E_LENGTH    19
#define ROUND_3E_LENGTH    27

#define ROUND_0E_SPEED_ON    250
#define ROUND_0E_SPEED_OFF   200
#define ROUND_1E_SPEED_ON    200
#define ROUND_1E_SPEED_OFF   150
#define ROUND_2E_SPEED_ON    150
#define ROUND_2E_SPEED_OFF   100
#define ROUND_3E_SPEED_ON    100
#define ROUND_3E_SPEED_OFF   50


boolean isWin = false;
boolean isGameOn = false;
boolean isGameStart = true;
int difficulty = 0;
int gameLevel = -1;
int countRound = 0;
unsigned long prevTime;       // Track time for game round




// Setup -------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);                 // initialize serial
  
  Serial.println("HELLO WORLD!");
  Serial.println("LNL/TA");
  Serial.println("Puzzle Box V02 - Emily Mak");
  Serial.println("V01_200719");
  Serial.println("\nInitializing...");

  initNeopixels();                      // Initialize Neopixels first to make sure they're off as quickly as possible
  
  pinMode(PIN_RESET, INPUT);            // Initialize the reset pin
  initPuzzleLEDs();                     // Initialize puzzle indicator LEDs
  initServo();                          // Initialize the lid servo

// Emmy's Setup
  pinMode(PIN_PIZZA_SWITCH, INPUT);     // Initialize the pizza pin
  initGame();                           // Initialize the speed sensor
  initTouchSensors();                   // Initialize touch sensors

  Serial.println("Starting...");
}



// Loop ---------------------------------------------------------------------------
void loop() {
  
// if puzzle 0 not solved, check pizza switch, if HIGH, then solved
  if(!isPuz[0] && analogRead(PIN_PIZZA_SWITCH) > 300) {
    Serial.println("Pizza time!");
    moveServo(PIN_SERVO_PIZZA, POS_PIZZA_FINAL);   // Move pizza servo to solved position
    solvedPuzzle(0);
  }


  
// If puzzle 1 not solved, check if playing the game, if made it through all levels, solved puzzle
  if(!isPuz[1]) {
    if(readButtonCount()>0) {
      Serial.println("Start Game");
      do {
        playGame();
      }while(gameLevel<4 && gameLevel != -1);
      Serial.println("Ended Game");
    }
    if(gameLevel == 4) {
      solvedPuzzle(1);                            // Turn LED ON
    }     
  }


// if puzzle 2 is not solved, check touch sensors, if yes then puzzle 2 is solved
  if(!isPuz[2]) {
    if(checkTouchSensors()) {
      solvedPuzzle(2);
    }
  }


  
  
// If reset button is hit, turn off the LCD and reset all puzzles
  if(analogRead(PIN_RESET)<100) {
    setToSolvedPuzzles();
    Serial.println("Got Magnet");
  }

  delay(200);

} // End Loop
