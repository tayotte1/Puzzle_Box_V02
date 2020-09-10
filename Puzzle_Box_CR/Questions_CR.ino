// Trivia game. writes questions to the LCD and gets response
void askQuestions() {
  lcdWrite("WELCOME TO","TRIVIA!");           // Display that it's trivia
  delay(5000);                                // Delay
  lcdWrite("Press A","To Continue");          // Display how to continue
  while(!digitalRead(PIN_SWITCH1)) {          // Wait for 'A' button press
    delay(10);                                // Delay
  }

  int it = 1;         // Iterator for keeping track of what question they're on
  
  while(it<6) {       // While iterator is < 6 cause there are 5 questions keep asking questions
    switch (it){      // Switch case based on the iterator
      case 1:         // Question 1
        if( question("1", "1. Bell Tower","in Italian?", "A. Bring out","your dead!", "B. Ring a linga!","Ding Dong!", "C. Yo quiero","cannoli!", 1 ) ) {
          it++;       // Increase iterator if question answered correctly
        }
        break;
      case 2:
        if( question("2", "2. Most Pats rec","yards in a game?", "A. Wes Welker","(217yds)", "B. Randy Moss","(398 yds)", "C. Troy Brown","(160yds)", 1 ) ) {
          it++;       // Increase iterator if question answered correctly
        }
        break;
      case 3:
        if( question("3", "3. Most Sox K's","in a season?", "A. Roger Clemens","(291 K's)", "B.Pedro Martinez","(313 K's)", "C. Cy Young","(207 K's)", 2 ) ) {
          it++;       // Increase iterator if question answered correctly
        }
        break;
      case 4:
        if( question("4", "4. Best","Steakhouse?", "A. Morten's","Steakhouse", "B. Capital","Grille", "C. Mom's","Kitchen", 3 ) ) {
          it++;       // Increase iterator if question answered correctly
        }
        break;
      case 5:
        if( question("5", "5. Your","Anniversary?", "A. October 10,","1987", "B. October 10,","1982", "C. December 20,","1987", 1 ) ) {
          it++;       // Increase iterator if question answered correctly
        }
        break;
    }
  }
  
  solvedPuzzle(2);          // If made it here, then have solved puzzle 2
}



/* Write question to LCD screen
** Parameters:
** num, string that is the number of the question
** q1, string first line of the question, can only be 16 characters long
** q2, string second line of the question, can only be 16 characters long
** a1, string first line of answer A, can only be 16 characters long
** a2, string second line of answer A, can only be 16 characters long
** b1, string first line of answer B, can only be 16 characters long
** b2, string second line of answer B, can only be 16 characters long
** c1, string first line of answer C, can only be 16 characters long
** c2, string second line of answer C, can only be 16 characters long
** answer, int answer number, can only be 1, 2, or 3, representing the buttons
** returns true if question was answered correctly, false if it was not
*/
boolean question(String num, String q1, String q2, String a1, String a2, String b1, String b2, String c1, String c2, int answer) {

  String t = num + " of 5...";                        // Create string for displaying what number question is about to be asked
   
  lcdWrite("Question",t);                             // Write to lcd what question number it is
  delay(2000);                                        // Delay
  lcdWrite(q1, q2);                                   // Write to lcd the question
  delay(5000);                                        // Delay
  lcdWrite(a1, a2);                                   // Write to lcd answer A
  delay(3000);                                        // Delay
  lcdWrite(b1, b2);                                   // Write to lcd answer B
  delay(3000);                                        // Delay
  lcdWrite(c1, c2);                                   // Write to lcd answer C
  delay(3000);                                        // Delay
  lcdWrite("Answer:  ", "A? B? C?");                  // Write to lcd the prompt

  Serial.println("Reading Buttons");                  // Debug print
  int a = readQuestionButtons();                      // Go check for a button press
  if( a == answer ) {                                 // If return with correct answer
    if(num.equals("4")) {                             // If on question 4 do some trickery
      lcdWrite("Incorrect :(", "Try again.");         // Fake that they're wrong
      delay(3000);                                    // Delay
      lcdWrite("Just Kidding!","");                   // Display
      delay(2000);                                    // Delay
    }
    lcdWrite("Correct! YAY!","");                     // Display that answer was correct
    delay(3000);                                      // Delay
    return true;                                      // Return that question was answered correctly
  } else if( a == -1 ){                               // Else if time out from reading buttons
    lcdWrite("Too Slow.", "Try again.");              // Display that they were too slow
    delay(3000);                                      // Delay
  } else {                                            // Otherwise answer was incorrect
    lcdWrite("Incorrect :(", "Try again.");           // Display incorrect answer
    delay(3000);                                      // Delay
  }

  return false;                                       // Return that answer was incorrect

}


// Check if answer buttons are pressed, return which button is pressed, or that it timed out
int readQuestionButtons() {
  unsigned long prevTime = millis();          // Track time so can abort asking questions
  
  while(millis() - prevTime < 30000) {        // While less than 30 seconds have passed
    if(digitalRead(PIN_SWITCH1)) {            // If button 1 is pressed
      Serial.println("Read pin 1");           // Debug print
      return 1;                               // Return 1
    }
    if(digitalRead(PIN_SWITCH2)) {            // If button 2 is pressed
      Serial.println("Read pin 2");           // Debug print
      return 2;                               // Return 2
    }
    if(digitalRead(PIN_SWITCH3)) {            // If button 3 is pressed
      Serial.println("Read pin 3");           // Debug print
      return 3;                               // Return 3
    }
  }
  return -1;                                  // Otherwise timed out and return -1
}
