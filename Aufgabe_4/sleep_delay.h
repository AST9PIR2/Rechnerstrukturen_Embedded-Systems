//
// Created by Pirmin on 14.06.2022.
//

#ifndef AUFGABE_3_1_SLEEP_DELAY_H
#define AUFGABE_3_1_SLEEP_DELAY_H

#include <Arduino.h>
#include <avr/wdt.h>
#include <avr/sleep.h>
#include <avr/power.h>

#define LEDPIN 12


class sleep{
private:
    uint32_t seconds = 0;
    uint32_t temp = seconds;
public:
    void sleep_setup();
    void sleep_delay(uint32_t seconds);
};

#endif //AUFGABE_3_1_SLEEP_DELAY_H
