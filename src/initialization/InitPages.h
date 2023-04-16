#pragma once

#include "../classes/Page.h"
#include "../numbers/DisplayNumber.h"

#include "../config/definitions.h"
#include "../config/variablesInit.h"

#include "callbacks.h"



Page* createWeatherPage(){
    Page* weatherPage = new Page;
    DisplayNumber* displayNumbers = new DisplayNumber[4];

    // setting temperature number
    displayNumbers[0] = DisplayNumber(0,-20,50,0,0,1,0,1); 
    temperatureNumber = &displayNumbers[0];

    // setting humidity number
    displayNumbers[1] = DisplayNumber(0,0,100,0,0,2,10,1);
    humidityNumber = &displayNumbers[1];

    // setting hours number
    displayNumbers[2] = DisplayNumber(0,0,23,1,0,3,0,0);
    currentHour = &displayNumbers[2];

    // setting minutes number
    displayNumbers[3] = DisplayNumber(0,0,59,1,0,4,3,0);
    currentMinute = &displayNumbers[3];



    // set root page
    *weatherPage = Page(0,"",displayNumbers,4,weatherPage,nullptr,0);
    return weatherPage;
}

void createSunTimes(){
    tm date1;

    date1.tm_hour = EEPROM.read(5);
    date1.tm_min = EEPROM.read(4);
    date1.tm_sec = 0;
    sunriseStartTime.setDate(date1);
    

    date1.tm_hour = EEPROM.read(7);
    date1.tm_min = EEPROM.read(6);
    date1.tm_sec = 0;
    sunriseEndTime.setDate(date1);

    date1.tm_hour = EEPROM.read(9);
    date1.tm_min = EEPROM.read(8);
    date1.tm_sec = 0;
    sunsetStartTime.setDate(date1);

    date1.tm_hour = EEPROM.read(11);
    date1.tm_min = EEPROM.read(10);
    date1.tm_sec = 0;
    sunsetEndTime.setDate(date1);
}

Page* createSunrisePage(Page* parentPage){

    Page* sunrisePage;
    // sunrise page
    DisplayNumber* sunriseNumbers = new DisplayNumber[4];

    // sunrise start
    sunriseNumbers[0] = DisplayNumber(sunriseStartTime.getDate().tm_hour,0,23,1,1,3,0,1);
    sunriseStartHour = &sunriseNumbers[0];
    sunriseStartHour->setOnValueChange([](float currentVal){
        lastMilightChange = millis();
        sunriseStartTime.setHour((uint8_t)currentVal);
        });

    
    sunriseNumbers[1] = DisplayNumber(sunriseStartTime.getDate().tm_min,0,59,1,1,5,3,1);
    sunriseStartMinute = &sunriseNumbers[1];
    sunriseStartMinute->setOnValueChange([](float currentVal){
        lastMilightChange = millis();
        sunriseStartTime.setMinute((uint8_t)currentVal);
        });


    // sunrise end
    sunriseNumbers[2] = DisplayNumber(sunriseEndTime.getDate().tm_hour,0,23,1,1,3,8,1);
    sunriseEndHour = &sunriseNumbers[2];
    sunriseEndHour->setOnValueChange([](float currentVal){
        lastMilightChange = millis();
        sunriseEndTime.setHour((uint8_t)currentVal);
        });

    sunriseNumbers[3] = DisplayNumber(sunriseEndTime.getDate().tm_min,0,59,1,1,4,11,1);
    sunriseEndMinute = &sunriseNumbers[3];
    sunriseEndMinute->setOnValueChange([](float currentVal){
        lastMilightChange = millis();
        sunriseEndTime.setMinute((uint8_t)currentVal);
        });

    sunrisePage = new Page(12,"Sunrise",sunriseNumbers,4,parentPage,nullptr,0);

    return sunrisePage;
}

Page* createSunsetPage(Page* parentPage){

    
    Page* sunsetPage;
    // sunset page
    DisplayNumber* sunsetNumbers = new DisplayNumber[4];

    // sunset start
    sunsetNumbers[0] = DisplayNumber(sunsetStartTime.getDate().tm_hour,0,23,1,1,3,0,1);
    sunsetStartHour = &sunsetNumbers[0];
    sunsetStartHour->setOnValueChange([](float currentVal){
        lastMilightChange = millis();
        sunsetStartTime.setHour((uint8_t)currentVal);
        });

    
    sunsetNumbers[1] = DisplayNumber(sunsetStartTime.getDate().tm_min,0,59,1,1,5,3,1);
    sunsetStartMinute = &sunsetNumbers[1];
    sunsetStartMinute->setOnValueChange([](float currentVal){
        lastMilightChange = millis();
        sunsetStartTime.setMinute((uint8_t)currentVal);
        });


    // sunset end
    sunsetNumbers[2] = DisplayNumber(sunsetEndTime.getDate().tm_hour,0,23,1,1,3,8,1);
    sunsetEndHour = &sunsetNumbers[2];
    sunsetEndHour->setOnValueChange([](float currentVal){
        lastMilightChange = millis();
        sunsetEndTime.setHour((uint8_t)currentVal);
        });

    sunsetNumbers[3] = DisplayNumber(sunsetEndTime.getDate().tm_min,0,59,1,1,4,11,1);
    sunsetEndMinute = &sunsetNumbers[3];
    sunsetEndMinute->setOnValueChange([](float currentVal){
        lastMilightChange = millis();
        sunsetEndTime.setMinute((uint8_t)currentVal);
        });

    sunsetPage = new Page(13,"Sunset",sunsetNumbers,4,parentPage,nullptr,0);

    return sunsetPage;


}

