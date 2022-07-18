#include <Arduino.h>
#include "bitoperations.h"
#include "JoystickHigh.h"
#include "dibse.h"


#define RGB_LED_PIN A4


#define LED_PIN 12
#define NOTE_B5 988
#define JOYSTICK_X  A0
#define JOYSTICK_Y  A1



//Chose between LOW or HIGH level lib
JoystickHigh joystick(JOYSTICK_X,JOYSTICK_Y);
//JoystickLow joystick;

DibsE * rgb_test = new DibsE();



void setup() {
    //Set baurate for serial communication:
    Serial.begin(115200);

    //Konfiguriere Pin 12 als Output Pin.
    pinMode(LED_PIN, OUTPUT);

    //Testing bitoperations.h
    int VALUE = 0;
    int POSITION = 0;

    //Set bit
    SB(VALUE, POSITION);
    digitalWrite(LED_PIN,VALUE);
    delay(360);

    //Clear bit
    CB(VALUE, POSITION);
    digitalWrite(LED_PIN,VALUE);
    delay(360);

    //Toggle bit and check if bit high
    for(int i = 0; i < 5; i++){
        TB(VALUE, POSITION);
        digitalWrite(LED_PIN,VALUE);
        if(IBS(VALUE, POSITION)){
            tone(6, NOTE_B5, 60);
        }
        delay(60);
    }

    //Clear bit
    CB(VALUE, POSITION);
    digitalWrite(LED_PIN,VALUE);

    joystick.begin();
    joystick.setDeadzone(5);

    rgb_test->setup();
    rgb_test->loop();


}

int8_t temp = 0;
unsigned long button_timer = 0;
unsigned long timeout =1000;


void loop() {
    joystick.update();
    joystick.getPosX();

    Serial.print("Joystick: x - ");
    Serial.print(joystick.getPosX());
    Serial.print(" y - ");
    Serial.print(joystick.getPosY());
    Serial.print(" button - ");
    Serial.println(joystick.getButton());

    //Toggling bit to switch ON/OFF with button
    if(joystick.getButton()){
        //Timer to read a human switching
        if (millis() > timeout + button_timer ){
            button_timer = millis();
            TB(temp,0);
        }
    }
    Serial.print(" temp - ");
    Serial.println(temp);

    if(temp){
        rgb_test->simpleBlinkOff();
    }else{
        //Remapping for the Joystick input to 0-255 for RGB
        rgb_test->simpleBlinkOn(100,(map(joystick.getPosX(),-512,512,0,255)),
                                        (map(joystick.getPosY(),-512,512,0,255)),
                                        ((map(joystick.getPosX(),-512,512,0,255))-(map(joystick.getPosY(),-512,512,0,255))));
    }
}