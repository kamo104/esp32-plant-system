#ifndef ROUTINES_INIT_H
#define ROUTINES_INIT_H

#include "../misc/functions.h"
#include "../numbers/TimeOfTheDay.h"

#include "../classes/RoutineManager.h"
#include "../config/definitions.h"
#include "../config/variablesInit.h"
#include "programClassesInit.h"

void screenUpdateRoutineFunction(unsigned long currentTime, Routine* self){

    if(currentTime-lastHumanInteraction<lcdTurnOffTimeout && backlightNumber->value()==0) backlightNumber->setValue(1);

    if(director->needToRedisplayCurrentPage == false) return;

    director->displayCurrentPage();

    *self->lastVariableUpdate = currentTime;
}

void ledSaveRoutineFunction(unsigned long currentTime, Routine* self){
    
    if(*self->lastVariableUpdate <= lastLedStateSave) return;
    Serial.println("SAVING LED DATA NOW");
    EEPROM.write(0,(uint8_t)brightnessNumber->value());
    EEPROM.write(1,(uint8_t)redNumber->value());
    EEPROM.write(2,(uint8_t)greenNumber->value());
    EEPROM.write(3,(uint8_t)blueNumber->value());

    EEPROM.commit();

    lastLedStateSave = currentTime;
}

void sunDatesSaveRoutineFunction(unsigned long currentTime, Routine* self){
    if(*self->lastVariableUpdate <= lastMilightSave) return;

    Serial.println("SAVING MILIGHT DATA NOW");
    // sunrise
    EEPROM.write(4,(uint8_t)sunriseStartMinute->value());
    EEPROM.write(5,(uint8_t)sunriseStartHour->value());
    EEPROM.write(6,(uint8_t)sunriseEndMinute->value());
    EEPROM.write(7,(uint8_t)sunriseEndHour->value());
    // sunset
    EEPROM.write(8,(uint8_t)sunsetStartMinute->value());
    EEPROM.write(9,(uint8_t)sunsetStartHour->value());
    EEPROM.write(10,(uint8_t)sunsetEndMinute->value());
    EEPROM.write(11,(uint8_t)sunsetEndHour->value());

    // sun brightness
    EEPROM.write(12,(uint8_t)sunBrightness->value());

    EEPROM.commit();

    lastMilightSave = currentTime;
}

void dhtReadRoutineFunction(unsigned long currentTime, Routine* self){
    try{
        float temperatureRead = dht->readTemperature();
        float humidityRead = dht->readHumidity();
        

        if(menu->currentPage()->title==nullptr) return;

        if(menu->currentPage()->index==0 && (temperatureRead != temperatureNumber->value() || humidityRead != humidityNumber->value())) director->needToRedisplayCurrentPage = true;

        temperatureNumber->setValue(temperatureRead);
        humidityNumber->setValue(humidityRead);

        *self->lastVariableUpdate=currentTime;

    }
    catch(int e){
        Serial.println("failed to read DHT temp and humidity");
    }
}

void sunsetRoutineFunction(unsigned long currentTime, Routine* self){
    if( ! globalTimeOfTheDay.isBetween(sunsetStartTime,sunsetEndTime) || brightnessNumber->value()==0){
        *self->lastVariableUpdate = currentTime;
        return;
    }
    int valueBefore = (int)milighthubBrightness.value();
    milighthubBrightness.setValue(abs(
            sunBrightness->value()-globalTimeOfTheDay.differenceInSeconds(sunsetStartTime)*
            sunBrightness->value()/sunsetEndTime.differenceInSeconds(sunsetStartTime)
            ));

    int valueAfter = (int)milighthubBrightness.value();

    if(valueAfter+1<=valueBefore){

        // Serial.printf("%s: %d\n","Sending milight update with brightness",(int)milighthubBrightness.value());
        milight.controllLight(milightColor,(int)milighthubBrightness.value());
        
        brightnessNumber->setValue((int)milighthubBrightness.value());

        if(menu->currentPage()->index==10) director->needToRedisplayCurrentPage = true; // if we're on the brightness page redisplay it
        
        lastLedChange = lastLedStateSave; // to disable saving during sunrises and sunsets
    } 


    *self->lastVariableUpdate = currentTime;
}

