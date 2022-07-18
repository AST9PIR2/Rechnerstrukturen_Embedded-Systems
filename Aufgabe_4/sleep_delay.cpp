//
// Created by Pirmin on 14.06.2022.
//

#include "sleep_delay.h"
volatile bool wdtFlag = false;

void sleep::sleep_setup() {

    Serial.begin(115200);
    pinMode(LEDPIN, OUTPUT);

    cli();
    wdt_reset();
    MCUSR &= ~(1 << WDRF);
    WDTCSR = (1 << WDCE) | (1 << WDE);
    WDTCSR = (1 << WDP2) | (1 << WDP1);
    WDTCSR |= (1 << WDIE);
    sei();
}

void sleep::sleep_delay(uint32_t seconds) {

    if (wdtFlag){
        temp--;
        wdtFlag = false;
    }

    if(temp == 0){
        digitalWrite(LEDPIN, HIGH);
        delay(100);
        digitalWrite(LEDPIN, LOW);
        temp = seconds;
    }
}

ISR(WDT_vect){
    wdtFlag = true;
}
