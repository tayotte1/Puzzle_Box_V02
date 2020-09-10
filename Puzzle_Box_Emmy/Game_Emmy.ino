// Initialize Game
void initGame() {
  for(int i=0; i<8; i++) {
    pinMode(PINS_GAME[i], INPUT);                           // Initialize the game button pins
  }

  if(readButtonCount() == 1) {                              // If read 2 buttons being pressed on initialization then
    Serial.println("HARD MODE ACTIVATED.");                 // Debug Print
    difficulty = 1;                                         // Set difficulty to 1
    flashRainbow(3);                                        // Flash to indicate Hard difficulty
  } else if(readButtonCount() == 2){                         // If read more than 2 buttons being pressed on initialization then
    Serial.println("EXTREME MODE ACTIVATED.");              // Debug Print
    difficulty = 2;                                         // Set difficulty to 2
    flashRainbow(5);                                        // Flash to indicate Extreme difficulty
  } else {                                                  
    Serial.println("NORMAL MODE ACTIVATED.");               // Debug Print
    difficulty = 0;                                         // Set difficulty to 0
    flashRainbow(2);                                        // Flash to indicate Normal difficulty
  }
}



// Read all game buttons and count how many are pressed
int readButtonCount() {
  int count = 0;                              // Variable to track how many buttons are pressed
  for(int i=0; i<8; i++) {                    // Run loop for how many buttons there are attached to digital pins
    if(digitalRead(PINS_GAME[i])){            // If pin is HIGH
      count++;                                // Increment count
    }
    if(analogRead(PINS_GAME[8]) > 150) {      // If button attached to analog pin is high
      count++;                                // Increment count
    }
  }
  
  return count;                               // Return
}


// Read all buttons for game to see which one is being pressed
int readButtons() {
  unsigned long prevTimeRead = millis();        // Track time for reading buttons to timeout of function
  Serial.println("Reading Buttons");            // Debug Print
  while(1) {                                    // Run forever
    for(int i=0; i<8; i++) {                    // Run loop for how many buttons there are attached to digital pins
      if(digitalRead(PINS_GAME[i])) {           // If pin is HIGH
        Serial.print("Read pin: ");             // Debug Print
        Serial.println(i);                      // Debug Print
        return i;                               // Return pin that is HIGH
      }
    }
    if(analogRead(PINS_GAME[8]) > 150) {        // If button attached to analog pin is high
      return 8;                                 // Return pin 8
    }
    
    if(millis()-prevTimeRead > 20000) {         // If we've been reading pins for 20 seconds and no buttons have been pressed
      return -1;                                // Return from function with error
    }
  }
  return -1;                                    // Return from function with error
}


// Flash round pattern
void showRoundPattern(int seq[], int len, int dON, int dOFF) {
  pixels.clear();                               // Set all pixel colors to 'off'
  pixels.show();                                // Send the clear command
  int pix = -1;                                 // Initialize pixel number
  int rP, gP, bP;                               // Initialize r,g,b values

  Serial.println("Showing Round");
  
  for(int i=0; i<len; i++) {                    // For length of sequence, turn on the desired pixel and delay
    pix = seq[i];                               // Set pixel to the sequence number
    rP = 0;                                     // Set red value
    gP = 255;                                   // Set green value
    bP = 0;                                     // Set blue value
    
    
    if(seq[i] == -1) {
      pix = random(9);                          // Set random decoy pixel (0-9)
      rP = 255;                                 // Set red value for decoy
      gP = 0;                                   // Set green value for decoy
      bP = 0;                                   // Set blue value for decoy
      Serial.println("Decoy");                  // Debug Print
    }

    Serial.print("pix, rP, gP, bP: ");          // Debug Print of what pixel is being lit up what color
    Serial.print(pix);
    Serial.print(", ");
    Serial.print(rP);
    Serial.print(", ");
    Serial.print(gP);
    Serial.print(", ");
    Serial.println(bP);
    
    setPixel(pix, rP, gP, bP);                  // Set next pixel in sequence on
    delay(dON);                                 // Delay for set time
    pixels.clear();                             // Set all pixel colors to 'off'
    pixels.show();                              // Send the clear command
    delay(dOFF);                                // Delay for set time
  }
  Serial.println("================================\n");   // Debug Print indicator of exit function
}