Page* createSunPage(Page* parentPage){
    createSunTimes();

    Page* sunPage = new Page;

    Page* sunSubPages = new Page[3];

    sunSubPages[0] = *createSunrisePage(sunPage);
    sunSubPages[1] = *createSunsetPage(sunPage);

    sunBrightness = new DisplayNumber(EEPROM.read(12),0,maxLedNumber,1,1,0);
    sunBrightness->setOnValueChange([](float currentVal){
        lastMilightChange = millis();
    });

    sunSubPages[2] = Page(14,"brightness",sunBrightness,1,sunPage,nullptr,0);

    *sunPage = Page(4,"sunrise & set",nullptr,0,parentPage,sunSubPages,3);
    
    return sunPage;
}

Page* createLampPage(Page* parentPage){

    brightnessNumber = new DisplayNumber(EEPROM.read(0),0,maxLedNumber,1,1,0);
    
    Page* lampPage;

    Page* subPages = new Page[2];


    // create brightness page
    subPages[0] = Page(10,"brightness", brightnessNumber, 1, lampPage, nullptr, 0);
    brightnessNumber->setOnValueChange(onBrightnessChange);

    // create r g b page
    DisplayNumber* displayNumbers = new DisplayNumber[3];

    displayNumbers[0] = DisplayNumber(EEPROM.read(1),0,maxLedNumber,1,1,0,0,1);
    redNumber = &displayNumbers[0];
    redNumber->setOnValueChange(onRedChange);

    displayNumbers[1] = DisplayNumber(EEPROM.read(2),0,maxLedNumber,1,1,0,4,1);
    greenNumber = &displayNumbers[1];
    greenNumber->setOnValueChange(onGreenChange);

    displayNumbers[2] = DisplayNumber(EEPROM.read(3),0,maxLedNumber,1,1,0,8,1);
    blueNumber = &displayNumbers[2];
    blueNumber->setOnValueChange(onBlueChange);

    subPages[1] = Page(11,"r   g   b", displayNumbers, 3, lampPage, nullptr, 0);

    lampPage = new Page(4,"Lamp",nullptr,0,parentPage,subPages,2);
    return lampPage;
}

Page* createLightPage(){
    Page* lightsPage = new Page;

    Page* subPages = new Page[2];

    subPages[0] = *createLampPage(lightsPage);

    subPages[1] = *createSunPage(lightsPage);

    // set root page
    *lightsPage = Page(1,"lights", nullptr, 0, lightsPage, subPages, 2);
    return lightsPage;
}

Page* createPlantsPage(){
    Page* plantsPage = new Page;

    Page* subPages = new Page[4];

    // setting each plant page
    subPages[0] = Page(5,"plant 0", new DisplayNumber(0,0,100,0,0,2), 1, plantsPage, nullptr, 0);
    subPages[1] = Page(6,"plant 1", new DisplayNumber(0,0,100,0,0,2), 1, plantsPage, nullptr, 0);
    subPages[2] = Page(7,"plant 2", new DisplayNumber(0,0,100,0,0,2), 1, plantsPage, nullptr, 0);
    subPages[3] = Page(8,"plant 3", new DisplayNumber(0,0,100,0,0,2), 1, plantsPage, nullptr, 0);

    // set root page
    *plantsPage = Page(3,"plants",nullptr,0,plantsPage,subPages,4);
    return plantsPage;
}



Page* createSettingsPage(){
    Page* settingsPage = new Page;

    Page* subPages = new Page[1];

    subPages[0] = Page(9,"backlight",backlightNumber,1,settingsPage,nullptr,0);
    backlightNumber->setOnValueChange(onBacklightChange);

    

    // set root page
    *settingsPage = Page(2,"settings", nullptr, 0, settingsPage, subPages, 1);
    return settingsPage;
}

Page* initPages(){

    Page* startingPages = new Page[MAIN_PAGES_NUM];

    startingPages[0] = *createWeatherPage();
    startingPages[1] = *createLightPage();
    startingPages[2] = *createPlantsPage();
    startingPages[3] = *createSettingsPage();



    return startingPages;
}
