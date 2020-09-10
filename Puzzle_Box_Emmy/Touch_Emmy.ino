// Initialize touch sensor pins
void initTouchSensors() {
  pinMode(PIN_TOUCH0,INPUT);   // set pin as INPUT
  pinMode(PIN_TOUCH1,INPUT);   // set pin as INPUT
}



// Check if all touch sensors are being touched, return true if they all are, else return false
boolean checkTouchSensors() {
  if(digitalRead(PIN_TOUCH0) && digitalRead(PIN_TOUCH1)) {
    return true;
  }
  return false;
}
