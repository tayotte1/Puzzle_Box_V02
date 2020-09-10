// Trivia game. writes questions to the LCD and gets response
void askQuestions() {
  lcdWrite("WELCOME TO","TRIVIA!");           // Display that it's trivia
  delay(5000);                                // Delay
  lcdWrite("Press A","To Continue");          // Display how to continue
  while(!digitalRead(PIN_BUTTON1)) {          // Wait for 'A' button press
    delay(10);
  }

  int it = 1;         // Iterator for keeping track of what question they're on
  
  while(it<6) {       // While iterator is < 6 cause there are 5 questions
    switch (it){      // Switch case based on the iterator
      case 1:         // Question 1
        if( question("1", "1. Age of the","universe?", "A. 14","Billion Years", "B. 670","Million Years", "C. 5.7","Billion Years", 1 ) ) {
          it++;       // Increase iterator if question answered correctly
        }
        break;
      case 2:
        if( question("2", "2. Simone Biles","# Olympic golds?", "A. 6","Golds", "B. 5","Golds", "C. 4","Golds", 3 ) ) {
          it++;       // Increase iterator if question answered correctly
        }
        break;
      case 3:
        if( question("3", "3. Which was an","SSX character?", "A. Gretchen"," ", "B.Yuri"," ", "C. Kaori"," ", 3 ) ) {
          it++;       // Increase iterator if question answered correctly
        }
        break;
      case 4:
        if( question("4", "4. Where did we","buy our rings?", "A. Neil's","Jewelry", "B. Trillion","Jewels", "C. Old Town","Gems", 2 ) ) {
          it++;       // Increase iterator if question answered correctly
        }
        break;
      case 5:
        if( question("5", "5. Name of","my school?", "A. UCSD"," ", "B. USD"," ", "C. UCSB"," ", 1 ) ) {
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
    if(digitalRead(PIN_BUTTON1)) {            // If button 1 is pressed
      Serial.println("Read pin 1");           // Debug print
      return 1;                               // Return 1
    }
    if(digitalRead(PIN_BUTTON2)) {            // If button 2 is pressed
      Serial.println("Read pin 2");           // Debug print
      return 2;                               // Return 2
    }
    if(digitalRead(PIN_BUTTON3)) {            // If button 3 is pressed
      Serial.println("Read pin 3");           // Debug print
      return 3;                               // Return 3
    }
  }
  return -1;                                  // Otherwise timed out and return -1
}
