#include <Arduino.h>
#include "clap.h"
#include "dibse.h"

#define BIT(pos) ( 1<<(pos) )
#define TB(VALUE, POSITION) ( (VALUE) ^= (BIT(POSITION)) )

ClapDetection test;
DibsE rgb;


unsigned long timeout = 0;
uint8_t flag1 = 0;
uint8_t flag2 = 0;


void setup() {

    rgb.setup();
    rgb.loop();
}

void loop() {

    test.clap();

    auto temp = test.signal;


    if(temp == 2) {
        TB(flag1, 0);
    }

    if(temp == 3) {
        TB(flag2, 0);
    }


    if(flag1){

        rgb.simpleBlinkOn(1,255,255,255);

    }else if (flag2){

        if (timeout < 150){
            rgb.simpleBlinkOn(1,255,255,255);
            timeout ++;
        }else {
            rgb.simpleBlinkOff();
            timeout ++;
        }

        if(timeout == 300){
            timeout = 0;
        }


    }else{
        rgb.simpleBlinkOff();
    }

}