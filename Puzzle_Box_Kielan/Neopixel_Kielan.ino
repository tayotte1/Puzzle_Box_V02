s// Initialize the Neopixels
void initNeopixels() {
  pixels.begin();                       // Begin the pixels
  pixels.setBrightness(50);             // Set brightness to not blinding
  pixels.clear();                       // Clear the neopixels
  pixels.show();                        // Send clear command
}



/* Set a single pixel to a RGB value
** Parameters:
** pixelNum, integer for which pixel to set, value can be 0 to NUM_PIXELS-1
** r, integer for the red value the pixel should be, value can be 0 to 255
** g, integer for the green value the pixel should be, value can be 0 to 255
** b, integer for the blue value the pixel should be, value can be 0 to 255
*/
void setPixel(int pixelNum, int r, int g, int b) {
  pixels.setPixelColor(pixelNum, pixels.Color(r, g, b));    // Set the pixel color
  pixels.show();                                            // Send the updated pixel color
}



/* Set all the pixels to a RGB value
** Parameters:
** r, integer for the red value the pixel should be, value can be 0 to 255
** g, integer for the green value the pixel should be, value can be 0 to 255
** b, integer for the blue value the pixel should be, value can be 0 to 255
*/
void setAllPixel(int r, int g, int b) {
  pixels.clear();                                       // Set all pixel colors to 'off'
  
  for(int i=0; i<NUM_PIXELS; i++) {                     // For each pixel set the color
    pixels.setPixelColor(i, pixels.Color(r, g, b));     // Set the pixel color
  }
  pixels.show();                                        // Send the updated pixel color
}



/* Flash all the pixels to a RGB value
** Parameters:
** num, integer for how many times to flash
** r, integer for the red value the pixels should be, value can be 0 to 255
** g, integer for the green value the pixels should be, value can be 0 to 255
** b, integer for the blue value the pixels should be, value can be 0 to 255
*/
void flashPixels(int num, int r, int g, int b) {
  pixels.clear();                                       // Set all pixel colors to 'off'
  for(int i=0; i<num; i++) {
    setAllPixel(r,g,b);                         // Set all pixels to color
    delay(650);                                 // Delay
    pixels.clear();                             // Set all pixel colors to 'off'
    pixels.show();                              // Send the clear command
    delay(250);                                 // Delay
  }
}



/* Flash all the pixels in a rainbow pattern
** Parameters:
** num, integer for how many times to flash
*/
void flashRainbow(int num) {
  for(int j=0; j<num; j++) {                                                        // Do this num amount of times
    for(int i=0; i< pixels.numPixels(); i++) {                                      // Set each pixel
      pixels.setPixelColor(i, Wheel(((i * 256 / pixels.numPixels()) + j) & 255));   // Set to color of rainbow
    }
    pixels.show();        // Show rainbow
    delay(650);           // Delay
    pixels.clear();       // Clear Rainbow
    pixels.show();        // Send clear
    delay(250);           // Delay
  }
}

/* Flash all the pixels in a rainbow pattern
** Parameters:
** offset, integer for setting offset of rainbow
*/
void setRainbow(int offset) {
  pixels.clear();                 // Set all pixel colors to 'off'
  
  for(int i=0; i< pixels.numPixels(); i++) {                                            // Set each pixel
    pixels.setPixelColor(i, Wheel(((i * 256 / pixels.numPixels()) + offset) & 255));    // Set Rainbow color
  }
  pixels.show();    // Show the rainbow
}



/* Cycle around the wheel a rainbow a certain number of times
** Parameters:
** wait, integer for how long to wait before moving the rainbow along
** num, integer for how many times to flash
*/
void rainbowCycle(int wait, int num) {
  uint16_t i, j;                                // Integers for the for loop

  for(j=0; j<256*num; j++) {                    // Cycles of all colors on wheel num amount of times
    for(i=0; i< pixels.numPixels(); i++) {      // Set each pixel
      pixels.setPixelColor(i, Wheel(((i * 256 / pixels.numPixels()) + j) & 255));
    }
    pixels.show();                              // Send updated colors
    delay(wait);                                // Delay wait amount of time
  }
}



/* Input a value 0 to 255 to get a color value. The colours are a transition r - g - b - back to r. Stole this from the example sketch and not entirely sure how it works.
** Parameters:
** WheelPos, byte for which position of the wheel the pixel is
*/
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}



// Go blue->green->red->blue on the neopixels
void rainbowAll(){
  int r=0;          // red
  int g=0;          // green
  int b=255;        // blue
  int i;            // counter
  int dTime = 1;    // delay between each color

  for(i=0; i<255; i++) {    // blue->green
    r = 0;
    g = i;
    b = 255-i;
    setAllPixel(r,g,b);
    delay(dTime);
  }
  for(i=0; i<255; i++) {    // green->red
    r = i;
    g = 255-i;
    b = 0;
    setAllPixel(r,g,b);
    delay(dTime);
  }
  for(i=0; i<255; i++) {    // red->blue
    r = 255-i;
    g = 0;
    b = i;
    setAllPixel(r,g,b);
    delay(dTime);
  }
  
}
