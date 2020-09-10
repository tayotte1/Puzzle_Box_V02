void initHeart() {
  
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) {
    Serial.println("MAX30105 was not found. Please check wiring/power. ");
    while (1);
  }
  particleSensor.setup();                     //Configure sensor with default settings
  particleSensor.setPulseAmplitudeRed(0x0A);  //Turn Red LED to low to indicate sensor is running
  particleSensor.setPulseAmplitudeGreen(0);   //Turn off Green LED
}


// Check the heart rate monitor
void checkHeart() {
  long irValue = particleSensor.getIR();    // Gets value

  if (checkForBeat(irValue) == true)
  {
    // We sensed a beat!
    long delta = millis() - lastBeat;
    lastBeat = millis();

    beatsPerMinute = 60 / (delta / 1000.0);

    if (beatsPerMinute < 255 && beatsPerMinute > 20)
    {
      rates[rateSpot++] = (byte)beatsPerMinute; //Store this reading in the array
      rateSpot %= RATE_SIZE; //Wrap variable

      //Take average of readings
      beatAvg = 0;
      for (byte x = 0 ; x < RATE_SIZE ; x++)
        beatAvg += rates[x];
      beatAvg /= RATE_SIZE;
    }
  }
//
//  Serial.print("IR=");
//  Serial.print(irValue);
//  Serial.print(", BPM=");
  Serial.println(beatsPerMinute);
//  Serial.print(", Avg BPM=");
//  Serial.println(beatAvg);

  if (irValue < 50000) {
    isFinger = false;
  } else {
    if(!isFinger) {
      countFinger++;
      isFinger = true;
      if(countFinger == 10) {
        solvedPuzzle(2);
      }
    } 
  }
    
//    Serial.print(" No finger?");

//  Serial.println();
}
