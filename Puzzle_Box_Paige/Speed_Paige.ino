// Initialize Speed Sensor
void initSpeed() {
  pinMode(PIN_SPEED, INPUT_PULLUP);                                         // Initialize the speed sensor pin switch
  attachInterrupt(digitalPinToInterrupt(PIN_SPEED), gotSpeed, CHANGE);      // Initialize the interrupt on pin, with routine, set on CHANGE
}



// Interrupt Service routine
void gotSpeed() {
  countSpeed++;                       // Increase speed count
  Serial.print("countSpeed: ");       // Debug Printing
  Serial.println(countSpeed);         // Debug Printing
}



// Check if the speed sensor has been spinning
void checkSpeed() {
  if(millis()-prevTimeSpeed > 500) {    // If its been 500 milliseconds since last check, check if was spinning
    if(countSpeed > 4) {                // If got 4 counts, it was spinning
      isSpinning = true;                // Set flag
    }
    countSpeed = 0;                     // Reset count
    prevTimeSpeed = millis();           // Set time to now
  }
}
