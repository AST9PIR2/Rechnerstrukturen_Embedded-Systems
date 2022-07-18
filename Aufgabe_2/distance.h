//
// Created by Pirmin on 05.06.2022.
//

#ifndef AUFGABE_1_TEST_DISTANCE_H
#define AUFGABE_1_TEST_DISTANCE_H

//#include "../.pio/libdeps/leonardo/NewPing/src/NewPing.h"
#include "dibse.h"
#include <math.h>

#define TRIGGER_PIN 8
#define ECHO_PIN 4
#define MAX_DISTANCE 400

#define LED_LATCH 11
#define LED_DATA 16
#define LED_CLOCK 15

class Distance{
private:
    unsigned long lastTime = 0;
    int i = 0;
    int check;
    double run;
    int a;
    int temp[7] = {0,0,0,0,0,0,0};


public:

    Distance(){
        check = 0;
        run = 0;
        a = 0;
    }

    ~Distance()= default;;

    DibsE * rgb_test = new DibsE();

    unsigned long duration{};
    unsigned long cm{};

    void setup();
    void loop();

};

#endif //AUFGABE_1_TEST_DISTANCE_H
