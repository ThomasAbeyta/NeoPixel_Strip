/*
 * Project Smart Trash Can 
 * Author: Thomas Abeyta
 * Date: 01/06/2023
 *  * Description: This is for an Smart Trash can to deteremine the 
 * fullness level, indicated by neoPixel lights, green, orange, red.
 * 
 */



#pragma once
#include "Grove-Ultrasonic-Ranger.h" 
#include "neopixel.h" 

#define PIXEL_COUNT 40// define the number of pixels in the neopixel strip
#define PIXEL_PIN D3 // define the pin the neopixel strip is connected to
#define PIXEL_TYPE WS2812B // define the type of neopixel being used
#define FLAME_PIN A4 // define the pin the flame sensor is connected to



Ultrasonic ultrasonic(A3); // create an ultrasonic object and assign it to pin A5
Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE); // create a neopixel object and assign it to the defined pin and type

float previousTrashCanFullness = 0; // create a variable to store the previous trash can fullness value

SYSTEM_MODE(SEMI_AUTOMATIC); // set system mode to semi-automatic

const int BUTTON = D6;
unsigned long previousMillis = 0;
unsigned long currentMillis;
int duration;
int state = 0;

void setup() {
    Serial.begin(800000);
    strip.begin();
    strip.show();
    pinMode(BUTTON, INPUT);
}

void loop() {
    strip.begin();
    int buttonPressed = digitalRead(BUTTON);
    
    if (buttonPressed >= 1){
      for (int i = 0; i < PIXEL_COUNT; i++) {
                strip.setPixelColor(i, 0, 0, 255);
                strip.show();
      }
    }else{for (int i = 0; i < PIXEL_COUNT; i++) {
                strip.setPixelColor(i, 0, 255, 0);
                strip.show();
              }
          }
}


void fade(uint32_t c1, uint32_t c2, uint8_t wait, int steps) {
  // Extract the red, green, and blue values of color 1
  uint8_t r1 = (c1 >> 16) & 0xff;
  uint8_t g1 = (c1 >> 8) & 0xff;
  uint8_t b1 = c1 & 0xff;

  // Extract the red, green, and blue values of color 2
  uint8_t r2 = (c2 >> 16) & 0xff;
  uint8_t g2 = (c2 >> 8) & 0xff;
  uint8_t b2 = c2 & 0xff;

  // Calculate the step size for each color channel
  int rStep = (r2 - r1) / steps;
  int gStep = (g2 - g1) / steps;
  int bStep = (b2 - b1) / steps;

  // Iterate over the number of steps in the fade
  for (int i = 0; i <= steps; i++) {
    // Calculate the interpolation factor
    for (int j = 0; j < PIXEL_COUNT; j++) {
      strip.setPixelColor(j, r1 + (i * rStep), g1 + (i * gStep), b1 + (i * bStep));
    }
    strip.show();
    delay(wait);
  }
}


// Function to perform a color wipe animation
void colorWipe(uint32_t c, uint8_t wait) {
  // Iterate over all pixels
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    // Set the color of the current pixel
    strip.setPixelColor(i, c);

    // Update the strip to show the new pixel colors
    strip.show();

    // Delay for the specified time
    delay(wait);
  }
}
 
// Function to get the distance measured by the ultrasonic sensor in inches
int getUltraSonicData() {
  

  // create int and measure the distance in inches
  int RangeInInches = ultrasonic.MeasureInInches();
  Serial.printf("The trashCanFullness is: %i \n", RangeInInches);

  // Print the measured distance
  //Serial.print(RangeInInches); // 0~157 inches
  Serial.println(" inch");

  // Return the measured distance
  return RangeInInches;
}