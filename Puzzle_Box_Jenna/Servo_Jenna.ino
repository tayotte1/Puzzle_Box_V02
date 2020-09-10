// Initialize the servo
void initServo() {
  pinMode(PIN_SERVO_LID_PWR, OUTPUT);           // Initialize the lid servo power pin
  digitalWrite(PIN_SERVO_LID_PWR, LOW);         // Set LOW
}



/* Move the servo on certain pin to position
** Parameters:
** pin, integer of the pin number
** pos, integer of the position to move the servo to
*/
void moveServo(int pin, int pos) {
  myServo.attach(pin);                    // attach it to myServo
  myServo.write(pos);                     // send it to proper position
  delay(20);
  digitalWrite(PIN_SERVO_LID_PWR, HIGH);  // Set power pin HIGH to turn servo on
  delay(1500);                            // let it move
  myServo.detach();                       // detach it
  digitalWrite(PIN_SERVO_LID_PWR, LOW);   // Set power pin HIGH to turn servo on
}
