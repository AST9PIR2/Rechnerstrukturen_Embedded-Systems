//
// Created by Pirmin on 02.06.2022.
//

#include <Arduino.h>
#include "JoystickHigh.h"

void JoystickHigh::begin() {
    //PE2 als Eingang
    DDRE &= ~(1 << PE2);
    //Pullup-Widerstand ausgeschaltet
    PORTE &= ~(1 << PE2);
}

void JoystickHigh::update() {
    posX = getPosX(true);
    posY = getPosY(true);
    button = getButton(true);
}

int16_t JoystickHigh::getPosX(bool immediate) {
    if(immediate) {
        int32_t pos = map(analogRead(pinX),0,1023,-512,512);
        if(abs(pos) <= deadzone){
            pos = 0;
        }
        return pos;
    }else{
        return posX;
    }
}

int16_t JoystickHigh::getPosY(bool immediate) {
    if(immediate) {
        int32_t pos = map(analogRead(pinY),0,1023,-512,512);
        if(abs(pos) <= deadzone){
            pos = 0;
        }
        return pos;
    }else{
        return posY;
    }
}

bool JoystickHigh::getButton(bool immediate) {
    if(immediate) {
        // List aktuellen Status von PE2 aus
        return PINE & (1<< PE2);

    }else{
        return button;
    }
}

void JoystickHigh::setDeadzone(int16_t deadzone) {
    this->deadzone = deadzone;
}

int16_t JoystickHigh::getDeadzone() {
    return deadzone;
}
