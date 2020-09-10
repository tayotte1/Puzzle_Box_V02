// Initialize Game Switch
void initGame() {
  pinMode(PIN_GAME_SWTICH, INPUT_PULLUP);                                            // Initialize the game button pin switch
  attachInterrupt(digitalPinToInterrupt(PIN_GAME_SWTICH), buttonPress, FALLING);     // Initialize the interrupt on pin, with routine, set on FALLING
}



// Interrupt Service Routine for game button
void buttonPress() {
  Serial.println("Button Press");
  if(!isPuz[2]) {                         // If haven't won the game
    if(isGameOn) {                        // If the game is on and we're playing
      isButtonPress = true;               // Set flag to say we pressed the button
      if(atPixel == WINNING_PIXEL) {      // If the light is on the correct pixel
        isWin = true;                     // Set flag to say won the round
        countRound = 0;
      }
    } else {                              // Else turn the game on
      isGameOn = true;                    // Set flag to say game is on
      isButtonPress = false;              // Set flag to not have it think we tried to play the game already
      countRound = 0;                     // Set flag that we're starting
      isWin = false;                      // Set flag to say didn't win the round
    }
  }
}



// Game logic
void playGame() {
  switch (gameLevel) {                              // Switch case based on what level of the game they're at
    case -1:                                        // If leve -1, we're starting the game
      rainbowCycle(2,4);                            // Set pretty colors for initialization
      gameLevel = 0;                                // Set gameLevel to first level
      countRound = 0;                               // Reset countRound
      break;
      
    case 0:                                         // If level 0, first round of game, easy level
      isButtonPress = false;
      while(gameLevel==0) {                         // Run infinitely while we're on level 0, makes it so there isn't a delay in the leds
        gameRound(pixels.Color(255, 0, 0), 200);    // Run a round of the game with color and delay
        countRound++;                               // Count the round so we don't get stuck here forever
        
        if(countRound == 20) {                      // If 20 rounds have gone by and no button press, then turn game off
          cancelGame();                             // Cancel playing the game
        }
      }
      break;
      
    case 1:                                         // If level 1, second round of game, medium level
      isButtonPress = false;
      while(gameLevel==1) {                         // Run infinitely while we're on level 1, makes it so there isn't a delay in the leds
        gameRound(pixels.Color(240, 50, 0), 130);   // Run a round of the game with color and delay
        countRound++;                               // Count the round so we don't get stuck here forever
        
        if(countRound == 30) {                      // If 30 rounds have gone by and no button press, then turn game off
          cancelGame();                             // Cancel playing the game
        }
      }
      break;
      
    case 2:                                         // If level 2, third round of game, hard level
      isButtonPress = false;
      while(gameLevel==2) {                         // Run infinitely while we're on level 1, makes it so there isn't a delay in the leds
        gameRound(pixels.Color(230, 130, 0), 75);  // Run a round of the game with color and delay
        countRound++;                               // Count the round so we don't get stuck here forever
        
        if(countRound == 40) {                      // If 40 rounds have gone by and no button press, then turn game off
          cancelGame();                             // Cancel playing the game
        }
      }
      break;
      
    default:                                        // If any other leve, default to turning everything off
      cancelGame();                                 // Cancel playing the game
      break; 
  }
}



/* A round of the game
** Parameters:
** c, uint32_t of the color for the round
** wait, integer for how long to wait before moving pixels in the round
*/
void gameRound(uint32_t c, int wait) {
  for(uint16_t i=0; i<pixels.numPixels(); i++) {      // For the number of pixels
    atPixel = i;                                      // Set flag for which pixel we're at
    Serial.print("atPixel: ");                        // Debug Printing
    Serial.println(atPixel);                          // Debug Printing
    pixels.clear();                                   // Clear all pixels
    pixels.setPixelColor(i, c);                       // Set the correct pixel to color
    pixels.show();                                    // Send updated color

    if(isButtonPress) {                               // If the button was pressed
      if(isWin) {                                     // If it was a winning button press
        gameLevel++;                                  // Increase the level
        rainbowCycle(2,4);                            // Show happy rainbow

      } else {                                        // Else was not a winning button press
        flashPixels(3, 255, 0, 0);                    // Flash angry three times
      }
      isButtonPress = false;                          // Set flag that says we've acknowledged the button press
      isWin = false;                                  // Reset flag
      return;                                         // Return out of the round
    }
    delay(wait);                                      // Delay for wait milliseconds
  }
}



// Turns the game off and resets to starting level
void cancelGame() {
  gameLevel = -1;                           // Set level back to start
  isGameOn = false;                         // Set flag for game being off
  pixels.clear();                           // Clear the neopixels
  pixels.show();                            // Send command to neopixels
}
