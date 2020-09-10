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




// Move servo to unlock lid and display finished!
void finishedPuzzles() {
  Serial.println("YAY YOU FINISHED ALL THE PUZZLES!");                // Debug Printing
  blinkLEDs();                                                        // Blink the LEDs 
  moveServo(PIN_SERVO_LID, PIN_SERVO_LID_PWR, POS_SERVO_SOLVED);      // Move the servo to unlock the lid
  prevTime = millis();                                                // Set time to now
  while(1) {                                                          // Repeat forever
    rainbowAll();                                                     // Rainbow colors on neopixels
    if(millis()-prevTime > 30000) {                                   // If more than 30 sec pass
      moveServo(PIN_SERVO_LID, PIN_SERVO_LID_PWR, POS_SERVO_SOLVED);  // Try to move servo again just incase it was stuck
      prevTime = millis();                                            // Set time to now
    }
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
      digitalWrite(puzzleLEDS[i], HIGH);                  // Set pin HIGH to turn LED on
    }
    setRainbow(x*50);
    delay(650);                                           // Delay
    for(int i=0; i<NUM_PUZZLES; i++) {                    // Do this for the number of puzzles
      digitalWrite(puzzleLEDS[i], LOW);                   // Set pin LOW to turn LED off
    }
    pixels.clear();                                       // Clear the neopixels
    pixels.show();                                        // Send clear command
    delay(250);                                           // Delay
  }
}
