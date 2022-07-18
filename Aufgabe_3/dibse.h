#ifndef DIBSE_H_
#define DIBSE_H_

#include <Arduino.h>
#include <Servo.h>
#include <Adafruit_NeoPixel.h>
#include <LedMatrix.h>
#include "JoystickHigh.h"

#define RGB_LED_PIN A4
#define TRIGGER_PIN 8
#define ECHO_PIN 4

#define LATCH_PIN 11
#define DATA_PIN 16
#define CLOCK_PIN 15

#define LEFT_SERVO 9
#define RIGHT_SERVO 10

#define JOY_X A0
#define JOY_Y A1
#define BUTTON 2


//	Klasse DibsE
class DibsE {

private:

	int red;		//	Rotwert
	int green;		//	Grünwert
	int blue;		//	Blauwert
	int duration;	//	Dauer
	bool blinking;	//	Variable zur Überprüfung, ob geblinkt werden soll

	int buffer[8];	//	Puffer für 8 Abstandswerte
	int write_pos;	//	Schreibposition (oder Ende des Puffers)

	unsigned long rgb_last_on;	//	Speichervariable für den Zeitpunkt an dem die RGB-LED angeschalten wird
	unsigned long last_update;	//	Speichervariable für den Zeitpunkt der letzten Aktualisierung der Matrix (alle 3 Sekunden)

	//	Initialisieren der RGB-LED
	Adafruit_NeoPixel rgbLED = Adafruit_NeoPixel(1, RGB_LED_PIN, NEO_GRB + NEO_KHZ800);
	//	Initialisieren der LED-Matrix
	LedMatrix ledMatrix = LedMatrix(LATCH_PIN, DATA_PIN, CLOCK_PIN);

	//	Initialisieren des rechten Servos
	Servo rightWheel;
	//	Initialisieren des linken Servos
	Servo leftWheel;

	//	Initialisieren des Joysticks
	JoystickHigh Joystick = JoystickHigh(JOY_X, JOY_Y, BUTTON);

public:

	//	Default Konstruktor
	DibsE();
	//	Setup-Funktion der Klasse
	void setup();
	//	Loop-Funktion der Klasse
	void loop();
	//	Funktion zum Setzen der Objektvariablen
	void simpleBlinkOn(int duration, int red, int green, int blue);
	//	Funktion zum Stoppen des Blinkens
	void simpleBlinkOff();
	//	Blinken zeitlich getimed
	void Blink(unsigned long time);
	//	Festlegen einer neuen Blinkdauer abgeleitet von der gemessenen Distanz
	void set_dist_Duration(int distance);
	//	Funktion zur Entfernungsmessung, Rückgabe in cm
	int readDistance();
	//	Beschreiben des Ringpuffers
	void writeBuffer(int distance);
	//	Ausgabe auf der Matrix
	void printBuffer();
	//	Einstellen der Geschwindigkeit der Servo-Motoren
	void setSpeed(int speedLeftWheel, int speedRightWheel);
	//	Steuern der Räder mittels des Joysticks
	void wheelRemote();
};

#endif /* DIBSE_H_ */
