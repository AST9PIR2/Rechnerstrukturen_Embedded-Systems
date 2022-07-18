#include "JoystickHigh.h"

//	Konstruktor
JoystickHigh::JoystickHigh(int X_Pin, int Y_Pin, int Button){

	this->X_Pin = X_Pin;				//	Initialisieren des X-Eingangs
	this->Y_Pin = Y_Pin;				//	Initialisieren des Y-Eingangs

	pinMode(X_Pin, INPUT);
	pinMode(Y_Pin, INPUT);

	this->Button = Button;		//	Initialisieren des Tasters

	//	Sollte der Pin für den Taster auf "Ausgang" (= 1) geschaltet sein -> Korrektur mit XOR
	if(DDRE & (1 << Button)){
		DDRE ^= (1 << Button);
	}

	this->deadzone = 10;				//	Werte meines Boards weichen um 5-7 ab. Um Schwankungen zu vermeiden auf 10 aufgerundet
}

//	Setter für die Deadzone des Joysticks
void JoystickHigh::setDeadzone(int deadzone){

	this->deadzone = deadzone;
}

//	Auslesen der X-Koordinate
int JoystickHigh::get_X(){

	//	Aufteilen des Wertebereichs in -512 - 0 - 512
	int coordinate = map(analogRead(this->X_Pin), 0, 1023, -512, 512);

	//	Prüfen, ob die ausgelesene Koordinate über/unter der Deadzone liegt
	if(coordinate < this->deadzone*(-1) || coordinate > this->deadzone){

		return coordinate;
	}
	else{

		return 0;	//	Sonst: Rückgabe 0
	}
}

//	Auslesen der Y-Koordinate
int JoystickHigh::get_Y(){

	//	Aufteilen des Wertebereichs in -512 - 0 - 512
	int coordinate = map(analogRead(Y_Pin), 0, 1023, -512, 512);

	//	Prüfen, ob die ausgelesene Koordinate über/unter der Deadzone liegt
	if(coordinate < this->deadzone*(-1) || coordinate > this->deadzone){

		return coordinate;
	}
	else{

		return 0;	//	Sonst: Rückgabe 0
	}
}

//	Auslesen der invertierten X-Koordinate
int JoystickHigh::get_inv_X(){

	return this->get_X()*(-1); // Multiplizieren des Ergebnisses der normalen Funktion mit -1
}

//	Auslesen der invertierten Y-Koordinate
int JoystickHigh::get_inv_Y(){

	return this->get_Y()*(-1); // Multiplizieren des Ergebnisses der normalen Funktion mit -1
}

//	Auslesen des Status des Tasters und Rückgabe von true wenn betätigt, sonst false
bool JoystickHigh::get_Button(){

	if(PINE & (1 << this->Button)){

		return true;
	}
	else{

		return false;
	}
}
