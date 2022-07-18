//
// Created by Pirmin on 22.06.2022.
//

#include "temperature.h"
#include <Wire.h>

void TemperatureSensor::begin() {

    Wire.begin();

    Wire.beginTransmission(I2C_ADDR);
    Wire.write(0x01);
    Wire.write((this->resolution << 5)|(3 << 3)|(1 << 2)|(1 << 1));
    Wire.endTransmission();
    this->sensorSleep = false;
}

void TemperatureSensor::switchToContinuousMode() {

    begin();
    update();

}

void TemperatureSensor::switchToOneShotMode() {

    sleep();

    Wire.beginTransmission(I2C_ADDR);
    Wire.write(0x01);
    Wire.write(1);
    Wire.write((1 << 7));
    Wire.endTransmission();
    this->sensorSleep = true;

}

void TemperatureSensor::setResolution(uint8_t res){

    if(res == 9){
        this->resolution = 0;
    }
    else if(res == 10){
        this->resolution = 1;
    }
    else if(res == 11){
        this->resolution = 2;
    }
    else if(res == 12){
        this->resolution = 3;
    }
    if(!sensorSleep){
        begin();
    }
}

void TemperatureSensor::update(){

    Wire.beginTransmission(I2C_ADDR);
    Wire.write(0x00);
    Wire.endTransmission(I2C_ADDR);

    Wire.requestFrom(I2C_ADDR, 2);

    if(Wire.available() == 2){

        uint8_t buffer[2];
        Wire.readBytes(buffer, 2);

        int combined = buffer[0] << 8;
        combined |= buffer[1];
        combined = combined >> 4;

        float temperature = (float) combined / 16;
        currentTemperature = temperature;
        //Serial.print("Temperature: ");
        //Serial.println(currentTemperature);
    }
    else{

        float temperature = -273.0;
        currentTemperature = temperature;
    }
}

float TemperatureSensor::getTemperature(bool immediate) {
    if(immediate) {
        update();
        return currentTemperature;
    }else{
        return currentTemperature;
    }
}

void TemperatureSensor::sleep(){

    Wire.beginTransmission(I2C_ADDR);
    Wire.write(0x01);
    Wire.write(1);
    Wire.endTransmission();
    this->sensorSleep = true;
}