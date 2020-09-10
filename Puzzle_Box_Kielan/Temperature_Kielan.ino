// Initialize temperature sensor
void initTemp() {
  tempSensors.begin();                         // Start One Wire for the temperature sensors

}



/*
 * Function to check the temperature sensor value
 * Return: int F, temperature in Fahrenheit
 */
int getTempurature()
{
  tempSensors.requestTemperatures();            // Request values from One Wire
  delay(20);                                    // Delay
  float C = tempSensors.getTempCByIndex(0);     // Celcius degrees of the temperature sensor
  float F = 0;                                  // Fahrenheit degrees of the temperature sensor
  
  F = tempSensors.toFahrenheit(C);              // convert to F
  
  Serial.print("C: ");                          // Debug printing
  Serial.print((int)C);
  Serial.print("   F: ");
  Serial.println((int)F);

  return (int)F;                                // return temperature in Fahrenheit
}



/*
 * Function to set the neopixels based on the temperature of the sensor to give indication temperature sensor is heating up
 * Parameters: int t, temperature from the temperature sensor
 */
void setPixelTemp(int t){
  int re = 0;             // Red
  int gr = 0;             // Green
  int bl = 0;             // Blue
  int midTemp = 100;      // Middle temperature for color range
  

  if(t < midTemp) {       // If less than mid way to target temp we're in the green->blue range
    re = 0;                                       // Set red to 0
    gr = map(t, startingTemp, midTemp, 0, 255);   // Map green value based on t, startingTemp, and midtemp
    bl = map(t, startingTemp, midTemp, 255, 0);   // Map blue value based on t, startingTemp, and midtemp
   
    if(gr < 0) {    // Catch negative values
      gr = 0;
    }
    if(bl < 0) {    // Catch negative values
      bl = 0;
    }
    setAllPixel(re, gr, bl);    // Set the neopixels the appropriate colors
  }else {                   // else more than mid way to target temp and we're in the green->red range
    re = map(t, midTemp, TARGET_TEMP, 0, 255);    // Map red value based on t, startingTemp, and midtemp
    gr = map(t, midTemp, TARGET_TEMP, 255, 0);    // Map green value based on t, startingTemp, and midtemp
    bl = 0;                                       // Set blue to 0
    
    if(re < 0) {    // Catch negative values
      re = 0;
    }
    if(gr < 0) {    // Catch negative values
      gr = 0;
    }
    if(re>255){     // Catch larger than 255 values
      re = 255;
    }
    setAllPixel(re, gr, bl);    // Set the neopixels the appropriate colors
  }
}
