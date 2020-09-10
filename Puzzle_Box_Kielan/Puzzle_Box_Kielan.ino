// Include Libraries
#include <Wire.h>                 // i2C
#include <Servo.h>                // Servo
#include <Adafruit_LIS3DH.h>      // Accelerometer
#include <Adafruit_Sensor.h>      // Accelerometer
#include <OneWire.h>              // Temperature
#include <DallasTemperature.h>    // Temperature
#include <Adafruit_NeoPixel.h>    // Neopixels




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



// Kielan's Pins ---------------------------------------------------------------
// Sensors
#define PIN_SHOCK0            4      // Pin for shock sensor 0 signal, SHOCK00
#define PIN_SERVO_TEMP        5      // Pin for the lid servo
#define PIN_NEOPIX            6      // Pin for Neopixels
#define PIN_TEMP              7      // Pin for tempurature sensor signal,
#define PIN_SHOCK1            8      // Pin for shock sensor 1 signal, SHOCK01
#define PIN_SERVO_TEMP_PWR    A3     // Pin for the lid servo power

// Kielan's Variables -----------------------------------------------------------
unsigned long prevTime;      // Track time for accelerometer
unsigned long prevTime2;     // Track time for accelerometer

// Accelerometer
Adafruit_LIS3DH lis = Adafruit_LIS3DH();          // Accelerometer object
int countPos = 0;                                 // Count for which orientation need to go to next
#define NUM_POS 12                                // Number of positions needed to go to
const int POS[] = { 2,1,5,3,4,0,5,1,5,3,1,4 };    // Positions needed to be put in


// Tempurature Sensor
#define POS_TEMP_FINAL       90             // Final position for temperature servo
#define TARGET_TEMP          120            // Target temperature to get to

OneWire oneWire(PIN_TEMP);                  // Set oneWire pin
DallasTemperature tempSensors(&oneWire);    // Temperature Sensor object
int currTemp = 0;                           // Current temperature
boolean isEject = false;                    // Flag for if tempurature sensor is ejected
int startingTemp = 0;                       // Starting temperature of box

// Neopixels
#define NUM_PIXELS            4             // Number of neopixels
Adafruit_NeoPixel pixels(NUM_PIXELS, PIN_NEOPIX, NEO_GRB + NEO_KHZ800);   // Neopixel object



// Setup -------------------------------------------------------------------------
void setup() {

  Serial.begin(9600);                 // initialize serial
  
  Serial.println("HELLO WORLD!");
  Serial.println("LNL/TA");
  Serial.println("Puzzle Box V02 - Kielan Crockett Crow");
  Serial.println("V01_200811");
  Serial.println("\nInitializing...");

  pinMode(PIN_RESET, INPUT);          // Initialize the reset pin
  initPuzzleLEDs();                   // Initialize puzzle indicator LEDs
  initServo();                        // Initialize the lid servo
  

// Kielans's Setup
  initNeopixels();                    // Initialize Neopixels first to make sure 
  initAccelerometer();                // Initialize the accelerometer
  initShock();                        // Initialize the shock sensors
  initTemp();                         // Initialize the temperature sensor

  
  delay(500);                         // Delay to let everything settle
  blinkStartLEDs();                   // Blink LEDs to indicate box is starting
  
  prevTime = millis();                // Set time to now
  startingTemp = getTempurature();    // Set starting temperature
  
  Serial.println("Starting...");
}



// Loop ---------------------------------------------------------------------------
void loop() {

// If shock sensors, and puzzle 1 isn't solved, then puzzle is solved
  if(checkShock() && !isPuz[0]) {
    solvedPuzzle(0);
  }


  
// If puzzle 1 not solved, and puzzle 0 is solved, start the game
  if(!isPuz[1] && isPuz[0]) {
    playGame();       
  }



// If puzzle 2 not solved, and both other puzzles are, eject the temperature sensor and
// start monitoring it. If above target tempurature then solved puzzle 2
  if(!isPuz[2] && isPuz[0] && isPuz[1]) {
    if(!isEject) {
      moveServo(PIN_SERVO_TEMP, PIN_SERVO_TEMP_PWR, POS_TEMP_FINAL);
      isEject = true;
    }

    currTemp = getTempurature();
    setPixelTemp(currTemp);
    
    if(currTemp > TARGET_TEMP) {
      solvedPuzzle(2);
    }
  }



// If reset button is hit, turn off the LCD and reset all puzzles
  if(analogRead(PIN_RESET)<100) {
    finishedPuzzles();
  }



} // End Loop
