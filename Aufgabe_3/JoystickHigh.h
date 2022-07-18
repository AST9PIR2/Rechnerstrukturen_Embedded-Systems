//	Einfügen der Arduino-Bibliothek
#include <Arduino.h>
#include <avr/io.h>

#ifndef JOYSTICKHIGH_H_
#define JOYSTICKHIGH_H_

class JoystickHigh {

private:

	int X_Pin;		//	Eingangs-Pin für die X-Achse
	int Y_Pin;		//	Eingangs-Pin für die Y-Achse
	int Button;	//	Eingangs-Pin für den Taster
	int deadzone;	//	Variable für die Deadzone des Joysticks

public:

	//	Konstruktor
	JoystickHigh(int X_Pin, int Y_Pin, int Button);

	//	Auslesefunktionen für die normale Position
	int get_X();
	int get_Y();

	//	Auslesefunktionen für die invertierte Position
	int get_inv_X();
	int get_inv_Y();

	//	Auslesenfunktion für den Taster des Joysticks
	bool get_Button();

	//	Setter für eine einstellbare Deadzone
	void setDeadzone(int deadzone);
};

#endif /* JOYSTICKHIGH_H_ */
