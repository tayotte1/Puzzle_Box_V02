// Initialize the LCD, clear it and turn it off 
void initLCD() {
  lcd.init();           // initialize lcd instance
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
  lcd.noCursor();       // turn cursor off
  lcd.noBlink();        // turn blinking cursor off
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






/* Flash strings on LCD screen 4 times
** Parameters:
** line1, string to write to the first line of the lcd, can only be 16 characters long
** line2, string to write to the second line of the lcd, can only be 16 characters long
** blnk, boolean for if to turn the cursor on after finished
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
