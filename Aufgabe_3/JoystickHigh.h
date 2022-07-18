//	Einf�gen der Arduino-Bibliothek
#include <Arduino.h>
#include <avr/io.h>

#ifndef JOYSTICKHIGH_H_
#define JOYSTICKHIGH_H_

class JoystickHigh {

private:

	int X_Pin;		//	Eingangs-Pin f�r die X-Achse
	int Y_Pin;		//	Eingangs-Pin f�r die Y-Achse
	int Button;	//	Eingangs-Pin f�r den Taster
	int deadzone;	//	Variable f�r die Deadzone des Joysticks

public:

	//	Konstruktor
	JoystickHigh(int X_Pin, int Y_Pin, int Button);

	//	Auslesefunktionen f�r die normale Position
	int get_X();
	int get_Y();

	//	Auslesefunktionen f�r die invertierte Position
	int get_inv_X();
	int get_inv_Y();

	//	Auslesenfunktion f�r den Taster des Joysticks
	bool get_Button();

	//	Setter f�r eine einstellbare Deadzone
	void setDeadzone(int deadzone);
};

#endif /* JOYSTICKHIGH_H_ */
