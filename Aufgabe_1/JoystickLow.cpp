//
// Created by Pirmin on 02.06.2022.
//

#include "JoystickLow.h"
#include <avr/io.h>

#define abs(x) ( (x)>0 ? (x) : -(x))

void JoystickLow::begin() {
    DDRE &= ~(1 << PE2);  //PE2 als Eingang
    PORTE &= ~(1 << PE2);  //Pullup-Widerstand ausgeschaltet

    // Konfiguriere die Betriebsspannung als Referenzspannung
    ADMUX = (1 << REFS0);
    // Setzt einen passenden Prescaler-Wert
    // Analog/Digital-Wandler-Frequenz = CPU-Frequenz / Prescaler-Wert
    // Die Wandler-Frequenz sollte zwischen 50kHz und 200kHz liegen
    // In unserem Fall: 16MHz / 128 = 125kHz
    ADCSRA = (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);
}

void JoystickLow::update() {
    posX = getPosX(true);
    posY = getPosY(true);
    button = getButton(true);
}

int16_t JoystickLow::getPosX(bool immediate) {
    if(immediate) {
        ADMUX = (ADMUX & 0xE0) |7;
        ADCSRA |= (1 << ADEN) | (1 << ADSC);

        // Solange das ADSC-Bit im ADCSRA Register 1 ist, ist der Umwandlungsprozess noch nicht abgeschlossen
        // Daher warten wir, bis dieses Bit 0 ist
        while (ADCSRA & (1 << ADSC));

        // Lese das Umwandlungsergebnis aus
        int low = ADCL; // Zuerst immer ADCL auslesen!
        int high = ADCH; // Erst dann ADCH auslesen!
        int value = (high << 8) | low; // Das endgültige Ergebnis zusammenbauen

        value -= 512;
        if(abs(value) <= deadzone){
            value = 0;
        }

        return value;
    }else{
        return posX;
    }
}

int16_t JoystickLow::getPosY(bool immediate) {
    if(immediate) {
        ADMUX = (ADMUX & 0xE0) | 6;
        ADCSRA |= (1 << ADEN) | (1 << ADSC);

        // Solange das ADSC-Bit im ADCSRA Register 1 ist, ist der Umwandlungsprozess noch nicht abgeschlossen
        // Daher warten wir, bis dieses Bit 0 ist
        while (ADCSRA & (1 << ADSC));

        // Lese das Umwandlungsergebnis aus
        int low = ADCL; // Zuerst immer ADCL auslesen!
        int high = ADCH; // Erst dann ADCH auslesen!
        int value = (high << 8) | low; // Das endgültige Ergebnis zusammenbauen

        value -= 512;
        if(abs(value) <= deadzone){
            value = 0;
        }

        return value;
    }else{
        return posY;
    }
}

bool JoystickLow::getButton(bool immediate) {
    if(immediate) {
        return PINE & (1<< PE2);  // List aktuellen Status von PE2 aus

    }else{
        return button;
    }
}

void JoystickLow::setDeadzone(int16_t deadzone) {
    this->deadzone = deadzone;
}

int16_t JoystickLow::getDeadzone() {
    return deadzone;
}
