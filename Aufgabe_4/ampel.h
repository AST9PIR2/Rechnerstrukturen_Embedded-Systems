//
// Created by Pirmin on 14.06.2022.
//

#ifndef AUFGABE_3_1_AMPEL_H
#define AUFGABE_3_1_AMPEL_H

#include "dibse.h"
#include "bitoperations.h"
#include "JoystickHigh.h"

#define JOYSTICK_X  A0
#define JOYSTICK_Y  A1

class Ampel{

private:
    int8_t temp[10] = {0,0,0,0,0,0,0,0,0,0};
    unsigned long timer[10] = {0,0,0,0,0,0,0,0,0,0};
    unsigned long button_timer = 100;
    unsigned long timeout[10] ={7000,3000,5000,0,0,0,0,0,0,0};
    int run = 1;

public:

    void ampel_setup();
    void ampel_loop();
    void ampelHumanInterrupt();
    void ampelEmergencyInterrupt();
    void ampelNight();
};

#endif //AUFGABE_3_1_AMPEL_H
