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
void checkAccelerometer() {
  lis.read();                               // Get X Y and Z data at once
// Then print out the raw data
//  Serial.print("X:  "); Serial.print(lis.x); 
//  Serial.print("  \tY:  "); Serial.print(lis.y); 
//  Serial.print("  \tZ:  "); Serial.print(lis.z); 

  sensors_event_t event;      // Set new event
  lis.getEvent(&event);       // Get event from latest reading, this converts raw data into normalized data in m/s^2
  
// Then print out the event data in m/s^2
//  Serial.print("\t\tX: "); Serial.print(event.acceleration.x);
//  Serial.print(" \tY: "); Serial.print(event.acceleration.y); 
//  Serial.print(" \tZ: "); Serial.print(event.acceleration.z); 
//  Serial.println(" m/s^2 ");

  double magnitude = sqrt(sq(event.acceleration.x) + sq(event.acceleration.y) + sq(event.acceleration.z));    // Calculate the magnitude of the acceleration vector
  Serial.print("Magnitude: ");        // Debug Printing
  Serial.println(magnitude);          // Debug Printing
  if(magnitude < 1) {                 // If vector is less than 1, box has been dropped, 0 acceleration would be complete free fall
    Serial.println("-------------------------------------Dropped");   // Debug Printing
    countDrop++;                      // Increase drop count
    Serial.print("countDrop: ");
    Serial.println(countDrop);
  }else {                             // Else box wasn't dropped
    Serial.println("Nope");           // Debug Printing
  }


// Check the drop count
  if(millis()-prevTimeAccel > 400) {    // If its been more than 100 milliseconds since last check, check how many drop counts
    if(countDrop > 2) {                 // If count is greater than 3, box was definitely dropped
      isDropped = true;                 // Set flag to true
    }
    countDrop = 0;                      // Reset count
    prevTimeAccel = millis();           // Set time to now
  }
}
