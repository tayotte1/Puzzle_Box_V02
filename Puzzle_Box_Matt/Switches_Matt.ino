// Initialize touch sensor pins
void initTouchSensors() {
  pinMode(PIN_TOUCH0,INPUT);   // set pin as INPUT
  pinMode(PIN_TOUCH1,INPUT);   // set pin as INPUT
  pinMode(PIN_TOUCH2,INPUT);   // set pin as INPUT
}

// Initialize LCD button pins
void initButtons() {
  pinMode(PIN_BUTTON0,INPUT);   // set pin as INPUT
  pinMode(PIN_BUTTON1,INPUT);   // set pin as INPUT
  pinMode(PIN_BUTTON2,INPUT);   // set pin as INPUT
}
