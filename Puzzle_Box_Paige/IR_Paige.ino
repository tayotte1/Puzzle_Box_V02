void initIR() {
  pinMode(PIN_IR, INPUT);             // Initialize the tool switch
  pinMode(PIN_TV, OUTPUT);            // Initialize the TV LED Pin
  digitalWrite(PIN_TV, LOW);          // Set pin LOW to turn LED off
}
