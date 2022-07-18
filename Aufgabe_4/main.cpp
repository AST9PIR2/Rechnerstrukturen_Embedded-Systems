#include "sleep_delay.h"
#include "temperature.h"
#include "LedMatrix.h"
#include "JoystickHigh.h"


#define LED_LATCH 11
#define LED_DATA 16
#define LED_CLOCK 15
#define JOYSTICK_X  A0
#define JOYSTICK_Y  A1

sleep sleep;
TemperatureSensor tempSensor;
LedMatrix display_space(LED_LATCH,LED_DATA,LED_CLOCK);
LedMatrixTextBuffer display(display_space);
JoystickHigh joystick(JOYSTICK_X,JOYSTICK_Y);

void setup() {

    tempSensor.begin();

    joystick.begin();
    joystick.setDeadzone(5);
}

float temp;
unsigned long timer_1;
unsigned long timer_2;
unsigned long timeout = 3000;



void loop() {

    //main1

    tempSensor.switchToOneShotMode();
    tempSensor.getTemperature(1);
    tempSensor.switchToContinuousMode();


    //main2
    joystick.update();
    joystick.getPosX();

    char buffer[10];

    dtostrf(temp,-6,3,buffer);


    if (millis() - timer_1 >= timeout) {
        timer_1 = millis();
        temp = tempSensor.getTemperature(1);
        dtostrf(temp,-5,2,buffer);
        display.drawText(buffer);
        Serial.print("Temperature: ");
        Serial.println(buffer);
    }

    if(joystick.getButton()){
        if (millis() - timer_2 >= 150) {
            timer_2 = millis();
            display.slideLeft(1);
        }
    }

    display.update();

}