// Game logic
void playGame() {
  
  switch (gameLevel) {                              // Switch case based on what level of the game they're at
    case -1:                                        // If level -1, we're starting the game
      flashPixels(3,0,0,255);                       // Set pretty colors for initialization
      gameLevel = 0;                                // Set gameLevel to first level
      Serial.println("Case -1");
      break;
      
    case 0:                                                                               // If level 0, first round of game, easy level
      Serial.println("Start Round 0");
      if(difficulty == 2) {
        playRound(ROUND_0E, ROUND_0E_LENGTH, ROUND_0E_SPEED_ON, ROUND_0E_SPEED_OFF);      // Play round 0 Extreme Mode
      } else if(difficulty == 1){
        playRound(ROUND_0H, ROUND_0H_LENGTH, ROUND_0H_SPEED_ON, ROUND_0H_SPEED_OFF);      // Play round 0 Hard Mode
      } else {
        playRound(ROUND_0, ROUND_0_LENGTH, ROUND_0_SPEED_ON, ROUND_0_SPEED_OFF);          // Play round 0
      }
      break;
      
    case 1:                                                                               // If level 1, second round of game, medium level
      Serial.println("Start Round 1");
      if(difficulty == 2) {
        playRound(ROUND_1E, ROUND_1E_LENGTH, ROUND_1E_SPEED_ON, ROUND_1E_SPEED_OFF);      // Play round 1 Extreme Mode
      } else if(difficulty == 1){
        playRound(ROUND_1H, ROUND_1H_LENGTH, ROUND_1H_SPEED_ON, ROUND_1H_SPEED_OFF);      // Play round 1 Hard Mode
      } else {
        playRound(ROUND_1, ROUND_1_LENGTH, ROUND_1_SPEED_ON, ROUND_1_SPEED_OFF);          // Play round 1
      }
      break;
      
    case 2:                                                                               // If level 2, third round of game, hard level
      Serial.println("Start Round 2");
      if(difficulty == 2) {
        playRound(ROUND_2E, ROUND_2E_LENGTH, ROUND_2E_SPEED_ON, ROUND_2E_SPEED_OFF);      // Play round 2 Extreme Mode
      } else if(difficulty == 1){
        playRound(ROUND_2H, ROUND_2H_LENGTH, ROUND_2H_SPEED_ON, ROUND_2H_SPEED_OFF);      // Play round 2 Hard Mode
      } else {
        playRound(ROUND_2, ROUND_2_LENGTH, ROUND_2_SPEED_ON, ROUND_2_SPEED_OFF);          // Play round 2
      }
      break;
      
    case 3:                                                                               // If level 3, third round of game, hardest level
      Serial.println("Start Round 3");
      if(difficulty == 2) {
        playRound(ROUND_3E, ROUND_3E_LENGTH, ROUND_3E_SPEED_ON, ROUND_3E_SPEED_OFF);      // Play round 3 Extreme Mode
      } else if(difficulty == 1){
        playRound(ROUND_3H, ROUND_3H_LENGTH, ROUND_3H_SPEED_ON, ROUND_3H_SPEED_OFF);      // Play round 3 Hard Mode
      } else {
        playRound(ROUND_3, ROUND_3_LENGTH, ROUND_3_SPEED_ON, ROUND_3_SPEED_OFF);          // Play round 3
      }
      break;
      
    default:                                        // If any other level, default to turning everything off
      cancelGame();                                 // Cancel playing the game
      break; 
  }
}


/* A round of the game
** Parameters:
** roundSeq, int array for pattern sequence
** roundLen, int length of the round
** roundSpeedOn, int for length of time to flash Neopixel on
** roundSpeedOff, int for length of time to flash Neopixel off
*/
void playRound(int roundSeq[], int roundLen, int roundSpeedOn, int roundSpeedOff) {
  prevTime = millis();                          // Set the prevTime to now
      
  showRoundPattern(roundSeq, roundLen, roundSpeedOn, roundSpeedOff);        // Show the sequence needed
  
  if(checkRound(roundSeq, roundLen)) {          // If returned true from checkRound, won the round
    Serial.print("Won Round ");                 // Debug Print
    Serial.print(gameLevel);                    // Debug Print
    Serial.println("!");                        // Debug Print
    gameLevel = gameLevel + 1;                  // Increase level
    flashPixels(3,0,0,255);                     // Flash before next round
  } else {                                      // Else lost
    Serial.print("Lost Round");                 // Debug Print
    Serial.print(gameLevel);                    // Debug Print
    Serial.println("!");                        // Debug Print
    gameLevel = -1;                             // Set gameLevel back to -1
    flashPixels(3,255,0,0);                     // Flash red to indicate wrong
    delay(1000);                                // Delay 1 second
  }
  Serial.println("End Round");
  Serial.print("gameLevel: ");
  Serial.println(gameLevel);
  return;
}




/* A check the round of the game
** Parameters:
** seq, int array for pattern sequence
** len, int for how long the array is
*/
boolean checkRound(int seq[], int len) {
  for(int j=0; j<len; j++) {                        // For length of sequence
    if(seq[j] != -1) {                              // If decoy in sequence then ignore
      if(seq[j] != readButtons()) {                 // If incorrect button is pressed
        Serial.print("Failed game on round: ");     // Debug printing
        Serial.print(gameLevel);                    // Debug printing
//        unSolvePuzzle();                          // Unsolve puzzles
        gameLevel = -1;                             // Go back to beginning level
        return false;                               // Return lost
      }
      while(readButtonCount()>0) {                  // Else correct button was pressed and need to wait until no buttons are pressed
        checkTime();                                // Check for timeout
      }
    }
  }
  return true;                                      // If made it here, then all correct buttons were pressed and won round
}




// Checks if its been too long
void checkTime() {
  if(millis() - prevTime > 40000) {
    cancelGame();
  }
  if(analogRead(PIN_RESET)<100) {
    setToSolvedPuzzles();
  }
}

// Turns the game off and resets to starting level
void cancelGame() {
  gameLevel = -1;                           // Set level back to start
  isGameOn = false;                         // Set flag for game being off
  pixels.clear();                           // Clear the neopixels
  pixels.show();                            // Send command to neopixels
}
