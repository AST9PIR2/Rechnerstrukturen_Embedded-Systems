//
// Created by Pirmin on 28.06.2022.
//

#include "clap.h"

int test2 = 0;

void ClapDetection::clap() {

    long sum = 0;
    uint32_t time;

    for (int i = 0; i < 50; i++) {
        sum += analogRead(MICROPHONE);
    }

    sum = sum / 50;

    time = millis();

    if (sum > 400) {


        if (this->signal == 0) {
            this->signal = 1;
            this->last_sound_input = millis();
        } else if (this->signal == 1 && time <= this->last_sound_input + 200 && time >= this->last_sound_input + 50) {
            this->signal = 2;
            this->last_sound_input = millis();
        } else if (this->signal == 2 && time <= this->last_sound_input + 200 && time >= this->last_sound_input + 50) {
            this->signal = 3;
        }
    }

    int run = 101;

    if (this->signal == 1 && time > this->last_sound_input + run) {
        this->signal = 0;
    } else if (this->signal == 2 && time > this->last_sound_input + run + 101) {
        this->signal = 0;
    } else if (this->signal == 3 && time > this->last_sound_input + run + 201) {
        this->signal = 0;
    }

    Serial.print("Signal: ");
    Serial.println(this->signal);

}