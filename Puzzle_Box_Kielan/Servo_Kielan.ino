// Initialize the servo to initial position
void initServo() {
  pinMode(PIN_SERVO_LID_PWR, OUTPUT);           // Initialize the lid servo power pin
  digitalWrite(PIN_SERVO_LID_PWR, LOW);         // Set LOW
  pinMode(PIN_SERVO_TEMP_PWR, OUTPUT);          // Initialize the lid servo power pin
  digitalWrite(PIN_SERVO_TEMP_PWR, LOW);        // Set LOW
}



/* Move the servo on certain pin to position
** Parameters:
** pinCon, integer of the pin number for controlling the servo
** pinPwr, integer of the pin number for powering the servo
** pos, integer of the position to move the servo to
*/
void moveServo(int pinCon, int pinPwr, int pos) {
  myServo.attach(pinCon);                 // attach it to myServo
  myServo.write(pos);                     // send it to proper position
  delay(20);                              // delay
  digitalWrite(pinPwr, HIGH);             // Set power pin HIGH to turn servo on
  delay(1500);                            // let it move
  myServo.detach();                       // detach it
  digitalWrite(pinPwr, LOW);              // Set power pin HIGH to turn servo on
}
