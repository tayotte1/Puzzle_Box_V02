// Initialize puzzle LED pins as output and set low
void initPuzzleLEDs() {
  for(int i=0; i<NUM_PUZZLES; i++) {          // Do this for the number of puzzles
    pinMode(puzzleLEDS[i], OUTPUT);           // Set pin to output mode, can set HIGH or LOW
    digitalWrite(puzzleLEDS[i],LOW);          // Set pin LOW to make sure LED is off
  }
}



// Method for if a puzzle is solved
void solvedPuzzle(int puz) {
  Serial.print("Solved puzzle: ");              // Debug printing
  Serial.print(puz);                            // Debug printing
  Serial.println("!");                          // Debug printing
  isPuz[puz] = true;                            // Set flag that puzzle is solved
  digitalWrite(puzzleLEDS[puz],isPuz[puz]);     // Turn LED ON
  if(isPuz[0] && isPuz[1] && isPuz[2]) {        // If solved all puzzles
    finishedPuzzles();                          // Run method for when finished with all puzzles
  }
}



// Sets all puzzles to solved
void setToSolvedPuzzles() {
  Serial.println("Setting Puzzles to Finished");      // Debug Printing
  for(int i=0; i<NUM_PUZZLES; i++) {                  // Do this for number of puzzles time
    solvedPuzzle(i);                                  // Sets flag as unsolved
  }  
}



// Move servo to unlock lid and display finished!
void finishedPuzzles() {
  Serial.println("YAY YOU FINISHED ALL THE PUZZLES!");    // Debug Printing
  blinkLEDs();                                            // Blink the LEDs 
  moveServo(PIN_SERVO_LID, POS_SERVO_SOLVED);             // Move the servo to unlock the lid
  while(1) {                                              // Repeat forever
    moveServo(PIN_SERVO_LID, POS_SERVO_SOLVED);           // Try to move servo again just incase it was stuck
    delay(5000);                                          // Delay
  }  
}



// Blink all puzzle leds, end on HIGH
void blinkLEDs() {
  for (int x=0; x<5; x++) {                               // Blink puzzle LEDs 5 times
    for(int i=0; i<NUM_PUZZLES; i++) {                    // Do this for the number of puzzles
      digitalWrite(puzzleLEDS[i], LOW);                   // Set pin LOW to turn LED off
    }
    delay(250);                                           // Delay
    for(int i=0; i<NUM_PUZZLES; i++) {                    // Do this for the number of puzzles
      digitalWrite(puzzleLEDS[i], HIGH);                  // Set pin HIGH to turn LED on
    }
    delay(650);                                           // Delay
  }
}

// Blink all puzzle leds, end on LOW
void blinkStartLEDs() {
  for (int x=0; x<3; x++) {                               // Blink puzzle LEDs 5 times
    for(int i=0; i<NUM_PUZZLES; i++) {                    // Do this for the number of puzzles
      digitalWrite(puzzleLEDS[i], HIGH);                   // Set pin LOW to turn LED off
    }
    delay(650);                                           // Delay
    for(int i=0; i<NUM_PUZZLES; i++) {                    // Do this for the number of puzzles
      digitalWrite(puzzleLEDS[i], LOW);                  // Set pin HIGH to turn LED on
    }
    delay(250);                                           // Delay
  }
}
