//
// Created by Pirmin on 28.06.2022.
//

#ifndef AUFGABE_5_CLAP_H
#define AUFGABE_5_CLAP_H

#include <Arduino.h>

#define MICROPHONE A3

class ClapDetection {
private:

        uint32_t last_sound_input;

public:
        int signal;
        void clap();
};

#endif //AUFGABE_5_CLAP_H
