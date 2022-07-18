#include <Arduino.h>
#include "sleep_delay.h"
#include "dibse.h"

//	Instanz der Klasse DibsE für unseren Roboter
DibsE robot;

void setup() {

	pinMode(LED, OUTPUT);
}


void loop() {

	digitalWrite(LED, HIGH);
	sleep_delay(BLINK);
	digitalWrite(LED, LOW);
	sleep_delay(BLINK);
}



