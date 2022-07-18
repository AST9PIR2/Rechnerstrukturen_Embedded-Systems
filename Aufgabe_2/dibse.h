//
// Created by Pirmin on 05.06.2022.
//

#ifndef AUFGABE_1_DIBSE_H
#define AUFGABE_1_DIBSE_H

//#include "../.pio/libdeps/leonardo/Adafruit NeoPixel/Adafruit_NeoPixel.h"
#include <Adafruit_NeoPixel.h>
#define RGB_LED_PIN A4

class DibsE {

private:
    int duration;
    int red;
    int green;
    int blue;
    unsigned long timer = 0;
    int mysetup = 0;
    int LED_STATE = LOW;

public:

    DibsE(){
        duration = 10;
        red= 255;
        green = 255;
        blue = 255;
    };
    ~DibsE()= default;;

    void setup();
    void loop();
    void simpleBlinkOn(int duration, int red, int green, int blue);
    void simpleBlinkOff();
};

#endif //AUFGABE_1_DIBSE_H
