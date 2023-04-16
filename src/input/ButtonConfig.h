#ifndef BUTTON_CONFIG_H
#define BUTTON_CONFIG_H

#include <Arduino.h>
#include "../config/definitions.h"


class ButtonConfig{
    public:
    uint8_t leftButtonPin = LEFT_BUTTON_PIN;
    uint8_t rightButtonPin = RIGHT_BUTTON_PIN;
    uint8_t enterButtonPin = ENTER_BUTTON_PIN;
    uint8_t backButtonPin = BACK_BUTTON_PIN;

    uint8_t leftButtonIndex=0;
    uint8_t rightButtonIndex=1;
    uint8_t enterButtonIndex=2;
    uint8_t backButtonIndex=3;

    // takes index returns pin number
    uint8_t& operator[](int which){
        switch(which){
            case(0):{
                return this->leftButtonPin;
            }
            case(1):{
                return this->rightButtonPin;
            }
            case(2):{
                return this->enterButtonPin;
            }
            case(3):{
                return this->backButtonPin;
            }
        }
        
        return this->leftButtonPin;
    }
    ButtonConfig(){}
    ButtonConfig(uint8_t leftButtonPin, uint8_t rightButtonPin, uint8_t enterButtonPin, uint8_t backButtonPin){
        this->leftButtonPin = leftButtonPin;
        this->rightButtonPin = rightButtonPin;
        this->enterButtonPin = enterButtonPin;
        this->backButtonPin = backButtonPin;
    }
};

ButtonConfig buttonConfig;

#endif