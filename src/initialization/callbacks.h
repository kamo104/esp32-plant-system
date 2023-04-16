#ifndef CALLBACKS_H
#define CALLBACKS_H

#include <Arduino.h>

#include "../config/definitions.h"
#include "../config/variablesInit.h"


void markLedChange(){
    lastLedChange = millis();
}

void onRedChange(float currentAmount){
    ledcWrite(redLedChannel, (int)((currentAmount*ledScalingFactor*(brightnessNumber->value()*ledScalingFactor/maxDutyCycleValue)))); 
    markLedChange();

}

void onGreenChange(float currentAmount){
    ledcWrite(greenLedChannel, (int)((currentAmount*ledScalingFactor*(brightnessNumber->value()*ledScalingFactor/maxDutyCycleValue)))); 
    markLedChange();

}

void onBlueChange(float currentAmount){
    ledcWrite(blueLedChannel, (int)((currentAmount*ledScalingFactor*(brightnessNumber->value()*ledScalingFactor/maxDutyCycleValue)))); 
    markLedChange();

}

void onBacklightChange(float currentAmount){
    if(currentAmount==0) lcd->noBacklight();
    else lcd->backlight();
    return;
}

void onBrightnessChange(float currentAmount){
    onRedChange(redNumber->value());
    onGreenChange(greenNumber->value());
    onBlueChange(blueNumber->value());
}
#endif