//
// Created by Pirmin on 05.06.2022.
//

#include "dibse.h"


// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel rgbLED(1, RGB_LED_PIN, NEO_GRB + NEO_KHZ800);

void DibsE::setup() {
    // Initialisiert das RGB-LED
    rgbLED.begin();
}

void DibsE::loop() {
    //uint8_t red, green, blue;

    //Sets color of the RGB LED to red
    simpleBlinkOn(100, 255, 0, 0);

    // Sets color of the RGB LED to green
    simpleBlinkOn(100, 0, 255, 0);

    // Sets color of the RGB LED to blue
    simpleBlinkOn(100, 0, 0, 255);

    // Sets color of the RGB LED to white
    simpleBlinkOn(100, 255, 255, 255);

    // Sets color of the RGB LED to yellow
    simpleBlinkOn(100, 255, 255, 0);

    // Sets color of the RGB LED to purple
    simpleBlinkOn(100, 255, 0, 255);

    // Sets color of the RGB LED to turquoise
    simpleBlinkOn(100, 0, 255, 255);

    simpleBlinkOff();
    mysetup = 1;

}

void DibsE::simpleBlinkOn(int duration, int red, int green, int blue) {

    if ((millis() > duration + timer ) && mysetup ==1 ){
        timer = millis();
        if (LED_STATE == LOW) {
            rgbLED.setPixelColor(0, red, green, blue);
            rgbLED.show();
            LED_STATE = HIGH;
        }else{
            simpleBlinkOff();
            LED_STATE = LOW;
        }
    } else{
        delay(duration);
    }
}

void DibsE::simpleBlinkOff() {

    rgbLED.setPixelColor(0, 0, 0, 0);
    rgbLED.show();

}
