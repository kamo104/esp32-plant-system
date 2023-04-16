#ifndef INTERRUPTS_INIT_H
#define INTERRUPTS_INIT_H

#include "../config/definitions.h"
#include "../config/variablesInit.h"
#include "../input/ButtonConfig.h"

void leftButtonInterrupt(){
    buttonPresses[buttonConfig.leftButtonIndex] = true;
}
void rightButtonInterrupt(){
    buttonPresses[buttonConfig.rightButtonIndex] = true;
}
void enterButtonInterrupt(){
    buttonPresses[buttonConfig.enterButtonIndex] = true;
}
void backButtonInterrupt(){
    buttonPresses[buttonConfig.backButtonIndex] = true;
}

void interruptsInit(){
    attachInterrupt(LEFT_BUTTON_PIN,leftButtonInterrupt,FALLING);
    attachInterrupt(RIGHT_BUTTON_PIN,rightButtonInterrupt,FALLING);
    attachInterrupt(ENTER_BUTTON_PIN,enterButtonInterrupt,FALLING);
    attachInterrupt(BACK_BUTTON_PIN,backButtonInterrupt,FALLING);
}

#endif