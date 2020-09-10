// Initialize the servo to initial position
void initShock() {
  pinMode(PIN_SHOCK0, INPUT);             // Initialize the lid servo power pin
  pinMode(PIN_SHOCK1, INPUT);             // Initialize the lid servo power pin
}


// check shock sensors
boolean checkShock() {
  boolean s0 = digitalRead(PIN_SHOCK0);   // Boolean if shock 0 is on
  boolean s1 = digitalRead(PIN_SHOCK1);   // Boolean if shock 1 is on

  if( !s0 ) {                   // If not s1 then shock 1 senses a shock
    Serial.print("s0: ");
    Serial.print(s0);
  }
  if( !s1 ) {                   // If not s1 then shock 1 senses a shock
    Serial.print(", s1: ");
    Serial.println(s1);
  }
  
  if( !s0 && !s1 ) {            // If not both then they are both shocked and return true
    return true;
  }

  return false;                 // Otherwise they were not shocked and return false
}
