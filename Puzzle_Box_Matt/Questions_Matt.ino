// Ask a question on the LCD
void askQuestion(){
  switch(Q) {
    case 1:
      lcd.noCursor();         // turn cursor off
      lcd.noBlink();          // turn blinking cursor off
      lcdWrite("Question","1 of 6...");
      delay(2000);
      lcd.cursor();         // turn cursor on
      lcd.blink();          // turn blinking cursor on
      lcdWrite("Combined rings","C's, B's, RS:   ");    // Write to lcd the question
      lcd.setCursor(14,1);                              // Move cursor
      break;
    case 2:
      lcd.noCursor();         // turn cursor off
      lcd.noBlink();          // turn blinking cursor off
      lcdWrite("Question","2 of 6...");
      delay(2000);
      lcd.cursor();         // turn cursor on
      lcd.blink();          // turn blinking cursor on
      lcdWrite("Vince Wilfork's ","Number:         ");    // Write to lcd the question
      lcd.setCursor(14,1);                                // Move cursor
      break;
    case 3:
      lcd.noCursor();         // turn cursor off
      lcd.noBlink();          // turn blinking cursor off
      lcdWrite("Question","3 of 6...");
      delay(2000);
      lcd.cursor();         // turn cursor on
      lcd.blink();          // turn blinking cursor on
      lcdWrite("Dave Roberts'   ","Number:         ");    // Write to lcd the question
      lcd.setCursor(14,1);                                // Move cursor
      break;
    case 4:
      lcd.noCursor();         // turn cursor off
      lcd.noBlink();          // turn blinking cursor off
      if( buttonQuestion("4", "4. Most B's","career OTG?", "A. Dit Clapper","(10 OTG)", "B. Brad Marchand","(15 OTG)", "C. Glen Murray","(18 OTG)", 2 ) ) {
        Q++;
      }
      break;
    case 5:
      lcd.noCursor();         // turn cursor off
      lcd.noBlink();          // turn blinking cursor off
      if( buttonQuestion("5", "5. Highest FG%","all time C's?", "A. Kendrick Perk","(56.3%)", "B. Kevin Garnett","(52.0%)", "C. Larry Bird","(49.6%)", 1 ) ) {
        Q++;
      }
      break;
    case 6:
      lcd.noCursor();         // turn cursor off
      lcd.noBlink();          // turn blinking cursor off
      if( buttonQuestion("6", "6. B's leader in","PTS and GP?", "A. John Bucyk","1339 PTS 1436 GP", "B. Pat Bergeron","517 PTS 1089 GP", "C. Ray Bourque","1506 PTS 1518 GP", 3 ) ) {
        solvedPuzzle(3);
      }
      break;
    default:
      break;
    
  }
}


// function to ask the questions that need button presses
// returns whether the question was answered correctly or not
boolean buttonQuestion(String num, String q1, String q2, String a1, String a2, String b1, String b2, String c1, String c2, int answer) {

  String t = num + " of 6...";
   
  lcdWrite("Question",t);
  delay(2000);
  lcdWrite(q1, q2);
  delay(5000);
  lcdWrite(a1, a2);
  delay(4000);
  lcdWrite(b1, b2);
  delay(4000);
  lcdWrite(c1, c2);
  delay(4000);
  lcdWrite("Answer:  ", "A? B? C?");

  Serial.println("Reading Buttons");
  int a = readQuestionButtons();
  if( a == answer ) {
    lcd.noCursor();         // turn cursor off
    lcd.noBlink();          // turn blinking cursor off
    lcdWrite("Correct! YAY!","");
    delay(3000);
    return true;
  } else if( a == -1 ){
    lcd.noCursor();         // turn cursor off
    lcd.noBlink();          // turn blinking cursor off
    lcdWrite("Too slow.", "Try again.");
    delay(3000);
  } else {
    lcd.noCursor();         // turn cursor off
    lcd.noBlink();          // turn blinking cursor off
    lcdWrite("Incorrect :(", "Try again.");
    delay(3000);
  }

  return false;

}


// Read the buttons for an answer to the question
int readQuestionButtons() {
  prevTime = millis();
  while(millis() - prevTime < 30000) {
    if(digitalRead(PIN_BUTTON0)) {
      Serial.println("Read pin 1");
      return 1;
    }
    if(digitalRead(PIN_BUTTON1)) {
      Serial.println("Read pin 2");
      return 2;
    }
    if(digitalRead(PIN_BUTTON2)) {
      Serial.println("Read pin 3");
      return 3;
    }
  }
  return -1;
}
