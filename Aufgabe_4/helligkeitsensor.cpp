#include <Arduino.h>
#include <time.h>
#include "helligkeitsensor.h"

#define LIGHTSENSOR_PIN 	A2

unsigned long lastTime = 0;

int helligkeitsensor::loop() {

	int helligkeit = analogRead(LIGHTSENSOR_PIN);
    unsigned long time = millis();


    if (time - lastTime >= 10) {
        Serial.print("Helligkeit: ");
        Serial.println(helligkeit);
        lastTime = time;
    }
    return helligkeit;
}





