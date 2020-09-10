// Initialize the accelerometer
void initAccelerometer() {
  if (! lis.begin(0x18)) {                  // Start accelerometer at address 0x18, if can't start, blink the LEDs 
    Serial.println("Couldnt start");        // Debug Printing
    while (1) {                             // Do this forever
      blinkLEDs();                          // Blink LEDs
      delay(1000);                          // Delay 1 second
    }
  }
  Serial.println("LIS3DH found!");          // Debug Printing
  
  lis.setRange(LIS3DH_RANGE_4_G);           // Set the accelerometer range: 2, 4, 8 or 16 G!
  
  Serial.print("Range = ");                 // Debug Printing
  Serial.print(2 << lis.getRange());        // Debug Printing
  Serial.println("G");                      // Debug Printing
}



// Get new accelerometer Data and check if dropped
int checkAccelerometer() {
  lis.read();                               // Get X Y and Z data at once
// Then print out the raw data
//  Serial.print("X:  "); Serial.print(lis.x); 
//  Serial.print("  \tY:  "); Serial.print(lis.y); 
//  Serial.print("  \tZ:  "); Serial.print(lis.z); 

  sensors_event_t event;      // Set new event
  lis.getEvent(&event);       // Get event from latest reading, this converts raw data into normalized data in m/s^2
  
// Then print out the event data in m/s^2
//  Serial.print("X: "); Serial.print(event.acceleration.x);
//  Serial.print(" \tY: "); Serial.print(event.acceleration.y); 
//  Serial.print(" \tZ: "); Serial.print(event.acceleration.z); 
//  Serial.print("        ");
  
  double x = event.acceleration.x;    // Set the x acceleration
  double y = event.acceleration.y;    // Set the y acceleration
  double z = event.acceleration.z;    // Set the z acceleration
  int curPos = -1;                    // Set current position to -1


// Figure out which orientation the box is in based on acceleration data
  if( x < 10.5 && x > 8.7) {
    curPos = 3;
    Serial.print("X is up, curPos: ");
    Serial.print(curPos);
    Serial.print(", ");
  }
  else if( x > -10.5 && x < -8.7) {
    curPos = 1;
    Serial.print("X is down, curPos: ");
    Serial.print(curPos);
    Serial.print(", ");
  }
  else if( y < 10.5 && y > 8.7) {
    curPos = 0;
    Serial.print("Y is up, curPos: ");
    Serial.print(curPos);
    Serial.print(", ");
  }
  else if( y > -10.5 && y < -8.7) {
    curPos = 2;
    Serial.print("Y is down, curPos: ");
    Serial.print(curPos);
    Serial.print(", ");
  }
  else if( z < 10.5 && z > 8.7) {
    curPos = 5;
    Serial.print("Z is up, curPos: ");
    Serial.print(curPos);
    Serial.print(", ");
  }
  else if( z > -10.5 && z < -8.7) {
    curPos = 4;
    Serial.print("Z is down, curPos: ");
    Serial.print(curPos);
    Serial.print(", ");
  } else {
//    Serial.println("");
  }

  return curPos;            // Return the current orientation of the box
}


// play the game of orientation based on neopixels
void playGame() {
  int c = 0;                            // count for correct orientation
  rainbowCycle(10,3);                   // show pretty colors to start
  
  while(countPos < NUM_POS) {           // while we haven't correctly done all positions
    prevTime = millis();                // set time to now
    setPosPixel(POS[countPos]);         // set the neopixel on
    c = 0;                              // set count to 0

    while(checkAccelerometer() != POS[countPos]) {          // while we're not at the correct orientation
//      Serial.print("countPos: ");                         // debug printing
//      Serial.print(countPos);
//      Serial.print(",   POS[countPos]: ");
//      Serial.println(POS[countPos]);
      if(millis()-prevTime > (NUM_POS-countPos)*1000) {     // set a timout because need to solve the round quickly
        Serial.println("Timed Out.");                       // debug printing
        countPos = 0;                                       // reset round count
        flashPixels(3,255,0,0);                             // flash red to indicate too slow
        return;                                             // return to main loop to restart game
      }
    }
    for(int i=0; i<8; i++) {                                // if we're at the position check it 8 times
      if(checkAccelerometer() == POS[countPos]) {           // if at position increase count
        c++;
      }
    }
    if(c > 5) {                                             // if 5 of 8 were correct position
      countPos++;                                           // go to next round
    }
  }

  solvedPuzzle(1);                      // if made it here, solved the puzzle and finished the game
  rainbowCycle(10,3);                   // show pretty colors to indicate finished
  
  pixels.clear();                       // Clear the neopixels
  pixels.show();                        // Send clear command
}


// function to set the which neopixel for orientation for the game
void setPosPixel(int p) {
  pixels.clear();                       // Clear the neopixels
  pixels.show();                        // Send clear command

  if(p == 4) {                          // if right side up set all pixels
    setAllPixel(255, 50, 0);
  } else if(p == 5){                    // if upside down set all pixels
    setAllPixel(0, 0, 255);
  } else{                               // else set single side
    setPixel(p, 0, 255, 0);
  }
}
