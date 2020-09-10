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
  
  double x = event.acceleration.x;
  double y = event.acceleration.y;
  double z = event.acceleration.z;
  int curPos = -1;

  if( x < 10.5 && x > 8.7) {
//    Serial.println("X is up");
    curPos = 1;
  }
  else if( x > -10.5 && x < -8.7) {
//    Serial.println("X is down");
    curPos = 2;
  }
  else if( y < 10.5 && y > 8.7) {
//    Serial.println("Y is up");
    curPos = 3;
  }
  else if( y > -10.5 && y < -8.7) {
//    Serial.println("Y is down");
    curPos = 4;
  }
  else if( z < 10.5 && z > 8.7) {
//    Serial.println("Z is up");
    curPos = 5;
  }
  else if( z > -10.5 && z < -8.7) {
//    Serial.println("Z is down");
    curPos = 6;
  } else {
//    Serial.println("");
  }

  return curPos;
}


// checks for if the box is in the correct orientation for it to indicate the start of the routine
void checkStartRoutine() {
  if( checkAccelerometer() == POS[countPos] ) {
    Serial.println("In handstand 1");
    if( millis()-prevTimeAccel > 2000 ) {
      countPos++;
      Serial.println("Start Routine ================================================");
      routine();
    }
  } else {
    prevTimeAccel = millis();
  }
}



// function to track the routine of the box
void routine() {
  prevTimeAccel = millis();
  int p = -1;
  
  while(millis() - prevTimeAccel < 30000) {
    p = checkAccelerometer();
    Serial.print("p = ");
    Serial.print(p);
    Serial.print(", countPos = ");
    Serial.print(countPos);
    Serial.print(", POS[countPos] = ");
    Serial.println(POS[countPos]);
    if(p == POS[countPos]) {
      Serial.println("Got position!");
      if(countPos == 12) {
        prevTimeAccel2 = millis();
        int c = 0;
        while(p == POS[countPos] && c < 3) {
          delay(20);
          Serial.println("In Second Handstand...");
          p = checkAccelerometer();
          
          if(p != POS[countPos]){
            c++;
            Serial.println("Misstep in handstand 2...");
            p = POS[countPos];
          }
        }
        if(millis()-prevTimeAccel2 < 2000) {
          countPos=0;
          Serial.println("Not long enough handstand!===================================");
          return;
        }
        Serial.println("Successfully completed handstand!+++++++++++++++++++++++++++++++");
      }
      
      countPos++;
      prevTimeAccel = millis();
      if(countPos == NUM_POS) {
        solvedPuzzle(2);
        return;
      }
    } else if (p == -1) {
      // ignore it.
    } else if (p == POS[countPos-1]) {
      Serial.println("In previous position, ignoring");
    }else {
      Serial.println("Failed routine due to misstep");
      countPos = 0;
      return;
    }
  }
  prevTimeAccel = millis();
  countPos = 0;
  Serial.println("Timed out of routine");
}
