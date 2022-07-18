//
// Created by Pirmin on 22.06.2022.
//

#ifndef AUFGABE_3_1_TEMPERATURE_H
#define AUFGABE_3_1_TEMPERATURE_H

#define I2C_ADDR 0x48

#include <stdint.h>

#include <Arduino.h>
#include <Wire.h>

class TemperatureSensor {

private:
    uint8_t resolution;
    bool sensorSleep;
    float currentTemperature;

public:
    TemperatureSensor(){
        this->resolution = 3;
        this->sensorSleep = false;
    };

    void begin();
    void switchToContinuousMode();
    void switchToOneShotMode();
    void setResolution(uint8_t res);
    void update();
    float getTemperature(bool immediate = false);
    void sleep();



};


#endif //AUFGABE_3_1_TEMPERATURE_H
