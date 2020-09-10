// Initialize the rotary encoder pins
void initRotaryEncoder() {
  pinMode(PIN_ROT_A, INPUT_PULLUP);       // Set pin to input with pullup resistor
  pinMode(PIN_ROT_B, INPUT_PULLUP);       // Set pin to input with pullup resistor
  pinMode(PIN_ROT_SWITCH, INPUT);         // Set pin to input

  attachInterrupt(digitalPinToInterrupt(PIN_ROT_A), updateEncoder, CHANGE);   // Attach interupt to pin, run updateEncoder when triggered, trigger on change event
  attachInterrupt(digitalPinToInterrupt(PIN_ROT_B), updateEncoder, CHANGE);   // Attach interupt to pin, run updateEncoder when triggered, trigger on change event
}



// Interrupt Service Routine for when rotary encoder is turned
void updateEncoder(){
  int MSB = digitalRead(PIN_ROT_A);           //MSB = most significant bit
  int LSB = digitalRead(PIN_ROT_B);           //LSB = least significant bit
  
  rotChange = true;                           // Set flag that we turned the encoder
  isLCDWrite = false;                         // Set flat that we haven't written to the LCD
  
  int encoded = (MSB << 1) |LSB;                                                          // Converting the 2 pin value to single number 
  int sum = (lastEncoded << 2) | encoded;                                                 // Adding it to the previous encoded value 
  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue++;    // Increase encoderValue if turned clockwise
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue--;    // Decrease encoderValue if turned counter-clockwise

  lastEncoded = encoded;                      // Store this value for next time
  Serial.println(encoderValue);               // Debug Printing
}



// Check if rotary encoder entered values are correct
void checkRotPress() {
  if(isYear && lcdYear == 1991) {                     // If checking year and the entered year is correct
      isMonth = false;                                // Set flag to false, not checking month
      isDay = false;                                  // Set flag to false, not checking day
      isYear = false;                                 // Set flag to false, not checking year
      rotChange = false;                              // Set flag to false, not checking rotary turns
      Serial.println("Got Year!");                    // Debug Printing
      lcdWriteBlink("CALCULATING...", " ", false);    // Blink that we're "Calculating" for suspense
      lcdWrite("YAY!", " ");                          // Write "YAY!" to the LCD
      lcd.noCursor();                                 // Turn the cursor off
      lcd.noBlink();                                  // Turn the blinking cursor off
      solvedPuzzle(2);                                // Set that we've solved puzzle 2
    }
    else if(isDay && lcdDay == 15) {                  // If checking day and entered day is correct
      isMonth = false;                                // Set flag to false, not checking month
      isDay = false;                                  // Set flag to false, not checking day
      isYear = true;                                  // Set flag to true, now checking year
      rotChange = false;                              // Set flag to false, encoder hasn't turned since we've checked
      lcdWriteYear(1800);                             // Write to LCD 2020 as the year, 1800 works for our method to do this
      Serial.println("Got Day!");                     // Debug Printing
    }
    else if(isMonth && lcdMonth == 9) {               // If checking month and entered month is correct
      isMonth = false;                                // Set flag to false, not checking month
      isDay = true;                                   // Set flag to true, now checking day
      isYear = false;                                 // Set flag to false, not checking year
      rotChange = false;                              // Set flag to false, encoder hasn't turned since we've checked
      lcdWriteDay(32);                                // Write to LCD 1 as the day, 32 works for our method to do this
      Serial.println("Got Month!");                   // Debug Printing
    } 
    else {                                            // Else he entered somthing wrong
      isMonth = true;                                 // Set flag to false, return to checking month
      isDay = false;                                  // Set flag to false, not checking day
      isYear = false;                                 // Set flag to false, not checking year
      rotChange = false;                              // Set flag to false, encoder hasn't turned since we've checked
      lcdWriteBlink("YOU'RE IN","TROUBLE...", true);  // Blink that he's in trouble for getting it wrong on the LCD
      lcdWrite("LINDSAY'S BDAY:","01/01/2020");       // Write the prompt back to the LCD
      lcd.setCursor(3,1);                             // Set cursor back to month space
      lcdWriteMonth(13);                              // Write to LCD 1 as the month, 13 works for our method to do this
    }
}
