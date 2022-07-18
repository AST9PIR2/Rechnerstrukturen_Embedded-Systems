#include "dibse.h"

//	Default Konstruktor
DibsE::DibsE(){

	this->red = 0;
	this->green = 0;
	this->blue = 0;

	this->duration = 0;
	this->blinking = false;

	this->rgb_last_on = 0;

	this->write_pos = 0;

	for(int i = 0; i < 8; i++){
		this->buffer[i] = 0;
	}

	this->last_update = 0;
}
//	Setup-Funktion der Klasse
void DibsE::setup() {

	//	Start der seriellen Ausgabe
	Serial.begin(9600);

	//	Auskommentieren von nicht benötigten Funktionen der letzten Hausaufgaben
	/*this->rgbLED.begin();

	//	Initialisieren der Pins für den Abstandssensor
	pinMode(TRIGGER_PIN, OUTPUT);
	pinMode(ECHO_PIN, INPUT);
	 */

	//	Einschalten der Servos
	this->leftWheel.attach(LEFT_SERVO);
	this->rightWheel.attach(RIGHT_SERVO);
}
//	Loop-Funktion der Klasse
void DibsE::loop() {

	//	Auskommentieren von nicht benötigten Funktionen der letzten Hausaufgaben
	/*
	//	Messen der Zeit seit Programmstart
	unsigned long time = millis();

	//	Messen der Distanz zu einem Objekt
	int distance = readDistance();

	//	Serielle Ausgabe der Entfernung
	Serial.print("Distanz: ");
	Serial.print(distance);
	Serial.println(" cm");

	//	Berechnen einer neuen Blinkdauer
	this->set_dist_Duration(distance);

	//	Alle 3 Sekunden, führe folgendes aus ...
	if(time >= this->last_update + 3000){

		ledMatrix.clear();					//	"Bereinigen" der Matrix

		this->writeBuffer(distance);		//	Schreiben der gemessenen Distanz in den Puffer

		this->printBuffer();				//	Ausgabe des Puffers auf der Matrix

		this->last_update = millis();		//	Erneuern der Messvariable für die nächsten 3 Sekunden
	}

	ledMatrix.update();						//	Updaten der Matrix damit die Änderungen angezeigt werden

	//	Speichern der momentanen Betriebszeit
	time = millis();

	//	Steuern des Blinkens anhand der gemessenen Betriebszeit
	this->Blink(time);
	*/

	//	Fernsteuern der Servos mittels des Joysticks
	this->wheelRemote();
}
//	Funktion zum Setzen der Objektvariablen
void DibsE::simpleBlinkOn(int duration, int red, int green, int blue){

	if(duration > 0){

		this->duration = duration;
	}
	else{

		this->duration = 0;
	}

	if(red >= 0){

		if(red < 255){

			this->red = red;
		}
		else{

			this->red = 255;
		}
	}
	else{

		this->red = 0;
	}

	if(green >= 0){

		if(green < 255){

			this->green = green;
		}
		else{

			this->green = 255;
		}
	}
	else {

		this->green = 0;
	}

	if(blue >= 0){

		if(blue < 255){

			this->blue = blue;
		}
		else{

			this->blue = 255;
		}
	}
	else {

		this->blue = 0;
	}

	this->rgb_last_on;
	this->blinking = true;
}
//	Funktion zum Stoppen des Blinkens
void DibsE::simpleBlinkOff(){

	this->red = 0;
	this->green = 0;
	this->blue = 0;
	this->duration = 0;
	this->blinking = false;
}
//	LED-Blinken getimed
void DibsE::Blink(unsigned long time){

	if(this->blinking){

		if(time >= this->rgb_last_on + this->duration){
			this->rgbLED.setPixelColor(0, this->red, this->green, this->blue);
			this->rgbLED.show();
		}

		if(time >= this->rgb_last_on + this->duration*2){
			this->rgbLED.setPixelColor(0, 0, 0, 0);
			this->rgbLED.show();
			this->rgb_last_on = millis();
		}
	}
}
//	Festlegen einer neuen Blinkdauer abgeleitet von der gemessenen Distanz
void DibsE::set_dist_Duration(int distance){

	//	Entfernung 0cm - 5cm -> Blinkdauer 20ms
	if(distance <= 5){
		this->duration = 20;
	}
	//	Entfernung 5cm - 10cm -> Blinkdauer 50ms
	else if(distance < 10){
		this->duration = 40;
	}
	//	Entfernung über 1m -> Blinkdauer -> 500ms
	else if(distance > 100){
		this->duration = 400;
	}
	//	Entfernung 10cm - 1m -> Blinkdauer (in ms) = 5 x die Entfernung in cm (Empirischer Wert, nach eigenem Empfinden)
	else if(distance > 0){
		this->duration = distance*4;
	}
}
//	Funktion zur Entfernungsmessung (Rückgabe in cm)
int DibsE::readDistance(){

	long duration = 0;

	//	Aussenden eines Signals
	digitalWrite(TRIGGER_PIN, LOW);
	delay(5);
	digitalWrite(TRIGGER_PIN, HIGH);
	delay(10);
	digitalWrite(TRIGGER_PIN, LOW);

	//	Empfangen des Signals und speichern der Dauer
	pinMode(ECHO_PIN, INPUT);
	duration = pulseIn(ECHO_PIN, HIGH);

	//	Errechnen der Entfernung in cm (daher / 29.1)
	int distance = (duration/2) / 29.1;

	//	Rückgabe der errechneten Entfernung
	//	Da der Sensor bis maximal 4m und minimal 2cm messen kann
	//	(Quelle: https://randomnerdtutorials.com/complete-guide-for-ultrasonic-sensor-hc-sr04/)
	//	Sollte der Messwert größer sein als die Maximaldistanz
	if(distance > 400){

		return 400;	//	Um Fehler zu vermeiden, rückgabe von 4m, sollte die Distanz größer sein
	}
	//	Sollte die Distanz unter der Minimaldistanz liegen
	else if(distance < 2){

		return 0;	//	Rückgabe von 0, um negative Werte auszuschließen
	}
	//	Ist die Distanz unter 4 Metern und nicht negativ (also unter normalen Umständen)
	else {

		return distance;	//	Rückgabe der gemessenen Distanz
	}
}
//	Beschreiben eines Ringpuffers
void DibsE::writeBuffer(int distance){

	//	Schreiben des übergebenen Abstandswertes an die Position write_pos
	this->buffer[this->write_pos] = distance;

	//	Weiterwandern der Schreibposition
	if(this->write_pos >= 7){	//	Sollte die Position über das Array hinauswandern
		this->write_pos = 0;	//	Rücksetzen an den Anfang des Arrays
	}
	else{
		this->write_pos++;		//	Sonst, normal weiterwandern
	}
}
//	Ausgabe des Puffers auf der LED-Matrix
void DibsE::printBuffer(){

	int pos = this->write_pos - 1;	//	Startpunkt des Auslesevorgangs Puffer -> tmp_array
	int tmp_array[8] = {0};			//	Array, in das die Distanzen im Puffer sortiert (neuester Wert <-> ältester Wert) kopiert werden

	//	Übertragen der Werte aus dem Puffer in ein Array (zur geordneten Ausgabe, neuester Wert zuerst)
	for(int counter = 0; counter < 8; counter++){

		if(pos < 0){	//	Würde der Positionszähler über das Array hinauswandern
			pos = 7;	//	Reset an das Ende des Arrays
		}

		tmp_array[counter] = this->buffer[pos];	//	Übertragen des Wertes in tmp_array
		pos--;									//	Weiterwandern im Puffer
	}

	//	Ausgabe des neuen Arrays
	for(int i = 0; i < 8; i++){		//	Durchwandern des tmp_array und einteilen der Höhe nach dem wert

		int value = tmp_array[i];	//	Wert des sortierten Arrays an Position i
		int pixel_count = 0;		//	Anzahl, wieviele Pixel ausgegeben werden sollen

		//	Einteilen der Höhe nach meinen Kriterien (bis 5cm - 8 Pixel, bis 10 - 7, bis 20 - 6, ...)
		if(value == 0){
			pixel_count = 0;
		}
		else if(value <= 5){
			pixel_count = 8;
		}
		else if(value <= 10){
			pixel_count = 7;
		}
		else if(value <= 20){
			pixel_count = 6;
		}
		else if(value <= 30){
			pixel_count = 5;
		}
		else if(value <= 50){
			pixel_count = 4;
		}
		else if(value <= 70){
			pixel_count = 3;
		}
		else if(value <= 110){
			pixel_count = 2;
		}
		else{
			pixel_count = 1;
		}

		//	Ausgabe der Spalte i
		for(int line = 0; line < pixel_count; line++){
			ledMatrix.drawPixel(i, line, true);
		}
	}
}
//	Einstellen der Geschwindigkeit der Servo-Motoren
void DibsE::setSpeed(int speedLeftWheel, int speedRightWheel){

	this->leftWheel.write(speedLeftWheel);		// Setzen des linken Rades auf Geschwindigkeit speedLeftWheel
	this->rightWheel.write(speedRightWheel);	// Setzen des rechten Rades auf Geschwindigkeit speedRightWheel
}
//	Auslesen des Joysticks und Steuerung der Räder
void DibsE::wheelRemote(){

	//	Auslesen der Joystickkoordinaten
	int x_coordinate = Joystick.get_X();
	int y_coordinate = Joystick.get_Y();

	//	Umrechnen der Koordinaten in Geschwindigkeit (-90 - 0 - 90)
	double x_speed = (x_coordinate / 512.0) * 90;
	double y_speed = (y_coordinate / 512.0) * 90;

	//	Serielle Ausgabe der Geschwindigkeiten zur Überprüfung
	Serial.print("X = ");
	Serial.print(x_speed);
	Serial.print(" Y = ");
	Serial.println(y_speed);

	//	Abfragen der Koordinaten
	//	Stick nach links
	if(x_coordinate < 0 && y_coordinate == 0){

		this->setSpeed(90 + x_speed, 90 + x_speed);	//	Drehung auf der Stelle nach links
	}
	//	Stick nach rechts
	else if(x_coordinate > 0 && y_coordinate == 0){

		this->setSpeed(90 + x_speed, 90 + x_speed);	//	Drehung auf der Stelle nach rechts
	}
	//	Stick nach unten
	else if(y_coordinate < 0 && x_coordinate == 0){

		this->setSpeed(90 + y_speed, 90 - y_speed);	//	Fahre nach hinten
	}
	//	Stick nach oben
	else if(y_coordinate > 0 && x_coordinate == 0){

			this->setSpeed(90 + y_speed, 90 - y_speed);	//	Fahre nach oben
	}
	//	Stick nach rechts oben
	else if(x_coordinate > 0 && y_coordinate > 0){

		this->setSpeed(90 + x_speed, 90 - (y_speed/5));	//	Fahre Rechtskurve
	}
	//	Stick nach links oben
	else if(x_coordinate < 0 && y_coordinate > 0){

		this->setSpeed(90 + (y_speed/5), 90 + x_speed);	//	Fahre Linkskurve
	}
	//	Stick nach rechts unten
	else if(x_coordinate > 0 && y_coordinate < 0){

			this->setSpeed(90 - x_speed, 90 - (y_speed/5));	//	Fahre Rechtskurve rückwärts
	}
	//	Stick nach links unten
	else if(x_coordinate < 0 && y_coordinate < 0){

		this->setSpeed(90 + (y_speed/5), 90 - x_speed);	//	Fahre Linkskurve rückwärts
	}
	//	Stick in Nullstellung
	else{
		this->setSpeed(90, 90);	//	Stoppe Motoren
	}
}
