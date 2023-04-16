#ifndef BUTTON_EVENT_H
#define BUTTON_EVENT_H

#include <Arduino.h>


struct ButtonEvent{
    unsigned long timestamp;
    uint8_t buttonIndex;
    int buttonState;
};


#endif