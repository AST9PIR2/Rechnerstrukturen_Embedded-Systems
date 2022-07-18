//
// Created by Pirmin on 05.06.2022.
//

/*
 * Posted on https://randomnerdtutorials.com
 * created by http://playground.arduino.cc/Code/NewPing
*/

//teckel12/NewPing@
#include "distance.h"
#include "LedMatrix.h"

// NewPing setup of pins and maximum distance
LedMatrix ledMatrix(LED_LATCH,LED_DATA,LED_CLOCK);


void Distance::setup() {
    pinMode(TRIGGER_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    rgb_test->setup();
    rgb_test->loop();

}

void Distance::loop() {

    digitalWrite(TRIGGER_PIN, LOW);
    delayMicroseconds(5);
    digitalWrite(TRIGGER_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER_PIN, LOW);

    pinMode(ECHO_PIN, INPUT);
    duration = pulseIn(ECHO_PIN, HIGH);

    cm = (duration/2) / 29.1;

    Serial.print(cm);
    Serial.print("cm_test");
    Serial.println();

    //rgb_test->simpleBlinkOn(4*cm,100,(0),0);

    unsigned long time = millis();

    ledMatrix.clear();
    check = map(cm,4,400,0,255);
    // Draws an x into the display buffer.

    //Convert the input to usable values: 0 1 3 7 15 31 63 127 255
    for(int v = 0; v < 9;v++){
        if( (check >= (pow(2,v) -1)) & (check < (pow(2,v+1)+1)) ){
            //making sure we get a proper int value
            run = int(pow(2,v+1)-1+0.5 -(pow(2,v+1)-1<0));
            break;
        }else{
            run = 0;
        }
    }

    //Running all LED's with the value provided from array
    ledMatrix.drawColumn(0,run);
    for(int c = 1; c < 8;c++){
        ledMatrix.drawColumn(c,temp[c-1]);
    }

    //Running a loop for 3seconds
    if (time - lastTime >= 3000) {
        lastTime = time;
        //Filling up the array, every loop shift all values to the right, overwrite the last one and get a new one from run.
        for(int x = 6; x > 0; x--){
            temp[x] = temp[x-1];
        }
        temp[0] = run;
    }

    ledMatrix.update();

}
