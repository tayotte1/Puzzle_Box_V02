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


// If question is answered correctly
void correctAnswer() {
  if(Q != 3) {
    lcd.noCursor();                               // turn cursor off
    lcd.noBlink();                                // turn blinking cursor off
    lcdWrite("Correct! YAY!","");
    delay(3000);
    rotChange = false;                            // Set flag to false, encoder hasn't turned since we've checked
    Q = Q+1;                                      // Increase Q
    lcd.cursor();                                 // turn cursor on
    lcd.blink();                                  // turn blinking cursor on
    askQuestion();                                // Ask next question
    lcdWriteNumber(101);                          // Write to LCD 00, 101 works for our method to do this
  } else {
    lcd.noCursor();                               // Turn the cursor off
    lcd.noBlink();                                // Turn the blinking cursor off
    lcdWrite("Impressive!", "");                  // Write "YAY!" to the LCD
    delay(3000);                                  // Delay
    solvedPuzzle(2);                              // Set that we've solved puzzle 2
    rotChange = false;                            // Set flag to false, encoder hasn't turned since we've checked
    Q++;                                          // Increase Q
    askQuestion();                                // Ask next question
  }
}


// Check if rotary encoder entered values are correct
void checkRotPress() {
  switch(Q) {
    case 1:
      if(lcdNumber == 32) {
        correctAnswer();                              // Answered correctly
        Serial.println("Got Question 0!");            // Debug Printing
      } else {
        lcd.noCursor();                               // turn cursor off
        lcd.noBlink();                                // turn blinking cursor off
        lcdWrite("Incorrect :(", "Try again.");
        delay(3000);
        lcd.cursor();                                 // turn cursor off
        lcd.blink();                                  // turn blinking cursor off
        askQuestion();
        lcdWriteNumber(encoderValue/4);               // Need to divide by 4 because each encoder notch counts as 4
      }
      break;
    case 2:
      if(lcdNumber == 75) {
        correctAnswer();                              // Answered correctly
        Serial.println("Got Question 1!");            // Debug Printing
      } else {
        lcd.noCursor();                               // turn cursor off
        lcd.noBlink();                                // turn blinking cursor off
        lcdWrite("Incorrect :(", "Try again.");
        delay(3000);
        lcd.cursor();                                 // turn cursor off
        lcd.blink();                                  // turn blinking cursor off
        askQuestion();
        lcdWriteNumber(encoderValue/4);               // Need to divide by 4 because each encoder notch counts as 4
      }
      break;
    case 3:
      if(lcdNumber == 31) {
        correctAnswer();                              // Answered correctly
        Serial.println("Got Question 2!");            // Debug Printing
      } else {
        lcd.noCursor();                               // turn cursor off
        lcd.noBlink();                                // turn blinking cursor off
        lcdWrite("Incorrect :(", "Try again.");
        delay(3000);
        lcd.cursor();                                 // turn cursor off
        lcd.blink();                                  // turn blinking cursor off
        askQuestion();
        lcdWriteNumber(encoderValue/4);               // Need to divide by 4 because each encoder notch counts as 4
      }
      break;
  }
}
