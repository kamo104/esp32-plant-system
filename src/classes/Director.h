#ifndef DIRECTOR_H
#define DIRECTOR_H


#include <Arduino.h>

#include "Menu.h"
#include "Display.h"
#include "Page.h"
#include "../input/ButtonEvent.h"
#include "../input/ButtonConfig.h"

#include "../numbers/DisplayNumber.h"
#include "../numbers/BoundedNumber.h"


// responsible for navigating through the menu and displaying appropriate things
class Director{
    // true: browsing pages
    // false: changing values in a page
    bool browseMode=true;
    ButtonConfig* buttonConfig;
    Menu* menu;
    Display* display;
    // InputManager* inputManager;

    DisplayNumber* currentChangingValue;
    uint8_t currentDisplayNumber=0;

    public:
    bool needToRedisplayCurrentPage=true;

    void displayCurrentPage(){
        if(needToRedisplayCurrentPage==false) return;

        needToRedisplayCurrentPage=false;
        this->display->displayPage(this->menu->currentPage(), !this->browseMode);
    }

    void confirm(){
        // if we can nest, always nest
        if(this->menu->currentPage()->subpagesNum>0){
            this->menu->nestNavigation();

            this->needToRedisplayCurrentPage=true;
            return;
        }

        // if we can't nest anymore select a value to work with
        else if(this->browseMode && this->menu->currentPage()->displayValuesNum > 0 && this->menu->currentPage()->displayValues[0].editable){
            this->browseMode = false;
            this->currentDisplayNumber=0;

            this->currentChangingValue = &this->menu->currentPage()->displayValues[0];

            this->needToRedisplayCurrentPage=true;
            return;
        }
        else if(this->browseMode==false 
            && this->currentDisplayNumber+1 < this->menu->currentPage()->displayValuesNum // if there is a number yet to be changed 
            && this->menu->currentPage()->displayValues[this->currentDisplayNumber+1].editable) // if the said number is subject to change
            { 

            this->currentChangingValue = &this->menu->currentPage()->displayValues[++this->currentDisplayNumber];

        }
        else if(this->browseMode==false){
            this->browseMode=true;
            this->needToRedisplayCurrentPage=true;
            return;
        }

        
    }

    void goLeft(){
        // if we are just browsing go to previous page
        if(this->browseMode==true){
            this->menu->previousPage();
            this->needToRedisplayCurrentPage=true;
            return;
        }

        // if we are changing a value, add a step and check if we need to refresh the displayed value
        this->currentChangingValue->operator--();

        this->needToRedisplayCurrentPage=true;
        return;
    }

    void goRight(){
        if(this->browseMode==true){
            this->menu->nextPage();
            this->needToRedisplayCurrentPage=true;
            return;
        }
        this->currentChangingValue->operator++();

        this->needToRedisplayCurrentPage=true;
    }

    void goBack(){
        if(this->browseMode==true){
            Page* previousPage = this->menu->currentPage();
            this->menu->denestNavigation();
            this->needToRedisplayCurrentPage=true;
            Page* currentPage = this->menu->currentPage();
            // if we are in the starting pages let us go to the first page
            if(previousPage->index==currentPage->index) for(int i=0;i<4;i++) this->menu->previousPage();
            
            return;
        }

        this->browseMode=true;
        this->needToRedisplayCurrentPage=true;
    }   


    Director(Menu* menu, Display* display){
        this->menu = menu;
        this->display = display;
    }
};

#endif