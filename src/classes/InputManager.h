#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "../input/ButtonConfig.h"
#include "Director.h"
#include "../numbers/BoundedNumber.h"

// responsible for taking in inputs and forwarding them appropriately to the director
class InputManager{
    Director* director;

    ButtonEvent heldButtons[4]; //despite being named held, sometimes has events that have HIGH states (not pressed)
    BoundedNumber buttonTriggerInterval[4];

    void (Director::*buttonFunctions[4])();

    void buttonPressLogic(ButtonEvent ev,void (Director::*buttonFunction)(void)){
        if(heldButtons[ev.buttonIndex].buttonState==HIGH){

            // execute the given function
            (this->director->*buttonFunction)();

            // since this is the first time ev.state is LOW, register this as a holdButton starting event
            heldButtons[ev.buttonIndex] = ev;
            return;
        }
        // if buttonHold starting event had LOW state and is bigger than threshold value
        else if(ev.timestamp-this->heldButtons[ev.buttonIndex].timestamp>this->buttonTriggerInterval[ev.buttonIndex].value()){

            this->heldButtons[ev.buttonIndex]=ev;

            this->buttonTriggerInterval[ev.buttonIndex].operator--();

            // execute the given function
            (this->director->*buttonFunction)();

            return;
        }
    }

    public:
    void registerButtonEvent(ButtonEvent ev){
        if(ev.buttonState==HIGH){
            // prevent rapid change low->high->low
            if(ev.timestamp - this->heldButtons[ev.buttonIndex].timestamp > 200)
            this->heldButtons[ev.buttonIndex] = ev;
            // reset the trigger interval
            this->buttonTriggerInterval[ev.buttonIndex].resetValue();
            return;
        } 

        // execute a right function based on buttonIndex
        this->buttonPressLogic(ev, buttonFunctions[ev.buttonIndex]);
        lastHumanInteraction = ev.timestamp;

    }
    InputManager(Director* director){
        this->director = director;

        this->buttonFunctions[buttonConfig.leftButtonIndex] = &Director::goLeft;
        this->buttonFunctions[buttonConfig.rightButtonIndex] = &Director::goRight;
        this->buttonFunctions[buttonConfig.enterButtonIndex] = &Director::confirm;
        this->buttonFunctions[buttonConfig.backButtonIndex] = &Director::goBack;


        for(int i=0;i<4;i++) this->buttonTriggerInterval[i] = BoundedNumber(300,1,300,40);
       
    }
};


#endif