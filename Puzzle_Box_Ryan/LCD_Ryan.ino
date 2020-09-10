// Initialize the LCD to 
void initLCD() {
  lcd.init();           // initialize lcd instance
  lcd.cursor();         // turn cursor on
  lcd.blink();          // turn blinking cursor on
  lcd.clear();          // clear the screen
  lcd.noBacklight();    // turn the backlight off
  lcd.noDisplay();      // turn the display off
}



// Turns the LCD OFF
void lcdOff() {
  lcd.clear();          // clear the screen
  lcd.noBacklight();    // turns the backlight off
  lcd.noDisplay();      // turns the display off
  isLCD = false;        // sets boolean to let program know lcd is off
}



// Turns the LCD ON
void lcdOn() {
  lcd.clear();          // clear the screen
  lcd.backlight();      // turn the backlight on
  lcd.display();        // turn the display on
  lcd.setCursor(0,0);   // set the cursor to the upper left corner
  lcd.cursor();         // turn cursor on
  lcd.blink();          // turn blinking cursor on
  isLCD = true;         // sets boolean to let program lcd is on
}



/* Write strings to LCD screen
** Parameters:
** line1, string to write to the first line of the lcd, can only be 16 characters long
** line2, string to write to the second line of the lcd, can only be 16 characters long
*/
void lcdWrite(String line1, String line2) {
  lcd.clear();                      // clear the screen
  int sp = 0;                       // Space count
  sp = (16 - line1.length())/2;     // determine how many blank spaces in front of line1 to put
  lcd.setCursor(sp,0);              // set the cursor to appropriate position
  lcd.print(line1);                 // print to screen

  sp = 0;                                           // Reset space count
  sp = round(((16.0 - line2.length())/2.0) + .1);   // determine spaces
  lcd.setCursor(sp,1);                              // set cursor to appropriate position
  lcd.print(line2);                                 // print to screen
}



/* Write the month to the lcd screen based on the rotary encoder input
** Parameters:
** val, integer of the value that it thinks the month should be
*/
void lcdWriteMonth(int val) {
// if input less than 1 then roll counter to 12 because we want to only display 1-12 for months
  if(val < 1) {
    encoderValue = 12*4+2;            // encoder starts at -1 so need to add 2
  }
// if input greater than 12 then roll counter to 1 because we want to only display 1-12 for months
  if(val > 12) {
    encoderValue = 1*4+2;             // encoder starts at -1 so need to add 2
  }


  lcdMonth = encoderValue/4;          // set lcdMonth
  
  lcd.setCursor(3,1);                 // move cursor to month
// if going to display month < 10, add leading zero
  if(lcdMonth < 10) {
    lcd.print("0");
  }

  lcd.print(lcdMonth);                // print the month to the LCD
  lcd.setCursor(3,1);                 // move cursor back
  Serial.print("Month: ");            // debug printing
  Serial.println(encoderValue/4);     // debug printing
}



/* Write the day to the lcd screen based on the rotary encoder input
** Parameters:
** val, integer of the value that it thinks the day should be
*/
void lcdWriteDay(int val) {
// if input less than 1 then roll counter to 31 because we want to only display 1-31 for days
  if(val < 1) {
    encoderValue = 31*4+2;            // encoder starts at -1 so need to add 2
  }
// if input greater than 31 then roll counter to 1 because we want to only display 1-31 for days
  if(val > 31) {
    encoderValue = 1*4+2;             // encoder starts at -1 so need to add 2
  }

  lcdDay = encoderValue/4;            // set lcdDay
    
  lcd.setCursor(6,1);                 // move cursor to month
// if going to display month < 10, add leading zero
  if(lcdDay < 10) {
    lcd.print("0");
  }

  lcd.print(lcdDay);                  // print the day to the LCD
  lcd.setCursor(6,1);                 // move cursor back
  Serial.print("Day: ");              // debug printing
  Serial.println(encoderValue/4);     // debug printing
}



/* Write the year to the lcd screen based on the rotary encoder input
** Parameters:
** val, integer of the value that it thinks the year should be
*/
void lcdWriteYear(int val) {
// if input less than 1900 then roll counter to 2020 because we want to only display 1900-2020 for year
  if(val < 1900) {
    encoderValue = 2020*4+2;          // encoder starts at -1 so need to add 2
  }
// if input greater than 2020 then roll counter to 1 because we want to only display 1900-2020 for years
  if(val > 2020) {
    encoderValue = 1900*4+2;          // encoder starts at -1 so need to add 2
  }
  
  lcdYear = encoderValue/4;           // set lcdYear
  lcd.setCursor(9,1);                 // move cursor to year
  lcd.print(lcdYear);                 // print the year to the LCD
  lcd.setCursor(9,1);                 // move cursor back
  Serial.print("Year: ");             // debug printing
  Serial.println(encoderValue/4);     // debug printing
}



/* Flash strings on LCD screen 4 times
** Parameters:
** line1, string to write to the first line of the lcd, can only be 16 characters long
** line2, string to write to the second line of the lcd, can only be 16 characters long
** blnk, boolean for if the cursor should be turned on after finishing
*/
void lcdWriteBlink(String line1, String line2, boolean blnk) {
  lcd.noCursor();             // Turn off cursor
  lcd.noBlink();              // Turn off blinking
  
  for(int i=0; i<4; i++) {    // Do this 4 times
    lcdWrite(line1, line2);   // Write to LCD
    delay(650);               // Leave it there for 650 milliseconds
    lcd.clear();              // Clear the LCD screen
    delay(250);               // Leave it blank for 250
  }

  if(blnk) {
    lcd.cursor();               // Turn cursor back on
    lcd.blink();                // Turn blink
  } 
}
