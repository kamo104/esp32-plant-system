#ifndef LED_INIT_H
#define LED_INIT_H

#include "../config/definitions.h"

void ledInit(){
    // led pins 
    ledcSetup(redLedChannel, freq, resolution);
    ledcSetup(greenLedChannel, freq, resolution);
    ledcSetup(blueLedChannel, freq, resolution);

    ledcAttachPin(RED_PIN, redLedChannel);
    ledcAttachPin(GREEN_PIN, greenLedChannel);
    ledcAttachPin(BLUE_PIN, blueLedChannel);
}

#endif