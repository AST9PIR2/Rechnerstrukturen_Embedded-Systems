#include <Arduino.h>
#include "bitoperations.h"
#include "JoystickHigh.h"
#include "dibse.h"
#include "distance.h"


#define LED_LATCH 11
#define LED_DATA 16
#define LED_CLOCK 15

//LedMatrix ledMatrix(LED_LATCH,LED_DATA,LED_CLOCK);
//LedMatrixTextBuffer test(ledMatrix);

#define RGB_LED_PIN A4


#define LED_PIN 12
#define NOTE_B5 988
#define JOYSTICK_X  A0
#define JOYSTICK_Y  A1



//Chose between LOW or HIGH level lib
JoystickHigh joystick(JOYSTICK_X,JOYSTICK_Y);
//JoystickLow joystick;

DibsE * rgb_test = new DibsE();
//NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
Distance * distance_test = new Distance();




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


    distance_test->setup();

    // Write text into text buffer
    //test.drawText("Coco <3 ");

    //NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

    //ledMatrix.clear();


}

int8_t temp = 0;
unsigned long button_timer = 100;
unsigned long timeout =1000;
unsigned long lastTime = 0;

int i = 7;


void loop() {
    joystick.update();
    joystick.getPosX();

/*  //Change LED with Joystick
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

    if(temp){
        rgb_test->simpleBlinkOff();
    }else{
        //Remapping for the Joystick input to 0-255 for RGB
        rgb_test->simpleBlinkOn(100,(map(joystick.getPosX(),-512,512,0,255)),
                                        (map(joystick.getPosY(),-512,512,0,255)),
                                        ((map(joystick.getPosX(),-512,512,0,255))-(map(joystick.getPosY(),-512,512,0,255))));
    }
*/

    //unsigned int distance = 4*sonar.ping_cm();
    //rgb_test->simpleBlinkOn(distance,255,0,0);

    //rgb_test->simpleBlinkOn((2*sonar.ping_cm()),100,(0),0);
    //rgb_test->simpleBlinkOff();
    //delay((2*sonar.ping_cm()));
    //rgb_test->simpleBlinkOff();
    //unsigned int distance = sonar.ping_cm();
    //Serial.print(distance);
    //Serial.println("cm");
    //delay(1000);

    //distance_test->loop();

    // Clears the display buffer.
    // ledMatrix.clear();

    // Draws an x into the display buffer.
    /*
    for (uint8_t x = 0; x < 8; x++) {
        ledMatrix.drawPixel(x, x, true);
        ledMatrix.drawPixel(x, 7-x, true);
    }
    */

    distance_test->loop();

}