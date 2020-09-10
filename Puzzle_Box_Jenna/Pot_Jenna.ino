// Checks if the potentiometers are at the correct positions
boolean checkPot(){
  int p0 = analogRead(PIN_POT0);
  int p1 = analogRead(PIN_POT1);
  int p2 = analogRead(PIN_POT2);
  int p3 = analogRead(PIN_POT3);
  int p4 = analogRead(PIN_POT4);
  int count = 0;

  Serial.print("p0: ");
  Serial.print(p0);
  Serial.print(", ");
  Serial.print("p1: ");
  Serial.print(p1);
  Serial.print(", ");
  Serial.print("p2: ");
  Serial.print(p2);
  Serial.print(", ");
  Serial.print("p3: ");
  Serial.print(p3);
  Serial.print(", ");
  Serial.print("p4: ");
  Serial.print(p4);
  Serial.print(", ");

  
  if(p0 <= V0+V_RANGE && p0 >= V0-V_RANGE) {
    count++;
  }
  if(p1 <= V1+V_RANGE && p1 >= V1-V_RANGE) {
    count++;
  }
  if(p2 <= V2+V_RANGE && p2 >= V2-V_RANGE) {
    count++;
  }
  if(p3 <= V3+V_RANGE && p3 >= V3-V_RANGE) {
    count++;
  }
  if(p4 <= V4+V_RANGE && p4 >= V4-V_RANGE) {
    count++;
  }

  Serial.print("Count: ");
  Serial.println(count);
  if(count == 5) {            // if all 5 are at correct position, return true
    return true;
  }
  return false;               // otherwise return false
}