void sunriseRoutineFunction(unsigned long currentTime, Routine* self){
    // send put request to server with values that scale up
    if( ! globalTimeOfTheDay.isBetween(sunriseStartTime,sunriseEndTime)){
        *self->lastVariableUpdate = currentTime;
        return;
    }
    int valueBefore = (int)milighthubBrightness.value();
    milighthubBrightness.setValue(abs(
            globalTimeOfTheDay.differenceInSeconds(sunriseStartTime)*
            sunBrightness->value()/sunriseEndTime.differenceInSeconds(sunriseStartTime)
            ));


    int valueAfter = (int)milighthubBrightness.value();

    if(valueAfter>=valueBefore+1){

        // Serial.printf("%s: %d\n","Sending milight update with brightness",(int)milighthubBrightness.value());
        milight.controllLight(milightColor,(int)milighthubBrightness.value());
        
        brightnessNumber->setValue((int)milighthubBrightness.value());
        lastLedChange = lastLedStateSave; // to disable saving during sunrises and sunsets
    } 


    *self->lastVariableUpdate = currentTime;
}


void clockRefreshRoutineFunction(unsigned long currentTime, Routine* self){
    tm timeBefore = globalTime;

    getLocalTime(&globalTime);
    globalTimeOfTheDay.setDate(globalTime);

    currentHour->setValue(globalTime.tm_hour);
    currentMinute->setValue(globalTime.tm_min);


    *(self->lastVariableUpdate) = currentTime;
    if(menu->currentPage()->index==0 && globalTime.tm_min!=timeBefore.tm_min) director->needToRedisplayCurrentPage = true;
}

void lcdTurnOffRoutineFunction(unsigned long currentTime, Routine* self){

    if(currentTime-lastHumanInteraction>lcdTurnOffTimeout) backlightNumber->setValue(0);

    *self->lastVariableUpdate = currentTime;
}


void routinesInit(){
    // create routines to run in loop
    Routine* screenUpdateRoutine = new Routine;
    screenUpdateRoutine->function = screenUpdateRoutineFunction;
    screenUpdateRoutine->lastVariableUpdate = &lastDisplayUpdate;
    screenUpdateRoutine->updateIntervalLength = &refreshRate;

    Routine* ledSaveRoutine = new Routine;
    ledSaveRoutine->function = ledSaveRoutineFunction;
    ledSaveRoutine->lastVariableUpdate = &lastLedChange;
    ledSaveRoutine->updateIntervalLength = &memorySaveFrequency;

    Routine* dhtReadRoutine = new Routine;
    dhtReadRoutine->function = dhtReadRoutineFunction;
    dhtReadRoutine->lastVariableUpdate = &lastDhtRead;
    dhtReadRoutine->updateIntervalLength = &dhtReadInterval;


    Routine* sunriseRoutine = new Routine;
    sunriseRoutine->function = sunriseRoutineFunction;
    sunriseRoutine->lastVariableUpdate = new unsigned long(0);
    sunriseRoutine->updateIntervalLength = &milightRoutineFrequency;

    Routine* sunsetRoutine = new Routine;
    sunsetRoutine->function = sunsetRoutineFunction;
    sunsetRoutine->lastVariableUpdate = new unsigned long(0);
    sunsetRoutine->updateIntervalLength = &milightRoutineFrequency;



    Routine* sunDatesSaveRoutine = new Routine;
    sunDatesSaveRoutine->function = sunDatesSaveRoutineFunction;
    sunDatesSaveRoutine->lastVariableUpdate = &lastMilightChange;
    sunDatesSaveRoutine->updateIntervalLength = &memorySaveFrequency;



    Routine* clockRefreshRoutine = new Routine;
    clockRefreshRoutine->function = clockRefreshRoutineFunction;
    clockRefreshRoutine->lastVariableUpdate = new unsigned long(0);
    clockRefreshRoutine->updateIntervalLength = new unsigned long(1000);



    Routine* lcdTurnOffRoutine = new Routine;
    lcdTurnOffRoutine->function = lcdTurnOffRoutineFunction;
    lcdTurnOffRoutine->lastVariableUpdate = new unsigned long(0);
    lcdTurnOffRoutine->updateIntervalLength = &lcdCheckTurnoffFrequency;


    routineManager->addRoutine(screenUpdateRoutine);
    routineManager->addRoutine(ledSaveRoutine);
    routineManager->addRoutine(dhtReadRoutine);

    if(connectionMode == true) routineManager->addRoutine(sunriseRoutine);
    if(connectionMode == true) routineManager->addRoutine(sunsetRoutine);


    if(connectionMode == true) routineManager->addRoutine(clockRefreshRoutine);
    routineManager->addRoutine(sunDatesSaveRoutine);
    routineManager->addRoutine(lcdTurnOffRoutine);

}

#endif