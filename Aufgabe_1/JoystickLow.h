//
// Created by Pirmin on 02.06.2022.
//

#ifndef AUFGABE_1_JOYSTICKLOW_H
#define AUFGABE_1_JOYSTICKLOW_H

#include <stdint.h>

class JoystickLow{
private:
    int32_t posX = 0;
    int32_t posY = 0;
    int32_t deadzone = 0;
    uint8_t button;

public:
    JoystickLow(){}

    ~JoystickLow()= default;

    void begin();

    void update();

    int16_t getPosX(bool immediate = false);

    int16_t getPosY(bool immediate = false);

    bool getButton(bool immediate = false);

    void setDeadzone(int16_t deadzone);

    int16_t getDeadzone();
};


#endif //AUFGABE_1_JOYSTICKLOW_H
