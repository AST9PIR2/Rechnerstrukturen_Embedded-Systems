//
// Created by Pirmin on 14.06.2022.
//

#include "ampel.h"
#include "helligkeitsensor.h"
#include "distance.h"


DibsE rgb;
helligkeitsensor daylight;
JoystickHigh EmergencyInterrupt(JOYSTICK_X,JOYSTICK_Y);
Distance HumanInterrupt;

void Ampel::ampel_setup() {
    rgb.setup();
    EmergencyInterrupt.begin();
    HumanInterrupt.setup();
}



void Ampel::ampel_loop() {

    if(daylight.loop() > 750){

        //red phase
        while(run) {
            if (millis() - timer[0] >= 7000) {
                timer[0] = millis();
                TB(temp[0], 0);
            }

            if (temp[0]) {
                rgb.simpleBlinkOn(1, 50, 0, 0);
            } else {
                run = 0;
            }
            EmergencyInterrupt.update();

            if(EmergencyInterrupt.getButton()){
                ampelEmergencyInterrupt();
                break;
            }
        }

        run = 1;

        //yellow phase
        rgb.simpleBlinkOn(3000, 50, 50, 0);

        //green phase
        while(run) {
            if (millis() - timer[1] >= 5000) {
                timer[1] = millis();
                TB(temp[1], 0);
            }

            if (temp[1]) {
                rgb.simpleBlinkOn(1, 0, 50, 0);
            } else {
                run = 0;
            }

            HumanInterrupt.loop();

            if(HumanInterrupt.cm < 20){
                ampelHumanInterrupt();
                break;
            }
        }
        run = 1;
        rgb.simpleBlinkOff();
        delay(500);
        rgb.simpleBlinkOn(500, 0, 50, 0);
        rgb.simpleBlinkOff();
        delay(500);
        rgb.simpleBlinkOn(500, 0, 50, 0);

        //yellow phase
        rgb.simpleBlinkOn(3000, 50, 50, 0);
    }else{
        ampelNight();
    }




}


void Ampel::ampelHumanInterrupt() {

    rgb.simpleBlinkOn(3000, 50, 50, 0);
    rgb.simpleBlinkOn(7000, 50, 0, 0);

}

void Ampel::ampelEmergencyInterrupt() {

    rgb.simpleBlinkOn(3000, 50, 50, 0);
    rgb.simpleBlinkOn(5000, 0, 50, 0);

}

void Ampel::ampelNight() {

    rgb.simpleBlinkOn(2000, 50, 50, 0);
    rgb.simpleBlinkOff();
    delay(2000);

}
