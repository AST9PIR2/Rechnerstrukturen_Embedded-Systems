//
// Created by Pirmin on 02.06.2022.
//

#ifndef AUFGABE_1_JOYSTICKHIGH_H
#define AUFGABE_1_JOYSTICKHIGH_H

#define JOYSTICK_X    A0
#define JOYSTICK_Y    A1
#define JOYSTICK_BUTTON (PINE & (1 << PE2))

#include <stdint.h>
#include <avr/io.h>
#include <pins_arduino.h>

class JoystickHigh {
private:
    int pinX;
    int pinY;
    int32_t posX = 0;
    int32_t posY = 0;
    int32_t deadzone = 0;
    uint8_t button;

public:
    JoystickHigh(int pinX, int pinY) : pinX(JOYSTICK_X), pinY(JOYSTICK_Y){

    }

    ~JoystickHigh()= default;

    void begin();

    void update();

    int16_t getPosX(bool immediate = false);

    int16_t getPosY(bool immediate = false);

    bool getButton(bool immediate = false);

    void setDeadzone(int16_t deadzone);

    int16_t getDeadzone();
};

#endif //AUFGABE_1_JOYSTICKHIGH_H
