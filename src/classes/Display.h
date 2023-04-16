#ifndef DISPLAY_H
#define DISPLAY_H

#include <LiquidCrystal_I2C.h>
#include <Arduino.h>
#include "../config/definitions.h"
#include "../misc/functions.h"

#include "Page.h"
#include "../numbers/DisplayNumber.h"


class Display{
    LiquidCrystal_I2C* lcd;
    uint8_t displayHeight;
    uint8_t displayWidth;

    

    public:
    void createDegreesSymbol(){
        byte degree[] = {
        0b00110,
        0b01001,
        0b01001,
        0b00110,
        0b00000,
        0b00000,
        0b00000,
        0b00000
        };
        this->lcd->createChar(0,degree);
        this->lcd->home();
    }
    

    // browsingSignPosition == top(0) || bottom(1)
    void displayPage(Page* page, bool browsingSignPosition){

        // display the page title
        this->lcd->clear();
        this->lcd->setCursor(0,0);
        this->lcd->print(page->title);

        //display browsing sign
        this->lcd->setCursor(LCD_WIDTH-2,browsingSignPosition);
        this->lcd->print("<-");

        // if there are no values to print don't print anything in the second row
        if(page->displayValuesNum==0) return;
        for(int i=0; i<page->displayValuesNum; i++){
            switch(page->displayValues[i].valueType){
                case(0):{ // any number
                    this->lcd->setCursor(page->displayValues[i].widthPosition,page->displayValues[i].heightPosition);
                    this->lcd->print(page->displayValues[i].value(),0);
                    break;
                }
                case(1):{ // temperature number
                    this->lcd->setCursor(page->displayValues[i].widthPosition,page->displayValues[i].heightPosition);
                    this->lcd->print("T:");
                    this->lcd->print(page->displayValues[i].value(),1);
                    this->lcd->write(0); // degrees symbol
                    this->lcd->print("C");
                    break;
                }
                case(2):{ // humidity number
                    this->lcd->setCursor(page->displayValues[i].widthPosition,page->displayValues[i].heightPosition);
                    this->lcd->print("H:");
                    this->lcd->print(page->displayValues[i].value(),0);
                    this->lcd->print("%");
                    break;
                }
                case(3):{ // hour number with spacer ex: 05:
                    this->lcd->setCursor(page->displayValues[i].widthPosition,page->displayValues[i].heightPosition);
                    if(numberLength(page->displayValues[i].value())==0) this->lcd->print(0);
                    this->lcd->print(page->displayValues[i].value(),0);
                    this->lcd->print(":");
                    break;
                }
                case(4):{ // ordinary minute number ex: 05
                    this->lcd->setCursor(page->displayValues[i].widthPosition,page->displayValues[i].heightPosition);
                    if(numberLength(page->displayValues[i].value())==0) this->lcd->print(0);
                    this->lcd->print(page->displayValues[i].value(),0);
                    break;
                }
                case(5):{ // minute number and seperator after
                    this->lcd->setCursor(page->displayValues[i].widthPosition,page->displayValues[i].heightPosition);
                    if(numberLength(page->displayValues[i].value())==0) this->lcd->print(0);
                    this->lcd->print(page->displayValues[i].value(),0);
                    this->lcd->print(" - ");
                    break;
                }
            }
        }
    }

    Display(uint8_t displayHeight, uint8_t displayWidth, LiquidCrystal_I2C* lcd){
        this->lcd = lcd;
        this->displayHeight = displayHeight;
        this->displayWidth = displayWidth;
    }
};

#endif